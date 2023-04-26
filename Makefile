##
## EPITECH PROJECT, 2023
## Corewar bootstrap
## File description:
## Makefile
##

PART_COUNT		:=	2
P1_NAMES		:=	write-some-text			\
					write-a-number-as-text	\
					write-a-number-as-int	\
					without-padding			\
					with-padding

P2_NAMES		:=	yolotron-asm			\
					yolotron-vm

BINS			:=

$(foreach i,$(shell seq -s' ' $(PART_COUNT)),							\
$(foreach j,$(shell seq -s' ' $(words $(P$i_NAMES))),$(eval				\
BINS			+=	$(addprefix part$i/step$j/,$(word $j,$(P$i_NAMES)))	\
)))

all: $(BINS)

$(BINS):	%:	%.c
	@gcc -o $@ $<

clean:
	@rm -f *.bytecode

fclean:	clean
	@rm -f $(BINS)

re:		fclean all

.PHONY:	all clean fclean re
