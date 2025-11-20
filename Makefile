comp: shell.c
	gcc shell.c -o shell.exe

run: shell.exe
	./shell.exe

clean:
	rm shell.exe