#include <stdio.h>
#include <stdlib.h>

int Iselecao = 0;
int Qselecao = 0;
int Selecionar;
int Finalizar = 0;
const int ItemS = 30;

int quant_itens()
{
    FILE* Estoque;//Aponta a localização de um registro 
    Estoque = fopen("Estoque.txt", "r"); //Leitura do arquivo txt
    char line[40];
    int c = 0;

    while (feof(Estoque) == 0)//Leitura dos caracteres do Estoque
    {
        fscanf(Estoque,"%s", line);//Lê o arquivo
        c += 1;
    }
    fclose(Estoque);
    return c / 2;
}

void carregar(char** item, int* quantidade, int quant)
{
    FILE* Estoque;
    Estoque = fopen("Estoque.txt", "r");//Carrega os arquivos do txt nas variáveis

    for (int i = 0; i < quant; i++)
    {
        fscanf(Estoque, "%s", item[i]);
        fscanf(Estoque, "%d", &quantidade[i]);
    }
   fclose(Estoque);
}

void SalvarAuto(char** item, int* quantidade, int quant)
{
    FILE* Estoque;
    Estoque = fopen("Estoque.txt", "w");//Arquiva os valores do txt nas variáveis

    for (int i = 0; i < quant; i++)
    {
        fprintf(Estoque, "%s\n", item[i]);
        fprintf(Estoque, "%d\n", quantidade[i]);
    }
    fclose(Estoque);
}

void imprimir(char** item, int* quantidade, int quant)
{
    printf("--------------------------------------------------\n\n");//Imprime os valores das variáveis na tela
    printf("%-30s%-20s\n", "Nome", "Quantidade");
    for (int i = 0; i < quant; i++)
    {
        printf("%-30s%-20d\n", item[i], quantidade[i]);
    }
    printf("\n--------------------------------------------------\n\n");
}

void lista_itens(char** item, int quant)
{
    //For para puxar lista de itens;
    for (int i = 0; i < quant; i++)
    {
        printf("%d - %s\n", i + 1, item[i]);
    }
}

int main()
 {
    int quant = quant_itens();
    char** item;
    int* quantidade;
    item = (char**)malloc(quant * sizeof(char*));

    for (int i = 0; i < quant; i++)
    {
        item[i] = (char*)malloc(ItemS * sizeof(char));
    }
    quantidade = (int*)malloc(quant * sizeof(int));
    carregar(item, quantidade, quant);
    printf("Gestao de Estoque\n\n");
    printf("\n--------------------------------------------------\n\n");
    while (1)
    {
        printf("Selecione uma operacao\n");
        printf("0 - Sair\n");
        printf("1 - Lista dos itens\n");
        printf("2 - Remover itens\n");
        printf("3 - Adicionar itens\n");
        printf("\n--------------------------------------------------\n\n");
        scanf("%d", &Selecionar);

        switch(Selecionar)
        {
        case 0:
            printf("\nFinalizado\n");
            Finalizar = 1;
            break;
        case 1:
            imprimir(item, quantidade, quant);
            break;
        case 2:
            printf("\n--------------------------------------------------\n\n");
            printf("Qual item voce gostaria de remover?\n");
            lista_itens(item, quant);
            scanf("%d", &Iselecao);
            printf("Quantos itens voce quer remover?\n");
            scanf("%d", &Qselecao);
            printf("\n--------------------------------------------------\n\n");
            quantidade[Iselecao - 1] -= Qselecao;
            SalvarAuto(item, quantidade, quant);
            break;
        case 3:
            printf("\n--------------------------------------------------\n\n");
            printf("Qual item voce gostaria de adicionar?\n");
            lista_itens(item, quant);
            scanf("%d", &Iselecao);
            printf("Quantos itens voce quer adicionar?\n");
            scanf("%d", &Qselecao);
            printf("\n--------------------------------------------------\n\n");
            quantidade[Iselecao - 1] += Qselecao;
            SalvarAuto(item, quantidade, quant);
            break;
        }
        if (Finalizar == 1)
        {
            break;
        }
    }
}