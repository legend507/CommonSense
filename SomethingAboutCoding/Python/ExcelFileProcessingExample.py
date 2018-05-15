#!/usr/bin/env python3
# -*- encoding: utf-8 -*-

'''
SELinux log merge

ドメイン機能担当各チーム から セキュリティチーム あてに不定期提出される SELinuxログ を入力し、
集中管理用CSVデータに仕立てるユーティリティツール。
(1) 入力ログは、所定のCSVデータレコード形式(各列が所定の意味を持つ)に書式化する。
(2) CSVファイルは、入出力兼用。
    既存レコードがある場合、上記(1)と併せて入力となる。
(3) 上記(1)(2)のすべてをマージし、所定の順序にソートする。
(4) 結果をCSVファイルへ書き出す。

@author kyoneda1@gw.nsw.co.jp
$Revision: 6203 $ $Date:: 2018-05-14 17:42:42 +0900#$
'''

import argparse
import csv
import inspect
import os
import os.path
import re
import sys
from collections import defaultdict, namedtuple
from datetime import datetime
from enum import Enum, unique


def my_name():
    return os.path.basename(sys.argv[0])

def print_(*args, **kwargs):
    print(my_name() + ':', *args, **kwargs)
def print_error(*args, **kwargs):
    print_(*args, file=sys.stderr, **kwargs)
print_verbose = lambda *args, **kw: None    # 空関数を既定値にしとく, @see main()

def whoami():
    return inspect.stack()[1][3]    # callerの関数名

def die(message, status=-1):
    '''
    異常終了用下請け - エラーメッセージを出力しプロセス終了
    '''
    print_error(message)
    sys.exit(status)

def find_f(root):
    '''
    指定ディレクトリ下のファイルパス名リストを求めて返す - find root -type f 相当
    '''
    result = []
    for root, dirs, files in os.walk(root):
        for f in files:
            path = os.path.join(root, f)
            if os.path.isfile(path):
                result.append(path)
    return result

def grep_q(pattern, path):
    '''
    指定ファイルが指定パターンを含むか調べて返す - grep -q 相当
    '''
    p = re.compile(pattern, flags=re.MULTILINE)
    with open(path, 'r') as f:
        return p.search(f.read()) != None

def eval_logfiles(paths):
    '''
    コマンドライン引数 logfiles を評価しファイルパス名リストを返す
    - 実在ファイル → as-is採用
    - 実在ディレクトリ → ディレクトリ下の全ファイルを求める
    - ファイルシステムに存在しない要素 → エラー報告後異常終了
    '''
    result = []
    for path in paths:
        if os.path.isfile(path):
            result.append(path)
        elif os.path.isdir(path):
            result += find_f(path)
        elif not os.path.exists(path):
            die('{}: No such file or directory'.format(path))
    return sorted(result)

def classify_logfiles(paths):
    '''
    指定ログファイルを 許容/除外 に仕分けし、各パス名リストを返す.
    - 除外 の定義 : 特定文字列を含む
    - 許容 の定義 : 上記外
    - パス名リスト×2 を返す
    '''
    # 除外ファイル(のパス名リスト)を求める。
    rejected = [path for path in paths if grep_q('Warning!', path)]
    # 許容ファイルリスト = 分母 - 除外ファイルリスト
    accepted = list(set(paths) - set(rejected))
    return (sorted(accepted), sorted(rejected))

def write_file(path, lines):
    '''
    listをテキストファイルに書き出すヘルパー
    '''
    with open(path, mode='w') as f:
        if len(lines) > 0:
            f.write(os.linesep.join(lines) + os.linesep)

def encoding_of(path):
    '''
    文字エンコーディングが一意予定できないテキストファイルのエンコーディングを強引に求めて返す
    - CSVファイル が、それ。 Microsoft Excel は、保存 する毎に shift_jis へデフォルト誘導する...。
    @see http://myfuturesightforpast.blogspot.jp/2015/01/auto-detecting-japanese-file-enconding.html
    '''
    encodings = ['utf-8-sig', 'shift_jis', 'cp932'] # Microsoft Excel on 日本語Windows 想定
    for encoding in encodings:
        with open(path, encoding=encoding) as f:
            try:
                f = f.read()
            except UnicodeDecodeError:
                continue
        return encoding

