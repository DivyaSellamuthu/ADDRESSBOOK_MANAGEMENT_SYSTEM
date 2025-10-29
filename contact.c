#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// Utility function: Compares strings (name/phone/email) to find matching contact.
// Returns index if match found; -1 if not found.

int comparing_strings(AddressBook *addressBook,char *str,int choice)
{
    for(int i=0;i<addressBook->contactCount;i++){
        if(choice==1){
            if((strcmp(str,addressBook->contacts[i].name))==0){
                return i;
            }
        }
        else if(choice==2){
            if((strcmp(str,addressBook->contacts[i].phone))==0){
                return i;
            }
        }
        else{
            if((strcmp(str,addressBook->contacts[i].email))==0){
                return i;
            }
        }
        }
        return -1;
        
}

void listContacts(AddressBook *addressBook) 
{
    int size=addressBook->contactCount;
    Contact temp;
        for(int i=0;i<size-1;i++){
            for(int j=0;j<size-i-1;j++){
                if(strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0){
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        
    printf("----------------------------------------------------------------------------------\n");
    printf("%-6s %-35s %-15s %-30s\n", "SL.No", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------------------\n");
    for(int i=0;i<size;i++){
        printf("%-6d %-35s %-15s %-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf("----------------------------------------------------------------------------------\n");
    printf("Total Contacts: %d\n",addressBook->contactCount);
    printf("----------------------------------------------------------------------------------\n");
    // Sort contacts based on the chosen criteria
    
}

void initialize(AddressBook *addressBook) {
    //addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    // Displays sorted contact list alphabetically by name for better readability.
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    char name[20],phone[20],email[20];
    int flag1,flag,len,index;
    printf("✍️  Enter your name : ");
    scanf(" %[^\n]",name);
    
    do{
            printf("✍️  Enter your phone number 📞 : ");
            scanf(" %s",phone);
            len=strlen(phone);
            if(len!=10){
                // Validate phone number: must be 10 digits and contain only numeric characters.
                printf("Enter the 10 digit number⚠️\n");
                continue;
            }
                flag1=1;
                for(int i=0;i<len;i++){
                    if(phone[i]<'0'||phone[i]>'9'){
                        flag1=0;
                        break;
                }
            }
            if(flag1==0){
                printf("Enter only digits⚠️!!\n");
                continue;
            }
            //Validation: Prevent duplicate phone numbers.
            index=comparing_strings(addressBook,phone,2);
            if((index!=-1)){
                printf("Contact exist⚠️! Enter the correct number\n");
                continue;
            }
            break;      
    }while(1);
    
    do{
            printf("✍️  Enter your email 📩 id : ");
            scanf(" %s",email);
            int len=strlen(email);
            // Validate email format: must include '@' and '.com', start with lowercase, no capitals or invalid symbols.
             if((strchr(email,'@')==NULL)||(strstr(email,".com")==NULL)){
                printf("Enter a valid mail id⚠️\n");
                continue;
            }
            flag=1;
            if((email[0]>='a'&&email[0]<='z')||(email[0]>='0'&&(email[0]<='9'))){
                flag=1;
            }
            else{
                flag=0;
            }
            for(int i=1;i<len;i++){
                if(email[i]>='A'&&email[i]<='Z'){
                        flag=0;
                        break;
                    }
                else{
                    if((email[i]<'a'||email[i]>'z')&&email[i]!='@'&&email[i]!='.'&&(email[i]<'0'||email[i]>'9')){
                            flag=0;
                            break;
                    }
                }
                
            }
        
            if(flag==0){
                printf("Oops☹️! Start with a lowercase 🔡 and avoid capitals ❌ , special symbols except @ and . in your email. Try again.\n");
                continue;
            }
            //Validation: Prevent duplicate email IDs.

            index=comparing_strings(addressBook,email,3);
            if(index!=-1){
                printf("Mail id exist⚠️ Enter the correct mail id!\n");
                continue;
                }
            break;
            
    }while(1);

    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);
    (addressBook->contactCount)++;
    printf("SUCCESSFULLY CREATED ✅");
	
}

void searchContact(AddressBook *addressBook) 
{
    int choice,index,flag;
    int size=addressBook->contactCount;
    char name[50],phone[20],email[20];
    do{
    // Validate search input based on user choice (name, phone, or email).
    printf("1.🔍 search by name\n2.🔍 search by phone number\n3.🔍 search by email\n4.🔚 Exit\n");
    printf("✍️  Enter your choice: ");
    scanf(" %d",&choice);
    switch(choice){
        case 1:
        printf("Enter Name 🔍: ");
        scanf(" %[^\n]",name);
        index=comparing_strings(addressBook,name,choice);
        
        if(index!=-1){
            printf("----------------------------------------------------------------------------------\n");
            printf("%-6s %-35s %-15s %-30s\n", "SL.No", "Name", "Phone", "Email");
            printf("----------------------------------------------------------------------------------\n");
            for(int i=0;i<size;i++){
                if(strcasecmp(addressBook->contacts[i].name,name)==0){
                    printf("%-6d %-35s %-15s %-30s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            }
            printf("----------------------------------------------------------------------------------\n");
        }
        else{
            printf("Contact not found ⚠️\n");// Displays 'Contact not found' for invalid or non-existent entries.
        }
        break;
        case 2:
        flag=0;
        // Ensures phone number entered during search is valid (10 digits, numeric only).
        do{
        printf("Enter phone number 🔍: ");
        scanf(" %s",phone);
        int len=strlen(phone);
        if(len!=10){
            printf("Enter the 10 digit number\n");
            continue;
        }
        flag=1;
        for(int i=0;i<len;i++){
            if(phone[i]<'0'||phone[i]>'9'){
                flag=0;
                break;
            }
        }
        if(flag==0){
            printf("Enter only digits ⚠️!!\n");
            continue;
        }
    }while(flag==0);
    
        index=comparing_strings(addressBook,phone,choice);
        if(index!=-1){
            printf("----------------------------------------------------------------------------------\n");
            printf("%-6s %-35s %-15s %-30s\n", "SL.No", "Name", "Phone", "Email");
            printf("----------------------------------------------------------------------------------\n");
            printf("%-6d %-35s %-15s %-30s\n",index,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
            printf("----------------------------------------------------------------------------------\n");

        }
        else{
            printf("Contact not found ⚠️\n");
        }
    
        break;
        case 3:
        printf("Enter email id 🔍: ");
        scanf(" %s",email);
        index=comparing_strings(addressBook,email,choice);
        if(index!=-1){
            printf("----------------------------------------------------------------------------------\n");
            printf("%-6s %-35s %-15s %-30s\n", "SL.No", "Name", "Phone", "Email");
            printf("----------------------------------------------------------------------------------\n");
            printf("%-6d %-35s %-15s %-30s\n",index,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
            printf("----------------------------------------------------------------------------------\n");
        }
        else{
            printf("Contact not found⚠️\n");
        }
        break;
        case 4:
        break;
        default:
        printf("Invalid Choice 🚫. please try again!\n");//This gets printed if the user enters the invalid choice
    }
    
    
}while(choice!=4);
        
}

void editContact(AddressBook *addressBook)
{
    int edit_choice,index,flag,serial_no,flag1,flag2,match_count;
    char name[50],phone[20],email[50];
    int size=addressBook->contactCount;
    int count[size];
    do{
    printf("1.✏️  Edit name\n2.✏️  Edit phone number\n3.✏️  Edit email\n4.🔚 Exit\n");
    printf("✍️  Enter your choice: ");
    scanf("%d",&edit_choice);
    getchar();    
    switch(edit_choice){
        case 1:
        flag=0;
        flag1=0;
        match_count=0;
        do{
            printf("Enter Name to be edited ✏️  :");
            scanf(" %[^\n]",name);
            flag1=0;

            int temp=0;
            // Validation: Checks if contact exists before editing.
            for(int i=0;i<size;i++){
                if(strcasecmp(addressBook->contacts[i].name,name)==0){
                    temp+=1;
                }
            }
            if(temp==1){
                index=comparing_strings(addressBook,name,edit_choice);
                if(index!=-1){
                    printf("✍️  Enter New name: ");
                    scanf(" %[^\n]",name);
                    strcpy(addressBook->contacts[index].name,name);
                    flag1=1;
                    printf("SUCCESSFULLY EDITED ✅\n");
                }
            }
            else if(temp==0){
                printf("Contact not found,enter the correct one ⚠️\n" );
            }
            else{
                match_count=0;
                printf("----------------------------------------------------------------------------------\n");
                printf("%-6s %-35s %-15s %-30s\n", "SL.No", "Name", "Phone", "Email");
                printf("----------------------------------------------------------------------------------\n");
                for(int i=0;i<size;i++){
                    if(strcasecmp(addressBook->contacts[i].name,name)==0){
                        printf("%-6d %-35s %-15s %-30s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        flag1=1;
                        count[match_count]=i;
                        match_count+=1;
                    }
                }
                printf("----------------------------------------------------------------------------------\n");
                // Validations: If multiple contacts share the same name, allows user to choose via serial number.
                do{
                    printf("Enter the serial number of the contact u want to edit ✏️  : ");
                    scanf("%d",&serial_no);
                    getchar();
                    flag=0;                        
                    for(int i=0;i<match_count;i++){
                            if(count[i]==serial_no){
                                printf("✍️  Enter New Name: ");
                                scanf(" %[^\n]",name);
                                strcpy(addressBook->contacts[count[i]].name,name);
                                flag=1;
                                printf("SUCCESSFULLY EDITED ✅\n");
                                break;
                            } 
                        }
                        if(flag==0){
                            printf("You have entered the wrong serial number 🚫\n");
                        }
                }while(flag==0);
            }        
    }while(flag1==0);
    break;

   
    case 2:
    flag=0;
    flag1=0;
    match_count=0;
        do{
            printf("Enter phone number to be edited ✏️  : ");
            scanf(" %s",phone);
            index=comparing_strings(addressBook,phone,edit_choice);
            if(index>=0 && index<size){
                do{
                    char new_phone[20];
                    printf("✍️  Enter New Phone number: ");
                    scanf(" %s",new_phone);
                    int len=strlen(new_phone);
                    flag1=1;
                    // Validations: Ensures new phone number follows 10-digit rule and is not duplicate.
                    if(len!=10){
                        printf("Enter the 10 digit number ⚠️\n");
                        flag1=0;
                        continue;
                    }
                    for(int i=0;i<len;i++){
                        if(new_phone[i]<'0'||new_phone[i]>'9'){
                            printf("Enter only digits ⚠️\n");
                            flag1=0;
                            break;
                        }
                    }
                    for(int i=0;i<size;i++){
                        if(i!=index && (strcmp(addressBook->contacts[i].phone,new_phone)==0)){
                            printf("The entered number already exist ⚠️ please enter the different one!\n");
                            flag1=0;
                            break;
                        }
                    }
                    if(flag1){
                        strcpy(addressBook->contacts[index].phone,new_phone);
                        printf("SUCCESSFULLY EDITED ✅\n");
                    }
                }while(flag1==0);
                
                flag=1;
            }
            else{
                printf("Contact not found,enter the correct one ⚠️\n" );
            }
        }while(flag==0);
        break;
    case 3:
    flag=0;
    flag1=0;
    flag2=0;
    match_count=0;
         do{
            printf("Enter Email id to be edited ✏️  : ");
            scanf(" %s",email);
            index=comparing_strings(addressBook,email,edit_choice);
            if(index!=-1 && index<size){
                flag=1;
                do{
                flag1=0;
                flag2=0;
                char new_email[20];
                //Validations: Ensures new email follows correct format and is unique.
                printf("✍️  Enter New Email id 📩: ");
                scanf(" %s",new_email);
                int len=strlen(new_email);
                flag1=0;
                if((strchr(new_email,'@')==NULL)||(strstr(new_email,".com")==NULL)){
                    printf("Enter a valid mail id⚠️\n");
                    flag1=0;
                    continue;
                }
                //flag1=1;
                if((new_email[0]>='a'&&new_email[0]<='z')||(new_email[0]>='0'&&(new_email[0]<='9'))){
                    flag1=1;
                }
                else{
                    flag1=0;
                }
                
                for(int i=1;i<len;i++){
                    //flag1=1;
                    if(new_email[i]>='A'&&new_email[i]<='Z'){
                        flag1=0;
                        break;
                    }
                    else{
                        if((new_email[i]<'a'||new_email[i]>'z')&&new_email[i]!='@'&&new_email[i]!='.'&&(new_email[i]<'0'||new_email[i]>'9')){
                            flag1=0;
                            break;
                        }
                    }
                }
                for(int i=0;i<size;i++){
                    if(i!=index && (strcmp(addressBook->contacts[i].email,new_email)==0)){
                        flag2=1;
                        break;
                    }
                }
                if(flag2==1){
                    printf("The entered mail id already exist -please enter a different one!\n");
                }
                else if(flag1==0){
                    printf("Oops☹️! avoid capitals ❌ , special symbols except @ and . in your email. Try again.\n");
                    continue;
                }
                else{
                    strcpy(addressBook->contacts[index].email,new_email);
                    printf("SUCCESSFULLY EDITED ✅\n");
                }
            }while(flag1==0||flag2==1);
            break;
            }
            else{
                printf("Contact not found,enter the correct one ⚠️\n" );
            }
        }while(flag==0);
        break;
        case 4:
        break;
        default:
        printf("Invalid Choice 🚫. please try again!\n");//This gets printed if the user enters the invalid choice
    }
}while(edit_choice!=4);
    
   
 
	/* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook)
{
    char name[20],phone[20],email[20];
    int index,flag=0,choice,flag1,serial_no,match_count=0;
    //int size=addressBook->contactCount;
    int count[addressBook->contactCount];
    do{
    printf("1.🗑️  Delete by name\n2.🗑️  Delete by phone number\n3.🗑️  Delete by email\n4.🔚 Exit\n");
    printf("✍️  Enter your choice: ");
    scanf(" %d",&choice);
    switch(choice){
        case 1:
        
        do{
            printf("Enter the Name to be deleted 🗑️: ");
            scanf(" %[^\n]",name);
            flag1=0;
            int temp=0;
            // Validation: Ensures contact exists before deletion.
            for(int i=0;i<addressBook->contactCount;i++){
                if(strcasecmp(addressBook->contacts[i].name,name)==0){
                    temp+=1;
                }
            }
            // Prevents deletion of non-existent contacts.
            if(temp==0){
                printf("Contact not found,enter the correct one ⚠️\n" );
            }
            else if(temp==1){
                index=comparing_strings(addressBook,name,choice);
                if(index!=-1){
                    for(int i=index;i<addressBook->contactCount-1;i++){
                        addressBook->contacts[i]=addressBook->contacts[i+1];
                    }
                    (addressBook->contactCount)--;
                    printf("SUCCESSFULLY DELETED ✅\n");
                    flag1=1;
                }
            }
            else{
                match_count=0;
                printf("----------------------------------------------------------------------------------\n");
                printf("%-6s %-35s %-15s %-30s\n", "SL.No", "Name", "Phone", "Email");
                printf("----------------------------------------------------------------------------------\n");
                for(int i=0;i<addressBook->contactCount;i++){
                    if(strcasecmp(addressBook->contacts[i].name,name)==0){
                        printf("%-6d %-35s %-15s %-30s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        flag1=1;
                        count[match_count]=i;
                        match_count+=1;
                    }
                }
                printf("----------------------------------------------------------------------------------\n");
                // Handles multiple contacts with same name using serial number confirmation.
                do{
                    printf("Enter the serial number of the contact to be deleted 🗑️: ");
                    scanf("%d",&serial_no);
                    getchar();
                    flag=0;
                    for(int i=0;i<match_count;i++){
                            if(count[i]==serial_no){
                                for(int i=serial_no;i<addressBook->contactCount-1;i++){
                                    addressBook->contacts[i]=addressBook->contacts[i+1];
                                }
                                (addressBook->contactCount)--;
                                printf("SUCCESSFULLY DELETED ✅\n");

                                flag=1;
                                break;
                            }
                        }
                        if(flag==0){
                            printf("You have entered the wrong serial number 🚫\n");
                            continue;
                        }
                    
            }while(flag==0);
            
        }
    }while(flag1==0);
    break;
        case 2:
        do{
            flag=0;
            printf("Enter the phone number to be deleted 🗑️: ");
            scanf(" %s",phone);
            index=comparing_strings(addressBook,phone,choice);
            if(index!=-1){
                flag=1;
                for(int i=index;i<addressBook->contactCount-1;i++){
                    addressBook->contacts[i]=addressBook->contacts[i+1];
                }
                (addressBook->contactCount)--;
                printf("SUCCESSFULLY DELETED ✅\n");

            }
            if(flag==0){
                printf("Contact not found,enter the correct one ⚠️\n" );
            }
        }while(flag==0);

        break;
        case 3:
         do{
            flag=0;
            printf("Enter the Email id to be deleted 🗑️: ");
            scanf(" %s",email);
            index=comparing_strings(addressBook,email,choice);
            if(index!=-1){
                flag=1;
                for(int i=index;i<addressBook->contactCount-1;i++){
                    addressBook->contacts[i]=addressBook->contacts[i+1];
                }
                (addressBook->contactCount)--;
                printf("SUCCESSFULLY DELETED ✅\n");

            }
            if(flag==0){
                printf("Contact not found,enter the correct one ⚠️\n" );
            }
        }while(flag==0);
        break;
        case 4:
        break;
        default:
        printf("Invalid Choice 🚫. please try again!\n");//This gets printed if the user enters the invalid choice
    
    }
}while(choice!=4);
    
    
	/* Define the logic for deletecontact */
   
}
