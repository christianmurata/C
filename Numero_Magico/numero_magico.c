#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <math.h>

#define LIMPAR system("cls");
#define AGUARDA_TECLA getch();
#define TECLA getche();

char *elements[100];
char **matriz = elements;

void gotoxy(int x, int y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = {x,y};
	
	SetConsoleCursorPosition(hStdout, position);
}

void exibe(int x, int y, const char *text)
{
	gotoxy(x, y);
	printf("%s", text);
}

void erro(const char *msg)
{
	gotoxy(25, 20);
	printf("** Erro! %s **", msg);
}

void lerNumeros()
{
	FILE *arq;
	char *result;
	char Linha[100];
	int i = 0;
	
	// abertura do arquivo apenas para leitura
	arq = fopen("numbers.txt", "rt");
	
	if(arq == NULL)
	{
		erro("Erro na leitura do arquivo");
		return;
	}
	
	while (!feof(arq))
	{
	  	// Lê uma linha (inclusive com o '\n')
	  	// o 'fgets' lê até 99 caracteres ou até o '\n'
	  	result = fgets(Linha, 100, arq);
	  	
	  	// Se foi possível ler, adiciona na matriz
		if (result)		
			matriz[i] = strdup(Linha);
		
		i++;
	}
	
	fclose(arq);
}

char caracter()
{
	char letra;
	letra = TECLA;
	
	return toupper(letra);
}

int mostra(char elementos[], int elevado)
{
	int value = 0;
	char tecla;
	
	LIMPAR;
	
	for(int i = 0; i < strlen(elementos); i++){
		if(elementos[i] == '*')
			elementos[i] = '\n';
	}
	
	exibe(30, 6, "O número que você pensou aparece aqui?");
	exibe(35, 8, elementos);
	exibe(35,15, "Digite S/N para continuar: ");
	
	while (tecla != 'S' && tecla != 'N')
	{
		tecla = caracter();
	}
	// se a tecla digitada for um S (sim)...
	if(tecla == 'S')
	{
		if(elevado == 0)
			value = 1;
		else
			value = pow(2, elevado);
	}
			
	return value;
}

void calcular()
{
	int calculo = 0;
	
	LIMPAR;
	lerNumeros();
	
	for(int i = 0; i < 6; i++)
	{
		calculo += mostra(matriz[i], i);
		fflush(stdin);
		
		AGUARDA_TECLA;
	}
	
	// se o usuario tiver apertado pelo menos uma vez a tecla S...
	if(calculo > 0 && calculo <= 63)
		printf("você pensou no número: %d", calculo);
		
	AGUARDA_TECLA;
}

void iniciar()
{
	LIMPAR;
	exibe(40, 12, "** ATENÇÃO **");
	exibe(20, 14, "Para que o resultado seja exato você não deve mentir!");
	
	AGUARDA_TECLA;
	
	calcular();
}

void construcao()
{
	LIMPAR;
	exibe(35, 12, "** EM CONSTRUÇÃO **");
	exibe(30, 14, "Digite qualque tecla para voltar");
	
	AGUARDA_TECLA;
}

int direciona(int option)
{
	switch(option)
	{
		// Play
		case 1:
			iniciar();
			return 1;
		// Sobre
		case 2:
			construcao();
			return 2;
		// Ajuda
		case 3:
			construcao();
			return 3;
		// Sair
		case 4:
			return 0;
		default:
			break;
	}
}

int leituraMenu()
{
	int option = 0;
	
	exibe(35,16, "Opção:  ");
	scanf("%d", &option);
	fflush(stdin);
	
	if(option > 5 || option <= 0)
		erro("A opção selecionada não é válida!");
	
	return direciona(option);
}

void menu()
{
	LIMPAR;
	exibe(40, 4, "Numero Mágico");
	exibe(25, 6, "Pense em um número entre 1 e 63 e nós acertamos");
	exibe(35, 8, " ______________________ ");
	exibe(35, 9, "|      1. Iniciar      |");
	exibe(35,10, "|      2. Sobre        |");
	exibe(35,11, "|      3. Ajuda        |");
	exibe(35,12, "|                      |");
	exibe(35,13, "|      4. Sair         |");
	exibe(35,14, "|______________________|");
	exibe(30,25, "Desenvolvido Por: Christian Murata");
	
	while(leituraMenu() > 0)
	{
		menu();
	}
}

void incializa()
{
	int system(const char *command);
	// Definindo a linguagem
	setlocale(LC_ALL, "portuguese");
	// Definindo as informações da janela
	system("mode con:cols=90 lines=30");
	system("color 70");	
	system("title Numero Mágico");
}

int main()
{
	incializa();
	menu();
	
	return 0;
}
