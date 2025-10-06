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
    // filas
    for(int i = 0; i < 9; i++){
        int visto[10] = {0};
        for(int j = 0; j < 9; j++){
            int v = n->sudo[i][j];
            if(v == 0) continue;          // vacias
            if(v < 1 || v > 9) return 0;  // fuera de rango
            if(visto[v]) return 0;        // repetido en la fila
            visto[v] = 1;
        }
    }
    // columnas
    for(int j = 0; j < 9; j++){
        int visto[10] = {0};
        for(int i = 0; i < 9; i++){
            int v = n->sudo[i][j];
            if(v == 0) continue;
            if(v < 1 || v > 9) return 0;
            if(visto[v]) return 0;        // repetido en la columna
            visto[v] = 1;
        }
    }
    // subcuadriculas 3x3
    for(int br = 0; br < 3; br++){
        for(int bc = 0; bc < 3; bc++){
            int visto[10] = {0};
            for(int p = 0; p < 9; p++){
                int i = 3*br + (p/3);
                int j = 3*bc + (p%3);
                int v = n->sudo[i][j];
                if(v == 0) continue;
                if(v < 1 || v > 9) return 0;
                if(visto[v]) return 0;    // repetido en el 3×3
                visto[v] = 1;
            }
        }
    }
    return 1;
}




List* get_adj_nodes(Node* n){
    List* list = createList();

    // encontrar la primera casilla vacia
    int row = -1, col = -1;
    for (int i = 0; i < 9 && row == -1; i++){
        for (int j = 0; j < 9; j++){
            if (n->sudo[i][j] == 0){
                row = i; col = j;
                break;
            }
        }
    }
    // Si no hay vacia no hay adjacente
    if (row == -1) return list;

    // intentar con valores del 1 al 9
    for (int val = 1; val <= 9; val++){
        Node* child = copy(n);
        child->sudo[row][col] = val;

        if (is_valid(child)){
            
            pushBack(list, child);
        } else {
            free(child); // evitar problemas de memoria
        }
    }
    return list;
}


int is_final(Node *n){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(n->sudo[i][j] == 0) return 0;  // si hay ceros no es final
        }
    }
    return 1; // no hay ceros -> tablero completo
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