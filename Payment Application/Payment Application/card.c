#include "stdio.h"
#include "card.h"
#include "string.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("\nPlease, Enter Your Name\n");
	gets(cardData->cardHolderName);

	if (strlen(cardData->cardHolderName) > 24 || strlen(cardData->cardHolderName) < 20 || cardData->cardHolderName == NULL)
	{
		printf("WRONG NAME\n");
		return WRONG_NAME;
	}
	else
	{
		//printf("CARD_OK\n");
		return CARD_OK;
	}
}




EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("\nPlease, Enter Your Card Expir Date in Format  MM/YY   \n");
	gets(cardData->cardExpirationDate);

	if (strlen(cardData->cardExpirationDate) == 5 && cardData->cardExpirationDate[0] <= '1' && cardData->cardExpirationDate[1] <= '9' && cardData->cardExpirationDate[2] == '/' && cardData->cardExpirationDate[3] <= '3' && cardData->cardExpirationDate[4] <= '9')
	{
		//printf("CARD_OK\n");
		return CARD_OK;
	}
	else
	{
		printf("WRONG_EXP_DATA\n");
		return WRONG_EXP_DATE;

	}

}






EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("\nPlease, Enter Your card's Primary Account Number \n");
	gets(cardData->primaryAccountNumber);

	if (strlen(cardData->primaryAccountNumber) > 19 || strlen(cardData->primaryAccountNumber) < 16 || cardData->primaryAccountNumber == NULL)
	{

		printf("WRONG_PAN\n");
		return WRONG_PAN;


	}
	else
	{
		//printf("CARD_OK\n");
		return CARD_OK;


	}

}

