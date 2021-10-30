/* File for the customer database related functionality */
/* Imports */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a3.h"

/* Definitions */
#define NAME_LIMIT 40
#define CUSTOMER_LIMIT 100

/* 
* Issues
* - Random bug where stack smashing occurs after overflowing cardNo 
*   even though the values stored are changed
*/

/* Michael */
/*******************************************************************************
 *This functions displays the options available within the database menu. 
 *inputs:
 *- none
 *outputs:
 *- none
 *******************************************************************************/
void printCustomerMenu() {
    printf("\n*********************************************************\n"
           "Database Options\n"
           "1. Add customer\n"
           "2. Delete customer\n"
           "3. Edit customer\n"
           "4. Display customer profiles\n"
           "5. Export database to file\n"
           "6. Import database from file\n"
           "7. Return to Main Menu\n"
           "*********************************************************\n"
           "Select an option>");
}

/*******************************************************************************
 *This function runs the database menu and handles the user's choice. It also
 *transfers the initialised customer data from the main menu to the functions.
 *inputs:
 *- Customer list
 *- Current index in list
 *outputs:
 *- none
 *******************************************************************************/
void runCustomerMenu(customer_t* customers, int* currIndex) {
    int choice = 0;
    while (choice != 7) {
        printCustomerMenu();
        if (scanf("%d", &choice) != 1) {
            while(fgetc(stdin) != '\n'); /* Eliminate overflow */
            printf("Invalid input, please enter a number.\n");
        }
        else {
            switch(choice) {
                case 1:
                    addCustomer(customers, currIndex);
                    break;
                case 2:
                    deleteCustomer(customers, currIndex);
                    break;
                case 3:
                    editCustomer(customers, currIndex);
                    break;
                case 4:
                    displayCustomers(customers, currIndex);
                    break;
                case 5:
                    exportDatabase(customers, currIndex);
                    break;
                case 6:
                    importDatabase(customers, currIndex);
                    break;
                case 7:
                    break;
                default:
                    printf("Invalid option\n");
            }
        }
    }
}

/*******************************************************************************
 *This function adds a new customer to the customer list while performing
 *validation on the input.
 *inputs:
 *- Customer list
 *- Current index in list
 *outputs:
 *- none
 *******************************************************************************/
void addCustomer(customer_t* customers, int* currIndex) {
    customer_t currCustomer;

    if (*currIndex > CUSTOMER_LIMIT) {
        printf("Max number of customers reached. Exitting\n");
        return;
    }
    /* Set the current customer's details*/
    setName(&currCustomer);
    setPhoneNo(&currCustomer);
    setBirthDay(&currCustomer);
    setBirthMonth(&currCustomer);
    setBirthYear(&currCustomer);
    setCardNo(&currCustomer);
    setCardCvv(&currCustomer);

    customers[*currIndex] = currCustomer;
    /* Increment the current index */
    *currIndex += 1;
    printf("Customer '%s' successfully added\n", currCustomer.name);
}

/*******************************************************************************
 *This function deletes the customer at the index selected by the user in
 *the internal database.
 *inputs:
 *- Customer list
 *- Current index in list
 *outputs:
 *- none
 *******************************************************************************/
void deleteCustomer(customer_t* customers, int* currIndex) {
    if (*currIndex == 0) {
        printf("No customers in the database\n");
        return;
    }

    int selectedIndex = 0;
    printf("Select a customer to delete>");
    scanf("%d", &selectedIndex);
    selectedIndex -= 1;

    if (selectedIndex > *currIndex || selectedIndex < 0) {
        printf("Delete error, customer does not exist\n");
        return;
    }

    char customerName[NAME_LIMIT]; 
    /* Temporarily store customer name */
    strcpy(customerName, customers[selectedIndex].name);
    if (selectedIndex == *currIndex) {
        *currIndex -= 1;
    }
    else {
        /* Move everything to the left by 1 */
        while(selectedIndex < *currIndex - 1) {
            customers[selectedIndex] = customers[selectedIndex+1];
            selectedIndex++;
        }
        *currIndex -= 1;
    }
    printf("Customer: '%s' successfully deleted\n", customerName);
}

/*******************************************************************************
 *This function edits the customer at the index selected by the user. It also
 *provides options to select which field to edit e.g. Name, phone number
 *inputs:
 *- Customer list
 *- Current index in list
 *outputs:
 *- none
 *******************************************************************************/
