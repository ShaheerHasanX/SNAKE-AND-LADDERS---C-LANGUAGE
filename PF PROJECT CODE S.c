#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Dice roll generator
int rollDie() {
    return rand() % 6 + 1;
}

// Global variables 
int playerPositions[4] = {0, 0, 0, 0};
int numPlayers, boardSize;
int isBot[4] = {0};
char playerNames[4][50];

// Excess input clearing
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n');
}

// Start Game promt
void gameStartMessage() {
    printf("<------Welcome to Snake and Ladder Game!------>\n");
    printf("Be the first to reach the TOP Win!\n");
    Beep(750, 300);
    Beep(1000, 500);
    Beep(500, 1000);
}

// Board Print
void printBoard(boardSize) {
    printf("\n+----+----+----+----+----+----+----+----+----+----+\n");

    for (int row = boardSize-1; row >= 0; row--) {
        if (row % 2 == 0) { 
// from left
            for (int col =1; col<= 10; col++) {
                int position = row*10 + col;
                int printed = 0;

// Player position
                for (int p = 0; p < numPlayers; p++) {
                    if (playerPositions[p] == position) {
                        printf("| P%d ", p + 1);
                        printed = 1;
                        break;
                    }
                }

                if (!printed) printf("| %2d ", position);
            }
        } 
		else { 
// from right 
            for (int col=10; col >= 1; col--) {
                int position = row * 10 + col;
                int printed = 0;

// Player location
                for (int p = 0; p < numPlayers; p++) {
                    if (playerPositions[p] == position) {
                        printf("| P%d ", p + 1);
                        printed = 1;
                        break;
                    }
                }

                if (!printed) printf("| %2d ", position);
            }
        }
        printf("|\n+----+----+----+----+----+----+----+----+----+----+\n");
    }
    printf("\n");
}

// Snake and ladders setter 
void defineSnakesAndLadders(int snakesAndLadders[101], int boardSize) {
    
    for (int i = 0; i < 101; i++) {
        snakesAndLadders[i] = 0;
    }

    if (boardSize == 5) {
        snakesAndLadders[6]  = 30;  
        snakesAndLadders[20] = 15;
        snakesAndLadders[37] =  8;
        snakesAndLadders[23] = -18;
        snakesAndLadders[49] = -30;
        snakesAndLadders[34] = -21;
        snakesAndLadders[25] = -10;
    }
	else if (boardSize == 7) {
        snakesAndLadders[3]  = 21; 
        snakesAndLadders[15] = 24;
        snakesAndLadders[28] =  4;
        snakesAndLadders[35] = 31;
        snakesAndLadders[69] = -40;
        snakesAndLadders[58] = -24;
        snakesAndLadders[44] = -21;
        snakesAndLadders[26] = -12;
        snakesAndLadders[19] = -13;
    } 
	else if (boardSize == 10) {
        snakesAndLadders[2]  = 21;  
        snakesAndLadders[11] = 17;  
        snakesAndLadders[25] = 19;  
        snakesAndLadders[15] = 14;  
        snakesAndLadders[32] = 23;  
        snakesAndLadders[51] = 21;  
        snakesAndLadders[58] =  7; 
		snakesAndLadders[66] = 21;  
        snakesAndLadders[60] = 13;  
        snakesAndLadders[77] = 18;  
        snakesAndLadders[19] = 30;  
        snakesAndLadders[24] = -19;  
        snakesAndLadders[39] = -19;  
        snakesAndLadders[47] = -33; 
		snakesAndLadders[55] = -29;  
        snakesAndLadders[88] = -34; 
        snakesAndLadders[92] = -21; 
		snakesAndLadders[96] = -20;  
        snakesAndLadders[99] = -81; 
		 
    } 
    
}

// Moving players
int movePlayer(int currentPosition, int roll, int snakesAndLadders[101]) {
    int newPosition = currentPosition + roll;

    if ((newPosition > 100 && boardSize == 10) ||
	    (newPosition > 70 && boardSize == 7)   || 
		(newPosition > 50 && boardSize == 5) ) {
        return currentPosition; 
    }
    

    int resultPosition = newPosition + snakesAndLadders[newPosition];
    if (snakesAndLadders[newPosition] > 0) {
        printf("Yay! You found a ladder to go up! \n");
        	Beep(700, 400);
			Beep(700, 400);
    } else if (snakesAndLadders[newPosition] < 0) {
        printf("Aw snap, a snake bit you. Down you go!\n");
        	Beep(350, 400);
			Beep(350, 400);
    }

    return resultPosition > 100 ? 100 : resultPosition;
}

