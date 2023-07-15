#ifndef BIBLIOTECA_LIVROS_H_INCLUDED
#define BIBLIOTECA_LIVROS_H_INCLUDED

void adiciona_livro(struct livro *cab,int *id,int *qtd_livros); // funcao responsavel por cadastras novos livros inseridos pelo usuario/criacao de novos nos
void listar_livros(struct livro *cab,struct aluno *cab2);   //funcao que lista TODOS os livros presentes no cadastro e seus atributos para  o usuaro
struct livro *busca_livro(struct livro *cab,int id,struct livro **ant); //funcao "auxiliar" para verificar a existencia ou nao de ID_livro previamente cadastrado
void remove_livro(struct livro *cab,int *qtd_livros);   //funcao que remove qualqer livro do cadastro, removendo o no presente que contem o ID_livro inserido pelo usuario
void lista_livro(struct livro *cab,struct aluno *cab2); //funcao que lista apenas o livro e seus atributos que o usuario inseriu por meio de se ID_livro
void altera_pendencia(struct livro *cab,struct aluno *cab2);    //funcao que permite que qualquer aluno "alugue" o livro escolhido pelo usuario. Ou seja, e possivel pegar e devolver o livro
void lista_categoria(struct livro *cab);    //funcao que lista para o ususario apenas os livros presentes na categoria desejada

#endif // BIBLIOTECA_LIVROS_H_INCLUDED
