#include"Terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	printf("Please enter Transaction Date:\n");
	gets_s(termData->transactionDate, 11);
	if ((strlen(termData->transactionDate) == 0) || (strlen(termData->transactionDate) < 10))
	{
		return WRONG_DATE;
	}
	else if ((termData->transactionDate[2] != '/') || (termData->transactionDate[5] != '/'))
	{
		return WRONG_DATE;
	}
	else
	{
		return TERMINAL_OK;
	}
}
EN_terminalError_t isCardExpired(void)
{
	if ((cardData.cardExpirationDate[0] < termData.transactionDate[3]) || (cardData.cardExpirationDate[1] < termData.transactionDate[4]))
	{
		return EXPIRED_CARD;
	}
	else if ((cardData.cardExpirationDate[3] < termData.transactionDate[8]) || (cardData.cardExpirationDate[4] < termData.transactionDate[9]))
	{
		return EXPIRED_CARD;
	}
	else
	{
		return TERMINAL_OK;
	}
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("Please enter the Transactiom Amount:\n");
	scanf_s("%f", &termData->transAmount);
	if (termData->transAmount <= 0)
	{
		return INVALID_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	printf("Maximum Amount:\n");
	scanf_s("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}
//EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData); // Optional