CC =g++
FLAGS =-Wall

FILES =main.o doctores.o pacientes.o GBJ.o
OUTPUTS =OUT
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

GBJ.o: GBJ.cpp
	$(CC) $(FLAGS) -c GBJ.cpp

clean:
	rm $(BINARY) $(FILES)

delete:
	rm -rf $(OUTPUTS)

run:
	@./$(BINARY) $(CASE)
