#include "includes.h"
#include "biblioteca alunos.h"

struct aluno *busca_cadastro(struct aluno *cab,int matricula,struct aluno **ant){
    (*ant)=cab;
    struct aluno *p=cab->prox;
    while(p != NULL && p->matricula != matricula){
        (*ant)=p;
        p=p->prox;
    }

    return p;
    /*utiliza o ponteiro p de retorno, para saber se a matricula foi encontrada ou nao
    p == null matricula ainda nao existe no cadastro
    p != null matricula ja existe no cadastro*/

}

void adiciona_cadastro(struct aluno *cab,int *id,int *qtd_alunos){
    int matricula;
    struct aluno *ant=NULL;
    printf("Insira a matricula, com apenas numeros, que deseja cadastrar: ");
    scanf("%d",&matricula);
    struct aluno *p=busca_cadastro(cab,matricula,&ant); // verificar se a matricula inserida pelo usuario ja esta presente no cadastro
    if(p != NULL){
        printf("Matricula %d ja esta cadastrada!!\n",matricula);
        return;
    }

    p=(struct aluno *)malloc(sizeof(struct aluno));

    printf("Confirme a matricula inserida acima: ");
    int matricula2=p->matricula;
    scanf("%d",&matricula2);

    if(matricula2 != matricula){ // cadastro da matricula ocorreu incorretamente
        printf("Matriculas sao diferentes!!\n");
        return;
    }

    else{
        p->matricula=matricula2; //salvar a matricula na struct

        printf("Insira o nome completo do aluno: ");
        fflush(stdin);
        gets(p->nome);

        p->ID_aluno=(*id);                                                      /*como e o proprio programa que gera o ID_aluno
                                                                                utilizado um ponteiro para atribuir e atualizar o ID_aluno*/
        (*id)++;
        printf("ID: %d atribuido com sucesso!!\n",p->ID_aluno);

        printf("Confirme o numero de pendencias do aluno (INSIRA 0): ");
        int pendencia=p->pendencia;
        scanf("%d",&pendencia);
        if(pendencia != 0){
            printf("Dado invalido!\n");
            return;
        }
        p->pendencia=pendencia;

        (*qtd_alunos)++; // atualiza o numero total de alunos cadastrados (utilizado no arquivo alunos.txt)

        p->prox=cab->prox;
        cab->prox=p;
    }
    printf("Aluno cadastrado nos registros com sucesso\n");
    printf("\n");
}

void listar_cadastros(struct aluno *cab){
    if(cab->prox == NULL){
        printf("Nao existem cadastros realizados ainda!!\n");
        return;
    }
    struct aluno *p=cab->prox;
    printf("ALUNOS CADASTRADOS: \n");
    while(p != NULL){
        printf("\n");
        printf("Nome: %s \n",p->nome);
        printf("Matricula: %d \n",p->matricula);
        printf("ID: %d \n",p->ID_aluno);
        if(p->pendencia != 0)
            printf("Este aluno ainda tem %d pendencia(s)!!\n",p->pendencia);
        else
            printf("Este aluno nao tem pendencias!!\n");
        p=p->prox;
    }
    printf("\n");
}

void remove_cadastro(struct aluno *cab, int *qtd_alunos){
    if(cab->prox == NULL){
        printf("Nao existem cadastros realizados ainda!!\n");
        return;
    }
    int matricula;
    struct aluno *ant=NULL;
    struct aluno *p;
    printf("Insira a matricula, com apenas numeros, que deseja remover: ");
    scanf("%d",&matricula);
    p=busca_cadastro(cab,matricula,&ant); // verificar se a matricula inserida pelo usuario e valida, ou seja, existe no cadastro
    if(p != NULL){
        if(p->pendencia != 0){
            printf("Aluno de matricula %d ainda possui %d pendencia(s)!!\n",p->matricula,p->pendencia);
            printf("Nao e possivel remove-lo\n");
            return;
        }
        else{
            ant->prox=p->prox;
            free(p);
            printf("Matricula %d excluida com sucesso!!\n",matricula);
            (*qtd_alunos)--; // decrementa a quantidade total de alunos cadastrados
        }
    }
    else
       printf("Matricula %d nao esta presente no cadastro!!\n",matricula);

    printf("Aluno removido dos registros\n");
    printf("\n");
}

void lista_aluno(struct aluno *cab){
    if(cab->prox == NULL){
        printf("Nao existem cadastros realizados ainda!!\n");
        return;
    }
    else{
        int matricula;
        struct aluno *ant=NULL;
        struct aluno *p;
        printf("Insira a matricula,com apenas numeros, para pesquisa: ");
        scanf("%d",&matricula);
        p=busca_cadastro(cab,matricula,&ant); // verificar se a matricula inserida pelo usuario e valida

        if(p == NULL){
            printf("Matricula %d nao esta presente no cadastro!!\n",matricula);
            return;
        }
        else{
            printf("ID: %d\n",p->ID_aluno);
            printf("Nome: %s\n",p->nome);
            printf("Matricula: %d\n",p->matricula);
            printf("Pendencia: %d\n",p->pendencia);
        }
    }
    printf("\n");
 }

struct aluno *busca_ID(struct aluno *cab,int id,struct aluno **ant){
    (*ant)=cab;
    struct aluno *p=cab->prox;
    while(p != NULL && p->ID_aluno != id){
        (*ant)=p;
        p=p->prox;
    }
    return p;
    // mesmo principio de busca_cadastro, porem agora utiliza o ID para busca
}

