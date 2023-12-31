#include <stdio.h>
#include <stdlib.h>

struct Pessoa;

typedef struct
{
    int idCarro;
    char marca[10];
    char modelo[10];
    int ano;
    char cor[10];
    int cpfProprietario;
} Carro;

typedef struct
{
    int idPessoa;
    char nome[30];
    char cpf[12];
    char endereco[50];
} Pessoa;

void CadastroPessoa()
{

    Pessoa proprietario;
    int id;

    FILE *arquivo;

    arquivo = fopen("proprietarios.bin", "rb");

    if (arquivo == NULL)
    {
        arquivo = fopen("proprietarios.bin", "wb");
        id = 1; // verifica se o arquivo é vazio, e se for, inicializa o id como 0
    } else
    {
        fseek(arquivo, -1*sizeof(Pessoa), SEEK_END); // coloca o ponteiro na posição do último proprietário para podermos pegar o id dele
        fread(&proprietario, sizeof(Pessoa), 1, arquivo);
        id = proprietario.idPessoa + 1;
    }

    fclose(arquivo);
    arquivo = fopen("proprietarios.bin", "ab");

    printf("Cadastro de motorista: \n");

    printf("Nome: ");
    scanf(" %[^\n]", proprietario.nome);

    printf("Endereço: ");
    scanf(" %[^\n]", proprietario.endereco);

    char cpf[12];

    printf("CPF: ");
    scanf(" %[^\n]", proprietario.cpf);

    proprietario.idPessoa = id;

    fwrite(&proprietario, 1, sizeof(Pessoa), arquivo);
    fclose(arquivo);
}

void ExibirMotoristas()
{
    FILE *arquivo = fopen("proprietarios.bin", "rb");

    if (arquivo == NULL)
    {
        printf("Erro ao ler arquivo!\n");
        return;
    }

    Pessoa proprietario;
    int quantidadeProprietarios = 0;

    while (fread(&proprietario, sizeof(Pessoa), 1, arquivo) == 1)
    {
        printf("Nome: %s\n", proprietario.nome);
        printf("CPF: %s\n", proprietario.cpf);
        printf("Endereço: %s\n", proprietario.endereco);
        printf("IdPessoa: %i\n", proprietario.idPessoa);
        printf("\n");
        quantidadeProprietarios++;
    }

    if (quantidadeProprietarios == 0)
    {
        printf("Sem motoristas no sistema!\n");
    }

    fclose(arquivo);
    
}

void CadastroCarros()
{
    Carro carro;

    int id;

    FILE *arquivo;

    arquivo = fopen("carros.bin", "rb");  // abrindo arquivo apenas para leitura (verificar se ele é vazio)

    if (arquivo == NULL)
    {
        arquivo = fopen("carros.bin", "wb");
        id = 1; // verifica se o arquivo é vazio, e se for, inicializa o id como 0
    } else
    {
        fseek(arquivo, -1*sizeof(Carro), SEEK_END); // coloca o ponteiro na posição do último proprietário para podermos pegar o id dele
        fread(&carro, sizeof(Carro), 1, arquivo);
        id = carro.idCarro + 1;
    }

    fclose(arquivo);
    arquivo = fopen("carros.bin", "ab");

    printf("Cadastro de veículo: \n");

    printf("Marca: ");
    scanf(" %[^\n]", carro.marca);

    printf("Modelo: ");
    scanf(" %[^\n]", carro.modelo);

    printf("Ano: ");
    scanf("%i", &carro.ano);

    printf("Cor: ");
    scanf(" %[^\n]", carro.cor);

    carro.idCarro = id;

    fwrite(&carro, 1, sizeof(Carro), arquivo);
    fclose(arquivo);
}

void ExibirCarros() // Alterar consulta para leitura de arquivo
{
    FILE *arquivo = fopen("carros.bin", "rb");

    if (arquivo == NULL)
    {
        printf("Erro ao ler arquivo!\n");
        return;
    }

    Carro carro;
    int quantidadeCarros = 0;

    while (fread(&carro, sizeof(Carro), 1, arquivo) == 1)
    {
        printf("Marca: %s\n", carro.marca);
        printf("Modelo: %s\n", carro.modelo);
        printf("Ano: %i\n", carro.ano);
        printf("Cor: %s\n", carro.cor);
        printf("CPF proprietário: %i\n", carro.cpfProprietario);
        printf("IdCarro: %i\n", carro.idCarro);
        quantidadeCarros++;
    }

    if (quantidadeCarros == 0)
    {
        printf("Sem carros no sistema!\n");
    }

    fclose(arquivo);
}

int main()
{
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
            CadastroPessoa();
            break;

        case 2:
            ExibirMotoristas();
            break;

        case 3:
            CadastroCarros();
            break;

        case 4:
            ExibirCarros();
            break;
        
        default:
            printf("Opção inválida!");
            break;
        }
    }
    while (opcao != 5);
    
}