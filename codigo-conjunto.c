#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VACINAS 100

// ================== ESTRUTURAS ==================

typedef struct
{
    char nome[50];
    int idade;
    char dataNascimento[11]; // DD/MM/AAAA
    char cpf[15];
} Paciente;

typedef struct
{
    char nome[50];
    char data[11];
    char hora[6];
    char status[20];
} RegistroVacina;

typedef struct
{
    RegistroVacina vacinas[MAX_VACINAS];
    int total;
} Historico;

// ================== DADOS FIXOS ==================

const char *vacinaNomes[] = {
    "BCG","Hepatite B","Pentavalente","Poliomielite",
    "Febre Amarela","Triplice Viral","Covid-19",
    "HPV","Influenza","DTP"
};

// ================== FUNÇÕES ==================

void formatarData(char *entrada, char *saida)
{
    // entrada no formato YYYY-MM-DD (como HTML)
    if (strlen(entrada) == 10)
    {
        snprintf(saida, 11, "%.2s/%.2s/%.4s",
                 entrada + 8, entrada + 5, entrada);
    }
    else
    {
        strcpy(saida, "Data invalida");
    }
}

void formatarCPF(char *entrada, char *saida)
{
    char num[12];
    int j = 0, i;

    for (i = 0; entrada[i] != '\0'; i++)
    {
        if (entrada[i] >= '0' && entrada[i] <= '9' && j < 11)
        {
            num[j++] = entrada[i];
        }
    }
    num[j] = '\0';

    if (j == 11)
    {
        snprintf(saida, 15, "%.3s.%.3s.%.3s-%.2s",
                 num, num+3, num+6, num+9);
    }
    else
    {
        strcpy(saida, "CPF invalido");
    }
}

void cadastrarPaciente(Paciente *p)
{
    char buffer[50];
    char dataRaw[15];
    char cpfRaw[20];

    printf("\n=== CADASTRO ===\n");

    printf("Nome: ");
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = '\0';

    printf("Idade: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &p->idade);

    printf("Data nascimento (YYYY-MM-DD): ");
    fgets(dataRaw, sizeof(dataRaw), stdin);
    dataRaw[strcspn(dataRaw, "\n")] = '\0';
    formatarData(dataRaw, p->dataNascimento);

    printf("CPF: ");
    fgets(cpfRaw, sizeof(cpfRaw), stdin);
    cpfRaw[strcspn(cpfRaw, "\n")] = '\0';
    formatarCPF(cpfRaw, p->cpf);
}

void registrarVacina(Historico *h, char *nome, char *data, char *hora)
{
    if (h->total < MAX_VACINAS)
    {
        strcpy(h->vacinas[h->total].nome, nome);
        strcpy(h->vacinas[h->total].data, data);
        strcpy(h->vacinas[h->total].hora, hora);
        strcpy(h->vacinas[h->total].status, "Agendada");

        h->total++;
    }
}

void mostrarHistorico(Historico *h)
{
    int i;

    printf("\n===== HISTORICO =====\n");

    if (h->total == 0)
    {
        printf("Nenhuma vacina registrada.\n");
        return;
    }

    printf("---------------------------------------------------\n");
    printf("| # | Vacina           | Data       | Hora | Status |\n");
    printf("---------------------------------------------------\n");

    for (i = 0; i < h->total; i++)
    {
        printf("| %-2d| %-15s | %-10s | %-5s | %-7s |\n",
               i+1,
               h->vacinas[i].nome,
               h->vacinas[i].data,
               h->vacinas[i].hora,
               h->vacinas[i].status);
    }

    printf("---------------------------------------------------\n");
}

void agendarVacina(Historico *h)
{
    int i, opcao;
    char buffer[10];
    char dataRaw[15], dataFormatada[15];
    char hora[10];

    printf("\n=== VACINAS ===\n");

    for (i = 0; i < 10; i++)
    {
        printf("%d - %s\n", i+1, vacinaNomes[i]);
    }

    printf("Escolha: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &opcao);

    if (opcao < 1 || opcao > 10)
    {
        printf("Opcao invalida!\n");
        return;
    }

    printf("Data (YYYY-MM-DD): ");
    fgets(dataRaw, sizeof(dataRaw), stdin);
    dataRaw[strcspn(dataRaw, "\n")] = '\0';
    formatarData(dataRaw, dataFormatada);

    printf("Hora (HH:MM): ");
    fgets(hora, sizeof(hora), stdin);
    hora[strcspn(hora, "\n")] = '\0';

    registrarVacina(h, (char*)vacinaNomes[opcao-1], dataFormatada, hora);

    printf("Vacina agendada com sucesso!\n");
}

// ================== MAIN ==================

int main()
{
    Paciente p;
    Historico h = {0};

    int opcao;
    char buffer[10];

    cadastrarPaciente(&p);

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Agendar vacina\n");
        printf("2 - Ver historico\n");
        printf("0 - Sair\n");
        printf("Opcao: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &opcao);

        switch (opcao)
        {
            case 1:
                agendarVacina(&h);
                break;

            case 2:
                mostrarHistorico(&h);
                break;
        }

    } while (opcao != 0);

    return 0;
}
