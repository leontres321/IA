#include "pacientes.h"

void paciente::initPaciente (){
    inicioSesiones = -1;
    for (int i = 0; i < 320; i++){
        horarioDoc[i] = 0;
        horarioMaq[i] = 0;
    }
}