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

#include <fcntl.h>      // open
#include <termios.h>    // tcgetattr, struct termios...
#include <stdlib.h>     // malloc
#include <string.h>     // strncpy
#include <stdio.h>

#define SEND_STRING_CODE   0xB3

void openUart(int *descriptor, char *path);
void setCommunicationOptions(struct termios *commOptions, int *descriptor);

void sendString(char *message, int msgLength, int *descriptor);

int main(){

   int uartDescriptor = -1;
   openUart(&uartDescriptor, "/dev/serial0");

   struct termios commOptions;
   setCommunicationOptions(&commOptions, &uartDescriptor);

   sendString("Eu sou eu", 9, &uartDescriptor);

   return 0;
} // end of main

void openUart(int *descriptor, char *path){
   descriptor = open(path, O_RDWR | O_NOCTTY | O_NDELAY);

   if(*descriptor == -1){
      printf("Error openning UART");
      exit(1);
   }

   return;
} // end of openUart

void setCommunicationOptions(struct termios *commOptions, int *descriptor){
   tcgetattr(*descriptor, commOptions);

   commOptions->c_cflag = B9600 | CS8 | CLOCAL | CREAD;  //<Set baud rate
   commOptions->c_iflag = IGNPAR;
   commOptions->c_oflag = 0;
   commOptions->c_lflag = 0;

   tcflush(*descriptor, TCIFLUSH);
   tcsetattr(*descriptor, TCSANOW, commOptions);

   return;
} // end of setCommunicationOptions

void sendString(char *message, int msgLength, int *descriptor){
   int pkgLength = 2+msgLength+4;
   char *package = (char *) malloc(pkgLength * sizeof(char));

   package[0]  =  SEND_STRING_CODE;
   package[1]  =  msgLength;

   strncpy(&package+2, message, msgLength);

   package[pkgLength-4] =  1;
   package[pkgLength-3] =  1;
   package[pkgLength-2] =  6;
   package[pkgLength-1] =  1;

   int numOfBytesWritten = 0;
   numOfBytesWritten = write(*descriptor, &package[0], pkgLength);

   return;
} // end of sendString