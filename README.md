# Trabalho 4 - Grafos

- **Aluno:** Paulo Victor Fernandes de Melo
- **Aluno:** João Luiz Rodrigues da Silva
- **Aluna:** Rebecca Aimée Lima de Lima
- **Aluna:** Beatriz Jacaúna Martins

# Estrutura

O diretório do projeto segue a seguinte estrutura.

```
out/                Pasta de saída dos executáveis gerados pelo GCC.
include/            Pasta contendo os cabeçalhos do código.
src/                Pasta contendo o código do trabalho.
doc/                Pasta contendo o documento final, com as tabelas e gráficos.
.gitignore          Lista de arquivos removidos do envio para o GitHub.
Makefile            Instruções para build do arquivo, leia mais abaixo.
README.md           O arquivo que você está lendo agora.
```

Os códigos relevantes ao trabalho devem ser armazenados na pasta `src`, e os executáveis gerados pelo GCC irão para o `out`. Os conteúdos da pasta `out` são filtrados para **não serem enviados** ao GitHub pelo arquivo chamado `.gitignore`.

Ao executar o código do trabalho, o programa irá gerar alguns arquivos com a extensão `.csv`, contendo os dados de cada questão. Os dados usados no documento final do trabalho podem ser encontrados na pasta `out/csv-final/`.

# Como buildar

Ao baixar o projeto num computador com sistema operacional **Linux**, abra um terminal na pasta do projeto e execute o comando `make`. Isso executará todos os comandos do `gcc` necessários para buildar os executáveis do trabalho, que estarão na pasta `out`. O executável final do trabalho terá o nome `trab4`, e pode ser executado diretamente usando `./trab4`

```
$ make
$ cd out
$ ./trab4
```

ou

```
$ make run
```

para executar o código diretamente após compilá-lo.