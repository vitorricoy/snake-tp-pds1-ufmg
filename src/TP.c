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
    //Caso ocorra um bug e a comida apare�a dentro da cobra, ela ser� coletada
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

void salvarHighscore(int pontuacao, char* nomeUsuario) {
    FILE *arquivo;
    arquivo = fopen("data.txt", "r");
    int numPontuacoes = 0, I, J;
    int pontuacoes[11];
    char* nomes[11];
    for(I=0; I<11; I++) {
        nomes[I] = malloc(sizeof(char)*21);
    }
    if(arquivo != NULL && !feof(arquivo)) {
        fscanf(arquivo, "%d ", &numPontuacoes);
        for(I = 0; I < numPontuacoes; I++) {
            fscanf(arquivo, "%d ", &pontuacoes[I]);
            fgets(nomes[I], 20, arquivo);
        }
        fclose(arquivo);
    }
    pontuacoes[numPontuacoes] = pontuacao;
    nomes[numPontuacoes] = nomeUsuario;
    //Ordena as pontuacoes
    for(I=0; I<numPontuacoes+1; I++) {
        int maior = I;
        int maiorVal = 0;
        for(J=I; J<numPontuacoes+1; J++) {
            if(pontuacoes[J] > maiorVal) {
                maior = J;
                maiorVal = pontuacoes[J];
            }
        }
        int aux = pontuacoes[I];
        char* aux2 = malloc(sizeof(char)*21);
        strcpy(aux2, nomes[I]);
        pontuacoes[I] = maiorVal;
        strcpy(nomes[I], nomes[maior]);
        pontuacoes[maior] = aux;
        strcpy(nomes[maior], aux2);
    }
    if(numPontuacoes < 10) {
        numPontuacoes++;
    }
    arquivo = fopen("data.txt", "w");
    fprintf(arquivo, "%d ", numPontuacoes);
    for(I=0; I<numPontuacoes; I++) {
        fprintf(arquivo, "%d %s ", pontuacoes[I], nomes[I]);
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
    int i, j; //Contador
    //Detectar se alguma parte da cobra encostou na borda da tela.    {
    for(i=0; i<tamanhoCobra; i++) {
        if((cobra[i].x==tamanhoTela.x)||(cobra[i].y==tamanhoTela.y)||(cobra[i].x==0)||(cobra[i].y==0))
        {
            return 1;
        }
        for(j = i+1; j<tamanhoCobra; j++) {
            if(cobra[i].x == cobra[j].x && cobra[i].y == cobra[j].y) {
                return 1;
            }
        }
    }

    return 0;
}

Coordenada gerarNovaComida(TamanhoTela tamanhoTela, Coordenada cobra[], int tamanhoCobra)
{
    Coordenada comida;
    comida.x=rand()%((tamanhoTela.x-2))+1;
    comida.y=rand()%((tamanhoTela.y-2))+1;
    return comida;
}

void movimentarCobra(Coordenada cobra[], Direcao direcao, int tamanhoCobra)
{
   int i;//Contador
   for(i=tamanhoCobra;i>0;i--)
   {
       cobra[i].x = cobra[i-1].x;
       cobra[i].y = cobra[i-1].y;
   }
   if(direcao==1)//Movimentar cobra para cima.
   {
       cobra[0].y = cobra[0].y + 1;
   }
   else if(direcao==0)
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
}

void imprimirComida(Coordenada comida)
{
    moverCursorTela(comida);
    printf("%c",254);
}

void exibirHighscore(TamanhoTela tamanhoTela)
{
   FILE *arq;
   int quantHighscores, I;
   int pontuacoes[10], maxPontuacao = 0;
   char nomeUsuario[10][21];
   arq=fopen("data.txt","r");
   Coordenada nachouarq;//Coordenada para printar que n�o foi poss�vel encontrar o arquivo do highscore.
   nachouarq.x=tamanhoTela.x/2 - 17;
   nachouarq.y=tamanhoTela.y/2;
   Coordenada printarhighscore;//Coordenada para inciar o print do highscore.
   int numcaracter;//Numero de caracteres do highscore.
   if(arq==NULL)
   {
     moverCursorTela(nachouarq);
     printf("Voce ainda nao possui um highscore.");
     fflush(stdin);
     getch();
   }
   else
   {
     if(!feof(arq))
     {
         fscanf(arq,"%d ",&quantHighscores);
         for(I=0; I<quantHighscores; I++) {
            fscanf(arq, "%d ", &pontuacoes[I]);
            if(pontuacoes[I] > maxPontuacao) {
                maxPontuacao = pontuacoes[I];
            }
            fgets(nomeUsuario[I], 20, arq);
            nomeUsuario[I][strlen(nomeUsuario[I])-1] = '\0';
         }
     } else {
        Coordenada semHighscore;
        semHighscore.y = tamanhoTela.y/2;
        semHighscore.x = tamanhoTela.x/2 - 17;
        printf("Voce ainda nao possui um highscore.");
        fflush(stdin);
        getch();
        return;
     }
     fclose(arq);
     numcaracter=0;
     int aux=maxPontuacao;
     while(aux>=1)
     {
         aux/=10;
         numcaracter=numcaracter+1;
     }
     printarhighscore.x=tamanhoTela.x/2 - 14;
     printarhighscore.y=tamanhoTela.y/2 - (quantHighscores/2) - 1;
     moverCursorTela(printarhighscore);
     printf("Nome                Pontuacao");
     int J;
     for(I=0; I<quantHighscores; I++) {
         int tamanhoNome = strlen(nomeUsuario[I]);
         printarhighscore.x = tamanhoTela.x/2 - 15 - (I > 10 ? 4 : 3);
         printarhighscore.y = tamanhoTela.y/2 + (I - quantHighscores/2);
         moverCursorTela(printarhighscore);
         if(I < 9) {
            printf("0%d. %s", I+1, nomeUsuario[I]);
         } else {
            printf("%d. %s", I+1, nomeUsuario[I]);
         }
         for(J=0; J<20 - tamanhoNome; J++) {
            printf(" ");
         }
         printf("%d", pontuacoes[I]);
     }
     fflush(stdin);
     getch();
   }
}
char* obterNomeUsuario(TamanhoTela tamanhoTela)
{
    Coordenada printfinstrucoes;
    char *nomeUsuario = malloc(sizeof(char) * 20);
    printfinstrucoes.y=tamanhoTela.y/2;
    printfinstrucoes.x=tamanhoTela.x/2 -9;
    moverCursorTela(printfinstrucoes);
    printf("Nome do usuario : ");
    fflush(stdin);
    fgets(nomeUsuario, 20, stdin);
    return nomeUsuario;
}

