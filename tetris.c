#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#define MAX 5  // Capacidade máxima da fila

// Estrutura para representar uma peça do Tetris
typedef struct {
    char Nome;  // Tipo da peça: 'I', 'O', 'T', 'L'
    int Id;     // Identificador único
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[MAX];
    int Inicio;
    int Fim;
    int Total;
} Fila;

// Função para inicializar a fila
void inicializarFila(Fila *f) {
    f->Inicio = 0;
    f->Fim = 0;
    f->Total = 0;
}

// Função para verificar se a fila está vazia
int filaVazia(Fila *f) {
    return f->Total == 0;
}

// Função para verificar se a fila está cheia
int filaCheia(Fila *f) {
    return f->Total == MAX;
}

// Função para gerar uma nova peça aleatória
Peca gerarPeca(int id) {
    Peca NovaPeca;
    char Tipos[] = {'I', 'O', 'T', 'L'};
    
    // Gera um tipo aleatório
    int Indice = rand() % 4;
    NovaPeca.Nome = Tipos[Indice];
    NovaPeca.Id = id;
    
    return NovaPeca;
}

// Função para inserir uma peça na fila (enqueue)
void inserir(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia. Não é possível inserir.\n");
        return;
    }
    
    f->itens[f->Fim] = p;
    f->Fim = (f->Fim + 1) % MAX;  // Atualização circular
    f->Total++;
}

// Função para remover uma peça da fila (dequeue)
Peca remover(Fila *f) {
    Peca pecaVazia = {' ', -1};  // Peça vazia para indicar erro
    
    if (filaVazia(f)) {
        printf("Fila vazia. Não é possível remover.\n");
        return pecaVazia;
    }
    
    Peca pecaRemovida = f->itens[f->Inicio];
    f->Inicio = (f->Inicio + 1) % MAX;  // Atualização circular
    f->Total--;
    
    return pecaRemovida;
}

// Função para exibir o estado atual da fila
void mostrarFila(Fila *f) {
    printf("\n=== FILA DE PEÇAS ===\n");
    
    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return;
    }
    
    printf("Ordem: ");
    int i, idx;
    for (i = 0, idx = f->Inicio; i < f->Total; i++, idx = (idx + 1) % MAX) {
        printf("[%c %d] ", f->itens[idx].Nome, f->itens[idx].Id);
    }
    printf("\n");
}

// Função para exibir o menu de opções
void mostrarMenu() {
    printf("\n=== TETRIS STACK  ===\n");
    printf("Opções disponíveis:\n");
    printf("1 - Jogar peça (dequeue)\n");
    printf("2 - Inserir nova peça (enqueue)\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

int main() {

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.



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
    Fila filaPecas;
    int Opcao;
    int ProximoId = 0;
    
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    // Inicializa a fila
    inicializarFila(&filaPecas);
    
    // Preenche a fila inicial com 5 peças
    printf("Inicializando fila com 5 peças...\n");
    for (int i = 0; i < MAX; i++) {
        Peca novaPeca = gerarPeca(ProximoId++);
        inserir(&filaPecas, novaPeca);
    }
    
    printf("Fila inicial criada com sucesso!\n");
    
    // Loop principal do programa
    do {
        mostrarFila(&filaPecas);
        mostrarMenu();
        scanf("%d", &Opcao);
        
        switch (Opcao) {
            case 1: // Jogar peça (remover da frente)
                {
                    Peca pecaRemovida = remover(&filaPecas);
                    if (pecaRemovida.Id != -1) {
                        printf("Peça jogada: [%c %d]\n", pecaRemovida.Nome, pecaRemovida.Id);
                        
                        // Gera uma nova peça para manter a fila cheia (se possível)
                        if (!filaCheia(&filaPecas)) {
                            Peca novaPeca = gerarPeca(ProximoId++);
                            inserir(&filaPecas, novaPeca);
                            printf("Nova peça gerada e adicionada ao final da fila.\n");
                        }
                    }
                }
                break;
                
            case 2: // Inserir nova peça
                if (!filaCheia(&filaPecas)) {
                    Peca novaPeca = gerarPeca(ProximoId++);
                    inserir(&filaPecas, novaPeca);
                    printf("Nova peça [%c %d] inserida no final da fila.\n", novaPeca.Nome, novaPeca.Id);
                } else {
                    printf("Não é possível inserir: fila cheia!\n");
                }
                break;
                
            case 0: // Sair
                printf("Encerrando o programa...\n");
                break;
                
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
        
    } while (Opcao != 0);
    

    return 0;
}

