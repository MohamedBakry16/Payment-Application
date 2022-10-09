#include "stdio.h"
#include "terminal.h"
#include "string.h"
#include <time.h>



EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	printf("\nPlease, Enter the transaction date in format DD/MM/YYYY  \n");
	gets(termData->transactionDate);

	if (strlen(termData->transactionDate) == 10 && termData->transactionDate[0] <= '3' && termData->transactionDate[1] <= '9' && termData->transactionDate[2] == '/' && termData->transactionDate[3] <= '1' && termData->transactionDate[4] <= '9' && termData->transactionDate[5] == '/' && termData->transactionDate[6] == '2' && termData->transactionDate[7] == '0' && termData->transactionDate[8] <= '3' && termData->transactionDate[9] <= '9')
	{
		//printf("TERMINAL_OK\n");
		return TERMINAL_OK;
	}
	else
	{
		printf(" WRONG_DATE \n");
		return WRONG_DATE;

	}
}





EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	if (termData->transactionDate[8] <= cardData->cardExpirationDate[3] && termData->transactionDate[9] <= cardData->cardExpirationDate[4])
	{
		if ((termData->transactionDate[3] * 10 + termData->transactionDate[4]) <= (cardData->cardExpirationDate[0] * +cardData->cardExpirationDate[1]))
		{
			
			return TERMINAL_OK;
		}
		else
		{
			printf("EXPIRED_CARD \n");
			return EXPIRED_CARD;
		}
	}

	else
	{
		printf("EXPIRED_CARD \n");
		return EXPIRED_CARD;
	}
}




EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("\nPlease, enter the transaction amount \n");
	scanf_s("%f", &termData->transAmount);
	if (termData->transAmount  <= 0)
	{
		printf(" INVALID_AMOUNT");
		return INVALID_AMOUNT;
	}

	else
	{
		//printf("TERMINAL_OK.");
		return TERMINAL_OK;

	}

}




EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	setMaxAmount(termData);
	if (termData->transAmount >= termData->maxTransAmount)
	{
		printf("EXCEED_MAX_AMOUNT\n");
		return EXCEED_MAX_AMOUNT;
	}

	else
	{
		//printf("TERMINAL_OK.");
		return TERMINAL_OK;
	}
}



EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	termData->maxTransAmount = 10000;
	return TERMINAL_OK;
}

