#include "includes.h"
#include "biblioteca cripto.h"

char mensagem[100]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

//COLOCAR CRIPTORAFIA PARA NUMEROS

void criptografa_descriptografa_alunos(struct aluno *cab,int *qtd_alunos,int *id_automatico){
    int opcao;
    printf("Insira 1 para criptografar o arquivo alunos.txt ou 2 para descriptografar o mesmo: ");
    scanf("%d",&opcao);
    int rot;
    if(opcao == 1){

//---------------- encriptando---------------

        printf("Insira a quantidade de rotacoes para a realizacao dos procesos: ");
        scanf("%d",&rot);

        FILE *file; // ponteiro para o arquivo
        file=fopen("alunos.txt","r"); // abrino arquivo no modo leitura "read"

        if(file != NULL){

            if( !filelength( fileno( file ) ) ){ // teste para saber se o tamanho do arquivo e zero
                printf("Arquivo esta vazio\n");
                fclose(file);
                return;
            }

            else{

            struct aluno *p;
            struct aluno *ant=cab;  //declarando os ponteiros da struct

            char *aux; //utilizar para a leitura da linha com o getline
            size_t tamanho=1; //muda o tamanho, passa o endereco no getline
            aux=(char *)malloc(sizeof(char)); // devo alocar o ponteito dinamicamente
            getline(&aux,&tamanho,file);
            (*qtd_alunos)=atoi(aux);    //funcao atoi transforma string em inteiro

            int qtd=(*qtd_alunos);//variavel so para nao mexer diretamente na quantidade de alunos
            char x,y; //armazenar os caracteres

            while(qtd != 0){

                p=ant->prox;
                p=(struct aluno *)malloc(sizeof(struct aluno));   //manipulacao dos ponteiros para a manipulacao correta dos nós
                ant->prox=p;

                getline(&aux,&tamanho,file);
                strcpy(p->nome,aux);
                p->nome[strcspn(p->nome,"\n")]=0; //retirar o \n que foi copiado do getline

                for(int i=0;p->nome[i] != '\0';i++){//percorrendo a string
                    x=p->nome[i];
                    if(x >= 'a' && x <= 'z'){ // verificacao se sao letras validas
                        x=x+rot;    // criptografando...
                        if(x > 'z'){
                            x=x-'z' + 'a'-1;
                        }
                        p->nome[i]=x;
                    }
                }

                getline(&aux,&tamanho,file);
                p->matricula=atoi(aux);

                getline(&aux,&tamanho,file);
                p->ID_aluno=atoi(aux);

                getline(&aux,&tamanho,file);
                p->pendencia=atoi(aux);

                p->prox=NULL;
                ant=p;

                qtd=qtd-1;
            }

            getline(&aux,&tamanho,file);
            (*id_automatico)=atoi(aux);
        }
        printf("Arquivo criptografado com sucesso\n");
        fclose(file);
    }

    //-------printar os novos valores criptografados dentro do arquivo alunos.txt-------

    FILE *file2;
    file2=fopen("alunos.txt","w"); // abrindo no modo de escrita "write"
    struct aluno *p=cab->prox;
    fprintf(file,"%d\n",*qtd_alunos); // pritando dentro do arquivo a quantidade de alunos cadastrados

    while(p != NULL){

        fprintf(file,"%s\n",p->nome); // nome criptografado
        fprintf(file,"%d\n",p->matricula);
        fprintf(file,"%d\n",p->ID_aluno);
        fprintf(file,"%d\n",p->pendencia);

        p=p->prox;
    }

    fprintf(file,"%d\n",*id_automatico);
    fclose(file2);
    }

    //------------decriptacao------------------


    if(opcao == 2){

    printf("Insira a quantidade de rotacoes utilizada na criptografia: ");
    scanf("%d",&rot);

    FILE *file;
    file=fopen("alunos.txt","r");

    if(file != NULL){

        if( !filelength( fileno( file ) ) ){ // teste para saber se o conteudo do arquivo é nulo
            printf("Arquivo esta vazio\n");
            fclose(file);
            return;
        }

        else{

            struct aluno *p;
            struct aluno *ant=cab;  //declarando os ponteiros da struct

            char *aux; //utilizar para a leitura da linha com o getline
            size_t tamanho=1; //muda o tamanho, passa o endereco no getline
            aux=(char *)malloc(sizeof(char)); // devo alocar o ponteito dinamicamente
            getline(&aux,&tamanho,file);
            (*qtd_alunos)=atoi(aux);

            int qtd=(*qtd_alunos);//variavel so para nao mexer diretamente na quantidade de alunos
            char x,y; //armazenar os caracteres

            while(qtd != 0){

                p=ant->prox;
                p=(struct aluno *)malloc(sizeof(struct aluno));     //manipulacao dos ponteiros para a manipulacao correta dos nós
                ant->prox=p;

                getline(&aux,&tamanho,file);
                strcpy(p->nome,aux);
                p->nome[strcspn(p->nome,"\n")]=0; //retirar o \n que foi copiado do getline

                for(int i=0;p->nome[i] != '\0';i++){//percorrendo a string
                    x=p->nome[i];
                    if(x >= 'a' && x <= 'z'){
                        x=x-rot;        // decriptografando...
                        if(x < 'a'){
                            x=x+'z' - 'a'+1;
                        }
                        p->nome[i]=x;
                    }
                    p->nome[i]=x;
                }

                getline(&aux,&tamanho,file);
                p->matricula=atoi(aux);

                getline(&aux,&tamanho,file);
                p->ID_aluno=atoi(aux);

                getline(&aux,&tamanho,file);
                p->pendencia=atoi(aux);

                p->prox=NULL;
                ant=p;

                qtd=qtd-1;
            }
            getline(&aux,&tamanho,file);
            (*id_automatico)=atoi(aux);
        }
        printf("Arquivo decriptografado com sucesso\n");
        fclose(file);
    }

 //-------printar os novos valores decriptografados dentro do arquivo alunos.txt-------

    FILE *file2;
    file2=fopen("alunos.txt","w"); // abrindo no modo de escrita
    struct aluno *p=cab->prox;
    fprintf(file,"%d\n",*qtd_alunos);

    while(p != NULL){

        fprintf(file,"%s\n",p->nome); // nome decriptografado
        fprintf(file,"%d\n",p->matricula);
        fprintf(file,"%d\n",p->ID_aluno);
        fprintf(file,"%d\n",p->pendencia);

        p=p->prox;
    }

    fprintf(file,"%d\n",*id_automatico);
    fclose(file2);
    }

}

