#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    int row_position;
    int column_postion;
    struct Node *next;
} Node;

typedef struct MatrixHead
{
    struct MatrixHead *next;
    Node *start;
} Matrix;

//----------------------------------------------------NODE FUNCRTIONS------------------------------------------------------
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
    if (*head_ref == NULL || (*head_ref)->row_position >= new_node->row_position)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        /* Locate the node before
the point of insertion */
        current = *head_ref;
        while (current->next != NULL && (current->next->row_position + current->next->column_postion * 10) < (new_node->row_position + new_node->column_postion * 10))
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
    while (tmp)
    {
        printf("%s%d%s%s%d%s%d%s", "[", tmp->row_position, "]", "[", tmp->column_postion, "]", tmp->value, "  ");
        tmp = tmp->next;
    }
}

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
//------------------------------------------------------Matrix Declarations------------------------------------------------------------------

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
//----------------------------------------------Matrix Operations------------------------------------------------------------------------

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
    Node *tmp;
    Node *At = NULL;
    while (A)
    {
        tmp->value = A->value;
        tmp->row_position = A->column_postion;
        tmp->column_postion = A->row_position;
        sortedInsert(&At, tmp);
        A = A->next;
    }
    return At;
}
//---------------------------------------------------------------------------------------------------------------------------------------

int main()
{
    Matrix *Mlist = NULL;
    int op, isMenu;
    isMenu = 1;
    printf("INSIRA A PRIMEIRA MATRIZ \n");
    read_write_list(&Mlist);
    printf("INSIRA A SEGUNDA MATRIZ \n");
    read_write_list(&Mlist);

    while (isMenu == 1)
    {
        printf("ESCOLHA UMA OPERAÇÃO \n1-SOMA \n2-SUBTRAÇÃO\n3-MULTIPLICAÇÃO\n>>");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            Mlist->start = sum_matrix(Mlist->start, Mlist->next->start);
            Mlist->next = NULL;
            break;
        case 2:
            Mlist->start = sub_matrix(Mlist->start, Mlist->next->start);
            Mlist->next = NULL;
            break;
        case 3:
            Mlist->start = mult_matrix(Mlist->start, Mlist->next->start);
            Mlist->next = NULL;
            break;
        default:
            printf("VOCÊ ESCOLHEU SAIR, BYE BYE");
            isMenu = 0;
            break;
        }
        if (isMenu == 1)
        {
            printf("RESULTADO\n");
            PrintList(Mlist->start);
            printf("\nINSIRA A MATRIZ PARA FAZER OPERAÇÃO COM O RESULTADO\n");
            read_write_list(&Mlist);
        }
    }
}