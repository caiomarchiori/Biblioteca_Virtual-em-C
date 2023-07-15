#ifndef BIBLIOTECA_SCA_H_INCLUDED
#define BIBLIOTECA_SCA_H_INCLUDED

void adiciona(struct sca *cab, struct aluno *cab2,int *qtd_sca);    //funcao que proporciona ao usuario a insercao de um novo cadastro dos tipos disponiveis
struct sca *busca_cadastro_sca(struct sca *cab,int id,struct sca **ant);    //funcao que realiza a busca algum ID_sca ja cadastrado pelo ususario, independente do tipo escolhido
void listar_sca(struct sca *cab,struct aluno *cab2);    //funcao que lista TODOS os cadastros realizados, tambem independente do tipo escolhido
void remove_sca(struct sca *cab,int *qtd_sca);  //funcao que remove algum cadastro/desfaz o no onde esta presente o ID_sca inserido pelo ususario
void altera_estado(struct sca *cab,struct aluno *cab2); // funcao que tambem proporciona ao usuario fazer emprestimos dos tipos disponiveis para qualqer aluno presente no cadastro

#endif // BIBLIOTECA_SCA_H_INCLUDED
