// C program for Sparse Matrix Representation
// using Linked Lists
#include <stdio.h>
#include <stdlib.h>

// Node to represent sparse matrix
struct Node
{
    int value;
    int row_position;
    int column_postion;
    struct Node *next;
} Nodo;

typedef struct Matrizes
{
    struct Node **array;
    int used;
    int size;
} Matrizes;

struct Node *aloca_nodo()
{

    struct Node *nodo;
    nodo = (struct Node *)malloc(sizeof(struct Node));
    if (!nodo)
    {
        printf("Problema de alocação");
        exit(0);
    }
    return nodo;
}

// Function to create new node
void cria_nodo(struct Node **start, int non_zero_element,
               int row_index, int column_index)
{
    struct Node *temp, *r;
    temp = *start;
    if (temp == NULL)
    {
        // Create new node dynamically
        temp = aloca_nodo();
        temp->value = non_zero_element;
        temp->row_position = row_index;
        temp->column_postion = column_index;
        temp->next = NULL;
        *start = temp;
    }
    else
    {
        while (temp->next != NULL)
            temp = temp->next;

        // Create new node dynamically
        r = aloca_nodo();
        r->value = non_zero_element;
        r->row_position = row_index;
        r->column_postion = column_index;
        r->next = NULL;
        temp->next = r;
    }
}
int busca_dado(struct Node **inicio, int linha, int coluna)
{
    struct Node *atual = *inicio;
    while (atual != NULL)
    {
        if (atual->row_position == linha && atual->column_postion == coluna)
        {
            return atual->value;
        }
        atual = atual->next;
    }
    return 0;
}

void libera_lista(struct Node **inicio)
{
    struct Node *atual = *inicio;
    struct Node *tmp;
    while (atual != NULL)
    {
        tmp = atual;
        atual = atual->next;
        free(tmp);
    }
    atual = NULL;
}

void soma_matriz(struct Node **inicio1, struct Node **inicio2)
{
    struct Node *atual1 = *inicio1;
    struct Node *atual2 = *inicio2;

    while (inicio1 != NULL)
    {
        while (inicio2 != NULL)
        {

            atual2 = atual2->next;
        }
        atual1 = atual1->next;
    }
}

// This function prints contents of linked list
// starting from start
void PrintList(struct Node *start)
{
    struct Node *temp, *r, *s;
    temp = r = s = start;

    printf("row_position: ");
    while (temp != NULL)
    {

        printf("%d ", temp->row_position);
        temp = temp->next;
    }
    printf("\n");

    printf("column_postion: ");
    while (r != NULL)
    {
        printf("%d ", r->column_postion);
        r = r->next;
    }
    printf("\n");
    printf("Value: ");
    while (s != NULL)
    {
        printf("%d ", s->value);
        s = s->next;
    }
    printf("\n");
}

void r_w_lista(struct Node **inicio)
{
    int matriz_linhas = 2;
    int matriz_colunas = 2;
    int value = 1;
    // printf("insira numero de linhas da matriz: \n");
    // scanf("%d", &matriz_linhas);
    // printf("insira numero de colunas da matriz: \n");
    // scanf("%d", &matriz_colunas);

    int matriz[matriz_linhas][matriz_colunas];

    for (int i = 0; i < matriz_linhas; i++)
    {
        for (int j = 0; j < matriz_colunas; j++)
        {
            // printf("insira o valor para");
            // printf("%s%d%s", "[", i, "]");
            // printf("%s%d%s", "[", j, "]");
            // scanf("%d", &value);

            if (value != 0)
            {
                cria_nodo(inicio, value, i, j);
            }
        }
    }
}

void cria_matrizes(Matrizes *p)
{
    int numero = 2;

    printf("insira numero de de matrizes: \n");
    scanf("%d", &numero);
    p->array = malloc(numero * sizeof(struct Node *));
    p->used = 0;
    p->size = numero;
    for (int i = 0; i < numero; i++)
    {
        struct Node *nodo = NULL;
        p->array[p->used++] = nodo;
        r_w_lista(&nodo);
        PrintList(nodo);
    }
    
}

int main()
{

    struct Matrizes all;
    cria_matrizes(&all);
    // // Assume 4x5 sparse matrix
    // int sparseMatric[4][5] =
    //     {
    //         {0, 0, 3, 0, 4},
    //         {0, 0, 5, 7, 0},
    //         {0, 0, 0, 0, 0},
    //         {0, 2, 6, 0, 0}};

    /* Start with the empty list */
    // struct Node *start = NULL;

    // for (int i = 0; i < 4; i++){
    //     for (int j = 0; j < 5; j++)

    //         // Pass only those values which are non - zero
    //         if (sparseMatric[i][j] != 0)
    //             cria_nodo(&start, sparseMatric[i][j], i, j);

    // }

    return 0;
}
