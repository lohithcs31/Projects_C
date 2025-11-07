#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    //Open the file to be written
    FILE *fptr = fopen("contacts.txt","w");
    if(fptr==NULL)
    {
        printf("Error!!File not opened\n");
        return;
    }
    //Store the contact count into the file using fprintf (store "#"contactcount)
    fprintf(fptr,"#%d\n",addressBook->contactCount);
    //Run a loop to store all contact details
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
}

void loadContactsFromFile(AddressBook* addressBook)
{
    //Open the file to be read
    FILE *fptr = fopen("contacts.txt","r");
    if(fptr==NULL)
    {
        printf("Error!!File not opened\n");
        return;
    }
    //Store the contact count into the file using fprintf (store "#"contactcount)
    fscanf(fptr,"#%d\n",&addressBook->contactCount);
    //Run a loop to store all contact details
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
}
