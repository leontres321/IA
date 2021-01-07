#include <iostream>
#include <fstream>
#include <signal.h>

#include "doctores.h"
#include "pacientes.h"
#include "helpers.h"

using namespace std;

helper help = helper();
int pacientesR, pacientesP, pacientesU;

void terminar(int s){
    fstream salida1, salida2;
    salida1.open("doctores.txt", ios::out);
    salida2.open("maquinas.txt", ios::out);

    for (int i = 0; i < pacientesU; i++){
        for (int j = 0; j < 320; j++){
            salida1 << help.listaU[i].horarioDoc[j] << " ";
            salida2 << help.listaU[i].horarioMaq[j] << " ";
        }
        salida1 << endl;
        salida2 << endl;
    }    

    for (int i = 0; i < pacientesP; i++){
        for (int j = 0; j < 320; j++){
            salida1 << help.listaP[i].horarioDoc[j] << " ";
            salida2 << help.listaP[i].horarioMaq[j] << " ";
        }
        salida1 << endl;
        salida2 << endl;
    }    

    for (int i = 0; i < pacientesR; i++){
        for (int j = 0; j < 320; j++){
            salida1 << help.listaR[i].horarioDoc[j] << " ";
            salida2 << help.listaR[i].horarioMaq[j] << " ";
        }
        salida1 << endl;
        salida2 << endl;
    }    

    salida1.close();
    salida2.close();

    cout << "Se genero los archivos requeridos" << endl;
    exit(0);
}

int main(int argc, char *argv[]) {
    int totalMaquinas, totalDoctores, totalPacientes;
    int idDoctores = 1;

    signal (SIGINT,terminar);

    doc* listaDoctores;
    paciente* listaRadical;
    paciente* listaPaliativa;
    paciente* listaUrgente;

    if (argc < 2){
        cout << "**********" << endl;
        cout << "Para poder utilizar correctamente este ejecutable es necesario entregar un valor a CASE" << endl;
        cout << "ejemplo: make run CASE=./Instances/Caso1" << endl;
        cout << "**********" << endl;
        exit(0);
    }
    
    fstream input;
    input.open(argv[1], ios::in);
    
    if (input.is_open()){
        input >> totalMaquinas >> totalDoctores >> totalPacientes;

        listaDoctores = new doc[totalDoctores];
        //parche
        totalMaquinas++;

        for (int i = 0; i < totalDoctores; i++){
            int l[5];
            input >> l[0] >> l[1] >> l[2] >> l[3] >> l[4];
            listaDoctores[i].initDoc(l, idDoctores++);
        }
        
        input >> pacientesR >> pacientesP >> pacientesU;

        listaRadical = new paciente[pacientesR];
        listaUrgente = new paciente[pacientesU];
        listaPaliativa = new paciente[pacientesP];

        help.initListaPacientes(listaRadical, pacientesR);
        help.initListaPacientes(listaPaliativa, pacientesP);
        help.initListaPacientes(listaUrgente, pacientesU);
    }
    else{
        input.close();
        exit(1);
    }

    help.initListasInternas(pacientesU, pacientesP, pacientesR);
    //Comenzar algoritmo
    help.BT(listaDoctores, listaRadical, listaPaliativa, listaUrgente,
            totalDoctores, pacientesR, pacientesP, pacientesU, totalMaquinas,
            0, 0, 1);
    
    //Limpieza
    input.close();
    
    terminar(0);

    help.limpiar (listaDoctores, listaRadical, listaPaliativa, listaUrgente);
    return 0;
}

