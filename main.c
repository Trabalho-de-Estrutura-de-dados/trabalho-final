// C program for Sparse Matrix Representation
// using Linked Lists
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//--------------------------------------------------------------typedefs--------------------------------------------------------------------------------------------------------
typedef struct Matrizes
{
    struct Node **array;
    int used;
    int size;
} Matrizes;

// Node to represent sparse matrix
struct Node
{
    int value;
    int row_position;
    int column_postion;
    struct Node *next;
} Nodo;
//--------------------------------------------------------------Nodo functions--------------------------------------------------------------------------------------------------

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
void insert_start(struct Node **N, int non_zero_element,
                  int row_index, int column_index)
{
    struct Node *novo;
    novo = (struct Node *)malloc(sizeof(node));

    if (*N == NULL)
    {
        novo->value = non_zero_element;
        novo->column_postion = column_index;
        novo->row_position = row_index;
        novo->prox = NULL;
        *N = novo;
    }
    else
    {
        novo->value = non_zero_element;
        novo->column_postion = column_index;
        novo->row_position = row_index;
        novo->prox = *N;
        *N = novo;
    }
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
// This function prints contents of linked list
// starting from start
void PrintList(struct Node *start)
{
    struct Node *temp, *r, *s;
    temp = r = s = start;
    int nowRow = temp->row_position;
    printf("\n-----------------------------\n");
    while (temp)
    {
        if (temp->row_position != nowRow)
        {
            printf("\n");
        }
        printf("%d%s", temp->value, " ");

        nowRow = temp->row_position;
        temp = temp->next;
    }
    printf("\n-----------------------------\n");
    printf("\n");
    // printf("row_position: \t");
    // while (temp != NULL)
    // {

    //     printf("%d ", temp->row_position);
    //     temp = temp->next;
    // }
    // printf("\n");

    // printf("column_postion:\t ");
    // while (r != NULL)
    // {
    //     printf("%d ", r->column_postion);
    //     r = r->next;
    // }
    // printf("\n");
    // printf("Value: ");
    // while (s != NULL)
    // {
    //     printf("%d ", s->value);
    //     s = s->next;
    // }
    // printf("\n");
}

//--------------------------------------------------------------Matriz Array Declare---------------------------------------------------------------------------------------------
void r_w_lista(struct Node **inicio, int mx, Matrizes *p)
{
    int matriz_linhas;
    int matriz_colunas;
    int value;
    printf("%s%d%s", "insira numero de linhas da matriz M", mx, ": \n");
    scanf("%d", &matriz_linhas);
    printf("%s%d%s", "insira numero de colunas da matriz M", mx, ": \n");
    scanf("%d", &matriz_colunas);
    for (int i = 0; i < matriz_linhas; i++)
    {
        for (int j = 0; j < matriz_colunas; j++)
        {
            printf("%s%d", "insira o valor para M", mx);
            printf("%s%d%s", "[", i, "]");
            printf("%s%d%s", "[", j, "]");
            scanf("%d", &value);

            if (value != 0)
            {
                cria_nodo(inicio, value, i, j);
            }
        }
    }
}

void cria_matrizes(Matrizes *p)
{
    int numero;

    printf("insira numero de de matrizes: \n");
    scanf("%d", &numero);
    p->array = malloc(numero * sizeof(struct Node *));
    p->used = 0;
    p->size = numero;
    for (int i = 0; i < numero; i++)
    {
        struct Node *nodo = NULL;
        p->array[i] = nodo;
        p->used++;
        r_w_lista(&(p->array[i]), i, p);
        PrintList((p->array[i]));
    }
}
//-------------------------------------------------------------------------utils (funções auxiliares)---------------------------------------------------------------------------
// op == 1 ? soma matriizes : subtrai matrizes
struct Node *soma_subtrai(struct Node *A, struct Node *B, bool op)
{

    int value;
    struct Node *C = NULL;
    while (A && B)
    {

        if (A->row_position == B->row_position)
        {
            if (A->column_postion == B->column_postion)
            {
                op == 1 ? (value = (A->value + B->value)) : (value = (A->value - (B->value)));
                cria_nodo(&C, value, A->row_position, A->column_postion);
                A = A->next;
                B = B->next;
            }
            else if (A->column_postion < B->column_postion)
            {
                cria_nodo(&C, A->value, A->row_position, A->column_postion);
                A = A->next;
            }
            else
            {
                op == 1 ? (value = B->value) : (value = -(B->value));
                cria_nodo(&C, value, B->row_position, B->column_postion);
                B = B->next;
            }
        }
        else
        {
            if (A->row_position < B->row_position)
            {

                cria_nodo(&C, A->value, A->row_position, A->column_postion);
                A = A->next;
            }
            else
            {
                op == 1 ? (value = B->value) : (value = -(B->value));
                cria_nodo(&C, value, B->row_position, B->column_postion);
                B = B->next;
            }
        }
    }
    while (A != NULL)
    {
        cria_nodo(&C, A->value, A->row_position, A->column_postion);
        A = A->next;
    }
    while (B != NULL)
    {
        op == 1 ? (value = B->value) : (value = -(B->value));
        cria_nodo(&C, value, B->row_position, B->column_postion);
        B = B->next;
    }
    return C;
}
//--------------------------------------------------------------------------Matriz Operations---------------------------------------------------------------------------------

void soma_matriz(Matrizes *p, int id1, int id2)
{
    struct Node *A = p->array[id1];
    struct Node *B = p->array[id2];
    struct Node *C = soma_subtrai(A, B, true); // op == 1 ? soma matriizes : subtrai matrizes

    PrintList(C);
}

void subtrai_matriz(Matrizes *p, int id1, int id2)
{
    struct Node *A = p->array[id1];
    struct Node *B = p->array[id2];
    struct Node *C = soma_subtrai(A, B, false); // op == 1 ? soma matriizes : subtrai matrizes

    PrintList(C);
}

void multiplica_matriz(Matrizes *p, int id1, int id2)
{
    struct Node *A = p->array[id1];
    struct Node *B = p->array[id2];
    struct Node *C = NULL;
    while (A && B)
    {
        if (A->row_position == B->row_position)
        {
            if (A->column_postion == B->column_postion)
            {
                cria_nodo(&C, (A->value * B->value), A->row_position, A->column_postion);
                A = A->next;
                B = B->next;
            }
            else if (A->column_postion < B->column_postion)
                A = A->next;
            else
                B = B->next;
        }
        else
        {
            if ((A->row_position < B->row_position))
                A = A->next;
            else
                B = B->next;
        }
    }
    PrintList(C);
}

void transpor_matriz(Matrizes *p, int id1)
{
    struct Node *A = p->array[id1];
    struct Node *aux;
    struct Node *prev;
    struct Node *At = NULL;
    int buffer;
    while (A)
    {
        if (At == NULL)
        {
            cria_nodo(&At, A->value, A->column_postion, A->row_position);
        }
        else
        {
            now = At;
            post = At->next;
            if (aux == NULL)
            {
                if (now->column_postion > A->column_postion)
                {
                    insert_start(&At, A->value, A->column_postion, A->row_position);
                }
                else
                {
                    (&At, A->value, A->column_postion, A->row_position);
                }
            }
        }

        A = A->next;
    }
    while (At)
    {
        prev
            aux = At->next;
        if (At->column_postion > aux->column_postion)
        {
        }
    }

    PrintList(At);
}

//------------------------------------------------------------------------------------main------------------------------------------------------------------------------------
int main()
{

    struct Matrizes all;
    cria_matrizes(&all);
    transpor_matriz(&all, 0);
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
