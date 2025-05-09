#include"Server.h"

ST_accountsDB_t accountsDB[255] = { 2000.0, BLOCKED, "8989374615436851", 4000.0,RUNNING,"5807007076043875"
,10000.0,RUNNING,"9826374653748594", 0.0,BLOCKED,"8625374837263728", 100.0,BLOCKED,"8263748574637489" };
ST_transaction_t accountsTD[255] = { 0 };

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	strcpy(accountsTD[0].cardHolderData.primaryAccountNumber, cardData.primaryAccountNumber);
	accountsTD[0].terminalData.transAmount = termData.transAmount;
	accountsTD[0].terminalData.maxTransAmount = termData.maxTransAmount;

	if (strcmp(accountsTD[0].cardHolderData.primaryAccountNumber, accountsDB[0].primaryAccountNumber) != 0)
	{
		return FRAUD_CARD;
	}
	else if (accountsTD[0].terminalData.transAmount > accountsDB[0].balance)
	{
		return DECLINED_INSUFFECIENT_FUND;
	}
	else if (accountsDB[0].state == BLOCKED)
	{
		return DECLINED_STOLEN_CARD;
	}
	else
	{
		accountsDB->balance = accountsDB->balance - accountsTD->terminalData.transAmount;
		return APPROVED;
	}
}
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_transaction_t* transData)
{
	if (strcmp((cardData->primaryAccountNumber), (accountsDB[0].primaryAccountNumber)) == 0)
	{
		return SERVER_OK;
	}
	else
	{
		return ACCOUNT_NOT_FOUND;
	}
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	*accountRefrence = accountsDB[0];
	if (accountRefrence->state)
	{
		return SERVER_OK;
	}
	else
		return BLOCKED_ACCOUNT;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	*accountRefrence = accountsDB[0];
	if (termData->transAmount > accountRefrence->balance)
	{
		return LOW_BALANCE;
	}
	else
	{
		return SERVER_OK;
	}
}
