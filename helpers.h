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

    //Esto es para minimizar tiempos de espera y maximizar cantidad de sesiones
    paciente* listaU;
    paciente* listaP;
    paciente* listaR;

    void pasarDia(int pacientesU, paciente* listaUrgente, int pacientesP, paciente* listaPaliativa, int pacientesR,
                     paciente* listaRadical, int bloqueActual);
    int buscarDoc(int bloque, int totalDoctores, doc* listaDoctores, 
                        int pacientesU, paciente* listaUrgente,
                        int pacientesP, paciente* listaPaliativa,
                        int pacientesR, paciente* listaRadical);
    void escribir(int pacientesU, paciente* listaUrgente, int pacientesP, paciente* listaPaliativa,
                  int pacientesR, paciente* listaRadical);

    bool minTiempoEspera();

    public:

        void initListaPacientes(paciente* lista, int largo);
        void initListasInternas(int pacientesU, int pacientesP, int pacientesR);
        void limpiar(doc* listaDoctores, paciente* listaRadical, paciente* listaPaliativa, paciente* listaUrgente);

        void BT(doc* listaDoctores, paciente* listaRadical, paciente* listaPaliativa, paciente* listaUrgente
            ,int totalDoctores, int pacientesR, int pacientesP, int pacientesU, int totalMaquinas
            ,int bloqueActual, int doctoresUsados, int maquinasUsadas);

};

