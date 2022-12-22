#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define aosv_size 50 //array of structure variable size
#define ADMIN_PASS_SIZE 50 //array password limitation
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

//Utilites
int passwordLoginAccess(char str[]); //pass cheacker/verify
void createResetkey(); //create a backup key for admin
void delay();// create time delay

// Interfaces and login operation
void forntInterface();

//Admin function and login
void admin();
void adminLogin();
void adminAccessOption();
void adminPassReset();
void adminUserpassReset();
void bankStatement();



//File operation functions admin
void create();
void append();
void display();
void search_id();
void update();
void delete_account();


//user
void userAcces(); // check password and user id match
void user(char name[] ,int ID); // main operation for user
int passwordLoginAccessUser(char str[], int ID);
void userDeposite(int ID);
void userWithdraw(int ID);
void userShowInfo(int ID);






// Main function
int main(){

    createResetkey();
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
        printf("\nEnter account Id: ");
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

    printf("\nID\tName\t\tBalance\t\t Age\t\tCreated");
    printf("\n--------------------------------------------------------------------------\n");
    while(fread(&person, sizeof(accHolder), 1, fp)){
        printf("\n%d\t%s\t%15.3f\t\t%d\t%10d/%d/%d\n",
               person.account_id,
               person.name,
               person.balance,
               person.age,
               person.doc.day,
               person.doc.month,
               person.doc.year);
    }
    fclose(fp);

}


