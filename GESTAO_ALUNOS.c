#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ALUNOS 100
#define TAM_MATRICULA 10
#define TAM_NOME 60
#define TAM_CURSO 40

#define NOTA_MINIMA 0.0f
#define NOTA_MAXIMA 10.0f
#define IDADE_MINIMA 1
#define IDADE_MAXIMA 120

#define MEDIA_APROVACAO 7.0f
#define MEDIA_RECUPERACAO 5.0f

struct Aluno {
    char matricula[TAM_MATRICULA];
    char nome[TAM_NOME];
    char curso[TAM_CURSO];
    int idade;
    float n1;
    float n2;
    float media;
};

/* prototipos */
void limpar_buffer(void);
void verificar_fim_entrada(void);
void ler_string(const char *rotulo, char *destino, int tamanho);
void ler_string_obrigatoria(const char *rotulo, char *destino, int tamanho);
int ler_inteiro(const char *rotulo, int minimo, int maximo);
float ler_nota(const char *rotulo);
int confirmar(const char *rotulo);

float calcular_media(struct Aluno *aluno);
const char *obter_situacao(float media);
int buscar_por_matricula(const struct Aluno *alunos, int quantidade, const char *matricula);
int contem_texto(const char *texto, const char *busca);

void imprimir_aluno(const struct Aluno *aluno);
void listar_alunos(struct Aluno *alunos, int quantidade);
void exibir_menu(int quantidade);
void exibir_criterios(void);

void cadastrar_aluno(struct Aluno *alunos, int *quantidade);
void lancar_notas(struct Aluno *alunos, int quantidade);
void recalcular_medias(struct Aluno *alunos, int quantidade);
void consultar_situacao(struct Aluno *alunos, int quantidade);
void consultar_aluno(struct Aluno *alunos, int quantidade);
void alterar_aluno(struct Aluno *alunos, int quantidade);
void excluir_aluno(struct Aluno *alunos, int *quantidade);

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void verificar_fim_entrada(void) {
    if (feof(stdin) || ferror(stdin)) {
        printf("\n>> Entrada de dados encerrada. Finalizando o sistema...\n");
        exit(0);
    }
}

void ler_string(const char *rotulo, char *destino, int tamanho) {
    printf("%s", rotulo);

    if (fgets(destino, tamanho, stdin) == NULL) {
        destino[0] = '\0';
        verificar_fim_entrada();
        return;
    }

    /* se nao veio o '\n', o usuario digitou mais do que o campo aceita */
    if (strchr(destino, '\n') == NULL) {
        limpar_buffer();
    }

    destino[strcspn(destino, "\n")] = '\0';
}

void ler_string_obrigatoria(const char *rotulo, char *destino, int tamanho) {
    do {
        ler_string(rotulo, destino, tamanho);
        if (strlen(destino) == 0) {
            printf(">> Este campo nao pode ficar vazio. Tente novamente.\n");
        }
    } while (strlen(destino) == 0);
}

int ler_inteiro(const char *rotulo, int minimo, int maximo) {
    char linha[64];
    int valor;

    while (1) {
        printf("%s", rotulo);

        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            verificar_fim_entrada();
            continue;
        }

        if (sscanf(linha, "%d", &valor) == 1 && valor >= minimo && valor <= maximo) {
            return valor;
        }

        printf(">> Valor invalido! Digite um numero entre %d e %d.\n", minimo, maximo);
    }
}

float ler_nota(const char *rotulo) {
    char linha[64];
    float valor;

    while (1) {
        printf("%s", rotulo);

        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            verificar_fim_entrada();
            continue;
        }

        if (sscanf(linha, "%f", &valor) == 1 && valor >= NOTA_MINIMA && valor <= NOTA_MAXIMA) {
            return valor;
        }

        printf(">> Nota invalida! Informe um valor entre %.0f e %.0f.\n", NOTA_MINIMA, NOTA_MAXIMA);
    }
}

int confirmar(const char *rotulo) {
    char resposta[16];

    while (1) {
        ler_string(rotulo, resposta, sizeof(resposta));

        if (resposta[0] == 's' || resposta[0] == 'S') {
            return 1;
        }
        if (resposta[0] == 'n' || resposta[0] == 'N') {
            return 0;
        }

        printf(">> Responda com 's' (sim) ou 'n' (nao).\n");
    }
}

/* recebe ponteiro porque altera a media dentro da struct */
float calcular_media(struct Aluno *aluno) {
    aluno->media = (aluno->n1 + aluno->n2) / 2.0f;
    return aluno->media;
}

const char *obter_situacao(float media) {
    if (media >= MEDIA_APROVACAO) {
        return "APROVADO";
    }
    if (media >= MEDIA_RECUPERACAO) {
        return "RECUPERACAO";
    }
    return "REPROVADO";
}

