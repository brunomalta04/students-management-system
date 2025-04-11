#include <stdio.h>
#include <string.h>
#define MAX_ALUNOS 100
#define ARQUIVO "dados_dos_alunos.txt"

typedef struct {
    int matricula;
    char nome[50];
    int idade;
    char curso[50];
    float media_das_notas;
} Aluno;

// FUNÇÕES

void carregarDados(Aluno alunos[], int *total);
void salvarDados(Aluno alunos[], int *total);
void cadastrarAluno(Aluno alunos[], int *total);
void listarAlunos(Aluno alunos[], int *total);
void buscarAluno(Aluno alunos[], int *total);
void atualizarAluno(Aluno alunos[], int *total);
void removerAluno(Aluno alunos[], int *total);

// FLUXO PRINCIPAL

int main() {
    Aluno alunos[MAX_ALUNOS];
    int total_alunos = 0;
    int opcao;

    carregarDados(alunos, &total_alunos);

    do {
        printf("\nSISTEMA DE ALUNOS:\n");
        printf("1.CADASTRAR ALUNO\n");
        printf("2.LISTAR ALUNO\n");
        printf("3.BUSCAR ALUNO\n");
        printf("4.ATUALIZAR ALUNO\n");
        printf("5.REMOVER ALUNO\n");
        printf("6.SAIR\n");
        printf("ESCOLHA: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1: cadastrarAluno(alunos, &total_alunos); 
            break;
            case 2: listarAlunos(alunos, &total_alunos); 
            break;
            case 3: buscarAluno(alunos, &total_alunos); 
            break;
            case 4: atualizarAluno(alunos, &total_alunos); 
            break;
            case 5: removerAluno(alunos, &total_alunos); 
            break;
            case 6: salvarDados(alunos, &total_alunos); 
            break;
            default: printf("\nOPÇÃO INVÁLIDA. TENTE NOVAMENTE.\n");
        }
    } while(opcao != 6);
    return 0;
}

void carregarDados(Aluno alunos[], int *total) {
  FILE *file = fopen(ARQUIVO, "r");
  if (!file) {
      printf("\nARQUIVO NÃO ENCONTRADO. CRIANDO UM NOVO...\n");
      file = fopen(ARQUIVO, "w"); 
      if (!file) {
          printf("\nERRO AO CRIAR O ARQUIVO.\n");
          return;
      }
  }
  fclose(file);
  
    while(fscanf(file, "%d", &alunos[*total].matricula) != EOF) {
        fscanf(file, " %49[^\n]", alunos[*total].nome);
        fscanf(file, "%d", &alunos[*total].idade);
        fscanf(file, " %49[^\n]", alunos[*total].curso);
        fscanf(file, "%f", &alunos[*total].media_das_notas);
        (*total)++;
    }
    fclose(file);
}

void salvarDados(Aluno alunos[], int *total) {
    FILE *file = fopen(ARQUIVO, "w");
    if(!file) {
        printf("\nERRO AO SALVAR OS DADOS DOS ALUNOS.\n");
        return;
    }

    for(int i = 0; i < *total; i++) {
        fprintf(file, "%d\n%s\n%d\n%s\n%.2f\n", alunos[i].matricula, alunos[i].nome, alunos[i].idade, alunos[i].curso, alunos[i].media_das_notas);
    }
    fclose(file);
}

void cadastrarAluno(Aluno alunos[], int *total) {
   
    printf("\nCADASTRO DE ALUNO\n");
    
    printf("MATRÍCULA: ");
    scanf("%d", &alunos[*total].matricula);
    getchar();

    printf("NOME: ");
    scanf(" %49[^\n]", alunos[*total].nome);
    getchar();

    printf("IDADE: ");
    scanf("%d", &alunos[*total].idade);
    getchar();

    printf("CURSO: ");
    scanf(" %49[^\n]", alunos[*total].curso);
    getchar();

    printf("MÉDIA: ");
    scanf("%f", &alunos[*total].media_das_notas);
    getchar();

    (*total)++;
    printf("ALUNO FOI CADASTRADO COM SUCESSO.\n");

    if(*total >= MAX_ALUNOS) {
      printf("\nLIMITE DE ALUNOS FOI ATINGIDO.\n");
      return;
  }
}

void listarAlunos(Aluno alunos[], int *total) {

    printf("\nLISTA DE ALUNOS\n");
    for(int i = 0; i < *total; i++) {
        printf("MATRÍCULA: %d\n", alunos[i].matricula);
        printf("NOME: %s\n", alunos[i].nome);
        printf("IDADE: %d\n", alunos[i].idade);
        printf("CURSO:  %s\n", alunos[i].curso);
        printf("MÉDIA: %.2f\n", alunos[i].media_das_notas);
    }

    if(*total == 0) {
      printf("\nNENHUM ALUNO CADASTRADO. \n");
      return;
  }
}

void buscarAluno(Aluno alunos[], int *total) {
    
    int matricula;
    printf("\nDIGITE A MATRÍCULA: ");
    scanf("%d", &matricula);
    getchar();

    for(int i = 0; i < *total; i++) {
        if(alunos[i].matricula == matricula) {
            printf("\nALUNO ENCONTRADO\n");
            printf("MATRÍCULA: %d\n", alunos[i].matricula);
            printf("NOME: %s\n", alunos[i].nome);
            printf("IDADE: %d\n", alunos[i].idade);
            printf("CURSO: %s\n", alunos[i].curso);
            printf("MÉDIA: %.2f\n", alunos[i].media_das_notas);
            return;
        }
    }
    printf("\nALUNO NÃO ENCONTRADO.\n");

    if(*total == 0) {
      printf("\nNENHUM ALUNO CADASTRADO. \n");
      return;
    
  }
}

void atualizarAluno(Aluno alunos[], int *total) {

    int matricula;
    printf("\nDIGITE A MATRÍCULA DO ALUNO: ");
    scanf("%d", &matricula);
    getchar();

    for(int i = 0; i < *total; i++) {
        if(alunos[i].matricula == matricula) {
            printf("\nATUALIZANDO DADOS DO ALUNO %s:\n", alunos[i].nome);
            
            printf("NOVO NOME: ");
            scanf(" %49[^\n]", alunos[i].nome);
            getchar();

            printf("NOVA IDADE: ");
            scanf("%d", &alunos[i].idade);
            getchar();

            printf("NOVO CURSO: ");
            scanf(" %49[^\n]", alunos[i].curso);
            getchar();

            printf("NOVA MÉDIA: ");
            scanf("%f", &alunos[i].media_das_notas);
            getchar();

            printf("\nDADOS ATUALIZADOS COM SUCESSO.\n");
            return;
        }
    }
    printf("\nALUNO NÃO ENCONTRADO.\n");
    
    if(*total == 0) {
      printf("\nNENHUM ALUNO CADASTRADO.\n");
      return;
  }

}

void removerAluno(Aluno alunos[], int *total) {
   
    int matricula;
    printf("\nDIGITE A MATRÍCULA DO ALUNO: ");
    scanf("%d", &matricula);
    getchar();

    for(int i = 0; i < *total; i++) {
        if(alunos[i].matricula == matricula) {
            for(int j = i; j < *total - 1; j++) {
                alunos[j] = alunos[j + 1];
            }
            (*total)--;
            printf("\nALUNO REMOVIDO COM SUCESSO.\n");
            return;
        }
    }

    if(*total == 0) {
      printf("\nNENHUM ALUNO CADASTRADO\n");
      return;
  }
}