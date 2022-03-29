WIDTH= 79

define compiling
	@printf 'Compiling %s\n' $1
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $1 -o $2
endef

define finishing
	@printf 'Finishing %s\n' $1
	@$(CC) $(CFLAGS) $(CPPFLAGS) $2 -o $1 $(LIBS)
endef

define cleaning
	@echo -n Cleaning
	@printf '%s\n' $1
	@make $2 -sC $1 > /dev/null
endef

define removing
	@printf ' %s ' $1
	@$(RM) $1 > /dev/null
endef

SRCS			= $(addprefix srcs/, \
				  	utils.c \
				  	routine_utils.c \
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

CFLAGS			= -Wall -Wextra -Werror -g#-fsanitize=thread

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
				@echo -n Removing
				$(call removing,$(OBJS))
				@echo -n Removing
				$(call removing,$(BONUS_OBJS))

fclean:			clean
				$(call removing,$(NAME))
				$(call removing,$(NAME_BONUS))

re:				fclean all
