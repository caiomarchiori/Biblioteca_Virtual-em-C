
#include "includes.h"
#include "biblioteca alunos.h"
#include "biblioteca livros.h"
#include "biblioteca sca.h"

void chama_menu(){  // somente para apresentar o menu de opcoes ao usuario

    printf("**************************** MENU PRINCIPAL **************************** \n");
    printf("0. Encerrar o programa \n");
    printf("\n");

    printf("FUNCOES DOS ALUNOS:                                 FUNCOES DOS LIVROS:\n");
    printf("\n");
    printf("1. Adiciona cadastro                                5. Adiciona livro\n");
    printf("2. Listar os cadastros                              6. Listar livros\n");
    printf("3. Remove cadastro                                  7. Remove livro\n");
    printf("4. Listar aluno                                     8. Lista livro\n ");
    printf("                                                   9. Alterar pendencia\n");
    printf("                                                   10. Lista categoria\n");

    printf("\n");
    printf("\n");
    printf("FUNCOES SALA,COMPUTADOR E ARMARIO:                  FUNCOES DE ARQUIVOS:\n");
    printf("\n");

    printf("11. Adiciona                                        15. Salvar no alunos.txt\n");
    printf("12. Listar_sca                                      16. Salvar no livros.txt\n");
    printf("13. Remove_sca                                      17. Salvar no SCA.txt\n");
    printf("14. Altera_estado                                   18. Importar dados do aluno.txt\n");
    printf("                                                    19. Importar dados do livros.txt\n");
    printf("                                                    20. Importar dados de sca.txt\n");

    printf("\n");
    printf("FUNCOES DE CRIPTOGRAFIA:\n");
    printf("\n");
    printf("21. Criptografar/Decriptografar alunos.txt\n");
    printf("22. Criptografar/Decriptografar livros.txt\n");
    printf("23. Criptografar/Decriptografar sca.txt\n");
    printf("\n");

}

