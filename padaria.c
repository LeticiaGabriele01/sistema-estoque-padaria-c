/*
 * ============================================================
 *   SISTEMA DE PADARIA
 *   Disciplina: Laboratório de Programação
 *   Linguagem: C
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/* ============================================================
 *  CONSTANTES
 * ============================================================ */
#define ARQUIVO_DADOS "produtos.dat"

/* ============================================================
 *  STRUCT DO PRODUTO (conforme especificado no enunciado)
 * ============================================================ */
typedef struct {
    int   codigo;
    char  nome[50];
    float preco;
    int   quantidade;
} Produto;

/* ============================================================
 *  PROTÓTIPOS
 * ============================================================ */
void menu_principal(void);
void cadastrar_produto(void);
void listar_produtos(void);
void buscar_por_codigo(void);
void limpar_buffer(void);
void exibir_produto(const Produto *p);
int  codigo_existe(int codigo);

/* ============================================================
 *  MAIN
 * ============================================================ */
int main(void) {
    setlocale(LC_ALL, "Portuguese");
    menu_principal();
    return 0;
}

/* ============================================================
 *  UTILITÁRIOS
 * ============================================================ */

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibir_produto(const Produto *p) {
    printf("  +------------------------------------------+\n");
    printf("  | Codigo    : %-28d |\n", p->codigo);
    printf("  | Nome      : %-28s |\n", p->nome);
    printf("  | Preco     : R$ %-25.2f |\n", p->preco);
    printf("  | Quantidade: %-28d |\n", p->quantidade);
    printf("  +------------------------------------------+\n");
}

/* Verifica se um código já existe no arquivo */
int codigo_existe(int codigo) {
    FILE *fp = fopen(ARQUIVO_DADOS, "rb");
    if (fp == NULL) return 0;   /* Arquivo ainda não existe */

    Produto p;
    while (fread(&p, sizeof(Produto), 1, fp) == 1) {
        if (p.codigo == codigo) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

/* ============================================================
 *  MENU PRINCIPAL
 * ============================================================ */
void menu_principal(void) {
    int opcao;

    while (1) {
        printf("\n");
        printf("  ===== SISTEMA DE PADARIA =====\n");
        printf("  1 - Cadastrar produto\n");
        printf("  2 - Listar produtos\n");
        printf("  3 - Buscar produto por codigo\n");
        printf("  4 - Sair\n");
        printf("  Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1: cadastrar_produto(); break;
            case 2: listar_produtos();   break;
            case 3: buscar_por_codigo(); break;
            case 4:
                printf("\n  Sistema encerrado. Ate logo!\n\n");
                return;
            default:
                printf("\n  [AVISO] Opcao invalida. Tente novamente.\n");
        }
    }
}

/* ============================================================
 *  1. CADASTRAR PRODUTO
 * ============================================================ */
void cadastrar_produto(void) {
    printf("\n  --- Cadastrar Produto ---\n");

    Produto p;

    /* Código */
    printf("  Codigo: ");
    scanf("%d", &p.codigo);
    limpar_buffer();

    if (p.codigo <= 0) {
        printf("\n  [ERRO] Codigo invalido. Deve ser maior que zero.\n");
        return;
    }

    if (codigo_existe(p.codigo)) {
        printf("\n  [ERRO] Ja existe um produto com o codigo %d.\n", p.codigo);
        return;
    }

    /* Nome */
    printf("  Nome do produto: ");
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';

    if (strlen(p.nome) == 0) {
        printf("\n  [ERRO] Nome nao pode ser vazio.\n");
        return;
    }

    /* Preço */
    printf("  Preco: ");
    scanf("%f", &p.preco);
    limpar_buffer();

    if (p.preco < 0) {
        printf("\n  [ERRO] Preco nao pode ser negativo.\n");
        return;
    }

    /* Quantidade */
    printf("  Quantidade: ");
    scanf("%d", &p.quantidade);
    limpar_buffer();

    if (p.quantidade < 0) {
        printf("\n  [ERRO] Quantidade nao pode ser negativa.\n");
        return;
    }

    /* Grava no arquivo (modo append binário) */
    FILE *fp = fopen(ARQUIVO_DADOS, "ab");
    if (fp == NULL) {
        printf("\n  [ERRO] Nao foi possivel abrir o arquivo para gravacao.\n");
        return;
    }

    fwrite(&p, sizeof(Produto), 1, fp);
    fclose(fp);

    printf("\n  Produto cadastrado com sucesso!\n");
}

/* ============================================================
 *  2. LISTAR PRODUTOS
 * ============================================================ */
void listar_produtos(void) {
    printf("\n  --- Lista de Produtos ---\n");

    FILE *fp = fopen(ARQUIVO_DADOS, "rb");
    if (fp == NULL) {
        printf("\n  [ERRO] Arquivo nao encontrado. Nenhum produto cadastrado ainda.\n");
        return;
    }

    Produto p;
    int count = 0;

    while (fread(&p, sizeof(Produto), 1, fp) == 1) {
        exibir_produto(&p);
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("  Nenhum produto cadastrado.\n");
    } else {
        printf("  Total de produtos: %d\n", count);
    }
}

/* ============================================================
 *  3. BUSCAR POR CÓDIGO
 * ============================================================ */
void buscar_por_codigo(void) {
    printf("\n  --- Buscar Produto por Codigo ---\n");

    int codigo;
    printf("  Codigo: ");
    scanf("%d", &codigo);
    limpar_buffer();

    FILE *fp = fopen(ARQUIVO_DADOS, "rb");
    if (fp == NULL) {
        printf("\n  [ERRO] Arquivo nao encontrado. Nenhum produto cadastrado ainda.\n");
        return;
    }

    Produto p;
    int encontrado = 0;

    while (fread(&p, sizeof(Produto), 1, fp) == 1) {
        if (p.codigo == codigo) {
            printf("\n  Produto encontrado:\n");
            exibir_produto(&p);
            encontrado = 1;
            break;
        }
    }
    fclose(fp);

    if (!encontrado) {
        printf("\n  Produto com codigo %d nao encontrado.\n", codigo);
    }
}
