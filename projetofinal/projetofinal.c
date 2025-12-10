#include <stdio.h>
#include <string.h>

// Definicao de uma constante para o tamanho maximo do historico
#define MAX_HISTORICO 100

// =================================================================
// 1. ESTRUTURA DE DADOS
// =================================================================

typedef struct
{
    char nome[50];   // Campo para armazenar o nome do paciente
    int pas;         // Pressao Arterial Sistolica
    int pad;         // Pressao Arterial Diastolica
    float pp;        // Pressao de Pulso
    float pam;       // Pressao Arterial Media
    char classe[30]; // Classificacao do nivel de pressao
} pressao;

// =================================================================
// 2. FUNCOES AUXILIARES E PROCEDIMENTOS
// =================================================================

void cabecalho()
{
    printf("=====================================================\n");
    printf("   SISTEMA DE ANALISE HEMODINAMICA - PROJETO FINAL   \n");
    printf("-----------------------------------------------------\n");
    printf(" Desenvolvido por: Maria Luisa Oliveira\n");
    printf("=====================================================\n\n");
}

// Funcao: calcular pressões e classificacao
// Recebe um ponteiro para a struct 'pressao' e preenche os campos calculados.
void calcularPressao(pressao *p)
{
    // Formula para Pressao de Pulso (PP)
    p->pp = (float)(p->pas - p->pad);
    // Formula para Pressao Arterial Media (PAM)
    p->pam = (p->pas + 2 * p->pad) / 3.0;

    // Logica de classificacao (padrao AHA/ACC 2017)
    if (p->pas < 120 && p->pad < 80)
    {
        strcpy(p->classe, "Normal");
    }
    else if (p->pas >= 120 && p->pas <= 129 && p->pad < 80)
    {
        strcpy(p->classe, "Elevada");
    }
    else if ((p->pas >= 130 && p->pas <= 139) || (p->pad >= 80 && p->pad <= 89))
    {
        strcpy(p->classe, "Hipertensao Estagio 1");
    }
    else if (p->pas >= 140 || p->pad >= 90)
    {
        strcpy(p->classe, "Hipertensao Estagio 2");
    }
    else
    {
        // Caso de seguranca (ex: erro de digitacao ou isolada)
        strcpy(p->classe, "Indefinida");
    }
}

// Procedimento para adicionar um novo registro ao array historico
void adicionarRegistro(pressao *novo_registro, pressao historico[], int *contador)
{
    if (*contador < MAX_HISTORICO)
    {
        historico[*contador] = *novo_registro;
        (*contador)++;
        printf("\nRegistro adicionado ao historico com sucesso!\n\n");
    }
    else
    {
        printf("\nERRO: Historico cheio. Nao foi possivel adicionar o registro.\n\n");
    }
}

// Procedimento para exibir todos os registros no historico
void exibirHistorico(pressao historico[], int contador)
{
    if (contador == 0)
    {
        printf("\nNenhum registro no historico.\n\n");
        return;
    }

    printf("\n==== HISTORICO DE ANALISE HEMODINAMICA (%d Registros) ====\n", contador);
    for (int i = 0; i < contador; i++)
    {
        printf("--- Registro %d ---\n", i + 1);
        printf("Paciente: %s\n", historico[i].nome);
        printf("PAS: %d\n", historico[i].pas);
        printf("PAD: %d\n", historico[i].pad);
        printf("PP: %.2f\n", historico[i].pp);
        printf("PAM: %.2f\n", historico[i].pam);
        printf("Classificacao: %s\n", historico[i].classe);
        printf("-------------------\n");
    }
    printf("\n");
}

// =================================================================
// 3. FUNCOES ESTATISTICAS
// =================================================================

// FUNCAO 1: Media das PAMs
float calcularMediaPAM(pressao historico[], int contador)
{
    if (contador == 0) return 0.0;

    float soma_pam = 0.0;
    for (int i = 0; i < contador; i++)
    {
        soma_pam += historico[i].pam;
    }
    return soma_pam / contador;
}

// FUNCAO 2: Contar Classificacao
int contarClassificacao(pressao historico[], int contador, const char *classificacao)
{
    int contagem = 0;
    for (int i = 0; i < contador; i++)
    {
        if (strncmp(historico[i].classe, classificacao, 30) == 0)
        {
            contagem++;
        }
    }
    return contagem;
}

// FUNCAO 3: Maior PAS
int encontrarRegistroMaxPAS(pressao historico[], int contador)
{
    if (contador == 0) return -1;

    int indice_max = 0;
    int max_pas = historico[0].pas;

    for (int i = 1; i < contador; i++)
    {
        if (historico[i].pas > max_pas)
        {
            max_pas = historico[i].pas;
            indice_max = i;
        }
    }
    return indice_max;
}

// =================================================================
// 4. FUNCAO PRINCIPAL
// =================================================================

