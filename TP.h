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
//Vitor
TamanhoTela detectarTamanhoTela();

//Move o cursor da tela para a posicao especificada
//Vitor
void moverCursorTela(Coordenada coordenada);

//Limpa a tela
//Gabriel
void limparTela();

//Detecta uma tecla pressionada no teclado
//Vitor
char detectarTeclado();

//Verifica a morte da cobra
//Gabriel
int verificarMorte(Coordenada[] cobra, TamanhoTela tamanhoTela);

//Verifica se a comida foi comida
//Vitor
int verificarComida(Coordenada[] cobra, Coordenada comida);

//Verifica se o movimento pressionado é valido
//Vitor
int verificarMovimento(Direcao direcaoAtual, Direcao novaDirecao);

//Gera uma nova comida
//Gabriel
Coordenada gerarNovaComida(TamanhoTela tamanhoTela, Coordenada[] cobra);

//Movimenta a cobra na direcao determinada
//Gabriel
void movimentarCobra(Coordenada[] cobra, Direcao direcao);

//Apaga a cobra antiga
//Vitor
void apagarCobraAntiga(Coordenada[] cobraAntiga);

//Imprime a cobra nova
//Vitor
void imprimirCobraNova(Coordenada[] cobraNova);

//Imprime a comida
//Gabriel
void imprimirComida(Coordenada comida);

//Imprime o menu com a seta na posicao posSeta
//Vitor
void imprimirMenu(int posSeta);

//Imprime a borda na tela
//Vitor
void imprimirBorda(TamanhoTela tamanhoTela);

//Mostra o menu e retorna a dificuldade (1, 2 ou 3) ou se vai sair (0)
//Vitor
int mostrarMenu();