// Filing
void saveWinnerToFile(const char *winner) {
    FILE *file = fopen("game_results.txt", "a");
    if (file == NULL) {
        printf("Error opening file to save results.\n");
        return;
    }

    fprintf(file, "Winner: %s\n", winner);
    fclose(file);
    printf("Game result saved to game_results.txt.\n");
    Beep(750, 300);
    Beep(1000, 500);
    Beep(500, 1000);
}
// BG COLOR CHANGER
void bgcolor() {
	
    int choice = 0;
    
    do {
        printf("Enter the background color you would like to have:\n");
        printf("1. Aqua Blue\n");
        printf("2. Yellow\n");
        printf("3. White\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 3) {
            printf("Invalid choice! Please enter a valid option (1, 2, or 3).\n");
        }
    } while (choice < 1 || choice > 3);

    switch (choice) {
        case 1:
            system("color 30");
            break;
        case 2:
            system("color E0");
            break;
        case 3:
            system("color F0");
            break;
    }
}

// Main function
int main() {
    srand(time(0));
    int currentPlayer = 0;
    int won = 0;
    
    gameStartMessage();
    bgcolor();

	while (1) {
        printf("Enter the number of players (1 to 4): ");
        
        if (scanf("%d", &numPlayers) == 1 && numPlayers >= 1 && numPlayers <= 4) {
            clearInputBuffer();
            break; 
        }
        printf("Invalid input! Please enter a number between 1 and 4.\a\n");
        clearInputBuffer(); 
    }
    
    for (int i = 0; i < numPlayers; i++) {
        printf("Enter the name of Player %d: ", i + 1);
        fgets(playerNames[i], sizeof(playerNames[i]), stdin);
        playerNames[i][strcspn(playerNames[i], "\n")] = '\0'; 
    }

    if (numPlayers == 1) {
        numPlayers = 2;
        isBot[1] = 1;
        printf("You will play against a bot!\n");
    } else {
        for (int i = 0; i < numPlayers; i++) {
            char choice;
            printf("Press 'Y' if Player %d is a bot: \n", i + 1);
            scanf(" %c", &choice);
            clearInputBuffer();
            isBot[i] = (choice == 'y' || choice == 'Y') ? 1 : 0;
        }
    }

    int boardChoice;
    while (1) { 
        printf("Choose the board size:\n");
        printf("1. 5x10\n2. 7x10\n3. 10x10\n");

        if (scanf("%d", &boardChoice) == 1 && (boardChoice == 1 || boardChoice == 2 || boardChoice == 3)) {
            clearInputBuffer();
            break; 
        }
        printf("Invalid input! Please choose 1, 2, or 3.\a\n");
        clearInputBuffer(); 
    }
    switch (boardChoice) {
        case 1: boardSize = 5; break;
        case 2: boardSize = 7; break;
        case 3: boardSize = 10; break;
        default: printf("Invalid choice.\a\n"); return 0;
    }

    int snakesAndLadders[101];
    defineSnakesAndLadders(snakesAndLadders, boardSize);

    printf("-----Let's start the game!-----\n");

    while (!won) {
        printf("\n%s's turn.\n", playerNames[currentPlayer]);
        Beep(1000, 200);

        if (!isBot[currentPlayer]) {
            printf("Press Enter to roll the die...");
            getchar(); 
        } else {
            printf("Bot is rolling the die...\n");
        }

        int roll = rollDie();
        printf("You rolled a %d.\n", roll);

        playerPositions[currentPlayer] = movePlayer(playerPositions[currentPlayer], roll, snakesAndLadders);
        printf("%s is now at square %d.\n", playerNames[currentPlayer], playerPositions[currentPlayer]);

        printBoard(boardSize);

        if ((playerPositions[currentPlayer] == 100 && boardSize == 10) ||
		 	(playerPositions[currentPlayer] == 70 && boardSize == 7)   ||
			(playerPositions[currentPlayer] == 50 && boardSize == 5)) {
            printf("%s wins!\n", playerNames[currentPlayer]);
            won = 1;
            saveWinnerToFile(playerNames[currentPlayer]);
        }

        currentPlayer = (currentPlayer + 1) % numPlayers;
    }

    printf("<------Game over! Thanks for playing.------>\n");

return 0;

// 2023
}