// Autor: Katlen Vanessa
// Eletronica Digital
/*Faça uma codificação em uma linguagem a seu critério, que a partir da leitura de um
arquivo de texto contendo apenas a saída de uma tabela verdade gere a expressão
booleana. Deve-se considerar saídas da tabela verdade em potências de 2 conforme a
quantidade de variáveis, ou seja, 2, 4, 8, 16, 32...*/

#include <stdio.h>
#include <stdlib.h>

#define linhas 1024
#define colunas 9

void imprimeTabela(int entradas, int variaveis, int tabela[][colunas]);
void tabelaVerdade(int variaveis, int entradas, int saidas[], int tabela[][colunas], int *arq2);
void mintermos(int entradas, int saidas[], int tabela[][colunas], int variaveis, int *arq2);
void escreverExpressao(int *arq2, char letra, char teste);
void lerExpressao(int *arq2);
int potencia(int base, int expoente);
int descobreVariavel(int entradas);

int main(void)
{
    FILE *arq1, *arq2;
    char arquivoSaidas[20];
    int saidas[100];
    int tabela[linhas][colunas];
    char arquivoExpressao[] = {"expressao.txt"};
    int valor, entradas, variaveis;
    valor = entradas = variaveis = 0;

    printf("\nDigite o nome do arquivo que deseja abrir\n");
    gets(arquivoSaidas);
    printf("\n");

    arq1 = fopen(arquivoSaidas, "r");
    if (arq1 == NULL)
    {
        printf("Arquivo nao encontrado!\n");
    }

    while (!feof(arq1))
    {
        while (fscanf(arq1, "%d", &valor) == 1)
        {
            saidas[entradas] = valor; // guarda as saidas
            entradas++;
        }
    }
    fclose(arq1);

    variaveis = descobreVariavel(entradas); // calcula a quantidade de variaveis com base nas saidas

    arq2 = fopen(arquivoExpressao, "w"); // cria o arquivo que guarda a expressao
    tabelaVerdade(variaveis, entradas, saidas, tabela, arq2);
    fclose(arq2);

    arq2 = fopen(arquivoExpressao, "r"); // abre o arquivo que guarda a expressao
    lerExpressao(arq2);
    fclose(arq2);

    return 0;
}

// Gera a tabela verdade
void tabelaVerdade(int variaveis, int entradas, int saidas[], int tabela[][colunas], int *arq2)
{

    int contador, valor, j, k, aux1, aux2, m;
    contador = valor = j = k = aux1 = aux2 = m = 0;
    int exp = 1;

    for (j = 0; j < variaveis; j++)
    {
        aux1 = potencia(2, exp);
        aux2 = entradas / aux1;
        valor = 0;
        contador = 0;

        for (k = 0; k < entradas; k++)
        {
            if (aux2 == contador)
            {
                valor = !valor;
                contador = 0;
            }
            tabela[k][j] = valor;
            contador++;
        }
        exp++;
    }

    for (m = 0; m < entradas; m++)
    {
        tabela[m][variaveis] = saidas[m];
    }

    imprimeTabela(entradas, variaveis, tabela);
    mintermos(entradas, saidas, tabela, variaveis, arq2);
}

// Mostra a tebela verdade
void imprimeTabela(int entradas, int variaveis, int tabela[][colunas])
{

    int j, k, m;
    char let = 65; // ASCII :A
    for (m = 0; m < variaveis; m++)
    {
        printf("%c ", let);
        let++;
    }
    printf("S\n");
    for (j = 0; j < entradas; j++)
    {
        for (k = 0; k <= variaveis; k++)
        {
            printf("%d|", tabela[j][k]);
        }
        printf("\n");
    }
}

// Gera os termos da expressao atraves da Forma Normal Disjuntiva, usando soma de produtos
void mintermos(int entradas, int saidas[], int tabela[][colunas], int variaveis, int *arq2)
{
    char letra = 65, teste;
    int auxLinhaSaidas, auxColunaTabela;

    printf("\n|Expressao Booleana para um Circuito com %d Variaveis e %d Saidas|\n", variaveis, entradas);

    for (auxLinhaSaidas = 0; auxLinhaSaidas < entradas; auxLinhaSaidas++)
    { // percorre a quantidade de entradas total
        if (saidas[auxLinhaSaidas] == 1)
        {
            for (auxColunaTabela = 0; auxColunaTabela < variaveis; auxColunaTabela++)
            { // percorre as colunas das variaveis(tabela)
                if (tabela[auxLinhaSaidas][auxColunaTabela] == 0)
                {
                    teste = 's';
                    escreverExpressao(arq2, letra, teste);
                }
                else
                {
                    teste = 'n';
                    escreverExpressao(arq2, letra, teste);
                }
                letra++; // Pula coluna para usar outra letra como variavel/elemento para o mintermo
            }
            teste = 'p';
            escreverExpressao(arq2, letra, teste);
            letra = 65;
        }
    }
}

// Guarda a expressao em um arquivo chamado expressao.txt
void escreverExpressao(int *arq2, char letra, char teste)
{
    char neg = '\'';

    if (arq2 == NULL)
    {
        printf("\n\t Erro ao abrir o arquivo\n");
    }
    else
    {
        if (teste == 's')
        {
            fprintf(arq2, "%c%c", neg, letra);
        }
        else if (teste == 'p')
        {
            fprintf(arq2, " + ");
        }
        else
        {
            fprintf(arq2, "%c", letra);
        }
    }
}

// Mostra na tela a expressao guardada no arquivo
void lerExpressao(int *arq2)
{
    char expressao[200];
    if (arq2 == NULL)
    {
        printf("\n\t Erro ao abrir o arquivo\n");
    }
    else
    {
        printf("S = ");
        while (fgets(expressao, 10, arq2) != NULL)
        {
            printf("%s", expressao);
        }
    }
}

// Função potencia para inteiros
int potencia(int base, int expoente)
{
    if (expoente == 0)
    {
        return 1;
    }
    else
    {
        return base = base * (potencia(base, expoente - 1));
    }
    return 0;
}

// Calcula quantas variaveis o sistema possui atraves da quantidade de saidas
int descobreVariavel(int entradas)
{
    int aux1 = 0, aux2 = 0;

    while (aux2 != entradas)
    {
        aux1++;
        aux2 = potencia(2, aux1);
    }
    return aux1;
}
