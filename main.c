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
int UserDeck[N_MAX_USER];					//number of user's current card							

//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users
int turnFlag;								//Go Stop Flag info
int DieBlack[N_MAX_USER];					//Player Die or BlackJack Flag 0=survive; 1=Die; 2=BlackJack;

//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD]={0}; //cards that currently the players hold
//cardhold is two dimensional array (user number and number of cards)
//Dealer have to be at the end (Dealer is Operator)

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
	int imgflag;
	imgflag = (cardnum - 1) / 13;
		switch (imgflag) {
		case 0:
			printf("¡ß");
        	switch (cardnum%13) {
        	case 0:
        		printf("K ");
            	break;
        	case 1:
            	printf("A ");
            	break;
        	case 11:
            	printf("J ");
            	break;
        	case 12:
            	printf("Q ");
            	break;
        	default:
            	printf("%d ", cardnum % 13);
        	}
        	break;
    	case 1:
        	printf("¢¼");
        	switch (cardnum % 13) {
        	case 0:
            	printf("K ");
            	break;
        	case 1:
            	printf("A ");
            	break;
        	case 11:
            	printf("J ");
            	break;
        	case 12:
            	printf("Q ");
            	break;
        	default:
            	printf("%d ", cardnum % 13);
        	}
        	break;
    	case 2:
        	printf("¢À");
        	switch (cardnum % 13) {
        	case 0:
        		printf("K ");
        		break;
        	case 1:
            	printf("A ");
            	break;
        	case 11:
            	printf("J ");
            	break;
        	case 12:
            	printf("Q ");
            	break;
        	default:
            	printf("%d ", cardnum % 13);
    		}
        	break;
    	case 3:
        	printf("¢¾");
        	switch (cardnum % 13) {
        	case 0:
        		printf("K ");
        		break;
        	case 1:
        		printf("A ");
        		break;
        	case 11:
        		printf("J ");
        		break;
        	case 12:
        		printf("Q ");
        		break;
        	default:
            	printf("%d ", cardnum % 13);
        	}
        	break;
      	}	
}

//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray(void) {
	
	int i;
	printf("\n\nSetting Cards");
	
	Sleep(300);
	printf(".");
	Sleep(300);
	printf(".");
	Sleep(300);
	printf(".\n");
	
	for (i = 0; i < N_CARDSET*N_CARD; i++) {
		CardTray[i] = i + 1;
	}
	
	Sleep(500);

	printf("\n\nMixing Cards");
	
	Sleep(300);
	printf(".");
	Sleep(300);
	printf(".");
	Sleep(300);
	printf(".\n");

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
	}
	Sleep(500);
}

//get one card from the tray
int pullCard(void) {
	int i;
	
	i = CardTray[cardIndex];
	cardIndex++;
	
	return i;
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
        	Sleep(300);
        	printf(".");
        	Sleep(300);
        	printf(".");
        	Sleep(300);
        	printf(".");
			break;
    	}
    	else {
        	printf("\nInvalid Num. Player number should be 1~5");
    	}
	}
}

//betting
int betDollar(void) {
	int money = NULL; 
	int i;
	printf("\n");
	
	//computer betting
	for (i = 0; i < n_user - 1; i++) {
    	Sleep(200);
    	while (1) {
        	bet[i] = rand() % dollar[i];
        	if (bet[i] > 0) {
        		break;
        	}
    	}
    	printf("\nUser%d Betting : %d", i + 1, bet[i]);
    	dollar[i] = dollar[i] - bet[i];
	}
	
	//player betting
	BetAgain:
	printf("\nMy Betting : ");
	scanf("%d", &bet[n_user-1]);
	
	while (1) {
    	if (bet[n_user-1] > 0 && bet[n_user-1] <= dollar[n_user-1]) {
        	dollar[n_user-1] = dollar[n_user-1] - bet[n_user-1];
        	break;
    	}
    	else {
        	printf("\nInvalid Number. Check your account");
        	goto BetAgain;
    	}
	}
}

