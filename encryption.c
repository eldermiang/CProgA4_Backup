#include<stdio.h> /*  fgetc, scanf, printf, fopen, fputc, fclose*/
#include "a3.h"
/* Rhys Ly*/

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
           "1. Encrypt exported database with Caeser Cipher\n"
           "2. Decrypt exported database with Caeser Cipher\n"
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
 *- key_t key: returns the key entered by the user
 *******************************************************************************/

key_t getKey(void){
    int k1, k2, k3;
    key_t key;
    printf("Enter 3 Alphanumeric Value Key seperated by spaces>");
    scanf("%d %d %d", &k1, &k2, &k3);
    while(fgetc(stdin) != '\n'); /* Eliminate overflow */


    key.k1 = k1;
    key.k2 = k2;
    key.k3 = k3;

    #ifdef DEBUG
        printf("Encryption Key Values Entered: %d %d %d\n", k1, k2, k3);
        printf("Encryption Key Values Saved in Key: %d %d %d\n", key.k1, key.k2, key.k3);
    #endif

    return key;
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

    FILE *inputFile, *outputFile;/* input file and output file*/
    char ch; /* characer for shifting in encryption algorithm*/
    key_t key; /* encryption key */

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
    key = getKey(); /* gets key from user */
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
            ch = ch - (key.k1 * key.k2 - key.k3);

            /*puts the char into the encrypted_database file*/
            fputc(ch, outputFile);
        }
    }
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

int databaseDecryption(){

    FILE *inputFile, *outputFile;/* input file and output file*/
    char ch; /* characer for shifting in encryption algorithm*/
    key_t key; /* encryption key */
    
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
    key = getKey();
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
            ch = ch + (key.k1 * key.k2 - key.k3);

            /*puts the char into the encrypted_database file*/
            fputc(ch, outputFile);
        }
    }
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
