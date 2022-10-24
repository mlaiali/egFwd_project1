//
// Created by server on 10/21/22.
//
#include <stdio.h>
#include "server.h"
#include "../util/utiliti.h"
#include <string.h>
#define  isBlockedAccountTest main
static short sequenceIndicate = 0;
ST_transaction_t  transaction[255] ={0} ;
/**
 *  float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
 * */
ST_accountsDB_t accountsDb [255] = {
        {1000, RUNNING, "8989374615436851"},
        {3500, BLOCKED,  "5807007076043875"},
        {45000, RUNNING, "5594444608764305"},

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
    EN_serverError_t sTransaction    = saveTransaction(transData);
    EN_serverError_t validAccount    = isValidAccount(&transData->cardHolderData,(ST_accountsDB_t*) &accountsDb);
    EN_serverError_t blockedAccount  = isBlockedAccount((ST_accountsDB_t *) &accountsDb);
    EN_serverError_t amountAvailable = isAmountAvailable(&transData->terminalData, (ST_accountsDB_t *) &accountsDb);



    if(validAccount == ACCOUNT_NOT_FOUND)
        return FRAUD_CARD;

    if(blockedAccount == BLOCKED_ACCOUNT)
        return DECLINED_STOLEN_CARD;

    if(amountAvailable == LOW_BALANCE)
        return DECLINED_INSUFFECIENT_FUND;

    if(sTransaction == SAVING_FAILED)
        return INTERNAL_SERVER_ERROR;

    if(sTransaction == SERVER_OK)
        return APPROVED;
    accountsDb->balance -= transData->terminalData.transAmount;
    return APPROVED;
}
void recieveTransactionDataTest(void){

    char * cases[] ={"Case 1 : Amount is not available ...",
                     "Case 2 : The account is blocked  ...",
                     "Case 3 : Approved Transaction  ...",
                     "Case 3 : Account not exist  ...",
    };

    ST_terminalData_t terminal ={2000,15000,"24/10/2022"};
    EN_transState_t receiveTransaction;
    ST_cardData_t card[]={
            {"ahmad hassan adelwahed", "8989374615436851", "12/22"},
            {"hesham elsayied jaafer", "5807007076043875", "12/22"},
            {"mohamed hussein mohamed", "5594444608764305", "12/22"},
            {"mamdouh hassan mohamed", "5807007076043874", "12/22"},

    };

    printf("Tester Name: Mohamed Hussein \n");
    printf("Function Name: receiveTransactionData\n");
    printf("--------------------------------\n");

        int i ;
    for ( i = 0; i < 4; ++i) {
        transaction->cardHolderData = card[i];
        transaction->terminalData = terminal;
        receiveTransaction = receiveTransactionData(transaction);

        printf("%s \n",cases[i]);
        printf("Input Data : %s\n",card[i].primaryAccountNumber);

        switch (i) {
            case 0:
                printf("Expected Result: 1 \n");
                printf("Actual Result  : %d \n",receiveTransaction);
                printf("--------------------------------\n");
                break;
            case 1:
                printf("Expected Result: 2 \n");
                printf("Actual Result  : %d \n",receiveTransaction);
                printf("--------------------------------\n");
                break;
            case 2:
                printf("Expected Result: 0 \n");
                printf("Actual Result  : %d \n",receiveTransaction);
                printf("--------------------------------\n");
                break;
            case 3:
                printf("Expected Result: 3 \n");
                printf("Actual Result  : %d \n",receiveTransaction);
                printf("--------------------------------\n");
                break;
            default:
                break;
        }


    }

    }





