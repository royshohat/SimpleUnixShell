sh: shell.c
	gcc -I -Wall shell.c util.c -o shell
clean:
	rm shell
