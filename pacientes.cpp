#include "pacientes.h"

void paciente::initPaciente (){
    tiempoEspera = 0;
    cantidadSesionesActuales = 0;
    tiempoEsperaPrimera = -1;
    for (int i = 0; i < 320; i++){
        horarioDoc[i] = 0;
        horarioMaq[i] = 0;
    }
}