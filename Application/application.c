//
// Created by server on 10/21/22.
//

#include "application.h"
#define appStart main
void appl(ST_cardData_t *cardData);
ST_cardData_t stCardData;
ST_terminalData_t stTerminalData;
void appStart(void ){
    //card error flags
    EN_cardError_t cardHolderName;
    EN_cardError_t cardExpDate;
    EN_cardError_t cardPAN;

    //card structure
    ST_cardData_t cardHolderData;
    ST_cardData_t *cardData = & cardHolderData;


    //card module
    cardHolderName = getCardHolderName(cardData);
    cardExpDate = getCardPAN(cardData);
    cardPAN = getCardPAN(cardData);

    if(cardHolderName == WRONG_NAME){
        printf("WRONG NAME ..!");
        exit(0);
    }

    if(cardExpDate == WRONG_EXP_DATE){
        printf("WRONG EXPIRY DATE ..!");
        exit(0);
    }

    if(cardPAN == WRONG_PAN){
        printf("WRONG PAN ..!");
        exit(0);
    }

    // --------------------//
    // terminal err flags

    EN_terminalError_t transactionDate;
    EN_terminalError_t cardExpired;
    EN_terminalError_t transactionAmount;
    EN_terminalError_t belowMaxAmount;
    EN_terminalError_t maxAmount;
    EN_terminalError_t validCardPAN;

    // terminal data struct
    ST_terminalData_t  terminalData ;
    ST_terminalData_t  *termData = &terminalData;


    //terminal module

    transactionDate = getTransactionDate(termData);
    cardExpired = isCardExpired(cardData,termData);
    transactionAmount = getTransactionAmount(termData);
    belowMaxAmount = isBelowMaxAmount(termData);
    maxAmount = setMaxAmount(termData, 15000);
    validCardPAN = isValidCardPAN(cardData);

    if (transactionDate == WRONG_DATE){
        printf("FAILED TO READ LOCAL DATE ...!");
        exit(0);
    }

    if (cardExpired == EXPIRED_CARD){
        printf("EXPIRED CARD ... !");
        exit(0);
    }

    if (transactionAmount == INVALID_AMOUNT){
        printf("INVALID AMOUNT ...!");
        exit(0);
    }

    if (belowMaxAmount == EXCEED_MAX_AMOUNT){
        printf("EXCEED MAX AMOUNT ...!");
        exit(0);
    }

    if(maxAmount == INVALID_MAX_AMOUNT){
        printf("INVALID MAX AMOUNT ..,!");
        exit(0);
    }

    if (validCardPAN == INVALID_CARD){
        printf("INVALID CARD PAN ...!");
        exit(0);
    }


    /// transactions err flag

    EN_transState_t receiveTransaction ;

    ///transaction data struct
    ST_transaction_t stTransaction;
    ST_transaction_t *transaction = &stTransaction;

    ///server module ;
    transaction->cardHolderData = cardHolderData;

}