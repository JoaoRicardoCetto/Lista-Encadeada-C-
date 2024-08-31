#include "Lista_Encadeada.hpp"

using namespace std;

void inicializaLista(TLista *L) {
    L->inicio = NULL;
    L->fim = NULL;
    L->totalElementos = 0;
}

void gravarNoArquivo(TLista *L, string nomeArquivo) {
    TElemento *atual = L->inicio;
    
    ofstream arquivo(nomeArquivo);  // Abre o arquivo para sobrescrever

    if (arquivo.is_open()) {
        while (atual != NULL) {
            arquivo << atual->valor << "\n";
            atual = atual->prox;
        }
        arquivo.close();
    } else {
        cout << "\nERRO ao abrir o arquivo: " << nomeArquivo << endl;
    }
}

int pesquisarMatricula(TLista *L, int pesquisa) {
    TElemento *atual = L->inicio;
    while (atual != NULL) {
        if (atual->valor == pesquisa) {
            cout << "\nA matricula " << pesquisa << " foi encontrada!";
            return 1;
        }
        atual = atual->prox;
    }
    cout << "\nA matricula " << pesquisa << " nao foi encontrada no sistema!";
    return 0;
}

void insereElemento(TLista *L, int valor) {
    TElemento *novo = (TElemento*)malloc(sizeof(TElemento));
    TElemento *atual = L->inicio;
    TElemento *anterior = NULL;

    novo->valor = valor;
    novo->prox = NULL;

    if (L->inicio == NULL) {
        L->inicio = novo;
        L->fim = novo;
    } 
    else if (pesquisarMatricula(L, valor) == 0) {  // Se a matrícula não existir, ela é cadastrada
        while (atual != NULL) {
            if (atual->valor >= novo->valor) {
                novo->prox = atual;

                if (anterior == NULL) {
                    L->inicio = novo;
                } else {
                    anterior->prox = novo;
                }
                break;
            }
            anterior = atual;
            atual = atual->prox;
        }

        if (atual == NULL) {  // Se inseriu no final
            anterior->prox = novo;
            L->fim = novo;
        }
    }
    L->totalElementos++;
    cout << "\n\nMatricula inserida no sistema com sucesso!\n";
}

void lerArquivo(TLista *lista, string nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    int matricula;

    if (arquivo.is_open()) {
        while (arquivo >> matricula) {
            insereElemento(lista, matricula);
        }
        arquivo.close();
    } else {
        cout << "\nNão foi possível abrir o arquivo: " << nomeArquivo << endl;
    }
}

void excluirMatricula(TLista *L, int valor) {
    TElemento *atual = L->inicio;
    TElemento *anterior = NULL;

    if (pesquisarMatricula(L, valor) == 1) { //Se a matricula existe, exclui
        while (atual != NULL) {
            if (atual->valor == valor) {
                if (anterior == NULL) {  // Está no início
                    L->inicio = atual->prox;
                } else {  // Está no meio ou no fim
                    anterior->prox = atual->prox;
                }

                if (atual == L->fim) {  // Está no fim
                    L->fim = anterior;
                }

                free(atual);
                L->totalElementos--;
                cout << "\nMatricula " << valor << " removida com sucesso!\n";
                return;
            }
            anterior = atual;
            atual = atual->prox;
        }
    }
}

void exibirQuantidadeMatriculas(TLista *L) {
    cout << "\nExistem " << L->totalElementos << " matriculas cadastradas no sistema";
}

void imprimirMatriculas(TLista *L) {
    TElemento *atual = L->inicio;
    while (atual != NULL) {
        cout << "\nMatricula: " << atual->valor;
        atual = atual->prox;
    }
}

void menuOpcoes(int *op) {
    cout << "\n============================== MENU ============================== \n";
    cout << "\n1) Ler matriculas gravadas no arquivo";
    cout << "\n2) Inserir uma nova matricula";
    cout << "\n3) Cancelar/Remover matricula";
    cout << "\n4) Pesquisar matricula";
    cout << "\n5) Exibir quantidade total de matriculas";
    cout << "\n6) Imprimir matriculas";
    cout << "\n================================================================== \n";
    cin >> *op;
}

void menu(TLista *lista, string nomeArquivo) {
    int opcao;
    int continuar = 1;
    
    while (continuar == 1) {
        menuOpcoes(&opcao);
        switch (opcao) {
            case 1: {
                lerArquivo(lista, nomeArquivo);
                break;
            }
            case 2: {
                int matricula;
                cout << "\nDigite o numero de matricula: ";
                cin >> matricula;
                insereElemento(lista, matricula);
                break;
            }
            case 3: {
                int matricula;
                cout << "\nDigite o numero da matricula a ser removida: ";
                cin >> matricula;
                excluirMatricula(lista, matricula);
                break;
            }
            case 4: {
                int pesquisa;
                cout << "\nDigite o numero da matricula que deseja pesquisar: ";
                cin >> pesquisa;
                pesquisarMatricula(lista, pesquisa);
                break;
            }
            case 5:
                exibirQuantidadeMatriculas(lista);
                break;
            case 6:
                imprimirMatriculas(lista);
                break;
            default:
                cout << "\nOpcao Invalida!" << endl;
                break;
        }

        cout << "\nPara continuar com outras operacoes, digite 1. Para sair, digite 0: ";
        cin >> continuar;
    }
}

int main() {
    TLista lista;
    string nomeArquivo = "Matriculas.txt";
    inicializaLista(&lista);

    menu(&lista, nomeArquivo);

    lerArquivo(&lista, nomeArquivo);
    gravarNoArquivo(&lista, nomeArquivo);
    return 0;
}
