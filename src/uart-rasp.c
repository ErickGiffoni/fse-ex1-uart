/**
 * @file uart-rasp.c
 
 * @author Erick Giffoni (github.com/ErickGiffoni)
 * @brief C code for communication in a Raspberry 4 using UART
 * @version 0.1
 * @date 2022-02-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <termios.h>    // struct termios
#include <stdio.h>      // printf, scanf
#include <stdlib.h>     // calloc
#include "uart.h"

int main(){

   openUart("/dev/serial0");

   struct termios commOptions;
   setCommunicationOptions(&commOptions);

   char *message = (char *) calloc(255, sizeof(char));
   int read_bytes = scanf(" %s", message);

   sendString(message, read_bytes);

   return 0;
} // end of main