//offering initial 2 cards
void offerCards(void) {
	int i, j;
	
	//have to give cards one by one, use double 'for'
	for (j = 0; j < 2; j++) {
		
		//dealer first, players are 'for'
		cardhold[n_user][j] = pullCard();
		UserDeck[n_user]++;
		//printf("\ndealer %d : ", j+1);
		//printCard(cardhold[n_user][j]);
		for (i = 0; i < n_user; i++)
    	{
			cardhold[i][j] = pullCard();
			UserDeck[i]++;
			//printf("\nUser%d %d : ", i + 1, j+1);
			//printCard(cardhold[i][j]);
		}
	}
	return;
}

//print initial card status
void printCardInitialStatus(void) {
	//dealer can see only the second card
	Sleep(500);
	printf("\n\nDealer : ");
	printf("[?] ");
	printCard(cardhold[n_user][1]);

	//cards of users are all open
	int i,j;
	for (i = 0; i < n_user; i++) {
		printf("\nUser %d : ", i + 1);
		for (j = 0; j < 2; j++) {
			Sleep(500);
			printCard(cardhold[i][j]);
    	}
	}
}

int getAction(int user) {
	//code when GO
	//check the current card number
	//assign the card in the array in addition
	//then go back to the start again

	int slot = 0;
	//in order to know the empty slot
	Sleep(1000);

	slot = UserDeck[user];
	cardhold[user][slot] = pullCard();

	printf(">>>");
	printf(" Received card : ");	
	printCard(cardhold[user][slot]);

	UserDeck[user]++;
	
	Sleep(1000);
}

void printUserCardStatus(int user, int cardcnt) {
	int i;
	
	printf("\nUser%d-> card : ", user+1);
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
}

// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult(int user, int cardcnt) {
	//card sum : cardnum cardnum cardnum A A A A
	//in case of sum : lowest number (A is all 1), (one of A is 11) (two of A is 11)
	//provide all number of sum
	
	//count 'A' separately to calculate later
	int i;
	int tmp = 0;
	int sum = 0;
	int a = 0;
	//cardSum[user] =  NULL ;

	printf("\n   card number : ");
	for (i = 0; i < cardcnt; i++) {
		tmp = cardhold[user][i];
		switch (tmp%13) {
		case 1:
        	a++;
        	tmp = 0;
        	break;
		case 11:
		case 12:
    	case 0:
        	tmp = 10;
        	break;
    	default:
        	tmp = tmp % 13;
        	break;
		}
    	printf("%d   ", tmp);
    	sum = sum + tmp;
	}

	printf("\n   card sum : ");
	switch (a) {
	case 0:
		printf("%d ", sum);
    	cardSum[user] = sum;
    	break;
	case 1:
    	if (sum < 10) {
        	printf("%d ", sum + 1);
        	printf("%d ", sum + 11);
        	cardSum[user] = sum+11;
    	}
    	else if (sum == 10) {
        	printf("%d ", sum + 11);
        	cardSum[user] = 21;
    	}
    	else if(sum>10){
        	printf("%d ", sum + 1);
        	cardSum[user] = sum + 1;
    	}
    	break;
	case 2:
    	if (sum < 10) {
    		printf("%d ", sum + 2);
        	printf("%d ", sum + 12);
        	cardSum[user] = sum + 12;
    	}
    	else {
        	printf("%d ", sum + 2);
        	cardSum[user] = sum + 2;
    	}
    	break;
	case 3:
    	if (sum < 9) {
        	printf("%d ", sum + 3);
        	printf("%d ", sum + 13);
        	cardSum[user] = sum + 13;
    	}
    	else {
        	printf("%d ", sum + 3);
        	cardSum[user] = sum + 3;
    	}
    	break;
	case 4:
    	if (sum < 8) {
        	printf("%d ", sum + 4);
        	printf("%d ", sum + 14);
        	cardSum[user] = sum + 14;
    	}
    	else {
    		printf("%d ", sum + 4);
        	cardSum[user] = sum + 4;
    	}
    	break;
	}
}