/* devolve a posicao do aluno no vetor ou -1 se nao achar */
int buscar_por_matricula(const struct Aluno *alunos, int quantidade, const char *matricula) {
    int i;

    for (i = 0; i < quantidade; i++) {
        if (strcmp(alunos[i].matricula, matricula) == 0) {
            return i;
        }
    }

    return -1;
}

/* procura um texto dentro do outro, sem diferenciar maiuscula de minuscula */
int contem_texto(const char *texto, const char *busca) {
    char texto_minusculo[TAM_NOME];
    char busca_minuscula[TAM_NOME];
    int i;

    if (strlen(busca) >= TAM_NOME) {
        return 0;
    }

    for (i = 0; texto[i] != '\0' && i < TAM_NOME - 1; i++) {
        texto_minusculo[i] = (char) tolower((unsigned char) texto[i]);
    }
    texto_minusculo[i] = '\0';

    for (i = 0; busca[i] != '\0'; i++) {
        busca_minuscula[i] = (char) tolower((unsigned char) busca[i]);
    }
    busca_minuscula[i] = '\0';

    return strstr(texto_minusculo, busca_minuscula) != NULL;
}

void imprimir_aluno(const struct Aluno *aluno) {
    printf("  Matricula : %s\n", aluno->matricula);
    printf("  Nome      : %s\n", aluno->nome);
    printf("  Curso     : %s\n", aluno->curso);
    printf("  Idade     : %d\n", aluno->idade);
    printf("  Notas     : N1 = %.2f | N2 = %.2f\n", aluno->n1, aluno->n2);
    printf("  Media     : %.2f\n", aluno->media);
    printf("  Situacao  : %s\n", obter_situacao(aluno->media));
}

void listar_alunos(struct Aluno *alunos, int quantidade) {
    int i;

    if (quantidade == 0) {
        printf("\n>> Nenhum aluno cadastrado no sistema.\n");
        return;
    }

    printf("\n================= LISTAGEM DE ALUNOS (%d) =================\n", quantidade);
    printf("%-10s %-20s %-14s %5s %6s %6s %7s  %s\n",
           "MATRIC.", "NOME", "CURSO", "IDADE", "N1", "N2", "MEDIA", "SITUACAO");

    for (i = 0; i < quantidade; i++) {
        printf("%-10s %-20s %-14s %5d %6.2f %6.2f %7.2f  %s\n",
               alunos[i].matricula,
               alunos[i].nome,
               alunos[i].curso,
               alunos[i].idade,
               alunos[i].n1,
               alunos[i].n2,
               alunos[i].media,
               obter_situacao(alunos[i].media));
    }

    printf("==========================================================\n");
}

void exibir_menu(int quantidade) {
    printf("\n=============================================\n");
    printf("        SISTEMA DE GESTAO DE ALUNOS\n");
    printf("=============================================\n");
    printf(" Alunos cadastrados: %d/%d\n", quantidade, MAX_ALUNOS);
    printf("---------------------------------------------\n");
    printf(" 1 - Cadastrar aluno\n");
    printf(" 2 - Lancar / atualizar notas\n");
    printf(" 3 - Recalcular medias\n");
    printf(" 4 - Ver situacao do aluno\n");
    printf(" 5 - Consultar aluno (matricula ou nome)\n");
    printf(" 6 - Listar todos os alunos\n");
    printf(" 7 - Alterar dados de um aluno\n");
    printf(" 8 - Excluir aluno\n");
    printf(" 9 - Criterios de avaliacao\n");
    printf(" 0 - Sair\n");
    printf("=============================================\n");
}

void exibir_criterios(void) {
    printf("\n============ CRITERIOS DE AVALIACAO ============\n");
    printf(" Media final = (N1 + N2) / 2\n\n");
    printf(" - Aprovado    : media >= %.1f\n", MEDIA_APROVACAO);
    printf(" - Recuperacao : media >= %.1f e < %.1f\n", MEDIA_RECUPERACAO, MEDIA_APROVACAO);
    printf(" - Reprovado   : media <  %.1f\n\n", MEDIA_RECUPERACAO);
    printf(" Notas aceitas  : de %.0f a %.0f\n", NOTA_MINIMA, NOTA_MAXIMA);
    printf(" Idade aceita   : de %d a %d anos\n", IDADE_MINIMA, IDADE_MAXIMA);
    printf("================================================\n");
}

