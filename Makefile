main:
	python utils.py combine
	gcc -o main combined_main.c

main-dont-use-yet: main.c
	gcc main.c -o main.o -c
	gcc src/pager.c -o pager.o -c
	gcc -o main main.o pager.o

run: main
	./main mydb

clean:
	rm -f main combined_main.c *.o *.db

format: *.c
	clang-format -style=Google -i *.c

debug: clean
	python utils.py combine
	gcc -o main combined_main.c -g
	gdb --args ./main mydb

valgrind:
	valgrind --leak-check=full ./main mydb

test:
	python tests/main.py
