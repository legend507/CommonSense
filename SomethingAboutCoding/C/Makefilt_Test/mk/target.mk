#
#	@file	target.mk
#	@brief	共通ターゲットの定義
#	
#	@author	Daisuke Kunimune
#	@date	2015.04.14
#

# 
# 実行ファイル
# 
$(TARGET_EXE):			$(OBJS) $(LIBS) Makefile
	@echo -e $(COLOR_CYAN)'$$TARGET_EXE($(TARGET_EXE)) is executed'$(COLOR_END)
	@echo -e $(COLOR_CYAN)'MAKECMDGOALS = '$(MAKECMDGOALS)$(COLOR_END)
	@echo -e $(COLOR_CYAN)'MAKEFLAGS = '$(MAKEFLAGS)$(COLOR_END)
	@echo -e $(COLOR_CYAN)'GOALS = '$(GOALS)$(COLOR_END)
	@echo -e $(COLOR_CYAN)'SRCS = '$(SRCS)$(COLOR_END)
	@echo -e $(COLOR_CYAN)'OBJS = '$(OBJS)$(COLOR_END)
	@echo -e $(COLOR_CYAN)'$$< = $<'$(COLOR_END)
	@echo -e $(COLOR_CYAN)'$$@ = $@'$(COLOR_END)
	@echo -e $(COLOR_CYAN)'$$^ = $^'$(COLOR_END)
	@echo -e $(COLOR_CYAN)'$$? = $?'$(COLOR_END)
	@echo -e $(COLOR_CYAN)'LDFLAGS = $(LDFLAGS)'$(COLOR_END)

#	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)
	g++ $(LDFLAGS) -o $@ $(OBJS) $(LIBS)
	@echo -e $(DPRINT)

# 
# ライブラリ
# 
$(TARGET_LIB):			$(OBJS) Makefile
	@echo -e $(COLOR_CYAN)'MAKECMDGOALS = '$(MAKECMDGOALS)$(COLOR_END)
	@echo -e $(COLOR_CYAN)'MAKEFLAGS = '$(MAKEFLAGS)$(COLOR_END)
	@echo -e $(COLOR_CYAN)'SRCS = '$(SRCS)$(COLOR_END)
	@echo -e $(COLOR_CYAN)'OBJS = '$(OBJS)$(COLOR_END)
	@echo -e $(COLOR_CYAN)'$$< = $<'$(COLOR_END)
	@echo -e $(COLOR_CYAN)'$$@ = $@'$(COLOR_END)
	@echo -e $(COLOR_CYAN)'$$^ = $^'$(COLOR_END)
ifeq ($(strip $(TARGET_TYPE)),SHARED_LIB)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $(OBJS)
else
	$(AR) rcv $@ $^
endif
	@echo -e $(DPRINT)

# 
# 共通クリーン
# 
clean_common:
	@echo -e $(COLOR_CYAN)'MAKECMDGOALS = '$(MAKECMDGOALS)$(COLOR_END)
	@echo -e $(COLOR_CYAN)'GOALS = '$(GOALS)$(COLOR_END)
	rm -f *.o
	rm -f *.i
	rm -f *.s
	rm -f *.a
	rm -f *.so
	rm -f *.out
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.gcov
	rm -f *.info
	rm -f massif.out.*
	rm -f ms_print.out.*
	rm -f ms_print.tmp.*
	rm -f core
	rm -rf lcov.html
	rm -rf doxygen

# 
# .c から .o を生成するルール
# 
.c.o:
	@echo -e $(COLOR_CYAN)'$$< = $<'$(COLOR_END)
	@echo -e $(COLOR_CYAN)'$$@ = $@'$(COLOR_END)
	@echo -e $(COLOR_CYAN)'$$^ = $^'$(COLOR_END)
	@echo -e $(COLOR_CYAN)'CFLAGS = $(CFLAGS)'$(COLOR_END)
	$(CC) -c $(CFLAGS) -o $@ $<

.cpp.o:
	@echo -e $(COLOR_CYAN)'$$< = $<'$(COLOR_END)
	@echo -e $(COLOR_CYAN)'$$@ = $@'$(COLOR_END)
	@echo -e $(COLOR_CYAN)'$$^ = $^'$(COLOR_END)
	@echo -e $(COLOR_CYAN)'CFLAGS = $(CFLAGS)'$(COLOR_END)
	$(CXX) -c $(CFLAGS) -o $@ $<

for-debug:
	@echo -e $(COLOR_CYAN)'CFLAGS = $(CFLAGS)'$(COLOR_END)
	@echo -e $(COLOR_CYAN)'LDFLAGS = $(LDFLAGS)'$(COLOR_END)
