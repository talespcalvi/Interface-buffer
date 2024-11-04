#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct celulaTCD
{
    char letra;
    struct celulaTCD *proximo;
    struct celulaTCD *anterior;
} celulaTCD;

typedef struct bufferTCD 
{
    celulaTCD *inicio;
    celulaTCD *cursor;
} bufferTCD;

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

void mover_cursor_para_frente(bufferTAD buffer)
{
    if (buffer != NULL && buffer->cursor->proximo != NULL)
    {
        buffer->cursor = buffer->cursor->proximo;
    }
}

void mover_cursor_para_tras(bufferTAD buffer)
{
    if (buffer != NULL && buffer->cursor->anterior != NULL)
    {
        buffer->cursor = buffer->cursor->anterior;
    }
}

void mover_cursor_para_inicio(bufferTAD buffer)
{
    if (buffer != NULL) buffer->cursor = buffer->inicio;
}

void mover_cursor_para_final(bufferTAD buffer)
{
    if (buffer != NULL) buffer->cursor = buffer->inicio->anterior;
}

void inserir_caractere(bufferTAD buffer, char c)
{
    if (buffer = NULL) return;

    celulaTCD *nova_celula = malloc(sizeof(celulaTCD));
    if (nova_celula === NULL)
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

void apagar_caractere(bufferTAD buffer)
{
    if (buffer == NULL || buffer->cursor->proximo == buffer->inicio) return;

    celulaTCD *remover = buffer->cursor->proximo;
    buffer->cursor->proximo = remover->proximo;
    remover->proximo->anterior = buffer->cursor;
    free(remover);
}

void exibir_buffer(bufferTAD buffer)
{
    if (buffer == NULL) return;

    for (celulaTCD *atual = buffer->inicio->proximo; atual != buffer->inicio; atual = atual->proximo;)
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