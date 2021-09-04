/**
 * @file lab3.c
 * @brief a program that emulates the well-known hangman game
 * @author Timothy Goetsch
 * @date 12/2019
 * @bugs probably exist, however I have not found any yet
 * @todo add better visuals, a buffer of guessed characters, statements if a user
 *       guesses an already guessed letter, the ability to guess the entire word
 * @reference for showHangman function https://github.com/tintinmj/Hangman-game/blob/master/game.c 
 */

/********DIRECTIVES********/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 100

/********PROTOTYPES********/
int word_validation(char *word, int length);
int test_letter(char * word, char letter, char *buf, int length);
int complete(char *word, char *buf, int length);
char win(int condition);
void showHangman(int tries);

/********BEGIN MAIN FUNCTION********/ 
int main()
{
    char buffer[SIZE]; /* general use buffer */
    char word[SIZE]; /* word entered by user */
    char buf[SIZE]; /* stores the correctly guessed letters */
    char letter; /* user's guess */
    int length = (int)strlen(word);
    int result = 0; /* stores result to determine win status*/
    int tries = 6; /* amount of tries the user has */
    char play = 'y';/* determines if game continues after a win */
   
    /* Introduce game */
    printf("Welcome to Hang-Man!\n"
        "This is a two-player game.\n"
        "Player One chooses a word and Player Two has to guess the word.\n"
        "Player Two gets 6 incorrect guesses before it is game over and"
        " their Hang-Man is completed.\n");
    
    /* Continue game while there are still attempts left and the user wants to play */
    while(play == 'y'){
        
        /* Collect word from Player One and check for errors */
        printf("Please enter a valid word of less than 100 letters: a-z or A-Z\n");

        if(fgets(buffer, sizeof(buffer), stdin)){
            if(sscanf(buffer, "%s", word) != 1){
                /* printf("Error in input string at sscanf for word\n"); */
               continue; 
            }
        } else{
            /* printf("Error in input string at fgets for word\n"); */
            continue;
        }

        length = (int)strlen(word);/* count of letters in word, doesnt include null character */

        if(!word_validation(word, length)){
            /* printf("Invalid Word, only letters are allowed.\n"); */
            continue;
        }
        
        if(length > 99){
            /* printf("Word must be less than 100 letters\n"); */
            continue;
        }

        /* fill buf with _ characters */
        for(int i = 0; i <= length; i++){
            if(i == length){
                buf[i] = '\0';
            } else {
                buf[i] = '_';
            }
        }
		
		system("clear");

        while(tries){/* keeps program running while user still has tries left */

            /* collect input from user */
            printf("Please enter a valid letter: a-z or A-Z\n");
            
            if(fgets(buffer, sizeof(buffer), stdin)){
                if(sscanf(buffer, "%c", &letter) != 1){
                    printf("Error collecting user input, Goodbye!\n");
                    return 0;
                }
            } else{
                printf("Error collecting user input, Goodbye!\n");
                return 0;
            }

            /* transform input into format for parsing*/
            letter = tolower(letter);

            /* check if input is valid character */
            if(!isalpha(letter)){
                continue;
            }

            /* check if letter is in word */
            if(!test_letter(word, letter, buf, length)){
                tries--;
				showHangman(tries);
            }

            /* check if player has completed word or ran out of tries & if they want to play again*/
           if((result = complete(word, buf, length) || tries == 0)){
                if((play = win(tries)) == 'n'){
                    printf("Have a good day!\n");
                    break;
                } else{
                    tries = 5; /* reset tries */
                    system("clear");
                    break;
                }
            }
        }
    }/* End of Game */

    return 0;
}


/**
 * checks if the word contains any illegal characters
 * @param word word being guessed
 * @param length size of word and buf (should be same for both)
 */
int word_validation(char *word, int length){

    for(int i = 0; i < length; i++){
        if(!isalpha(word[i])){
            return 0;
        }
    }
    return 1;
}

/**
 * checks if a letter is in a word
 * @param word word being guessed
 * @param letter user's guess
 * @param buf string holding user's guess
 * @param word word being guessed
 *
 */
int test_letter(char *word, char letter, char *buf, int length){
    
    int counter = 0;

    for(int i = 0; i < length; i++){
        if(word[i] == letter) {
            buf[i] = letter;
            counter = 1;
        }
    }
        
    if(counter == 0){
        printf("Incorrect!\n");
        printf("Letters Guessed: %s\n", buf);
        return 0;
    }

    printf("Correct!\n");
    printf("Letters Guessed: %s\n\n", buf);

    return 1;
}

/**
 * determines if user has completed the word
 * @param word word being guessed
 * @param buf string holding user guess's 
 * @param length size of word and buf (should be the same for both)
 */
int complete(char *word, char *buf, int length)
{
    for(int i = 0; i < length; i++){
        if(buf[i] != word[i]){
            return 0;
        }
    }

    return 1;
}

/**
 * informs user of win/lose status & prompts user to play again
 * @param condition value declaring win/lose status
 * @return answer whether or not the user want's to play again 
 */
char win(int condition)
{
    char answer = '\0';
    char buffer[256];

    if(condition != 0){
        printf("You got it!\n");
    } else{
        printf("Oh no, you ran out of guesses! Better luck next time!\n");
    }

    while(1){
        printf("Would you like to play again? Y or N: ");
        
        if(fgets(buffer, sizeof(buffer), stdin)){
            if(sscanf(buffer, "%c", &answer) != 1){
                printf("Error in input string at sscanf for letter\n");
                continue;
            }
        } else{
            printf("Error in input string at fgets for word\n");
            continue;
        }
        
        answer = tolower(answer);

        if(answer == 'y' || answer == 'n')
            return answer;
        else
            continue;
    }
    
} 

/**
 * prints the hangman
 * @tries amount of tries left
 */
void showHangman(int tries)
 {

     switch(tries)
     {

     case 0:
         /* system("clear"); */
	printf("\n\t||===== ");
	printf("\n\t||    | ");
	printf("\n\t||   %cO/",'\\');
	printf("\n\t||    | ");
	printf("\n\t||   / %c",'\\');
	printf("\n\t||      \n");
	break;
     case 1:
         /* system("clear"); */
	printf("\n\t||===== ");
	printf("\n\t||    | ");
	printf("\n\t||   %cO/",'\\');
	printf("\n\t||    | ");
	printf("\n\t||     %c",'\\');
	printf("\n\t||      \n");
	break;
     case 2:
         /* system("clear"); */
	printf("\n\t||===== ");
	printf("\n\t||    | ");
	printf("\n\t||   %cO/",'\\');
	printf("\n\t||    | ");
	printf("\n\t||      ");
	printf("\n\t||      \n");
	break;
     case 3:
         /* system("clear"); */
	printf("\n\t||===== ");
	printf("\n\t||    | ");
	printf("\n\t||   %cO/",'\\');
	printf("\n\t||      ");
	printf("\n\t||      ");
	printf("\n\t||      \n");
	break;
     case 4:
         /* system("clear"); */
	printf("\n\t||===== ");
	printf("\n\t||    | ");
	printf("\n\t||   \\O ");
	printf("\n\t||      ");
	printf("\n\t||      ");
	printf("\n\t||      \n");
	break;
     case 5:
         /* system("clear"); */
	printf("\n\t||===== ");
	printf("\n\t||    | ");
	printf("\n\t||    O ");
	printf("\n\t||      ");
	printf("\n\t||      ");
	printf("\n\t||      \n");
	break;
      }//end of switch-case

 }
/********EOF********/
