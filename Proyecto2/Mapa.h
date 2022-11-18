#define TALLA 100
//-----------------------------------FUNCIONES A UTILIZAR-----------------------
void mostrarGrafo(GRAFO *apGrafo);
void verGrafo(GRAFO *apGrafo);
void crearTarea(GRAFO *apGrafo);
void crearCamino(GRAFO *apGrafo);



//-------------------------------------------------------------------------
//Función para crear la tarea
void crearTarea(GRAFO *apGrafo){
	char respuesta = 's';
	char nombre[TALLA],descripcion[TALLA];
	int ID;
	char tipo[TALLA];
	char encargado[TALLA];
	do
	{
		system("cls");
		printf("\t\tREGISTRAR TAREA\n\n");
		//Datos que se solicitan al usuario
		printf("\t\t**INGRESE LOS SIGUIENTES DATOS**\n\n");
		printf("ID: "); fflush(stdin); scanf("%d",&ID); 
		printf("NOMBRE DE LA TAREA: ");fflush(stdin); scanf(" %99[^\n]", &nombre);
		printf("BREVE DESCRIPCION: "); fflush(stdin);scanf(" %99[^\n]",&descripcion);
		printf("TIPO DE TAREA: \n");
		printf("Recuerde que son: \n"); 
		printf("Tarea Operativa, Tarea de Aprobacion, Firma de Contrato, Tarea de Gestion, Cambios: "); fflush(stdin);scanf(" %99[^\n]",&tipo);
		printf("ENCARGADO DE LA TAREA: ");fflush(stdin); scanf(" %99[^\n]", &encargado); 
		insertarVerticeLugar(apGrafo,ID,nombre,descripcion,tipo,encargado);
		printf("\nREGISTRAR OTRO LUGAR <s>");
		fflush(stdin);	respuesta = getchar();
	}while((respuesta == 's' || respuesta =='S'));
}


//Función para ver el grafo
void verGrafo(GRAFO *apGrafo){
	char respuesta;
	do
	{
		listaAdyacencia(apGrafo);
		printf("Ingrese enter para volver al menu: ");
		fflush(stdin); respuesta=getchar();
	}while((respuesta == '/'));
}

//Función para crear el camino
void crearCamino(GRAFO *apGrafo){
	char respuesta= 's';
	char nombreOrigen[TALLA];
	char nombreDestino[TALLA];
	int esfuerzo,tiempo;
	VERTICE *origen;
	VERTICE *destino;
	do
	{
		system("cls");
		printf("\t\tREGISTRAR CAMINO\n\n");
		//Datos que se le solicitean al usuario
		printf("\t\t**INGRESE LOS SIGUIENTES DATOS**\n\n");
		printf("TAREA ORIGEN: ");fflush(stdin); scanf(" %99[^\n]",&nombreOrigen);
		printf("TAREA DESTINO: ");fflush(stdin);scanf(" %99[^\n]",&nombreDestino);
		printf("ESFUERZO(ESCALA DEL 1 AL 5): ");fflush(stdin);scanf("%d",&esfuerzo);
		printf("TIEMPO ORIGEN-DESTINO (minutos): ");fflush(stdin);scanf("%d",&tiempo);
		origen=getVertice(apGrafo, nombreOrigen);
		destino=getVertice(apGrafo,nombreDestino);
		if(origen==NULL || destino==NULL){
			printf("No es posible crear el camino. Origen o destino incorrectos.");
		}
		else{
			insertarArista(origen,destino,esfuerzo,tiempo);
		}
		printf("\nREGISTRAR OTRO LUGAR <s>");
		fflush(stdin);	respuesta = getchar();
	}while((respuesta == 's' || respuesta =='S'));
	
}