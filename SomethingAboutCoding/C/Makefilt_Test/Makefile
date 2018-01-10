TOPDIR				=	.
include					$(TOPDIR)/mk/color.mk
include                 $(TOPDIR)/mk/config.mk

SUBDIRS             =   folder1 MsgFilter

export DPRINT		=	'\n'$(COLOR_YELLOW)'*** target "$@" is done, $$DEBUG=$(DEBUG) ***'$(COLOR_END)'\n'
export DPRINTTOP	=	'\n'$(COLOR_BLINK)$(COLOR_YELLOW)'*** target "$@" is done, $$DEBUG=$(DEBUG) ***'$(COLOR_END)'\n'

.PHONY:					all clean $(SUBDIRS) preprocess postprocess

all:					preprocess $(SUBDIRS) $(GOALS) postprocess

include					$(TOPDIR)/mk/target.mk

preprocess:
	@echo 'preprocess'	
	@echo -e $(COLOR_BLUE)'preprocess: $$PLACE = '$(PLACE)', $$SUBDIRS = '$(SUBDIRS)', $$GOALS = '$(GOALS)''$(COLOR_END)

postprocess:
	@echo 'postprocess'	
	@echo -e $(COLOR_BLUE)'postprocess: All is well'$(COLOR_END)

clean:
	@echo 'clean'	
	rm -f *.o

$(SUBDIRS):
	$(MAKE) -C $@