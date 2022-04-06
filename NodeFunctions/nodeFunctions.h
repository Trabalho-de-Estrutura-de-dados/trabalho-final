// Declaracao de Funcoes relacionadas a Lista Encadeada que representa uma Matriz Esparsa
#ifndef sparseNode
#define sparseNode

//Inicio de uma Lista encadeada que representa uma Matriz Sparsa
typedef struct Node
{
    int value;
    int row_position;
    int column_postion;
    struct Node *next;
} Node;

Node * alocate_node();
void insert_start(Node **N, int value, int row, int col);
void create_node(Node **N, int value, int row, int col);
void free_list(Node **start);
void PrintList(Node *start);
int get_data(Node **start, int row, int col);

#endif