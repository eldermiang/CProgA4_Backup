#include<stdio.h>
#include <stdlib.h>
#include "a3.h"
/* Rhys Ly*/

    FILE *fp1, *fp2;
    char ch;


/*******************************************************************************
 *This function prints the encryption options showing what the program can do.
 *inputs:
 *- none
 *outputs:
 *- none
 *******************************************************************************/
void printEncryptionMenu() {
    printf("\nEncryption Options\n"
           "1. Encrypt with Caeser Cipher\n"
           "2. Decrypt with Caeser Cipher\n"
           "3. Return to Main Menu\n"
           "Enter a number of your choice>");
}

/*******************************************************************************
 *This function runs the encryption options and handels the users choice.
 *inputs:
 *- none
 *outputs:
 *- none
 *******************************************************************************/
void runEncryptionMenu() {
    int choice = 0;
    while (choice != 3) {
        printEncryptionMenu();
        if (scanf("%d", &choice) != 1) {
            while(fgetc(stdin) != '\n'); /* Eliminate overflow */
            printf("Invalid input, please enter a number.\n");
        }
        else {
            switch(choice) {
                case 1: 
                    printf("Encrypting...\n");
                    databaseEncryption();
                    break;
                case 2:
                    printf("Decrypting...\n");
                    databaseDecryption();
                    break;
                case 3:
                    break;
                default:
                    printf("Invalid choice.\n");
            }
        }
    }
}


/*******************************************************************************
 *This function encrypts the database file containing the customer information
 *using our own style of the ceaser cipher algorithm.
 *inputs:
 *- none
 *outputs:
 *- none
 *******************************************************************************/

int databaseEncryption(){
    /*opens the customer_database file to be read*/
    fp1 = fopen("customer_database","r");
    if(fp1 == NULL)
    {
        printf("Something went wrong!\n");
    }
    /*opens the encrypted_database file to write*/
    fp2 = fopen("encrypted_database","w");
    if(fp2 == NULL)
    {
        printf("Something went wrong!\n");
    }
    while(1) /*while the function is running*/
    {
        /*get char from customer database*/
        ch = fgetc(fp1); 
        if(ch == EOF)
        {
            /* stops getting char if the char */
            /* reaches the end of file*/
            break;
        }
        else
        {
            /*assigns the the ASCII value to the char*/
            /* its shifts in the negative direction */
            ch = ch - (8 * 5 - 3);
            /*puts the char into the encrypted_database file*/
            fputc(ch, fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}

int databaseDecryption(){
    /*opens the encrypted_database file to be read*/
    fp1 = fopen("encrypted_database","r");
    if(fp1 == NULL)
    {
        printf("Something went wrong!\n");
    }
    /*opens the decrypted_database file to write*/
    fp2 = fopen("decrypted_database","w");
    if(fp2 == NULL)
    {
        printf("Something went wrong!\n");
    }
    while(1)/*while the function is running*/
    {
        /*get char from customer database*/
        ch = fgetc(fp1);
        if(ch == EOF)
        {
            /* stops getting char if the char */
            /* reaches the end of file*/
            break;
        }
        else
        {
            /*assigns the the ASCII value to the char*/
            /* its shifts in the positive direction */
            ch = ch + (8 * 5 - 3);
            /*puts the char into the encrypted_database file*/
            fputc(ch, fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}
