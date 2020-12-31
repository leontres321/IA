#pragma once

#include "pacientes.h"
#include "doctores.h"

class helper{
    //Podria ser lista pero queria ponerlo más obvio, podria haber hecho un enum tambien
    int minR = 14;
    int maxR = 28;
    int minP = 2;
    int maxP = 14;
    int minU = 1;
    int maxU = 2;

    int sesionesR = 30;
    int sesionesP = 4;
    int sesionesU = 2;

    public:

        void initListaPacientes(paciente* lista, int largo);
        void limpiar(doc* listaDoctores, paciente* listaRadical, paciente* listaPaliativa, paciente* listaUrgente);
        void BT(doc* listaDoctores, paciente* listaRadical, paciente* listaPaliativa, paciente* listaUrgente);
        void escribir();

};

