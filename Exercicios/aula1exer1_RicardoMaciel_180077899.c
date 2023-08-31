#include <stdio.h>
#include <stdlib.h>

struct Pessoa;

typedef struct
{
    int id;
    char marca[10];
    char modelo[10];
    int ano;
    char cor[10];
    struct Pessoa *proprietario;
} Carro;

typedef struct
{
    int id;
    char nome[100];
    char cpf[11], rg[7], cnh[20];
    char endereco[50];
    Carro carros[100];
} Pessoa;

void CadastroPessoa(Pessoa *bancoMotoristas, int *quantidadeMotoristas)
{
    Pessoa proprietario;
    printf("Cadastro de motorista: \n");

    printf("Nome: ");
    scanf(" %[^\n]", proprietario.nome);

    printf("CPF: ");
    scanf(" %[^\n]", proprietario.cpf);

    printf("RG: ");
    scanf(" %[^\n]", proprietario.rg);

    printf("CNH: ");
    scanf(" %[^\n]", proprietario.cnh);

    printf("Endereço: ");
    scanf(" %[^\n]", proprietario.endereco);

    proprietario.id = *quantidadeMotoristas + 1;

    bancoMotoristas[*quantidadeMotoristas] = proprietario;
    (*quantidadeMotoristas)++;
}

void ExibirMotoristas(Pessoa *bancoMotoristas, int quantidadeMotoristas)
{
    for (int i = 0; i < quantidadeMotoristas; i++)
    {
        printf("Nome: %s\n", bancoMotoristas[i].nome);
    }
}

void CadastroCarros(Carro *bancoCarros, int *quantidadeCarros)
{
    Carro carro;

    printf("Cadastro de veículo: ");

    printf("Marca: ");
    scanf(" %[^\n]", carro.marca);

    printf("Modelo: ");
    scanf(" %[^\n]", carro.modelo);

    printf("Ano: ");
    scanf("%i", carro.ano);

    printf("Cor: ");
    scanf(" %[^\n]", carro.cor);

    printf("Proprietário: ");
    scanf(" %[^\n]", carro.proprietario);

    bancoCarros[*quantidadeCarros] = carro;
    (*quantidadeCarros)++;
}

int main()
{
    int quantidadeMaximaMotoristas = 100;
    Pessoa *bancoMotoristas = (Pessoa *) malloc(quantidadeMaximaMotoristas * (sizeof(Pessoa)));
    int quantidadeMotoristas = 0;

    int quantidadeMaximaCarros = 200;
    Carro *bancoCarros = (Carro *) malloc(quantidadeMaximaCarros * (sizeof(Carro)));
    int quantidadeCarros = 0;

    int opcao;

    do{
        printf("\n");
        printf("Escolha uma opção: \n");
        printf("Cadastro de motorista: 1\n");
        printf("Exibir motoristas: 2\n");
        printf("Cadastro de veículo: 3\n");
        scanf("%i", &opcao);
        printf("\n");

        switch (opcao)
        {
        case 1:
            CadastroPessoa(bancoMotoristas, &quantidadeMotoristas);
            break;

        case 2:
            ExibirMotoristas(bancoMotoristas, quantidadeMotoristas);
            break;
        
        default:
            printf("Opção inválida!");
            break;
        }
    }
    while (opcao != 4);
    
}