void criptografa_descriptografa_livros(struct livro *cab,int *qtd_livros,int *id_livros){

    int opcao;
    printf("Insira 1 para criptografar o arquivo livros.txt ou 2 para descriptografar o mesmo: ");
    scanf("%d",&opcao);
    int rot;
    if(opcao == 1){

//---------------- encriptando---------------

        printf("Insira a quantidade de rotacoes para a realizacao dos procesos: ");
        scanf("%d",&rot);

        FILE *file;
        file=fopen("livros.txt","r");

        if(file != NULL){

            if( !filelength( fileno( file ) ) ){
                printf("Arquivo esta vazio\n");
                fclose(file);
                return;
            }

            else{

            struct livro *p;
            struct livro *ant=cab;  //declarando os ponteiros da struct

            char *aux; //utilizar para a leitura da linha com o getline
            size_t tamanho=1; //muda o tamanho, passa o endereco no getline
            aux=(char *)malloc(sizeof(char)); // devo alocar o ponteito dinamicamente
            getline(&aux,&tamanho,file);
            (*qtd_livros)=atoi(aux);

            int qtd=(*qtd_livros);//variavel so para nao mexer diretamente na quantidade de alunos
            char x,y; //armazenar os caracteres

            while(qtd != 0){

                p=ant->prox;
                p=(struct livro *)malloc(sizeof(struct livro));     //manipulacao dos ponteiros para a manipulacao correta dos nós
                ant->prox=p;

                getline(&aux,&tamanho,file);
                strcpy(p->nome,aux);
                p->nome[strcspn(p->nome,"\n")]=0; //retirar o \n que foi copiado do getline

                for(int i=0;p->nome[i] != '\0';i++){//percorrendo a string
                    x=p->nome[i];
                    if(x >= 'a' && x <= 'z'){
                        x=x+rot;
                        if(x > 'z'){
                            x=x-'z' + 'a'-1; // para evitar repeticoes na criptografia
                        }
                        p->nome[i]=x;
                    }
                }

                getline(&aux,&tamanho,file);
                strcpy(p->categoria,aux);
                p->categoria[strcspn(p->categoria,"\n")]=0;

                for(int i=0;p->categoria[i] != '\0';i++){
                    x=p->categoria[i];
                    if(x >= 'a' && x <= 'z'){
                        x=x+rot;
                        if(x > 'z'){
                            x=x-'z' + 'a'-1;
                        }
                        p->categoria[i]=x;
                    }
                }

                getline(&aux,&tamanho,file);
                p->ID_livro=atoi(aux);

                getline(&aux,&tamanho,file);
                p->ano_de_publicacao=atoi(aux);

                getline(&aux,&tamanho,file);
                p->estado=atoi(aux);

                p->prox=NULL;
                ant=p;

                qtd=qtd-1;
            }

            getline(&aux,&tamanho,file);
            (*id_livros)=atoi(aux);
        }
        printf("Arquivo criptografado com sucesso\n");
        fclose(file);
    }

    //-------printar os novos valores criptografados dentro do arquivo livros.txt-------

    FILE *file2;
    file2=fopen("livros.txt","w"); // abrindo no modo de escrita
    struct livro *p=cab->prox;
    fprintf(file,"%d\n",*qtd_livros); // pritando dentro do arquivo a quantidade de alunos cadastrados

    while(p != NULL){

        fprintf(file,"%s\n",p->nome); // nome criptografado
        fprintf(file,"%s\n",p->categoria); // categoria criptografada
        fprintf(file,"%d\n",p->ID_livro);
        fprintf(file,"%d\n",p->ano_de_publicacao);
        fprintf(file,"%d\n",p->estado);

        p=p->prox;
    }

    fprintf(file,"%d\n",*id_livros);
    fclose(file2);
    }

    //------------decriptacao------------------


    if(opcao == 2){

    printf("Insira a quantidade de rotacoes utilizada na criptografia: ");
    scanf("%d",&rot);

    FILE *file;
    file=fopen("livros.txt","r");

    if(file != NULL){

        if( !filelength( fileno( file ) ) ){ // teste para saber se o tamanho do arquivo e zero
            printf("Arquivo esta vazio\n");
            fclose(file);
            return;
        }

        else{

            struct livro *p;
            struct livro *ant=cab;  //declarando os ponteiros da struct

            char *aux; //utilizar para a leitura da linha com o getline
            size_t tamanho=1; //muda o tamanho, passa o endereco no getline
            aux=(char *)malloc(sizeof(char)); // devo alocar o ponteito dinamicamente
            getline(&aux,&tamanho,file);
            (*qtd_livros)=atoi(aux);

            int qtd=(*qtd_livros);//variavel so para nao mexer diretamente na quantidade de alunos
            char x,y; //armazenar os caracteres

            while(qtd != 0){

                p=ant->prox;
                p=(struct livro *)malloc(sizeof(struct livro));     //manipulacao dos ponteiros para a manipulacao correta dos nós
                ant->prox=p;

                getline(&aux,&tamanho,file);
                strcpy(p->nome,aux);
                p->nome[strcspn(p->nome,"\n")]=0; //retirar o \n que foi copiado do getline

                for(int i=0;p->nome[i] != '\0';i++){//percorrendo a string
                    x=p->nome[i];
                    if(x >= 'a' && x <= 'z'){
                        x=x-rot;
                        if(x < 'a'){
                            x=x+'z' - 'a'+1;
                        }
                        p->nome[i]=x;
                    }
                    p->nome[i]=x;
                }

                getline(&aux,&tamanho,file);
                strcpy(p->categoria,aux);
                p->categoria[strcspn(p->categoria,"\n")]=0;

                for(int i=0;p->categoria[i] != '\0';i++){
                    x=p->categoria[i];
                    if(x >= 'a' && x <= 'z'){
                        x=x-rot;
                        if(x < 'a'){
                            x=x+'z' - 'a'+1;
                        }
                        p->categoria[i]=x;
                    }
                    p->categoria[i]=x;
                }

                getline(&aux,&tamanho,file);
                p->ID_livro=atoi(aux);

                getline(&aux,&tamanho,file);
                p->ano_de_publicacao=atoi(aux);

                getline(&aux,&tamanho,file);
                p->estado=atoi(aux);

                p->prox=NULL;
                ant=p;

                qtd=qtd-1;
            }
            getline(&aux,&tamanho,file);
            (*id_livros)=atoi(aux);
        }
        printf("Arquivo decriptografado com sucesso\n");
        fclose(file);
    }

 //-------printar os novos valores decriptografados dentro do arquivo livros.txt-------

    FILE *file2;
    file2=fopen("livros.txt","w"); // abrindo no modo de escrita
    struct livro *p=cab->prox;
    fprintf(file,"%d\n",*qtd_livros);

    while(p != NULL){

        fprintf(file,"%s\n",p->nome);
        fprintf(file,"%s\n",p->categoria);
        fprintf(file,"%d\n",p->ID_livro);
        fprintf(file,"%d\n",p->ano_de_publicacao);
        fprintf(file,"%d\n",p->estado);


        p=p->prox;
    }

    fprintf(file,"%d\n",*id_livros);
    fclose(file2);
    }

}

