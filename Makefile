SRCS = server.c client.c server_bonus.c client_bonus.c
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: server client

server: server.o libft
	$(CC) -o $@ $< -Llibft -lft

client: client.o libft
	$(CC) -o $@ $< -Llibft -lft

%.o: %.c
	$(CC) -c $(CFLAGS) $?

libft:
	make -C libft

bonus_client: client_bonus.o libft
	$(CC) -o $@ $< -Llibft -lft

bonus_server: server_bonus.o libft
	$(CC) -o $@ $< -Llibft -lft

clean:
	rm -f $(OBJS)
	make -C libft clean
	
fclean: clean
	rm -f server client server_bonus client_bonus libft/libft.a

re: fclean all

.PHONY: all bonus_server bonus_client libft clean fclean re