# Trabalho 3 - Indexação e Tabela Hash

- **Aluno:** Paulo Victor Fernandes de Melo
- **Aluno:** João Luiz Rodrigues da Silva
- **Aluna:** Rebecca Aimée Lima de Lima
- **Aluna:** Beatriz Jacaúna Martins

# Estrutura

O diretório do projeto segue a seguinte estrutura.

```
out/                Pasta de saída dos executáveis gerados pelo GCC.
src/                Pasta contendo o código do trabalho.
doc/                Pasta contendo o documento final, com as tabelas e gráficos.
.gitignore          Lista de arquivos removidos do envio para o GitHub.
Makefile            Instruções para build do arquivo, leia mais abaixo.
README.md           O arquivo que você está lendo agora.
```

Os códigos relevantes ao trabalho devem ser armazenados na pasta `src`, e os executáveis gerados pelo GCC irão para o `out`. Os conteúdos da pasta `out` são filtrados para **não serem enviados** ao GitHub pelo arquivo chamado `.gitignore`.

Ao executar o código do trabalho, o programa irá gerar alguns arquivos com a extensão `.csv`, contendo os dados de cada questão. Os dados usados no documento final do trabalho podem ser encontrados na pasta `out/csv-final/`.

# Como buildar

Ao baixar o projeto no computador, abra um terminal na pasta do projeto e execute o comando `make`. Isso executará todos os comandos do `gcc` necessários para buildar os executáveis do trabalho, que estarão na pasta `out`.

# Atividades

## Qualquer um
- [ ] Criação do arquivo

## Todos
- [ ] Inserção nos tipos de dados

## Rebeca
- [ ] Função de busca múltipla na árvore binária
- [ ] Busca na árvore binária por atributo não-chave (>, <, >=, <=)

## João
- [ ] Busca por atributo chave na árvore binária

## Bea
- [ ] Busca sequencial direto no arquivo por atributo chave
- [ ] Busca sequencial direto no arquivo por atributo não-chave

## Paulo
- [ ] Implementar a tabela hash
- [ ] Busca por atributo chave na tabela hash