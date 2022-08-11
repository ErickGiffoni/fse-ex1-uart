/**
 * @file uart.c
 
 * @author Erick Giffoni (github.com/ErickGiffoni)
 * @brief C module implementation for communication in a Raspberry 4 using UART
 * @version 0.1
 * @date 2022-02-10
 * 
 * Ref 1          : https://gitlab.com/fse_fga/exercicios/exercicio-1-uart
 * Ref 2 (MODBUS) : https://gitlab.com/fse_fga/exercicios/exercicio-2-uart-modbus
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "uart.h"

#include <fcntl.h>      // open
#include <stdlib.h>     // malloc
#include <unistd.h>     // write
#include <string.h>     // strncpy
#include <stdio.h>

static int uartDescriptor = -1;

void openUart(char *path){
   uartDescriptor = open(path, O_RDWR | O_NOCTTY | O_NDELAY);

   if(uartDescriptor == -1){
      printf("Error openning UART");
      exit(1);
   }

   return;
} // end of openUart

/**
 * Access UART hardware and sets its configurations
 */
void setCommunicationOptions(struct termios *commOptions){
   tcgetattr(uartDescriptor, commOptions);

   commOptions->c_cflag = B9600 | CS8 | CLOCAL | CREAD;  //<Set baud rate
   commOptions->c_iflag = IGNPAR;
   commOptions->c_oflag = 0;
   commOptions->c_lflag = 0;

   tcflush(uartDescriptor, TCIFLUSH);
   tcsetattr(uartDescriptor, TCSANOW, commOptions);

   return;
} // end of setCommunicationOptions

void sendString(char *message, int msgLength){
   int pkgLength = 2+msgLength+4;
   char *package = (char *) malloc(pkgLength * sizeof(char));

   package[0]  =  SEND_STRING_CODE;
   package[1]  =  msgLength;

   strncpy(package+2, message, msgLength);

   package[pkgLength-4] =  1;
   package[pkgLength-3] =  1;
   package[pkgLength-2] =  6;
   package[pkgLength-1] =  1;

   int numOfBytesWritten = 0;
   numOfBytesWritten = write(uartDescriptor, &package[0], pkgLength);

   return;
} // end of sendString