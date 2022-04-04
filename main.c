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
    novo = aloca_nodo();

    if (*N == NULL)
    {
        novo->value = non_zero_element;
        novo->column_postion = column_index;
        novo->row_position = row_index;
        novo->next = NULL;
        *N = novo;
    }
    else
    {
        novo->value = non_zero_element;
        novo->column_postion = column_index;
        novo->row_position = row_index;
        novo->next = *N;
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

// Insere matriz ordenada por linha e coluna
void insert_sequential(struct Node **N, int val, int row, int col)
{
    struct Node *novo, *this, *prev;
    novo = aloca_nodo();
    novo->value = val;
    novo->row_position = row;
    novo->column_postion = col;
    this = *N;
    if (*N == NULL)
    {
        printf("NULL POINTER, CREATING NODE\n");
        novo->next = NULL;
        *N = novo;
        printf("---------------------\n");
    }
    else
    {
        if (this->next == NULL)
        {
            if (this->row_position == row)
            {
                if (this->column_postion > col)
                {
                    novo->next = this;
                    *N = novo;
                }
                else
                {
                    this->next = novo;
                }
            }
            else
            {
                if (this->row_position > row)
                {
                    novo->next = this;
                    *N = novo;
                }
                else
                {
                    this->next = novo;
                }
            }
            return;
        }
        prev = this;

        while (prev)
        {
            this = prev->next;
            printf("LOOPING\n");
            while (this)
            {
                if (this->row_position == row)
                {

                    if (this->column_postion > col)
                    {
                        prev->next = novo;
                        novo->next = this;
                    }
                    else
                    {
                        prev->next = this;
                        novo->next = this->next;
                        this->next = novo;
                    }
                }
                else
                {
                    if (this->row_position > row)
                    {
                        prev->next = novo;
                        novo->next = this;
                    }
                    else
                    {
                        prev->next = this;
                        novo->next = this->next;
                        this->next = novo;
                    }
                }
                this = this->next;
            }
            prev = prev->next;
        }
        printf("-----------------\n");
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
    struct Node *temp, *r, *s, *aux;
    temp = r = s = start;
    int nowRow = temp->row_position;
    printf("\n-----------------------------\n");
    while (temp)
    {
        if (temp->row_position != nowRow)
        {
            printf("\n");
        }
        printf("%d%s", temp->value, "  ");

        nowRow = temp->row_position;
        temp = temp->next;
    }
    printf("\n-----------------------------\n");
    printf("\n");


}

//--------------------------------------------------------------Matriz Array Declare---------------------------------------------------------------------------------------------
void r_w_lista(struct Node **inicio, int mx)
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
        r_w_lista(&(p->array[i]), i);
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

void Print_All(struct Matrizes *p)
{
    int i = 0;
    while (p->array[i])
    {
        printf("%s%d", "Matriz No: ", i);
        PrintList(p->array[i]);
        i++;
    }
}

//--------------------------------------------------------------------------Matriz Operations---------------------------------------------------------------------------------

void soma_matriz(Matrizes *p, int id1, int id2)
{
    struct Node *A = p->array[id1];
    struct Node *B = p->array[id2];
    struct Node *C = soma_subtrai(A, B, true); // op == 1 ? soma matriizes : subtrai matrizes
    int i = 0;
    libera_lista(&A);
    libera_lista(&B);
    p->array[id1] = C;
    while (p->array[i])
    {
        if (i == id1 || i == id2)
        {
            i++;
            continue;
        }
        else
        {
            p->array[(i - 1)] == p->array[i];
            i++; 
        }
    }
    p->array[(i - 1)] = NULL;
}

void subtrai_matriz(Matrizes *p, int id1, int id2)
{
    struct Node *A = p->array[id1];
    struct Node *B = p->array[id2];
    struct Node *C = soma_subtrai(A, B, false); // op == 1 ? soma matriizes : subtrai matrizes

    PrintList(C);
}

struct Node *multiplica_matriz(Matrizes *p, int id1, int id2)
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
    return C;
}

void transpor_matriz(Matrizes *p, int id1)// NAO FUNCIONA
{
    struct Node *A = p->array[id1];
    struct Node *At = NULL;
    while (A)
    {
        cria_nodo(&At, A->value, A->column_postion, A->row_position);
        A = A->next;
    }

    PrintList(At);

}

//------------------------------------------------------------------------------------main------------------------------------------------------------------------------------
int main()
{

    struct Matrizes all;
    struct Matrizes *p = &all;
    struct Node *atual = NULL;
    int isMenu = 1;
    cria_matrizes(p);
    //MAIS DE 2 MATRIZES MENU NAO FUNCIONA
    while (isMenu == 1)
    {
        int op;
        int m1, m2;
        printf("Escolha uma operação \n1 - Soma \n2 - Subtração\n3 - Multiplicação\n");
        scanf("%d", &op);
        printf("Escolha duas das matrizes para realizar a operação\n");
        Print_All(p);
        printf("Matriz A: \n");
        scanf("%d", &m1);
        printf("Matriz B: \n");
        scanf("%d", &m2);
        switch (op)
        {
        case 1:
            soma_matriz(p, m1, m2);
            printf("RESULTADO\n");
            Print_All(p);
            break;
        case 2:
            subtrai_matriz(p, m1, m2);
            printf("RESULTADO\n");
            Print_All(p);
            break;
        case 3:
            multiplica_matriz(p, m1, m2);
            printf("RESULTADO\n");
            Print_All(p);
            break;

        default:
            isMenu = 0;
            break;
        }
    }



    return 0;
}
