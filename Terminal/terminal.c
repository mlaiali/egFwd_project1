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
void getDate(uint8_t *date , int *month , int *year){

    short length  = (short) strlen((char*)date);
    for(int i = length-1 ; i > 0 ; --i){
        if(date[i] == '/') {
            for (int j = i - 2; j < length; ++j) {
                if (j == i)
                    j = length - 2;
                if (j < i)
                    *month = (*month * 10) + (date[j] - '0');
                else
                    *year = (*year * 10) + (date[j] - '0');
            }
            return;
        }
    }
}
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

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){
    int terminalMonth =0 , terminalYear =0 , cardMonth =0 , cardYear =0;
    getDate(cardData->cardExpirationDate, &cardMonth, &cardYear);
    getDate(termData->transactionDate, &terminalMonth, &terminalYear);
    if(terminalYear == cardYear && terminalMonth <= cardMonth || terminalYear < cardYear )
        return TERMINAL_OK;
    else
        return EXPIRED_CARD;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    char val[8] ;
    printf("\nENTER WITHDRAW AMOUNT : " );
    readLine(val);
    termData->transAmount = atof(val);
    if(termData->transAmount <= 0 )
        return INVALID_AMOUNT;
    else
        return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
     if(termData->transAmount > termData->maxTransAmount)
         return EXCEED_MAX_AMOUNT;
     else
         return TERMINAL_OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount){
    termData->maxTransAmount = maxAmount;
    if(maxAmount <= 0 )
        return INVALID_MAX_AMOUNT;
    else
        return TERMINAL_OK;
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