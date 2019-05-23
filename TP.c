#include <windows.h>
#include <stdio.h>
#include <wincon.h>
#include <conio.h>
#include "TP.h"

TamanhoTela detectarTamanhoTela() {
    HANDLE console;
	CONSOLE_SCREEN_BUFFER_INFO info;
	short rows;
	short columns;
    TamanhoTela tamanho;
	console = CreateFileW(L"CONOUT$", GENERIC_READ | GENERIC_WRITE,
	    FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
	    0, NULL);
	if (console == INVALID_HANDLE_VALUE)
		return tamanho;

	/* Calculate the size of the console window. */
	if (GetConsoleScreenBufferInfo(console, &info) == 0)
		return tamanho;
	CloseHandle(console);
	columns = info.srWindow.Right - info.srWindow.Left;
	rows = info.srWindow.Bottom - info.srWindow.Top;
    tamanho.y = rows;
    tamanho.x = columns;
    return tamanho;
}

void moverCursorTela(Coordenada coordenada) {
    HANDLE Screen;
    Screen = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position={coordenada.x, coordenada.y};
    SetConsoleCursorPosition(Screen, Position);
}

void imprimirBorda(TamanhoTela tamanhoTela) {
    Coordenada coordenada;
    coordenada.x = 0;
    coordenada.y = 0;
    moverCursorTela(coordenada);
    printf("%c", 201);
    coordenada.y = tamanhoTela.y;
    moverCursorTela(coordenada);
    printf("%c", 200);
    coordenada.x = tamanhoTela.x;
    coordenada.y = 0;
    moverCursorTela(coordenada);
    printf("%c", 187);
    coordenada.x = tamanhoTela.x;
    coordenada.y = tamanhoTela.y;
    moverCursorTela(coordenada);
    printf("%c", 188);
    int I;
    for(I=1; I<tamanhoTela.x; I++) {
        coordenada.y = 0;
        coordenada.x = I;
        moverCursorTela(coordenada);
        printf("%c", 205);
        coordenada.y = tamanhoTela.y;
        coordenada.x = I;
        moverCursorTela(coordenada);
        printf("%c", 205);
    }

    for(I=1; I<tamanhoTela.y; I++) {
        coordenada.y = I;
        coordenada.x = 0;
        moverCursorTela(coordenada);
        printf("%c", 186);
        coordenada.x = tamanhoTela.x;
        coordenada.y = I;
        moverCursorTela(coordenada);
        printf("%c", 186);
    }
    coordenada.y = 1;
    coordenada.x = 1;
    moverCursorTela(coordenada);
}

Direcao detectarTeclado() {
    unsigned char c = '\0';
    if(kbhit()){
        c=getch();
        if(c == 224) {
            c = getch();
            // ->
            if(c == 77) {
                return DIREITA;
            }
            // <-
            if(c == 75) {
                return ESQUERDA;
            }
            // Seta para cima
            if(c == 72) {
                return CIMA;
            }
            // Seta para baixo
            if(c == 80) {
                return BAIXO;
            }
        }
        //A
        if(c == 97) {
            return ESQUERDA;
        }
        //D
        if(c == 100) {
            return DIREITA;
        }
        //S
        if(c == 115) {
            return BAIXO;
        }
        //W
        if(c == 119) {
            return CIMA;
        }
    }
    return NENHUMA;
}

int verificarComida(Coordenada cobra[], Coordenada comida, int tamanhoCobra) {
    int I;
    //Caso ocorra um bug e a comida apareça dentro da cobra, ela será coletada
    for(I = 0; I < tamanhoCobra; I++) {
        if(cobra[I].x == comida.x && cobra[I].y == comida.y) {
            return 1;
        }
    }
    return 0;
}

void apagarCobraAntiga(Coordenada cobraAntiga[], int tamanhoCobraAntiga) {
    int I;
    for(I = 0; I < tamanhoCobraAntiga; I++) {
        moverCursorTela(cobraAntiga[I]);
        printf(" ");
    }
}

void imprimirCobraNova(Coordenada cobraNova[], int tamanhoCobraNova) {
    int I;
    for(I = 0; I < tamanhoCobraNova; I++) {
        moverCursorTela(cobraNova[I]);
        printf("%c", 254);
    }
}
