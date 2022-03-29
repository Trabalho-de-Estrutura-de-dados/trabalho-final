
#include <stdio.h>
#include <stdlib.h>
#include "nodo.c"



void subtrai_matriz(Matrizes *p, int id1, int id2)
{
    struct Node *A = p->array[id1];
    struct Node *B = p->array[id2];
    struct Node *C = NULL;
    int size = p->msizes[id1][0];

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
        while (A || B)
        {
            if ((A->column_postion == B->column_postion) && (A->row_position == B->row_position))
            {
                cria_nodo(&C, (A->value - B->value), A->row_position, A->column_postion);

                A = A->next;

                B = B->next;
            }
            else
            {
                if (A->row_position > B->row_position)
                {
                    cria_nodo(&C, -(B->value), B->row_position, B->column_postion);

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
                        cria_nodo(&C, -(B->value), B->row_position, B->column_postion);

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
