# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 12:50:38 by rmakinen          #+#    #+#              #
#    Updated: 2023/06/07 11:13:40 by rmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
HEADER = -I philo.h
SRC_DIR = ./
FILES = philo philo_utils init_args init error routine monitoring
SRC = $(addprefix $(SRC_DIR),$(addsuffix .c, $(FILES)))
OBJ = $(addprefix $(SRC_DIR),$(addsuffix .o, $(FILES)))
FLAGS = -Wall -Wextra -Werror -pthread -o2

all: $(NAME)

$(NAME): $(SRC)
	@cc $(FLAGS) $(SRC) -o $(NAME)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
