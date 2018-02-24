#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

#define LIMPAR system("cls");

char *elements[100];
char **matriz = elements;

void gotoxy(int x, int y){
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = {x,y};
	
	SetConsoleCursorPosition(hStdout, position);
}

void exibe(int x, int y, const char *text){
	gotoxy(x, y);
	printf("%s", text);
}

void erro(const char *msg){
	gotoxy(25, 20);
	printf("** Erro! %s **", msg);
}

// gambiarra para apagar apenas alguns textos da telas
// OBS: n�o funciona
//void limpa(){
//	gotoxy(0, 9);
//	printf("Agora vamos limpar o que deve ser limpo");
//	clreol();
//	
//	for (int i = 8; i< 15; i++){
//		gotoxy(0,0);
//		clreol();
//	}
//}

void lerNumeros(){
	FILE *arq;
	char *result;
	char Linha[100];
	int i = 0;
	
	// abertura do arquivo apenas para leitura
	arq = fopen("numbers.txt", "rt");
	
	if(arq == NULL){
		erro("Erro na leitura do arquivo");
		return;
	}
	
	while (!feof(arq)){
	  	// L� uma linha (inclusive com o '\n')
	  	result = fgets(Linha, 100, arq);  // o 'fgets' l� at� 99 caracteres ou at� o '\n'
	  	
	  	// Se foi poss�vel ler, adiciona na matriz
		if (result)		
			matriz[i] = strdup(Linha);
		
		i++;
	}
	
	fclose(arq);
}

int mostra(char elementos[], int elevado){
	char teste;
	
	LIMPAR;
	// A fun��o mostra ir� receber uma lista com os elementos
	// que ser�o exibidos na tela, e a casa decimal na qual o
	// n�mero 2 estar� elevado.
	// *** Funcionamento da fun��o ***
	// A fun��o buscar� os espa�os em brancos entre os elementos
	// e a cada n espa�os haver� a substitui��o deste �ltimo por 
	// um caracter de quebra de linha (\n)
	
	for(int i = 0; i < strlen(elementos); i++){
		if(elementos[i] == '*')
			elementos[i] = '\n';
	}
		
		
	printf("%s", elementos);
		
	teste = getch();
		
	return (teste == 's') ? 2^elevado : 0;
}

void calcular(){
	int calculo = 0;
	
	LIMPAR;
	lerNumeros();
	
	for(int i = 0; i < 6; i++){
		calculo += mostra(matriz[i], i);
	}
	
	printf("voc� pensou no n�mero %d", calculo);
	getch();
}

void iniciar(){
	// Tela Aten��o
	LIMPAR;
	
	exibe(40, 12, "** ATEN��O **");
	exibe(20, 14, "Para que o resultado seja exato voc� n�o deve mentir!");
	
	getch();
	calcular();
}

int direciona(int option){
	switch(option){
		// Play
		case 1:
			iniciar();
			return 1;
		// Sobre
		case 2:
			return 2;
		// Ajuda
		case 3:
			return 3;
		// Sair
		case 4:
			return 0;
		default:
			break;
	}
}

int leituraMenu(){
	int option = 0;
	
	exibe(35,16, "Op��o:  ");
	scanf("%d", &option);
	
	if(option > 5 || option <= 0){
		erro("A op��o selecionada n�o � v�lida!");
	}
	
	return direciona(option);
}

void menu(){	
	exibe(40, 4, "Numero M�gico");
	exibe(25, 6, "Pense em um n�mero entre 1 e 63 e n�s acertamos");
	exibe(35, 8, " ______________________ ");
	exibe(35, 9, "|      1. Iniciar      |");
	exibe(35,10, "|      2. Sobre        |");
	exibe(35,11, "|      3. Ajuda        |");
	exibe(35,12, "|                      |");
	exibe(35,13, "|      4. Sair         |");
	exibe(35,14, "|______________________|");
	exibe(30,25, "Desenvolvido Por: Christian Murata");
	
	while(leituraMenu() != 0){
		menu();
	}
}

void incializa(){
	int system(const char *command);
	// Definindo a linguagem
	setlocale(LC_ALL, "portuguese");
	// Definindo as informa��es da janela
	system("mode con:cols=90 lines=30");
	system("color 70");	
	system("title Numero M�gico");
}

main(){
	incializa();
	menu();
}
