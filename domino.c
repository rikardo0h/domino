#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
 //Esturcutra pila
 typedef struct _nodo {
   int valor;
   int frente;
   int atras;
   int mula;
   struct _nodo *siguiente;
} tipoNodo;
 
typedef tipoNodo *pNodo;
typedef tipoNodo *Pila;

 
typedef struct ElementoLista{
    int dato;    
    int mula;
    struct ElementoLista *siguiente;
}Elemento;
 
typedef struct ListaIdentificar{
    Elemento *inicio;
    Elemento *fin;
    int tamano;
}Lista;
 

void incializacion(Lista *lista); 
int InsercionEnListaVacia(Lista *lista, int dato,int mul);
int InsercionInicioLista(Lista *lista, int dato);  
int InsercionFinLista(Lista *lista, Elemento *actual, int dato,int mul);
int EliminarInicio(Lista *lista); 



int EliminarEnLista(Lista *lista, int pos);


void visualizacion(Lista *lista);



int busqueda_mula(Lista *lista);
void ver_juego(Lista *lista);

//Funciones pila


/* Funciones con pilas: */
void Push(Pila *pila, int frente,int atras,int mul);
pNodo Pop(Pila *pila) ;
void generar_fichas( Pila *pila); 
int vacia(Pila *pila);
void repartir( Pila *pila,Lista *lista,Lista *lista2);



