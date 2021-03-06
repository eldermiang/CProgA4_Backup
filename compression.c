#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a3.h"

/* Kenny */
/*******************************************************************************
 *This function prints the menu with options to compress and decompress
 *inputs:
 *- none
 *outputs:
 *- none
 *******************************************************************************/
void printCompressMenu() {
    printf("\n*********************************************************"
           "\nCompression Options\n"
           "1. Compress exported database with Run-Length-Encoding\n"
           "2. Decompress exported database with Run-Length-Decoding\n"
           "3. Return to Main Menu\n"
           "*********************************************************\n"
          );
}

/* Kenny */
/*******************************************************************************
 *This function runs the menu and calls functions depending on the user choice
 *inputs:
 *- none
 *outputs:
 *- none
 *******************************************************************************/
void runCompressMenu() {

    int choice = 0;
    
    while (choice != 3) {

        printCompressMenu();
        printf("Enter a number of your choice>");

        if(scanf("%d", &choice) != 1) {
            while(fgetc(stdin) != '\n'); /* Eliminate overflow */
            printf("Invalid input, please enter a number.\n");
        }
        else {
            switch (choice) {
                case 1 :
                char * string = readDatabase();
                #ifdef DEBUG
                    printf("*****Database Text****\n");
                    printf("%s\n", string);
                #endif
                run_length_encode(string);
                break;

                case 2 :
                run_length_decode();
                break;

                case 3 :
                break;

                default :
                printf("Invalid choice.\n");
            }
        }
    }
}

/* Kenny */
/*******************************************************************************
 *This function reads the customer database and returns it as a string
 *inputs:
 *- none
 *outputs:
 *- string_db
 *******************************************************************************/
char* readDatabase() {
    char * string_db;
    int fileSize = 0;
    char ch;

    FILE * database;

    database = fopen("customer_database", "r");
    if (database == NULL) {
        printf("Read error\n");
        /*free(string_db);*/
        return "1";
    }
    
    /* Get length of a file */
    fseek(database, 0, SEEK_END);
    fileSize = ftell(database);
    rewind(database);

    char buffer[fileSize+1];
    /* Read through database by chars and append to buffer */
    while((ch = fgetc(database)) != EOF) {
        strncat(buffer, &ch, 1);
    }
    /* Copy buffer to string_db */
    string_db = (char*) malloc(strlen(buffer) * sizeof(char*));
    strcpy(string_db, buffer);

    fclose(database);
    
    return string_db;
}

/* Kenny */
/*******************************************************************************
 *This function gets a string and prints the encoded string into a FILE
 *inputs:
 *- string
 *outputs:
 *- none
 *******************************************************************************/
void run_length_encode(char* string) {
    int char_count;
    int x;
    int length = strlen(string);
    char run_count[length];
    char encoded_text[length];
    char token = '.';

    if(strlen(string) <= 1) {
        return;
    }

    FILE * new_database, * database;

    /* Iterate through input text */
    for (x = 0; x < length; x++) {
        
        /* A counter for duplicates of characters */
        char_count = 1;
    /*While the character at the current index is the same at the next index*/
        while (x + 1 < length && string[x] == string[x + 1]) {
            char_count++;
            x++;
        }
        /* Append the count, token and character to the "encoded text" */
        if (char_count > 1 && (string[x] >= '0' && string[x] <= '9')) {
            sprintf(run_count, "%d%c%c", char_count, token, string[x]);
        }
        /* Append the count and character to the "encoded text" */
        else if (char_count > 1 && !(string[x] >= '0' && string[x] <= '9')) {
            sprintf(run_count, "%d%c", char_count, string[x]);
        }
        else {
            sprintf(run_count, "%c", string[x]);
        }
        strncat(encoded_text, run_count, length);
    }
    
    #ifdef DEBUG
        printf("*****Encoded Text****\n");
        printf("%s\n", encoded_text);       
    #endif

    new_database = fopen("compressed_database", "w");
    database = fopen("customer_database", "r");
    
    if (new_database == NULL || database == NULL) {
        printf("Read error");
    }
    /* Writing encoded_text to new_database */
    else {
        fprintf(new_database, "%s", encoded_text);
    }

    fseek(database, 0L, SEEK_END);
    long int db_size = ftell(database);
    fseek(new_database, 0L, SEEK_END);
    long int cdb_size = ftell(new_database);

    fclose(new_database);
    fclose(database);

    printf("\n");
    printf("Original database size: %ld bytes\n", db_size);
    printf("Compressed database size: %ld bytes\n", cdb_size);
    printf("\n");

    printf("Run-length encoding successful!\n");
}


/*******************************************************************************
 *This function decompresses the previously encoded text and stores in a new 
 *database file.
 *inputs:
 *- none
 *outputs:
 *- none
 *******************************************************************************/
void run_length_decode() {
    char ch;
    FILE * db, *new_db;
    
    db = fopen("compressed_database", "r");

    if (db == NULL) {
        printf("Read error\n");
        return;
    }

    new_db = fopen("decompressed_database", "w");

    while ((ch = fgetc(db)) != EOF) {
        /* Is number */
        if (ch >= 48 && ch <= 57) {
            int noRepeats = ch - 48;
            /* Peek at next char then move back */
            char next = fgetc(db);
            ungetc(next, db);
            int i = 0;
            /* Is letter */
            if (next >= 97 && next <= 122) {
                while (i < noRepeats) {
                    fprintf(new_db, "%c", next);
                    i++;
                }
                /* Set ch to char after next char */
                fgetc(db);
                ch = fgetc(db);
            }
            /* Is token */
            else if (next == '.') {
                fgetc(db);
                /* get char after next */
                char nextNext = fgetc(db);
                while (i < noRepeats) {
                    fprintf(new_db, "%c", nextNext);
                    i++;
                }
                /* Set ch to char after nextNext char */
                ch = fgetc(db);
            }
        }
        fprintf(new_db, "%c", ch);
    }
    fclose(db);
    fclose(new_db);

    printf("Run-length decoding successful!\n");
}
