#include <iostream>
#include <fstream>

#include "doctores.h"
#include "pacientes.h"
#include "helpers.h"

using namespace std;

int main(int argc, char *argv[]) {

    helper help = helper();

    int totalMaquinas, totalDoctores, totalPacientes;
    int pacientesR, pacientesP, pacientesU;

    int idDoctores = 1;

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

        for (int i = 0; i < totalDoctores; i++){
            int l[5];
            input >> l[0] >> l[1] >> l[2] >> l[3] >> l[4];
            listaDoctores[i].initDoc(l, idDoctores++);
        }
        
        input >> pacientesR >> pacientesP >> pacientesU;

        listaRadical = new paciente[pacientesR];
        listaPaliativa = new paciente[pacientesP];
        listaUrgente = new paciente[pacientesU];

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
            0, 0, 0);

    //Limpieza
    input.close();
    help.limpiar (listaDoctores, listaRadical, listaPaliativa, listaUrgente);
    return 0;
}
