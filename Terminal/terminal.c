//
// Created by server on 10/21/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "time.h"
#include "terminal.h"
#include "ctype.h"
#include "../util/utiliti.h"
//#define isValidCardPANTest main

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    time_t T = time(NULL);
    struct tm tm = *localtime(&T);
    /** get local date and store it in terminal date transaction with format (DD/MM/YYYY) */
    snprintf((char *)termData->transactionDate,11,"%02d/%02d/%04d",tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
    short length = (short )strlen((char *)termData->transactionDate);
    if(length > 0 && length < 11)

        return TERMINAL_OK;
    else
        return WRONG_DATE;

}
void getTransactionDateTest(void){
    ST_terminalData_t terminalData;
    EN_terminalError_t terminalError;
    terminalError = getTransactionDate(&terminalData);
    printf("Tester Name: Mohamed Hussein Mohamed\n");
    printf("Function Name: getTransactionDate\n");
    printf("-------------------------------------\n");
    printf("Test Case      : The function read the current date from current local machine .\n");
    printf("Input Data     : read from local machine .\n");
    printf("Expected Result: 0 .\n");
    printf("Actual Result  : %d.\n",terminalError);

}


EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){

    int terminalMonth =0 , terminalYear =0 , cardMonth =0 , cardYear =0;

    getDate(cardData->cardExpirationDate, &cardMonth, &cardYear);
    getDate(termData->transactionDate, &terminalMonth, &terminalYear);

    printf("terminal month %d , term year %d , card month %d , card year %d . \n",terminalMonth , terminalYear , cardMonth , cardYear);
    if(terminalYear == cardYear && terminalMonth <= cardMonth || terminalYear < cardYear )
        return TERMINAL_OK;
    else
        return EXPIRED_CARD;
}
void isCardExpriedTest(void){

    ST_terminalData_t terminalData ;

    EN_terminalError_t getTransaction_d;
    getTransaction_d = getTransactionDate(&terminalData);

    EN_terminalError_t isExp;

    ST_cardData_t cardData[1];

    strcpy(cardData[0].cardExpirationDate , "08/22");
    strcpy(cardData[1].cardExpirationDate , "12/22");

    char *cases[2] = {"Case 1 : Expired card ...",
                      "Case 2 : Valid card .."};

    printf("Tester Name: Mohamed Hussein \n");
    printf("Function Name: isCardExpired\n");
    printf("--------------------------------\n");

    for (int i = 0; i < 2; ++i) {
        printf("%s \n",cases[i]);
        printf("Input Data : %s\n",cardData[i].cardExpirationDate);
        isExp = isCardExpired(&cardData[i],&terminalData);
        if(i==0){
            printf("Expected Result : 2\n");
            printf("Actual Result   : %d\n",isExp);
        }else
        {
            printf("Expected Result : 0\n");
            printf("Actual Result   : %d\n",isExp);
        }
        printf("--------------------------------\n");
    }


}


EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    char val[8] ;
//    printf("\nENTER WITHDRAW AMOUNT : " );
    readLine(val);
    termData->transAmount = atof(val);
    if(termData->transAmount <= 0 )
        return INVALID_AMOUNT;
    else
        return TERMINAL_OK;
}
void getTransactionAmountTest(void){

    ST_terminalData_t terminalData ;
    EN_terminalError_t terminalError;
    char *cases[2] = {"Case 1 : Amount less than or equal to zero  ...",
                      "Case 3 : Amount more than zero ..."};

    printf("Tester Name: Mohamed Hussein \n");
    printf("Function Name: getTransactionAmount\n");
    printf("--------------------------------\n");

    for (int i = 0; i < 2; ++i) {
        printf("%s \n",cases[i]);
        printf("Input Data : ");
        terminalError = getTransactionAmount(&terminalData);
        if(i != 1){
            printf("Expected Result: 4 \n");
            printf("Actual Result: %d \n",terminalError);
        }
        else{
            printf("Expected Result: 0 \n");
            printf("Actual Result: %d \n",terminalError);
        }
    }


}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
     if(termData->transAmount > termData->maxTransAmount)
         return EXCEED_MAX_AMOUNT;
     else
         return TERMINAL_OK;
}
void isBelowMaxAmountTest(void){
    ST_terminalData_t terminalData ;
    EN_terminalError_t terminalError;
    EN_terminalError_t gettransactionamount;

    setMaxAmount(&terminalData , 15000);

    char *cases[2] = {"Case 1 : Exceeded Max Amount (More than 15000 as max amount) ...",
                      "Case 2 : Amount less than max amount (15000) ...",
                      };

    printf("Tester Name: Mohamed Hussein \n");
    printf("Function Name: isBelowMaxAmount\n");
    printf("--------------------------------\n");

    for (int i = 0; i < 2; ++i) {
        printf("%s \n",cases[i]);
        printf("Input Data : ");
        gettransactionamount = getTransactionAmount(&terminalData);
        terminalError = isBelowMaxAmount(&terminalData);
        if(i != 1){
            printf("Expected Result: 5 \n");
            printf("Actual Result: %d \n",terminalError);
        }
        else{
            printf("Expected Result: 0 \n");
            printf("Actual Result: %d \n",terminalError);
        }
    }


}


EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount){
    termData->maxTransAmount = maxAmount;
    if(maxAmount <= 0 )
        return INVALID_MAX_AMOUNT;
    else
        return TERMINAL_OK;
}
void setMaxAmountTest(void){
    ST_cardData_t  cardData;
    EN_terminalError_t terminalError;
    float maxAm;

    char *cases[2] = {"Case 1 : Set max amount less than or equal to zero ...",
                      "Case 2 : Set max amount more than zero ...",
    };
    printf("Tester Name: Mohamed Hussein \n");
    printf("Function Name: setMaxAmount\n");
    printf("--------------------------------\n");

    for (int i = 0; i < 2; ++i) {
        printf("%s \n",cases[i]);
        printf("Input Data : ");
        scanf("%f",&maxAm);
        terminalError = setMaxAmount(&cardData,maxAm);
        if(i != 1){
            printf("Expected Result: 6 \n");
            printf("Actual Result: %d \n",terminalError);
        }
        else{
            printf("Expected Result: 0 \n");
            printf("Actual Result: %d \n",terminalError);
        }
    }


}

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){
    int temp =0, luhnNumber =0;
    bool isNext = false;
    short length = (short) strlen((char *) cardData->primaryAccountNumber);
    short ind = 0;
    while (ind <length){

        if(!isdigit(cardData->primaryAccountNumber[ind]))
            return INVALID_CARD;
        ind++;
    }
    if (length >= 16 && length <= 19) {
        for (int i = length - 1; i >= 0; --i) {
            temp += (cardData->primaryAccountNumber[i] - '0');
            if (isNext)
                (temp * 2) > 9 ? (temp =temp * 2 - 9) : (temp =temp* 2);
            luhnNumber += temp;
            isNext = !isNext;
            temp = 0;
        }
        if(luhnNumber %10 ==0)
            return TERMINAL_OK;
        else
            return INVALID_CARD;
    }

}

void isValidCardPANTest(void){
    EN_terminalError_t terminalError;
    ST_cardData_t cardData[2];
    strcpy(cardData[0].primaryAccountNumber,"8989374615436851");
    strcpy(cardData[1].primaryAccountNumber,"8989374615436820");

    char *cases[2] = {"Case 1 : The PAN is luhn number ...",
                      "Case 2 : The PAN is not luhn number ...",
    };

    printf("Tester Name: Mohamed Hussein \n");
    printf("Function Name: isValidCardPAN\n");
    printf("--------------------------------\n");


    for (int i = 0; i < 2; ++i) {
        printf("%s \n",cases[i]);
        printf("Input Data : %s\n",cardData[i].primaryAccountNumber);

        terminalError = isValidCardPAN(&cardData[i]);

        if(i != 0){
            printf("Expected Result: 3 \n");
            printf("Actual Result: %d \n",terminalError);
        }
        else{
            printf("Expected Result: 0 \n");
            printf("Actual Result: %d \n",terminalError);
        }
        printf("--------------------------------\n");
    }




}