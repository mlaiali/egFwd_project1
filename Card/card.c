//
// Created by server on 10/20/22.
//
#include <stdio.h>
#include "card.h"
#include <string.h>
#include "../util/utiliti.h"
#include <ctype.h>
#include "stdlib.h"


#define MAX_HOLDER_NAME 25
#define MIN_HOLDER_NAME 20
#define EXP_DATE_LEN 6
#define MAX_EXP_DATE 5
#define CARD_PAN_LEN 20
#define MAX_CARD_PAN 19
#define MIN_CARD_PAN 16

EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
    printf("\nENTER HOLDER NAME : ");

    int numberCharEntered = 0;
    short  lettersLength=0 ;
    scanl(cardData->cardHolderName , MAX_HOLDER_NAME , &numberCharEntered);
    for (int i = 0; i < MAX_HOLDER_NAME; ++i) {
        if(isalpha(cardData->cardHolderName[i]))
            lettersLength++;
    }
    if(lettersLength >=MIN_HOLDER_NAME && lettersLength <MAX_HOLDER_NAME && numberCharEntered < MAX_HOLDER_NAME)
    {
        return CARD_OK;
    }
    else
    {
        return WRONG_NAME;
    }
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){

    printf("\nEnter Expiry Date (MM/YY) : ");
    int  month =0, year =0 ,numberCharEntered;

    scanl((char *)cardData->cardExpirationDate , EXP_DATE_LEN , &numberCharEntered);
    if (cardData->cardExpirationDate[2] == '/' && numberCharEntered == MAX_EXP_DATE) {
        for (int i = 0; i < EXP_DATE_LEN-1; ++i) {
            if(i == 2)
                i=3;
            if(!(isdigit(cardData->cardExpirationDate[i])))
                return WRONG_EXP_DATE;
        }

        month = ((cardData->cardExpirationDate[0] - '0') * 10 )+ (cardData->cardExpirationDate[1] - '0');
        month = month > 12 ? 0 : month <= 0 ? 0 : 1;
        year = ((cardData->cardExpirationDate[3] - '0') * 10) + (cardData->cardExpirationDate[4] - '0');
        year = year <=0 ? 0 : 1;
    }
    if (month && year)
        return CARD_OK;
    else
        return WRONG_EXP_DATE;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){
//    printf("\nEnter Primary Account Number : ");
    int length;
    scanl((char *)cardData->primaryAccountNumber , CARD_PAN_LEN ,&length);
    if (length >= MIN_CARD_PAN && length <= MAX_CARD_PAN){
        for (int i = 0; i < length; ++i) {
            if(!isdigit(cardData->primaryAccountNumber[i]))
                return WRONG_PAN;
        }
        return CARD_OK;
    }
    else
        return WRONG_PAN;
}