int main()
{
    int opcao;
    pressao temp_paciente;
    FILE *arquivo;
    pressao historico[MAX_HISTORICO];
    int contador_registros = 0;

    cabecalho();

    do
    {
        printf("========== MENU ==========\n");
        printf("1 - Inserir novo registro manualmente\n");
        printf("2 - Importar dados de um arquivo TXT (dados.txt)\n");
        printf("3 - Exibir HISTORICO de registros\n");
        printf("4 - Estatisticas e Analise\n");
        printf("5 - Salvar relatorio COMPLETO\n");
        printf("6 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1: // Inserção manual CORRIGIDA
            printf("\n--- Novo Registro ---\n");
            
            // Limpeza do buffer do teclado antes de ler string
            // Isso consome o 'enter' que sobrou do scanf da opcao
            while(getchar() != '\n'); 

            printf("Digite o Nome do Paciente: ");
            // Lê até encontrar uma quebra de linha (permite espaços)
            // O %49 limita a leitura para evitar estourar o vetor 'nome'
            scanf("%49[^\n]", temp_paciente.nome);

            printf("Digite a PAS: ");
            scanf("%d", &temp_paciente.pas);

            printf("Digite a PAD: ");
            scanf("%d", &temp_paciente.pad);

            calcularPressao(&temp_paciente);
            adicionarRegistro(&temp_paciente, historico, &contador_registros);
            break;

        case 2: // Importa TXT
            arquivo = fopen("dados.txt", "r");
            if (arquivo == NULL)
            {
                printf("Erro ao abrir 'dados.txt'! Certifique-se de que ele existe.\n");
                printf("Formato esperado: Nome_Sem_Espaco PAS PAD\n\n");
                break;
            }

            // CORRECAO: Adicionado %49s para segurança
            // Nota: Para arquivos simples, recomenda-se usar nomes sem espaço (ex: Maria_Luisa)
            while (fscanf(arquivo, "%49s %d %d", temp_paciente.nome, &temp_paciente.pas, &temp_paciente.pad) == 3)
            {
                calcularPressao(&temp_paciente);
                adicionarRegistro(&temp_paciente, historico, &contador_registros);
            }
            
            if (contador_registros == 0) {
                 printf("Nenhum registro valido lido ou arquivo vazio.\n");
            } else {
                 printf("Importacao concluida.\n");
            }

            fclose(arquivo);
            break;

        case 3: 
            exibirHistorico(historico, contador_registros);
            break;

        case 4: 
            if (contador_registros == 0)
            {
                printf("\nNao ha dados no historico para calcular estatisticas.\n\n");
                break;
            }

            printf("\n==== RELATORIO ESTATISTICO ====\n");
            float media_pam = calcularMediaPAM(historico, contador_registros);
            printf("Media da PAM: %.2f mmHg\n\n", media_pam);

            printf("--- Contagem por Classificacao ---\n");
            printf("Normal: %d\n", contarClassificacao(historico, contador_registros, "Normal"));
            printf("Elevada: %d\n", contarClassificacao(historico, contador_registros, "Elevada"));
            printf("Estagio 1: %d\n", contarClassificacao(historico, contador_registros, "Hipertensao Estagio 1"));
            printf("Estagio 2: %d\n", contarClassificacao(historico, contador_registros, "Hipertensao Estagio 2"));
            printf("Indefinida: %d\n\n", contarClassificacao(historico, contador_registros, "Indefinida"));

            int indice_max = encontrarRegistroMaxPAS(historico, contador_registros);
            if (indice_max != -1)
            {
                printf("--- Registro com a MAIOR PAS ---\n");
                printf("Paciente: %s\n", historico[indice_max].nome);
                printf("PAS Maxima: %d\n", historico[indice_max].pas);
                printf("Classificacao: %s\n", historico[indice_max].classe);
            }
            printf("----------------------------------\n\n");
            break;

        case 5: 
        {
            char nomeArquivo[50];
            printf("Nome do arquivo para salvar (ex: relatorio.txt): ");
            scanf("%s", nomeArquivo);

            FILE *arquivo_saida = fopen(nomeArquivo, "w");
            if (arquivo_saida == NULL)
            {
                printf("Erro ao salvar arquivo!\n\n");
                break;
            }

            fprintf(arquivo_saida, "Relatorio de Analise Hemodinamica (%d Registros)\n", contador_registros);
            fprintf(arquivo_saida, "------------------------------------------------\n");

            for (int i = 0; i < contador_registros; i++)
            {
                fprintf(arquivo_saida, "--- Registro %d ---\n", i + 1);
                fprintf(arquivo_saida, "Paciente: %s\n", historico[i].nome);
                fprintf(arquivo_saida, "PAS: %d | PAD: %d\n", historico[i].pas, historico[i].pad);
                fprintf(arquivo_saida, "PAM: %.2f | Classe: %s\n", historico[i].pam, historico[i].classe);
            }

            fprintf(arquivo_saida, "\nESTATISTICAS GERAIS\n");
            fprintf(arquivo_saida, "Media da PAM: %.2f\n", calcularMediaPAM(historico, contador_registros));

            fclose(arquivo_saida);
            printf("Relatorio salvo com sucesso!\n\n");
        }
        break;

        case 6:
            printf("Encerrando o programa...\n");
            break;

        default:
            printf("Opcao invalida!\n\n");
        }

    } while (opcao != 6);

    return 0;
}