#include "matrixOperations.h"
#include <stdio.h>
#include <stdlib.h>
#include "../NodeFunctions/nodeFunctions.h"

Node *sum_sub(Node *A, Node *B, int op)
{

    int value;
    Node *C = NULL;
    while (A && B)
    {

        if (A->row_position == B->row_position)
        {
            if (A->column_postion == B->column_postion)
            {
                op == 1 ? (value = (A->value + B->value)) : (value = (A->value - (B->value)));
                create_node(&C, value, A->row_position, A->column_postion);
                A = A->next;
                B = B->next;
            }
            else if (A->column_postion < B->column_postion)
            {
                create_node(&C, A->value, A->row_position, A->column_postion);
                A = A->next;
            }
            else
            {
                op == 1 ? (value = B->value) : (value = -(B->value));
                create_node(&C, value, B->row_position, B->column_postion);
                B = B->next;
            }
        }
        else
        {
            if (A->row_position < B->row_position)
            {

                create_node(&C, A->value, A->row_position, A->column_postion);
                A = A->next;
            }
            else
            {
                op == 1 ? (value = B->value) : (value = -(B->value));
                create_node(&C, value, B->row_position, B->column_postion);
                B = B->next;
            }
        }
    }
    while (A != NULL)
    {
        create_node(&C, A->value, A->row_position, A->column_postion);
        A = A->next;
    }
    while (B != NULL)
    {
        op == 1 ? (value = B->value) : (value = -(B->value));
        create_node(&C, value, B->row_position, B->column_postion);
        B = B->next;
    }
    return C;
}

Node *sum_matrix(Node *MA, Node *MB)
{

    Node *C = sum_sub(MA, MB, 1); // op == 1 ? soma matriizes : subtrai matrizes
    return C;
}
Node *sub_matrix(Node *MA, Node *MB)
{

    Node *C = sum_sub(MA, MB, 2); // op == 1 ? soma matriizes : subtrai matrizes
    return C;
}

Node *mult_matrix(Node *A, Node *B)
{
    Node *C = NULL;
    while (A && B)
    {
        if (A->row_position == B->row_position)
        {
            if (A->column_postion == B->column_postion)
            {
                create_node(&C, (A->value * B->value), A->row_position, A->column_postion);
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
    return C;
}

Node *transpose_matrix(Node *A)
{
    Node *aux = NULL;
    Node *tmp, *next, *prev;
    Node *At = NULL;
    while (A)
    {
        create_node(&At, A->value, A->column_postion, A->row_position);
        A = A->next;
    }
    return At;
}