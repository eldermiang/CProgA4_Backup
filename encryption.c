#include<stdio.h> /*  fgetc, scanf, printf, fopen, fputc, fclose*/
#include "a3.h"
/* Rhys Ly*/

    FILE *inputFile, *outputFile;/* input file and output file*/
    char ch; /* characer for shifting in encryption algorithm*/
    int k1, k2, k3;/* key 1 key 2 and key 3 */


/*******************************************************************************
 *This function prints the encryption options showing what the program can do.
 *inputs:
 *- none
 *outputs:
 *- none
 *******************************************************************************/
void printEncryptionMenu() {
    printf("\n*********************************************************"
           "\nEncryption Options\n"
           "1. Encrypt with Caeser Cipher\n"
           "2. Decrypt with Caeser Cipher\n"
           "3. Return to Main Menu\n"
           "*********************************************************\n"
           "Enter a number of your choice>");
}

/*******************************************************************************
 *This function runs the encryption options and handles the users choice.
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
 *This function gets the encryption key to encrypt and decrypt the database.
 *inputs:
 *- none
 *outputs:
 *- none
 *******************************************************************************/

void getKey(){
    printf("Enter 3 Number Key seperated by spaces>\n");
    scanf("%d %d %d", &k1, &k2, &k3);
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
    getKey();
    /*opens the customer_database file to be read*/
    inputFile = fopen("customer_database","r");
    if(inputFile == NULL)
    {
        printf("Something went wrong!\n");
        return 1;
    }
    /*opens the encrypted_database file to write*/
    outputFile = fopen("encrypted_database","w");
    if(outputFile == NULL)
    {
        printf("Something went wrong!\n");
    }
    while(1) /*while the function is running*/
    {
        /*get char from customer database*/
        ch = fgetc(inputFile); 
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
            ch = ch - (k1 * k2 - k3);
            /*puts the char into the encrypted_database file*/
            fputc(ch, outputFile);
        }
    }
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

int databaseDecryption(){
    getKey();
    /*opens the encrypted_database file to be read*/
    inputFile = fopen("encrypted_database","r");
    if(inputFile == NULL)
    {
        printf("Something went wrong!\n");
        return 1;
    }
    /*opens the decrypted_database file to write*/
    outputFile = fopen("decrypted_database","w");
    if(outputFile == NULL)
    {
        printf("Something went wrong!\n");
    }
    while(1)/*while the function is running*/
    {
        /*get char from customer database*/
        ch = fgetc(inputFile);
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
            ch = ch + (k1 * k2 - k3);
            /*puts the char into the encrypted_database file*/
            fputc(ch, outputFile);
        }
    }
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

/* Generates a 6 digit key for encryption and decryption */
/*
char* generateKey() {
    char* key[7];
    char segment;
    segment = (rand() % 26);
    return key;
}
*/
