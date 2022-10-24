//
// Created by server on 10/21/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits/stdint-uintn.h>

void readLine(char *dist){
    int input;
    int index = 0;
    while ((input=getchar()) != '\n'){
        dist[index]= input;
        index++;
    }
}

void scanl (char *dis,int size ,int *charCount){
    int read;
    int index = 0;
    char src[size];
    char *temp = malloc(size * sizeof (char ));
    while ((read=getchar()) != '\n' ){
        temp[index]= read;
        index++;
    }

    for (int i = 0; i < size-1; ++i) {
        src[i] = temp[i];
    }

    strcpy(dis,src);
    *charCount = index;
    free(temp);
}


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