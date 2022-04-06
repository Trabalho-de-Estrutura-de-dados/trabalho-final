#include <stdio.h>
#include <stdlib.h>
#include "NodeFunctions/nodeFunctions.h"
#include "MatrixFunctions/matrixDeclaration.h"
#include "MatrixFunctions/matrixOperations.h"

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
        printf("ESCOLHA UMA OPERAÇÃO \n1-SOMA \n2-SUBTRAÇÃO\n3-MULTIPLICAÇÃO\n");
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
            printf("INSIRA A MATRIZ PARA FAZER OPERAÇÃO COM O RESULTADO\n");
            read_write_list(&Mlist);
        }
    }
}