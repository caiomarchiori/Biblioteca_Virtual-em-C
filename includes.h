#ifndef INCLUDES_H_INCLUDED
#define INCLUDES_H_INCLUDED

/*biblioteca que possui todos as bibliotecas usadas nas funcoes do programa\
alem de conter todas as structs utilizadas, a fim de utilizar sempre a original, e nao sua copia*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aluno{
    char nome[101];
    int matricula;
    int ID_aluno;
    int pendencia;
    struct aluno *prox;
};
struct livro{
    char nome[101];
    int ano_de_publicacao;
    char categoria[50];
    int ID_livro;
    int estado;
    int ID_aluno;
    struct livro *prox;
};
struct sca{
    int ID_sca;
    char tipo[15];
    int estado;
    int ID_aluno;
    struct sca *prox;
};

#endif // INCLUDES_H_INCLUDED
