//
// Created by server on 10/21/22.
//
#include <stdio.h>
#include "server.h"
#include <string.h>

static short sequenceIndicate = 0;
ST_transaction_t  transaction[255] ={0} ;
/**
 *  float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
 * */
ST_accountsDB_t accountsDb [255] = {
        {25000, RUNNING, "8989374615436851"},
        {3500, BLOCKED, "8989374615435051"},
        {45000, RUNNING, "8989374615435051"},

};



/**
 * This function will take all transaction data and validate its data, it contains all server logic.
It checks the account details and amount availability.
If the account does not exist return FRAUD_CARD, if the amount is not available will return DECLINED_INSUFFECIENT_FUND,
if the account is blocked will return DECLINED_STOLEN_CARD, if a transaction can't be saved will return INTERNAL_SERVER_ERROR , else returns APPROVED.
It will update the database with the new balance.
Test your function:
 * */
EN_transState_t receiveTransactionData(ST_transaction_t *transData){
    EN_serverError_t validAccount = isValidAccount(&transData->cardHolderData,&accountsDb);
    EN_serverError_t blockedAccount = isBlockedAccount(&accountsDb);
    EN_serverError_t amountAvailable = isAmountAvailable(&transData->terminalData,&accountsDb);
    EN_serverError_t sTransaction = saveTransaction(&transData);
//    listSavedTransactions();
    if(validAccount == ACCOUNT_NOT_FOUND)
        return DECLINED_STOLEN_CARD;
    if(blockedAccount == TRANSACTION_NOT_FOUND)
        return FRAUD_CARD;
    if(amountAvailable == LOW_BALANCE)
        return DECLINED_INSUFFECIENT_FUND;
    if(sTransaction == SAVING_FAILED)
        return INTERNAL_SERVER_ERROR;

    return APPROVED;
}

/**
 * This function will take card data and validate if the account related to this card exists or not.
It checks if the PAN exists or not in the server's database (searches for the card PAN in the DB).
If the PAN doesn't exist will return ACCOUNT_NOT_FOUND and the account reference will be NULL, else will return SERVER_OK and return a reference to this account in the DB.
 * */
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountReference){
    for (int i = 0; i < 255; ++i) {
        if(strcmp(cardData->primaryAccountNumber , accountReference[i].primaryAccountNumber) ==0)
        {
            *accountReference =accountReference[i];
            return SERVER_OK;
        } else
        {
            accountReference = NULL;
            return ACCOUNT_NOT_FOUND;
        }
    }
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference){

    if(accountReference->state == RUNNING)
        return SERVER_OK ;
    else if (accountReference->state == BLOCKED)
        return BLOCKED_ACCOUNT;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountReference){
    if(termData->transAmount > accountReference->balance)
        return LOW_BALANCE;
    else return SERVER_OK;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){
    transData->transactionSequenceNumber = sequenceIndicate;
    if(transData->transactionSequenceNumber < 255){
        transaction[transData->transactionSequenceNumber].cardHolderData =transData->cardHolderData;
        transaction[transData->transactionSequenceNumber].terminalData =transData->terminalData;
        transaction[transData->transactionSequenceNumber].transState =transData->transState;
        transaction[transData->transactionSequenceNumber].transactionSequenceNumber =transData->transactionSequenceNumber +1;

        sequenceIndicate ++;

    }

    return SERVER_OK;
}

void listSavedTransactions(void){
    for (int i = 0; i < 255; ++i) {
        printf("\n%d",transaction[i].transactionSequenceNumber);
        printf("\n%s",transaction[i].terminalData.transactionDate);
        printf("\n%f",transaction[i].terminalData.transAmount);
        printf("\n%f",transaction[i].terminalData.maxTransAmount);
        printf("\n%s",transaction[i].cardHolderData.cardHolderName);
        printf("\n%s",transaction[i].cardHolderData.primaryAccountNumber);
        printf("\n%s",transaction[i].cardHolderData.cardExpirationDate);

    }
}