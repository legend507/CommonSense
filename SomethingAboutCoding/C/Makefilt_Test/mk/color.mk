# ------------------------------------------------------------------
# ◆カラー定義
# ------------------------------------------------------------------
# 00=none 01=bold 04=underscore 05=blink 07=reverse 08=concealed
COLOR_BOLD			=	'\x1b[01m'					# 太文字
COLOR_BLINK			=	'\x1b[05m'					# 輝度高くする？
COLOR_BOLD			=	'\x1b[05m'					# 太文字
COLOR_YELLOW		=	'\x1b[43m\x1b[30m'			# 00: 黄背景(Yellow)黒文字(Black)	# COLOR_YELLOW		LOG_TMP
COLOR_RED			=	'\x1b[41m\x1b[37m'			# 01: 赤背景(Red)白文字(White)		# COLOR_RED			LOG_ERR
COLOR_CYAN			=	'\x1b[46m'					# 02: 水背景(Cyan)					# COLOR_CYAN		LOG_DEBUG
COLOR_BLACK			=	'\x1b[40m\x1b[37m'			# 03: 黒背景(Black)白文字(White)	# COLOR_BLACK		default
COLOR_BLUE			=	'\x1b[44m\x1b[37m'			# 04: 青背景(Blue)白文字(White)		# COLOR_BLUE		LOG_INFO
COLOR_MAGENTA		=	'\x1b[45m'					# 05: 紫背景(Magenta)				# COLOR_PURPLE		LOG_WARNING
COLOR_GREEN			=	'\x1b[42m'					# 06: 緑背景(Green)					# COLOR_GREEN		LOG_NOTICE
COLOR_WHITE			=	'\x1b[47m'					# 07: 白背景(White)
COLOR_END			=	'\x1b[0m'					# エスケープ終了
