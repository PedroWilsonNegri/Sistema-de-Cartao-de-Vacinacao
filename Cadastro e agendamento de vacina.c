#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Estrutura do cadastro
typedef struct {
    char nome[100];
    char cpf[20];
    int idade;
    char vacina[100];
    char data[20];
    int aplicada; // 0 = não, 1 = sim
} Pessoa;

Pessoa lista[MAX];
int total = 0;

// Função para cadastrar e agendar
void cadastrar() {
    if (total >= MAX) {
        printf("Limite de cadastros atingido!\n");
        return;
    }

    printf("\n=== Cadastro e Agendamento ===\n");

    printf("Nome: ");
    fgets(lista[total].nome, 100, stdin);

    printf("CPF: ");
    fgets(lista[total].cpf, 20, stdin);

    printf("Idade: ");
    scanf("%d", &lista[total].idade);
    getchar();

    printf("Vacina: ");
    fgets(lista[total].vacina, 100, stdin);

    printf("Data da aplicacao: ");
    fgets(lista[total].data, 20, stdin);

    lista[total].aplicada = 0;

    total++;

    printf("Cadastro realizado com sucesso!\n");
}

// Funcionário registra aplicação pelo CPF do cliente
void aplicarVacina() {
    char cpfBusca[20];
    int encontrado = 0;

    printf("\n=== Aplicar Vacina ===\n");
    printf("Digite o CPF: ");
    fgets(cpfBusca, 20, stdin);

    	int i;
		for (i = 0; i < total; i++) {
        if (strcmp(lista[i].cpf, cpfBusca) == 0) {
            lista[i].aplicada = 1;
            printf("Vacina aplicada com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("CPF nao encontrado!\n");
    }
}

// Mostrar todos os registros
void listar() {
    printf("\n=== Lista de Vacinacao ===\n");

    	int i;
		for (i = 0; i < total; i++) {
        printf("\nNome: %s", lista[i].nome);
        printf("CPF: %s", lista[i].cpf);
        printf("Idade: %d\n", lista[i].idade);
        printf("Vacina: %s", lista[i].vacina);
        printf("Data: %s", lista[i].data);

        if (lista[i].aplicada)
            printf("Status: Aplicada\n");
        else
            printf("Status: Pendente\n");
    }
}

int main() {
    int opcao;

    do {
        printf("\n=== Sistema de Vacinacao ===\n");
        printf("1 - Cadastrar e Agendar\n");
        printf("2 - Registrar Aplicacao (Funcionario)\n");
        printf("3 - Listar Registros\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrar();
                break;
            case 2:
                aplicarVacina();
                break;
            case 3:
                listar();
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}