int main(){

    struct aluno *cab=(struct aluno *)malloc(sizeof(struct aluno)); // declaracao dinamica dos auxiliares (cabeca) utilizados para cada estrutura
    cab->prox=NULL;

    struct livro *cab2=(struct livro *)malloc(sizeof(struct livro));
    cab2->prox=NULL;

    struct sca *cab3=(struct sca *)malloc(sizeof(struct sca));
    cab3->prox=NULL;

    int id_automatico=1;    //usado para dar ID_aluno
    int id_livro=1;         //usado para dar ID_livro
    int qtd_alunos=0;       //quantidade de alunos presente no arquivo e no cadastro
    int qtd_livros=0;       //quantidade de livros presente no arquivo e no cadastro
    int qtd_sca=0;          //quantidade de sca presente no arquivo e no cadastro
    int escolha=0;


    for(;;){

        int menu;
        printf("Insira 1 para ir ao menu principal: ");
        scanf("%d",&menu);
        if(menu == 1){
            system("cls"); // responsavel por limpar o terminal de comando
            chama_menu();
        }
        else{
            while(menu != 1){
                printf("Valor diferente de 1\n");
                printf("Tente novamente: \n");
                scanf("%d",&menu);
            }
            system("cls");
            chama_menu();
        }

        printf("INSIRA O NUMERO DA FUNCAO QUE DESEJA UTILIZAR: ");
        scanf("%d",&escolha);

        if(escolha == 0){
            printf("\n");
            printf("PROGRAMA ENCERRADO!!\n");
            return 0;
        }

        // onde realmente ocorre a utilizacao das funcoes

        switch(escolha){

            case 1:
                printf("Opcao selecionada: adiciona_cadastro");
                printf("\n");
                system("cls");
                adiciona_cadastro(cab,&id_automatico,&qtd_alunos);  // chamada das funcoes presente no includes.h
                break;
            case 2:
                printf("Opcao selecionada: listar_cadastros");
                printf("\n");
                system("cls");
                listar_cadastros(cab);
                break;
            case 3:
                printf("Opcao selecionada: remove_cadastro");
                printf("\n");
                system("cls");
                remove_cadastro(cab,&qtd_alunos);
                break;
            case 4:
                printf("Opcao selecionada: lista_aluno");
                printf("\n");
                system("cls");
                lista_aluno(cab);
                break;

            case 5:
                printf("Opcao selecionada: adiciona_livro");
                printf("\n");
                system("cls");
                adiciona_livro(cab2,&id_livro,&qtd_livros);
                break;
            case 6:
                printf("Opcao selecionada: listar_livros");
                printf("\n");
                system("cls");
                listar_livros(cab2,cab);
                break;
            case 7:
                printf("Opcao selecionada: remove_livro");
                printf("\n");
                system("cls");
                remove_livro(cab2,&qtd_livros);
                break;
            case 8:
                printf("Opcao selecionada: lista_livro");
                printf("\n");
                system("cls");
                lista_livro(cab2,cab);
                break;
            case 9:
                printf("Opcao selecionada: altera_pendencia");
                printf("\n");
                system("cls");
                altera_pendencia(cab2,cab);
                break;
            case 10:
                printf("Opcao selecionada: lista_categoria");
                printf("\n");
                system("cls");
                lista_categoria(cab2);
                break;
            case 11:
                printf("Opcao selecionada: adiciona");
                printf("\n");
                system("cls");
                adiciona(cab3,cab,&qtd_sca);
                break;
            case 12:
                printf("Opcao selecionada: listar_sca");
                printf("\n");
                system("cls");
                listar_sca(cab3,cab);
                break;
            case 13:
                printf("Opcao selecionada: remove_sca");
                printf("\n");
                system("cls");
                remove_sca(cab3,&qtd_sca);
                break;
            case 14:
                printf("Opcao selecionada: altera_estado");
                printf("\n");
                system("cls");
                altera_estado(cab3,cab);
                break;

            case 15:
                printf("Opcao selecionada: alunos.txt");
                printf("\n");
                system("cls");
                printar_alunos(cab,&qtd_alunos,&id_automatico);
                break;

            case 16:
                printf("Opcao selecionada: livros.txt");
                printf("\n");
                system("cls");
                printar_livros(cab2,&qtd_livros,&id_livro,cab);
                break;
            case 17:
                printf("Opcao selecionada: sca.txt");
                printf("\n");
                system("cls");
                printar_sca(cab3,&qtd_sca,cab);
                break;
            case 18:
                printf("Opcao selecionada: salva no aluno.txt");
                printf("\n");
                system("cls");
                ler_aluno(cab,&qtd_alunos,&id_automatico);
                break;
            case 19:
                printf("Opcao selecionada: salva no livro.txt");
                printf("\n");
                system("cls");
                ler_livro(cab2,&qtd_livros,&id_livro);
                break;
            case 20:
                printf("Opcao selecionada: salva no sca.txt");
                printf("\n");
                system("cls");
                ler_sca(cab3,&qtd_sca);
                break;
            case 21:
                printf("Opcao selecionada: cripto ou decripto alunos.txt");
                printf("\n");
                system("cls");
                criptografa_descriptografa_alunos(cab,&qtd_alunos,&id_automatico);
                break;
            case 22:
                printf("Opcao selecionada: cripto ou decripto livros.txt");
                printf("\n");
                system("cls");
                criptografa_descriptografa_livros(cab2,&qtd_livros,&id_livro);
                break;
            case 23:
                printf("Opcao selecionada: cripto ou decripto sca.txt");
                printf("\n");
                system("cls");
                criptografa_descriptografa_sca(cab3,&qtd_sca);
                break;
            default:
                printf("\n");
                printf("OPCAO INVALIDA!!\n");
                printf("\n");
                break;
        }

    }

    //-------- agora deve-se liberar as memorias utilizadas ----------

    struct aluno *ant1=cab;
    struct aluno *p1=cab->prox; //acessando as listas criadas

    while(p1 != NULL){ // percorre a lista ate o ultimo nó,ate o ponteiro apontar para nulo

        ant1=p1;
        p1=p1->prox;    // manipulacao dos nós
        free(ant1);     // liberando o nó que se encontra

    }

    free(p1);

    struct livro *ant2=cab2;
    struct livro *p2=cab2->prox;

    while(p2 != NULL){

        ant2=p2;
        p2=p2->prox;
        free(ant2);

    }

    free(p2);

    struct sca *ant3=cab3;
    struct sca *p3=cab3->prox;

    while(p3 != NULL){

        ant3=p3;
        p3=p3->prox;
        free(ant3);

    }

    free(p3);

    // ------- liberando a memoria dos auxiliares alocados no inicio da main ---------

    free(cab);
    free(cab2);
    free(cab3);

    return 0;   // retornando 0 apenas para indicar o fim do programa
}
