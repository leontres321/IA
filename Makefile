CC =g++
FLAGS =-Wall

FILES =main.o doctores.o pacientes.o helpers.o
OUTPUTS = doctores.txt maquinas.txt
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

helpers.o: helpers.cpp
	$(CC) $(FLAGS) -c helpers.cpp

clean:
	rm $(BINARY) $(FILES) $(OUTPUTS)

run:
	@./out $(CASE)
