# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/12 15:17:15 by amoujane          #+#    #+#              #
#    Updated: 2021/01/12 18:55:13 by amoujane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =		main.c \
			init.c \
			sleep.c \
			time.c \
			util.c \
			util2.c

HEADER =	./philo_three.h

FLAGS = 

NAME = philo_three

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@echo "\n"
	@echo "\033[0;32mCompiling philo_three..."
	@gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIBS)
	@echo "\n\033[0mDone !"

%.o: %.c
	@printf "\033[0;33mGenerating philo_three objects... %-33.33s\r" $@
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