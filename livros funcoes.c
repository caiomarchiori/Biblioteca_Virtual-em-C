
#include "includes.h"
#include "biblioteca alunos.h"
#include "biblioteca livros.h"


// strings utilizadas para facilitar a mensagem para o usuario
char string_disponivel[11]="DISPONIVEL";
char string_emprestado[11]="EMPRESTADO";


struct livro *busca_categoria(struct livro *cab,char categoria[50],struct livro **ant){
    (*ant)=cab;
    struct livro *p=cab->prox;
    while(p != NULL && strcmp(p->categoria,categoria) != 0){
        (*ant)=p;
        p=p->prox;
    }
    return p;
    // mesmo principio de busca_cadastro (nas funcoes de alunos), porem agora utiliza a categoria para busca
    // p esta retornando NULL caso nao ache a categoria
    // p retorna != NULL caso ache a categoria
}

void lista_categoria(struct livro *cab){
    if(cab->prox == NULL){
        printf("Nao existe categorias cadastradas ainda\n");
        return;
    }
    else{
        char categoria[50];;
        printf("Insira a categoria que deseja listar os livros: ");
        fflush(stdin);
        gets(categoria);
        struct livro *ant=NULL;
        struct livro *ptr=busca_categoria(cab,categoria,&ant); // analisa se a categoria inserida pelo usuario esta nos cadastros de livros
        if(ptr == NULL){
            printf("Categoria nao existe no cadastro!!\n");
            return;
        }
        else{
            struct livro *p=cab->prox;
            while(p != NULL){
                int resultado=strcmp(p->categoria,categoria);
                if(resultado == 0){ // para mostrar apenas as info dos livros da categoria
                    printf("\n");
                    printf("Nome: %s \n",p->nome);
                    printf("ID: %d \n",p->ID_livro);
                    printf("Ano de publicacao: %d \n",p->ano_de_publicacao);
                    printf("Estado: %d -",p->estado);
                    if(p->estado == 0)
                        printf("%s\n",string_emprestado);
                    else
                        printf("%s\n",string_disponivel);
                }
                p=p->prox;
            }
        }
    }
    printf("\n");
}

struct livro *busca_livro(struct livro *cab,int id,struct livro **ant){
    (*ant)=cab;
    struct livro *p=cab->prox;
    while(p != NULL && p->ID_livro != id){
        (*ant)=p;
        p=p->prox;
    }
    return p;
    // mesmo principio da busca_categoria, mas agora utiliza o ID_livro para pesquisa
}

void adiciona_livro(struct livro *cab,int *id,int *qtd_livros){
    struct livro *ant=NULL;
    struct livro *p=busca_livro(cab,*id,&ant); // utilizado para nao haver mesmo cadastro de ID
    if(p != NULL){
        printf("ID %d ja esta cadastrado!!\n",p->ID_livro);
        return;
    }

    p=(struct livro *)malloc(sizeof(struct livro));

    printf("Insira o nome do livro: ");
    fflush(stdin);
    gets(p->nome);

    printf("Insira o ano de publicacao: ");
    int ano=p->ano_de_publicacao;
    scanf("%d",&ano);
    p->ano_de_publicacao=ano;

    printf("Insira a categoria: ");
    fflush(stdin);
    gets(p->categoria);


    p->ID_livro=(*id);                                              /*como e o proprio programa que gera o ID_livro
                                                                    utilizado um ponteiro para atribuir e atualizar o ID_livro*/
    printf("ID %d criado com sucesso\n",p->ID_livro);
    (*id)++;


    printf("Confirme o estado (INSIRA 1): ");
    int estado=p->estado;
    scanf("%d",&estado);
    if(estado != 1){
        printf("Estado invalido\n");
        return;
    }
    p->estado=estado;

    if(p->estado != 0 && p->estado !=1){ //usuario inseriu um estado invalido
        printf("Estado invalido\n");
        return;
    }

    (*qtd_livros)++; // incrementa a quantidade de livros cadastrados

    p->prox=cab->prox;
    cab->prox=p;

    printf("Livro cadastrado nos registros com sucesso\n");
    printf("\n");

}

void listar_livros(struct livro *cab,struct aluno *cab2) {
    if(cab->prox == NULL){
        printf("Nao existem livros cadastrados ainda\n");
        return;
    }
    struct livro *p=cab->prox;
    printf("LIVROS CADASTRADOS: \n");
    while(p != NULL){
        printf("\n");
        printf("Nome: %s\n",p->nome);
        printf("Categoria: %s\n",p->categoria);
        printf("ID: %d\n",p->ID_livro);
        printf("Ano de publicacao: %d\n",p->ano_de_publicacao);
        printf("Estado: %d",p->estado);

        if(p->estado == 0)
            printf("-%s\n",string_emprestado);
        else
            printf("-%s\n",string_disponivel);

        if(p->estado == 1)
            printf("Livro nao esta emprestado para nenhum aluno \n");

        if(p->estado == 0){
            struct aluno *ant=NULL;
            struct aluno *ptr=busca_ID(cab2,p->ID_aluno,&ant); // verificar para qual aluno o livro esta emprestado
            printf("Livro esta emprestado para o aluno de matricula: %d\n",ptr->matricula);
        }
        p=p->prox;
    }
    printf("\n");
}

