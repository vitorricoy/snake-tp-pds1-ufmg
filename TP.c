#include <windows.h>
#include <stdio.h>
#include <wincon.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
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

Teclas detectarTeclado() {
    unsigned char c = '\0';
    if(kbhit()){
        c=getch();
        if(c == 224) {
            c = getch();
            // ->
            if(c == 77) {
                return TECLA_DIREITA;
            }
            // <-
            if(c == 75) {
                return TECLA_ESQUERDA;
            }
            // Seta para cima
            if(c == 72) {
                return TECLA_CIMA;
            }
            // Seta para baixo
            if(c == 80) {
                return TECLA_BAIXO;
            }
        }
        //A
        if(c == 97) {
            return TECLA_ESQUERDA;
        }
        //D
        if(c == 100) {
            return TECLA_DIREITA;
        }
        //S
        if(c == 115) {
            return TECLA_BAIXO;
        }
        //W
        if(c == 119) {
            return TECLA_CIMA;
        }
        if(c == 13) {
            return TECLA_ENTER;
        }
    }
    return NENHUMA_TECLA;
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
    moverCursorTela(cobraAntiga[tamanhoCobraAntiga-1]);
    printf(" ");
}

void imprimirCobraNova(Coordenada cobraNova[], int tamanhoCobraNova) {
    int I;
    for(I = 0; I < tamanhoCobraNova; I++) {
        moverCursorTela(cobraNova[I]);
        printf("%c", '*');
    }
}

void salvarHighscore(int pontuacoes[], char nomeUsuario[][20], int quantidadePontuacoes) {
    FILE *arquivo;
    arquivo = fopen("data.bin", "wb");
    fprintf(arquivo, "%d ", quantidadePontuacoes);
    int I;
    for(I = 0; I < quantidadePontuacoes; I++) {
        fprintf(arquivo, "%d %s ", pontuacoes[I], nomeUsuario[I]);
    }
    fclose(arquivo);
}

OpcaoMenu mostrarMenu(TamanhoTela tamanhoTela) {
    imprimirBorda(tamanhoTela);
    Coordenada coord;
    //Jogar - Facil
    coord.x = tamanhoTela.x/2 - 6;
    coord.y = tamanhoTela.y/2 - 2;
    moverCursorTela(coord);
    printf("Jogar - Facil");
    //Jogar - Medio
    coord.x = tamanhoTela.x/2 - 6;
    coord.y = tamanhoTela.y/2 - 1;
    moverCursorTela(coord);
    printf("Jogar - Media");
    //Jogar - Dificil
    coord.x = tamanhoTela.x/2 - 7;
    coord.y = tamanhoTela.y/2;
    moverCursorTela(coord);
    printf("Jogar - Dificil");
    //Highscore
    coord.x = tamanhoTela.x/2 - 4;
    coord.y = tamanhoTela.y/2 + 1;
    moverCursorTela(coord);
    printf("Highscore");
    //Sair
    coord.x = tamanhoTela.x/2 - 2;
    coord.y = tamanhoTela.y/2 + 2;
    moverCursorTela(coord);
    printf("Sair");
    Teclas tecla = detectarTeclado();
    int indexSeta = 0, indexAnterior = -1;
    while(tecla != TECLA_ENTER) {
        if(tecla == TECLA_CIMA) {
            indexSeta = indexSeta > 0 ? indexSeta - 1 : indexSeta;
        }
        if(tecla == TECLA_BAIXO) {
            indexSeta = indexSeta < 4 ? indexSeta + 1 : indexSeta;
        }
        if(indexSeta != indexAnterior) {
            coord.x = tamanhoTela.x/2 - 10;
            coord.y = tamanhoTela.y/2 - 2 + indexAnterior;
            moverCursorTela(coord);
            indexAnterior = indexSeta;
            printf("  ");
            coord.x = tamanhoTela.x/2 - 10;
            coord.y = tamanhoTela.y/2 - 2 + indexSeta;
            moverCursorTela(coord);
            printf("->");
        }
        tecla = detectarTeclado();
    }
    switch(indexSeta) {
        case 0: return FACIL;
        case 1: return MEDIO;
        case 2: return DIFICIL;
        case 3: return HIGHSCORE;
        case 4: return SAIR;
    }
}

