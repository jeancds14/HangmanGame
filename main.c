#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

char wrongAttempt[30],
	 newWord[],
	 word[];

int error = 0,
	attempts = 0,
	hit = 0,
	finished = 0;
	

int startGame(){
	
	hit = 0;
	finished = 0;
	error = 0;
	attempts = 0;
	
	int option;
	
	printf("<  Seja bem-vindo ao jogo da forca  >\n\n");
	printf("Digitando o número referente a opção abaixo:\n");
	printf("1 - Sortea uma palavra já registrada no sistema.\n");
	printf("2 - Digitar uma palavra.\n");
	printf("3 - Registrar uma nova palavra no sistema.\n");
	printf("4 - Sair do jogo.\n");
	scanf(" %d", &option);
	
	switch(option){
		case 1:
			system("cls");
			chooseWord();
			break;
		case 2:
			system("cls");
			printf("Digite a palavra.\n");
			scanf("%s", &word);
			break;
		case 3:
			system("cls");
			addWord();
			break;
		case 4:
			exit(1);
			break;
		default:
			printf("Opção não encontrada.\n");
			break;
	}
}

int existingLetter(char letter){
	int i;
	
	for(i = 0; i < attempts; i++) {
		if(wrongAttempt[i] == letter) {
			return 1;
		}
	}	
	
	return 0;
}

void hangman() {

	int size = stringSize(word),
		i;
	printf("<  Seja bem-vindo ao jogo da forca  >\n\n");
	printf("  _______       \n");
	printf(" |       |      \n");
	printf(" |      %c%c%c  \n", (error>=1?'(':' '), ' ', (error>=1?')':' '));
	printf(" |      %c%c%c  \n", (error>=3?'/':' '), (error>=2?'|':' '), (error>=3?'\\': ' '));
	printf(" |       %c     \n", (error>=2?'|':' '));
	printf(" |      %c %c   \n", (error>=4?'/':' '), (error>=4?'\\':' '));
	printf(" |              \n");
	printf("_|_    ");

	for(i = 0; i < size; i++)
	{
		if(attempts == 0){
			printf("_ ");
		}else{
			if(existingLetter(word[i]) == 1){
				printf("%c ", word[i]);
			}else{
				printf("_ ");
			}
		}
	}
	
	printf("\n\n");

}

void writerLetter(){
	char letter;
	int i,
		hitLetter = 0,
		size = stringSize(word);

	printf("Digite a letra:\n");
	scanf(" %c", &letter);
	
	for(i = 0; i < size; i++)
	{
		if(word[i] == letter){
			++hitLetter;
		}
	}
	
	wrongAttempt[attempts] = letter;
	++attempts;
	
	if(hitLetter >= 1){
		hit += hitLetter;
		if(hit == size){
			finished = 1;
		}
	}else{
		++error;
		if(error == 5){
			finished = 2;
		}
	}
}


void chooseWord() {
	int i;

	FILE* f;

	f = fopen("word.txt", "r");
	if(f == 0) {
		printf("Não foi encontrado o arquivo de palavras.\n");
		exit(1);
	}

	int amountWord;
	fscanf(f, "%d", &amountWord);

	srand(time(0));
	int randomico = rand() % amountWord;

	for(i = 0; i <= randomico; i++) {
		fscanf(f, "%s", word);
	}

	fclose(f);
}


void addWord() {

	printf("Digite a nova palavra: \n");
	scanf("%s", word);

	FILE* f;

	f = fopen("word.txt", "r+");
	if(f == 0) {
		printf("Não foi encontrado o arquivo de palavras.\n");
		exit(1);
	}

	int amount;
	fscanf(f, "%d", &amount);
	amount++;
	fseek(f, 0, SEEK_SET);
	fprintf(f, "%d", amount);

	fseek(f, 0, SEEK_END);
	fprintf(f, "\n%s", word);

	fclose(f);

}

int stringSize(char string[]){
	int numChar = 0;
	
	while(string[numChar] != '\0') {
		++numChar;
	}
	
	return numChar;
}

void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Stroing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds) 
        ; 
} 

void main() {
	setlocale(LC_ALL, "Portuguese");
	
	int status;
	int finishedGame = 0;
	
	while(finishedGame == 0){
		system("cls");
		startGame();
		do{
			system("cls");
			hangman();
			writerLetter();
		}while (finished == 0);
		system("cls");
		if(finished == 1){
			printf("Você ganhou.");
		}else{
			printf("Você infelizmente perdeu.");
		}
		delay(1); 
	}
	
}
