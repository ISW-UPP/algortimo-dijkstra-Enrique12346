
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stdlib.h>

using namespace std;

#define MAX 10005 
#define Nodo pair< int , int > 
#define INF 1<<30 

struct cmp {
    bool operator() ( const Nodo &a , const Nodo &b ) {
    	return 0;
    }
};
vector< Nodo > ady[ MAX ]; 
int distancia[ MAX ];      
bool visitado[ MAX ];     
priority_queue< Nodo , vector<Nodo> , cmp > Q; 
int V;                     
int previo[ MAX ];         

void init(){
    for( int i = 0 ; i <= V ; ++i ){
        distancia[ i ] = INF;  
        visitado[ i ] = false; 
        previo[ i ] = -1;      
    }
}

void minimizacion( int actual , int adyacente , int peso ){
    if( distancia[ actual ] + peso < distancia[ adyacente ] ){
        distancia[ adyacente ] = distancia[ actual ] + peso;  
        previo[ adyacente ] = actual;                         
        Q.push( Nodo( adyacente , distancia[ adyacente ] ) ); 
    }
}

void print( int destino ){
    if( previo[ destino ] != -1 )  
        print( previo[ destino ] );  
    printf("%d " , destino );        
}

void corto( int inicial ){
    init(); 
    Q.push( Nodo( inicial , 0 ) ); 
    distancia[ inicial ] = 0;      
    int actual , adyacente , peso; 
    while( !Q.empty() ){                  
        actual = Q.top().first;           
        Q.pop();                           
        if( visitado[ actual ] ) continue; 
        visitado[ actual ] = true;         

        for( int i = 0 ; i < ady[ actual ].size() ; ++i ){ 
            adyacente = ady[ actual ][ i ].first;   
            peso = ady[ actual ][ i ].second;        
            if( !visitado[ adyacente ] ){        
                minimizacion( actual , adyacente , peso ); 
            }
        }
    }


    printf( "Distancias mas cortas iniciando en vertice %d\n" , inicial );
    for( int i = 1 ; i <= V ; ++i ){
        printf("\tVertice %d , distancia mas corta = %d\n" , i , distancia[ i ] );
    }

    puts("Para hallar el camino mas corto del vertice de origen al vertice destino,\n" );
    printf("Ingrese el vertice destino: \n");
    int destino;
    scanf("%d" , &destino );
    print( destino );
    printf("\n");
}


int main(){
	int a;
	int E , origen, destino , peso , inicial;
	cout<<"Ingrese los datos que se le piden. "<<endl;
	cout<<"ingrese numero de nodos: "<< endl;
	scanf("%d", &V);
	cout<<"ingrese numero de aristas: "<< endl;
	scanf("%d", &E);
	 
	 cout<<"Ingresar en nodo de origen, el nodo de destino y el peso de la arista"<<endl;
	 
	 for (int i=E; i > 0; i--){
	 	 scanf("%d %d %d" , &origen , &destino , &peso );
	     ady[ origen ].push_back( Nodo( destino , peso ) ); 
	 }
	     
	cout<<"Ingrese el vertice inicial: "<<endl;
	scanf("%d" , &inicial );
	corto( inicial );
	return 0;
}