void editCustomer(customer_t* customers, int* currIndex) {
    if (*currIndex == 0) {
        printf("No customers in the database\n");
        return;
    }

    int selectedIndex = 0;
    printf("Select a customer to edit>");
    scanf("%d", &selectedIndex);
    selectedIndex -= 1;

    if (selectedIndex > *currIndex || selectedIndex < 0) {
        printf("Edit error, customer does not exist\n");
        return;
    }

    printf("Editing customer: '%s'\n", customers[selectedIndex].name);
    runEditMenu(customers, selectedIndex);
    printf("Changes successfully made to customer: '%s'\n", customers[selectedIndex].name);
}

/* Kenson */
/*******************************************************************************
 *This function displays all of the available customers in the internal database.
 *inputs:
 *- Customer list
 *- Current index in list
 *outputs:
 *- none
 *******************************************************************************/
void displayCustomers(customer_t* customers, int* currIndex) {
    if (*currIndex == 0) {
        printf("No customers in the database\n");
        return;
    }

    int num_customer = 1;
    int i;
    char* empty_space = " ";

    if ( *currIndex > 0 ) {
        printf("Displaying customer profiles:\n");
        printf("%-14sCustomer Name%-16s| %-2sNumber%-3s| %-3sDOB%-5s| Credit Card Number | CVV |\n",
        empty_space, empty_space, empty_space, empty_space, empty_space, empty_space);

    for ( i = 0; i < *currIndex; i++ ) {
        printf("%3d. %-37s | %s | %02d/%02d/%02d | %s%-2s | %-3s |\n", 
            num_customer, 
            customers[i].name,
            customers[i].phoneNumber,
            customers[i].dateOfBirth.day,
            customers[i].dateOfBirth.month,
            customers[i].dateOfBirth.year,
            customers[i].cardNo,
            empty_space,
            customers[i].cardcvv);
            num_customer++;
        }
    }
}

/* Kenson */
/*******************************************************************************
 *This functions exports all of the customers in the internal database to and
 *external file.
 *inputs:
 *- Customer list
 *- Current index in list
 *outputs:
 *- none
 *******************************************************************************/
void exportDatabase(customer_t* customers, int* currIndex) {
    if (*currIndex == 0) {
        printf("No customers in the database\n");
        return;
    }
    
    FILE* fp = fopen("customer_database", "w");
    int i = 0;
    
    /* printing database layout */
    if ( fp != NULL ) {
        while ( i < *currIndex ) {
            fprintf(fp, "%s %s %d %d %d %s %s\n", 
            customers[i].name,
            customers[i].phoneNumber,
            customers[i].dateOfBirth.day,
            customers[i].dateOfBirth.month,
            customers[i].dateOfBirth.year,
            customers[i].cardNo,
            customers[i].cardcvv);
            i++;
        }
        printf("Customer data successfully exported to database file\n");
    }

    else {
        printf("Failed to export to database file\n");
    }

    fclose(fp);

}   

/*******************************************************************************
 *This function imports all of the customers from an external file to the
 *internal customer database in the program.
 *inputs:
 *- Customer list
 *- Current index in list
 *outputs:
 *- none
 *******************************************************************************/
void importDatabase(customer_t* customers, int* currIndex) {
    int number_of_lines = 0;
    int i = 0;
    char dbName[50];
    printf("Enter the name of the file>");
    scanf("%s", dbName);
    /* open file in read mode */
    FILE* fp = fopen(dbName, "r");
    /* Test import database in wrong format*/
    #ifdef DEBUG
        fp = fopen("test_db", "r");
    #endif
    /* check if file exists */
    if ( fp == NULL ) {
        printf("Database failed to be read\n");
        return;
    }
    /* get character from customer db*/
    int c;
    for (c = fgetc(fp); c != EOF; c = fgetc(fp)) {
        if (c == '\n') {
            number_of_lines += 1;
        }
    }
   
    rewind(fp); /* reset file position*/

    /* scanning customer information from file */
    while ( i < number_of_lines ) {
            if (fscanf(fp, "%s %s %d %d %d %s %s\n", 
                customers[i].name,
                customers[i].phoneNumber,
                &customers[i].dateOfBirth.day,
                &customers[i].dateOfBirth.month,
                &customers[i].dateOfBirth.year,
                customers[i].cardNo,
                customers[i].cardcvv) == 7 )  {
                i++;    
            }
            /* inform user of failed import */
            else {
                number_of_lines = 0;
                printf("Failed to import database\n");
                break;
            }  
      }  

        /* inform user that database import is completed */
      if (number_of_lines > 0 ) {
          printf("Database successfully imported\n");
      }
        
    /* updating customer position in list */
    *currIndex = number_of_lines;
    fclose(fp);
}

