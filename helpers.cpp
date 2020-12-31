#include "helpers.h"

void helper::limpiar (doc* listaDoctores, paciente* listaRadical, paciente* listaPaliativa, paciente* listaUrgente){
    delete listaDoctores;
    delete listaRadical;
    delete listaPaliativa;
    delete listaUrgente;
}

void helper::initListaPacientes(paciente* lista, int largo){
    for (int i = 0; i < largo; i++){
        lista[i].initPaciente();
    }
}

void helper::BT(doc* listaDoctores, paciente* listaRadical, paciente* listaPaliativa, paciente* listaUrgente){

}
