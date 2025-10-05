#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição da struct Peca
typedef struct {
    char tipo;
    int id;
} Peca;

// Definição da struct Fila
typedef struct {
    Peca *itens;
    int frente;
    int tras;
    int capacidade;
    int tamanho;
} Fila;

// Função para inicializar a fila
Fila* inicializarFila(int capacidade) {
    Fila* fila = (Fila*) malloc(sizeof(Fila));
    if (fila == NULL) {
        printf("Erro ao alocar memória para a fila.\n");
        exit(EXIT_FAILURE);
    }

    fila->itens = (Peca*) malloc(capacidade * sizeof(Peca));
    if (fila->itens == NULL) {
        printf("Erro ao alocar memória para os itens da fila.\n");
        exit(EXIT_FAILURE);
    }

    fila->frente = 0;
    fila->tras = -1;
    fila->capacidade = capacidade;
    fila->tamanho = 0;
    return fila;
}

// Função para verificar se a fila está cheia
int filaCheia(Fila* fila) {
    return fila->tamanho == fila->capacidade;
}

// Função para verificar se a fila está vazia
int filaVazia(Fila* fila) {
    return fila->tamanho == 0;
}

// Função para inserir uma peça na fila (enqueue)
void enqueue(Fila* fila, Peca peca) {
    if (filaCheia(fila)) {
        printf("Fila cheia! Não é possível adicionar mais peças.\n");
        return;
    }

    fila->tras = (fila->tras + 1) % fila->capacidade;
    fila->itens[fila->tras] = peca;
    fila->tamanho++;
}

// Função para remover uma peça da fila (dequeue)
Peca dequeue(Fila* fila) {
    if (filaVazia(fila)) {
        Peca peca_vazia = {' ', -1};
        printf("Fila vazia! Nenhuma peça para remover.\n");
        return peca_vazia;
    }

    Peca peca_removida = fila->itens[fila->frente];
    fila->frente = (fila->frente + 1) % fila->capacidade;
    fila->tamanho--;
    return peca_removida;
}

// Função para mostrar o estado atual da fila
void mostrarFila(Fila* fila) {
    printf("Fila de peças:\n");
    if (filaVazia(fila)) {
        printf("Fila vazia.\n");
        return;
    }

    int i, index;
    for (i = 0; i < fila->tamanho; i++) {
        index = (fila->frente + i) % fila->capacidade;
        printf("[%c %d] ", fila->itens[index].tipo, fila->itens[index].id);
    }
    printf("\n");
}

// Função para gerar uma peça aleatória
Peca gerarPeca(int id) {
    char tipos_pecas[] = {'I', 'O', 'T', 'L'};
    int indice_tipo = rand() % 4;
    Peca nova_peca;
    nova_peca.tipo = tipos_pecas[indice_tipo];
    nova_peca.id = id;
    return nova_peca;
}

int main() {
    srand(time(NULL));

    int capacidade_fila = 5;
    Fila* fila_pecas = inicializarFila(capacidade_fila);
    int id_peca = 0;

    // Inicializa a fila com 5 peças (capacidade total)
    for (int i = 0; i < capacidade_fila; i++) {
        Peca nova_peca = gerarPeca(id_peca++);
        enqueue(fila_pecas, nova_peca);
    }

    int opcao;

    do {
        mostrarFila(fila_pecas);

        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca peca_jogada = dequeue(fila_pecas);
                if (peca_jogada.id != -1) {
                    printf("Peça jogada: [%c %d]\n", peca_jogada.tipo, peca_jogada.id);
                }
                break;
            }
            case 2: {
                if (!filaCheia(fila_pecas)) {
                    Peca nova_peca = gerarPeca(id_peca++);
                    enqueue(fila_pecas, nova_peca);
                    printf("Peça adicionada com sucesso!\n");
                } else {
                    printf("Fila cheia! Não foi possível adicionar nova peça.\n");
                }
                break;
            }
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    // Libera a memória alocada
    free(fila_pecas->itens);
    free(fila_pecas);

    return 0;
}


    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha

 


