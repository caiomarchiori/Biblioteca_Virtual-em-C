
#include "includes.h"
#include "biblioteca alunos.h"
#include "biblioteca sca.h"

// apenas declarando os 3 tipos existentes de cadastro

char sala[5]="sala";
char computador[11]="computador";
char armario[8]="armario";

struct sca *busca_cadastro_sca(struct sca *cab,int id,struct sca **ant){
    (*ant)=cab;
    struct sca *p=cab->prox;
    while(p != NULL && p->ID_sca != id){
        (*ant)=p;
        p=p->prox;
    }
    return p;
    /*utiliza o ponteiro p de retorno, para saber se o id foi encontrada ou nao
    p==null novo cadastro
    p!=null cadastro ja existe*/
}

void adiciona(struct sca *cab, struct aluno *cab2,int *qtd_sca){
    char tipo[11];
    printf("Sala,Computador ou Armario\n");
    printf("\n");
    printf("Insira o tipo de  cadastro: ");
    fflush(stdin);
    gets(tipo);
    int aux=strcmp(tipo,sala);  //vejo se a string digitada pelo usuario é igual, strcmp retorna 0 se é verdade
    int aux2=strcmp(tipo,computador);
    int aux3=strcmp(tipo,armario);

    if(aux == 0 || aux2 == 0 || aux3 == 0){
        int id;
        struct sca *ant=NULL;
        printf("Insira o ID que deseja cadastrar: ");
        scanf("%d",&id);
        struct sca *p=busca_cadastro_sca(cab,id,&ant);

        if(p != NULL){
            printf("ID %d ja esta cadastrado!!\n",id);
            return;
        }

        p=(struct sca *)malloc(sizeof(struct sca));

        strcpy(p->tipo,tipo); //salvei o tipo de cadastro na struct

        p->ID_sca=id; //salvei o ID de cadastro na struct

        printf("Confirme o estado (INSIRA 1): ");
        int estado=p->estado;
        scanf("%d",&estado);
        if(estado != 1){
            printf("Estado invalido\n");
            return;
        }
        p->estado=estado;

        if(p->estado != 0 && p->estado !=1){
            printf("Estado invalido\n");
            return;
        }

        (*qtd_sca)++; //atualizo o numero de cadastros

        p->prox=cab->prox;
        cab->prox=p;
    }
    else{
        printf("Essa categoria nao existe!!\n");
        return;
    }

    printf("SCA cadastrada nos registros com sucesso\n");
    printf("\n");

}

void listar_sca(struct sca *cab,struct aluno *cab2) {
    if(cab->prox == NULL){
        printf("Nao existem cadastros de Sala,Computador ou Armario ainda\n");
        return;
    }
    struct sca *p=cab->prox;
    printf("Salas,Computadores e Armarios cadastrados: \n");
    while(p != NULL){
        printf("\n");
        printf("Tipo: %s\n",p->tipo);
        printf("ID: %d\n",p->ID_sca);
        printf("Estado: %d\n",p->estado);
        if(p->estado == 1)
            printf("ID %d nao esta emprestado para nenhum aluno\n", p->ID_sca);
        else{
            struct aluno *ant=NULL;
            struct aluno *ptr=busca_ID(cab2,p->ID_aluno,&ant);
            printf("ID %d esta emprestado para o aluno de matricula %d\n",p->ID_sca,ptr->matricula);
        }
        p=p->prox;
    }
    printf("\n");
}

void remove_sca(struct sca *cab,int *qtd_sca){
    if(cab->prox == NULL){
        printf("Nao existem cadastros de Sala,Computador ou Armario ainda\n");
        return;
    }
    int id;
    struct sca *ant=NULL;
    struct sca *p;
    printf("Insira o ID  que deseja remover: ");
    scanf("%d",&id);
    p=busca_cadastro_sca(cab,id,&ant);
    if(p != NULL){
        if(p->estado == 0){// se estiver emprestado a algum aluno ainda nao e possivel retira-la do cadastro
            printf("ID %d se encontra emprestado!\n",p->ID_sca);
            printf("Nao e possivel remove-lo\n");
            return;
        }
        else{
            ant->prox=p->prox;
            free(p);
            printf("ID %d excluido com sucesso!!\n",id );
            (*qtd_sca)--;
        }
    }
    else
       printf("ID %d nao esta presente nos cadasdtros!!\n",id);

    printf("\n");
}

