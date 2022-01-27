WIDTH= 79

define compiling
	@printf '%s\t' "-> Compiling $1"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $1 -o $2
	@echo "√"
endef

define finishing
	@printf '%s\t' "-> Finishing $1"
	@$(CC) $(CFLAGS) $(CPPFLAGS) $2 -o $1 $(LIBS)
	@echo "√"
endef

define cleaning
	@printf '%s\t' "-> Cleaning $1"
	@make $2 -sC $1 > /dev/null
	@echo "√"
endef

define removing
	@printf '%s\t' "-> Removing $1"
	@$(RM) $1 > /dev/null
	@echo "√"
endef

SRCS			= $(addprefix srcs/, \
				  	utils.c \
				  	routine.c \
			  		main.c \
					)

BONUS			= $(addprefix srcs/, \
			  		)

OBJS			= $(SRCS:.c=.o)

BONUS_OBJS		= $(BONUS:.c=.o)

NAME			= philo

NAME_BONUS		= philo_bonus

RM				= rm -f

CC				= cc

CFLAGS			= -Wall -Wextra -Werror -g

CPPFLAGS		= -Iincludes

LIBS			= -lpthread

%.o : %.c
				$(call compiling,$<,$(<:.c=.o),0)

${NAME}:		$(OBJS)
				$(call finishing,$(NAME), $(OBJS))

${NAME_BONUS}:	$(NAME) $(BONUS_OBJS)
				$(call finishing,$(NAME_BONUS),$(BONUS_OBJS))

all:			$(NAME)

bonus:			$(NAME_BONUS)

clean:	
				$(call removing,$(OBJS))
				$(call removing,$(BONUS_OBJS))

fclean:			clean
				$(call removing,$(NAME))
				$(call removing,$(NAME_BONUS))

re:				fclean all
