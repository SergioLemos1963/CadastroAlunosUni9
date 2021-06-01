#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
        int ra;
        char nome[50];
} Aluno;

typedef struct local
{
        Aluno aluno;
        struct local *pProximaLocal;
} Local;

typedef struct
{
        Local *pPrimeiraLocal;
} Amigos;

void listar(const Amigos *pAmigos)
{
        Local *p;

        system("cls");
        printf("%10s  %4s  %-20s \n\n","ENDERECO DA MEMORIA","RA","NOME\n");
        for (p=pAmigos->pPrimeiraLocal; p; p=p->pProximaLocal)
        {
            printf("[%p] %4d  %-20s\n\n", p, p->aluno.ra, p->aluno.nome);
        }
}

void maiorNome(const Amigos *pAmigos)
{
        Local *p;
        Aluno selecionado;
        int comprimento = 0;

        system("cls");
        printf("\n%-20s %s\n\n","ENDERECO DA MEMORIA","Exibir o maior nome cadastrado.\n");
        for (p=pAmigos->pPrimeiraLocal; p; p=p->pProximaLocal)
        {
          if (strlen(p->aluno.nome) > comprimento) {
            comprimento = strlen(p->aluno.nome);
            selecionado = p->aluno;
          }
        }
        printf("RA: %4d NOME: %-20s\n\n", selecionado.ra, selecionado.nome);
}

void menorNome(const Amigos *pAmigos)
{
        Local *p;
        Aluno selecionado;
        int comprimento = 51;

        system("cls");
        printf("\n%-20s %s\n\n","ENDERECO DA MEMORIA","Exibir o menor nome cadastrado.\n");
        for (p=pAmigos->pPrimeiraLocal; p; p=p->pProximaLocal) {
          if (strlen(p->aluno.nome) < comprimento) {
            comprimento = strlen(p->aluno.nome);
            selecionado = p->aluno;
          }
        }
        printf("RA: %4d NOME: %-20s\n\n", selecionado.ra, selecionado.nome);
}


int inserir(Amigos *pAmigos, const Aluno *pNovoAluno)
{
        Local *pNovaLocal;
        pNovaLocal = malloc(sizeof(Local));

        if (!pNovaLocal) return 1;

        pNovaLocal->aluno = *pNovoAluno;

        pNovaLocal->pProximaLocal = pAmigos->pPrimeiraLocal;

        pAmigos->pPrimeiraLocal = pNovaLocal;

        return 0;
}

Aluno *localizar(const Amigos *pAmigos, const int ra)
{
        Local *p;

        for (p=pAmigos->pPrimeiraLocal; p; p=p->pProximaLocal)
        {
            if (p->aluno.ra == ra)
            {
                return (Aluno *) &(p->aluno);
            }
        }
        return (Aluno *) NULL;
}

void localizarPorNome(const Amigos *pAmigos, char nome[50])
{
        Local *p;

        int c, encontrado = 0;
        char sub[50];

        for (p=pAmigos->pPrimeiraLocal; p; p=p->pProximaLocal)
        {
            c = 0;
            while (c < strlen(nome)) {
              sub[c] = p->aluno.nome[c];
              c++;
            }

            if (strcmp(p->aluno.nome, nome) == 0 || strcmp(sub, nome) == 0)
            {
              encontrado = 1;
              printf("\nAluno encontrado: RA: %4d NOME: %s\n\n",p->aluno.ra,p->aluno.nome);
            }
        }
        if (encontrado == 0) {
          printf("\n\n ERRO: Aluno nao encontrado\n\n");
        }
}

int excluir(Amigos *pAmigos, const int ra)
{
        Local *p, *pExcluir;
        int r=1;

        if (pAmigos->pPrimeiraLocal == NULL) return 2;

        if (pAmigos->pPrimeiraLocal->aluno.ra == ra)
        {

                pExcluir = pAmigos->pPrimeiraLocal;
                pAmigos->pPrimeiraLocal = pAmigos->pPrimeiraLocal->pProximaLocal;
                free(pExcluir);
                r=0;
        }
        else
        {

                for (p=pAmigos->pPrimeiraLocal; p!=NULL; p=p->pProximaLocal)
                {
                        if (p->pProximaLocal->aluno.ra == ra)
                        {
                                pExcluir = p->pProximaLocal;
                                p->pProximaLocal = p->pProximaLocal->pProximaLocal;
                                free(pExcluir);
                                r=0; break;
                        }
                }
        }

        return r;
}


