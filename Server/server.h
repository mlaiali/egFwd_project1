//
// Created by server on 10/21/22.
//

#ifndef EGFWD_PROJECT1_SERVER_H
#define EGFWD_PROJECT1_SERVER_H

#include "../Card/card.h"
#include "../Terminal/terminal.h"

typedef enum EN_transState_t
{
    APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef enum EN_serverError_t
{
    SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t ;

typedef enum EN_accountState_t
{
    RUNNING,
    BLOCKED
}EN_accountState_t;

typedef struct ST_accountsDB_t
{
    float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;


/**
 * This function will take all transaction data and validate its data, it contains all server logic.
It checks the account details and amount availability.
If the account does not exist return FRAUD_CARD,
if the amount is not available will return DECLINED_INSUFFICIENT_FUND,
if the account is blocked will return DECLINED_STOLEN_CARD,
if a transaction can't be saved will return INTERNAL_SERVER_ERROR , else returns APPROVED.
It will update the database with the new balance.
Test your function:*/
EN_transState_t receiveTransactionData(ST_transaction_t *transData);

/**
 * This function will take card data and validate if the account related to this card exists or not.
It checks if the PAN exists or not in the server's database (searches for the card PAN in the DB).
If the PAN doesn't exist will return ACCOUNT_NOT_FOUND and the account reference will be NULL, else will return SERVER_OK and return a reference to this account in the DB.
 * */
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountReference);

/**
 * This function takes a reference to the account into the database and verifies if it is blocked or not.
If the account is running it will return SERVER_OK, else if the account is blocked it will return BLOCKED_ACCOUNT.
Test your function:
 * */
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference);


/**
 * This function will take terminal data and a reference to the account in the database and check if the account has a sufficient amount to withdraw or not.
It checks if the transaction's amount is available or not.
If the transaction amount is greater than the balance in the database will return LOW_BALANCE, else will return SERVER_OK.
Test your function:
 * */
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountReference);


/**
This function will store all transaction data in the transactions database.
It gives a sequence number to a transaction,
this number is incremented once a transaction is processed into the server,
you must check the last sequence number in the server to give the new transaction a new sequence number.
It saves any type of transaction, APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD,
INTERNAL_SERVER_ERROR.
It will list all saved transactions using the listSavedTransactions function.
Assuming that the connection between the terminal and server is always connected,
then it will return SERVER_OK.
Test your function:
*/

EN_serverError_t saveTransaction(ST_transaction_t *transData);


void listSavedTransactions(void);


#endif //EGFWD_PROJECT1_SERVER_H
