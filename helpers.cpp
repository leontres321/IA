#include <iostream>
#include <fstream>
#include <vector>
#include "helpers.h"

using namespace std;

///Borrar punteros de pacientes y doctores
void helper::limpiar (doc* listaDoctores, paciente* listaRadical, paciente* listaPaliativa, paciente* listaUrgente){
    delete[] listaDoctores;
    delete[] listaRadical;
    delete[] listaPaliativa;
    delete[] listaUrgente;

    delete[] listaU;
    delete[] listaR;
    delete[] listaP;
}

///Llamar initPaciente por cada persona en la lista
void helper::initListaPacientes(paciente* lista, int largo){
    for (int i = 0; i < largo; i++){
        lista[i].initPaciente();
    }
}

///Busca id doctor, retorna el primer id que encuentre
int helper::buscarDoc(int bloque, int totalDoctores, doc* listaDoctores,
                    int pacientesU, paciente* listaUrgente,
                    int pacientesP, paciente* listaPaliativa,
                    int pacientesR, paciente* listaRadical){

    bool usado;
    bool posibleCandidato;

    //Tomo un doc
    for (int i = 0; i < totalDoctores; i++){

        int horario = listaDoctores[i].horario[(bloque/16)%5];
        usado = false;
        posibleCandidato = false;

        switch (horario){
            case 0:
                //No se encuentra trabajando
                break;
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
        if (!usado){
            return listaDoctores[i].id;       
        }
    }

    //Se reviso todos los doctores y ya estan ocupados (los id parten de 1)
    return 0;
}

///Agrega tiempo de espera a todos los que no fueron atendidos en el bloque actual
void helper::pasarDia(int pacientesU, paciente* listaUrgente, int pacientesP, paciente* listaPaliativa, int pacientesR,
                     paciente* listaRadical, int bloqueActual){
    //Primer loop revisa las personas, segundo loop revisa las sesiones del dia
    bool noAgendado;
    for (int i = 0; i < pacientesU; i++){
        noAgendado = true;
        for (int j = 0; j < 16; j++){
            if (listaUrgente[i].horarioDoc[bloqueActual-j] != 0 ){
                noAgendado = false;
                break;
            }            
        }
        if (noAgendado && listaUrgente[i].cantidadSesionesActuales < sesionesU){
            listaUrgente[i].tiempoEspera++;
            if (listaUrgente[i].cantidadSesionesActuales == 0){
                listaUrgente[i].tiempoEsperaPrimera++;
            }
        }
    }

    for (int i = 0; i < pacientesP; i++){
        noAgendado = true;
        for (int j = 0; j < 16; j++){
            if (listaPaliativa[i].horarioDoc[bloqueActual-j] != 0){
                noAgendado = false;
                break;
            }
        }
        if (noAgendado && listaPaliativa[i].cantidadSesionesActuales < sesionesP){
            listaPaliativa[i].tiempoEspera++;
            if (listaPaliativa[i].cantidadSesionesActuales == 0){
                listaPaliativa[i].tiempoEsperaPrimera++;
            }
        }
    }

    for (int i = 0; i < pacientesR; i++){
        noAgendado = true;
        for (int j = 0; j < 16; j++){
            if (listaRadical[i].horarioDoc[bloqueActual-j] != 0){
                noAgendado = false;
                break;
            }
        }
        if (noAgendado && listaRadical[i].cantidadSesionesActuales < sesionesR){
            listaRadical[i].tiempoEspera++;
            if (listaRadical[i].cantidadSesionesActuales == 0){
                listaRadical[i].tiempoEsperaPrimera++;
            }
        }
    }
}

///Regresa los tiempos de espera que existian
void helper::regresarDia(int pacientesU, paciente* listaUrgente, int pacientesP, paciente* listaPaliativa, int pacientesR,
                     paciente* listaRadical, int bloqueActual){
    bool noAgendado;
    for (int i = 0; i < pacientesU; i++){
        noAgendado = true;
        for (int j = 0; j < 16; j++){
            if (listaUrgente[i].horarioDoc[bloqueActual-j] != 0){
                noAgendado = false;
                break;
            }
        }
        if (noAgendado && listaUrgente[i].cantidadSesionesActuales < sesionesU){
            listaUrgente[i].tiempoEspera--;
            if (listaUrgente[i].cantidadSesionesActuales == 0){
                listaUrgente[i].tiempoEsperaPrimera--;
            }
        }
    }

    for (int i = 0; i < pacientesP; i++){
        noAgendado = true;
        for (int j = 0; j < 16; j++){
            if (listaPaliativa[i].horarioDoc[bloqueActual-j] != 0){
                noAgendado = false;
                break;
            }
        }
        if (noAgendado && listaPaliativa[i].cantidadSesionesActuales < sesionesP){
            listaPaliativa[i].tiempoEspera--;
            if (listaPaliativa[i].cantidadSesionesActuales == 0){
                listaPaliativa[i].tiempoEsperaPrimera--;
            }
        }
    }

    for (int i = 0; i < pacientesR; i++){
        noAgendado = true;
        for (int j = 0; j < 16; j++){
            if (listaRadical[i].horarioDoc[bloqueActual-j] != 0){
                noAgendado = false;
                break;
            }
        }
        if (noAgendado && listaRadical[i].cantidadSesionesActuales < sesionesR){
            listaRadical[i].tiempoEspera--;
            if (listaRadical[i].cantidadSesionesActuales == 0){
                listaRadical[i].tiempoEsperaPrimera--;
            }
        }
    }
}

///Inicializa las listas internas... tantos for
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

int helper::encontrarOtroPaciente(int cantidadPacientes, paciente* listaPaciente, vector<int> &excluidos, int typo, int bloqueActual){
    bool esViernes = false;
    int min, max, sesiones;
    
    switch (typo)
    {
    case 1:
        min = minU;
        max = maxU;
        sesiones = sesionesU;
        break;
    case 2:
        min = minP;
        max = maxP;
        sesiones = sesionesP;
        break;
    case 3:
        min = minR;
        max = maxR;
        sesiones = sesionesR;
        for (int i = 0; i < 4; i++){
            if (bloqueActual >= 64 + i * 80 && bloqueActual <= 79 + i * 80){
                esViernes = true;
            }
        }
        break;
    }

    for (int i = 0; i < cantidadPacientes; i++){
        bool excluido = false;
        
        //RESTRICCION: los pacientes no pueden agendar más sesiones de las que requieren
        //RESTRICCION: los pacientes tienen un tiempo min y max para los tiempos de espera
        if (listaPaciente[i].cantidadSesionesActuales < sesiones && listaPaciente[i].tiempoEspera >= min && 
            listaPaciente[i].tiempoEspera <= max){ //es necesario lo de max?
            
            //RESTRICCION: pacientes radicales no inician tratamiento los viernes
            if (typo == 3 && listaPaciente[i].cantidadSesionesActuales == 0 && esViernes){
                continue;
            }

            //Revisar lista de restricciones
            if (excluidos.size() > 0){
                for (int j = 0; j < int(excluidos.size()); j++){
                    if (excluidos[i] == i){
                        excluido = true;
                        break;
                    }
                }
            }
            if (excluido){
                continue;
            }
            //No esta en la lista restricciones o esta no existe, se entrega el iterador para el paciente
            return i;
        }
    }
    //No se encontró un paciente que pudiese ser entregado, asi que -1
    //lista vacia o todos son radicales, es viernes y no han iniciado sus sesiones
    return -1;
}

void helper::devolverHora(paciente* listaPacientes, int iterador, int bloqueActual, vector<int> &exclusiones){
    //Quitar la sesion
    listaPacientes[iterador].horarioDoc[bloqueActual] = 0;
    listaPacientes[iterador].horarioMaq[bloqueActual] = 0;
    listaPacientes[iterador].tiempoEspera = listaPacientes[iterador].pilaEsperas.back();
    listaPacientes[iterador].pilaEsperas.pop_back();
    listaPacientes[iterador].cantidadSesionesActuales--;
    exclusiones.push_back(iterador);
}

bool helper::revisarDiasMaximos(int pacientesU, paciente* listaUrgente, int pacientesP, paciente* listaPaliativa, int pacientesR,
                     paciente* listaRadical){
        for (int i = 0; i < pacientesU; i++){
            if (listaUrgente[i].tiempoEspera > maxU){
                return true;
            }
        }
        for (int i = 0; i < pacientesP; i++){
            if (listaPaliativa[i].tiempoEspera > maxP){
                return true;
            }
        }
        for (int i = 0; i < pacientesR; i++){
            if (listaRadical[i].tiempoEspera > maxR){
                return true;
            }
        }
        return false;
    }

void helper::escribir(int pacientesU, paciente* listaUrgente, int pacientesP, paciente* listaPaliativa,
                  int pacientesR, paciente* listaRadical){
    int espera = 0;
    int sesiones = 0;

    //Sumo todas las esperas de los pacientes
    for (int i = 0; i < pacientesU; i++){
        espera += listaUrgente[i].tiempoEsperaPrimera;
        sesiones += listaUrgente[i].cantidadSesionesActuales;
    }

    for (int i = 0; i < pacientesP; i++){
        espera += listaPaliativa[i].tiempoEsperaPrimera;
        sesiones += listaPaliativa[i].cantidadSesionesActuales;
    }

    for (int i = 0; i < pacientesR; i++){
        espera += listaRadical[i].tiempoEsperaPrimera;
        sesiones += listaRadical[i].cantidadSesionesActuales;
    }

    if (espera <= esperaAntigua && sesiones >= sesionesAntigua){
        //Guardar nueva solucion
        //escribirla en el archivo?
        esperaAntigua = espera;
        sesionesAntigua = sesiones;
    }
    
    //TODO: terminar esto pibe
}

void helper::pasarBloque(int pacienteU, paciente* listaUrgente, int pacienteP, paciente* listaPaliativa, int pacienteR, paciente* listaRadical){
    for (int i = 0; i < pacienteU; i++){
        if (listaUrgente[i].cantidadSesionesActuales == 0){
            listaUrgente[i].tiempoEsperaPrimera++;
        }
    }

    for (int i = 0; i < pacienteR; i++){
        if (listaRadical[i].cantidadSesionesActuales == 0){
            listaRadical[i].tiempoEsperaPrimera++;
        }
    }

    for (int i = 0; i < pacienteP; i++){
        if (listaPaliativa[i].cantidadSesionesActuales == 0){
            listaPaliativa[i].tiempoEsperaPrimera++;
        }
    }
}

void helper::devolverBloque(int pacienteU, paciente* listaUrgente, int pacienteP, paciente* listaPaliativa, int pacienteR, paciente* listaRadical){
    for (int i = 0; i < pacienteU; i++){
        if (listaUrgente[i].cantidadSesionesActuales == 0){
            listaUrgente[i].tiempoEsperaPrimera--;
        }
    }

    for (int i = 0; i < pacienteR; i++){
        if (listaRadical[i].cantidadSesionesActuales == 0){
            listaRadical[i].tiempoEsperaPrimera--;
        }
    }

    for (int i = 0; i < pacienteP; i++){
        if (listaPaliativa[i].cantidadSesionesActuales == 0){
            listaPaliativa[i].tiempoEsperaPrimera--;
        }
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
    bool restriccionRota = false;
    bool pasoDia = false;
    bool siguienteBloque=false;

    //Variables para desagendar la hora
    int typoPaciente = 0; //1: U, 2: P, 3:R
    int iterador = 0; //Para saber que cliente es el que se le hizo el cambio

    //Exclusiones de pacientes en el bloque porque ya rompieron algo los weritos
    vector<int> exclusionU; 
    vector<int> exclusionP; 
    vector<int> exclusionR; 

    pasarBloque(pacientesU, listaUrgente, pacientesP, listaPaliativa, pacientesR, listaRadical);

    //cout << "Entrando en bloque: " <<  bloqueActual << endl;
    if (bloqueActual == 320){
        escribir(pacientesU, listaUrgente, pacientesP, listaPaliativa, pacientesR, listaRadical);
        return;
    }
    
    //Revisar si actualmente existe algun problema
    //RESTRICCION: los pacientes no superan el tiempo maximo de espera    
    if(bloqueActual%16==0 && bloqueActual!=0){
    	restriccionRota = revisarDiasMaximos(pacientesU, listaUrgente, pacientesP, listaPaliativa, pacientesR, listaRadical);
    	if(restriccionRota){
    		return;
        }
	}

    //Si no existen más doctores o maquinas entonces no se puede atender nadie más en ese bloque
    //deberia pasarse al siguiente bloque y resetear los doctores usados y maquinas usadas
    if (doctoresUsados == totalDoctores || maquinasUsadas == totalMaquinas){
	    siguienteBloque=true;            
    }

    //RESTRICCION: doctores solo atienden en sus horarios
    int iddoc = buscarDoc(bloqueActual, totalDoctores, listaDoctores, pacientesU,
                        listaUrgente, pacientesP, listaPaliativa, pacientesR, listaRadical); 
    
    if (iddoc == 0){
    	siguienteBloque=true;
	}
	
	if(siguienteBloque){		
		if(bloqueActual%16==15){//ultimo bloque del dia
    		pasoDia=true;
    		pasarDia(pacientesU, listaUrgente, pacientesP, listaPaliativa, pacientesR, listaRadical, bloqueActual);
		}
	
	    BT(listaDoctores, listaRadical, listaPaliativa, listaUrgente, totalDoctores, pacientesR, pacientesP,
	    pacientesU, totalMaquinas, bloqueActual+1, 0, 0);
    
    	if (pasoDia){
      		regresarDia(pacientesU, listaUrgente, pacientesP, listaPaliativa, pacientesR, listaRadical, bloqueActual);
    	}
        
        devolverBloque(pacientesU, listaUrgente, pacientesP, listaPaliativa, pacientesR, listaRadical);
    	return;
	}
    //Se busca la maquina?
    //No es necesario porque no se busca el id de la maquina, solo la cantidad
    //y como se reviso que maquinasUsadas < totalMaquinas entonces todo gud
    //y con todo gud me refiero a que debo tener un id para el segundo archivo asi que 
    //deberia tener un ++ en la llamada de BT
    //y con todo gud me refiero a que debo tener un id para el segundo archivo asi que 
    //deberia tener un ++ en la llamada de BT

    //Primero se revisan los urgentes ya que tienen menos tiempo de espera
    iterador = encontrarOtroPaciente(pacientesU, listaUrgente, exclusionU, 1, bloqueActual);
    
    if (iterador != -1){
        yaAgendo = true;
        //Se hace la sesion y se guarda el tipo para el retorno
        listaUrgente[iterador].pilaEsperas.push_back(listaUrgente[iterador].tiempoEspera);
        listaUrgente[iterador].tiempoEspera = 0;
        listaUrgente[iterador].horarioDoc[bloqueActual] = listaDoctores[iddoc].id;
        listaUrgente[iterador].horarioMaq[bloqueActual] = maquinasUsadas;
        listaUrgente[iterador].cantidadSesionesActuales++;
        typoPaciente = 1;
    }

    //if ternario para darme color, paliativos
    iterador = (iterador == -1) ? encontrarOtroPaciente(pacientesP, listaPaliativa, exclusionP, 2, bloqueActual) : iterador;
    
    if (!yaAgendo && iterador != -1){
        yaAgendo = true;

        //Se hace la sesion y se guarda el tipo para el retorno
        listaPaliativa[iterador].pilaEsperas.push_back(listaPaliativa[iterador].tiempoEspera);
        listaPaliativa[iterador].tiempoEspera = 0;
        listaPaliativa[iterador].horarioDoc[bloqueActual] = listaDoctores[iddoc].id;
        listaPaliativa[iterador].horarioMaq[bloqueActual] = maquinasUsadas;
        listaPaliativa[iterador].cantidadSesionesActuales++;
        typoPaciente = 2;
    }

    //finalmente radicales
    iterador = (iterador == -1) ? encontrarOtroPaciente(pacientesR, listaRadical, exclusionR, 3, bloqueActual) : iterador;
    if (!yaAgendo && iterador != -1){
        yaAgendo = true;

        //Se hace la sesion y se guarda el tipo para el retorno
        listaRadical[iterador].pilaEsperas.push_back(listaRadical[iterador].tiempoEspera);
        listaRadical[iterador].tiempoEspera = 0;
        listaRadical[iterador].horarioDoc[bloqueActual] = listaDoctores[iddoc].id;
        listaRadical[iterador].horarioMaq[bloqueActual] = maquinasUsadas;
        listaRadical[iterador].cantidadSesionesActuales++;
        typoPaciente = 3;
    }

   

    while(yaAgendo){
        
        BT(listaDoctores, listaRadical, listaPaliativa, listaUrgente, totalDoctores, pacientesR,
            pacientesP, pacientesU, totalMaquinas, bloqueActual, doctoresUsados+1, maquinasUsadas+1);
        //Agendamos a alguien en este bloque pero queda mas gente, por lo tanto es necesario
        //hace BT en el mismo bloque pero cambiando parametros, ahora cuando falle es necesario
        //que exista una manera de devolver los pasos, guardar algunos int o algo asi para poder devolver
        //ya que uso punteros asi que siempre son los mismos objetos 
        switch(typoPaciente){
            case 1:
                devolverHora(listaUrgente, iterador, bloqueActual, exclusionU);
                break;
            case 2:
                devolverHora(listaPaliativa, iterador, bloqueActual, exclusionP);
                break;
            case 3:
                devolverHora(listaRadical, iterador, bloqueActual, exclusionR);
                break;
        }
        
        yaAgendo = false;
        //Copy paste
        iterador = encontrarOtroPaciente(pacientesU, listaUrgente, exclusionU, 1, bloqueActual);
        if (iterador != -1){
            yaAgendo = true;

            listaUrgente[iterador].pilaEsperas.push_back(listaUrgente[iterador].tiempoEspera);
            listaUrgente[iterador].tiempoEspera = 0;
            listaUrgente[iterador].horarioDoc[bloqueActual] = listaDoctores[iddoc].id;
            listaUrgente[iterador].horarioMaq[bloqueActual] = maquinasUsadas;
            listaUrgente[iterador].cantidadSesionesActuales++;
            typoPaciente = 1;
        }

        iterador = (iterador == -1) ? encontrarOtroPaciente(pacientesP, listaPaliativa, exclusionP, 2, bloqueActual) : iterador;
        if (!yaAgendo && iterador != -1){
            yaAgendo = true;

            listaPaliativa[iterador].pilaEsperas.push_back(listaPaliativa[iterador].tiempoEspera);
            listaPaliativa[iterador].tiempoEspera = 0;
            listaPaliativa[iterador].horarioDoc[bloqueActual] = listaDoctores[iddoc].id;
            listaPaliativa[iterador].horarioMaq[bloqueActual] = maquinasUsadas;
            listaPaliativa[iterador].cantidadSesionesActuales++;
            typoPaciente = 2;
        }

        iterador = (iterador == -1) ? encontrarOtroPaciente(pacientesR, listaRadical, exclusionR, 3, bloqueActual) : iterador;
        if (!yaAgendo && iterador != -1){
            yaAgendo = true;

            listaRadical[iterador].pilaEsperas.push_back(listaRadical[iterador].tiempoEspera);
            listaRadical[iterador].tiempoEspera = 0;
            listaRadical[iterador].horarioDoc[bloqueActual] = listaDoctores[iddoc].id;
            listaRadical[iterador].horarioMaq[bloqueActual] = maquinasUsadas;
            listaRadical[iterador].cantidadSesionesActuales++;
            typoPaciente = 3;
        }
    }
	
	//no hay paciente que agendar------
    if(bloqueActual%16==15){//ultimo bloque del dia
    	pasoDia=true;
    	pasarDia(pacientesU, listaUrgente, pacientesP, listaPaliativa, pacientesR, listaRadical, bloqueActual);
	}
	
    BT(listaDoctores, listaRadical, listaPaliativa, listaUrgente, totalDoctores, pacientesR, pacientesP,
    pacientesU, totalMaquinas, bloqueActual+1, 0, 0);
    
    if (pasoDia){
        regresarDia(pacientesU, listaUrgente, pacientesP, listaPaliativa, pacientesR, listaRadical, bloqueActual);
    }
    //-------
    devolverBloque(pacientesU, listaUrgente, pacientesP, listaPaliativa, pacientesR, listaRadical);
    return;
}
