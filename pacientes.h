#pragma once
#include <vector>

class paciente{
    public:
        int cantidadSesionesActuales; 
        int tiempoEspera;
        int tiempoEsperaPrimera;

        std::vector<int> pilaEsperas;

        //Esto podría ser disminuido a un total de 60 ints pero y a mi que? (5.1kb por paciente)
        int horarioDoc[320];
        int horarioMaq[320];

        void initPaciente ();
};
