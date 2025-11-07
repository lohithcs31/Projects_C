#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    //Everything under do-while loop (until entered name is valid, keep prompting the user)
    //1. Read name
    //2. Validate name
    //3. If valid, use strcpy to store name

    //Everything under do-while loop (until entered number is valid, keep prompting the user)
    //1. Read ph number
    //2. Validate number
    //3. If valid, use strcpy to store number

    //Everything under do-while loop (until entered email is valid, keep prompting the user)
    //1. Read email
    //2. Validate email
    //3. If valid, use strcpy to store email

    printf("Enter the details :\n");
    //Receive user input until its valid using do-while loop
    char name[50];
    int valid_name;
    do
    {
        printf("Enter the name : ");
        scanf(" %[^\n]",name);
        valid_name = check_name(name);
        if(valid_name)
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name,name);
        }
        else
        {
            printf("Invalid name, please enter valid name\n");
        }
    }while(!valid_name);
    char phone[20];
    int valid_number;
    do
    {
        printf("Enter the phone number : ");
        scanf("%s",phone);
        valid_number = check_number(addressBook,phone);
        if(valid_number)
        {
            strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
        }
        else
        {
            printf("Invalid phone number, please enter valid phone number\n");
        }
    }while(!valid_number);
    char email[50];
    int valid_email;
    do
    {
        printf("Enter the email address : ");
        scanf("%s",email);
        valid_email = check_mail(addressBook,email);
        if(valid_email)
        {
            strcpy(addressBook->contacts[addressBook->contactCount].email,email);
        }
        else
        {
            printf("Invalid email address, please enter valid email address\n");
        }
    }while(!valid_email);
    /*if(addressBook->contactCount>MAX_CONTACTS)
    {
        printf("Address Book is full! Contact cannot be filled\n");
        return;
    }*/
	/* Define the logic to create a Contacts */
    /*printf("Enter the name : ");
    scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);
    printf("Enter the phone number : ");
    scanf("%s",addressBook->contacts[addressBook->contactCount].phone);
    printf("Enter the email address : ");
    scanf("%s",addressBook->contacts[addressBook->contactCount].email);*/

    addressBook->contactCount++;
}

int searchContact(AddressBook *addressBook, int *index) 
{
    /* Define the logic for search */
    int temp=0;
    int criteria;
    printf("Enter search criteria:\n");
    printf("1. Search by name\n");
    printf("2. Search by phone\n");
    printf("3. Search by email\n");
    scanf("%d",&criteria);
    switch(criteria)
    {
        case 1: printf("Enter the name : ");
                char search_name[50];
                int flag_name = 0;
                scanf(" %[^\n]",search_name);
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(!(strcmp(addressBook->contacts[i].name,search_name)))
                    {
                        *index = i;
                        printf("Contact found!\n");
                        printf("%d %s %s %s\n",*index, addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        temp++;
                        flag_name = 1;
                    }
                }
                if(flag_name == 0)
                {
                    printf("Contact not found!!!\n");
                }
                break;
        case 2: printf("Enter the phone number : ");
                char search_phone[20];
                int flag_phone = 0;
                scanf("%s",search_phone);
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(!(strcmp(addressBook->contacts[i].phone,search_phone)))
                    {
                        *index = i;
                        printf("Contact found!\n");
                        printf("%d %s %s %s\n",*index,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        temp++;
                        flag_phone = 1;
                    }
                }
                if(flag_phone == 0)
                {
                    printf("Contact not found!!!\n");
                }
                break;
        case 3: printf("Enter the email address : ");
                char search_email[20];
                int flag_mail = 0;
                scanf("%s",search_email);
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(!(strcmp(addressBook->contacts[i].email,search_email)))
                    {
                        *index = i;
                        printf("Contact found!\n");
                        printf("%d %s %s %s\n",*index, addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        temp++;
                        flag_mail = 1;
                    }
                }
                if(flag_mail == 0)
                {
                    printf("Contact not found!!!\n");
                }
                break;
        default : printf("Enter valid search criteria!\n");
    }
    return temp;
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int res,index=0;
    int option;
    res = searchContact(addressBook,&index);
    if(res==0)
    {
        printf("Contact not found!\n");
        return;
    }
    else if(res>1)
    {
        printf("Enter the contact index to be edited : ");
        scanf("%d",&index);
    }
    else
    {//
    }
    printf("Enter the option :\n");
    printf("1. Edit Name\n");
    printf("2. Edit Phone Number\n");
    printf("3. Edit Email address\n");
    scanf("%d",&option);
    switch(option)
    { //Receive user input until its valid using do-while loop
        case 1: char name[50];
                int valid_name;
                do
                {
                    printf("Enter the name : ");
                    scanf(" %[^\n]",name);
                    valid_name = check_name(name);
                    if(valid_name)
                    {
                        strcpy(addressBook->contacts[index].name,name);
                    }
                    else
                    {
                        printf("Invalid name, please enter valid name\n");
                    }
                }while(!valid_name);
                break;
        case 2: char phone[20];
                int valid_number;
                do
                {
                    printf("Enter the phone number : ");
                    scanf("%s",phone);
                    valid_number = check_number(addressBook,phone);
                    if(valid_number)
                    {
                        strcpy(addressBook->contacts[index].phone,phone);
                    }
                    else
                    {
                        printf("Invalid phone number, please enter valid phone number\n");
                    }
                }while(!valid_number);
                break;
        case 3: char email[50];
                int valid_email;
                do
                {
                    printf("Enter the email address : ");
                    scanf("%s",email);
                    valid_email = check_mail(addressBook,email);
                    if(valid_email)
                    {
                        strcpy(addressBook->contacts[index].email,email);
                    }
                    else
                    {
                        printf("Invalid email address, please enter valid email address\n");
                    }
                }while(!valid_email);
                break;
        default : printf("Enter valid choice\n");
    }
}


