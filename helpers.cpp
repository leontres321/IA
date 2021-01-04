#include <algorithm>
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

void helper::BT(doc* listaDoctores, 
    paciente* listaRadical, 
    paciente* listaPaliativa, 
    paciente* listaUrgente,
    int totalDoctores, int pacientesR, int pacientesP, int pacientesU, int totalMaquinas,
    int bloqueActual, int doctoresUsados, int maquinasUsadas){

    //Variables auxiliares
    bool yaAgendo = false;
    bool esViernes = false;

    //Variables para desagendar la hora
    int typoPaciente = 0; //1: U, 2: P, 3:R
    int iterador = 0; //Para saber que cliente es el que se le hizo el cambio

    if (bloqueActual == 320){
        //TODO: revisar, quizas aca solo sea revizar lo de min y max, ademas hay que guardar el resultado
        escribir(pacientesU, listaUrgente, pacientesP, listaPaliativa, pacientesR, listaRadical);
        return;
    }

    //Si no existen más doctores o maquinas entonces no se puede atender nadie más en ese bloque
    //deberia pasarse al siguiente bloque y resetear los doctores usados y maquinas usadas
    if (doctoresUsados == totalDoctores || maquinasUsadas == totalMaquinas){
        //pasarDia(pacientesU, listaUrgente, pacientesP, listaPaliativa, pacientesR, listaRadical,bloqueActual);
        //TODO: Solo pasar el dia cuando sea ciertos bloques... no?
        BT(listaDoctores, listaRadical, listaPaliativa, listaUrgente, totalDoctores, pacientesP, pacientesR,
        pacientesU, totalMaquinas, bloqueActual+1, 0, 0);
        return;
    }

    //Buscar un doc libre en este horario
    //RESTRICCION: doctores solo atienden en sus horarios
    int iddoc = buscarDoc(bloqueActual, totalDoctores, listaDoctores, pacientesU,
                        listaUrgente, pacientesP, listaPaliativa, pacientesR, listaRadical); 
    
    if (iddoc == 0){
        BT(listaDoctores, listaRadical, listaPaliativa, listaUrgente, totalDoctores, pacientesP, pacientesR,
        pacientesU, totalMaquinas, bloqueActual+1, 0, 0);
        return; //?????
    }
    //Se busca la maquina?
    //No es necesario porque no se busca el id de la maquina, solo la cantidad
    //y como se reviso que maquinasUsadas < totalMaquinas entonces todo gud
    //y con todo gud me refiero a que debo tener un id para el segundo archivo asi que 
    //deberia tener un ++ en la llamada de BT
    //y con todo gud me refiero a que debo tener un id para el segundo archivo asi que 
    //deberia tener un ++ en la llamada de BT

    //Primero se revisan los urgentes ya que tienen menos tiempo de espera
    for (int i = 0; i < pacientesU; i++){
        //RESTRICCION: los pacientes no pueden agendar más sesiones de las que requieren
        //RESTRICCION: los pacientes tienen un tiempo min y max para los tiempos de espera
        if (listaUrgente[i].cantidadSesionesActuales < sesionesU && listaUrgente[i].tiempoEspera >= minU &&
        listaUrgente[i].tiempoEspera <= maxU){

            //Se hace la sesion
            listaUrgente[i].tiempoEspera = 0;
            listaUrgente[i].horarioDoc[bloqueActual] = listaDoctores[iddoc].id;
            listaUrgente[i].horarioMaq[bloqueActual] = maquinasUsadas;
            
            yaAgendo = true;

            //Para retorno
            typoPaciente = 1;
            iterador = i;

            break;
        }
    }
    
    //Luego los paliativos
    if (!yaAgendo){
        for (int i = 0; i < pacientesP; i++){
            if (listaPaliativa[i].cantidadSesionesActuales < sesionesP && listaPaliativa[i].tiempoEspera >= minP &&
                listaPaliativa[i].tiempoEspera <= maxP){

                //Se hace la sesion
                listaPaliativa[i].tiempoEspera = 0;
                listaPaliativa[i].horarioDoc[bloqueActual] = listaDoctores[iddoc].id;
                listaPaliativa[i].horarioMaq[bloqueActual] = maquinasUsadas;

                yaAgendo = true;

                //Para retorno
                typoPaciente = 2;
                iterador = i;

                break;
            }
        }
    }

    //Por ultimo los radicales
    if (!yaAgendo){
        //Revisamos si es viernes
        for (int i = 0; i < 4; i++){
            if (bloqueActual >= 64 + i * 80 && bloqueActual <= 79 + i * 80){
                esViernes = true;
            }
        }
    
        for (int i = 0; i < pacientesR; i++){
            if (listaRadical[i].cantidadSesionesActuales < sesionesR && listaRadical[i].tiempoEspera >= minR && 
                listaRadical[i].tiempoEspera <= maxR){

                //RESTRICCION: pacientes radicales no inician tratamiento los viernes
                if (listaRadical[i].cantidadSesionesActuales == 0 && esViernes){
                    break;
                }

                //Se hace la sesion
                listaRadical[i].tiempoEspera = 0;
                listaRadical[i].horarioDoc[bloqueActual] = listaDoctores[iddoc].id;
                listaRadical[i].horarioMaq[bloqueActual] = maquinasUsadas;
                
                yaAgendo = true;

                //Para retorno
                typoPaciente = 3;
                iterador = i;

                break;
            }
        }
    }

    if (yaAgendo){
        BT(listaDoctores, listaRadical, listaPaliativa, listaUrgente, totalDoctores, pacientesR,
            pacientesP, pacientesU, totalMaquinas, bloqueActual, doctoresUsados+1, maquinasUsadas+1);
        //Agendamos a alguien en este bloque pero queda mas gente, por lo tanto es necesario
        //hace BT en el mismo bloque pero cambiando parametros, ahora cuando falle es necesario
        //que exista una manera de devolver los pasos, guardar algunos int o algo asi para poder devolver
        //ya que uso punteros asi que siempre son los mismos objetos 

        //Quitar la sesion
        switch (typoPaciente){
            case 1:
                listaUrgente[iterador].horarioDoc[bloqueActual] = 0;
                listaUrgente[iterador].horarioMaq[bloqueActual] = 0;
                break;
            case 2:
                listaPaliativa[iterador].horarioDoc[bloqueActual] = 0;
                listaPaliativa[iterador].horarioMaq[bloqueActual] = 0;
                break;
            case 3:
                listaRadical[iterador].horarioDoc[bloqueActual] = 0;
                listaRadical[iterador].horarioMaq[bloqueActual] = 0;
                break;
        }

        //TODO: Y luego que onda?, como pruebo a otro paciente?
        //yo guardo el iter y tipo, quizas podria hacer un while y revisar todos sino su return loco
    }
    else{
        //No se puede agendar por diferentes razones, por lo tanto queda solo pasar al siguiente bloque
        BT(listaDoctores, listaRadical, listaPaliativa, listaUrgente, totalDoctores, pacientesP, pacientesR,
        pacientesU, totalMaquinas, bloqueActual+1, 0, 0);
        //Al retornar quiere decir que: fallo algo o se completo todo, por lo tanto otro return no se ve mal
        //como no agende nada entonces no debo hacer el movimiento al revez... cierto?
        return;
    }
    //TODO: revisar si no rompe algo, de ser así return sino arreglar tiempos de espera y llamar a BT again
    //Lo unico que deberia poder romperse es que los pacientes esperen mas del tiempo maximo
    //si retorno entonces deberia bajar los tiempos de espera... eso suena a que necesito mas variables
}