void remove_livro(struct livro *cab,int *qtd_livros){
    if(cab->prox == NULL){
        printf("Nao existem livros cadastrados ainda\n");
        return;
    }
    int id;
    struct livro *ant=NULL;
    struct livro *p;
    printf("Insira o ID que deseja remover: ");
    scanf("%d",&id);
    p=busca_livro(cab,id,&ant); // validar o estado do ID_livro que o usuario inseriu
    if(p != NULL){
        if(p->estado == 0){
            printf("Livro %s ainda nao foi devolvido\n",p->nome);
            printf("Nao e possivel remove-lo");
            return;
        }
        else{
            ant->prox=p->prox;
            free(p);
            printf("ID %d excluido com sucesso!!\n",id);
            (*qtd_livros)--;
        }
    }
    else
       printf("ID %d nao esta presente no cadastro!!\n",id);

    printf("Livro removido dos registros com sucesso\n");
    printf("\n");
}

void lista_livro(struct livro *cab,struct aluno *cab2){
    if(cab->prox == NULL){
        printf("Nao existem livros cadastrados ainda\n");
        return;
    }
    else{
        int id;
        struct livro*ant=NULL;
        struct livro *p;
        printf("Insira o ID para pesquisa: ");
        scanf("%d",&id);
        p=busca_livro(cab,id,&ant); // verificar se o ID_livro esta presente nos cadastros

        if(p == NULL){
            printf("ID %d nao encontrado\n",id);
            return;
        }
        else{
            printf("ID: %d \n",p->ID_livro);
            printf("Nome: %s \n",p->nome);
            printf("Ano de publicacao: %d \n",p->ano_de_publicacao);
            printf("Categoria: %s \n",p->categoria);
            printf("Estado: %d-",p->estado);

            if(p->estado==0){
                printf("%s\n",string_emprestado);
                struct aluno *ant2=NULL;
                struct aluno *ptr=busca_ID(cab2,p->ID_aluno,&ant2);
                printf("Livro esta emprestado para o aluno de matricula: %d\n",ptr->matricula);
            }
            else{
                printf("%s\n",string_disponivel);
                printf("Livro nao esta emprestado para nenhum aluno!!\n");
            }
        }
    }

 }

void altera_pendencia(struct livro *cab,struct aluno *cab2){
    if(cab->prox == NULL){
        printf("Nao existem livros cadastrados ainda\n");
        return;
    }
    else{
        int id;
        printf("Insira o ID do livro que deseja alterar o estado: ");
        scanf("%d",&id);
        struct livro *ant=NULL;
        struct livro *p=busca_livro(cab,id,&ant);
        if(p == NULL){
            printf("ID %d nao encontrado\n",id);
            return;
        }
        else{
            int escolha=0;
            printf("Insira 1 para devolver ou 0 para pegar um livro: ");
            scanf("%d",&escolha);
            if(escolha == 0){ //pegando livro
                if(p->estado == 1){//esta disponivel
                    printf("Insira o ID aluno que esta pegando o livro: ");
                    int id=p->ID_aluno;
                    scanf("%d",&id);
                    p->ID_aluno=id;

                    struct aluno *ant3=NULL;
                    struct aluno *pointer=busca_ID(cab2,p->ID_aluno,&ant3); // buscando o ID do aluno inserido

                    if(pointer == NULL){
                        printf("ID %d nao encontrado \n",p->ID_aluno);
                        return;
                    }
                    else{
                        int estado;
                        printf("Insira o novo valor de estado (EMPRESTADO=0 E DISPONIVEL=1): ");
                        scanf("%d",&estado);
                        if(estado == 1){
                            printf("Este valor ja esta atribuido\n");
                            return;
                        }
                        if(estado != 0 && estado != 1){ // testando o valor inserido pelo usuario
                            printf("Estado invalido\n");
                            return;
                        }
                        else{
                            printf("Estado atualizado para: %d",estado) ;
                            p->estado=estado;
                        }
                        if(p->estado == 0){
                            printf(" -%s\n",string_emprestado);
                            pointer->pendencia++;
                        }
                        else{
                            printf(" -%s\n",string_disponivel);
                            pointer->pendencia--;
                        }
                    }
                }
                else{
                    printf("%d ja esta emprestado!!\n",p->ID_livro);
                    return;
                }
            }
            if(escolha == 1){ // devolvendo livro
                if(p->estado == 0){//esta alugado
                    int id2;
                    printf("Insira o ID do aluno que esta devolvendo o livro: ");
                    scanf("%d",&id2);
                    if(id2 == p->ID_aluno){ // inseriu um ID igual ao do aluno que pegou o livro
                        p->ID_aluno=id2;
                        struct aluno *ant2=NULL;
                        struct aluno *ptr=busca_ID(cab2,p->ID_aluno,&ant2);  // buscando o ID do aluno inserido
                        if(ptr == NULL){
                            printf("ID %d nao encontrado \n", p->ID_aluno);
                            return;
                        }
                        else{
                            int estado2;
                            printf("Insira o novo valor de estado (EMPRESTADO=0 E DISPONIVEL=1): ");
                            scanf("%d",&estado2);
                            if(estado2 == 0){
                                printf("Este valor ja esta atribuido\n");
                                return;
                            }
                            if(estado2 != 0 && estado2 !=1){ // testando o valor inserido pelo usuario
                                printf("Estado invalido\n");
                                return;
                            }
                            else{
                                printf("Estado atualizado para:%d",estado2);
                                p->estado=estado2;
                            }
                            if(p->estado == 1){
                                printf(" -%s\n",string_disponivel);
                                ptr->pendencia--;
                            }
                            else{
                                printf(" -%s\n",string_emprestado);
                                ptr->pendencia++;
                            }
                        }
                    }
                    else{
                        printf("ID: %d nao e o mesmo do aluno que pegou o livro\n",id2); // caso insira um id diferente de quem pegou o livro emprestado
                        return;
                    }

                }
                else{
                    printf("%d ainda esta disponivel \n",p->ID_livro);
                    printf("Nao e possivel devolve-lo\n");
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