void cadastrar_aluno(struct Aluno *alunos, int *quantidade) {
    struct Aluno *novo;

    if (*quantidade >= MAX_ALUNOS) {
        printf("\n>> Limite de %d alunos ja foi atingido.\n", MAX_ALUNOS);
        return;
    }

    novo = &alunos[*quantidade];

    printf("\n--------------- CADASTRO DE ALUNO ---------------\n");

    /* matricula nao pode repetir */
    while (1) {
        ler_string_obrigatoria("Matricula: ", novo->matricula, TAM_MATRICULA);

        if (buscar_por_matricula(alunos, *quantidade, novo->matricula) != -1) {
            printf(">> Ja existe um aluno cadastrado com essa matricula.\n");
        } else {
            break;
        }
    }

    ler_string_obrigatoria("Nome: ", novo->nome, TAM_NOME);
    ler_string_obrigatoria("Curso: ", novo->curso, TAM_CURSO);
    novo->idade = ler_inteiro("Idade: ", IDADE_MINIMA, IDADE_MAXIMA);

    printf("--- Notas ---\n");
    novo->n1 = ler_nota("Nota N1: ");
    novo->n2 = ler_nota("Nota N2: ");

    calcular_media(novo);
    (*quantidade)++;

    printf("\n>> Aluno '%s' cadastrado com sucesso! Media: %.2f (%s)\n",
           novo->nome, novo->media, obter_situacao(novo->media));
}

void lancar_notas(struct Aluno *alunos, int quantidade) {
    struct Aluno *aluno;
    char matricula[TAM_MATRICULA];
    int indice;

    if (quantidade == 0) {
        printf("\n>> Nenhum aluno cadastrado. Cadastre um aluno primeiro.\n");
        return;
    }

    ler_string_obrigatoria("Matricula do aluno: ", matricula, TAM_MATRICULA);
    indice = buscar_por_matricula(alunos, quantidade, matricula);

    if (indice == -1) {
        printf(">> Aluno nao encontrado. Nenhuma nota foi alterada.\n");
        return;
    }

    aluno = &alunos[indice];

    printf("\n---------- LANCAMENTO DE NOTAS: %s ----------\n", aluno->nome);
    printf("Notas atuais -> N1 = %.2f | N2 = %.2f\n", aluno->n1, aluno->n2);

    aluno->n1 = ler_nota("Nova N1: ");
    aluno->n2 = ler_nota("Nova N2: ");

    calcular_media(aluno);

    printf(">> Notas atualizadas! Nova media: %.2f (%s)\n",
           aluno->media, obter_situacao(aluno->media));
}

void recalcular_medias(struct Aluno *alunos, int quantidade) {
    int i;

    if (quantidade == 0) {
        printf("\n>> Nenhum aluno cadastrado.\n");
        return;
    }

    for (i = 0; i < quantidade; i++) {
        calcular_media(&alunos[i]);
    }

    printf("\n>> Medias recalculadas para %d aluno(s).\n", quantidade);
    listar_alunos(alunos, quantidade);
}

void consultar_situacao(struct Aluno *alunos, int quantidade) {
    char matricula[TAM_MATRICULA];
    int indice;

    if (quantidade == 0) {
        printf("\n>> Nenhum aluno cadastrado no sistema.\n");
        return;
    }

    ler_string_obrigatoria("Matricula do aluno: ", matricula, TAM_MATRICULA);
    indice = buscar_por_matricula(alunos, quantidade, matricula);

    if (indice == -1) {
        printf(">> Aluno com a matricula '%s' nao encontrado.\n", matricula);
        return;
    }

    printf("\n------------- SITUACAO DO ALUNO -------------\n");
    printf(" Aluno    : %s\n", alunos[indice].nome);
    printf(" Matricula: %s\n", alunos[indice].matricula);
    printf(" Media    : %.2f\n", alunos[indice].media);
    printf(" Situacao : %s\n", obter_situacao(alunos[indice].media));
    printf("---------------------------------------------\n");
}

void consultar_aluno(struct Aluno *alunos, int quantidade) {
    char busca[TAM_NOME];
    int i;
    int encontrados = 0;

    if (quantidade == 0) {
        printf("\n>> Nenhum aluno cadastrado no sistema.\n");
        return;
    }

    printf("\n--------------- CONSULTA DE ALUNO ---------------\n");
    ler_string_obrigatoria("Digite a matricula ou o nome do aluno: ", busca, TAM_NOME);

    for (i = 0; i < quantidade; i++) {
        if (strcmp(alunos[i].matricula, busca) == 0 || contem_texto(alunos[i].nome, busca)) {
            encontrados++;
            printf("\n[%d] ", encontrados);
            imprimir_aluno(&alunos[i]);
        }
    }

    if (encontrados == 0) {
        printf(">> Nenhum aluno encontrado com o valor '%s'.\n", busca);
    } else {
        printf("\n>> %d aluno(s) encontrado(s).\n", encontrados);
    }
}

