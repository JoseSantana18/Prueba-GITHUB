#define TALLA 100
//-----------------------------------FUNCIONES A UTILIZAR-----------------------
void mostrarGrafo(GRAFO *apGrafo);
void verGrafo(GRAFO *apGrafo);
void crearTarea(GRAFO *apGrafo);
void crearCamino(GRAFO *apGrafo);



//-------------------------------------------------------------------------
//Función para crear el lugar
void crearTarea(GRAFO *apGrafo){
	char respuesta = 's';
	char nombre[TALLA],descripcion[TALLA];
	int esfuerzo;
	int ID;
	char tipo[TALLA];
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
		printf("Esfuerzo: "); fflush(stdin); scanf("%d",&esfuerzo);  
		insertarVerticeLugar(apGrafo,ID,nombre,descripcion,tipo,esfuerzo);
		printf("\nREGISTRAR OTRO LUGAR <s>");
		fflush(stdin);	respuesta = getchar();
	}while((respuesta == 's' || respuesta =='S'));
}
//Función para crear el camino

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