int main()
{
    //Generar fichas
    //Pila de fichas
   Pila pila = NULL;
   generar_fichas(&pila);
    
	
	char eleccion;
    char *nom;
    Lista *lista,*lista2,*juego;
    Elemento *actual;
 	int aux;
 	
    if ((lista = (Lista *) malloc (sizeof (Lista))) == NULL)
        return -1;
    if ((lista2 = (Lista *) malloc (sizeof (Lista))) == NULL)
        return -1;
	
	if ((juego = (Lista *) malloc (sizeof (Lista))) == NULL)
        return -1;
	
	if ((nom = (char *) malloc (50)) == NULL)
        return -1;
    actual = NULL;
    eleccion = 'o';
 
    incializacion(lista);
    incializacion(lista2);
    incializacion(juego);
    ///////// Repartir las fichas a los usuarios
    repartir(&pila,lista,lista2);
    printf ("\n\n Fichas asignadas, turno del jugador que tenga la mula de 6");
    
	////////////// Observar las fichas 
    
    printf ("\n Fichas dle jugador 1 : \n ");
    visualizacion(lista);
    printf ("\n Fichas dle jugador 2 : \n ");
    visualizacion(lista2);
    
	int jugador1=0;
    int jugador2=0;
    
    jugador1 = busqueda_mula(lista);
    jugador2 = busqueda_mula(lista2);
    
	//VE QUE USUARIO TIENE LA MULA MAYOR
	int partida=0;
    if(jugador1>jugador2){
    	printf("\n JUGADOR 1 Comienza \n");    	
	}else{
		if(jugador1<jugador2){
			partida=1;
			printf("\n JUGADOR 2 Comienza \n");	
		}else{
			//Por defecto en caso de que no alla mullas
			printf("\n JUGADOR 1 Comienza \n");	
		}		
	}
   	
	
	printf("Tamaño= %i",lista->tamano/2);
	printf("Tamaño= %i",lista2->tamano/2);
	int menu;
	int e1=0,e2=0;
	int lado,otroLado,op;
	while((lista->tamano/2>0)&&(lista2->tamano/2>0)){
		printf("\n 							JUGANDO 					\n");	
		switch (partida){
			if(lista->tamano==0){
					printf("\n 							JUGADOR 1 GANOOOOO 					\n");			
			}else{
				if(lista2->tamano==0){
					printf("\n 							JUGADOR 2 GANOOOOO 					\n");			
				}else{											
			case 0:
				system("cls");
				printf("\n JUGADOR 1  \n");    				
				printf("\n -------------- Juego --------   \n");//,juego->inicio->dato,juego->fin->dato);								
				ver_juego(juego);
				printf("\n -------------- Juego -------- \n");											
				
				printf("\n -------------- Fichas propias -------- \n");			
				visualizacion(lista);								
				printf("\n -------------- Fichas propias -------- \n");			
				
				
				
				printf("\n Preciona opcion deseada");
				printf("\n 1- Comer");
				printf("\n 2- Jugar ficha");
				printf("\n 3- pila");
				printf("\n telclea Opcion: ");
				scanf ("%i", &menu);
				switch (menu){
					case 1:						
						if(!vacia(&pila)){
							printf("COMER");						
							pNodo nodo = Pop(&pila);
							printf("Saque Nodo -> %i %i ",nodo->frente,nodo->atras);
							InsercionFinLista(lista,lista->fin,nodo->frente,nodo->mula);																									
							InsercionFinLista(lista,lista->fin,nodo->atras,nodo->mula);																
							
						}else{
							printf("No hay que comer");	
							getch();						
						}									
						
						getchar ();
					break;
					case 2:									
						
						printf("\n Selecciona el numero de ficha a meter?");						
						scanf ("%i", &menu);
						//Elimina la primera 0
						if(menu==0){
							e1 = EliminarInicio(lista);
							e2 = EliminarInicio(lista);
						}else{
							e1 = EliminarEnLista (lista, menu*2);						    
							e2 = EliminarEnLista (lista, menu*2);						    	
						}				
						
						if(juego->tamano==0){
							InsercionEnListaVacia(juego,e1,0);
							InsercionFinLista(juego,juego->fin,e2,0);																
							printf("\n -------------- Juego --------  %i %i \n",e1,e2);
							ver_juego(juego);
							printf("\n -------------- Juego -------- \n");								
						}else{
							if((e1==juego->fin->dato)||(e1==juego->inicio->dato)||(e2==juego->fin->dato)||(e2==juego->inicio->dato)){
								printf("¿Qué lado usaras? Izquiera o derecha    %i || %i",e1,e2);								
								printf("\n 1- Izquieerda %i ",e1);
								printf("\n 2- Derecha %i ",e2);
								scanf ("%i", &lado);								
								if(lado==1){
									lado=e1;
									otroLado=e2;
								}else{
									lado=e2;
									otroLado=e1;
								}
								printf("Lado = %i   %i  %i",lado,juego->inicio->dato,juego->fin->dato);
								if((lado!=juego->inicio->dato)&&(lado!=juego->fin->dato)){
									printf("Lado no compatible, se usara el otro");
									if(lado==e1){										
										lado==e2;
										otroLado=e1;
									}else{
										lado==e1;
										otroLado=e2;
									}									
								}
								
								printf("\n  ¿En que lado pondras la ficha?");
								printf("\n 1- izquiera = %i ",juego->inicio->dato);
								printf("\n 2- Derecha = %i ",juego->fin->dato);
								scanf ("%i", &op);								
								
								if(op==1){
									InsercionInicioLista(juego,lado);									
									InsercionInicioLista(juego,otroLado);																
								}else{
									InsercionFinLista(juego,juego->fin,lado,0);						
									InsercionFinLista(juego,juego->fin,otroLado,0);						
								}
								
								
								printf("\n  %i -------------- Juego -------- %i   \n",e1,e2);								
								ver_juego(juego);
								printf("\n -------------- Juego -------- \n");			
							}else{							
								printf("\n -------------- Juego -------- %i %i \n",e1,e2);
								printf("\n Puedes poner COMER o usar otra >> %i o << %i ",juego->fin->dato,juego->inicio->dato);
								InsercionFinLista(lista,lista->fin,e1,0);																									
								InsercionFinLista(lista,lista->fin,e2,0);																
								printf("\n -------------- Juego -------- \n");			
							}
						}
						if(lista->tamano==0){
							printf("\n 							JUGADOR 1 GANOOOOO 					\n");			
						}			
						visualizacion (lista);						      																								
						getch();							
					break;
					case 3:
						printf("ver pila");
						pNodo nodo2;
						while(!vacia(&pila)){
							 nodo2= Pop(&pila);
							 printf("Nodo -> %i %i ",nodo2->frente,nodo2->atras);
						}
						getchar ();
						break;
				}				
				//getchar ();
				partida=1;
			break;
			case 1:				
					system("cls");
				printf("\n JUGADOR 2  \n");    				
				printf("\n -------------- Juego --------   \n");//,juego->inicio->dato,juego->fin->dato);								
				ver_juego(juego);
				printf("\n -------------- Juego -------- \n");											
				
				printf("\n -------------- Fichas propias -------- \n");			
				visualizacion(lista2);								
				printf("\n -------------- Fichas propias -------- \n");			
				
				
				printf("\n Preciona opcion deseada");
				printf("\n 1- Comer");
				printf("\n 2- Jugar ficha");
				printf("\n 3- pila");
				printf("\n telclea Opcion: ");
				scanf ("%i", &menu);
				switch (menu){
					case 1:						
						if(!vacia(&pila)){
							printf("COMER");						
							pNodo nodo = Pop(&pila);
							printf("Saque Nodo -> %i %i ",nodo->frente,nodo->atras);
							InsercionFinLista(lista2,lista2->fin,nodo->frente,nodo->mula);																									
							InsercionFinLista(lista2,lista2->fin,nodo->atras,nodo->mula);																
							
						}else{
							printf("No hay que comer");							
							getch();
						}									
						
						getchar ();
					break;
					case 2:									
						
						printf("\n Selecciona el numero de ficha a meter?");						
						scanf ("%i", &menu);
						//Elimina la primera 0
						if(menu==0){
							e1 = EliminarInicio(lista2);
							e2 = EliminarInicio(lista2);
						}else{
							e1 = EliminarEnLista (lista2, menu*2);						    
							e2 = EliminarEnLista (lista2, menu*2);						    	
						}				
						
						if(juego->tamano==0){
							InsercionEnListaVacia(juego,e1,0);
							InsercionFinLista(juego,juego->fin,e2,0);																
							printf("\n -------------- Juego --------  %i %i \n",e1,e2);
							ver_juego(juego);
							printf("\n -------------- Juego -------- \n");								
						}else{
							if((e1==juego->fin->dato)||(e1==juego->inicio->dato)||(e2==juego->fin->dato)||(e2==juego->inicio->dato)){
								printf("¿Qué lado usaras? Izquiera o derecha    %i || %i",e1,e2);								
								printf("\n 1- Izquieerda %i ",e1);
								printf("\n 2- Derecha %i ",e2);
								scanf ("%i", &lado);								
								if(lado==1){
									lado=e1;
									otroLado=e2;
								}else{
									lado=e2;
									otroLado=e1;
								}
								printf("Lado = %i   %i  %i",lado,juego->inicio->dato,juego->fin->dato);
								if((lado!=juego->inicio->dato)&&(lado!=juego->fin->dato)){
									printf("Lado no compatible, se usara el otro");
									if(lado==e1){										
										lado==e2;
										otroLado=e1;
									}else{
										lado==e1;
										otroLado=e2;
									}									
								}
								
								printf("\n  ¿En que lado pondras la ficha?");
								printf("\n 1- izquiera = %i ",juego->inicio->dato);
								printf("\n 2- Derecha = %i ",juego->fin->dato);
								scanf ("%i", &op);								
								
								if(op==1){
									InsercionInicioLista(juego,lado);									
									InsercionInicioLista(juego,otroLado);																
								}else{
									InsercionFinLista(juego,juego->fin,lado,0);						
									InsercionFinLista(juego,juego->fin,otroLado,0);						
								}
								
								
								printf("\n  %i -------------- Juego -------- %i   \n",e1,e2);								
								ver_juego(juego);
								printf("\n -------------- Juego -------- \n");			
							}else{							
								printf("\n -------------- Juego -------- %i %i \n",e1,e2);
								printf("\n Puedes poner COMER o usar otra >> %i o << %i ",juego->fin->dato,juego->inicio->dato);
								InsercionFinLista(lista2,lista2->fin,e1,0);																									
								InsercionFinLista(lista2,lista2->fin,e2,0);																
								printf("\n -------------- Juego -------- \n");			
							}
						}
						visualizacion (lista2);						      																								
						if(lista2->tamano==0){
							printf("\n 							JUGADOR 2 GANOOOOO 					\n");			
						}			
						getch();							
					break;
					case 3:
						printf("ver pila");
						pNodo nodo2;
						while(!vacia(&pila)){
							 nodo2= Pop(&pila);
							 printf("Nodo -> %i %i ",nodo2->frente,nodo2->atras);
						}
						getchar ();
						break;
				}				
				//getchar ();				
				partida=0;
			break;
		}
	} 
		}
			}
   
    
    int k, pos;

  return 0;
}
 
 
/*Inicializar una lista*/
void incializacion(Lista *lista){
    lista->inicio = NULL;
    lista->fin= NULL;
    lista->tamano = 0;    
}
 
