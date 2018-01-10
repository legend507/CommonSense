/*
書式指定変換した出力を文字列に格納します

【書式】
#include <stdio.h>
int sprintf(char *str, const char *format,  ．．． ); 
【引数】
char *str　：　変換した出力を格納する文字列。
const char *format　：　書式指定文字列。　詳しくはprintf関数を参照のこと。
．．．　：　可変個引数。この引数を書式指定に従い変換します。書式指定文字列はこの引数と同数必要です。

【戻り値】
成功時　：　strに格納した文字数（最後の'\0'は除く）
失敗時　：　EOF
【使用例】
// step1: put char array into str, 
// step2: use puts(str); to output what's in str
*/
#include        <stdio.h>

int     main(void)
{
        int             i;
        char    str[100];
        char    str1[] = "文字列";
        char    str2[] = "連結";
        char    str3[] = "お手軽";

        for (i=1; i<=10; i++) {
                /* ループ回数を文字列に格納 */
                sprintf(str,"ループ回数：%2d",i);
                puts(str);
        }

        sprintf(str,"%sの%sだって%sよ",str1,str2,str3);
        puts(str);

        return 0;
}
/*
【実行結果】
ループ回数： 1
ループ回数： 2
ループ回数： 3
ループ回数： 4
ループ回数： 5
ループ回数： 6
ループ回数： 7
ループ回数： 8
ループ回数： 9
ループ回数：10
文字列の連結だってお手軽よ
*/
