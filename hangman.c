//Abheesh Gupta
//Hangman game created in first programming course using the C language

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define MAXSTRIKES 6 //macro constant for strikes
#define MAXSIZE 20 //macro constant for size
void rules(void); //display rules of the game
void maskWord (char starword[], int size); //mask the word with stars to display
int playRound(char starword[], char answer[]); //play a round of hangman
int occurancesInWord(char userguess, char answer[]); //number of times letter occurs in word
void updateStarWord(char starword[], char answer[], char userguess); //replace respective *
void playAgain(int *play); //ask user if to play again. 1 is yes 2 is no

int main ()
{
    rules();
    FILE *word;
    char x[20];
    int z = 0;
    int play = 1; //initialize variables
    char answer[MAXSIZE];
    word = fopen("words.txt", "r"); //opens file located in directory with words

    while (play == 1 && z != 8) //while loop used until user is done playing or no more words inside file
    {
        fscanf(word, "%s", x); //scans file for word
        strcpy(answer, x); 
        int y = sizeof(answer);
        maskWord(x, y); //calls function that masks word with *
        if (playRound(x, answer) == 1) //conditional used to determine if user won
        {
            printf("Congratulations! You won! The word was %s.\n", answer);
            printf("************************************************************************\n");
        }
        else
        {
            printf("Sorry you did not win the round. The word was %s.\n", answer);
            printf("************************************************************************\n");
        }
        playAgain(&play); //function used to determine if user wants to play again
        ++z;
    }

    if (z == 8) //conditional used to determine if words are no longer inside file
    {
        printf("Looks like there are no more words to play with.\n");
        printf("************************************************************************\n");
    }

    printf("Thank you for playing today!\n");

    fclose(word); //closes file

    return 0;
}

void rules(void) //displays rules of the game
{
    printf("Welcome to the Hangman Game!\n");
    printf("************************************************************************\n");
    printf("Here are the rules.\n");
    printf("I will provide you a set of * characters for each round.\n");
    printf("Each * represents a letter in the English Alphabet.\n");
    printf("You must figure out each letter of the missing word.\n");
    printf("For every correct letter guessed, I will reveal its place in the word.\n");
    printf("Each mistake will result in a strike.\n");
    printf("6 strikes will result in a loss that round.\n");
    printf("Are you ready? Here we go!\n");
    printf("************************************************************************\n");
}

void maskWord (char starword[], int size)
{
    size = 0;
    for (int b = 0; starword[b] != '\0'; ++b) //for loop used to determine size of word
    {
        ++size;
    }

    for (int a = 0; a < size; ++a) //for loop used to change letters of word to *
    {
        if (starword[a] != '\0')
        {
            starword[a] = '*';
        }
    }
    printf("\n");
}

int playRound(char starword[], char answer[]) //simulates entire round of game
{
    char guess;
    char guessed[MAXSIZE] = {'\0'};
    int e = 0;
    int win = 0;
    int strikes = 0;
    int count; //declares variables
    int size = strlen(answer); //assigns size to length of answer

    printf("Welcome to the Round!\n"); 
    printf("The size of the word has %d letters\n\n", size);

    while (strikes < MAXSTRIKES) //loop runs until max amount of strikes is reached
    {
        count = 0;
	    for(int i = 0; i < size; ++i) //for loop used to determine if word still contains *
	    {
		    if(starword[i] == '*')
			    ++count;
	    }

        if (count == 0) //conditional used to determine if * still exist within word
        {
            win = 1;
            break; //breaks loop and returns 1 if * is no longer in the word
        }
        
        printf("You currently have %d strike(s)\n", strikes); //displays strikes user has 
        printf("Letter(s) you have guessed: %s\n\n", guessed); //displays letters guessed by user
        printf("%s\n\n", starword); //displays word w/ *
        printf("Enter your guess: ");
        scanf(" %c", &guess); //user enters their guess
        printf("\n");

        if (isupper(guess) != 0)
        {
            guess = tolower(guess); //lowers letter if upper entered by user
        }
        
        if ((guess < 'A' || guess > 'Z') && (guess < 'a' || guess > 'z')) //conditional used to determine if user entered valid character
        {
            printf("You did not enter a letter from the alphabet.\n\n");
        }
        else
        {
            if (occurancesInWord(guess, answer) > 0) //conditional used to determine if char entered by user occurs in word
            {
                {
                    updateStarWord(starword, answer, guess); //updates word by replacing * with user guess
                    printf("The letter %c is in the word\n\n", guess);
                }
            }    
            else 
            {
                printf("The letter %c is NOT in the word\n\n", guess);
                ++strikes; //users guess not in word so strike increments by 1
            }
            guessed[e] = guess; //updates values held in guessed for every char entered by user
            e++;
        }
    } 

    return win; //returns int after user completes a round
}

int occurancesInWord(char userguess, char answer[]) //determines how many time char is within word
{
    int occur = 0;

    for (int b = 0; answer[b] != '\0'; ++b) //for loop used to return how many times char entered by user occurs in word
    {
        if (answer[b] == userguess)
        {
            ++occur; //increments by 1 every time char occurs in word
        }
    }

    return occur; //returns amount of times character is within word
}

void updateStarWord(char starword[], char answer[], char userguess) //updates word after guesses by user
{
    for(int c = 0; c < strlen(answer); ++c) //for loop used to remove * from word
	{
		if (userguess == answer[c])
		{
			if (starword[c] == '*')
			{
				starword[c] = userguess; //replaces * with user guess if user guess is within word
			}
		}	
	}
}

void playAgain(int *play) //determines whether or not to play again
{
    int choice;

    printf("Would you like to play another round?\n");
    printf("1: Yes\n");
    printf("2: No\n");
    printf("Choice: ");
    scanf("%d", &choice); //user inputs whether or not they would like to play again

    while (choice != 1 && choice != 2) //while loop runs if user doesn't enter valid choice
    {
        printf("You did not enter a valid choice.\n");
        printf("Please try again.\n");
        printf("Choice: ");
        scanf("%d", &choice);
    }

    *play = choice; //play is dereferenced and assigned to int choice

    printf("************************************************************************\n");
}
