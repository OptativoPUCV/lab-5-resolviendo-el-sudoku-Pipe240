#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node *n){
    // 1) Filas
    for(int i = 0; i < 9; i++){
        int visto[10] = {0};
        for(int j = 0; j < 9; j++){
            int v = n->sudo[i][j];
            if(v == 0) continue;        // ignorar casillas vacías
            if(v < 1 || v > 9) return 0; // valor fuera de rango
            if(visto[v]) return 0;       // repetido en la fila
            visto[v] = 1;
        }
    }

    // 2) Columnas
    for(int j = 0; j < 9; j++){
        int visto[10] = {0};
        for(int i = 0; i < 9; i++){
            int v = n->sudo[i][j];
            if(v == 0) continue;
            if(v < 1 || v > 9) return 0;
            if(visto[v]) return 0;       // repetido en la columna
            visto[v] = 1;
        }
    }

    // 3) Submatrices 3x3
    for(int br = 0; br < 3; br++){
        for(int bc = 0; bc < 3; bc++){
            int visto[10] = {0};
            // recorre los 9 elementos de la submatriz con el truco p->(i,j)
            for(int p = 0; p < 9; p++){
                int i = 3*br + (p/3);
                int j = 3*bc + (p%3);
                int v = n->sudo[i][j];
                if(v == 0) continue;
                if(v < 1 || v > 9) return 0;
                if(visto[v]) return 0;   // repetido en el 3x3
                visto[v] = 1;
            }
        }
    }

    return 1; 
}



List* get_adj_nodes(Node* n){
    List* list = createList();

    // 1) Buscar la primera casilla vacia
    int row = -1, col = -1;
    for(int i = 0; i < 9 && row == -1; i++){
        for(int j = 0; j < 9; j++){
            if(n->sudo[i][j] == 0){
                row = i; col = j;
                break;
            }
        }
    }

    // Si no hay vacias no hay adjacentes
    if(row == -1) return list;

    // 2) Generar 9 hijos: copiar el nodo y asignar 1..9 en (row,col)
    for(int val = 1; val <= 9; val++){
        Node* child = copy(n);              
        child->sudo[row][col] = val;
        
        pushBack(list, child);  
    }

    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/