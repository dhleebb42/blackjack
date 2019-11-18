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

//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
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
			printf("��");
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
        	printf("��");
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
        	printf("��");
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
        	printf("��");
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
	
	//computer betting
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
	
	//player betting
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
	int i, j;
	
	
	//���徿 ������� �ϱ⿡, ���� For �� ���
	for (j = 0; j < 2; j++) {
		//��������, �÷��̾���� for��
		cardhold[n_user][j] = pullCard();
		UserDeck[n_user]++;
		//printf("\n���� %d�� : ", j+1);
		//printCard(cardhold[n_user][j]);
	for (i = 0; i < n_user; i++)
    	{
			cardhold[i][j] = pullCard();
			UserDeck[i]++;
			//printf("\nUser%d %d�� : ", i + 1, j+1);
			//printCard(cardhold[i][j]);
		}
	}

	return;
}

//print initial card status
void printCardInitialStatus(void) {
	//������ �ι�° �常 ����
	printf("\n\nDealer : ");
	printf("[?] ");
	printCard(cardhold[n_user][1]);

	//������ ī��� ���� ����
	int i,j;
	for (i = 0; i < n_user; i++) {
		printf("\nUser %d : ", i + 1);
		for (j = 0; j < 2; j++) {
			printCard(cardhold[i][j]);
    	}
	}
}

int getAction(void) {
	//GO �ҋ� �ڵ��Դϴ�.
	//���� ī�� �� ���� Ȯ���ϰ�
	//ī�� �߰��� �迭�� �������ְ�
	//�ٽ� �������� ���ư��ָ� �˴ϴ�.

	int slot = 0;
	int user; 
	//�󽽷� �ľǿ�

	slot = UserDeck[user];
	cardhold[user][slot] = pullCard();

	printCard(cardhold[user][slot]);
	printf(" ī�带 �޾ҽ��ϴ�\n");

	UserDeck[user]++;
}


void printUserCardStatus(int user, int cardcnt) {
	int i;
	
	printf("\nUser%d-> card : ", user+1);
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
}




// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult(int user, int cardcnt) {
	//ī�� �� : ī���ȣ ī���ȣ ī���ȣ A A A A
	//�� ��� : �� ���� �� (A�� �� 1), (A�� �ϳ��� 11) (A�� ���� 11)
	//��� ���� ���� �� �����ϴ� ��
	
	//a�� ���� ����� ���� ���� ī��Ʈ
	int i;
	int tmp = 0;
	int sum = 0;
	int a = 0;
	cardSum[user] =  NULL ;

	printf("\n   ī�� �� : ");
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

	printf("\n   ī�� �� : ");
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
      	//printf("%d ", sum + 22);
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
    	//printf("%d ", sum + 23);
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
    	//printf("%d ", sum + 24);
    	break;
	}
}

int checkResult() {
	
}

int checkWinner() {
	
}



int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;
	
	//���� �Լ� ��� �� �ߺ� ������ 
	srand((unsigned)time(NULL));
	
	//���� ���� 
	printf("===============================\n");
	printf("Welcome to SMWU BlackJack\n");
	printf("Release Date : 20191118-0133 \n");
	printf("===============================\n");

	Sleep(1000);
	//set the number of players
	configUser();


	//Game initialization --------
	//1. players' dollar
	//�÷��̾��� ���� �ں��� ���� �� ǥ��
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
	//ī�� �ѹ� �����ϰ�, �����ִ� �ڵ�
	//�Ʒ� �Լ����� printf �ּ� ������ Ȯ�� ����
	mixCardTray();



	//Game start --------
	Sleep(1000);
	//system("cls");
	//â�ʱ�ȭ
	do {
    	printf("\n\n------------------ Round Info --------------------------\n");
		
		//���� �߰�
		roundIndex++;
		printf("Round %d\n", roundIndex);
		
		//���� �� �ں���
		for (i = 0; i < n_user; i++) {
        	printf("\nUSER%d : %d", i+1, dollar[i]);
    	}
    	
		//����
    	betDollar();
    	
		//���� �� �ں���
    	for (i = 0; i < n_user; i++) {
        	printf("\nUSER%d : %d", i + 1, dollar[i]);
    	}

    	offerCards();
		//ī�带 �����ٶ��� Dealer - User1 - User? - Player ������ 1�徿 �ݺ�

		printCardInitialStatus();
		
    	printf("\n\n------------------ GAME start --------------------------\n");
    	//each player's turn
    	//Player - Computer - Dealer ������ ����
    	//Player �� n_user-1 ������ n_user
    	for (i = n_user-1; i > -1;i--) //each player
		{
        	//print current card status 
        	//���� ī�� ���� �ִ��� �����ֱ�
        	printUserCardStatus(i, UserDeck[i]);
        	//check the card status ::: 
        	//���� ī�� �� �˷��ֱ� a���Խ� ����� �� ���
        	calcStepResult(i, UserDeck[i]);
        	while (1) //do until the player dies or player says stop
        	{
        		//GO? STOP? ::: getAction();
        		char select;
            	printf("\n\nGO �Ͻðڽ��ϱ�? (Y/N)");
        		//scanf�� ���� �ҷ��ö��� %c�տ� ��ĭ ������Ѵ�. �׷��� ������ �ݺ������� ���������µ�, �Է� ���۰� �ֱ� �����̶� ����.. 2019-11-19
            
			scanf(" %c", &select);
        	if (select == 'Y' || select == 'y') {
            	getAction(i);
            	printUserCardStatus(i, UserDeck[i]);
            	calcStepResult(i, UserDeck[i]);
            	if (cardSum[i] > 21) {
                	printf("\n 21�ʰ�\n");
                	goto STOP;
				}
        	}
            else if (select == 'N' || select == 'n') {
            	printf("STOP\n\n");
            	goto STOP;
        		}
        	}
        	STOP:
        	turnFlag = 0;
        	//Stop ���� �ʱ�ȭ
    	}
    	gameEnd = 1;	
		//result
		checkResult();
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}
