#include "Headers/controleArquivo.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"
#define ERRO_ABRIR_ARQUIVO "\n\tERRO: Erro na abertura do arquivo!\n"
#define ERRO_CRIAR_ARQUIVO "\n\tERRO: Erro ao criar o arquivo!\n"

#define MENSSAGE_LENDO_ARQUIVO "\n\tAVISO: Lendo arquivo, por favor aguarde...\n"
#define DIRETORIO_ARQUIVO_ENTRADA "../entrada/aleatorio300000.txt"
#define DIRETORIO_ARQUIVO_SAIDA "../saida/"
#define LINE_MAX_LENGTH 255
#define FILE_NAME_MAX_LENGTH 31
#define DELIMITER ";"

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

aluno *readNextAluno(FILE *fp);

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

aluno *readNextAluno(FILE *fp) {
    aluno *aluno = allocStudant();
    char *line = (char *) malloc((LINE_MAX_LENGTH + 1) * sizeof(char));
    char *ptr;

    fscanf(fp, " %[^\n]%*c", line);
    ptr = strtok(line, DELIMITER);
    aluno->matricula = (int) atof(ptr);

    ptr = strtok(NULL, DELIMITER);
    strcpy(aluno->nome, ptr);

    ptr = strtok(NULL, DELIMITER);
    aluno->nota = (int) atof(ptr);

    free(line);

    return aluno;
}
// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=

biTree * readTreeAlunoFromFile(biTree * tree)
{
    FILE *fp = fopen(DIRETORIO_ARQUIVO_ENTRADA, "r");
    int contador = 0;
    int registros;

    if (!fp)
    {
        printf(ERRO_ABRIR_ARQUIVO);
        return NULL;
    }

    printf(MENSSAGE_LENDO_ARQUIVO);
    fscanf(fp, "%d", &registros);
    while (!feof(fp) && contador < registros)
    {
        aluno * a = readNextAluno(fp);
        tree = insertStudant(tree, a);
        contador++;
    }
    fclose(fp);
    return tree;
}

void writeTreeOnFile(biTree * root, int typePrint)
{
    int nomeArquivoSaidaLength = strlen(DIRETORIO_ARQUIVO_SAIDA) + FILE_NAME_MAX_LENGTH + 1;
    char *nomeArquivoSaida = (char *)malloc(nomeArquivoSaidaLength * sizeof(char));
    FILE *fp;

    if (!fp)
    {
        printf(ERRO_CRIAR_ARQUIVO);
        return;
    }

    switch (typePrint) {
        case 1:
            sprintf(nomeArquivoSaida, "%ssaida-%s.txt", DIRETORIO_ARQUIVO_SAIDA, "PreOrder");
            fp = fopen(nomeArquivoSaida, "w");
            writePreOrder(fp, root->root);
            fclose(fp);
            break;
        case 2:
            sprintf(nomeArquivoSaida, "%ssaida-%s.txt", DIRETORIO_ARQUIVO_SAIDA, "InOrder");
            fp = fopen(nomeArquivoSaida, "w");
            writeInOrder(fp, root->root);
            fclose(fp);
            break;
        case 3:
            sprintf(nomeArquivoSaida, "%ssaida-%s.txt", DIRETORIO_ARQUIVO_SAIDA, "PosOrder");
            fp = fopen(nomeArquivoSaida, "w");
            writePosOrder(fp, root->root);
            fclose(fp);
            break;
        case 4:
            printf("\nSAIR\n");
            break;
        default:
            printf("\nPOR FAVOR DIGITE UM NUMERO CORRETO!\n");
            break;
    }
}

void writeMenu(biTree * root){
    int res = 0;
    while(res != 4){
        printf("\n\nMetodos de printar a arvore:\n");
        printf("1 - Print pre Order\n");
        printf("2 - Print in Order\n");
        printf("3 - Print pos order\n");
        printf("4 - Nao desejo mais escrever o arquivo\n");
        printf("Digite qual voce quer: ");
        scanf("%d", &res);
        writeTreeOnFile(root, res);
    }
}

void writePreOrder(FILE * fp, node * root){
    if(root == NULL){}
    else{
        aluno *a = root->element;
        fprintf(fp,"%d;%s;%d\n", a->matricula, a->nome, a->nota);
        writePreOrder(fp, root->left);
        writePreOrder(fp, root->right);
    }
}

void writeInOrder(FILE * fp, node * root){
    if(root == NULL){}
    else{
        aluno *a = root->element;
        writeInOrder(fp, root->left);
        fprintf(fp,"%d;%s;%d\n", a->matricula, a->nome, a->nota);
        writeInOrder(fp, root->right);
    }
}

void writePosOrder(FILE * fp, node * root){
    if(root == NULL){}
    else{
        aluno *a = root->element;
        writePosOrder(fp, root->left);
        writePosOrder(fp, root->right);
        fprintf(fp,"%d;%s;%d\n", a->matricula, a->nome, a->nota);
    }
}
