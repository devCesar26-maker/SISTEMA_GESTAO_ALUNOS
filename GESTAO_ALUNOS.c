#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Aluno {
    char Matricula[10];
    char nome[50];
    char curso[30];
    int idade;
    float N1, N2, N3;
    
};

void cadastrar_aluno(struct Aluno *aluno) {
    printf("Digite a matricula do aluno: ");
    scanf("%9s", aluno->Matricula);
    getchar();

    printf("Digite o nome do aluno: ");
    scanf("%49[^\n]", aluno->nome);
    getchar();

    printf("Digite o curso do aluno: ");
    scanf("%29[^\n]", aluno->curso);
    getchar();

    printf("Digite a idade do aluno: ");
    scanf("%d", &aluno->idade);

    printf("Digite a nota 1 do aluno: ");
    scanf("%f", &aluno->N1);
    
    printf("Digite a nota 2 do aluno: ");
    scanf("%f", &aluno->N2);
    
    printf("Digite a nota 3 do aluno: ");
    scanf("%f", &aluno->N3);
}

void alterar_aluno(struct Aluno *alunos, int quantidade_alunos) {
    char busca[50];
    int encontrado = -1;
    
    printf("Digite a matricula do aluno que deseja alterar: ");
    scanf("%49s", busca);
    getchar();
    
    for (int i = 0; i < quantidade_alunos; i++) {
        if (strcmp(alunos[i].Matricula, busca) == 0) {
            encontrado = i;
            break;
        }
    }
    
    if (encontrado != -1) {
        printf("\n--- Alterando dados do aluno: %s ---\n", alunos[encontrado].nome);
        
        printf("Digite o novo nome (ou pressione Enter para manter): ");
        char novo_nome[50];
        fgets(novo_nome, sizeof(novo_nome), stdin);
        if (novo_nome[0] != '\n') {
            novo_nome[strcspn(novo_nome, "\n")] = 0;
            strcpy(alunos[encontrado].nome, novo_nome);
        }
        
        printf("Digite o novo curso (ou pressione Enter para manter): ");
        char novo_curso[30];
        fgets(novo_curso, sizeof(novo_curso), stdin);
        if (novo_curso[0] != '\n') {
            novo_curso[strcspn(novo_curso, "\n")] = 0;
            strcpy(alunos[encontrado].curso, novo_curso);
        }
        
        printf("Deseja alterar a idade? (1 - Sim / 0 - Nao): ");
        int alterar;
        scanf("%d", &alterar);
        if (alterar == 1) {
            printf("Digite a nova idade: ");
            scanf("%d", &alunos[encontrado].idade);
        }
        
        printf("Deseja alterar as notas? (1 - Sim / 0 - Nao): ");
        scanf("%d", &alterar);
        if (alterar == 1) {
            printf("Digite a nova nota 1: ");
            scanf("%f", &alunos[encontrado].N1);
            printf("Digite a nova nota 2: ");
            scanf("%f", &alunos[encontrado].N2);
            printf("Digite a nova nota 3: ");
            scanf("%f", &alunos[encontrado].N3);
        }
        
        printf("Dados alterados com sucesso!\n");
    } else {
        printf("Aluno com matricula '%s' nao encontrado.\n", busca);
    }
}

void exibir_menu(int quantidade_alunos) {
    printf("\n===================================\n");
    printf("    SISTEMA DE GESTAO DE ALUNOS    \n");
    printf("===================================\n");
    printf("Alunos cadastrados: %d\n", quantidade_alunos);
    printf("1. Cadastrar aluno\n");
    printf("2. Cadastrar notas (em desenvolvimento)\n");
    printf("3. Calcular media (em desenvolvimento)\n");
    printf("4. Situacao do aluno (em desenvolvimento)\n");
    printf("5. Consultar aluno (em desenvolvimento)\n");
    printf("6. Listagem geral (em desenvolvimento)\n");
    printf("7. Alterar dados de um aluno\n");
    printf("0. Sair\n");
    printf("===================================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    struct Aluno *alunos = NULL;
    int quantidade_alunos = 0;
    int escolha;

    do {
        exibir_menu(quantidade_alunos);
        if (scanf("%d", &escolha) != 1) {
            printf("Entrada invalida!\n");
            while(getchar() != '\n');
            continue;
        }
        
        switch (escolha) {
            case 1: {
                struct Aluno *tmp = realloc(alunos, (quantidade_alunos + 1) * sizeof(struct Aluno));
                if (tmp == NULL) {
                    printf("Erro ao alocar memoria!\n");
                    free(alunos);
                    return 1;
                }
                alunos = tmp;
                cadastrar_aluno(&alunos[quantidade_alunos]);
                quantidade_alunos++;
                printf("Aluno cadastrado com sucesso!\n");
                break;
            }
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                printf("\nOpcao %d esta em desenvolvimento pelos outros membros do grupo...\n", escolha);
                break;
            case 7:
                if (quantidade_alunos == 0) {
                    printf("\nNenhum aluno cadastrado no sistema para ser alterado.\n");
                } else {
                    alterar_aluno(alunos, quantidade_alunos);
                }
                break;
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }
    } while (escolha != 0); 

    free(alunos);
    return 0;

}

