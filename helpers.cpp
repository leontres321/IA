#include "helpers.h"

void limpiar (doc* listaDoctores, paciente* listaRadical, paciente* listaPaliativa, paciente* listaUrgente){
    delete listaDoctores;
    delete listaRadical;
    delete listaPaliativa;
    delete listaUrgente;
}

void initListaPacientes(paciente* lista, int largo){
    for (int i = 0; i < largo; i++){
        lista[i].initPaciente();
    }
}
