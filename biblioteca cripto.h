#ifndef BIBLIOTECA_CRIPTO_H_INCLUDED
#define BIBLIOTECA_CRIPTO_H_INCLUDED

void criptografa_descriptografa_alunos(struct aluno *cab,int *qtd_alunos,int *id_automatico); // funcao responsavel por criptografar e descriptografar as informacoes presente no arquivo alunos.txt
void criptografa_descriptografa_livros(struct livro *cab,int *qtd_livros,int *id_livros);   // funcao responsavel por criptografar e descriptografar as informacoes presente no arquivo livros.txt
void criptografa_descriptografa_sca(struct sca *cab,int *qtd_sca);  // funcao responsavel por criptografar e descriptografar as informacoes presente no arquivo sca.txt

#endif // BIBLIOTECA_CRIPTO_H_INCLUDED
