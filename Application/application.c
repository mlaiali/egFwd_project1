//
// Created by server on 10/21/22.
//

#include "application.h"
#define appStart main
//
//ST_cardData_t stCardData;
//ST_terminalData_t stTerminalData;
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
    cardExpDate = getCardExpiryDate(cardData);
    cardPAN = getCardPAN(cardData);

    if(cardHolderName == WRONG_NAME){
        printf("\nWRONG NAME ..!");
        exit(0);
    }

    if(cardExpDate == WRONG_EXP_DATE){
        printf("\nWRONG EXPIRY DATE ..!");
        exit(0);
    }

    if(cardPAN == WRONG_PAN){
        printf("\nWRONG PAN ..!");
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
    maxAmount = setMaxAmount(termData, 15000);
    belowMaxAmount = isBelowMaxAmount(termData);

    validCardPAN = isValidCardPAN(cardData);

    if (transactionDate == WRONG_DATE){
        printf("\nFAILED TO READ LOCAL DATE ...!");
        exit(0);
    }

    if (cardExpired == EXPIRED_CARD){
        printf("\nEXPIRED CARD ... !");
        exit(0);
    }

    if (transactionAmount == INVALID_AMOUNT){
        printf("\nINVALID AMOUNT ...!");
        exit(0);
    }

    if (belowMaxAmount == EXCEED_MAX_AMOUNT){
        printf("\nEXCEED MAX AMOUNT ...!");
        exit(0);
    }

    if(maxAmount == INVALID_MAX_AMOUNT){
        printf("\nINVALID MAX AMOUNT ..,!");
        exit(0);
    }

    if (validCardPAN == INVALID_CARD){
        printf("\nINVALID CARD PAN ...!");
        exit(0);
    }


    /// transactions err flag

    EN_transState_t receiveTransaction ;

    ///transaction data struct
    ST_transaction_t stTransaction;
    ST_transaction_t *transaction = &stTransaction;

    ///server module ;get card data and terminal data
    transaction->cardHolderData = cardHolderData;
    transaction->terminalData = terminalData;

    receiveTransaction = receiveTransactionData(transaction);
    //APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
    switch (receiveTransaction) {
        case APPROVED:
            printf("\nsuccessful transaction .");
            break;
        case DECLINED_INSUFFECIENT_FUND:
            printf("\ndecline transaction , insufficient fund");
            break;
        case DECLINED_STOLEN_CARD:
            printf("\ndecline transaction , this card is stolen");
            break;
        case FRAUD_CARD:
            printf("\nAccount not found ");
            break;
        case INTERNAL_SERVER_ERROR:
            printf("\nsaving failed");
        default:
            break;


    }
    printf("\n");
    listSavedTransactions();

}
