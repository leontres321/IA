CC =g++
FLAGS =-Wall

FILES =main.o doctores.o
BINARY =out

all: $(BINARY)

out: $(FILES)
	$(CC) $(FLAGS) -o $(BINARY) $(FILES)

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

doctores.o: doctores.cpp
	$(CC) $(FLAGS) -c doctores.cpp



clean:
	rm $(BINARY) $(FILES)

run:
	@./out $(CASE)