void criptografa_descriptografa_sca(struct sca *cab,int *qtd_sca){

    int opcao;
    printf("Insira 1 para criptografar o arquivo sca.txt ou 2 para descriptografar o mesmo: ");
    scanf("%d",&opcao);
    int rot;
    if(opcao == 1){

//---------------- encriptando---------------

        printf("Insira a quantidade de rotacoes para a realizacao dos procesos: ");
        scanf("%d",&rot);

        FILE *file;
        file=fopen("sca.txt","r");

        if(file != NULL){

            if( !filelength( fileno( file ) ) ){
                printf("Arquivo esta vazio\n");
                fclose(file);
                return;
            }

            else{

            struct sca *p;
            struct sca *ant=cab;  //declarando os ponteiros da struct

            char *aux; //utilizar para a leitura da linha com o getline
            size_t tamanho=1; //muda o tamanho, passa o endereco no getline
            aux=(char *)malloc(sizeof(char)); // devo alocar o ponteito dinamicamente
            getline(&aux,&tamanho,file);
            (*qtd_sca)=atoi(aux);

            int qtd=(*qtd_sca);//variavel so para nao mexer diretamente na quantidade de alunos
            char x,y; //armazenar os caracteres

            while(qtd != 0){

                p=ant->prox;
                p=(struct sca *)malloc(sizeof(struct sca));     //manipulacao dos ponteiros para a manipulacao correta dos nós
                ant->prox=p;

                getline(&aux,&tamanho,file);
                strcpy(p->tipo,aux);
                p->tipo[strcspn(p->tipo,"\n")]=0; //retirar o \n que foi copiado do getline

                for(int i=0;p->tipo[i] != '\0';i++){//percorrendo a string
                    x=p->tipo[i];
                    if(x >= 'a' && x <= 'z'){
                        x=x+rot;
                        if(x > 'z'){
                            x=x-'z' + 'a'-1;
                        }
                        p->tipo[i]=x;
                    }
                }

                getline(&aux,&tamanho,file);
                p->ID_sca=atoi(aux);

                getline(&aux,&tamanho,file);
                p->estado=atoi(aux);

                p->prox=NULL;
                ant=p;

                qtd=qtd-1;
            }
        }
        printf("Arquivo criptografado com sucesso\n");
        fclose(file);
    }

    //-------printar os novos valores criptografados dentro do arquivo sca.txt-------

    FILE *file2;
    file2=fopen("sca.txt","w");
    struct sca *p=cab->prox;
    fprintf(file,"%d\n",*qtd_sca);

    while(p != NULL){

        fprintf(file,"%s\n",p->tipo);
        fprintf(file,"%d\n",p->ID_sca);
        fprintf(file,"%d\n",p->estado);

        p=p->prox;
    }

    fclose(file2);

    }

    //------------decriptacao------------------


    if(opcao == 2){

    printf("Insira a quantidade de rotacoes utilizada na criptografia: ");
    scanf("%d",&rot);

    FILE *file;
    file=fopen("sca.txt","r");

    if(file != NULL){

        if( !filelength( fileno( file ) ) ){ // teste para saber se o tamanho do arquivo e zero
            printf("Arquivo esta vazio\n");
            fclose(file);
            return;
        }

        else{

            struct sca *p;
            struct sca *ant=cab;  //declarando os ponteiros da struct

            char *aux; //utilizar para a leitura da linha com o getline
            size_t tamanho=1; //muda o tamanho, passa o endereco no getline
            aux=(char *)malloc(sizeof(char)); // devo alocar o ponteito dinamicamente
            getline(&aux,&tamanho,file);
            (*qtd_sca)=atoi(aux);

            int qtd=(*qtd_sca);//variavel so para nao mexer diretamente na quantidade de alunos
            char x,y; //armazenar os caracteres

            while(qtd != 0){

                p=ant->prox;
                p=(struct sca *)malloc(sizeof(struct sca));     //manipulacao dos ponteiros para a manipulacao correta dos nós
                ant->prox=p;

                getline(&aux,&tamanho,file);
                strcpy(p->tipo,aux);
                p->tipo[strcspn(p->tipo,"\n")]=0; //retirar o \n que foi copiado do getline

                for(int i=0;p->tipo[i] != '\0';i++){//percorrendo a string
                    x=p->tipo[i];
                    if(x >= 'a' && x <= 'z'){
                        x=x-rot;  // decriptografando...
                        if(x < 'a'){
                            x=x+'z' - 'a'+1;
                        }
                        p->tipo[i]=x;
                    }
                    p->tipo[i]=x;
                }

                getline(&aux,&tamanho,file);
                p->ID_sca=atoi(aux);

                getline(&aux,&tamanho,file);
                p->estado=atoi(aux);

                p->prox=NULL;
                ant=p;

                qtd=qtd-1;
            }
        }
        printf("Arquivo decriptografado com sucesso\n");
        fclose(file);

    }

 //-------printar os novos valores decriptografados dentro do arqvio sca.txt-------

    FILE *file2;
    file2=fopen("sca.txt","w");
    struct sca *p=cab->prox;
    fprintf(file,"%d\n",*qtd_sca);

    while(p != NULL){

        fprintf(file,"%s\n",p->tipo);
        fprintf(file,"%d\n",p->ID_sca);
        fprintf(file,"%d\n",p->estado);

        p=p->prox;
    }
    fclose(file2);

    }
}