/* Utility functions */
/*******************************************************************************
 *This function returns the number of digits or the length of the string 
 *inputted to this function.
 *inputs:
 *- String of numbers
 *outputs:
 *- Number of digits
 *******************************************************************************/
int countDigits(char* number) {
    int digits = strlen(number);
    #ifdef DEBUG
        printf("%d", digits);
    #endif
    return digits;
}

/*******************************************************************************
 *This functions displays all of the options available in the edit menu which is
 *displayed when the user selects to edit customer information.
 *inputs:
 *- none
 *outputs:
 *- none
 *******************************************************************************/
void printEditMenu() {
    printf("\n*********************************************************\n"
           "1. Name\n"
           "2. Phone number\n"
           "3. Day of birth\n"
           "4. Month of birth\n"
           "5. Year of birth\n"
           "6. Card number\n"
           "7. Card cvv\n"
           "8. Exit\n"
           "*********************************************************\n"
           "Select an option>");
}

/*******************************************************************************
 *This function runs the edit menu as well as transfers the customer data from
 *the previous menu to the edit menu.
 *inputs:
 *- Customer list
 *- Index of the customer being edited
 *outputs:
 *- none
 *******************************************************************************/
void runEditMenu(customer_t* customers, int selectedIndex) {
    int choice = 0;
    while (choice != 8) {
        printEditMenu();
        if (scanf("%d", &choice) != 1) {
            while(fgetc(stdin) != '\n'); /* Eliminate overflow */
            printf("Invalid input, please enter a number.\n");
        }
        else {
            switch(choice) {
                case 1: 
                    setName(&customers[selectedIndex]);
                    break;
                case 2:
                    setPhoneNo(&customers[selectedIndex]);
                    break;
                case 3:
                    setBirthDay(&customers[selectedIndex]);
                    break;
                case 4:
                    setBirthMonth(&customers[selectedIndex]);
                    break;
                case 5:
                    setBirthYear(&customers[selectedIndex]);
                    break;
                case 6:
                    setCardNo(&customers[selectedIndex]);
                    break;
                case 7:
                    setCardCvv(&customers[selectedIndex]);
                    break;
                case 8:
                    break;
                default:
                    printf("Invalid option.\n");
            }
        }
    }
}

/* Functions for setting customer data */
/*******************************************************************************
 *This function sets and validates the name of a customer.
 *inputs:
 *- A customer 
 *outputs:
 *- none
 *******************************************************************************/
void setName(customer_t* customer) {
    char temp;
    /* Eat extra newline */
    scanf("%c", &temp);
    printf("Enter customer name>");
    fgets(customer->name, NAME_LIMIT, stdin);
    /* Input length validation */
    while (strchr(customer->name, '\n') == NULL || customer->name[1] == '\0') {
    /* Handle input too long */
        if (strchr(customer->name, '\n') == NULL) {
            printf("Name too long\n");
            while(fgetc(stdin) != '\n'); /* Eliminate overflow*/
            printf("Enter customer name>");
            fgets(customer->name, NAME_LIMIT, stdin);
        }
        /* Handle no input */
        if (customer->name[1] == '\0') {
            printf("Invalid Input\n");
            printf("Enter customer name>");
            fgets(customer->name, NAME_LIMIT, stdin);
        }
    }
    /* Remove any extra newlines */
    customer->name[strcspn(customer->name, "\n")] = 0;
}

/*******************************************************************************
 *This function sets and validates the phone number of a customer.
 *inputs:
 *- A customer 
 *outputs:
 *- none
 *******************************************************************************/
void setPhoneNo(customer_t* customer) {
    printf("Enter customer phone number>");
    scanf("%s", customer->phoneNumber);
    /* Restrict to numbers only */
    /* ASCII range - 48-57 for 0-9 */
    int i;
    int invalidValue = 1;
    while(invalidValue == 1) {
        for (i = 0; i < strlen(customer->phoneNumber); i++) {
            if (customer->phoneNumber[i] > 57 || customer->phoneNumber[i] < 48) {
                invalidValue = 1;
                printf("Invalid Input.\n");
                printf("Enter customer phone number>");
                scanf("%s", customer->phoneNumber);
            }
            else {
                invalidValue = 0;
            }
        }
    }
    /* Restrict to 10 digits */
    while (countDigits(customer->phoneNumber) != 10) {
        printf("Invalid number, please enter a 10 digit number.\n");
        printf("Enter customer phone number>");
        scanf("%s", customer->phoneNumber);
    }
}