void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int res,index=0;
    int option;
    res = searchContact(addressBook,&index);
    if(res==0)
    {
        printf("Contact not found!\n");
        return;
    }
    else if(res>1)
    {
        printf("Enter the contact index to be deleted : ");
        scanf("%d",&index);
    }
    else
    {//
    }
    
    for(int k=index;k<addressBook->contactCount;k++)
    {
        addressBook->contacts[k] = addressBook->contacts[k+1];
    }
                    
    addressBook->contactCount--;

}

int check_name(char str[])
{
    int flag=1;
    for(int i=0;str[i]!='\0';i++)
    {
        if(!((str[i]>='A'&&str[i]<='Z')||(str[i]>='a'&&str[i]<='z')||str[i]==' '))
        {
            flag=0;
            break;
        }
    }
    return flag;
}
int check_number(AddressBook *addressBook, char str[])
{
    int flag = 1;
    if(strlen(str)!=10)
    {
        flag = 0;
        return flag;
    }
    else
    {
        for(int i=0;str[i]!='\0';i++)
        {
            if(!(str[i]>='0'&&str[i]<='9'))
            {
                flag=0;
                return flag;
            }
        }
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if((!(strcmp(addressBook->contacts[i].phone,str))))
            {
                flag=0;
                return flag;
            }
        }
    }
    return flag;
}
int check_mail(AddressBook *addressBook, char str[])
{
    int flag = 1;
    for(int i=0;str[i]!='\0';i++)
    {
        if(!((str[i]>='a'&&str[i]<='z')||(str[i]=='@')||(str[i]=='.')||(str[i]=='_')||(str[i]>='0'&&str[i]<='9')))
        {
            flag=0;
            return flag;
        }
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if((!(strcmp(addressBook->contacts[i].email,str))))
        {
            flag=0;
            return flag;
        }
    }
    if(str[0]=='@')
    {
        flag=0;
        return flag;
    }
    int at_the_rate = 0;
    int count=0;
    for(int i=0;str[i]!='\0';i++)
    {
        if(str[i]=='@')
        {
            at_the_rate = 1;
            count++;
        }
    }
    if(count>1 || at_the_rate==0)
    {
        flag=0;
        return flag;
    }
    if(!(strstr(str,".com")))
    {
        flag=0;
        return flag;
    }
    for(int i=0;str[i]!='\0';i++)
    {
        if(str[i]=='@')
        {
            if(!(((str[i-1]>='a'&&str[i-1]<='z')||(str[i-1]>='0'&&str[i-1]<='9'))||((str[i+1]>='a'&&str[i+1]<='z')||(str[i+1]>='0'&&str[i+1]<='9'))))
            {
                flag = 0;
                return flag;
            }
        }
    }
    return flag;
}