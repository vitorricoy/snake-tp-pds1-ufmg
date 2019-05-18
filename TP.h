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

//Detecta o tamanho do terminal
TamanhoTela detectarTamanhoTela();

//Move o cursor da tela para a posicao especificada
void moverCursorTela(Coordenada coordenada);

//Limpa a tela
void limparTela();

//Detecta uma tecla pressionada no teclado
char detectarTeclado();

//Verifica a morte da cobra
int verificarMorte(Coordenada[] cobra, TamanhoTela tamanhoTela);

//Verifica se a comida foi comida
int verificarComida(Coordenada[] cobra, Coordenada comida);

//Verifica se o movimento pressionado é valido
int verificarMovimento(Direcao direcaoAtual, Direcao novaDirecao);

//Gera uma nova comida
Coordenada gerarNovaComida(TamanhoTela tamanhoTela, Coordenada[] cobra);

//Movimenta a cobra na direcao determinada
void movimentarCobra(Coordenada[] cobra, Direcao direcao);

//Apaga a cobra antiga
void apagarCobraAntiga(Coordenada[] cobraAntiga);

//Imprime a cobra nova
void imprimirCobraNova(Coordenada[] cobraNova);

//Imprime a comida
void imprimirComida(Coordenada comida);

//Imprime o menu com a seta na posicao posSeta
void imprimirMenu(int posSeta);

//Imprime a borda na tela
void imprimirBorda(TamanhoTela tamanhoTela);

//Mostra o menu e retorna a dificuldade (1, 2 ou 3) ou se vai sair (0)
int mostrarMenu();





