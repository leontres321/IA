#pragma once

#include "pacientes.h"
#include "doctores.h"
#include <vector>

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

    int esperaAntigua = INT32_MAX;
    int sesionesAntigua = 0;

    void pasarDia(int pacientesU, paciente* listaUrgente, int pacientesP, paciente* listaPaliativa, int pacientesR,
                     paciente* listaRadical, int bloqueActual);

    void regresarDia(int pacientesU, paciente* listaUrgente, int pacientesP, paciente* listaPaliativa, int pacientesR,
                     paciente* listaRadical, int bloqueActual);
            
    int buscarDoc(int bloque, int totalDoctores, doc* listaDoctores, 
                        int pacientesU, paciente* listaUrgente,
                        int pacientesP, paciente* listaPaliativa,
                        int pacientesR, paciente* listaRadical);

    void escribir(int pacientesU, paciente* listaUrgente, int pacientesP, paciente* listaPaliativa,
                  int pacientesR, paciente* listaRadical);

    int encontrarOtroPaciente(int cantidadPacientes, paciente* listaPaciente, std::vector<int> &excluidos, int typo, int bloqueActual);
    void devolverHora(paciente* listaPacientes, int iterador, int bloqueActual, std::vector<int> &exclusiones);
    bool revisarDiasMaximos(int pacientesU, paciente* listaUrgente, int pacientesP, paciente* listaPaliativa, int pacientesR,
                     paciente* listaRadical);

    void pasarBloque(int pacienteU, paciente* listaUrgente, int pacienteP, paciente* listaPaliativa, int pacienteR, paciente* listaRadical);
    void devolverBloque(int pacienteU, paciente* listaUrgente, int pacienteP, paciente* listaPaliativa, int pacienteR, paciente* listaRadical);

    void copiarLista(int cantidad, paciente* listaOriginal, paciente* listaCopiada);

    public:
        //Esto es para minimizar tiempos de espera y maximizar cantidad de sesiones
        paciente* listaU;
        paciente* listaP;
        paciente* listaR;
        void initListaPacientes(paciente* lista, int largo);
        void initListasInternas(int pacientesU, int pacientesP, int pacientesR);
        void limpiar(doc* listaDoctores, paciente* listaRadical, paciente* listaPaliativa, paciente* listaUrgente);

        void BT(doc* listaDoctores, paciente* listaRadical, paciente* listaPaliativa, paciente* listaUrgente
            ,int totalDoctores, int pacientesR, int pacientesP, int pacientesU, int totalMaquinas
            ,int bloqueActual, int doctoresUsados, int maquinasUsadas);

};

