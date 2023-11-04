#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// lista
struct Contato {
    char nome[50];
    char fone[20];
    struct Contato* prox;
    struct Contato* ant;
};

// Estrutura para representar a agenda de contatos
struct ListaContatos {
    struct Contato* head;
    struct Contato* tail;
};

// Função para criar um novo nó de contato
struct Contato* criarContato(const char* nome, const char* fone) {
    struct Contato* novoContato = (struct Contato*)malloc(sizeof(struct Contato));
    //criamos uma variavel ponteiro para uma estruturado tipo contato.
    // a função malloc aloca memoria dinamicamente, usando a estrutura contato como
    // parametro para a quantidade de memoria a ser alocada.
    //malloc retorna um ponteiro generico, apos isso usamos um casting para garantir
    //que o ponteiro seja do tipo certo.
    strncpy(novoContato->nome, nome, sizeof(novoContato->nome));
    strncpy(novoContato->fone, fone, sizeof(novoContato->fone));
    //o comando strncpy é usado para copiar a informação nome e fone respectivamente para os
    //campos compatíveis dentro do novo contato recém criado, alocando dinamicamente essa
    //memoria.
    novoContato->prox = NULL;
    novoContato->ant = NULL;
    //por ser um contato recem criado, não existem nem proximos nem anteriores
    return novoContato;
}

//basicamente novocontato é um dado estruturado contato, que contem as informações que inserimos na função e também possui memoria dinamica alocada para si mesmo.

// Função para inserir um contato na agenda
void inserirContato(struct ListaContatos* lista, const char* nome, const char* fone) {
    struct Contato* novoContato = criarContato(nome, fone);
    //chamamos a função criarContato, que resulta num ponteiro novoContato. 
    // (que aponta para uma instancia de contato)
    if (lista->tail == NULL) {
        lista->head = lista->tail = novoContato;
        //se a lista estiver vazia, o contato recem criado é o primeiro e tambem o ultimo dessa lista.
    } else {
        novoContato->ant = lista->tail;
        //o contato anterior ao que acabou de ser criado passa a ser a tail da lista
        lista->tail->prox = novoContato;
        //o proximo contato em relação ao ultimo elemento da lista (tail)
        // passa a ser o contato que acabou de ser criado
        //as duas linhas basicamente garantem que uma "concorda" com a outra
        lista->tail = novoContato;
        //o contato recem criado passa a ser a tail da lista.
    }
}
// a função inserir só funciona pois utiliza a função criar!

// Função para exibir todos os contatos na agenda
void mostrarContatos(struct ListaContatos* lista) {
    struct Contato* atual = lista->head;
    //acessamos a head da lista (primeiro contato)
    //o ponteiro do tipo contato atual passa a acessar a head da lista
    while (atual != NULL) {
        //enquanto o atual não for nulo...
        printf("Name: %s\nTelefone: %s\n\n", atual->nome, atual->fone);
        atual = atual->prox;
        //nessa linha o atual passa a ser o proximo valor de cada contato,
        //e eventualmente não haverá um contato, ou seja, null, e nesse momento
        //o loop irá parar.
    }
}

// Função para pesquisar um contato na agenda pelo nome
struct Contato* encontrarContato(struct ListaContatos* lista, const char* nome) {
    struct Contato* atual = lista->head;
    //acessamos a head da lista (primeiro contato)
    //o ponteiro do tipo contato atual passa a acessar a head da lista
    while (atual != NULL) {
        //enquanto o atual não for nulo... (mesma coisa da função anterior)
        if (strcmp(atual->nome, nome) == 0) {
            //compara o nome do ponteiro "atual" com o parametro nome da função
            //se retornar 0, significa que os dois são iguais
            return atual;
        }
        atual = atual->prox;
        //nessa linha o atual passa a ser o proximo valor de cada contato,
        //e eventualmente não haverá um contato, ou seja, null, e nesse momento
        //o loop irá parar. (mesma coisa que a função anterior)
    }
    return NULL;
}

// Função para excluir um contato da agenda
void deletarContato(struct ListaContatos* lista, const char* nome) {
    struct Contato* deletar = encontrarContato(lista, nome);
    //ponteiro do tipo contato deletar recebe o endereço da função encontrarContat
    if (deletar != NULL) {
        if (deletar->ant) {
            //verifica a existencia de um contato anterior
            deletar->ant->prox = deletar->prox;
            //o valor a ser deletado passa a ser o proximo contato
        } else {
            //se não tem, a head da lista passa a ser o valor a ser deletado
            lista->head = deletar->prox;
        }
        if (deletar->prox) {
            //verifica a existencia de um proximo contato
            deletar->prox->ant = deletar->ant;
            // o valor a ser deletado passa a ser o contato anterior
        } else {
            lista->tail = deletar->ant;
            //se não tem, a tail da lista passa a ser o valor deletado
        }
        free(deletar);
        //libera a memoria do ponteiro, ou seja, deleta.
    }
}

int main() {
    struct ListaContatos lista_contatos;
    lista_contatos.head = lista_contatos.tail = NULL;

    int opcao;
    char nome[50];
    char fone[20];

    while (1) {
        printf("\nAgenda de Contatos\n");
        printf("1. Inserir Contato\n");
        printf("2. Consultar Contato\n");
        printf("3. Excluir Contato\n");
        printf("4. Lista de Todos os Contatos\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Nome: ");
                scanf(" %[^\n]", nome);
                printf("Telefone: ");
                scanf(" %[^\n]", fone);
                inserirContato(&lista_contatos, nome, fone);
                printf("Contato inserido com sucesso!\n");
                break;
            case 2:
                printf("Nome a ser consultado: ");
                scanf(" %[^\n]", nome);
                struct Contato* encontrado = encontrarContato(&lista_contatos, nome);
                if (encontrado) {
                    printf("Nome: %s\nTelefone: %s\n", encontrado->nome, encontrado->fone);
                } else {
                    printf("Contato não encontrado.\n");
                }
                break;
            case 3:
                printf("Nome a ser excluído: ");
                scanf(" %[^\n]", nome);
                deletarContato(&lista_contatos, nome);
                printf("Contato excluído com sucesso!\n");
                break;
            case 4:
                mostrarContatos(&lista_contatos);
                break;
            case 5:
                exit(0);
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
