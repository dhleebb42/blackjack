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

