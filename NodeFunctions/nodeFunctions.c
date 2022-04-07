#include <stdio.h>
#include <stdlib.h>
#include "nodeFunctions.h"

Node *alocate_node()
{
    Node *node;
    node = (Node *)malloc(sizeof(Node));
    if (!node)
    {
        printf("Problema de alocação");
        exit(0);
    }
    return node;
}

void insert_start(Node **N, int value, int row, int col)
{
    Node *new;
    new = alocate_node();

    if (*N == NULL)
    {
        new->value = value;
        new->row_position = row;
        new->column_postion = col;
        new->next = NULL;
        *N = new;
    }
    else
    {
        new->value = value;
        new->row_position = row;
        new->column_postion = col;
        new->next = *N;
        *N = new;
    }
}

void create_node(Node **N, int value, int row, int col)
{
    Node *temp = *N;
    Node *aux;
    if (*N == NULL)
    {
        temp = alocate_node();
        temp->value = value;
        temp->row_position = row;
        temp->column_postion = col;
        temp->next = NULL;
        *N = temp;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        aux = alocate_node();
        aux->value = value;
        aux->row_position = row;
        aux->column_postion = col;
        aux->next = NULL;
        temp->next = aux;
    }
}

void free_list(Node **start)
{
    Node *now = *start;
    Node *tmp;
    while (now != NULL)
    {
        tmp = now;
        now = now->next;
        free(tmp);
    }
    now = NULL;
}

void sortedInsert(Node **head_ref,
                  Node *new_node)
{
    Node *current;
    /* Special case for the head end */
    if (*head_ref == NULL || (*head_ref)->row_position >= new_node->row_position )
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        /* Locate the node before
the point of insertion */
        current = *head_ref;
        while (current->next != NULL && current->next->row_position < new_node->row_position)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void PrintList(Node *start)
{

    Node *tmp = start;
    int nowRow = tmp->row_position;
    int cc = 0;
    int cr = 0;
    printf("\n-----------------------------\n");
    while (tmp)
    {
        printf("%s%d%s%s%d%s%d%s", "[", tmp->row_position, "]", "[", tmp->column_postion, "]", tmp->value, "  ");
        tmp = tmp->next;
    }
}

// void PrintList(Node *start)
// {
//     Node *temp, *r, *s, *aux;
//     temp = start;
//     int nowRow = temp->row_position;
//     int counter = 0;

//     printf("\n-----------------------------\n");
//     while (temp)
//     {
//         if (temp->row_position != nowRow)
//         {
//             counter = 0;
//             printf("\n");
//         }
//         if (temp->column_postion != counter)
//         {
//             printf("0  ");
//         }
//         else
//         {
//             printf("%d%s", temp->value, "  ");
//         }
//         nowRow = temp->row_position;
//         temp = temp->next;
//         counter ++;
//     }
//     printf("\n-----------------------------\n");
//     printf("\n");
// }

int get_data(Node **start, int row, int col)
{
    Node *now = *start;
    while (now != NULL)
    {
        if (now->row_position == row && now->column_postion == col)
        {
            return now->value;
        }
        now = now->next;
    }
    return 0;
}