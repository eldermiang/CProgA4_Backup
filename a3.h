/* Structs */
/* Customer */
struct Date {
    unsigned int day;
    unsigned int month;
    unsigned int year;
};
typedef struct Date date_t;

struct Customer {
    /* Char fields have 1 additional char for null character */
    char name[41];
    char phoneNumber[11];
    date_t dateOfBirth;
    char cardNo[17];
    char cardcvv[4];
};
typedef struct Customer customer_t;

/* Functions */
/* Main Menu */
void printMenu();
void runMenu(customer_t* customers, int* currIndex);

/* Customer Database */
void printCustomerMenu();
void runCustomerMenu(customer_t* customers, int* currIndex);
void addCustomer(customer_t* customers, int* currIndex);
void deleteCustomer(customer_t* customers, int* currIndex);
void editCustomer(customer_t* customers, int* currIndex);
void displayCustomers(customer_t* customers, int* currIndex);
void exportDatabase(customer_t* customers, int* currIndex);
void importDatabase();
/* Utility Functions */
int countDigits(char* number);
void printEditMenu();
void runEditMenu(customer_t* customers, int selectedIndex);
/* Customer data manipulation */
void setName(customer_t* customer);
void setNameRecursive(customer_t* customer); /* Test */
void setPhoneNo(customer_t* customer);
void setBirthDay(customer_t* customer);
void setBirthMonth(customer_t* customer);
void setBirthYear(customer_t* customer);
void setCardNo(customer_t* customer);
void setCardCvv(customer_t* customer);

/* Text Compression */
void printCompressMenu();
void runCompressMenu();
char* readDatabase();
void run_length_encode(char* string);
void run_length_decode();
void compare_db();

/* Text Encryption */
void printEncryptionMenu();
void runEncryptionMenu();
void fileEncryption(char* string);
void fileDecryption(char* string);
int databaseEncryption();
int databaseDecryption();