///Busca id doctor, retorna el primer id que encuentre
int helper::buscarDoc(int bloque, int totalDoctores, doc* listaDoctores,
                    int pacientesU, paciente* listaUrgente,
                    int pacientesP, paciente* listaPaliativa,
                    int pacientesR, paciente* listaRadical){

    bool usado;
    bool posibleCandidato;
    for (int i = 0; i < totalDoctores; i++){
        
        int horario = listaDoctores[i].horario[bloque/16];
        usado = false;
        posibleCandidato = false;

        switch (horario){
            case 0:
                //No se encuentra trabajando
                continue;
            case 1:
                for (int i = 0; i < 20; i++){
                    if (bloque >= 16 * i && bloque <= 16 * i + 7){
                        posibleCandidato = true;
                        break;
                    }
                }
                if (!posibleCandidato) continue;
            case 2:
                for (int i = 0; i < 20; i++){
                    if (bloque >= 16 * i + 8 && bloque <= 16 * (i + 1) - 1){
                        posibleCandidato = true;
                        break;
                    }
                }
                if (!posibleCandidato) continue;
            case 3:
                //Sí está trabajando por lo tanto no hay que revisar si tiene le horario
                break;
        }

        //Revisar si algun paciente tiene registrado este doctor, si está registrado pasar al siguiente doc
        //sino esta registrado devolver su id
        for (int j = 0; j < pacientesU; j ++){
            if (listaUrgente[j].horarioDoc[bloque] == listaDoctores[i].id){
                usado = true;
                break;
            }
        }
        if (usado) continue;

        for (int j = 0; j < pacientesP; j++){
            if (listaPaliativa[j].horarioDoc[bloque] == listaDoctores[i].id){
                usado = true;
                break;
            }
        }
        if (usado) continue;

        for (int j = 0; j < pacientesR; j++){
            if (listaRadical[j].horarioDoc[bloque] == listaDoctores[i].id){
                usado = true;
                break;
            }
        }
        return listaDoctores[i].id;       
    }

    //Se reviso todos los doctores y ya estan ocupados (los id parten de 1)
    return 0;
}