int checkResult(int roundIndex) {
	int i;
	printf("\n\n\n==========Round%d Result==========\n",roundIndex);
	Sleep(500);

		//when dealer is over 21
		if (cardSum[n_user] > 21) {
        	printf("\nAll Player Win");
		extern int source1();
    	}
    	
    	if (cardSum[n_user] <= 21) {
        	//when dealer is blackjack
        	if (cardSum[n_user] == 21) {
        		if (UserDeck[n_user] == 2) {
            		printf("\n>> Dealer is BlackJack! <<");
            		for (i = 0; i < n_user; i++) {
                		Sleep(300);
                		switch (DieBlack[i]) {
                		case 0:
                    		printf("\n   User%d  -$%d", i + 1, bet[i]);
                    		break;
                		case 1:
                    		printf("\n   User%d  -$%d", i + 1, bet[i]);
                    		break;
                		case 2:
                    		printf("\n   User%d  +$%d", i + 1, bet[i] * 2);
                    		dollar[i] = dollar[i] + (bet[i] * 3);
                    		break;
                		}
            		}
        		}
        		
            	else {
            		//when dealer is 21
            		printf("\nDealer is 21. Checking Player CardSum...");
            		for (i = 0; i < n_user; i++) {
                		Sleep(300);
                		switch (DieBlack[i]) {
                		case 0:
                    		if (cardSum[i] >= cardSum[n_user]) {
								printf("\n   User%d  +$%d", i + 1, bet[i]);
                    			dollar[i] = dollar[i] + (bet[i] * 2);
                    		}
                    		if (cardSum[i] < cardSum[n_user]) {
								printf("\n   User%d  -$%d", i + 1, bet[i]);
                    		}
                    		break;
                		case 1:
                    		printf("\n   User%d  -$%d", i + 1, bet[i]);
                    		break;
                		case 2:
                    		printf("\n   User%d  +$%d", i + 1, bet[i] * 2);
                    		dollar[i] = dollar[i] + (bet[i] * 3);
                    		break;
                		}
            		}
        		}
        	}
        	
        	else {
            	//when dealer is under 21
        		printf("\nDealer Under 21. Checking Player CardSum...");
				extern int source1();
        	}
    	}
    	
    	//capital after betting
    	Sleep(500);
    	printf("\n\n Player Accounts");
    	
		for (i = 0; i < n_user; i++) {
        	Sleep(300);
        	printf("\n   USER%d Money : %d", i + 1, dollar[i]);
    	}
    	
		printf("\n\n\n");
}

int checkWinner() {
	int i,max,winner;

	printf("\n\n\n===========Final Account Result==========\n");
	//capital after game over
	for (i = 0; i < n_user; i++) {
		printf("\n   USER%d Money : %d", i + 1, dollar[i]);
	}

	//compare ranking
	for (i = 0, max = 0; i <= N_MAX_USER; i++) {
		if (dollar[i] > max) {
        	max = dollar[i];
        	winner = i;
    	}
	}
	printf("\n\n>> Winner [ User%d ] [ $%d ] <<\n\n\n\n", winner + 1, dollar[winner]);
}