@unique
class Col(Enum):
    '''
    列 の識別子
    '''            # (列番号, ログテキストから値を取り出す正規表現)     # 18MY版 : [列番号] 列名
    ASSIGN         = ( 0)                                               # [ 0] 担当
    STATE          = ( 1)                                               # [ 1] 状態
    STATE_REMARKS  = ( 2)                                               # [ 2] 状態詳細
    FIXED_BY       = ( 3)                                               # [ 3] 対応ファイル
    FIXED_BUILD    = ( 4)                                               # [ 5] 対応 ver.
    MERGED_DATE    = ( 5)                                               # [16] ログ追加日付
    # @note: build_id はめんどくさい - 下記のようなログあり
    #        <space>YYYY-MM-DD<space>HH:MM:SS の「直前まで」をキャプチャすることで、拾う。
    # ------------------------------------------------------------------------------------------------------------------------------------------------------------------
    # build_id=msm8996-userdebug 8.0.0 OPR6.170623.013 eng.masuda.20171123.015925 test-keys 1970-01-01 00:00:36.175 logd(    0): SELinux: Loaded service_contexts from:
    # ------------------------------------------------------------------------------------------------------------------------------------------------------------------
    BUILD          = ( 6, re.compile(r'(^|\s)build_id=(.+)\s+\d{4}-\d{2}-\d{2}\s\d{2}:\d{2}:\d{2}'))    # [15] build_id
    EXAMPLE_POLICY = ( 7)                                               # [ 4] sepolicy
    SCONTEXT       = ( 8, re.compile(r'\sscontext=([^:]+:){2}([^:]+)')) # [ 6] scontext
    TCONTEXT       = ( 9, re.compile(r'\stcontext=([^:]+:){2}([^:]+)')) # [ 7] tcontext
    TCLASS         = (10, re.compile(r'\stclass=(\S+)'))                # [ 8] tclass
    SERVICE        = (11, re.compile(r'\sservice=(\S+)'))               # [ 9] service
    NAME           = (12, re.compile(r'\sname=(\S+)'))                  # [10] name
    PATH           = (13, re.compile(r'\spath=(\S+)'))                  # [11] path
    DEV            = (14, re.compile(r'\sdev=(\S+)'))                   # [12] dev
    INO            = (15, re.compile(r'\sino=(\S+)'))                   # [13] ino
    ACCESS         = (16, re.compile(r'\savc:\s+\S+\s+({[^}]+})'))      # [14] access
    ORIGINAL_FILE  = (17)                                               # - 18MY版には存在しない -
    ORIGINAL_LOG   = (18, re.compile(r'(^.*$)'))                        # [17] log
    def __init__(self, index, pattern=None):
        self.index = index
        self.pattern = pattern

