/*--------------------------------------------------------
* CURSO: Algoritmos y estructuras de datos
* PROFESORA: Maria Jose Artavia Jimenez
* ASIGNACION: PROYECTO2
* ESTUDIANTE1: Jose Santana Solís
* ESTUDIANTE2: Gabriel Rivera
* ESTUDIANTE3: Pablo Solís Valverde
* II SEMESTRE 2022
---------------------------------------------------------*/
//----------------------Librerias------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "Grafo.h"
#include "Mapa.h"
//#include "Transportes.h"

//------------------------------------------------------
//----------------------Variables-----------------------
//VARIABLES GENERALES
#define TALLA 100
#define VERDADERO			88
#define FALSO				89
//VARIABLES PARA EL MENU DE LUGARES
#define CREAR_TAREA		 	90
#define MODIFICAR_TAREA			91
#define CREAR_CAMINO			92
#define ATRAS_TAREA				93	
#define VER_GRAFO				94

//-------------------------------------------------------------Funciones a utilizar--------------------------------------------------
void menuTareas(GRAFO *apGrafo);
int menuTareasAux();
ListaT *crearLista(void);
void mostrarListaT(const ListaT *L);
void liberarListaT(ListaT *L);
//-----------------------------------------------------------------MENU LUGARES------------------------------------------------------
//Funcion que contiene el menu de las funcionalidades para gestionar lugares (Crear lugar, eliminar lugar, crear camino, eliminar camino)
//ENTRADAS: El grafo del lugares
void menuTareas(GRAFO *apGrafo)
{
	int 	Salir = FALSO;
	do{
		switch(menuTareasAux())
		{
			case CREAR_TAREA:{
				system("cls");
				crearTarea(apGrafo);
				break;
			}
			case MODIFICAR_TAREA:
			{
				
			}
			case CREAR_CAMINO:
			{
				system("cls");
				crearCamino(apGrafo);
				break;	
			}
			case VER_GRAFO:{
				system("cls");
				printf("\t\tGRAFO TAREAS\n");
				verGrafo(apGrafo);
				break;
			}
			case ATRAS_TAREA:{
				Salir = VERDADERO;
				break;
			}
		}
	}while(Salir != VERDADERO);
	//return ;
}

//Funcion que depliega las opciones que existe en el menu de lugares, la funcion retornara la opcion que ingreso el usuario 
//1. CREAR_TAREA 2. MODIFICAR_TAREA 3. CREAR_RUTA 4.VER_GRAFO 5.ATRAS_TAREA
int menuTareasAux()
{
	int indice = 0;
	const int opciones[] = {
		CREAR_TAREA, MODIFICAR_TAREA, CREAR_CAMINO, VER_GRAFO,ATRAS_TAREA};
		
	do{
		system("cls");
		printf("\t\tMENU TAREAS\n\n");
		printf("1- CREAR TAREA\n2- MODIFICAR TAREA\n3- CREAR RUTA\n4- VER GRAFO\n5- ATRAS\nINGRESE LA OPCION SELECCIONADA: ");
		fflush(stdin);
		indice = getchar()-48;
		
	}while((indice<1)||(indice>5));
	return opciones[indice-1];
}

//Funcion para validar un entero
int validarEntero(char numero[])
{
    int i;
    for (i=0; i<strlen(numero); i++)
    {
        if(!isdigit(numero[i]))
            return 0;
    }
    return 1;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------MENU PRINCIPAL---------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------*/
int validarEntero(char numero[]);
//Funcion que despliega el menu principal del sistema
//ENTRADAS: El grafo para ingresar caminos y tareas / La lista para ingresar los datos de la configuracion de la administración de proyectos
void menuPrincipal(GRAFO *apGrafo,ListaT *L){
	system("cls");
	char opAux[10];
	int op;
	bool continuar= true;
	printf("\n------------------------APTEC------------------------\n\n");
	printf("\n-------------------------------MENU PRINCIPAL-------------------------------\n\n");
    printf("PUEDE REALIZAR LAS SIGUIENTES OPCIONES:\n");
    printf(" 1. FUNCIONALIDADES PARA TAREAS\n");
    printf(" 2. FUNCIONALIDADES PARA RECURSOS\n");
    printf(" 3. FUNCIONALIDADES SOBRE RECOMENDACIONES\n");
    printf(" 4. SALIR\n");
    do{
    	printf("\nINGRESE LA OPCION SELECCIONADA: ");
    	scanf("%s",&opAux);
    	if(validarEntero(opAux)==1)
    	{
    		op=atoi(opAux);
			switch(op){
				case 1:{
					menuTareas(apGrafo);
					continuar=false;
					menuPrincipal(apGrafo,L);
					break;
				}
				case 2:{
					
				}
				case 3:{
					
				}
		
				case 4:{
					printf("\n\n\t\tHA SALIDO DEL SISTEMA\n");
					continuar=false;
					break;
				}
				default:{
					printf("\nERROR, INGRESE UNA OPCION CORRECTA\n");
					continuar=true;
					break;
				}    		
		}}
		else{
    		printf("\nERROR, DEBE INGRESAR SOLO NUMEROS\n");
			continuar=true;
			}
		
	}while(continuar);
	continuar=false;
	return; 
}
int main(){
	GRAFO *G;
	ListaT *L;
	L=crearLista();
	G= nuevoGrafo();
	menuPrincipal(G,L);
	liberarGrafo(G);
	liberarListaT(L);
	return 0;
}
