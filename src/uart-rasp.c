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
#include "uart.h"

int main(){

   openUart("/dev/serial0");

   struct termios commOptions;
   setCommunicationOptions(&commOptions);

   sendString("Eu sou eu", 9);

   return 0;
} // end of main
