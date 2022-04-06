#include <stdio.h>
#include <stdlib.h>
#include "matrixDeclaration.h"
#include "../NodeFunctions/nodeFunctions.h"

Matrix *alocate_Mnode()
{
    Matrix *node;
    node = (Matrix *)malloc(sizeof(Matrix));
    if (!node)
    {
        printf("Problema de alocação");
        exit(0);
    }
    return node;
}

void append_node(Matrix **M, Node **N)
{
    Matrix *temp, *r;
    temp = *M;
    if (temp == NULL)
    {
        temp = alocate_Mnode();
        temp->start = *N;
        temp->next = NULL;
        *M = temp;
    }
    else
    {
        while (temp->next != NULL)
            temp = temp->next;

        r = alocate_Mnode();
        r->start = *N;
        r->next = NULL;
        temp->next = r;
    }
}

void read_write_list(Matrix **Mlist)
{
    struct Node *start = NULL;
    int matrix_rows;
    int matrix_columns;
    int value;
    printf("insira numero de linhas da matriz M: \n");
    scanf("%d", &matrix_rows);
    printf("insira numero de colunas da matriz M: \n");
    scanf("%d", &matrix_columns);
    for (int i = 0; i < matrix_rows; i++)
    {
        for (int j = 0; j < matrix_columns; j++)
        {
            printf("insira o valor para M");
            printf("%s%d%s", "[", i, "]");
            printf("%s%d%s", "[", j, "]\n");
            scanf("%d", &value);

            if (value != 0)
            {
                create_node(&start, value, i, j);
            }
        }
    }
    append_node(Mlist, &start);
}