class Row(defaultdict):
    '''
    行 の表現
    '''
    HEADER = [col.name for col in Col]
    def __init__(self):
        super().__init__(lambda: '')

    @classmethod
    def from_row(cls, row):
        '''
        csv.reader ⇒ Rowオブジェクト
        '''
        if len(row) != len(Col) or row == cls.HEADER:
            return None
        result = Row()
        for col in Col:
            result[col] = row[col.index]

        # Microsoft Excelのお節介仕様 - 日付認識すると常にデフォルト書式(Control Panel [地域と言語])で保存 - をケアする補正
        try:
            col = Col.MERGED_DATE
            result[col] = datetime.strptime(result[col], '%Y/%m/%d').strftime(cls.DATE_FORMAT)  # 日本語Windowsでのデフォルトがこれらしい
        except:
            pass

        return result

    ACCEPTABLE = namedtuple('Acceptable', 'required rejects')(
        # "必須"パターン : これがマッチ*しない*ログ行は捨てられる
        required = re.compile(r'build_id=.*denied'),
        # "拒否"パターン : これがマッチ*した*ログ行は捨てられる
        rejects   = re.compile(r'^\s*$|avc:\s+granted|Warning!'),
        )
    @classmethod
    def acceptable(cls, log):
        return cls.ACCEPTABLE.required.search(log) and \
           not cls.ACCEPTABLE.rejects.search(log)

    DATE_FORMAT = '%Y-%m-%d'
    TODAY = datetime.now().strftime(DATE_FORMAT)
    @classmethod
    def from_log(cls, log, logfile, lnum, rejected):
        '''
        ログ行テキスト ⇒ Rowオブジェクト
        '''
        if not cls.acceptable(log):
            with open(rejected, 'a') as f:
                f.write('{}:{}:{}{}'.format(logfile, lnum, log, os.linesep)) # 捨てたログ行はファイル記録を残す
            return None
        result = Row()
        result[Col.ORIGINAL_FILE] = logfile
        result[Col.MERGED_DATE] = cls.TODAY
        for col in Col:
            if col.pattern:
                matched = col.pattern.search(log)
                if matched:
                    result[col] = matched.groups()[-1]  # キャプチャグループの最終要素
        if result[Col.SCONTEXT] and result[Col.TCONTEXT] and result[Col.TCLASS] and result[Col.ACCESS]:
            result[Col.EXAMPLE_POLICY] = 'allow {} {}:{} {}'.format(result[Col.SCONTEXT], result[Col.TCONTEXT], result[Col.TCLASS], result[Col.ACCESS])
        return result

    def to_list(self):
        '''
        self ⇒ list(カラム値)
        '''
        return [self[col] for col in Col]

    COLS = namedtuple('Cols', 'equivalence sort_key')(
        # for uniqued(): 等価要素の判定: 並び順に意味はない
        equivalence = (
            Col.SCONTEXT,
            Col.TCONTEXT,
            Col.TCLASS,
            Col.SERVICE,
            Col.NAME,
            Col.PATH,
            Col.DEV,
            # Col.INO,  # これを有効にすると i-node番号を等価判定に使用する
                        # つまり Col.NAME と Col.PATH の両方が空であっても
                        # 同一 Col.TCONTEXT ディレクトリ配下の 異なるファイルの違いを判定できるようになる
            Col.ACCESS,
            # Col.ORIGINAL_FILE,  # これを有効にすると スコープは 1ログファイル に限定され 複数ログファイルにまたがる等価は発生しなくなる
        ),
        # for sort(): ソートキー: 並び順 が 優先順 [第1キー, 第2キー, ...]
        sort_key = (
            Col.SCONTEXT,
            Col.TCONTEXT,
            Col.TCLASS,
            Col.SERVICE,
            Col.NAME,
            Col.PATH,
            Col.DEV,
            Col.INO,
            Col.ACCESS,
            Col.BUILD,
            Col.STATE,
        ),
    )

    @classmethod
    def uniqued(cls, rows):
        '''
        list(Row)から等価要素の重複を排除
        '''
        before = len(rows)

        key_of = lambda row: tuple(row[col] for col in cls.COLS.equivalence)
        hint_of = lambda row: tuple(row[Col.BUILD])

        # [pass-1] 抽出用補助情報 : {等価判定キー, ヒント情報}  (ヒント は当面 Col.BUILD のみ)
        #
        #   仕様変更(追加):
        #   - 旧: 入力内で等価キー初出現(先勝ち)なものを抽出 (これなら 1 pass で可だった)
        #   - 新: 等価グループ内でなるべく直近のbuild_idのものを抽出
        #   ※ 等価判定ルールは変わらない、どれを残す(抽出する)のかだけの違い。
        #   ※ build_idの新旧判定はファジー(SIチーム[のみ]裁量、命名則が機種途上で変わることもあり)。
        #      ここでは「文字辞書順とみなせる」と割り切り前提する。(これが成立しなくなるような途上命名則変更には対応不可)
        hint = {}
        hint_set = hint.__setitem__
        hint_get = hint.__getitem__
        for row in sorted(rows, key=lambda row: hint_of(row), reverse=True):
            key = key_of(row)
            if key not in hint:   # 降順ソート の 初出
                hint_set(key, hint_of(row))

        # [pass-2] 対象要素を抽出
        done = set()    # ログファイル内での多数同一keyログ重複もあるので、これ(既に抽出済みか?)はこれで必要。
        done_add = done.add
        def is_target(row):
            key = key_of(row)
            if key not in done and hint_of(row) == hint_get(key):   # 未抽出 かつ ヒント合致
                done_add(key)
                return True
            else:
                return False
        rows = [row for row in rows if is_target(row)]

        print_verbose('{}({} row(s))\t{} row(s)'.format(whoami(), before, len(rows)))
        return rows

    @classmethod
    def sort(cls, rows):
        '''
        list(Row)をソート : 解析担当者friendlyな所定順序に.
        '''
        print_verbose('{}({} row(s)'.format(whoami(), len(rows)))
        def cell(row, col):
            value = row[col]
            return value if col != Col.STATE or value else '\uffff' # STATE列未記入(未対処)なものを後方にしたい
        rows.sort(key=lambda row: tuple(cell(row, col) for col in cls.COLS.sort_key))

