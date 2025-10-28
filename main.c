#include <stdio.h>
#include "contact.h"
#include<string.h>

int main() {
    int choice;
    AddressBook addressBook;

    initialize(&addressBook); // Initialize the address book

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
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook);
                break;
            case 6:
            char save[5];
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
                printf("Invalid choice 🚫. Please try again.\n");
        }
    } while (choice != 6);
    
       return 0;
}
