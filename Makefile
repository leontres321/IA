CC =g++
FLAGS =-Wall

FILES =main.o doctores.o pacientes.o
BINARY =out

all: $(BINARY)

out: $(FILES)
	$(CC) $(FLAGS) -o $(BINARY) $(FILES)

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

doctores.o: doctores.cpp
	$(CC) $(FLAGS) -c doctores.cpp

pacientes.o: pacientes.cpp
	$(CC) $(FLAGS) -c pacientes.cpp

clean:
	rm $(BINARY) $(FILES)

run:
	@./out $(CASE)