int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;
	
	//no overlap when using random function 
	srand((unsigned)time(NULL));
	
	//version information
	printf("===============================\n");
	printf("Welcome to SMWU BlackJack\n");
	printf("Release Date : 20191118-0133 \n");
	printf("===============================\n");

	Sleep(1000);
	//set the number of players
	configUser();


	//Game initialization --------
	//1. players' dollar
	//reset and mark the number of players and capital
	Sleep(1000);

	printf("\n\n------------------ Initializing Game --------------------------\n");
	Sleep(1000);
	for (i = 0; i < n_user-1; i++) {
    	printf("\n  User%d : Computer",i+1);
    	dollar[i] = N_DOLLAR;
    	printf("\n      Wallet : %d", dollar[i]);
    	Sleep(300);
	}
	printf("\n  User%d : naneundahyeda", n_user);
	dollar[n_user-1] = N_DOLLAR;
	printf("\n      Wallet : %d", dollar[n_user-1]);

	//2. card tray
	//code that array the cards once and mix
	mixCardTray();


	//Game start --------
	Sleep(1000);
	//system("cls");
	//initializaion of window
	do {
    	printf("\n\n------------------ Round Info --------------------------\n");
		
		//additional round
		roundIndex++;
		printf("Round %d\n", roundIndex);
		
		//capital before betting
		for (i = 0; i < n_user; i++) {
        	printf("\nUSER%d : %d", i+1, dollar[i]);
    	}
    	
		//betting
    	betDollar();
    	
		//mark the distributed cards up to now
    	if (roundIndex != 1) {
        	//printf("\n\nUsed Card : ");
        	for (i = 0; i < cardIndex; i++) {
        		printCard(CardTray[i]);
        	Sleep(50);
        	}
    	}

    	offerCards();
		//distribute card in order of Dealer - User1 - User? - Player, one card each, repeat

		printCardInitialStatus();
		
    	printf("\n\n------------------ GAME start --------------------------\n");
    	//each player's turn
    	//operate in order of Player - Computer - Dealer
    	//Player is n_user-1, dealer is n_user
    	for (i = n_user-1; i > -1;i--) //each player
		{
        	//inform dealer's turn
        	if (i == -1) {
        		i = n_user;
        		printf("\n<<<Dealer Turn>>>", i + 1);
        	}
        	else {
        		//inform current user's turn
        		printf("\n<<<User%d Turn>>>", i + 1);
        	}

			//print current card status 
        	printUserCardStatus(i, UserDeck[i]);
        	//check the card status ::: 
        	//when including 'A', all of number of casesa
        	calcStepResult(i, UserDeck[i]);
        	
			while (1) //do until the player dies or player says stop
        	{
        		//GO? STOP? ::: getAction();
        		//Computer or Player
        		if (i == n_user - 1) {

            		if (cardSum[i] == 21&&UserDeck[i]==2) {
                	//Player is blackjack
                	printf("\n>> User%d is BlackJack! <<", i + 1);
                	DieBlack[i] = 2;
                	goto STOP;
            	}
				
				char select;
            	printf("\n\nGO? (Y/N)");
            
				scanf(" %c", &select);
    			if (select == 'Y' || select == 'y') {
            		getAction(i);
            		printUserCardStatus(i, UserDeck[i]);
            		calcStepResult(i, UserDeck[i]);
            		if (cardSum[i] > 21) {
                		printf("\n over 21\n");
                		goto STOP;
					}
        		}
            	else if (select == 'N' || select == 'n') {
            		printf("STOP\n\n");
            		goto STOP;
        		}
        	}
				else {
            		Sleep(1800);
            		if (cardSum[i] < 17) {
                		printf("\n\nGo.\n");
                		getAction(i);
                		printUserCardStatus(i, UserDeck[i]);
                		Sleep(500);
                		calcStepResult(i, UserDeck[i]);
                		if (cardSum[i] > 21) {
                    		printf("\n\n  over 21");
                    		printf("\n   User%d  -$%d\n\n\n", i + 1, bet[i]);
                    		if (i == n_user) {
                    			goto RoundEND;
                    		}
                    		DieBlack[i] = 1;
                    		goto STOP;
                		}
            		}
            		else {
                		printf("\n\nSTOP.\n\n\n");
                		if (i == n_user) {
                    		goto RoundEND;
                		}
                		goto STOP;
            		}
        		}
        	}

    	STOP:
        	Sleep(2000);
    	}
	RoundEND:

    	//round result
    	checkResult(roundIndex);

    	//initialization of cards that user received
    	for (i = 0; i <= N_MAX_USER; i++) {
        	UserDeck[i] = 0;
    	}

    	//game over due to running out of cards
    	if (cardIndex + n_user*2 >= N_CARDSET * N_CARD) {
        	printf("\nRun out of cards. \nGame is over.");
        	gameEnd = 1;
    	}

    	//game over due to bankruptcy of user
    	for (i = 0; i < n_user; i++) {
        	if (dollar[i] <= 0) {
            	printf("User%d went bankrupt. Game is over.", i + 1);
            	gameEnd = 1;
        	}
    	}

	} while (gameEnd == 0);
	
	checkWinner();
	

	return 0;
}
