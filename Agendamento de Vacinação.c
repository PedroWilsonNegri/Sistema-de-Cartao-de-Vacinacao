/*Um sistema de cadastro básico, onde um paciente deve inserir seus dados de:
Nome, Idade, Data de Nascimento e CPF. Após o cadastro, o paciente deve ser
solicitado o nome de uma vacina necessária ou da vacina desejada a ser tomada,
onde a vacina deve apresentar, Lote, Validade e Fabricante Laboratorial.
Assim solicitando uma data de agendamento para a aplicação, juntamente com o
local e horário.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
    char nome[50];
    char dataNascimento[15];
    char cpf[15];
    int idade;
} Paciente;

typedef struct 
{
    char nomeVacina[50];
    char lote[10];
    char validade[11];
    char fabricante[50];
} Vacina;

typedef struct 
{
    Vacina vacinas[6]; 
    int numVacinas;
} BancoDeDados;

const char *vacinaNomes[] = {"Gripe", "Hepatite A e B", "Anti-Rabica", "Anti-Tetanica", "BCG", "Covid"};
const char *vacinaLots[] = {"12345", "67890", "ABCDE", "FGHI", "JKLMN", "OPQR"};
const char *vacinaValidades[] = {"01/01/2026", "02/01/2026", "03/01/2026", "04/01/2026", "05/01/2026", "06/01/2026"};
const char *vacinaFabricantes[] = {"Lab X", "Lab Y", "Lab Z", "Lab A", "Lab B", "Lab C"};

void lerPaciente(Paciente *p) 
{
    char bufferIdade[10];

    printf("--- Cadastro do Paciente ---\n");
    printf("Nome: ");
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = '\0'; 
    
    // FORMA SEGURA: Le a idade como texto e converte para evitar crash de buffer
    printf("Idade: ");
    fgets(bufferIdade, sizeof(bufferIdade), stdin);
    p->idade = atoi(bufferIdade); 
    
    printf("Data de Nascimento (DD/MM/AAAA): ");
    fgets(p->dataNascimento, sizeof(p->dataNascimento), stdin);
    p->dataNascimento[strcspn(p->dataNascimento, "\n")] = '\0'; 
    
    printf("CPF: ");
    fgets(p->cpf, sizeof(p->cpf), stdin);
    p->cpf[strcspn(p->cpf, "\n")] = '\0'; 
}

void lerVacina(BancoDeDados *bd) 
{
    char bufferOpcao[10];
    int opcao, i;

    printf("\n--- Selecione uma vacina ---\n");
    for(i = 0; i < 6; i++) 
	{
        printf("%d - %s\n", i + 1, vacinaNomes[i]);
    }
    
    printf("Opcao (1-6): ");
    fgets(bufferOpcao, sizeof(bufferOpcao), stdin);
    opcao = atoi(bufferOpcao);

    if (opcao >= 1 && opcao <= 6) 
	{
        int idx = opcao - 1;
        if (bd->numVacinas < 6) 
		{
            strcpy(bd->vacinas[bd->numVacinas].nomeVacina, vacinaNomes[idx]);
            strcpy(bd->vacinas[bd->numVacinas].lote, vacinaLots[idx]);
            strcpy(bd->vacinas[bd->numVacinas].validade, vacinaValidades[idx]);
            strcpy(bd->vacinas[bd->numVacinas].fabricante, vacinaFabricantes[idx]);
            bd->numVacinas++;
            printf(">> Vacina selecionada com sucesso!\n");
        }
    } else 
    {
        printf(">> Opcao invalida.\n");
    }
}

int main() 
{
    Paciente paciente;
    BancoDeDados bd;
    bd.numVacinas = 0;

    lerPaciente(&paciente);
    lerVacina(&bd);

    if (bd.numVacinas > 0) 
	{
        char dataA[15], local[50], hora[10];
        
        printf("\n--- Dados do Agendamento ---\n");
        printf("Data da aplicacao: ");
        fgets(dataA, sizeof(dataA), stdin);
        dataA[strcspn(dataA, "\n")] = '\0';

        printf("Local: ");
        fgets(local, sizeof(local), stdin);
        local[strcspn(local, "\n")] = '\0';

        printf("Horario: ");
        fgets(hora, sizeof(hora), stdin);
        hora[strcspn(hora, "\n")] = '\0';

        printf("\n============================\n");
        printf("   RESUMO DO AGENDAMENTO\n");
        printf("============================\n");
        printf("Paciente: %s\n", paciente.nome);
        printf("CPF: %s | Idade: %d\n", paciente.cpf, paciente.idade);
        printf("Vacina: %s\n", bd.vacinas[bd.numVacinas-1].nomeVacina);
        printf("Lote: %s | Lab: %s\n", bd.vacinas[bd.numVacinas-1].lote, bd.vacinas[bd.numVacinas-1].fabricante);
        printf("Data: %s as %s\n", dataA, hora);
        printf("Local: %s\n", local);
        printf("============================\n");
    }

    printf("\nPressione Enter para sair...");
    getchar(); 
    return 0;
}
