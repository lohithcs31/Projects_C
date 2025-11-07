#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook, int *index);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveAndExit(AddressBook *AddressBook);
void loadContactsFromFile(AddressBook *addressBook);
int check_name(char str[]);
int check_number(AddressBook *addressBook, char str[]);
int check_mail(AddressBook *addressBook, char str[]);
#endif
