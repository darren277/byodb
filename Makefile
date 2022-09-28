main: main.c
	gcc main.c -o main

run: main
	./main mydb.db

clean:
	rm -f main *.db

test: main
	bundle exec rspec

format: *.c
	clang-format -style=Google -i *.c
