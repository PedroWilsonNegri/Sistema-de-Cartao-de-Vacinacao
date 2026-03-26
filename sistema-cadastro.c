#include <stdio.h>
#include <stdlib.h>

int main() {
    char nome[100];
    char cpf[11];
    int idade;
    char vacina[100];
    char data[20];

    printf("=== Cadastro de Vacinacao ===\n");

    printf("Nome: ");
    fgets(nome, 100, stdin);

    printf("CPF: ");
    fgets(cpf, 20, stdin);

    printf("Idade: ");
    scanf("%d", &idade);
    getchar();

    printf("Nome da Vacina: ");
    fgets(vacina, 100, stdin);

    printf("Data da aplicacao (dd/mm/aaaa): ");
    fgets(data, 20, stdin);

    printf("\n=== Cartao de Vacinacao ===\n");
    printf("Nome: %s", nome);
    printf("CPF: %s", cpf);
    printf("Idade: %d\n", idade);
    printf("Vacina: %s", vacina);
    printf("Data da aplicacao: %s", data);

    return 0;
}
