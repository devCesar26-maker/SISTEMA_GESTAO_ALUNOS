# Sistema de Gestão de Alunos

Trabalho da disciplina de Programação — Grupo 3.

Sistema feito em linguagem C, executado no terminal (console), para cadastrar
alunos e suas notas, calcular a média e informar a situação de cada um
(aprovado, recuperação ou reprovado).

## Integrantes

- Otávio Figueredo Alves - @otaviofigueredoalves
- César de Araújo Oliveira - @devCesar26-maker
- João Pedro Martins dos Santos - @JPMS2070
- Livia Maria dos Santos Alves
- Inácio Rodrigues Gonçalves - @itsinacio
- Daniel Candido Mendes da Silva

## Descrição do sistema

O programa guarda os dados dos alunos apenas na memória, durante a execução.
Não usa arquivos nem banco de dados.

Cada aluno tem matrícula, nome, curso, idade e as duas notas (N1 e N2).
A partir dessas notas, o sistema calcula a média e classifica o aluno.

A entidade principal do sistema é a struct Aluno:

```c
struct Aluno {
    char matricula[10];
    char nome[60];
    char curso[40];
    int idade;
    float n1;
    float n2;
    float media;
};
```

Os alunos ficam armazenados em um vetor de structs:

```c
struct Aluno alunos[MAX_ALUNOS];   /* MAX_ALUNOS = 100 */
```

## Critérios de avaliação adotados

A média é calculada pela fórmula:

```
Média = (N1 + N2) / 2
```

Situação do aluno:

- Aprovado: média maior ou igual a 7,0.
- Recuperação: média maior ou igual a 5,0 e menor que 7,0.
- Reprovado: média menor que 5,0.

As notas devem estar entre 0,0 e 10,0. Os critérios também aparecem dentro do
programa, na opção 9 do menu.

## Funcionalidades

1. Cadastrar aluno (matrícula, nome, curso, idade, N1 e N2).
2. Lançar ou atualizar as notas de um aluno já cadastrado.
3. Recalcular as médias de todos os alunos.
4. Mostrar a situação de um aluno (média e classificação).
5. Consultar aluno pela matrícula (exata) ou pelo nome (parte do nome).
6. Listar todos os alunos em forma de tabela.
7. Alterar os dados de um aluno.
8. Excluir um aluno, com confirmação.
9. Exibir os critérios de avaliação usados pelo grupo.
0. Sair.

## Regras de negócio e validações

- Não permite matrícula repetida (nem no cadastro nem na alteração).
- Não aceita nota fora do intervalo de 0 a 10.
- Não aceita idade menor que 1 nem maior que 120.
- Não aceita matrícula, nome ou curso em branco.
- Verifica se o aluno existe antes de consultar, alterar ou excluir.
- A exclusão pede confirmação (s/n).
- Limite de 100 alunos cadastrados.

## Organização do código

O código está dividido em funções e a função main apenas controla o menu.
As funções que alteram dados recebem ponteiros (passagem por referência),
como pede o trabalho:

- cadastrar_aluno: cadastra um aluno (recebe int *quantidade).
- lancar_notas: lança ou atualiza as notas (recebe struct Aluno *).
- recalcular_medias: recalcula a média de todos os alunos.
- consultar_situacao: mostra a média e a situação de um aluno.
- consultar_aluno: busca por matrícula ou por nome.
- listar_alunos: lista todos os alunos.
- alterar_aluno: altera os dados de um aluno.
- excluir_aluno: exclui um aluno (recebe int *quantidade).
- calcular_media: calcula a média (recebe struct Aluno *).
- obter_situacao: retorna a situação a partir da média.
- buscar_por_matricula: localiza um aluno e devolve sua posição (ou -1).
- ler_nota, ler_inteiro, ler_string, confirmar: leitura e validação de dados.
- exibir_menu, exibir_criterios, imprimir_aluno: exibição de dados na tela.

## Como compilar e executar

É preciso ter um compilador C instalado (por exemplo o GCC).

Compilar:

```bash
gcc GESTAO_ALUNOS.c -o gestao_alunos
```

Executar no Linux ou macOS:

```bash
./gestao_alunos
```

Executar no Windows:

```
gestao_alunos.exe
```

## Como usar

Ao executar, aparece o menu principal:

```
 SISTEMA DE GESTAO DE ALUNOS
 Alunos cadastrados: 0/100
 1 - Cadastrar aluno
 2 - Lancar / atualizar notas
 3 - Recalcular medias
 4 - Ver situacao do aluno
 5 - Consultar aluno (matricula ou nome)
 6 - Listar todos os alunos
 7 - Alterar dados de um aluno
 8 - Excluir aluno
 9 - Criterios de avaliacao
 0 - Sair
```

Basta digitar o número da opção desejada e apertar Enter. Exemplo de listagem:

```
MATRIC.    NOME                 CURSO            IDADE     N1     N2   MEDIA  SITUACAO
2024001    Ana Silva            Engenharia          20   8.50   7.00    7.75  APROVADO
2024002    Bruno Costa          Direito             22   4.00   5.00    4.50  REPROVADO
```

## Estrutura do repositório

```
SISTEMA_GESTAO_ALUNOS/
  GESTAO_ALUNOS.c   codigo-fonte do sistema
  README.md         documentacao do projeto
  .gitignore        arquivos ignorados pelo Git
```

## Conteúdos utilizados

- Linguagem C (padrão C99).
- struct para representar o aluno.
- Vetor de structs para armazenar os dados em memória.
- Funções e protótipos para organizar o código.
- Ponteiros / passagem por referência para alterar as estruturas.
- Validação de dados e regras de negócio.
