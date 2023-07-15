#ifndef BIBLIOTECA_ARQUIVOS_H_INCLUDED
#define BIBLIOTECA_ARQUIVOS_H_INCLUDED

void printar_alunos(struct aluno *cab,int *qtd_alunos,int *id_automatico);  // funcao responsavel por inserir as informacoes da lista encadeada de alunos no arquivo vazio previamente criado (alunos.txt)
void printar_livros(struct livro *cab,int *qtd_livros,int *id_livro,struct aluno *cab2);    // funcao responsavel por inserir as informacoes da lista encadeada de livros no arquivo vazio previamente criado (livros.txt)
void printar_sca(struct sca *cab,int *qtd_sca,struct aluno *cab2);  // funcao responsavel por inserir as informacoes da lista encadeada de sca no arquivo vazio previamente criado (sca.txt)
void ler_aluno(struct aluno *cab,int *qtd_alunos,int *id_automatico);   // funcao responsavel por importar as informacoes presentes nos respectivos arquivos.txt para a lista encadeada
void ler_livro(struct livro *cab,int *qtd_livros,int *id_livro);    // funcao responsavel por importar as informacoes presentes nos respectivos arquivos.txt para a lista encadeada
void ler_sca(struct sca *cab,int *qtd_sca); // funcao responsavel por importar as informacoes presentes nos respectivos arquivos.txt para a lista encadeada

#endif // BIBLIOTECA_ARQUIVOS_H_INCLUDED
