#include"Card.h"
#include<string.h>
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("Please enter Card Holder Name: \n");
	gets_s(cardData->cardHolderName, 25);

	if (strlen(cardData->cardHolderName) > 25 || strlen(cardData->cardHolderName) < 19)
	{
		return WRONG_NAME;
	}
	else
	{
		return CARD_OK;
	}
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("Please enter Card Expiry Date: \n");
	gets_s(cardData->cardExpirationDate, 6);

	if ((strlen(cardData->cardExpirationDate) == 0) || (strlen(cardData->cardExpirationDate) < 5) || (strlen(cardData->cardExpirationDate) > 5))
	{
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[2] != '/')
	{
		return WRONG_EXP_DATE;
	}
	else
	{
		return CARD_OK;
	}
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("Please enter Primary Account Number of the card:\n ");
	scanf_s(cardData->primaryAccountNumber);

	if ((strlen(cardData->primaryAccountNumber) > 19) || (strlen(cardData->primaryAccountNumber) < 16) || (strlen(cardData->primaryAccountNumber) == 0))
	{
		return WRONG_PAN;
	}
	else
	{
		return CARD_OK;
	}
}