/*Inserción en una lista vacía */
int InsercionEnListaVacia(Lista *lista, int dato,int mul){
    Elemento *nuevo_elemento;
    
    if((nuevo_elemento = (Elemento *)malloc(sizeof(Elemento)))==NULL)
        return -1;
        
    if((nuevo_elemento->dato = (int *)malloc(sizeof(int)))==NULL)
        return -1;
        
    if((nuevo_elemento->mula = (int *)malloc(sizeof(int)))==NULL)
        return -1;
    
    //strcpy(nuevo_elemento->dato, dato);
    
    nuevo_elemento->dato= dato;
    nuevo_elemento->mula=mul;
 
    nuevo_elemento->siguiente = NULL;
    lista->inicio = nuevo_elemento;
    lista->fin = nuevo_elemento;
    lista->tamano++;
    
    return 0;
}
 
/*Insercion al inicio de una lista*/

int InsercionInicioLista(Lista *lista, int dato){
    Elemento *nuevo_elemento;
    if((nuevo_elemento = (Elemento *)malloc(sizeof(Elemento)))==NULL)
        return -1;
    if((nuevo_elemento->dato = (int *)malloc(sizeof(int)))==NULL)
        return -1;
        
    nuevo_elemento->dato = dato;
 
    nuevo_elemento->siguiente = lista->inicio;
    lista->inicio=nuevo_elemento;
    lista->tamano++;
    return 0;
}

 
/*Insercion al final de la lista */
int InsercionFinLista(Lista *lista, Elemento *actual, int dato,int mul){
    Elemento *nuevo_elemento;
    if((nuevo_elemento = (Elemento *)malloc(sizeof(Elemento)))==NULL)
        return -1;
    if((nuevo_elemento->dato = (int *)malloc(sizeof(int)))==NULL)
        return -1;
        
    if((nuevo_elemento->mula = (int *)malloc(sizeof(int)))==NULL)
        return -1;
    
    nuevo_elemento->dato= dato;
    nuevo_elemento->mula=mul;
 	
    actual->siguiente = nuevo_elemento;
    nuevo_elemento->siguiente = NULL; 	
    lista->fin = nuevo_elemento;
    lista->tamano++;    
    return 0;
}
 

