#define TALLA 100
//-----------------------------------------------------------Estructuras a utilizar para crear el grafo-----------------------------------------------------
typedef struct TAREA TAREA;
typedef struct ARISTA ARISTA;
typedef struct VERTICE VERTICE;
typedef struct GRAFO GRAFO;
typedef struct ListaT ListaT;
typedef struct NodoT NodoT;
//-----------------------------------------------------------------------------------------------------------------------------------------------------------

struct ListaT{
	NodoT *inicio;
};
struct NodoT{
	NodoT *siguiente;
};

struct TAREA
{
	int ID;
    char nombre[TALLA];
    char descripcion[TALLA];
    char tipo[TALLA];
    int esfuerzo;
};

struct VERTICE
{
	TAREA *lugar; //lugar que va a representar
	ARISTA *adyacente; //
	VERTICE *sig; //apunta la siguiente vertice
	
	int visitado;
	float tiempoAcumulado; // se va ir guardando el camino
	float distanciaAcumulada;
	TAREA *anterior; // se va ir guardando el lugar anterior

};


struct GRAFO
{
	int cantVertices;
	VERTICE *verticeInicial;
};


//Inicializar el grafo
GRAFO *nuevoGrafo(void)
{ 
	GRAFO *Grafo;
	Grafo = (GRAFO*)malloc(sizeof(GRAFO));
	Grafo->cantVertices = 0;
	Grafo->verticeInicial = NULL;
	return Grafo;
}
//Liberar grafo


void liberarGrafo(GRAFO *apGrafo)
{
	VERTICE *aux;
	
	while(apGrafo->verticeInicial !=NULL)
	{
		aux = apGrafo->verticeInicial;
		apGrafo->verticeInicial = apGrafo->verticeInicial->sig;
		aux = NULL;
		free(aux);
	}
	apGrafo->cantVertices = 0;
	return;
}
//Return 1 si el grafo está vacio; 0 si no
int grafoVacio(GRAFO *pGrafo)
{
	if(pGrafo->verticeInicial == NULL){return 1;}
	else{return 0;}
}

//Return cantidad de vertices en el grafo
int tamanoGrafo(GRAFO *pGrafo)
{
	return pGrafo->cantVertices; //retorna la cantidad de vertices
}

//Inicializa un nodo lugar
VERTICE* crearVerticeLugar(int aID,char aNombre[], char aDescripcion[],char aTipo[], int aEsfuerzo)
{
	VERTICE *nuevoLugar;
	nuevoLugar = (VERTICE*) malloc(sizeof(VERTICE));
	nuevoLugar->adyacente = NULL;
	nuevoLugar->sig = NULL;
	nuevoLugar->lugar =(TAREA*)malloc(sizeof(TAREA));
	nuevoLugar->lugar->ID = aID;
	strcpy(nuevoLugar->lugar->nombre,aNombre);
	strcpy(nuevoLugar->lugar->descripcion, aDescripcion);
	strcpy(nuevoLugar->lugar->tipo, aTipo);
	nuevoLugar->lugar->esfuerzo = aEsfuerzo;
	
	//Nuevas inicializaciones
	nuevoLugar->visitado =  0;
	nuevoLugar->tiempoAcumulado = -1;
	nuevoLugar->distanciaAcumulada = -1;
	nuevoLugar->anterior = (TAREA*)malloc(sizeof(TAREA));
	nuevoLugar->anterior = NULL;
	
	return nuevoLugar;
}
//Función para insertar el vertice de un lugar en el grafo, teniendo en cuenta los datos a ingresar, entre ellos: el nombre del lugar, la provincia de pertenciencia y la población
//ENTRADAS: El grafo de los lugares, el nombre del lugar, provincia y población
void insertarVerticeLugar(GRAFO *apGrafo, int aID,char aNombre[], char aDescripcion[], char aTipo[],int aEsfuerzo)
{
	VERTICE *pVerticeHead, *pVerticeAux;
	if(grafoVacio(apGrafo))
	{
		apGrafo->verticeInicial = crearVerticeLugar(aID,aNombre,aDescripcion,aTipo,aEsfuerzo);
		return;
	}
	pVerticeHead = apGrafo->verticeInicial;
	while(pVerticeHead!=NULL)
	{
		pVerticeAux = pVerticeHead; 
		pVerticeHead = pVerticeHead->sig;
	}
	pVerticeAux->sig = crearVerticeLugar(aID,aNombre,aDescripcion,aTipo,aEsfuerzo);
	pVerticeAux->sig->sig = NULL;

	apGrafo->cantVertices = apGrafo->cantVertices+1;

	return;	
}
//Función que permite obtener el vertice (lugar) de un grafo dado su el nombre del lugar
//ENTRADAS: El grafo de los lugares y un dato de tipo char que almacena el nombre del lugar
//SALIDAS: La función retornará NULL si el lugar no existe y retornará el vertice si sí existe el lugar
VERTICE *getVertice(GRAFO *grafo,char nombreLugar[])
{
	VERTICE *nVerticeAux = NULL;
	nVerticeAux = grafo->verticeInicial;
	while(nVerticeAux!=NULL)
	{
		if(strcmp(nombreLugar, nVerticeAux->lugar->nombre)==0){
			return nVerticeAux;
		}
		nVerticeAux = nVerticeAux->sig;
	}
	return NULL;
	
}

//Funcion que permite crear una arista (camino) en el grafo,la cual almacena los sig.tes datos: Tiempo y la distanacia de traslado
//ENTRADAS: datos de tipo float que indiquen el tiempo y distancia de traslado. 

//Función que permite mostrar el grafo como una lista de adyacencia tomando en cuenta los lugares (vertices) y caminos (aristas)
//ENTRADAS: El grafo con los lugares y caminos
void listaAdyacencia(GRAFO *apGrafo)
{
	VERTICE *pVerticeAux;
	ARISTA *pAristaAux;
	
	pVerticeAux = apGrafo->verticeInicial;
	while(pVerticeAux != NULL)
	{ 
		printf("_____________________");
		printf("\nID: %d\n",pVerticeAux->lugar->ID);
		printf("Tarea %s\n",pVerticeAux->lugar->nombre);
		printf("Descripcion: %s\n",pVerticeAux->lugar->descripcion);
		printf("Tipo de tarea: %s\n",pVerticeAux->lugar->tipo);
		printf("Esfuerzo: %d\n",pVerticeAux->lugar->esfuerzo);
		printf("_____________________  -->");
		pVerticeAux = pVerticeAux->sig;
		printf("\n");	
	}
}
//Función que permite eliminar una arista (camino) tomando en cuenta el destino y origen del camino
//ENTRADAS: Punteros que referencian la ubicacion de origen y el destino

ListaT *crearLista(void)
{
	ListaT *L;
	L=(ListaT*)malloc(sizeof(ListaT));
	L->inicio=NULL;
	return L;
}
//FUNCION PARA CREAR UN NODO
//E: nombre del transporte, maximo de pasajeros, minimo de pasajeros, cantidad de viajes
//S: nodo creado
//R: NH
void liberarListaT(ListaT *L)
{
	NodoT *n,*aux;
	if(L->inicio == NULL){
		return;
	}
	if(L->inicio->siguiente == NULL){
		return ;
	}
	n=L->inicio;
	while(n != NULL){
		aux=n;
		n=n->siguiente;
		free(aux);
	}
}