/*******************************************************************************
 *This function sets and validates the birth day of a customer.
 *inputs:
 *- A customer 
 *outputs:
 *- none
 *******************************************************************************/
void setBirthDay(customer_t* customer) {
    printf("Enter customer birthday: day>");
    /* Input type validation */
    while (scanf("%d", &customer->dateOfBirth.day) != 1) {
        while(fgetc(stdin) != '\n'); /* Eliminate overflow */
        printf("Invalid Input.\n");
        printf("Enter customer birthday: day>");
    }
    /* Day validation */
    while (customer->dateOfBirth.day > 31 || customer->dateOfBirth.day < 1) {
        printf("Invalid day.\n");
        printf("Enter customer birthday: day>");
        scanf("%d", &customer->dateOfBirth.day);
    }
}

/*******************************************************************************
 *This function sets and validates the birth month of a customer.
 *inputs:
 *- A customer 
 *outputs:
 *- none
 *******************************************************************************/
void setBirthMonth(customer_t* customer) {
    printf("Enter customer birthday: month>");
    /* Input type validation */
    while (scanf("%d", &customer->dateOfBirth.month) != 1) {
        while(fgetc(stdin) != '\n'); /* Eliminate overflow */
        printf("Invalid Input.\n");
        printf("Enter customer birthday: month>");
    }
    /* Month validation */
    while (customer->dateOfBirth.month > 12 || customer->dateOfBirth.month < 1) {
        printf("Invalid month.\n");
        printf("Enter customer birthday: month>");
        scanf("%d", &customer->dateOfBirth.month);
    }
}

/*******************************************************************************
 *This function sets and validates the birth year of a customer.
 *inputs:
 *- A customer 
 *outputs:
 *- none
 *******************************************************************************/
void setBirthYear(customer_t* customer) {
    printf("Enter customer birthday: year>");
    /* Input type validation */
    while (scanf("%d", &customer->dateOfBirth.year) != 1) {
        while(fgetc(stdin) != '\n'); /* Eliminate overflow */
        printf("Invalid Input.\n");
        printf("Enter customer birthday: year>");
    }
    /* Year validation */
    while (customer->dateOfBirth.year > 2008 || customer->dateOfBirth.year < 1900) {
        printf("Invalid year.\n");
        printf("Enter customer birthday: year>");
        scanf("%d", &customer->dateOfBirth.year);
    }
}

/*******************************************************************************
 *This function sets and validates the transaction card number of a customer.
 *inputs:
 *- A customer 
 *outputs:
 *- none
 *******************************************************************************/
void setCardNo(customer_t* customer) {
    printf("Enter customer card number>");
    scanf("%s", customer->cardNo);
    /* Restrict to numbers only */
    /* ASCII range - 48-57 for 0-9 */
    int i;
    int invalidValue = 1;
    while(invalidValue == 1) {
        for (i = 0; i < strlen(customer->cardNo); i++) {
            if (customer->cardNo[i] > 57 || customer->cardNo[i] < 48) {
                invalidValue = 1;
                printf("Invalid Input.\n");
                printf("Enter customer card number>");
                scanf("%s", customer->cardNo);
            }
            else {
                invalidValue = 0;
            }
        }
    }
    /* Restrict length to 16 digits */
    while (countDigits(customer->cardNo) != 16) {
        printf("Invalid value, please enter a 16 digit value.\n");
        printf("Enter customer card number>");
        scanf("%s", customer->cardNo);
    }
}

/*******************************************************************************
 *This function sets and validates the transaction card cvv of a customer.
 *inputs:
 *- A customer 
 *outputs:
 *- none
 *******************************************************************************/
void setCardCvv(customer_t* customer) {
    printf("Enter customer card cvv>");
    scanf("%s", customer->cardcvv);
    /* Restrict length to 3 digits */
    while (countDigits(customer->cardcvv) != 3) {
        printf("Invalid value, please enter a 3 digit value.\n");
        printf("Enter customer card cvv>");
        scanf("%s", customer->cardcvv);
    }
}
