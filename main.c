#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define aosv_size 50 //array of structure variable size
#define ADMIN_PASS_SIZE 50
const char SUPERKEY[] = "QJGWaZzePAPFBRo"; //for admin password reset



typedef struct AccountHolderInformations{
    int account_id;
    char name[aosv_size];
    struct date{
        int day;
        int month;
        int year;
    }doc; // date of account creation.
    float balance;
    char password[aosv_size];
    int age;

}accHolder;

// Interfaces and login operation functions
void delay();
void admin();
int passwordLoginAccess(char str[]);
void adminLogin();
void adminAccessOption();
void adminPassReset();
void forntInterface();


//File operation functions
void create();
//void append();
void display();
//void search_id();
//void total_account_number();
//void update();
//void sort_by_name();
//void delete_account();




void user(){
    printf("User login");
}



// Main function
int main(){


    forntInterface();


    return 0;
}




void create(){
    FILE *fp;
    int accsize = 0;
    printf("\t\t\t\tBank Management System (ADMIN) \n");
    printf("\t\t\t----------------------------------------------\n\n\n");
    printf("\n\nHow many account do you want to create: ");
    scanf("%d", &accsize);
    accHolder person[accsize];
    fp = fopen("accountrecords.txt", "w");
    for(int i=0; i<accsize; i++){
        printf("Enter account Id: ");
        scanf("%d", &person[i].account_id);
        printf("Enter account holder name: ");
        fflush(stdin);
        scanf("%[^\n]s", person[i].name);
        printf("Enter account register date. Ex,(day month year) with spaces: ");
        scanf("%d %d %d", &person[i].doc.day, &person[i].doc.month, &person[i].doc.year);
        printf("Account holder age: ");
        scanf("%d", &person[i].age);
        printf("Amount to deposite: ");
        scanf("%f", &person[i].balance);
        printf("Create pass for account holder: ");
        scanf("%s", person[i].password);
        fwrite(&person[i], sizeof(accHolder), 1, fp);
    }
    fclose(fp);
}


void display(){
    accHolder person;
    FILE *fp = fopen("accountrecords.txt", "r");

    printf("\nID\tName\tAge\t\Created Date\tBalance\n");
    while(fread(&person, sizeof(accHolder), 1, fp)){
        printf("%d\t%s\t%d\t%.4f\t%d %d %d\n",
               person.account_id,
               person.name,
               person.age,
               person.balance,
               person.doc.day,
               person.doc.month,
               person.doc.year);
    }

}



void delay(){
    for(int i=0, j=0; i<1000000000; i++){ // 3s delay timer
       j=i;
    }
}

void admin(){ //admin string operations
        system("cls");
        printf("\t\t\t\tBank Management System (ADMIN) \n");
        printf("\t\t\t-------------------------------------------------\n\n\n");
        printf("Login........");
        delay(); // delay for 3 second
        printf("Admin Login....");

        system("cls");
        printf("Admin Login Success");

        system("cls");
        printf("\t\t\t\tBank Management System (ADMIN) \n");
        printf("\t\t\t--------------------------------------------\n\n\n");
        int ch;
    do{
        printf("\n");
        printf("\n1.CREATE ACCOUNT(previous data will lost) ");
        printf("\n2.ADD ACCOUNT(append account) ");
        printf("\n3.DISPLAY ACCOUNT LIST");
        printf("\n4.SEARCH ACCOUNT ID");
        printf("\n5.DISPLAY TOTAL ACCOUNT NUMBER");
        printf("\n6.UPDATE ACCOUNT");
        printf("\n7.SORT ACCOUNT BY NAME");
        printf("\n8.DELETE ACCOUNT");
        printf("\n0.EXIT");
        printf("\n\nInput: ");
        scanf("%d", &ch);

        switch(ch){
        case 1:
            system("cls");
            create();
            break;
        case 2:
            system("cls");
            //append();
            break;
        case 3:
            system("cls");
            display();
            break;
        case 4:
            system("cls");
            //search_id();
            break;
        case 5:
            system("cls");
            //total_account_number();
            break;
        case 6:
            //update();
            break;
        case 7:
            //sort_by_name();
            break;
        case 8:
            //delete_account();
            break;
        }

    }while(ch!=0);



}

int passwordLoginAccess(char str[]){ //password matching code only for admin login, password is stored in file.

    char pass[50];
    int status = 0;
    FILE *passfile;

    passfile = fopen("adminpass.txt", "r");
    if(passfile==NULL){

         adminAccessOption(); // if adminpass.txt file missing then create a file with ,"admin123" password.

    }

    fscanf(passfile, "%s", pass);

    int passSame = strcmp(str, pass); // matching password

    fclose(passfile);
    if(!passSame){
        return 1;
    }else
        return 0;
}