/*Eliminar en el inicio de la lista*/

int EliminarInicio(Lista *lista){
    if(lista->tamano == 0)
        return -1;
    Elemento *sup_elemento;
    sup_elemento = lista->inicio;
    lista->inicio=lista->inicio->siguiente;
    if(lista->tamano==1)
        lista->fin = NULL;
    //free(sup_elemento->dato);
    free(sup_elemento);
    lista->tamano--;
    return sup_elemento->dato;
}
 
/*Eliminar en X posicion de la lista*/

int EliminarEnLista(Lista *lista, int pos){
	int aux;
    if(lista->tamano <= 1 ||  pos < 1 || pos >= lista->tamano)
        return -1;
    int i;
    Elemento *actual;
    Elemento *sup_elemento;
    actual = lista->inicio;
    for(i=1;i<pos;++i)
        actual = actual ->siguiente;
    sup_elemento = actual->siguiente;
    actual->siguiente = actual->siguiente->siguiente;
    if(actual->siguiente==NULL)
        lista->fin = actual;
    aux=sup_elemento->dato;
    free(sup_elemento);
    lista->tamano--;
    return aux;
}

/*visualizar lista entera*/
void visualizacion(Lista *lista){	
    Elemento *actual;
    actual = lista->inicio;    
    int x=0,w=0;
	printf("  FICHA     Num de Ficha     \n");		    
    while(actual != NULL){
    		if(x==2){
    			printf("     %i     \n",w);		
    			x=0;
    			w++;
			}
			printf("%i | ",actual->dato);				
			x++;    		
            //printf("%p - %i\n",actual,actual->dato);
            actual = actual->siguiente;
    }
    printf("     %i     \n",w);		
}

void ver_juego(Lista *lista){	
    Elemento *actual;
    actual = lista->inicio;    
    int x=0,w=0;	
    while(actual != NULL){    		
			printf("%i | ",actual->dato);				
			x++;    		
            //printf("%p - %i\n",actual,actual->dato);
            actual = actual->siguiente;
    }    
}

 

void Push(Pila *pila, int frente,int atras,int mul) {
   pNodo nuevo;
 
   /* Crear un nodo nuevo */
   nuevo = (pNodo)malloc(sizeof(tipoNodo));
   
   nuevo->frente = frente;
   nuevo->atras = atras;
   nuevo->mula = mul;
   
   /* Añadimos la pila a continuación del nuevo nodo */
   nuevo->siguiente = *pila;
   /* Ahora, el comienzo de nuestra pila es en nuevo nodo */
   *pila = nuevo;
}

