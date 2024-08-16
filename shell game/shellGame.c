#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void shuffleBall(int randomNumber, int ball); //will go through the process of shuffling the ball through the 3 cups
void initializeBall(); //shows the ball, meant to be done before shuffling and after guessing.
int allowPick(char pick); //will prompt the player to pick which cup they think the ball is in after shuffling
void countdown();
void evaluatePick(int guess, int location);
bool playAgainOrEnd();
void startMenu();

int cupNum; //signifies which of 3 cups the ball can be in. 0, 1, 2 and moving left and right will subtract and add 1 respectively
int ballLocation; //signifies which cup the ball is in
int randTurnsDecider; //decides how many times the ball will be moved. up to 25 times as of now, minimum of 1 time.
char pick; // what the player picks L, C, or R.

int main(){
startMenu();
do{
srand(time(NULL));
initializeBall(ballLocation);
shuffleBall(randTurnsDecider, ballLocation);
int guess = allowPick(pick);
evaluatePick(guess, ballLocation);
} while(playAgainOrEnd());
return 0;
}

void shuffleBall(int randomNumber, int ball){
    randomNumber = (rand() % 24) + 1;
    int action;
    ballLocation = ball;
    for(int i = 0; i < randomNumber; i++){
    action = rand() % 2; //to restrict inputs to 0, 1
        if(action == 0){
        ballLocation--;
        printf("Left!\n");
        }
        else{
        ballLocation++;
        printf("Right!\n");
        }
        switch (ballLocation) { //this switch statement ensures the ball stays in the legal range of cups.
            case -1: //if ball goes left on leftmost cup, it is switched around to the other side
                ballLocation = 2;
                printf("Leftmost to Rightmost!\n");
                break;
            case 3: //if ball goes right on rightmost cup, it is switched around to leftmost side
                ballLocation = 0;
                printf("Rightmost to Leftmost!\n");
                break;
            default: //if the ball is in legal range, nothing is changed.
                break;
            }
        //printf("Ball Location: %d\n", ballLocation);
        countdown();
    }
    printf("Number of Moves: %d\n", randomNumber); //prints the number of moves after they are done (lol) so you are left in suspense
}

void initializeBall(){
    ballLocation = rand() % 3;
    char *ballStr;
    switch (ballLocation){
    case 0:
        ballStr = "Left"; 
        break;
    case 1:
        ballStr = "Center"; 
        break;
    case 2:
        ballStr = "Right";
        break;
    default:
        ballStr = "Unknown";
        break;
    }
    printf("Intial Ball Location: %s Cup\n", ballStr);
}

int allowPick(char pick){ //prompts the player to guess which cup the ball is in. has some error control
    bool madePick;
    printf("Which Cup is the ball in?\nEnter L, C, or R: ");
    do{
    scanf(" %c", &pick);
    pick = toupper(pick);
        switch (pick){
            case 'L':
                madePick = true;
                cupNum = 0;
                return cupNum;
            case 'C':
                madePick = true;
                cupNum = 1;
                return cupNum;
            case 'R':
                madePick = true;
                cupNum = 2;
                return cupNum;
            default:
                madePick = false;
                printf("Your Guess was not valid or read correctly, Enter Again.\n");
                break;
                }
    }while(!madePick);
    return -1;
}

void countdown(){
    #ifdef _WIN32 //gives a countdown before the next number displays (Windows version)
    Sleep(1000);
    printf("3\n");
    Sleep(1000);
    printf("2\n");
    Sleep(1000);
    printf("1\n");
    Sleep(1000);
    system("cls");
    #else //gives a countdown before the next number displays (Linux and MacOs version)
    sleep(1);
    printf("3\n");
    sleep(1);
    printf("2\n");
    sleep(1);
    printf("1\n");
    sleep(1);
    system("clear");
    #endif
}

void evaluatePick(int guess, int location){
    char *guessStr;
    char *locationStr;
    switch (guess){ // Determines the string for the guessed cup
    case 0:
        guessStr = "Left"; 
        break;
    case 1:
        guessStr = "Center"; 
        break;
    case 2:
        guessStr = "Right";
        break;
    default:
        guessStr = "Unknown";
        break;
    }
    switch (location){  // Determines the string for the actual ball location
    case 0:
        locationStr = "Left"; 
        break;
    case 1:
        locationStr = "Center"; 
        break;
    case 2:
        locationStr = "Right";
        break;
    default:
        locationStr = "Unknown";
        break;
    }
    if(guess == location){
        printf("You got it! The ball was under the %s cup!\n", locationStr);
    }
    else{
        printf("Not correct, the ball is located under the %s cup.\n", locationStr);
    }
}

bool playAgainOrEnd(){
    char choice;
    printf("do you want to play again?(y/n):");
    scanf(" %c", &choice);
    choice = toupper(choice);
    switch (choice){
    case 'Y':
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
        return true;
    case 'N':
        printf("\nThanks for Playing!");
        return false;
    default:
        printf("\nThanks for Playing! (default case, sign you input something other than Y and N or (y and n)");
        return false;
    }

}

void startMenu(){
    printf("Welcome to Shell Game!\n\nCreated by Louis Queneau\n\nThe object of this game is to keep track of a ball between 3 Shells.\nOnce you start, the initial ball location and initial direction will be shown.\nAfter up to 25 times of moving the ball, you will be prompted to guess the answer!\nIf a ball goes right on the Right shell, it will go over to the left side.\nSame is true in reverse on the Left Side\n\nPress the Enter key to start the game");
    getchar();
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}