/**
 * This function will take card data and validate if the account related to this card exists or not.
It checks if the PAN exists or not in the server's database (searches for the card PAN in the DB).
If the PAN doesn't exist will return ACCOUNT_NOT_FOUND and the account reference will be NULL, else will return SERVER_OK and return a reference to this account in the DB.
 * */
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountReference){
    int res;
    int i = 0;
    for ( i = 0; i < 3; ++i) {
        res = strcmp(cardData->primaryAccountNumber , accountReference[i].primaryAccountNumber);
        if(res == 0)
            break;
    }
    if( res == 0){
        *accountReference =accountReference[i];
        return SERVER_OK;
    } else
    {
        accountReference = NULL;
        return ACCOUNT_NOT_FOUND;
    }
}
void isValidAccountTest(void){
    // 2 cases -> 1- account does not exist . 2 - account is exist
    char * cases[2] ={
            "Case 1 : Account doesn't exist ...",
            "Case 2 : Account Exist ..."
    };

    EN_serverError_t serverError ;
    ST_cardData_t  cardData[2] ;

    printf("Tester Name: Mohamed Hussein \n");
    printf("Function Name: isValidAccount\n");
    printf("--------------------------------\n");

    for (int i = 0; i < 2; ++i) {
        printf("%s \n",cases[i]);

        //        8989374615436851  -- exist number
        // input exist number last
        printf("Input Data : ");
        readLine(cardData[i].primaryAccountNumber);

        serverError = isValidAccount(&cardData[i],accountsDb);

        if(i != 1){
            printf("Expected Result: 3 \n");
            printf("Actual Result: %d \n",serverError);
        }
        else{
            printf("Expected Result: 0 \n");
            printf("Actual Result: %d \n",serverError);
        }
        printf("--------------------------------\n");
    }


}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference){

    if(accountReference->state == RUNNING)
        return SERVER_OK ;
    else if (accountReference->state == BLOCKED)
        return BLOCKED_ACCOUNT;
}
void isBlockedAccountTest(void){
    char * cases[2] ={
            "Case 1          : Account is Running ...",
            "Case 2          : Account is Bocked ..."
    };

//    {1000, RUNNING, "8989374615436851"},
//    {3500, BLOCKED,  "5807007076043875"},
//    {45000, RUNNING, "5594444608764305"},

    EN_serverError_t serverError ;
    ST_cardData_t  cardData[2] ;

    printf("Tester Name  : Mohamed Hussein \n");
    printf("Function Name: isBlockedAccount\n");
    printf("--------------------------------\n");

    for (int i = 0; i < 2; ++i) {
        printf("%s \n",cases[i]);


        *accountsDb = accountsDb[i];
            printf("Input Data      : %s \n",accountsDb[i].primaryAccountNumber);

        serverError = isBlockedAccount(accountsDb);

        if(i != 1){
            printf("Expected Result : 0 \n");
            printf("Actual Result   : %d \n",serverError);
        }
        else{
            printf("Expected Result : 5 \n");
            printf("Actual Result   : %d \n",serverError);
        }
        printf("--------------------------------\n");
    }

}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountReference){
    if(termData->transAmount > accountReference->balance)
        return LOW_BALANCE;
    else return SERVER_OK;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){
    transData->transactionSequenceNumber = sequenceIndicate;
    int len = strlen(transaction);
    if(transData->transactionSequenceNumber < 255){
        transaction[len].transactionSequenceNumber = transData->transactionSequenceNumber+1;
        strcpy(transaction[transData->transactionSequenceNumber].cardHolderData.cardHolderName ,transData->cardHolderData.cardHolderName);
        strcpy(transaction[transData->transactionSequenceNumber].cardHolderData.cardExpirationDate ,transData->cardHolderData.cardExpirationDate);
        strcpy(transaction[transData->transactionSequenceNumber].cardHolderData.primaryAccountNumber ,transData->cardHolderData.primaryAccountNumber);



        sequenceIndicate ++;

    }

    return SERVER_OK;
}

void listSavedTransactions(void){

    for (int i = 0; i < sequenceIndicate; ++i) {
//        printf("\n%d",transaction[i].transactionSequenceNumber);
////        printf("\n%s",transaction[i].terminalData);
////        printf("\n%f",transaction[i].terminalData.transAmount);
////        printf("\n%f",transaction[i].terminalData.maxTransAmount);
        printf("##########--- Transaction Report ---###########");
        printf("\n# SEQUENCE N   : %d ",transaction[i].transactionSequenceNumber );
        printf("\n# HOLDER NAME  : %s ", transaction[i].cardHolderData.cardHolderName);
        printf("\n# EXPIRY DATE  : %s ",transaction[i].cardHolderData.cardExpirationDate);
        printf("\n# PAN          : %s ",transaction[i].cardHolderData.primaryAccountNumber);
////        printf("\n%s",transaction[i].cardHolderData.cardExpirationDate);
        printf("\n##########---- End ----###########");

    }
}