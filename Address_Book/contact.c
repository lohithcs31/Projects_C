#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

void listContacts(AddressBook *addressBook) 
{
    // List all the contacts present in the address book
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    //(Until entered name is valid, keep prompting the user)
    //1. Read name
    //2. Validate name
    //3. If valid, use strcpy to store name

    //(Until entered number is valid, keep prompting the user)
    //1. Read ph number
    //2. Validate number
    //3. If valid, use strcpy to store number

    //(Until entered email is valid, keep prompting the user)
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
    //Increment the contact count to update that a contact is added to the address book
    addressBook->contactCount++;
    printf("Contact created successfully!\n");
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
                //Flag to determine if the name is found
                int flag_name = 0; 
                //Read name until new line character is encountered
                scanf(" %[^\n]",search_name); 
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(!(strcmp(addressBook->contacts[i].name,search_name)))
                    {
                        //Store the index where the contact was found
                        *index = i; 
                        printf("Contact found!\n");
                        printf("%d %s %s %s\n",*index, addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        //Increment temp everytime entered search name matches with the one in the address book
                        temp++;
                        //If name is found, set flag to 1
                        flag_name = 1; 
                    }
                }
                if(flag_name == 0) //If flag is 0, the contact was not found
                {
                    printf("Contact not found!!!\n");
                }
                break;
        case 2: printf("Enter the phone number : ");
                char search_phone[20];
                //Flag to determine if the phone number is found
                int flag_phone = 0;
                scanf("%s",search_phone);
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(!(strcmp(addressBook->contacts[i].phone,search_phone)))
                    {
                        //Store the index where the contact was found
                        *index = i;
                        printf("Contact found!\n");
                        printf("%d %s %s %s\n",*index,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        //Increment temp everytime entered phone number matches with the one in the address book
                        temp++;
                        //If phone number is found, set flag to 1
                        flag_phone = 1;
                    }
                }
                if(flag_phone == 0) //If flag is 0, the contact was not found
                {
                    printf("Contact not found!!!\n");
                }
                break;
        case 3: printf("Enter the email address : ");
                char search_email[20];
                //Flag to determine if the email address is found
                int flag_mail = 0;
                scanf("%s",search_email);
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(!(strcmp(addressBook->contacts[i].email,search_email)))
                    {
                        //Store the index where the contact was found
                        *index = i;
                        printf("Contact found!\n");
                        printf("%d %s %s %s\n",*index, addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        //Increment temp everytime entered phone number matches with the one in the address book
                        temp++;
                        //If phone number is found, set flag to 1
                        flag_mail = 1;
                    }
                }
                if(flag_mail == 0) //If flag is 0, the contact was not found
                {
                    printf("Contact not found!!!\n");
                }
                break;
        default : printf("Enter valid search criteria!\n"); //If the choice is not between 1-3, print and return to main menu
    }
    return temp;
}