void adminLogin(){ //check admin password


        int access;
        char password[ADMIN_PASS_SIZE];
        label:
        system("cls");
        printf("\t\t\t\tBank Management System (Admin panel)\n");
        printf("\t\t\t-------------------------------------------------\n\n\n");
        FILE *fp;
        fp = fopen("adminpass.txt", "r");
        if(fp==NULL){
            fclose(fp);
            char _pass[ADMIN_PASS_SIZE];
            printf("Create a new password For admin: ");
            fflush(stdin);
            scanf("%[^\n]s", _pass);
            fp = fopen("adminpass.txt", "w");
            fprintf(fp, "%s", _pass);
            fclose(fp);
            adminAccessOption();
        }

        printf("Enter admin password: ");
        fflush(stdin);
        scanf("%[^\n]s", password);
        access = passwordLoginAccess(password);

        if(access){
            admin();
        }else{
            system("cls");
            int key;
            printf("\t\t\t\tBank Management System (Admin panel)\n");
            printf("\t\t\t-------------------------------------------------\n\n\n\n");
            printf("\nWrongPassword\n");
            printf("\n1 Reset password.\n");
            printf("\n2 Retry login.\n");
            printf("\n3.Go to back.");
            printf("\n\n\nEnter 0-3 to operate the system.\n\n");
            printf("\n\nInput: ");
            scanf("%d", &key);
                if(key==1){
                    adminPassReset(); //reset password
                }
                else if(key==2)
                    goto label;
                else if(key==3)
                    adminAccessOption();
                else
                    goto label;
        }
}

void adminAccessOption(){ //options for login
    int status;
    labelAccess:
    system("cls");
    printf("\t\t\t\tBank Management System\n");
    printf("\t\t\t-----------------------------------\n\n\n");
    printf("\n\n1.Enter admin Panel.");
    printf("\n\n2.Reset PassWord.");
    printf("\n\n3.Go to back.");
    printf("\n\n0.Exit.");
    printf("\n\n\nEnter 0-3 to operate the system.\n\n");
    printf("Input: ");
    scanf("%d", &status);

    switch(status){
    case 1:
        adminLogin();
        break;
    case 2:
        adminPassReset();
        break;
    case 3:
        forntInterface();
        break;
    case 0:
        exit(1);
        break;
    default:
        goto labelAccess;
    }


}

void adminPassReset(){ //admin pass reset
    char pass[ADMIN_PASS_SIZE], pass2[ADMIN_PASS_SIZE];
    char super[50];
    label:
    system("cls");
    printf("\t\t\t\tBank Management System (password reset)\n");
    printf("\t\t\t-------------------------------------------------\n\n\n");

    printf("\nEnter Super key: "); // super key: QJGWaZzePAPFBRo
    fflush(stdin);
    scanf("%[^\n]s", super);

    if(!strcmp(super, SUPERKEY)){
        passInput:
        system("cls");
        printf("\t\t\t\tBank Management System (password reset)\n");
        printf("\t\t\t-------------------------------------------------\n\n\n");
        printf("Checking super key.....");
        delay();
        system("cls");
        printf("Super key accepted..");
        delay();
        system("cls");
        printf("\t\t\t\tBank Management System (password reset)\n");
        printf("\t\t\t-------------------------------------------------\n\n\n");
        printf("\n\n\nEnter new password: ");
        fflush(stdin);
        scanf("%[^\n]s", pass);
        printf("Confirm password: ");
        fflush(stdin);
        scanf("%[^\n]s", pass2);

        if(!strcmp(pass2, pass)){
            FILE *fp = fopen("adminpass.txt", "w");
            fprintf(fp, "%s", pass);
            fclose(fp);
            system("cls");
            printf("\t\t\t\tBank Management System (password reset)\n");
            printf("\t\t\t-------------------------------------------------\n\n\n");
            printf("\nPassword is successfully reset!.");
            delay(); //3 sec delay
            adminAccessOption();
        }
        else{
            system("cls");
            printf("\t\t\t\tBank Management System (password reset)\n");
            printf("\t\t\t-------------------------------------------------\n\n\n");
            printf("Password didn't match. try again");
            delay();
            goto passInput;
        }
    }else{
        system("cls");
        printf("\n\nSuper key didnt match (super key is in top of the program define section)...");
        delay(); // 3 sec delay
        goto label;
    }


}

void forntInterface(){ //main panel, starter interface

    int loginSelection = 1;
    mainlabel:
    system("cls");
    printf("\t\t\t\tBank Management System\n");
    printf("\t\t\t-----------------------------------\n\n\n");
    printf("\n\n\nLogin As: \n");
    printf("----------\n");
    printf("\n1.Admin\n");
    printf("\n2.User\n");
    printf("\n0.Exit");
    printf("\n\n\nEnter 0-2 to operate the sy0stem.\n\n");
    printf("Input: ");
    scanf("%d", &loginSelection);



    if(loginSelection>=0 && loginSelection <=9){
        switch(loginSelection){
        case 1:
            system("cls");
            adminAccessOption();
            break;
        case 2:
            system("cls");
            user();
            break;
        case 0:
            exit(1);
        default:
            system("cls");
            goto mainlabel;
        }
    }
}