pNodo Pop(Pila *pila) {
   pNodo nodo; /* variable auxiliar para manipular nodo */
   int v;      /* variable auxiliar para retorno */
   
   /* Nodo apunta al primer elemento de la pila */
   nodo = *pila;
   if(!nodo) return 0; /* Si no hay nodos en la pila retornamos 0 */
   /* Asignamos a pila toda la pila menos el primer elemento */
   *pila = nodo->siguiente;
   /* Guardamos el valor de retorno */
   v = nodo->valor; 
   /* Borrar el nodo */
   //free(nodo);
   return nodo;
}

void generar_fichas(Pila *pila){
	int x,y,w;
	Pila pila2 = NULL;
	Pila pilas[6];
	pNodo nodo;
    /*for (x=0; x<7; x++) {
    	pilas[x]=NULL;
        for (y=0; y<7; y++) {            
            Push(&pilas[x],x,y);
        }
    }
    */
    int au;
    int mul=0;
    for(au=0,x=6;x>=0;x--){		
		printf("\n <<<>>>>");
		pilas[x]=NULL;
		for(y=0;y<=x;y++,au++){
			printf("\n Ficha %i= %i,%i",au,x,y);						
			if(x==y){
				printf("mula");
				mul=1;
			}
			Push(&pilas[x],x,y,mul);
			mul=0;
		}		
	}
	
	
   //Llenado de la pila al azar
    int numero;
    srand(time(NULL));
    for(x=0,numero=0;x<28;){
        numero = rand() % 7;        
        if (!vacia(&pilas[numero])){
        	nodo = Pop(&pilas[numero]);
			Push(pila,nodo->frente,nodo->atras,nodo->mula );                         
			//printf("\n meti %i Ficha= %i,%i %i",x,nodo->frente,nodo->atras,nodo->mula );                       
			x++;
        }else{
        	//printf("\n no meti %i" ,numero);
		}
    }
    pilas[0] = NULL;
    pilas[1] = NULL;
    pilas[2] = NULL;
    pilas[3] = NULL;
    pilas[4] = NULL;
    pilas[5] = NULL;
}
 
 
 int vacia(Pila *pila) {
   pNodo nodo; /* variable auxiliar para manipular nodo */      
   /* Nodo apunta al primer elemento de la pila */
   nodo = *pila;
   if(!nodo) {   	
   		return 1; /* Si no hay nodos en la pila retornamos 0 */
	}else {		
		return 0;
	}   
}


void repartir( Pila *pila,Lista *lista,Lista *lista2){
	pNodo nodo; /* variable auxiliar para manipular nodo */      	
    printf("\n PILAS FINAL");
    int x,y;
    char c;       
	char *aux; 	
    for (x=0; x<2; x++) {
        printf("\n Jugador %i ",x);
        for (y=0; y<7; y++) {
        	nodo = Pop(pila);             
            printf("\n Ficha= %i,%i",nodo->frente,nodo->atras,nodo->mula);
			if(x==0){
				if(y==0){
					InsercionEnListaVacia(lista,nodo->atras,nodo->mula);
					InsercionFinLista(lista,lista->fin,nodo->frente,nodo->mula);
				}else{
					InsercionFinLista(lista,lista->fin,nodo->atras,nodo->mula);
					InsercionFinLista(lista,lista->fin,nodo->frente,nodo->mula);
				}
				
			}  else{
				if(y==0){
					InsercionEnListaVacia(lista2,nodo->atras,nodo->mula);
					InsercionFinLista(lista2,lista2->fin,nodo->frente,nodo->mula);
				}else{
					InsercionFinLista(lista2,lista2->fin,nodo->atras,nodo->mula);
					InsercionFinLista(lista2,lista2->fin,nodo->frente,nodo->mula);
				}
			}
			         
        }
    }
}

int busqueda_mula(Lista *lista){	
    Elemento *actual;
    actual = lista->inicio;    
    int x=-1;
    while(actual != NULL){    	
    		if(actual->mula){ 					    	    			
    			if(actual->dato>x){
    				printf("%i",actual->dato);			
    				x=actual->dato;							
				}    							
			}						
        actual = actual->siguiente;
    }
    return x;
}


