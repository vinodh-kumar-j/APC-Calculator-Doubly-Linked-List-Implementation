a.out: main.c operation.c dll_utils.c
	gcc -o a.out main.c operation.c dll_utils.c

clean:
	rm -f a.out
