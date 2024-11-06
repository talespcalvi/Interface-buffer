/** 
* Arquivo: lcdebuff.c
* -----------------
* Este arquivo implementa a interface buffer.h utilizando
* os tipos de dados 'celulaTCD' e 'bufferTCD'.
*/

#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>

/** 
 * Tipo: struct celulaTCD
 * ----------------------
 * Estrutura que representa uma célula na lista circular duplamente encadeada,
 * que contém um caractere e ponteiros para a célula seguinte e a anterior.
 */
typedef struct celulaTCD 
{
    char letra;
    struct celulaTCD *proximo;
    struct celulaTCD *anterior;
} celulaTCD;

/**
 * Tipo: struct bufferTCD
 * ----------------------
 * Estrutura que representa o buffer do editor, contendo uma célula inicial
 * (dummy) e um cursor para navegação dentro do buffer.
 */
typedef struct bufferTCD 
{
    celulaTCD *inicio;
    celulaTCD *cursor;
} bufferTCD;

/**
 * FUNÇÃO: criar_buffer
 * Uso: buffer = criar_buffer();
 * -----------------------------
 * Inicializa um novo buffer alocando espaço para ele e configurando
 * o cursor e o início do buffer para apontarem para a célula inicial.
 * Retorna o buffer alocado ou NULL em caso de falha de alocação.
 */
bufferTAD criar_buffer(void) 
{
    bufferTAD buffer = malloc(sizeof(bufferTCD));
    if (buffer == NULL) 
    {
        fprintf(stderr, "ERRO: IMPOSSÍVEL ALOCAR BUFFER.\n");
        free(buffer);
        return NULL;
    }

    buffer->inicio->proximo = buffer->inicio;
    buffer->inicio->anterior = buffer->inicio;
    buffer->cursor = buffer->inicio;

    return buffer;
}

/**
 * PROCEDIMENTO: liberar_buffer
 * Uso: liberar_buffer(&buffer);
 * -----------------------------
 * Libera toda a memória alocada para o buffer, incluindo todas as células
 * dentro dele. Após essa chamada, o ponteiro para o buffer é definido como NULL.
 */
void liberar_buffer(bufferTAD *buffer) 
{
    if (buffer == NULL || *buffer == NULL) return;

    celulaTCD *atual = (*buffer)->inicio->proximo;
    while (atual != (*buffer)->inicio) 
    {
        celulaTCD *proxima = atual->proximo;
        free(atual);
        atual = proxima;
    }

    free((*buffer)->inicio);
    free(*buffer);
    *buffer = NULL;
}

/**
 * PROCEDIMENTO: mover_cursor_para_frente
 * Uso: mover_cursor_para_frente(buffer);
 * --------------------------------------
 * Move o cursor do buffer para a próxima célula, se existir.
 */
void mover_cursor_para_frente(bufferTAD buffer) 
{
    if (buffer != NULL && buffer->cursor->proximo != NULL) 
    {
        buffer->cursor = buffer->cursor->proximo;
    }
}

/**
 * PROCEDIMENTO: mover_cursor_para_tras
 * Uso: mover_cursor_para_tras(buffer);
 * ------------------------------------
 * Move o cursor do buffer para a célula anterior, se existir.
 */
void mover_cursor_para_tras(bufferTAD buffer) 
{
    if (buffer != NULL && buffer->cursor->anterior != NULL) 
    {
        buffer->cursor = buffer->cursor->anterior;
    }
}

/**
 * PROCEDIMENTO: mover_cursor_para_inicio
 * Uso: mover_cursor_para_inicio(buffer);
 * --------------------------------------
 * Posiciona o cursor na primeira célula útil (após a célula inicial) do buffer.
 */
void mover_cursor_para_inicio(bufferTAD buffer) 
{
    if (buffer != NULL) buffer->cursor = buffer->inicio;
}

/**
 * PROCEDIMENTO: mover_cursor_para_final
 * Uso: mover_cursor_para_final(buffer);
 * -------------------------------------
 * Posiciona o cursor na última célula útil do buffer.
 */
void mover_cursor_para_final(bufferTAD buffer) 
{
    if (buffer != NULL) buffer->cursor = buffer->inicio->anterior;
}

/**
 * PROCEDIMENTO: inserir_caractere
 * Uso: inserir_caractere(buffer, 'A');
 * ------------------------------------
 * Insere um novo caractere na posição do cursor. A nova célula é adicionada
 * após o cursor, e o cursor é movido para a nova célula.
 */
void inserir_caractere(bufferTAD buffer, char c) 
{
    if (buffer == NULL) return;

    celulaTCD *nova_celula = malloc(sizeof(celulaTCD));
    if (nova_celula == NULL) 
    {
        fprintf(stderr, "ERRO: IMPOSSÍVEL ALOCAR NOVA CÉLULA.");
        exit(1);
    }

    nova_celula->letra = c;
    nova_celula->proximo = buffer->cursor->proximo;
    nova_celula->anterior = buffer->cursor;

    buffer->cursor->proximo->anterior = nova_celula;
    buffer->cursor->proximo = nova_celula;
    buffer->cursor = nova_celula;
}

/**
 * PROCEDIMENTO: apagar_caractere
 * Uso: apagar_caractere(buffer);
 * ------------------------------
 * Remove a célula atual apontada pelo cursor do buffer.
 */
void apagar_caractere(bufferTAD buffer) 
{
    if (buffer == NULL || buffer->cursor->proximo == buffer->inicio) return;

    celulaTCD *remover = buffer->cursor->proximo;
    buffer->cursor->proximo = remover->proximo;
    remover->proximo->anterior = buffer->cursor;
    free(remover);
}

/**
 * PROCEDIMENTO: exibir_buffer
 * Uso: exibir_buffer(buffer);
 * ---------------------------
 * Exibe o conteúdo do buffer a partir da primeira célula útil.
 * Após exibir os caracteres, posiciona o cursor.
 */
void exibir_buffer(bufferTAD buffer) 
{
    if (buffer == NULL) return;

    for (celulaTCD *atual = buffer->inicio->proximo; atual != buffer->inicio; atual = atual->proximo) 
    {
        printf(" %c", atual->letra);
    }
    printf("\n");

    celulaTCD *atual = buffer->inicio->proximo;
    while (atual != buffer->cursor) 
    {
        printf(" ");
        atual = atual->proximo;
    }
    printf("\n");
}
