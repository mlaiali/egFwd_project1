//
// Created by server on 10/20/22.
//
#include <stdio.h>
#include "card.h"
#include <string.h>
#include "../util/utiliti.h"
#include <ctype.h>
#include <stdbool.h>

EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
    printf("ENTER HOLDER NAME : ");
    readLine((char *)cardData->cardHolderName);
    short  lengthName = (short )strlen((char *)cardData->cardHolderName);
    short  lettersLength=0 ;
    for (int i = 0; i < lengthName; ++i) {
        if(isalpha(cardData->cardHolderName[i]))
            lettersLength++;
    }
    if(lettersLength >=20 && lettersLength <25 && lengthName <25)
        return CARD_OK;
    else
        return WRONG_NAME;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){

    printf("Enter Expiry Date (MM/YY) : ");
    readLine((char *)cardData->cardExpirationDate);
    short  length =(short ) strlen((char *)cardData->cardExpirationDate);
    int  month = 0, year = 0;
    if (length == 5 && cardData->cardExpirationDate[2] == '/') {
        month = (cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0');
        month = month > 12 ? 0 : month <= 0 ? 0 : 1;
        year = (cardData->cardExpirationDate[3] - '0') * 10 + (cardData->cardExpirationDate[4] - '0');
        year = year > 00 ? 1 : 0;
    }
    if (month && year)
        return CARD_OK;
    else
        return WRONG_EXP_DATE;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    printf("Enter Primary Account Number : ");
    readLine((char *)cardData->primaryAccountNumber);
    short length = (short) strlen((char *) cardData->primaryAccountNumber);
    if (length >= 16 && length <= 19)
        return CARD_OK;
    else
        return WRONG_PAN;
}

void appl(ST_cardData_t *cardData) {
    getCardHolderName(cardData);
    getCardExpiryDate(cardData);
    getCardPAN(cardData);
}


//    int temp =0, luhnNumber =0;
//    bool isNext = false;
//    printf("Enter Primary Account Number : ");
//    readLine((char *)cardData->primaryAccountNumber);
//    short length = (short) strlen((char *) cardData->primaryAccountNumber);
//    if (length >= 16 && length <= 19) {
//        for (int i = length - 1; i >= 0; --i) {
//            temp += (cardData->primaryAccountNumber[i] - '0');
//            if (isNext)
//                (temp * 2) > 9 ? (temp *= 2 - 9) : (temp *= 2);
//            luhnNumber += temp;
//            isNext = !isNext;
//            temp = 0;
//        }
//    }
//    if(luhnNumber %10 ==0)
//        return CARD_OK;
//    else
//        return WRONG_EXP_DATE;