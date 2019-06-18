#ifndef TP_H
#define TP_H

#include <stdio.h>
#include <stdlib.h>

struct TamanhoTela {
    int x;
    int y;
};

typedef struct TamanhoTela TamanhoTela;

struct Coordenada {
    int x;
    int y;
};

typedef struct Coordenada Coordenada;

enum Direcao {
    CIMA = 0,
    BAIXO = 1,
    ESQUERDA = 2,
    DIREITA = 3
};

typedef enum Direcao Direcao;

enum Teclas {
    TECLA_CIMA = 0,
    TECLA_BAIXO = 1,
    TECLA_ESQUERDA = 2,
    TECLA_DIREITA = 3,
    TECLA_ENTER = 4,
    NENHUMA_TECLA = 5
};

typedef enum Teclas Teclas;

enum OpcaoMenu {
    SAIR = 0,
    FACIL = 1,
    MEDIO = 2,
    DIFICIL = 3,
    HIGHSCORE = 4
};

typedef enum OpcaoMenu OpcaoMenu;

//Detecta o tamanho do terminal
//Vitor
TamanhoTela detectarTamanhoTela();

//Move o cursor da tela para a posicao especificada
//Vitor
void moverCursorTela(Coordenada coordenada);

//Limpa a tela
//Gabriel
void limparTela();

//Detecta uma tecla pressionada no teclado, retorna a tecla caso positivo, caso contrario retorna '\0'
//Vitor
Teclas detectarTeclado();

//Verifica a morte da cobra
//Gabriel
int verificarMorte(Coordenada cobra[], TamanhoTela tamanhoTela, int tamanhoCobra);

//Verifica se a comida foi comida
//Vitor
int verificarComida(Coordenada cobra[], Coordenada comida, int tamanhoCobra);

 //Verifica se o movimento pressionado é valido
//Vitor
int verificarMovimento(Direcao direcaoAtual, Direcao novaDirecao);

//Movimenta a cobra na direcao determinada e cresce uma posição caso seja necessário
//Gabriel
void movimentarCobra(Coordenada cobra[], Direcao direcao, int tamanhoCobra);

//Apaga a cobra antiga
//Vitor
void apagarCobraAntiga(Coordenada cobraAntiga[], int tamanhoCobraAntiga);

//Imprime a cobra nova
//Vitor
void imprimirCobraNova(Coordenada cobraNova[], int tamanhoCobraNova);

//Gera Nova Comida
//Gabriel
Coordenada gerarNovaComida(TamanhoTela tamanhoTela, Coordenada cobra[], int tamanhoCobra);

//Imprime a comida
//Gabriel
void imprimirComida(Coordenada comida);

//Imprime a borda na tela
//Vitor
void imprimirBorda(TamanhoTela tamanhoTela);

//Mostra o menu e retorna a dificuldade, se vai exeibir os highscores, ou se vai sair
//Vitor
OpcaoMenu mostrarMenu(TamanhoTela tamanhoTela);

//Mostra o highscore na tela (deve ler de arquivo)
//Gabriel
void exibirHighscore(TamanhoTela tamanhoTela);

//Salva o highscore (deve escrever no arquivo)
//Vitor
void salvarHighscore(int pontuacao, char* nomeUsuario);

//Pede o usuário para digitar o nome
//Gabriel
char* obterNomeUsuario(TamanhoTela tamanhoTela);

#endif TP_H
