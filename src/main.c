#include "TP.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void gameLoop(TamanhoTela tamanhoTela, OpcaoMenu dificuldade) {
    char* nomeUsuario = obterNomeUsuario(tamanhoTela);
    limparTela();
    imprimirBorda(tamanhoTela);
    Coordenada cobra[200];
    cobra[0].x = tamanhoTela.x / 2;
    cobra[0].y = tamanhoTela.y / 2;
    cobra[1].x = tamanhoTela.x / 2 - 1;
    cobra[1].y = tamanhoTela.y / 2;
    cobra[2].x = tamanhoTela.x / 2 - 2;
    cobra[2].y = tamanhoTela.y / 2;
    int tamanhoCobra = 3;
    Coordenada comida = gerarNovaComida(tamanhoTela, cobra, tamanhoCobra);
    imprimirComida(comida);
    Direcao direcaoCobra = DIREITA;
    imprimirCobraNova(cobra, tamanhoCobra);
    while(1) {
        Teclas tecla = detectarTeclado();
        Direcao novaDirecao;
        apagarCobraAntiga(cobra, tamanhoCobra);
        switch(tecla) {
            case TECLA_BAIXO:
                novaDirecao = BAIXO;
                if(verificarMovimento(direcaoCobra, novaDirecao))
                    direcaoCobra = BAIXO;
                break;
            case TECLA_CIMA:
                novaDirecao = CIMA;
                if(verificarMovimento(direcaoCobra, novaDirecao))
                    direcaoCobra = CIMA;
                break;
            case TECLA_DIREITA:
                novaDirecao = DIREITA;
                if(verificarMovimento(direcaoCobra, novaDirecao))
                    direcaoCobra = DIREITA;
                break;
            case TECLA_ESQUERDA:
                novaDirecao = ESQUERDA;
                if(verificarMovimento(direcaoCobra, novaDirecao))
                    direcaoCobra = ESQUERDA;
                break;
        }
        int comeu = verificarComida(cobra, comida, tamanhoCobra);
        if(comeu) {
            comida = gerarNovaComida(tamanhoTela, cobra, tamanhoCobra);
            tamanhoCobra++;
            imprimirComida(comida);
        }
        movimentarCobra(cobra, direcaoCobra, tamanhoCobra);
        imprimirCobraNova(cobra, tamanhoCobra);
        Coordenada zero;
        zero.x = 0;
        zero.y = 0;
        moverCursorTela(zero);
        if(verificarMorte(cobra, tamanhoTela, tamanhoCobra)) {
            salvarHighscore(tamanhoCobra * dificuldade, nomeUsuario);
            return;
        }
        if(dificuldade == DIFICIL) {
            Sleep(10);
        }

        if(dificuldade == MEDIO) {
            Sleep(50);
        }

        if(dificuldade == FACIL) {
            Sleep(80);
        }
    }
}

int main() {
    TamanhoTela tamanhoTela = detectarTamanhoTela();
    srand(time(NULL));
    while(1) {
        limparTela();
        OpcaoMenu opcaoMenu = mostrarMenu(tamanhoTela);
        limparTela();
        switch(opcaoMenu) {
            case SAIR: return 0;
            case HIGHSCORE: exibirHighscore(tamanhoTela); break;
            default: gameLoop(tamanhoTela, opcaoMenu); break;
        }
    }
}
