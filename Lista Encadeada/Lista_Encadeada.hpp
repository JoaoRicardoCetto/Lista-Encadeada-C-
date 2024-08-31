#ifndef LISTA_ENCADEADA_HPP
#define LISTA_ENCADEADA_HPP

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct tipoElemento{
    int valor;
    struct tipoElemento *prox;

}; typedef struct tipoElemento TElemento;


struct tipoLista{
    tipoElemento *inicio;
    tipoElemento *fim;
    int totalElementos;

}; typedef struct tipoLista TLista; 

void inicializaLista(TLista *L);

int pesquisarMatricula(TLista *L, int pesquisa);

void insereElemento(TLista *L, int valor);

void lerArquivo(TLista *L, string nomeArquivo);

void gravarNoArquivo(TLista *L, string nomeArquivo);

void excluirMatricula(TLista *L);

void menuOpcoes(int *op);

void menu(TLista *L, string nomeArquivo);

#endif