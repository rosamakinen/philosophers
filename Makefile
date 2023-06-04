# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 12:50:38 by rmakinen          #+#    #+#              #
#    Updated: 2023/06/03 15:05:23 by rmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
HEADER = -I philo.h
SRC_DIR = ./
FILES = philo philo_utils init_args init error routine monitoring
SRC = $(addprefix $(SRC_DIR),$(addsuffix .c, $(FILES)))
OBJ = $(addprefix $(SRC_DIR),$(addsuffix .o, $(FILES)))
FLAGS = -Wall -Wextra -Werror -g -pthread #-fsanitize=thread

all: $(NAME)

$(NAME): $(SRC)
	@cc -o $(NAME) $(FLAGS) $(SRC)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
