#include "doctores.h"

void doc::initDoc(int listaHorario[5], int idNuevo){
    for (int i = 0; i < 5; i++){
        horario[i] = listaHorario[i];
    }
    id = idNuevo;
}