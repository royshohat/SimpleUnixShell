sh: shell.c
	gcc -I -Wall shell.c -o shell
	./shell
clean:
	rm shell
