//
// Created by server on 10/21/22.
//
#include <stdio.h>
void readLine(char *dist){
    int input;
    int index = 0;
    while ((input=getchar()) != '\n'){
        dist[index]= input;
        index++;
    }
}