void altera_estado(struct sca *cab,struct aluno *cab2){
    if(cab->prox == NULL){
        printf("Nao existem cadastros de Sala,Computador ou Armario ainda\n");
        return;
    }
    else{
        int id;
        printf("Insira o ID do que deseja alterar o estado: ");
        scanf("%d",&id);
        struct sca *ant=NULL;
        struct sca *p=busca_cadastro_sca(cab,id,&ant);
        if(p == NULL){
            printf("ID: %d nao encontrado\n",id);
            return;
        }
        else{
            int escolha=0;
            printf("Insira 1 para devolver ou 0 para pegar: ");
            scanf("%d",&escolha);
            if(escolha == 0){ //pegando livro
                if(p->estado == 1){//esta disponivel
                    printf("Insira o ID aluno que esta pegando: ");
                    int id=p->ID_aluno; // para leitura e insercao do ID inserido pelo usuario
                    scanf("%d",&id);
                    p->ID_aluno=id;

                    struct aluno *ant3=NULL;
                    struct aluno *pointer=busca_ID(cab2,p->ID_aluno,&ant3);

                    if(pointer == NULL){
                        printf("ID: %d nao encontrado \n",p->ID_aluno);
                        return;
                    }
                    else{
                        int estado;
                        printf("Insira o novo valor de estado (EMPRESTADO=0 E DISPONIVEL=1): ");
                        estado=p->estado;
                        scanf("%d",&estado);
                        p->estado=estado;

                        if(estado == 1){
                            printf("Este valor ja esta atribuido\n");
                            return;
                        }
                        if(estado != 0 && estado != 1){
                            printf("Estado invalido\n");
                            return;
                        }
                        else{
                            printf("Estado atualizado para: %d",estado);
                            p->estado=estado; // salvei o valor correto na struct
                        }
                        if(p->estado == 0){
                            printf(" -EMPRESTADO \n");
                            pointer->pendencia++; // muda a pendencia do aluno
                        }
                        else{
                            printf(" -DISPONIVEL \n");
                            pointer->pendencia--;
                        }
                    }

                }
                else{
                    printf("%d ja esta emprestado \n",p->ID_sca);
                    return;
                }
            }
            if(escolha == 1){ // devolvendo livro
                if(p->estado == 0){//esta alugado
                    int id2;
                    printf("Insira o ID do aluno que esta devolvendo: ");
                    scanf("%d",&id2);
                    if(id2 == p->ID_aluno){
                        p->ID_aluno=id2;
                        struct aluno *ant2=NULL;
                        struct aluno *ptr=busca_ID(cab2,p->ID_aluno,&ant2);
                        if(ptr == NULL){
                            printf("ID: %d nao foi encontrado nos cadastros \n",p->ID_aluno);
                            return;
                        }
                        else{
                            int estado2;
                            printf("Insira o novo valor de estado (EMPRESTADO=0 E DISPONIVEL=1): ");
                            estado2=p->estado;
                            scanf("%d",&estado2);
                            p->estado=estado2;

                            if(estado2 == 0){
                                printf("Este valor ja esta atribuido\n");
                                return;
                            }
                            if(estado2 != 0 && estado2 != 1){
                                printf("Estado invalido\n");
                                return;
                            }
                            else{
                                printf("Estado atualizado para: %d",estado2);
                                p->estado=estado2;
                            }

                            if(p->estado == 1){
                                printf(" -DISPONIVEL \n");
                                ptr->pendencia--;
                            }
                            else{
                                printf(" -EMPRESTADO \n");
                                ptr->pendencia++;
                            }
                        }
                    }
                    else{
                        printf("ID %d nao eh o mesmo do aluno que pegou emprestado\n",id2);
                        return;
                    }

                }
                else{
                    printf("%d ainda esta disponivel\n,",p->ID_sca);
                    printf("Nao e possivel devolve-lo \n");
                    return;
                }

            }
            if(escolha != 0 && escolha != 1){
                printf("Opcao invalida \n");
                return;
            }
        }
    }
}
