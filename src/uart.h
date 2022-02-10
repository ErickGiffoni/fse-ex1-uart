/**
 * @file uart.h
 
 * @author Erick Giffoni (github.com/ErickGiffoni)
 * @brief C module for communication in a Raspberry 4 using UART
 * @version 0.1
 * @date 2022-02-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef  UART_H
#define  UART_H

#define SEND_STRING_CODE   0xB3

void openUart(char *path);
void setCommunicationOptions(struct termios *commOptions);

void sendString(char *message, int msgLength);

#endif