int main()
{
        Aluno meuAluno;
        Amigos minhaAmigos;
        int resultado,Item,m;
        char nome[50];
        Aluno *pAluno;

        minhaAmigos.pPrimeiraLocal = NULL;

        do
        {
                system("cls");
                printf("\n");
                printf(" Trabalho Professor Leandro Fernandes da Mota\n\n");
                printf(" Cadastro de Alunos - UNI9\n\n");
                printf(" 1 - Cadastrar - Aluno e RA\n\n");
                printf(" 2 - Consultar - por RA\n\n");
                printf(" 3 - Listar    - todos Alunos\n\n");
                printf(" 4 - Buscar    - por Nome\n\n");
                printf(" 5 - Excluir   - todos por RA\n\n");
                printf(" 6 - Exibir    - Maior e Menor Nome Cadastrado\n\n");
                printf(" 7 - Sair\n");
                printf("\nGrupo SERGIO DE SOUZA LEMOS            - RA 920103473");
                printf("\nALANA LARISSA FERREIRA DE JESUS        - RA 920123346");
                printf("\nANDRE AUGUSTO MARQUES                  - RA 920110931");
                printf("\nCAIQUE MILAN ARAUJO                    - RA 920120809");
                printf("\nFABIO CONCEICAO SILVA                  - RA 920105347");
                printf("\nHENRIQUE DUTRA TEIXEIRA                - RA 920113454");
                printf("\nINGRID DOMENICALI SATO LIMA DOS SANTOS - RA 920118078");
                printf("\nFLAVIO MARTINS DE OLIVEIRA JUNIOR      - RA 920118587");
                printf("\nJACQUELINE DE JESUS NOGUEIRA           - RA 920102612");
                printf("\nVICTOR AUGUSTO MAZZA RONCHI            - RA 920123341");
                printf("\n\nEscolha uma Opcao: ");
                scanf("%d",&Item);


                if (Item == 1)
                {
                        system("cls");
                        printf("\nCadastrar novo Aluno\n");
                        printf("\nDigite o RA: "); scanf("%d",&(meuAluno.ra));
                        printf("\nDigite o Nome: "); scanf("%s",meuAluno.nome);

                        resultado = inserir(&minhaAmigos,&meuAluno);

                        if (resultado==0) printf("\nInclusao bem sucedida\n\n");
                }

                if (Item == 3)
                {
                        listar(&minhaAmigos);
                }

                if (Item == 2)
                {
                        system("cls");
                        printf("\nProcurar por RA\n\n");
                        printf("Digite o RA: "); scanf("%d",&m);
                        pAluno = localizar(&minhaAmigos,m);

                        if (pAluno)
                        {
                                printf("\nAluno encontrado: %s\n\n",pAluno->nome);
                        }
                        else
                        {
                                printf("\n\n ERRO: Aluno nao encontrado\n\n");
                        }
                }

                if (Item == 4)
                {
                        system("cls");
                        printf("\nProcurar por Nome\n\n");
                        printf("Digite o nome (completo ou inicio): "); scanf("%s", nome);
                        localizarPorNome(&minhaAmigos, nome);
                }

                if (Item == 5)
                {
                        system("cls");
                        printf("\nExcluir Aluno\n");
                        printf("\nDigite RA: "); scanf("%d",&m);
                        resultado = excluir(&minhaAmigos,m);


                        if (resultado==0) printf("\nExclusao bem sucedida.\n\n");
                        if (resultado==1) printf("\nAluno nao encontrado.\n\n");
                        if (resultado==2) printf("\nLista vazia.\n\n");

                }

                if (Item == 6)
                {
                        system("cls");
                        printf("\n\nEscolher opcoes:");
                        printf("\n\nDigite 1 = Menor ou 2 = Maior: "); scanf("%d",&m);

                        if (m == 1)
                        {
                                menorNome(&minhaAmigos);
                        }
                        else
                        {
                                maiorNome(&minhaAmigos);
                        }
                }

                system("pause");
        }

        while (Item != 7);
        system("cls");
        printf("\n\nObrigado e ate breve!!!\n\n\n");
        system("pause");

        return 0;
}
