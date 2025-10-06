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

// Definição da struct Pilha
typedef struct {
    Peca *itens;
    int topo;
    int capacidade;
} Pilha;

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

// Função para inicializar a pilha
Pilha* inicializarPilha(int capacidade) {
    Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
    if (pilha == NULL) {
        printf("Erro ao alocar memória para a pilha.\n");
        exit(EXIT_FAILURE);
    }

    pilha->itens = (Peca*) malloc(capacidade * sizeof(Peca));
    if (pilha->itens == NULL) {
        printf("Erro ao alocar memória para os itens da pilha.\n");
        exit(EXIT_FAILURE);
    }

    pilha->topo = -1;
    pilha->capacidade = capacidade;
    return pilha;
}

// Função para verificar se a fila está cheia
int filaCheia(Fila* fila) {
    return fila->tamanho == fila->capacidade;
}

// Função para verificar se a fila está vazia
int filaVazia(Fila* fila) {
    return fila->tamanho == 0;
}

// Função para verificar se a pilha está cheia
int pilhaCheia(Pilha* pilha) {
    return pilha->topo == pilha->capacidade - 1;
}

// Função para verificar se a pilha está vazia
int pilhaVazia(Pilha* pilha) {
    return pilha->topo == -1;
}

// Função para inserir uma peça na fila (enqueue)
void enqueue(Fila* fila, Peca peca) {
    if (filaCheia(fila)) {
        // Sobrescreve o elemento mais antigo
        fila->frente = (fila->frente + 1) % fila->capacidade;
        fila->tras = (fila->tras + 1) % fila->capacidade;
        fila->itens[fila->tras] = peca;
    } else {
        fila->tras = (fila->tras + 1) % fila->capacidade;
        fila->itens[fila->tras] = peca;
        fila->tamanho++;
    }
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

// Função para inserir uma peça na pilha (push)
void push(Pilha* pilha, Peca peca) {
    if (pilhaCheia(pilha)) {
        printf("Pilha cheia! Não é possível adicionar mais peças.\n");
        return;
    }

    pilha->topo++;
    pilha->itens[pilha->topo] = peca;
}

// Função para remover uma peça da pilha (pop)
Peca pop(Pilha* pilha) {
    if (pilhaVazia(pilha)) {
        Peca peca_vazia = {' ', -1};
        printf("Pilha vazia! Nenhuma peça para remover.\n");
        return peca_vazia;
    }

    Peca peca_removida = pilha->itens[pilha->topo];
    pilha->topo--;
    return peca_removida;
}

// Função para mostrar o estado atual da fila
void mostrarFila(Fila* fila) {
    printf("Fila de peças:  ");
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

// Função para mostrar o estado atual da pilha
void mostrarPilha(Pilha* pilha) {
    printf("Pilha de reserva (Topo -> Base):  ");
    if (pilhaVazia(pilha)) {
        printf("Pilha vazia.\n");
        return;
    }

    for (int i = pilha->topo; i >= 0; i--) {
        printf("[%c %d] ", pilha->itens[i].tipo, pilha->itens[i].id);
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
    int capacidade_pilha = 3;
    Fila* fila_pecas = inicializarFila(capacidade_fila);
    Pilha* pilha_reserva = inicializarPilha(capacidade_pilha);
    int id_peca = 0;

    // Inicializa a fila com 5 peças (capacidade total)
    for (int i = 0; i < capacidade_fila; i++) {
        Peca nova_peca = gerarPeca(id_peca++);
        enqueue(fila_pecas, nova_peca);
    }

    int opcao;

    do {
        printf("\nEstado atual:\n");
        mostrarFila(fila_pecas);
        mostrarPilha(pilha_reserva);

        printf("\nOpções de Ação:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca peca_jogada = dequeue(fila_pecas);
                if (peca_jogada.id != -1) {
                    printf("Peça jogada: [%c %d]\n", peca_jogada.tipo, peca_jogada.id);
                }
                // Adiciona uma nova peça ao final da fila
                Peca nova_peca = gerarPeca(id_peca++);
                enqueue(fila_pecas, nova_peca);
                break;
            }
            case 2: {
                if (!filaVazia(fila_pecas) && !pilhaCheia(pilha_reserva)) {
                    Peca peca_reservada = dequeue(fila_pecas);
                    push(pilha_reserva, peca_reservada);
                    printf("Peça [%c %d] reservada com sucesso.\n", peca_reservada.tipo, peca_reservada.id);

                    // Adiciona uma nova peça ao final da fila
                    Peca nova_peca = gerarPeca(id_peca++);
                    enqueue(fila_pecas, nova_peca);

                } else {
                    if(filaVazia(fila_pecas)){
                        printf("Não há peças para reservar, a fila está vazia.\n");
                    } else {
                        printf("Pilha de reserva cheia. Não é possível reservar.\n");
                    }

                }
                break;
            }
            case 3: {
                Peca peca_usada = pop(pilha_reserva);
                if (peca_usada.id != -1) {
                    printf("Peça reservada usada: [%c %d]\n", peca_usada.tipo, peca_usada.id);
                    enqueue(fila_pecas, peca_usada); // Adiciona a peça usada de volta à fila
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
    free(pilha_reserva->itens);
    free(pilha_reserva);

    return 0;
}
