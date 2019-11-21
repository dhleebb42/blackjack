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