///Agrega tiempo de espera a todos los que no fueron atendidos en el bloque actual
void helper::pasarDia(int pacientesU, paciente* listaUrgente, int pacientesP, paciente* listaPaliativa, int pacientesR,
                     paciente* listaRadical, int bloqueActual){
        for (int i = 0; i < pacientesU; i++){
            if (listaUrgente[i].horarioDoc[bloqueActual] == 0){
                listaUrgente[i].tiempoEspera++;
                listaUrgente[i].tiempoEsperaMAX = std::max(listaUrgente[i].tiempoEsperaMAX, listaUrgente[i].tiempoEspera);
            }
        }

        for (int i = 0; i < pacientesP; i++){
            if (listaPaliativa[i].horarioDoc[bloqueActual] == 0){
                listaPaliativa[i].tiempoEspera++;
                listaPaliativa[i].tiempoEsperaMAX = std::max(listaPaliativa[i].tiempoEsperaMAX, listaPaliativa[i].tiempoEspera);
            }
        }

        for (int i = 0; i < pacientesU; i++){
            if (listaRadical[i].horarioDoc[bloqueActual] == 0){
                listaRadical[i].tiempoEspera++;
                listaRadical[i].tiempoEsperaMAX = std::max(listaRadical[i].tiempoEsperaMAX, listaRadical[i].tiempoEspera);
            }
        }
}


//Inicializa las listas internas... tantos for
void helper::initListasInternas(int pacientesU, int pacientesP, int pacientesR){
    listaU = new paciente[pacientesU];
    listaP = new paciente[pacientesP];
    listaR = new paciente[pacientesR];
    for (int i = 0; i < pacientesU; i++){
        listaU[i].initPaciente();
    }
    for (int i = 0; i < pacientesP; i++){
        listaP[i].initPaciente();
    }
    for (int i = 0; i < pacientesR; i++){
        listaR[i].initPaciente();
    }
}