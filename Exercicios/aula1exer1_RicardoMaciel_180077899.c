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
    int id;

    FILE *arquivo;

    arquivo = fopen("proprietarios.bin", "ab");

    if (arquivo == NULL)
    {
        id = 0; // verifica se o arquivo é vazio, e se for, inicializa o id como 0
    } else
    {
        fseek(arquivo, -1*sizeof(Pessoa), SEEK_END); // coloca o ponteiro na posição do último proprietário para podermos pegar o id dele
        fread(&proprietario, sizeof(Pessoa), 1, arquivo);
        id = proprietario.id + 1;
    }

    fclose(arquivo);
    arquivo = fopen("proprietarios.bin", "wb");

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

    fwrite(&proprietario, 1, sizeof(Pessoa), arquivo);
    fclose(arquivo);
}

void ExibirMotoristas(Pessoa *bancoMotoristas, int quantidadeMotoristas) // Alterar consulta para leitura de arquivo
{
    for (int i = 0; i < quantidadeMotoristas; i++)
    {
        printf("Nome: %s\n", bancoMotoristas[i].nome);
    }
}

void CadastroCarros(Carro *bancoCarros, int *quantidadeCarros)
{
    Carro carro;

    int id;

    FILE *arquivo;

    arquivo = fopen("carros.bin", "ab");  // abrindo arquivo apenas para leitura (verificar se ele é vazio)

    if (arquivo == NULL)
    {
        id = 0; // verifica se o arquivo é vazio, e se for, inicializa o id como 0
    } else
    {
        fseek(arquivo, -1*sizeof(Carro), SEEK_END); // coloca o ponteiro na posição do último proprietário para podermos pegar o id dele
        fread(&carro, sizeof(Carro), 1, arquivo);
        id = carro.id + 1;
    }

    printf("Cadastro de veículo: \n");

    printf("Marca: ");
    scanf(" %[^\n]", carro.marca);

    printf("Modelo: ");
    scanf(" %[^\n]", carro.modelo);

    printf("Ano: ");
    scanf("%i", &carro.ano);

    printf("Cor: ");
    scanf(" %[^\n]", carro.cor);

    // printf("Proprietário: ");
    // scanf(" %[^\n]", carro.proprietario);

    bancoCarros[*quantidadeCarros] = carro;
    (*quantidadeCarros)++;

    fwrite(&carro, 1, sizeof(Carro), arquivo);
    fclose(arquivo);
}

void ExibirCarros(Carro *bancoCarros, int quantidadeCarros) // Alterar consulta para leitura de arquivo
{
    for (int i = 0; i < quantidadeCarros; i++)
    {
        printf("Marca: %s\n", bancoCarros[i].marca);
        printf("Modelo: %s\n", bancoCarros[i].modelo);
        printf("Ano: %i\n", bancoCarros[i].ano);
        printf("Cor: %s\n", bancoCarros[i].cor);
    }
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
        printf("Exibir carros: 4\n");
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

        case 3:
            CadastroCarros(bancoCarros, &quantidadeCarros);
            break;

        case 4:
            ExibirCarros(bancoCarros, quantidadeCarros);
            break;
        
        default:
            printf("Opção inválida!");
            break;
        }
    }
    while (opcao != 5);
    
}