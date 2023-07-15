#include "includes.h"
#include "biblioteca alunos.h"
#include "biblioteca livros.h"
#include "biblioteca sca.h"

void printar_alunos(struct aluno *cab,int *qtd_alunos,int *id_automatico){

    FILE *file;
    file=fopen("alunos.txt","w");//escrever no arqivo

    if(file == NULL){
        printf("Arquivo nao foi encontrado");
        return;
    }

    if(cab->prox == NULL){
        printf("Lista vazia\n"); // printando no console, nao no arquivo
        printf("Nao existe alunos inseridos\n");
        return;
    }

    struct aluno *p=cab->prox;
    fprintf(file,"%d\n",*qtd_alunos); // pritando dentro do arquivo a quantidade de alunos cadastrados

    while(p != NULL){

        fprintf(file,"%s\n",p->nome);
        fprintf(file,"%d\n",p->matricula);
        fprintf(file,"%d\n",p->ID_aluno);
        fprintf(file,"%d\n",p->pendencia);

        p=p->prox;
    }

    fprintf(file,"%d\n",*id_automatico);
    printf("Exportado para o arquivo com sucesso!!\n");
    fclose(file);
}

void printar_livros(struct livro *cab,int *qtd_livros,int *id_livro,struct aluno *cab2){

    FILE *file;
    file=fopen("livros.txt","w");

    if(file == NULL){
        printf("Arquivo nao foi encontrado");
        return;
    }

    if(cab->prox == NULL){
        printf("Lista vazia\n"); // printando no console, nao no arquivo
        printf("Nao existe livros inseridos\n");
        return;
    }

    struct livro *p=cab->prox;
    fprintf(file,"%d\n",*qtd_livros);

    while(p != NULL){

        fprintf(file,"%s\n",p->nome);
        fprintf(file,"%s\n",p->categoria);
        fprintf(file,"%d\n",p->ID_livro);
        fprintf(file,"%d\n",p->ano_de_publicacao);
        fprintf(file,"%d\n",p->estado);
        if(p->estado == 0){ //emprestado
            struct aluno *ant=NULL;
            struct aluno *ptr=busca_ID(cab2,p->ID_aluno,&ant);
            fprintf(file,"%d\n",ptr->ID_aluno); // colocar dentro do arquivo o aluno
        }

        p=p->prox;
    }

    fprintf(file,"%d\n",*id_livro);
    printf("Exportado para o arquivo com sucesso!!\n");
    fclose(file);
}

void printar_sca(struct sca *cab,int *qtd_sca,struct aluno *cab2){ // verificar se o estado for 0 ver pra qual aluno ele ta emprestado

    // n usa id, pois nesse caso o usuario digita

    FILE *file;
    file=fopen("sca.txt","w");

    if(file == NULL){
        printf("Arquivo nao foi encontrado");
        return;
    }

    if(cab->prox == NULL){
        printf("Lista vazia\n"); // printando no console, nao no arquivo
        printf("Nao existe Salas,Computadores ou Armarios cadastrados\n");
        return;
    }

    struct sca *p=cab->prox;
    fprintf(file,"%d\n",*qtd_sca);

    while(p != NULL){

        fprintf(file,"%s\n",p->tipo);
        fprintf(file,"%d\n",p->ID_sca);
        fprintf(file,"%d\n",p->estado);
        if(p->estado == 0){//tem algum aluno com ele
            //verificar qual aluno esta cm ele
            struct aluno *ant=NULL;
            struct aluno *ptr=busca_ID(cab2,p->ID_aluno,&ant);
            fprintf(file,"%d\n",ptr->ID_aluno); // colocar dentro do arquivo o aluno
        }

        p=p->prox;
    }

    //nao printamos o id, pois nesse caso o usuario que gera o ID
    printf("Exportado para o arquivo com sucesso!!\n");
    fclose(file);
}

void ler_aluno(struct aluno *cab,int *qtd_alunos,int *id_automatico){

    FILE *file;
    file=fopen("alunos.txt","r");//ler do arquivo

    if(file != NULL){

        if( !filelength( fileno( file ) ) ){ // teste para saber se o tamanho do arquivo e zero
            printf("Arquivo esta vazio\n");
            fclose(file);
            return;
        }

        else{

            char *aux; //utilizar para a leitura da linha com o getline
            size_t tamanho=1; //muda o tamanho, passa o endereco no getline
            aux=(char *)malloc(sizeof(char)); // devo alocar o ponteito dinamicamente

            getline(&aux,&tamanho,file);
            (*qtd_alunos)=atoi(aux);
            int qtd=(*qtd_alunos);
            printf("Arquivo possui %d aluno(s)\n",(*qtd_alunos));

            struct aluno *p;
            struct aluno *ant=cab;  //declarando os ponteiros da struct

            while(qtd != 0){

                p=ant->prox;
                p=(struct aluno *)malloc(sizeof(struct aluno));     //manipulacao dos ponteiros para a manipulacao correta dos nós
                ant->prox=p;

                getline(&aux,&tamanho,file);
                strcpy(p->nome,aux);
                p->nome[strcspn(p->nome,"\n")]=0; //retirar o \n que foi copiado do getline

                getline(&aux,&tamanho,file);
                p->matricula=atoi(aux);

                getline(&aux,&tamanho,file);
                p->ID_aluno=atoi(aux);

                getline(&aux,&tamanho,file);
                p->pendencia=atoi(aux);

                p->prox=NULL;
                ant=p;              //atualizando os ponteiros, fazendo com que consiga ler/imprimir os proximos alunos que o usuario queira

                qtd=qtd-1;
            }

            getline(&aux,&tamanho,file);
            (*id_automatico)=atoi(aux);
        }
        printf("Importado do arquivo com sucesso!!\n");
        fclose(file);
    }

    else{
        printf("Arquivo nao foi encontrado\n");
        return;
    }
}

