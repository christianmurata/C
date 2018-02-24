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
// OBS: não funciona
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
	  	// Lê uma linha (inclusive com o '\n')
	  	result = fgets(Linha, 100, arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'
	  	
	  	// Se foi possível ler, adiciona na matriz
		if (result)		
			matriz[i] = strdup(Linha);
		
		i++;
	}
	
	fclose(arq);
}

int mostra(char elementos[], int elevado){
	char teste;
	
	LIMPAR;
	// A função mostra irá receber uma lista com os elementos
	// que serão exibidos na tela, e a casa decimal na qual o
	// número 2 estará elevado.
	// *** Funcionamento da função ***
	// A função buscará os espaços em brancos entre os elementos
	// e a cada n espaços haverá a substituição deste último por 
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
	
	printf("você pensou no número %d", calculo);
	getch();
}

void iniciar(){
	// Tela Atençõo
	LIMPAR;
	
	exibe(40, 12, "** ATENÇÃO **");
	exibe(20, 14, "Para que o resultado seja exato você não deve mentir!");
	
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
	
	exibe(35,16, "Opção:  ");
	scanf("%d", &option);
	
	if(option > 5 || option <= 0){
		erro("A opção selecionada não é válida!");
	}
	
	return direciona(option);
}

void menu(){	
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
	
	while(leituraMenu() != 0){
		menu();
	}
}

void incializa(){
	int system(const char *command);
	// Definindo a linguagem
	setlocale(LC_ALL, "portuguese");
	// Definindo as informações da janela
	system("mode con:cols=90 lines=30");
	system("color 70");	
	system("title Numero Mágico");
}

main(){
	incializa();
	menu();
}
