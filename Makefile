WIDTH= 79

define building
	@printf '%s\n' "-> Building $1"
	@make -sC $1 > /dev/null
	@echo "√"
endef

define compiling
	@printf '%s\n' "-> Compiling $1"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $1 -o $2
	@echo "√"
endef

define finishing
	@printf '%s\n' "-> Finishing $1"
	@$(CC) $(CFLAGS) $(CPPFLAGS) $2 -o $1 $(LIBS)
	@echo "√"
endef

define cleaning
	@printf '%s\n' "-> Cleaning $1"
	@make $2 -sC $1 > /dev/null
	@echo "√"
endef

define removing
	@printf '%s\n' "-> Removing $1"
	@$(RM) $1 > /dev/null
	@echo "√"
endef

SRCS		= $(addprefix srcs/, \
			  	parsing.c \
			  	stack.c \
				stackop.c \
				sortsmallest.c \
				sortsmall.c \
				costsort.c \
				utils.c \
				sort.c \
			  	main.c \
				)

BONUS		= $(addprefix srcs/, \
			  	parsing.c \
			  	stack.c \
				stackop.c \
				utils.c \
				sortsmallest.c \
				sortsmall.c \
				costsort.c \
				sort.c \
			 	get_next_line_utils.c \
				get_next_line.c \
				checker_utils.c \
			  	checker.c \
			  )

OBJS		= $(SRCS:.c=.o)

BONUS_OBJS	= $(BONUS:.c=.o)

NAME		= push_swap

RM			= rm -f

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address

CPPFLAGS	= -Iincludes

LIBS		= ./libft/libft.a

%.o : %.c
			$(call compiling,$<,$(<:.c=.o),0)

${NAME}:	$(OBJS)
			$(call building,libft)
			$(call finishing,$(NAME), $(OBJS))

checker:	$(NAME) $(BONUS_OBJS)
			$(call finishing,checker,$(BONUS_OBJS))

all:		$(NAME)

bonus:		checker

clean:	
			$(call removing,$(OBJS))
			$(call removing,$(BONUS_OBJS))

fclean:		clean
			$(call cleaning,libft,fclean)
			$(call removing,${NAME})
			$(call removing,checker)

re:			fclean all
