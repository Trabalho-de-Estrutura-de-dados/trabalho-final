// C program for Sparse Matrix Representation
// using Linked Lists
#include <stdio.h>
#include <stdlib.h>
#include "nodo.c"

typedef struct Matrizes
{
    struct Node **array;
    int **msizes;
    int used;
    int size;
} Matrizes;

void r_w_lista(struct Node **inicio, int mx, Matrizes *p)
{
    int matriz_linhas;
    int matriz_colunas;
    int value;
    printf("%s%d%s", "insira numero de linhas da matriz M", mx, ": \n");
    scanf("%d", &matriz_linhas);
    printf("%s%d%s", "insira numero de colunas da matriz M", mx, ": \n");
    scanf("%d", &matriz_colunas);
    int size[2] = {matriz_linhas, matriz_colunas};
    p->msizes[mx] = size;
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
    p->msizes = malloc(numero * sizeof(int[2]));
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

void soma_matriz(Matrizes *p, int id1, int id2)
{
    struct Node *A = p->array[id1];
    struct Node *B = p->array[id2];
    struct Node *C = NULL;
    // int size = p->msizes[id1][0];

    if ((p->msizes[id1][0] != p->msizes[id2][0]) && (p->msizes[id1][1] != p->msizes[id2][1]))
    {
        printf("Não pode somar matrizes de ordens diferentes");
    }
    else if ((p->msizes[id2][0] != p->msizes[id2][1]) && (p->msizes[id1][0] != p->msizes[id1][1]))
    {
        printf("Não pode somar matrizes não quadradas");
    }
    else
    {
        while (A->next != NULL || B->next != NULL)
        {
            if ((A->column_postion == B->column_postion) && (A->row_position == B->row_position))
            {
                cria_nodo(&C, (A->value + B->value), A->row_position, A->column_postion);

                A = A->next;

                B = B->next;
            }
            else
            {
                if (A->row_position > B->row_position)
                {
                    cria_nodo(&C, B->value, B->row_position, B->column_postion);

                    B = B->next;
                }
                else if (B->row_position > A->row_position)
                {
                    cria_nodo(&C, A->value, A->row_position, A->column_postion);

                    A = A->next;
                }
                else if (B->row_position == A->row_position)
                {
                    if (A->column_postion > B->column_postion)
                    {
                        cria_nodo(&C, B->value, B->row_position, B->column_postion);

                        B = B->next;
                    }
                    else if (B->column_postion > A->column_postion)
                    {
                        cria_nodo(&C, A->value, A->row_position, A->column_postion);

                        A = A->next;
                    }
                }
            }
        }
    }
    PrintList(C);
}

// void soma_matriz(struct Node **inicio1, struct Node **inicio2)
// {
//     struct Node *atual1 = *inicio1;
//     struct Node *atual2 = *inicio2;

//     while (inicio1 != NULL)
//     {
//         while (inicio2 != NULL)
//         {

//             atual2 = atual2->next;
//         }
//         atual1 = atual1->next;
//     }
// }

int main()
{

    struct Matrizes all;
    cria_matrizes(&all);
    soma_matriz(&all, 0, 1);
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
