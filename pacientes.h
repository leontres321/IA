#pragma once

class paciente{
    public:
        int inicioSesiones; //Para restriccion de viernes a pacientes radicales.
        int cantidadSesionesActuales; 
        int tiempoEspera;
        int tiempoEsperaMAX;


        //Esto podría ser disminuido a un total de 60 ints pero y a mi que? (5.1kb por paciente)
        int horarioDoc[320];
        int horarioMaq[320];

        void initPaciente ();
};
