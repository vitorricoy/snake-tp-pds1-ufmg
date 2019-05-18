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
    tamanho.lin = rows;
    tamanho.col = columns;
    return tamanho;
}

void moverCursorTela(Coordenada coordenada) {
    HANDLE Screen;
    Screen = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position={coordenada.y, coordenada.x};
    SetConsoleCursorPosition(Screen, Position);
}

void imprimirBorda(TamanhoTela tamanhoTela) {
    SetPosition(0, 0);
    printf("%c", 201);
    SetPosition(tamanhoTela.y, 0);
    printf("%c", 200);
    SetPosition(0, tamanhoTela.x);
    printf("%c", 187);
    SetPosition(tamanhoTela.y, tamanhoTela.x);
    printf("%c", 188);
    int I;
    for(I=1; I<tamanhoTela.x; I++) {
        SetPosition(0, I);
        printf("%c", 205);
        SetPosition(tamanhoTela.y, I);
        printf("%c", 205);
    }

    for(I=1; I<tamanhoTela.y; I++) {
        SetPosition(I, 0);
        printf("%c", 186);
        SetPosition(I, tamanhoTela.x);
        printf("%c", 186);
    }
    SetPosition(1, 1);
}
