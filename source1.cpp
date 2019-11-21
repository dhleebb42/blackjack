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
