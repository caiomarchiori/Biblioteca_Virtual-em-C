#ifndef BIBLIOTECA_ALUNOS_H_INCLUDED
#define BIBLIOTECA_ALUNOS_H_INCLUDED

void listar_cadastros(struct aluno *cab);   //funcao e utilizada para fazer a listagem de TODOS os alunos cadastrados, juntamente com seus atributos ate o usuario chama-la
struct aluno *busca_cadastro(struct aluno *cab,int matricula,struct aluno **ant); // funcao "auxiliar" para buscar se a matricula que o usuario/funcao necessita esta presente ou nao no casdastro
void adiciona_cadastro(struct aluno *cab,int *id,int *qtd_alunos); // funcao que realiza a insercao de um novo cadastro/cria um novo no com as informacoes inseridas pelo ususario
void remove_cadastro(struct aluno *cab, int *qtd_alunos);   //funcao que e responsavel por remover um no da minha lista, ou seja, deleta o no que o ID_aluno inserido pelo usuario se encontra
void lista_aluno(struct aluno *cab);    // funcao que lista os atributos de um unico aluno, o ususario necessita apenas inserir a matricula que deseja saber
struct aluno *busca_ID(struct aluno *cab,int id,struct aluno **ant);    //funcao "auxiliar" para a busca de ID_aluno existente ou nao nos cadastros

#endif // BIBLIOTECA_ALUNOS_H_INCLUDED
