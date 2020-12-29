#include <iostream>
#include <fstream>

#include "doctores.h"

using namespace std;

int main(int argc, char *argv[]) {
    int totalMaquinas, totalDoctores, totalPacientes;
    int pacientesR, pacientesP, pacientesU;

    int idDoctores = 0;

    doc* listaDoctores;

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
    }
    else{
        input.close();
        exit(1);
    }


    //Limpieza
    input.close();
    delete listaDoctores;
    return 0;
}
