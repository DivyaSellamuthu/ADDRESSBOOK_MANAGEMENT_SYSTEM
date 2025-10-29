/*
    NAME        : Divya S
    DATE        : 29-10-25
    TITLE       : AddressBook Management System
    DESCRIPTION : A console based application that allows users to CREATE,SEARCH,EDIT,DELETE and SAVE contact details efficiently.
    VALIDATION FEATURES :
        -> Ensures phone number contains exactly 10 digits and no alphabets/special characters.
        -> Prevents duplicate entries for phone numbers and email IDs.
        -> Validates email structure: must contain '@' and '.com', start with a lowercase letter or digit,
            and contain no uppercase or invalid symbols.
        -> Confirms contact existence before editing or deleting.
        -> Handles multiple contacts with the same name using serial number selection.
        -> Displays appropriate warning messages for invalid inputs.
        -> Prevents invalid menu options and input types through repeated prompts.
*/
#include <stdio.h>//header files which contains only built-in function prototype
#include "contact.h"
#include<string.h>

int main() {
    int choice;
    AddressBook addressBook;

    initialize(&addressBook); // Initialize the address book- load conatacts from file.

    do {
        printf("\nAddress Book Menu:\n");
        printf("1.➕ Create contact\n");
        printf("2.🔍 Search contact\n");
        printf("3.✏️  Edit contact\n");
        printf("4.🗑️  Delete contact\n");
        printf("5.📋 List all contacts\n");
        printf("6.🔚 Exit\n");
        printf("✍️  Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);//This function used to create contact  
                break;
            case 2:
                searchContact(&addressBook);//This function used to search contact
                break;
            case 3:
                editContact(&addressBook);//This function used to edit contact
                break;
            case 4:
                deleteContact(&addressBook);//This function used to delete contact
                break;
            case 5:
                listContacts(&addressBook);//This function used to display contact
                break;
            case 6:
            char save[5];//This case is used to ask the user to save the changes or not ,if not then exit .
            printf("Do u want to save 💾 the changes? ");
            scanf(" %s",save);
            if((strcmp(save,"yes")==0)||(strcmp(save,"Yes")==0)||(strcmp(save,"Y")==0)||(strcmp(save,"y")==0)){
                printf("Saving and Exiting 😊...\n");
                saveContactsToFile(&addressBook);
            }
            else{
                printf("Exiting 😊...\n");
            }
            break;
            
            default:
                printf("Invalid choice 🚫. Please try again.\n");//This gets printed if the user enters the invalid choice
        }
    } while (choice != 6);
    
       return 0;
}
