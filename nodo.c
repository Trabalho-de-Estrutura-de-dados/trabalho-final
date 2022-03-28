// Node to represent sparse matrix
struct Node
{
    int value;
    int row_position;
    int column_postion;
    struct Node *next;
} Nodo;

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
// This function prints contents of linked list
// starting from start
void PrintList(struct Node *start)
{
    struct Node *temp, *r, *s;
    temp = r = s = start;

    printf("row_position: \t");
    while (temp != NULL)
    {

        printf("%d ", temp->row_position);
        temp = temp->next;
    }
    printf("\n");

    printf("column_postion:\t ");
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