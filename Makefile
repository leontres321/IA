CC =g++
FLAGS =-Wall

FILES =main.o
BINARY =out

all: $(BINARY)

out: $(FILES)
	$(CC) $(FLAGS) -o $(BINARY) $(FILES)

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

clean:
	rm $(BINARY) *.o

run:
	@./out