def load(csvfile):
    '''
    CSVファイルの内容を読み list(Row) を返す
    '''
    with open(csvfile, 'r', encoding=encoding_of(csvfile)) as f:
        reader = csv.reader(f, delimiter=',', quotechar='"')
        rows = list(filter(None, [Row.from_row(r) for r in reader]))
        print_verbose('{}({})\t{} row(s)'.format(whoami(), csvfile, len(rows)))
        return rows

def load_log(logfile, rejected):
    '''
    ログファイルの内容を読み list(Row) に仕立てて返す
    '''
    with open(logfile, 'r') as f:
        rows = list(filter(None, [Row.from_log(line.rstrip(), logfile, lnum, rejected) for lnum, line in enumerate(f, start=1)]))
        print_verbose('{}({})\t{} row(s)'.format(whoami(), logfile, len(rows)))
        return rows

def save(rows, csvfile):
    '''
    list(Row) を CSV形式 でファイル保存
    '''
    if os.path.isfile(csvfile):
        os.rename(csvfile, csvfile + '~')   # 既存ならばbackup : 1世代のみ, バックアップファイルが既存でも置換される
    with open(csvfile, 'w', encoding='utf-8-sig') as f: # UTF-8 with BOM : Microsoft Excel が文字化けせず認識するエンコーディング
        writer = csv.writer(f, delimiter=',', quotechar='"')
        writer.writerow(Row.HEADER)
        for row in rows:
            writer.writerow(row.to_list())
        print_verbose('{}({})\t{} row(s)'.format(whoami(), csvfile, len(rows)))

def reduced(rows):
    '''
    list(Row) の冗長性を除去して返す
    '''
    before = len(rows)

    # 蓄積過去情報(in CSV)も含めての冗長性排除は、曖昧模糊としたアイディアレベルの域を出ないので、当面手を出さない。
    # 実際の運用過程で、現実に根ざしたまっとうな仕様アイディアが浮上してきたら、その際に検討する。
    print_verbose('@note: {}() not implemented [return list as-is].'.format(whoami()))

    print_verbose('{}({} row(s))\t{} row(s)'.format(whoami(), before, len(rows)))
    return rows




def main():
    '''
    entry point.
    '''
    # コマンドライン引数 取り込み
    parser = argparse.ArgumentParser(
        description='This is a tool to merge SELinux log files and make it CSV{sep}  {rev}{sep}  @author {author}' \
            .format(sep=os.linesep, rev='$Revision: 6203 $ $Date:: 2018-05-14 17:42:42 +0900#$', author='kyoneda1@gw.nsw.co.jp, ryano1@gw.nsw.co.jp'),
        formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('logfiles', \
        action='store', \
        nargs='+', \
        help='The paths of the log file or the directory where the log files are located.')
    parser.add_argument('-c', '--csv-file', \
        action='store', \
        nargs=None, \
        default='./SELinuxlog.csv', \
        help='CSV File path where you want to input/output. (default: ./SELinuxlog.csv)')
    parser.add_argument('-v', '--verbose', \
        action='store_true', \
        default=False, \
        help='verbose mode if this flag is set. (default: False)')
    args = parser.parse_args()
    #print(args)
    if args.verbose:
        global print_verbose
        print_verbose = print_

    # 入力対象ログファイル(パス名)決定
    accepted, rejected = classify_logfiles(eval_logfiles(args.logfiles))
    ## 各々の内容を、各痕跡ファイルに残す。
    prefix = os.path.splitext(args.csv_file)[0]
    write_file(prefix + '.file.accepted', accepted)
    write_file(prefix + '.file.rejected', rejected)
    ## 除外 の警告メッセージ
    if rejected:
        print_error('*rejected* {}'.format(rejected))

    # 入力
    rows = []
    ## ログファイル(s)
    rejected = prefix + '.line.rejected'
    if os.path.exists(rejected):
        os.remove(rejected) # 追記(append mode)で書きたいので最初に削除しとく : 存在しないとき FileNotFoundError 投げられるので検査必要...
    for logfile in accepted:
        rows += load_log(logfile, rejected)
    rows = Row.uniqued(rows)    # 今回入力ログ内での冗長性(重複要素)を除去
    ## 既存CSVファイル(の内容)を追加
    if os.path.isfile(args.csv_file):
        rows += load(args.csv_file)

    # 所定順(解析担当者friendly順)に
    Row.sort(rows)

    # 冗長性を除去し保存
    save(reduced(rows), csvfile=args.csv_file)

if __name__ == '__main__':
    main()
