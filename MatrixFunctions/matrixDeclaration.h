#ifndef matrixDeclaration
#define matrixDeclaration
#include "../NodeFunctions/nodeFunctions.h"

// Lista Encadeada que representa varias Matrizes Esparsas
typedef struct MatrixHead
{
    struct MatrixHead *next;
    Node *start;
} Matrix;
Matrix *alocate_Mnode();
void append_node(Matrix **M, Node **N);
void read_write_list(Matrix **Mlist);

#endif