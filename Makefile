# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rogerio <rogerio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/17 13:23:38 by rogerio           #+#    #+#              #
#    Updated: 2021/08/22 15:51:17 by rogerio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= HelloApi
CC		= gcc
CFLAGS	= -c -Wall -Wextra -Werror
MFLAGS	= -DMG_ENABLE_MBEDTLS=1 -I/usr/lib/x86_64-linux-gnu/include -I/usr/include
DBFLAGS = -I/usr/local/include/libbson-1.0 -I/usr/local/include/libmongoc-1.0 -lmongoc-1.0 -lbson-1.0
MFLAGSO	= -L/usr/lib/x86_64-linux-gnu/lib -lmbedtls -lmbedcrypto -lmbedx509
RM		= rm -rf

SRCS =	mjson/mjson.c			\
		mongoose/mongoose.c		\
		src/callbacks.c			\
		src/mongo_handler.c		\
		src/info_request.c		\
		src/routes.c			\
		src/utils.c				\
		src/utils_get.c			\
		src/main.c

OBJS = ${SRCS:%.c=%.o}

all:	${NAME}

${NAME}:	${OBJS}
	${CC} ${OBJS} ${MFLAGSO} ${DBFLAGS} -o ${NAME}

%.o:	%.c
	${CC} ${CFLAGS} ${MFLAGS} $< -o $@

mongo:
	${CC} mmongo.c ${DBFLAGS} 

clean:
	${RM}	mjson/*.o	mongoose/*.o	src/*.o		*.o 

fclean:	clean
	${RM} ${NAME}

run:	all
	./${NAME}

docker: fclean
	docker build -t rogeriorslf/infoapi . 
	docker rm -f rogeriorslf/infoapi
	docker run -it -p 4242:4242 --name rogeriorslf/infoapi \
		rogeriorslf/infoapi:latest

re: fclean all