int verificarMovimento(Direcao direcaoAtual, Direcao novaDirecao) {
    switch(direcaoAtual) {
        case BAIXO:
            if(novaDirecao == ESQUERDA || novaDirecao == DIREITA) {
                return 1;
            }
            return 0;
        case CIMA:
            if(novaDirecao == ESQUERDA || novaDirecao == DIREITA) {
                return 1;
            }
            return 0;
        case DIREITA:
            if(novaDirecao == CIMA || novaDirecao == BAIXO) {
                return 1;
            }
            return 0;
        case ESQUERDA:
            if(novaDirecao == CIMA || novaDirecao == BAIXO) {
                return 1;
            }
            return 0;
    }
}

void limparTela()
{
    system("cls");
}
int verificarMorte(Coordenada cobra[], TamanhoTela tamanhoTela, int tamanhoCobra)
{
    int i;//Contador
    for(i=0;i<tamanhoCobra;i++)//Detectar se alguma parte da cobra encostou na borda da tela.    {
        if((cobra[i].x==tamanhoTela.x)||(cobra[i].y==tamanhoTela.y))
        {
            return 1;
        }

    return 0;
}
Coordenada gerarNovaComida(TamanhoTela tamanhoTela, Coordenada cobra[], int tamanhoCobra)
{

    Coordenada comida;
    NovaComida.x=rand()%(tamanhotela.x-1);
    NovaComida.y=rand()%(tamanhoTela.y-1);
    return comida;
}
void movimentarCobra(Coordenada cobra[], Direcao direcao, int tamanhoCobra, int deveCrescer)
{
   if(deveCrescer==1)
   {
       tamanhoCobra=tamanhoCobra + 1;
   }
   if(direcao==0)//Movimentar cobra para cima.
   {
       cobra[0].y = cobra[0].y + 1;
   }
   else if(direcao==1)
   {
       cobra[0].y = cobra[0].y - 1;
   }
   else if(direcao==2)
   {
       cobra[0].x = cobra[0].x - 1;
   }
   else
   {
       cobra[0].x=cobra[0].x + 1;
   }
   int i;//Contador
   for(i=tamanhoCobra;i>0;i--)
       {
           cobra[i].x = cobra[i-1].x;
           cobra[i].y = cobra[i-1].y;
       }
}
void imprimirComida(Coordenada comida)
{
    moverCursorTela(comida);
    printf("%c",'*');
}
void exibirHighscore(TamanhoTela tamanhoTela)
{
   FILE *arq;
   int highscore,aux,aux2;
   hishscore=0;
   arq=fopen("data.txt","r")
   Coordenada nachouarq;//Coordenada para printar que não foi possível encontrar o arquivo do highscore.
   nachouarq.x=tamanhoTela.x/2 - 18;
   nachouarq.y=tamanhoTela.y/2;
   Coordenada printarhighscore;//Coordenada para inciar o print do highscore.
   int numcaracter;//Número de caracteres do highscore.
   if(arq==NULL)
   {
     moverCursorTela(nachouarq);
     printf("Nao foi possivel encontrar o arquivo.");
   }
   else
   {
     while(!f(eof))
     {
         fscanf(arq,"%d",&aux);
         if(aux>highscore)
         {
             highscore=aux;
         }
     }
     numcaracter=0;
     aux2=highscore;
     while(aux2>=1)
     {
         aux2=aux/10;
         numcaracter=numcaracter+1;
     }
     printarhighscore.x=tamanhoTela.x/2 - numcaracter/2 - 6;
     printarhighscore.y=tamanhoTela.y/2;
     moverCursorTela(printarhighscore);
     printf("Highscore: %i", highscore);
   }
}
char* obterNomeUsuario(TamanhoTela tamanhoTela)
{
    Coordenada printfinstrucoes;
    char *nomeUsuário;
    printfinstrucoes.y==tamanhoTela.y/2;
    printfinstrucoes.x=tamanhoTela.y/2 -9;
    moverCursorTela(printfinstrucoes);
    printf("Nome do usuario : ");
    fflush(stdin);
    gets(nomeUsuário);
    return nomeUsuário;
}
//TESTE
int main() {
    TamanhoTela tamanhoTela = detectarTamanhoTela();
    imprimirBorda(tamanhoTela);
    Coordenada cobra[200];
    srand(time(NULL));
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
        Coordenada coord;
        coord.x=0;coord.y=0;
        moverCursorTela(coord);
        int I;

        movimentarCobra(cobra, direcaoCobra, tamanhoCobra, comeu);
        imprimirCobraNova(cobra, tamanhoCobra);
        Coordenada zero;
        zero.x = 0;
        zero.y = 0;
        moverCursorTela(zero);
        Sleep(10);
    }
}
