#
#	@file	configdef.mk
#	@brief	コンフィグレーション
#	
#	@author	Daisuke Kunimune
#	@date	2014.07.19
#

# ------------------------------------------------------------------
# ◆設定
# ------------------------------------------------------------------
#PLACE				=	cygwin
#PLACE				=	ubuntu32bit
PLACE				=	ubuntu64bit
#PLACE				=	self
#PLACE				=	cross
#PLACE				=	cross_poky
#PLACE				=	cross_bbb
#PLACE				=	cross_raspi
#PLACE				=	raspi
#PLACE				=	bbb

# -------------------
# ログ関連
# -------------------
DEBUG				=	ON
#LOGLEVEL_DEBUG		=	LOGLEVEL_TRACE
LOGLEVEL_DEBUG		=	LOGLEVEL_DEBUG
#LOGLEVEL_DEBUG		=	LOGLEVEL_INFO
LOGLEVEL_RELEASE	=	LOGLEVEL_INFO
#LOGLEVEL_RELEASE	=	LOGLEVEL_WARNING

#LOG_FORMAT_DEBUG	=	LOG_FORMAT_FILE_FUNC_LINE
LOG_FORMAT_DEBUG	=	LOG_FORMAT_FUNC_LINE
LOG_FORMAT_RELEASE	=	LOG_FORMAT_FUNC

LOG_COLOR_ON		=	ON

# 最適化
#OPTIMIZE			=	-Ofast

# -------------------
# CRYPTO関連
# ・CRYPTOMETHOD：通常はONにすること(OpenSSLが入ってるかどうかは別設定)
#   ⇒ CRYPTOMETHOD が OPENSSL なら PANACRYPT を使わない、OPENSSL 以外なら PANACRYPT を使う
# -------------------
#DATA_VERIFY			=	ON
CRYPTOMETHOD		=	OPENSSL

# -------------------
# ネットワーク関連
# -------------------
NETMETHOD			=	SERVER

# -------------------
# BBB関連
# ・BBB_GPIO_LED    ：P9_14にLEDを接続すること
# ・BBB_GPIO_LED_PWM：P9_14にLEDを接続すること
# ・BBB_MOTOR       ：P9_15、P9_23、P9_27、P9_30にモーターを接続すること
# ・BBB_SERVO       ：サーボ(SG90)を接続すること
# ・BBB_I2C         ：P9_17、P9_18にI2Cデバイスを接続すること
# -------------------
#BBB_GPIO_LED		=	ON
#BBB_GPIO_LED_PWM	=	ON
#BBB_MOTOR			=	ON
#BBB_SERVO			=	ON
#BBB_I2C			=	ON

# -------------------
# テスト対象選択(ディレクトリ)
# ・TEST_DIR：通常はCTESTSを設定すること
#   ⇒ CANTESTはMsgFilterのITテストプログラム
# -------------------
#TEST_DIR			=	CANTEST
#TEST_DIR			=	CTESTS
TEST_DIR			=	CANPG

# -------------------
# テスト対象選択(個別)
# -------------------
# TEST_DIR = CANTEST のテスト対象
TEST_CANTEST		=	ON

# TEST_DIR = CTESTS のテスト対象
TEST_HELLO			=	ON
#TEST_CRYPTO			=	ON
#TEST_CAN			=	ON
#TEST_BBB			=	ON

# TEST_DIR = CANPG のテスト対象
TEST_CANPG			=	ON
# SYSのテストを対象にする場合のみONにする
TEST_CANPG_SYS		=	ON