void append(){
    FILE *fp;
    int accsize = 0;
    printf("\t\t\t\tBank Management System (ADMIN) \n");
    printf("\t\t\t----------------------------------------------\n\n\n");
    printf("\n\nHow many account do you want to create: ");
    scanf("%d", &accsize);
    accHolder person[accsize];
    fp = fopen("accountrecords.txt", "a");
    for(int i=0; i<accsize; i++){
        printf("\nEnter account Id: ");
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

void search_id(){
    accHolder person;
    FILE *fp;
    fp = fopen("accountrecords.txt", "r");

    int id, found = 0;
    printf("Enter account Id to search: ");
    scanf("%d", &id);
    printf("\nID\tName\t\tBalance\t\tAge\t\tCreated");
    printf("\n--------------------------------------------------------------------------\n");
    while(fread(&person, sizeof(accHolder), 1, fp)){
        if(person.account_id == id){
            found = 1;
            printf("\n%d\t%s\t%15.3f\t\t%d\t%10d/%d/%d\n",
               person.account_id,
               person.name,
               person.balance,
               person.age,
               person.doc.day,
               person.doc.month,
               person.doc.year);
        }

    }
    if(!found){
        system("cls");
        printf("\n Id: %d, Not Found\n", id);
    }

    fclose(fp);
}

void delete_account(){
    accHolder person;
    FILE *fp, *fp1;
    fp = fopen("accountrecords.txt", "r");
    fp1 = fopen("temp.txt", "w");
    int id, found = 0;
    printf("Enter Id to delete: ");
    scanf("%d", &id);
    while(fread(&person, sizeof(accHolder), 1, fp)){
        if(person.account_id == id){
            found = 1;
        }else
            fwrite(&person, sizeof(accHolder), 1, fp1);
    }
    fclose(fp);
    fclose(fp1);
    if(found){
        fp1 = fopen("temp.txt", "r");
        fp = fopen("accountrecords.txt", "w");

        while(fread(&person, sizeof(accHolder), 1, fp1)){
            fwrite(&person, sizeof(accHolder), 1, fp);
        }

        fclose(fp);
        fclose(fp1);
        printf("\nId: %d deleted permanently\n", id);
    }else{
        printf("\nRecord not found!\n");
    }
}

void update(){
    accHolder person;
    FILE *fp, *fp1;
    fp = fopen("accountrecords.txt", "r");
    fp1 = fopen("temp.txt", "w");
    int id, found = 0;
    printf("Enter Id to update: ");
    scanf("%d", &id);
    while(fread(&person, sizeof(accHolder), 1, fp)){
        if(person.account_id == id){
            found = 1;
            fflush(stdin);
            printf("\nEnter new name: ");
            scanf("%[^\n]s", person.name);
            printf("Enter new age: ");
            scanf("%d", &person.age);
            printf("Enter account created new date: (day/month/year): ");
            scanf("%d %d %d", &person.doc.day, &person.doc.month, &person.doc.year);
            printf("Enter new balance: ");
            scanf("%f", &person.balance);
        }

        fwrite(&person, sizeof(accHolder), 1, fp1);
    }
    fclose(fp);
    fclose(fp1);
    if(found){
        fp1 = fopen("temp.txt", "r");
        fp = fopen("accountrecords.txt", "w");

        while(fread(&person, sizeof(accHolder), 1, fp1)){
            fwrite(&person, sizeof(accHolder), 1, fp);
        }

        fclose(fp);
        fclose(fp1);
    }else{
        printf("\nRecord not found!\n");
    }
}

void bankStatement(){
    accHolder person;
    FILE *fp = fopen("accountrecords.txt", "r");

    float totalBankAmmount = 0;
    printf("\t\t\t\tBank Management System (ADMIN) \n");
    printf("\t\t\t----------------------------------------------\n\n\n");
    printf("");
    while(fread(&person, sizeof(accHolder), 1, fp)){
        totalBankAmmount += person.balance;
        printf("\nID:%d, Name: %s, Balance: %f", person.account_id, person.name, person.balance);
    }
    fclose(fp);
    printf("\n\nTotal bank reserve: %lf TK.", totalBankAmmount);
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
        printf("\n5.UPDATE ACCOUNT");
        printf("\n6.DELETE ACCOUNT");
        printf("\n7.PASSWORD RESET OF ACCOUNT.");
        printf("\n8.Bank Statement.");
        printf("\n9.Back");
        printf("\n0.EXIT");
        printf("\n\n\nEnter 0-9 to operate the system.\n\n");
        printf("\n\nInput: ");
        scanf("%d", &ch);

        switch(ch){
        case 1:
            system("cls");
            create();
            break;
        case 2:
            system("cls");
            append();
            break;
        case 3:
            system("cls");
            display();
            break;
        case 4:
            system("cls");
            search_id();
            break;
        case 5:
            system("cls");
            update();
            break;
        case 6:
            system("cls");
            delete_account();
            break;
        case 7:
            system("cls");
            adminUserpassReset();
            break;
        case 8:
            system("cls");
            bankStatement();
            break;
        case 9:
            system("cls");
            adminAccessOption();
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

    printf("\nEnter password reset key( created file in your program diractory): "); // super key: QJGWaZzePAPFBRo
    fflush(stdin);
    scanf("%[^\n]s", super);

    if(!strcmp(super, SUPERKEY)){
        passInput:
        system("cls");
        printf("\t\t\t\tBank Management System (password reset)\n");
        printf("\t\t\t-------------------------------------------------\n\n\n");
        printf("Checking reset key.....");
        delay();
        system("cls");
        printf("Reset key accepted..");
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
        printf("\n\nReset key did not match (reset key is in top of the program define section)...");
        delay(); // 3 sec delay
        goto label;
    }


}

void adminUserpassReset(){

    accHolder person;
    FILE *fp, *fp1;
    fp = fopen("accountrecords.txt", "r");
    fp1 = fopen("temp.txt", "w");
    int id, found = 0;
    char userName[aosv_size];
    printf("Enter Id to update password: ");
    scanf("%d", &id);
    while(fread(&person, sizeof(accHolder), 1, fp)){
        if(person.account_id == id){
            found = 1;
            fflush(stdin);
            printf("\nEnter new password of Id: %d, name: %s : ", id, person.name);
            scanf("%[^\n]s", person.password);
            strcpy(userName, person.name);
        }

        fwrite(&person, sizeof(accHolder), 1, fp1);
    }
    fclose(fp);
    fclose(fp1);
    if(found){
        fp1 = fopen("temp.txt", "r");
        fp = fopen("accountrecords.txt", "w");

        while(fread(&person, sizeof(accHolder), 1, fp1)){
            fwrite(&person, sizeof(accHolder), 1, fp);
        }
        printf("\nPassword reset successful for id: %d, name: %s", id, userName);
        fclose(fp);
        fclose(fp1);
    }else{
        printf("\nRecord not found!\n");
    }

}


void user(char name[], int ID){
        system("cls");
        printf("Login........");
        delay(); // delay for 3 second
        printf("User Login....");

        system("cls");
        printf("User Login Success");
        delay();
        system("cls");
        printf("\t\t\t\tBank Management System ( %s, %d ) \n", name, ID );
        printf("\t\t\t-------------------------------------------------\n\n\n");
        int ch;
    do{
        printf("\n");
        printf("\n1.DIPOSITE AMMOUNT.");
        printf("\n2.WIDTHDRAW AMMOUNT.");
        printf("\n3.SHOW INFORMATION.");
        printf("\n4.BACK.");
        printf("\n0.EXIT.");
        printf("\n\n\nEnter 0-4 to operate the system.\n\n");
        printf("\n\nInput: ");
        scanf("%d", &ch);

        switch(ch){
        case 1:
            system("cls");
            userDeposite(ID);
            break;
        case 2:
            system("cls");
            userWithdraw(ID);
            break;
        case 3:
            system("cls");
            userShowInfo(ID);
            break;
        case 4:
            system("cls");
            forntInterface();
            break;
        case 0:
            return 0;
        }

    }while(1);
}

int passwordLoginAccessUser(char pass[], int ID){ //password matching code only for admin login, password is stored in file.
    accHolder person;
    FILE *passfile;
    passfile = fopen("accountrecords.txt", "r");
    if(passfile==NULL){
          printf("Error, pass not found.");
          fclose(passfile);
          delay();
          forntInterface();// if adminpass.txt file missing then create a file with ,"admin123" password.
    }
    int passSame=0;
    while(fread(&person, sizeof(accHolder), 1, passfile)){
        if(person.account_id == ID){
            if(!strcmp(pass, person.password) ){
            passSame = 1;
            }
        }
    }

    fclose(passfile);
    if(passSame){
        return 1;
    }else
        return 0;
}

void userAcces(){

    accHolder person;
    FILE *fp;
    fp = fopen("accountrecords.txt", "r");

    int userid, found = 0;
    char userpass[ADMIN_PASS_SIZE];
    char userName[aosv_size];
    if(fp!=NULL){

        printf("User ID: ");
        scanf("%d", &userid);

        while(fread(&person, sizeof(accHolder), 1, fp)){
            if(person.account_id == userid){
                found = 1;
                strcpy(userName, person.name);
            }
        }
        fclose(fp);

        if(found){
            printf("\nEnter passWord: ");
            fflush(stdin);
            scanf("%[^\n]s", &userpass);
            int access = passwordLoginAccessUser(userpass, userid);
            if(access){
                user(userName, userid); // go to user operations
            }else{
                printf("\n\nPassword not matched");
                delay();
                forntInterface();
            }

        }
        else{
            printf("\n\nID not found");
            delay();
            forntInterface();
        }

    }
    else{
        fclose(fp);
        printf("\nNo account found.Create account with bank admin.");
        delay();
        forntInterface();
    }

}

void userShowInfo(int ID){
    accHolder person;
    FILE *fp = fopen("accountrecords.txt", "r");

    printf("\nID\tName\t\tBalance\t\t Age\t\tCreated");
    printf("\n--------------------------------------------------------------------------\n");
    while(fread(&person, sizeof(accHolder), 1, fp)){
            if(person.account_id == ID){
               printf("\n%d\t%s\t%15.3f\t\t%d\t%10d/%d/%d\n",
               person.account_id,
               person.name,
               person.balance,
               person.age,
               person.doc.day,
               person.doc.month,
               person.doc.year);
            }
    }
}

void userDeposite(int ID){
  accHolder person;
    FILE *fp, *fp1;
    fp = fopen("accountrecords.txt", "r");
    fp1 = fopen("temp.txt", "w");
    int found = 0;
    float ammount = 0;
    while(fread(&person, sizeof(accHolder), 1, fp)){
        if(person.account_id == ID){
            found = 1;
            printf("\nEnter amount to deposite: ");
            fflush(stdin);
            scanf("%f", &ammount);
            person.balance += ammount;
        }

        fwrite(&person, sizeof(accHolder), 1, fp1);
    }
    fclose(fp);
    fclose(fp1);
    if(found){
        fp1 = fopen("temp.txt", "r");
        fp = fopen("accountrecords.txt", "w");

        while(fread(&person, sizeof(accHolder), 1, fp1)){
            fwrite(&person, sizeof(accHolder), 1, fp);
        }
        printf("%f ammount successfully deposited.", ammount);
        fclose(fp);
        fclose(fp1);
        delay();
    }else{
        printf("\nRecord not found!\n");
    }
}

void userWithdraw(int ID){
    accHolder person;
    FILE *fp, *fp1;
    fp = fopen("accountrecords.txt", "r");
    fp1 = fopen("temp.txt", "w");
    int found = 0;
    float ammount = 0;
    while(fread(&person, sizeof(accHolder), 1, fp)){
        if(person.account_id == ID){
            found = 1;
            printf("\nEnter amount to deposite: ");
            fflush(stdin);
            scanf("%f", &ammount);
            if(person.balance >= ammount){
                person.balance -= ammount;
            }else{
                printf("\nIn insufficient ammount.");
                delay();
            }
        }

        fwrite(&person, sizeof(accHolder), 1, fp1);
    }
    fclose(fp);
    fclose(fp1);
    if(found){
        fp1 = fopen("temp.txt", "r");
        fp = fopen("accountrecords.txt", "w");

        while(fread(&person, sizeof(accHolder), 1, fp1)){
            fwrite(&person, sizeof(accHolder), 1, fp);
        }
        printf("%f ammount successfully withdraw.", ammount);
        fclose(fp);
        fclose(fp1);
        delay();
    }else{
        printf("\nRecord not found!\n");
    }
}

//--------------------------------------------------------------------------

//



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
    printf("\n\n\nEnter 0-2 to operate the system.\n\n");
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
            userAcces();
            break;
        case 0:
            exit(1);
        default:
            system("cls");
            goto mainlabel;
        }
    }
    else{
        printf("\n\nWrong Input");
        delay();
        goto mainlabel;
    }
}




void createResetkey(){ //create a backup key
    FILE * fp = fopen("resetkey.txt", "w");
    fprintf(fp,"%s", SUPERKEY);
    fclose(fp);
}