void ler_livro(struct livro *cab,int *qtd_livros,int *id_livro){

    FILE *file;
    file=fopen("livros.txt","r");//ler do arquivo

    if(file != NULL){

        if( !filelength( fileno( file ) ) ){ // teste para saber se o tamanho do arquivo e zero
            printf("Arquivo esta vazio\n");
            fclose(file);
            return;
        }

        else{

            char *aux; //utilizar para a leitura da linha com o getline
            size_t tamanho=1; //muda o tamanho, passa o endereco no getline

            aux=(char *)malloc(sizeof(char)); // devo alocar o ponteito dinamicamente

            getline(&aux,&tamanho,file);
            (*qtd_livros)=atoi(aux);
            int qtd=(*qtd_livros);
            printf("Arquivo possui %d livro(s)\n",(*qtd_livros));


            struct livro *p;
            struct livro *ant=cab;  //declarando os ponteiros da struct

            while(qtd != 0){

                p=ant->prox;
                p=(struct livro *)malloc(sizeof(struct livro));     //manipulacao dos ponteiros para a manipulacao correta dos nós
                ant->prox=p;

                getline(&aux,&tamanho,file);
                strcpy(p->nome,aux);
                p->nome[strcspn(p->nome,"\n")]=0; //retirar o \n que foi copiado do getline

                getline(&aux,&tamanho,file);
                strcpy(p->categoria,aux);
                p->categoria[strcspn(p->categoria,"\n")]=0;

                getline(&aux,&tamanho,file);
                p->ID_livro=atoi(aux);

                getline(&aux,&tamanho,file);
                p->ano_de_publicacao=atoi(aux);

                getline(&aux,&tamanho,file);
                p->estado=atoi(aux);

                if(p->estado == 0){ //sugnifica que ele esta emprestado
                   getline(&aux,&tamanho,file); // ler o id do aluno
                   p->ID_aluno=atoi(aux);
                }


                p->prox=NULL;
                ant=p;              //atualizando os ponteiros, fazendo com que consiga ler/imprimir os proximos livros que o usuario queira

                qtd=qtd-1;
            }

            fscanf(file,"%d\n",&(*id_livro));
        }

        printf("Importado do arquivo com sucesso!!\n");
        fclose(file);
    }

    else{
        printf("Arquivo nao foi encontrado\n");
        return;
    }
}

void ler_sca(struct sca *cab,int *qtd_sca){ // verificar se o estado for 0 ver pra qual aluno ele ta emprestado

    FILE *file;
    file=fopen("sca.txt","r");//ler do arquivo

    if(file != NULL){

        if( !filelength( fileno( file ) ) ){ // teste para saber se o tamanho do arquivo e zero
            printf("Arquivo esta vazio\n");
            fclose(file);
            return;
        }

        else{

            char *aux; //utilizar para a leitura da linha com o getline
            size_t tamanho=1; //muda o tamanho, passa o endereco no getline

            aux=(char *)malloc(sizeof(char)); // devo alocar o ponteito dinamicamente

            getline(&aux,&tamanho,file);
            (*qtd_sca)=atoi(aux);
            int qtd=(*qtd_sca);
            printf("Arquivo possui %d cadastro(s)\n",(*qtd_sca));


            struct sca *p;
            struct sca *ant=cab;  //declarando os ponteiros da struct

            while(qtd != 0){

                p=ant->prox;
                p=(struct sca *)malloc(sizeof(struct sca));     //manipulacao dos ponteiros para a manipulacao correta dos nós
                ant->prox=p;

                getline(&aux,&tamanho,file);
                strcpy(p->tipo,aux); // p->tipo recebe uma copia do char aux
                p->tipo[strcspn(p->tipo,"\n")]=0; //retirar o \n que foi copiado do getline

                getline(&aux,&tamanho,file);
                p->ID_sca=atoi(aux); //atoi,funcoa que transforma char em inteiro

                getline(&aux,&tamanho,file);
                p->estado=atoi(aux);
                if(p->estado == 0){
                    getline(&aux,&tamanho,file); // ler o id do aluno
                    p->ID_aluno=atoi(aux);
                }

                p->prox=NULL;
                ant=p;              //atualizando os ponteiros, fazendo com que consiga ler/imprimir os proximos livros que o usuario queira

                qtd=qtd-1;
            }
        }

        printf("Importado do arquivo com sucesso!!\n");
        fclose(file);
    }

    else{
        printf("Arquivo nao foi encontrado\n");
        return;
    }
}
