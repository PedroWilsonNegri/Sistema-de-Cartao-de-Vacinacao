#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ================== ESTRUTURAS ==================

// estrutura principal do paciente, onde guardamos os dados pessoais dele
typedef struct 
{
    char nome[50];
    char dataNascimento[15];
    char cpf[15];
    int idade;
} Paciente;

// estrutura usada para registrar o hist�rico de vacinas do paciente
typedef struct 
{
    char nome[50];
    char data[11];
    char status[20]; // Tomada, Agendada ou Nao Tomada
} RegistroVacina;

// estrutura que armazena todo o hist�rico do paciente
typedef struct 
{
    RegistroVacina vacinas[100];
    int totalVacinas;
} Historico;

// ================== DADOS FIXOS ==================

// lista de vacinas dispon�veis (igual ao HTML/JS)
const char *vacinaNomes[] = {"Gripe", "Hepatite A e B", "Anti-Rabica", "Anti-Tetanica", "BCG", "Covid"};

// ================== FUN��ES ==================

// fun��o usada para limpar o buffer do teclado
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// essa fun��o � respons�vel por cadastrar o paciente
void cadastrarPaciente(Paciente *p)
{
    char bufferIdade[10];

    printf("\n=== Cadastro do Paciente ===\n");

    printf("Nome: ");
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = '\0';

    printf("Idade: ");
    fgets(bufferIdade, sizeof(bufferIdade), stdin);
    p->idade = atoi(bufferIdade);

    printf("Data de Nascimento: ");
    fgets(p->dataNascimento, sizeof(p->dataNascimento), stdin);
    p->dataNascimento[strcspn(p->dataNascimento, "\n")] = '\0';

    printf("CPF: ");
    fgets(p->cpf, sizeof(p->cpf), stdin);
    p->cpf[strcspn(p->cpf, "\n")] = '\0';
}

// essa fun��o registra uma vacina no hist�rico
void registrarVacina(Historico *h, char *nome, char *data, char *status)
{
    if (h->totalVacinas < 100)
    {
        strcpy(h->vacinas[h->totalVacinas].nome, nome);
        strcpy(h->vacinas[h->totalVacinas].data, data);
        strcpy(h->vacinas[h->totalVacinas].status, status);

        h->totalVacinas++;
    }
}

// essa fun��o exibe o hist�rico completo (equivalente � tabela do HTML)
void mostrarHistorico(Historico *h, char *nomePaciente)
{
    printf("\n=== HISTORICO DE VACINAS ===\n");
    printf("Paciente: %s\n", nomePaciente);

    if (h->totalVacinas == 0)
    {
        printf("Nenhuma vacina registrada.\n");
        return;
    }

    int i;
    for (i = 0; i < h->totalVacinas; i++)
    {
        printf("[%d] Vacina: %s | Data: %s | Status: %s\n",
               i + 1,
               h->vacinas[i].nome,
               h->vacinas[i].data,
               h->vacinas[i].status);
    }
}

// fun��o que representa o bot�o "Agendar Vacina" (ainda n�o implementada)
void agendarVacina()
{
    printf("\n[!] Funcao de agendamento ainda nao implementada.\n");
}

// ================== MOCK (SIMULA��O) ==================

// essa fun��o simula dados iniciais, igual ao que fizemos no JS
void carregarDadosIniciais(Historico *h)
{
    registrarVacina(h, "Gripe", "01/05/2026", "Tomada");
    registrarVacina(h, "Covid", "10/05/2026", "Agendada");
}

// ================== MAIN ==================

// fun��o principal onde o programa roda
int main()
{
    Paciente paciente;
    Historico historico;

    historico.totalVacinas = 0;

    // simulando dados iniciais
    carregarDadosIniciais(&historico);

    // cadastro do paciente
    cadastrarPaciente(&paciente);

    int opcao;
    char buffer[10];

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Ver historico\n");
        printf("2 - Agendar vacina\n");
        printf("0 - Sair\n");
        printf("Opcao: ");

        fgets(buffer, sizeof(buffer), stdin);
        opcao = atoi(buffer);

        switch (opcao)
        {
            case 1:
                mostrarHistorico(&historico, paciente.nome);
                break;

            case 2:
                agendarVacina(); // ainda n�o implementado
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
