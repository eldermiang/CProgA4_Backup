#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a3.h"

#define DEBUG

/* Kenny */
void printCompressMenu() {
    printf("\nCompression Options\n"
           "1. Compress database with Run-Length-Encoding\n"
           "2. Decompress database with Run-Length-Decoding\n"
           "3. Return to Main Menu\n"
          );
}

/* Kenny */
void runCompressMenu() {

    int choice = 0;
    char * string = readDatabase();
  
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
                run_length_encode(string);
                break;

                case 2 :
                /*run_length_decode(string);*/
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
char* readDatabase() {
    
    char * string_db;
    char buffer[500];
    char ch;

    FILE * database;

    database = fopen("customer_database", "r");
    if (database == NULL) {
        printf("Read error");
    }
    
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
void run_length_encode(char* string) {
   
    /* Run-length Encoding */
    int char_count;
    int x;
    int length = strlen(string);
    char run_count[length];
    char encoded_text[500];
    char token = '.';

    FILE * new_database;

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
        /* Append the countand character to the "encoded text" */
        else if (char_count > 1 && !(string[x] >= '0' && string[x] <= '9')) {
            sprintf(run_count, "%d%c", char_count, string[x]);
        }
        else {
            sprintf(run_count, "%c", string[x]);
        }
        strncat(encoded_text, run_count, 100);
    }
    /* Writing encoded_text to new_database */
     new_database = fopen("compressed_database", "w");
    
    if (new_database == NULL) {
        printf("Read error");
    }
    else {
        fprintf(new_database, "%s", encoded_text);
     }
    fclose(new_database);
    printf("Run-length encoding successful!\n");
}

/* Kenson */

void run_length_decode(char* string) {
    
    char ch;
    FILE * db, *new_db;
  

    db = fopen("compressed_database", "r");
    new_db = fopen("decompressed_database", "w");

    if (db == NULL || new_db == NULL) {
        printf("Read error");
    }
    
    ch = fgetc(db);
    while ( ch != EOF) {
       
       if ( ch >= '0' && ch <= '9' ) {
           
       }

       else {
           fscanf(new_db, "%c", ch);
       }
       ch = fgetc(db);
    }
    

    fclose(db);
    fclose(new_db);
   
}




