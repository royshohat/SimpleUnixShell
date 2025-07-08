sh: shell.c
	gcc -I -Wall shell.c util.c -o shell
	./shell
clean:
	rm shell
