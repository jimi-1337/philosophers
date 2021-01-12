# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/12 15:17:15 by amoujane          #+#    #+#              #
#    Updated: 2021/01/12 15:22:18 by amoujane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =		main.c \
			init.c \
			sleep.c \
			time.c \
			util.c \
			util2.c

HEADER =	./philo_one.h

FLAGS = -Wall -Wextra -Werror

NAME = philo_one

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@echo "\n"
	@echo "\033[0;32mCompiling philo_one..."
	@gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIBS)
	@echo "\n\033[0mDone !"

%.o: %.c
	@printf "\033[0;33mGenerating philo_one objects... %-33.33s\r" $@
	@gcc ${FLAGS} -c $< -o $@

norm :
	@norminette $(SRC) $(HEADER)

clean:
	@echo "\nRemoving binaries..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@echo "\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all