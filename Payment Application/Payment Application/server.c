
#include "stdio.h"
#include "server.h"
#include "string.h"
#include <time.h>

int sequence = 0;
ST_accountsDB_t accountDB[255] =
{
{200000 ,RUNNING, "5459374615436851"},
{0      ,RUNNING, "5459374615436852"},
{5000   ,RUNNING, "5459374615436853"},
{93483  ,BLOCKED, "5459374615436854"},
{248293 ,RUNNING, "5459374615436855"},
{2000000,BLOCKED, "5459374615436856"},
{1000000,BLOCKED, "5459374615436857"},
{3000   ,RUNNING, "5459374615436858"},
{20000  ,BLOCKED, "5459374615436859"},
{4000   ,RUNNING, "5459374615436860"} };




ST_transaction_t transactions_DB[255] = { 0 };

int i = 0;

ST_cardData_t cardData;
ST_terminalData_t  termdData;







EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_transaction_t* transData, ST_terminalData_t* termData)  //  Valid Account and Valid Amount and Running Account in the same function.
{
	float amount;
	getCardPAN(cardData);

	for (i = 0; i < 255; i++)
	{
		char x[20] = { 0 };

		for (int j = 0; j < 20; j++)
		{
			x[j] = accountDB[i].primaryAccountNumber[j];
		}

		if (strcmp(cardData->primaryAccountNumber, x) == 0)
		{
			//printf("SERVER_OK CORRECT PAN\n");
			if (accountDB[i].state)

			{
				printf("DECLINED_STOLEN_CARD\n");
				return DECLINED_STOLEN_CARD;
			}
			else

			{
				//printf("RUNNING\n");
				printf("\nPLEASE, ENTER THE AMOUNT\n");
				scanf_s("%f", &amount);
				termData->transAmount = amount;
				if (isBelowMaxAmount(termData) == TERMINAL_OK)
				{
					if (amount <= accountDB[i].balance)
					{
						accountDB[i].balance = accountDB[i].balance - amount;
						transData->terminalData.transAmount = amount;
						return APPROVED;

					}
					else
					{
						printf("LOW BALANCE\n");
						return LOW_BALANCE;
					}
				}
				else
				{
					return EXCEED_MAX_AMOUNT;
				}

			}
		}

	}
	printf("\nACCOUNT_NOT_FOUND\n");
	return ACCOUNT_NOT_FOUND;
}



EN_accountState_t recieveTransactionData(ST_transaction_t* transData) 
{
	
		printf("\nSuccessful transaction\nNew blance is: ");
		printf("%f", accountDB[i].balance);
		printf("\n");

		return APPROVED;


}


EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	sequence++;
	transData->transactionSequenceNumber = sequence;

	strcpy_s(transactions_DB[sequence].cardHolderData.cardHolderName,25*sizeof(char), transData->cardHolderData.cardHolderName);
	strcpy_s(transactions_DB[sequence].cardHolderData.primaryAccountNumber, 20 * sizeof(char), transData->cardHolderData.primaryAccountNumber);
	strcpy_s(transactions_DB[sequence].terminalData.transactionDate, 11 * sizeof(char), transData->terminalData.transactionDate);
	transactions_DB[sequence].terminalData.transAmount = transData->terminalData.transAmount;
	transactions_DB[sequence].transactionSequenceNumber = transData->transactionSequenceNumber;

	return SERVER_OK;

}



EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	printf("\nEnter transaction number\n");
	scanf_s("%d", &transactionSequenceNumber);

	if (transactionSequenceNumber <= transData->transactionSequenceNumber && transactionSequenceNumber >= 0)
	{
		printf("\n\nName is:                         %s\n", transactions_DB[transactionSequenceNumber].cardHolderData.cardHolderName);
		printf("Primary account number is:       %s\n", transactions_DB[transactionSequenceNumber].cardHolderData.primaryAccountNumber);
		printf("Trans amount is:                 %f\n", transactions_DB[transactionSequenceNumber].terminalData.transAmount);
		printf("Transaction date is:             %s\n", transactions_DB[transactionSequenceNumber].terminalData.transactionDate);
		printf("Transaction sequence number is:  %d\n\n\n", transactions_DB[transactionSequenceNumber].transactionSequenceNumber);

		return SERVER_OK;
	}

	else
	{
		printf("TRANSACTION_NOT_FOUND\n\n");
		return TRANSACTION_NOT_FOUND;

	}
}




