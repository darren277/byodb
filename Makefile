main: main.c
	gcc main.c -o main

run: main
	./main mydb.db

clean:
	rm -f main *.db

format: *.c
	clang-format -style=Google -i *.c


test:
	python tests/main.py