void editContact(AddressBook *addressBook)
{
	//Variable res to store the return value from searchContact function
    //index variable to pass as an argument to receive the contact index value
    int res,index=0;
    int option;
    res = searchContact(addressBook,&index);
    if(res==0) //If result is 0, then the contact was not found, no need to edit
    {
        //print statement present in search function, hence avoiding duplication
        return;
    }
    else if(res>1) //If there is more than 1 matching contact, prompt the user for the contact index to edit
    {
        printf("Enter the contact index to be edited : ");
        scanf("%d",&index);
    }
    else
    {//Do nothing
    }
    printf("Enter the option :\n");
    printf("1. Edit Name\n");
    printf("2. Edit Phone Number\n");
    printf("3. Edit Email address\n");
    scanf("%d",&option);
    switch(option)
    {           //Receive user input for name until its valid
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
                        printf("Name edited successfully!\n");
                    }
                    else
                    {
                        printf("Invalid name, please enter valid name\n");
                    }
                }while(!valid_name);
                break;
        case 2: //Receive user input for phone number until its valid
                char phone[20];
                int valid_number;
                do
                {
                    printf("Enter the phone number : ");
                    scanf("%s",phone);
                    valid_number = check_number(addressBook,phone);
                    if(valid_number)
                    {
                        strcpy(addressBook->contacts[index].phone,phone);
                        printf("Phone number edited successfully!\n");
                    }
                    else
                    {
                        printf("Invalid phone number, please enter valid phone number\n");
                    }
                }while(!valid_number);
                break;
        case 3: //Receive user input for email address until its valid
                char email[50];
                int valid_email;
                do
                {
                    printf("Enter the email address : ");
                    scanf("%s",email);
                    valid_email = check_mail(addressBook,email);
                    if(valid_email)
                    {
                        strcpy(addressBook->contacts[index].email,email);
                        printf("Email address edited successfully!\n");
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
    //Variable res to store the return value from searchContact function
    //index variable to pass as an argument to receive the contact index value
    int res,index=0;
    int option;
    res = searchContact(addressBook,&index);
    if(res==0) //If result is 0, then the contact was not found, no need to delete, 
    {
        //print statement present in search function, hence avoiding duplication
        return;
    }
    else if(res>1) //If there is more than 1 matching contact, prompt the user for the contact index to delete
    {
        printf("Enter the contact index to be deleted : ");
        scanf("%d",&index);
    }
    else
    {//Do nothing
    }
    //After the index is updated, shift all elements from index until contact count value
    for(int k=index;k<addressBook->contactCount;k++)
    {
        addressBook->contacts[k] = addressBook->contacts[k+1];
    }
    //Decrement the contact count to update that a contact is deleted from the address book
    addressBook->contactCount--;
    printf("Contact deleted successfully!\n");
}

//Function to check whether the user entered valid name
int check_name(char str[])
{
    //Name should contain alphabets and space characters only
    //Flag variable to indicate if the name is valid
    int flag=1;
    for(int i=0;str[i]!='\0';i++)
    {
        if(!((str[i]>='A'&&str[i]<='Z')||(str[i]>='a'&&str[i]<='z')||str[i]==' '))
        {
            //Update flag to 0 to indicate that the name is invalid
            flag=0;
            break;
        }
    }
    return flag;
}
int check_number(AddressBook *addressBook, char str[])
{
    //Phone number should contain digits, length should be 10, and it should be unique
    //Flag variable to indicate if the phone number is valid
    int flag = 1;
    if(strlen(str)!=10)
    {
        //If the phone number is not 10 digit, then set flag to 0
        flag = 0;
        return flag;
    }
    else
    {
        for(int i=0;str[i]!='\0';i++)
        {
            if(!(str[i]>='0'&&str[i]<='9'))
            {
                //If the phone number contains a character other digits (0-9), then set flag to 0
                flag=0;
                return flag;
            }
        }
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if((!(strcmp(addressBook->contacts[i].phone,str))))
            {
                //If the entered phone number is already present in the address book, then set flag to 0
                flag=0;
                return flag;
            }
        }
    }
    return flag;
}
int check_mail(AddressBook *addressBook, char str[])
{
    //Email address should contain alphanumeric characters, _(underscore), and .(dot). It should be unique
    //Flag variable to indicate if the email address is valid
    int flag = 1;
    for(int i=0;str[i]!='\0';i++)
    {
        if(!((str[i]>='a'&&str[i]<='z')||(str[i]=='@')||(str[i]=='.')||(str[i]=='_')||(str[i]>='0'&&str[i]<='9')))
        {
            //If the character is not any one of the characters mentioned above, then set flag to 0
            flag=0;
            return flag;
        }
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if((!(strcmp(addressBook->contacts[i].email,str))))
        {
            //If the email address is not unique, then set flag to 0
            flag=0;
            return flag;
        }
    }
    if(str[0]=='@')
    {
        //If character '@' is present at index 0, then set flag to 0
        flag=0;
        return flag;
    }
    int at_the_rate = 0; //Variable to indicate that the character '@' is present
    int count = 0; //Variable to keep track of the number of '@' characters in the email address
    for(int i=0;str[i]!='\0';i++)
    {
        if(str[i]=='@')
        {
            //If character '@' is found, set at_the_rate to 1 and increment count
            at_the_rate = 1;
            count++;
        }
    }
    if(count>1 || at_the_rate==0)
    {
        //If either the count is greater than 1 or character '@' is not present, then set flag to 0
        flag=0;
        return flag;
    }
    if(!(strstr(str,".com")))
    {
        //If the substring '.com' is not present in the email address, then set flag to 0
        flag=0;
        return flag;
    }
    for(int i=0;str[i]!='\0';i++)
    {
        if(str[i]=='@')
        {
            if(!(((str[i-1]>='a'&&str[i-1]<='z')||(str[i-1]>='0'&&str[i-1]<='9'))||((str[i+1]>='a'&&str[i+1]<='z')||(str[i+1]>='0'&&str[i+1]<='9'))))
            {
                //If there are no alphanumeric characters before and after '@' character, then set flag to 0
                flag = 0;
                return flag;
            }
        }
    }
    return flag;
}