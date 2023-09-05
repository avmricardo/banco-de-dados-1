#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pessoa;

typedef struct
{
    int idCarro;
    char marca[10];
    char modelo[10];
    int ano;
    char cor[10];
    char renavam[12];
    char cpfProprietario[12];
} Carro;

typedef struct
{
    int idPessoa;
    char nome[30];
    char cpf[12];
    char endereco[50];
} Pessoa;


int CPFJaCadastrado(char *cpf)
{
    FILE *arquivo = fopen("proprietarios.bin", "rb");

    if (arquivo == NULL)
    {
        printf("Erro ao ler arquivo!\n");
        return 0; // Retorna 0 para indicar erro
    }

    Pessoa proprietario;

    while (fread(&proprietario, sizeof(Pessoa), 1, arquivo) == 1)
    {
        if (strcmp(proprietario.cpf, cpf) == 0)
        {
            fclose(arquivo);
            return 1; // Retorna 1 para indicar que o CPF já está cadastrado
        }
    }

    fclose(arquivo);
    return 0; // Retorna 0 para indicar que o CPF não está cadastrado
}


void InserirOrdenadoPorCPF(Pessoa novaPessoa)
{
    FILE *arquivo = fopen("proprietarios.bin", "r+b");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Pessoa proprietario;
    int posicaoInserir = 0;

    // Encontra a posição correta para inserção
    while (fread(&proprietario, sizeof(Pessoa), 1, arquivo) == 1)
    {
        if (strcmp(novaPessoa.cpf, proprietario.cpf) < 0)
            break;
        posicaoInserir++;
    }

    // Move os registros após a posição de inserção para frente
    fseek(arquivo, 0, SEEK_END);
    int tamanhoDeslocamento = (ftell(arquivo) - (posicaoInserir * sizeof(Pessoa)));

    for (int i = ftell(arquivo) / sizeof(Pessoa); i > posicaoInserir; i--)
    {
        fseek(arquivo, (i - 1) * sizeof(Pessoa), SEEK_SET);
        fread(&proprietario, sizeof(Pessoa), 1, arquivo);
        fseek(arquivo, i * sizeof(Pessoa), SEEK_SET);
        fwrite(&proprietario, sizeof(Pessoa), 1, arquivo);
    }

    // Volta para a posição correta e escreve a nova pessoa
    fseek(arquivo, posicaoInserir * sizeof(Pessoa), SEEK_SET);
    fwrite(&novaPessoa, sizeof(Pessoa), 1, arquivo);

    fclose(arquivo);
}


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

    printf("CPF: ");
    scanf(" %[^\n]", proprietario.cpf);

    if (CPFJaCadastrado(proprietario.cpf))
    {
        printf("CPF já cadastrado no sistema!\n");
        return;
    }

    proprietario.idPessoa = id;

    InserirOrdenadoPorCPF(proprietario);
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


int RenavamJaCadastrado(char *renavam)
{
    FILE *arquivo = fopen("carros.bin", "rb");

    if (arquivo == NULL)
    {
        printf("Erro ao ler arquivo!\n");
        return 0; // Retorna 0 para indicar erro
    }

    Carro carro;

    while (fread(&carro, sizeof(Carro), 1, arquivo) == 1)
    {
        if (strcmp(carro.renavam, renavam) == 0)
        {
            fclose(arquivo);
            return 1; // Retorna 1 para indicar que o CPF já está cadastrado
        }
    }

    fclose(arquivo);
    return 0; // Retorna 0 para indicar que o CPF não está cadastrado
}


void InserirOrdenadoPorRenavam(Carro novoCarro)
{
    FILE *arquivo = fopen("carros.bin", "r+b");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Carro carro;
    int posicaoInserir = 0;

    // Encontra a posição correta para inserção
    while (fread(&carro, sizeof(Carro), 1, arquivo) == 1)
    {
        if (strcmp(novoCarro.renavam, carro.renavam) < 0)
            break;
        posicaoInserir++;
    }

    // Move os registros após a posição de inserção para frente
    fseek(arquivo, 0, SEEK_END);
    int tamanhoDeslocamento = (ftell(arquivo) - (posicaoInserir * sizeof(Carro)));

    for (int i = ftell(arquivo) / sizeof(Carro); i > posicaoInserir; i--)
    {
        fseek(arquivo, (i - 1) * sizeof(Carro), SEEK_SET);
        fread(&carro, sizeof(Carro), 1, arquivo);
        fseek(arquivo, i * sizeof(Carro), SEEK_SET);
        fwrite(&carro, sizeof(Carro), 1, arquivo);
    }

    // Volta para a posição correta e escreve a nova pessoa
    fseek(arquivo, posicaoInserir * sizeof(Carro), SEEK_SET);
    fwrite(&novoCarro, sizeof(Carro), 1, arquivo);

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
    
    printf("RENAVAM: ");
    scanf(" %[^\n]", carro.renavam);

    if (RenavamJaCadastrado(carro.renavam))
    {
        printf("RENAVAM já cadastrado no sistema!\n");
        return;
    }

    printf("Ano: ");
    scanf("%i", &carro.ano);

    printf("Cor: ");
    scanf(" %[^\n]", carro.cor);

    printf("CPF do proprietário: ");
    scanf(" %[^\n]", carro.cpfProprietario);

    if (!CPFJaCadastrado(carro.cpfProprietario))
    {
        printf("CPF não cadastrado no sistema!\n Cadastre o motorista antes.\n");
        return;
    }

    carro.idCarro = id;

    InserirOrdenadoPorRenavam(carro);
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
        printf("CPF proprietário: %s\n", carro.cpfProprietario);
        printf("RENAVAM: %s\n", carro.renavam);
        printf("\n");
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