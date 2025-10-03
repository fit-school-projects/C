#include <stdio.h>
#include <stdlib.h>

// Struktura pro uchovávání informací o žetonu
typedef struct {
  int value; // Hodnota žetonu
  int row; // Číslo řádku (N, E, W, S)
  int col; // Číslo sloupce (0, 1, 2, atd.)
} Token;

// Globální proměnné pro uchovávání informací o žetonech a skóre
Token tokens[4][4]; // Pole pro uchování informací o žetonech
int scores[2] = {0, 0}; // Pole pro uchování skóre hráčů
int currentPlayer = 0; // Index hráče, který právě hraje (0 nebo 1)
int numTokens = 0; // Počet žetonů, které jsou ještě na stole

// Funkce pro načtení hodnot žetonů z vstupu
void readInput() {
  char rowName;
  int value;
  int row = 0;
  int col = 0;

  // Načítání hodnot žetonů z vstupu
  while (scanf(" %c: {", &rowName) == 1) {
    // Přiřazení čísla řádku podle názvu (N, E, W, S)
    switch (rowName) {
      case 'N':
        row = 0;
        break;
      case 'E':
        row = 1;
        break;
      case 'W':
        row = 2;
        break;
      case 'S':
        row = 3;
        break;
    }

    // Načítání hodnot žetonů pro daný řádek
    while (scanf(" %d", &value) == 1) {
      // Uložení informací o žetonu do globální proměnné
      tokens[row][col].value = value;
      tokens[row][col].row = row;
      tokens[row][col].col = col;
      col++;
      numTokens++;
    }

    // Nulování proměnné pro další řádek
    col = 0;
  }
}

// Funkce pro výběr nejlepšího tahu pro hráče
Token pickBestToken() {
  Token bestToken;
  bestToken.value = -10000; // Inicializace na nízkou hodnotu

  // Procházení všech žetonů
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      // Získání informací o žetonu
      Token token = tokens[i][j];

      // Pokud je žeton ještě dostupný a jeho hodnota je vyšší než dosud
      // nejlepší nalezená hodnota, přiřadíme ho jako nejlepší možný tah
      if (token.value > bestToken.value && token.value != 0) {
        bestToken = token;
      }
    }
  }

  // Vrácení nejlepšího nalezeného žetonu
  return bestToken;
}

// Funkce pro odebrání zvoleného žetonu ze stolu
void removeToken(Token token) {
  // Nastavení hodnoty žetonu na 0, aby byl označen jako odebraný
  tokens[token.row][token.col].value = 0;
  numTokens--; // Snížení počtu žetonů na stole
}

// Funkce pro zjištění, zda je hra ukončená
int isGameOver() {
  // Hra je ukončená, pokud nejsou na stole žádné další žetony
  return numTokens == 0;
}

// Funkce pro simulaci hry
void playGame() {
  // Hraje se, dokud nejsou na stole žádné další žetony
  while (!isGameOver()) {
    // Získání nejlepšího možného tahu pro hráče
    Token token = pickBestToken();

    // Odebrání žetonu ze stolu
    removeToken(token);

    // Přidání hodnoty žetonu do skóre hráče
    scores[currentPlayer] += token.value;

    // Výpis tahu hráče a jeho skóre
    printf("%c: %c[%d] (%d)\n", currentPlayer == 0 ? 'A' : 'B',
           token.row == 0 ? 'N' : (token.row == 1 ? 'E' : (token.row == 2 ? 'W' : 'S')),
           token.col, token.value);

    // Přepnutí na dalšího hráče
    currentPlayer = (currentPlayer + 1) % 2;
  }

  // Výpis celkového skóre obou hráčů
  printf("Celkem A/B: %d/%d\n", scores[0], scores[1]);
}

// Hlavní funkce programu
int main() {
  // Načtení hodnot žetonů ze vstupu
  readInput();

  // Spuštění simulace hry
  playGame();

  return 0;
}