void alterar_aluno(struct Aluno *alunos, int quantidade) {
    struct Aluno *aluno;
    char matricula[TAM_MATRICULA];
    int indice;
    int indice_duplicado;

    if (quantidade == 0) {
        printf("\n>> Nenhum aluno cadastrado para ser alterado.\n");
        return;
    }

    ler_string_obrigatoria("Matricula do aluno a alterar: ", matricula, TAM_MATRICULA);
    indice = buscar_por_matricula(alunos, quantidade, matricula);

    if (indice == -1) {
        printf(">> Aluno nao encontrado. Nenhuma alteracao foi feita.\n");
        return;
    }

    aluno = &alunos[indice];

    printf("\n--------------- ALTERACAO DE ALUNO ---------------\n");
    imprimir_aluno(aluno);
    printf("Pressione Enter sem digitar nada para manter os outros dados.\n");

    if (confirmar("Deseja alterar a matricula? (s/n): ")) {
        char nova_matricula[TAM_MATRICULA];

        while (1) {
            ler_string_obrigatoria("Nova matricula: ", nova_matricula, TAM_MATRICULA);
            indice_duplicado = buscar_por_matricula(alunos, quantidade, nova_matricula);

            /* pode repetir a propria matricula, mas nao a de outro aluno */
            if (indice_duplicado != -1 && indice_duplicado != indice) {
                printf(">> Essa matricula ja pertence a outro aluno.\n");
            } else {
                strcpy(aluno->matricula, nova_matricula);
                break;
            }
        }
    }

    if (confirmar("Deseja alterar o nome? (s/n): ")) {
        ler_string_obrigatoria("Novo nome: ", aluno->nome, TAM_NOME);
    }

    if (confirmar("Deseja alterar o curso? (s/n): ")) {
        ler_string_obrigatoria("Novo curso: ", aluno->curso, TAM_CURSO);
    }

    if (confirmar("Deseja alterar a idade? (s/n): ")) {
        aluno->idade = ler_inteiro("Nova idade: ", IDADE_MINIMA, IDADE_MAXIMA);
    }

    if (confirmar("Deseja alterar as notas? (s/n): ")) {
        aluno->n1 = ler_nota("Nova N1: ");
        aluno->n2 = ler_nota("Nova N2: ");
        calcular_media(aluno);
    }

    printf("\n>> Dados alterados com sucesso!\n");
    imprimir_aluno(aluno);
}

void excluir_aluno(struct Aluno *alunos, int *quantidade) {
    char matricula[TAM_MATRICULA];
    int indice;
    int i;

    if (*quantidade == 0) {
        printf("\n>> Nenhum aluno cadastrado para excluir.\n");
        return;
    }

    ler_string_obrigatoria("Matricula do aluno a excluir: ", matricula, TAM_MATRICULA);
    indice = buscar_por_matricula(alunos, *quantidade, matricula);

    if (indice == -1) {
        printf(">> Aluno nao encontrado. Nada foi excluido.\n");
        return;
    }

    printf("\nAluno encontrado:\n");
    imprimir_aluno(&alunos[indice]);

    if (!confirmar("\nConfirma a exclusao deste aluno? (s/n): ")) {
        printf(">> Exclusao cancelada.\n");
        return;
    }

    /* puxa os alunos seguintes uma posicao para tras */
    for (i = indice; i < *quantidade - 1; i++) {
        alunos[i] = alunos[i + 1];
    }

    (*quantidade)--;

    printf(">> Aluno excluido com sucesso! Total de alunos: %d\n", *quantidade);
}

int main(void) {
    struct Aluno alunos[MAX_ALUNOS];
    int quantidade = 0;
    int opcao;

    printf("Bem-vindo ao Sistema de Gestao de Alunos!\n");

    do {
        exibir_menu(quantidade);
        opcao = ler_inteiro("Escolha uma opcao: ", 0, 9);

        switch (opcao) {
            case 1:
                cadastrar_aluno(alunos, &quantidade);
                break;
            case 2:
                lancar_notas(alunos, quantidade);
                break;
            case 3:
                recalcular_medias(alunos, quantidade);
                break;
            case 4:
                consultar_situacao(alunos, quantidade);
                break;
            case 5:
                consultar_aluno(alunos, quantidade);
                break;
            case 6:
                listar_alunos(alunos, quantidade);
                break;
            case 7:
                alterar_aluno(alunos, quantidade);
                break;
            case 8:
                excluir_aluno(alunos, &quantidade);
                break;
            case 9:
                exibir_criterios();
                break;
            case 0:
                printf("\nEncerrando o sistema... Ate logo!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
