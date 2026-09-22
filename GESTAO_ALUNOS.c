#include <stdio.h>
#include <stdlib.h>

struct Aluno {
    char Matricula[10];
    char nome[50];
    char curso[30];
    int idade;
    float N1, N2, N3;
    float media; 
};

void cadastrar_aluno( struct Aluno *aluno) {
    printf("Digite a matricula do aluno: ");
    scanf("%9s", aluno->Matricula);

    printf("Digite o nome do aluno: ");
    scanf(" %49[^\n]", aluno->nome);

    printf("Digite o curso do aluno: ");
    scanf(" %29[^\n]", aluno->curso);

    printf("Digite a idade do aluno: ");
    scanf("%d", &aluno->idade);

    printf("Digite a nota 1 do aluno: ");
    scanf("%f", &aluno->N1);
    
    printf("Digite a nota 2 do aluno: ");
    scanf("%f", &aluno->N2);
    
    printf("Digite a nota 3 do aluno: ");
    scanf("%f", &aluno->N3);
    
    aluno->media = (aluno->N1 + aluno->N2 + aluno->N3) / 3.0;
}


int main(){
    struct Aluno *alunos=NULL;
    int quantidade_alunos=0;
    int escolha;

    
    do {
        printf("Sistema de Gestao de Alunos\n");
        printf("Quantidade de alunos cadastrados: %d\n", quantidade_alunos);
        printf("0. Sair\n");
        printf("1. Cadastrar aluno\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        switch (escolha) {
            case 0:
                printf("Saindo do sistema...\n");
                break;
            case 1:{

                struct Aluno *tmp=realloc(alunos, (quantidade_alunos+1)*sizeof(struct Aluno));
                if (tmp==NULL){
                    printf("Erro ao alocar memoria!\n");
                    free(alunos);
                    return 1;
                }
                alunos=tmp;
                cadastrar_aluno(&alunos[quantidade_alunos]);
                quantidade_alunos++;
                printf("Aluno cadastrado com sucesso!\n");
                break;
            }
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (escolha != 0); 

    free(alunos);
    return 0;

}

