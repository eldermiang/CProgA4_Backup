/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Lab 06 - Group 3: Rhys Ly (13537182), Michael Jiang (13554136)
 * Kenny Doan (13554098), Kenson Lang (13554148)
 * A brief statement on what this program does:
 * 
 * A program that takes a text as an input and can perform
 * compression, encryption or both simultaneously. It also has the 
 * functionality to decrypt text that were encrypted using the
 * program
 * 
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a3.h"

#define CUSTOMER_LIMIT 100

/*******************************************************************************
 *This is the main function and starts up the program by initialising the customers
 *list and current index then running the main menu.
 *inputs:
 *- none
 *outputs:
 *- none
 *******************************************************************************/
int main(void) {
    #ifdef DEBUG 
        printf("Starting program in debugging mode\n");
    #endif
    customer_t customers[CUSTOMER_LIMIT];
    int currIndex = 0;
    runMenu(customers, &currIndex);
	return 0;
}

/*******************************************************************************
 *This function displays the list of options available in the main menu of 
 *the program.
 *inputs:
 *- none
 *outputs:
 *- none
 *******************************************************************************/
void printMenu() {
    printf("*********************************************************\n"
           "Customer Database System\n"
           "1. Database options\n"
           "2. Encryption options\n" 
           "3. Compression options \n" 
           "4. Exit Program\n"
           "*********************************************************\n"
           "Enter a number of your choice>");
}

/*******************************************************************************
 *This function runs the main menu of the program, allowing users to select
 *an option. It also transfers the customer data from the main function to the 
 *relevant functions where required.
 *inputs:
 *- Customers list
 *- Current index in list
 *outputs:
 *- none
 *******************************************************************************/
void runMenu(customer_t* customers, int* currIndex) {
    int choice = 0;
    while (choice != 4) {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            while(fgetc(stdin) != '\n'); /* Eliminate overflow */
            printf("Invalid input, please enter a number.\n");
        }
        else {
            switch (choice) {
                case 1:  
                    runCustomerMenu(customers, currIndex);
                    break; 
                case 2:
                    runEncryptionMenu();
                    break;
                case 3:
                    runCompressMenu();
                    break;
                case 4:
                    exit(0);
                default: 
                    printf("Invalid choice.\n");
            }
        }
        printf("\n");
    }
}


