#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30


//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;							


//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users


//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0; 							//game end flag

//some utility functions

//get an integer input from standard input (keyboard)
//return : input integer value
//         (-1 is returned if keyboard input was not integer)
int getIntegerInput(void) {
    int input, num;
    
    num = scanf("%d", &input);
    fflush(stdin);
    if (num != 1) //if it fails to get integer
        input = -1;
    
    return input;
}


//card processing functions ---------------

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {
	
}


//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray(void) {
	int CardTray[N_CARDSET*N_CARD] = {0};
	int i;
	
	printf("\n\nBefore MixCard\n");
	for(i = 0; i < N_CARDSET*N_CARD; i++) {
    	CardTray[i] = i + 1;
    	printf(" %d",CardTray[i]);
   }
   printf("\n\nAfter MixCard\n");
   int rnd1,rnd2 = 0;
   int tmp = NULL;
   srand((unsigned)time(NULL));
   for (i = 0; i < N_CARDSET*N_CARD; i++) {
      rnd1 = rand() % 52;
      rnd2 = rand() % 52;
      if (rnd1 != rnd2) {
         tmp = CardTray[rnd1];
         CardTray[rnd1] = CardTray[rnd2];
         CardTray[rnd2] = tmp;
      }
   }
   for (i = 0; i < N_CARDSET*N_CARD; i++) {
      printf(" %d", CardTray[i]);
   }

}

//get one card from the tray
int pullCard(void) {
}


//playing game functions -----------------------------

//player settiing
int configUser(void) {
   printf("\nHow many Players?");
   Sleep(500);
   while (1) {
      printf("\nPlayer Num : ");
      scanf("%d", &n_user);
      Sleep(500);
      printf("\n===Checking===");
      Sleep(1000);
      if (0 < n_user&&n_user < 6) {
         printf("\n%d Players entered the game...", n_user);
         break;
      }
      else {
         printf("\nInvalid Num. Player number should be 1~5");
      }
   }
}


//betting
int betDollar(void) {
   int money=NULL; int i;
   printf("\n");
   //컴퓨터 베팅
   for (i = 0; i < n_user - 1; i++) {
      Sleep(200);
      while (1) {
         money = rand() % dollar[i];
         if (money > 0) {
            break;
         }
      }
      printf("\nUser%d Betting : %d", i + 1, money);
      dollar[i] = dollar[i] - money;
   }
   //플레이어 베팅
   printf("\nMy Betting : ");
   scanf("%d", &money);
   while (1) {
      if (money > 0 && money < dollar[n_user-1]) {
         dollar[n_user-1] = dollar[n_user-1] - money;
         break;
      }
      else {
         printf("\nInvalid Number. Check your account");
      }
   }
}


//offering initial 2 cards
void offerCards(void) {
	int i;
	//1. give two card for each players
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0] = pullCard();
		cardhold[i][1] = pullCard();
	}
	//2. give two card for the operator
	cardhold[n_user][0] = pullCard();
	cardhold[n_user][1] = pullCard();
	
	return;
}

//print initial card status
void printCardInitialStatus(void) {
	
}

int getAction(void) {
	
}


void printUserCardStatus(int user, int cardcnt) {
	int i;
	
	printf("   -> card : ");
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
	printf("\t ::: ");
}




// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult() {
	
}

int checkResult() {
	
}

int checkWinner() {
	
}



int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;
	
	srand((unsigned)time(NULL));
	
	printf("===============================\n");
	printf("Welcome to SMWU BlackJack\n");
	printf("Release Date : 20191118-0133 \n");
	printf("===============================\n");

	Sleep(1000);

	//set the number of players
	configUser();


	//Game initialization --------
	//1. players' dollar
	//플레이어의 수와 자본금 리셋 및 표기
	Sleep(2000);
	system("cls");

	printf("\n===Initializing Game===");
	Sleep(1000);
	for (i = 1; i < n_user; i++) {
		printf("\n  User%d : Computer",i);
    	dollar[i - 1] = N_DOLLAR;
    	printf("\n      Wallet : %d", dollar[i-1]);
	}
	printf("\n  User%d : naneundahyeda", n_user);
	dollar[n_user] = N_DOLLAR;
	printf("\n      Wallet : %d", dollar[n_user]);

	//2. card tray
	//카드 한번 정렬하고, 섞어주는 코드
	//아래 함수에서 printf 주석 해제시 확인 가능
	mixCardTray();



	//Game start --------
	do {
		
		betDollar();
		offerCards(); //1. give cards to all the players
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		printf("%d", gameEnd);
    	gameEnd = 1;
    	printf("%d", gameEnd);
		//each player's turn
		//for () //each player
		{
			//while () //do until the player dies or player says stop
			{
				//print current card status printUserCardStatus();
				//check the card status ::: calcStepResult()
				//GO? STOP? ::: getAction()
				//check if the turn ends or not
			}
		}
		
		//result
		checkResult();
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}
