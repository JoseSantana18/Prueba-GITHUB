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
    char encargado[TALLA];
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

struct ARISTA
{
	ARISTA *sig; //para saber la siguiente arista
	VERTICE *tareaDestino; //Vertice destino/adyacente
	int esfuerzo; //esfuerzo de una tarea a otra
	int tiempo; //tiempo de una tarea a otra
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
VERTICE* crearVerticeLugar(int aID,char aNombre[], char aDescripcion[],char aTipo[],char aEncargado[])
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
	strcpy(nuevoLugar->lugar->encargado, aEncargado);
	
	
	//Nuevas inicializaciones
	nuevoLugar->visitado =  0;
	nuevoLugar->tiempoAcumulado = -1;
	nuevoLugar->distanciaAcumulada = -1;
	nuevoLugar->anterior = (TAREA*)malloc(sizeof(TAREA));
	nuevoLugar->anterior = NULL;
	
	return nuevoLugar;
}
//Función para insertar el vertice de un lugar en el grafo, teniendo en cuenta los datos a ingresar
//ENTRADAS: El grafo de las tareas con el ID, nombre, descripcion, tipo, encargado
void insertarVerticeLugar(GRAFO *apGrafo, int aID,char aNombre[], char aDescripcion[], char aTipo[],char aEncargado[])
{
	VERTICE *pVerticeHead, *pVerticeAux;
	if(grafoVacio(apGrafo))
	{
		apGrafo->verticeInicial = crearVerticeLugar(aID,aNombre,aDescripcion,aTipo,aEncargado);
		return;
	}
	pVerticeHead = apGrafo->verticeInicial;
	while(pVerticeHead!=NULL)
	{
		pVerticeAux = pVerticeHead; 
		pVerticeHead = pVerticeHead->sig;
	}
	pVerticeAux->sig = crearVerticeLugar(aID,aNombre,aDescripcion,aTipo,aEncargado);
	pVerticeAux->sig->sig = NULL;

	apGrafo->cantVertices = apGrafo->cantVertices+1;

	return;	
}
//Función que permite obtener el vertice (tarea) de un grafo dado su el nombre de la tarea
//ENTRADAS: El grafo de las tareas y un dato de tipo char que almacena el nombre de la tarea
//SALIDAS: La función retornará NULL si la tarea no existe y retornará el vertice si sí existe la tarea
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



//Función que permite mostrar el grafo como una lista de adyacencia tomando en cuenta las tareas (vertices) y caminos (aristas)
//ENTRADAS: El grafo con las tareas y caminos
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
		printf("Encargado de la tarea: %s\n",pVerticeAux->lugar->encargado);
		printf("_______________________________________  -->");
		pAristaAux = pVerticeAux->adyacente;
		while(pAristaAux != NULL)
		{
			printf("|Destino:%s|Esfuerzo:%d|Tiempo:%d|-->", pAristaAux->tareaDestino->lugar->nombre,pAristaAux->esfuerzo,pAristaAux->tiempo);
			pAristaAux = pAristaAux->sig;
		}
		pVerticeAux = pVerticeAux->sig;
		printf("\n");	
	}
	}


ListaT *crearLista(void)
{
	ListaT *L;
	L=(ListaT*)malloc(sizeof(ListaT));
	L->inicio=NULL;
	return L;
}

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

//Funcion que permite crear una arista (camino) en el grafo,la cual almacena los sig.tes datos: esfuerzo y tiempo de solucion
//ENTRADAS: datos de tipo int que indiquen el esfuerzo y tiempo de traslado. 
ARISTA* crearArista(int esfuerzo, int tiempo)
{
	ARISTA *nuevaArista = NULL;
	nuevaArista = (ARISTA*)malloc(sizeof(ARISTA));
	nuevaArista->sig = NULL;
	nuevaArista->esfuerzo = esfuerzo;
	nuevaArista->tiempo = tiempo;
	nuevaArista->tareaDestino =(VERTICE*)malloc(sizeof(VERTICE));
	nuevaArista->tareaDestino = NULL;
	return nuevaArista;
}
//Función que permite insertar una arista (camino) dentro del grafo. Tomando en cuenta la tarea de origen y destino, el esfuerzo y tiempo de traslado entre origen-destino
//ENTRADAS: Datos de tipo VERTICE que indiquen la ubicación del destino y origen en memoria, el esfuerzo y tiempo de traslado
void insertarArista(VERTICE *apOrigen,VERTICE *apDestino,int esfuerzo, int tiempo)  
{
	ARISTA *newArista = crearArista(esfuerzo, tiempo);
	ARISTA *pAristaAux;
	pAristaAux = apOrigen->adyacente;
	
	if(pAristaAux == NULL)
	{
		apOrigen->adyacente = newArista;
		newArista->tareaDestino = apDestino;
		
	}else{
		while(pAristaAux->sig!=NULL)
		{
			pAristaAux = pAristaAux->sig;
		}
		pAristaAux->sig = newArista;
		newArista->tareaDestino = apDestino;
		newArista->sig = NULL;
	}
}