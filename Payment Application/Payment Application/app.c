#include "stdio.h"
#pragma warning(disable : 4996)
#include "app.h"
#include "string.h"



ST_cardData_t cardData;
ST_terminalData_t termData;
ST_transaction_t transData;
uint32_t transactionSequenceNumber=0;



void appStart(void)
{
	while (1)
	{
		if (getCardHolderName(&(transData.cardHolderData)) == CARD_OK)
		{
			if (getCardExpiryDate(&(transData.cardHolderData)) == CARD_OK)
			{
				if (getTransactionDate(&transData.terminalData) == TERMINAL_OK)
				{
					if (isCardExpired(&(transData.cardHolderData),&(transData.terminalData)) == TERMINAL_OK)
					{
						if (isValidAccount(&(transData.cardHolderData), &transData, &termData) == APPROVED)
						{
							if (recieveTransactionData(&transData) == APPROVED)
							{
								saveTransaction(&transData);
								getTransaction(transactionSequenceNumber, &transData);
							}
						}

					}
				}
			}
		}
	}
}