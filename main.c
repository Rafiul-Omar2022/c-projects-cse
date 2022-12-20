#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ADMIN_PASS_SIZE 50
const char SUPERKEY[] = "QJGWaZzePAPFBRo"; //for admin password reset

void delay(){
    for(int i=0, j=0; i<1000000000; i++){ // 3s delay timer
       j=i;
    }
}

void admin(){
        system("cls");
        printf("\t\t\t\tBank Management System (ADMIN) \n");
        printf("\t\t\t---------------------------------------\n\n\n");
        printf("Login........");
        delay(); // delay for 3 second
        printf("Admin Login....");

        system("cls");
        printf("Admin Login Success");

        system("cls");
        printf("\t\t\t\tBank Management System (ADMIN) \n");
        printf("\t\t\t---------------------------------------\n\n\n");
        printf("\n1.CREATE ACCOUNT(previous data will lost) ");
        printf("\n2.ADD ACCOUNT(append account) ");
        printf("\n3.DISPLAY ACCOUNT LIST");
        printf("\n4.SEARCH ACCOUNT ID");
        printf("\n5.DISPLAY TOTAL ACCOUNT NUMBER");
        printf("\n6.UPDATE ACCOUNT");
        printf("\n7.SORT ACCOUNT BY NAME");
        printf("\n8.DELETE ACCOUNT");
        printf("\n0.EXIT");
        printf("\n\n\nEnter 0-2 to operate the sy0stem.\n\n");
        printf("Input: ");



}

int passwordLoginAccess(char str[]){ //password matching code only for admin login, password is stored in file.

    char pass[50];
    int status = 0;
    FILE *passfile = fopen("adminpass.txt", "r");

    if(passfile==NULL){
         printf("Error! Login with password");
         exit(1);
    }

    fscanf(passfile, "%s", pass);

    int passSame = strcmp(str, pass); // matching password

    fclose(passfile);
    if(!passSame){
        return 1;
    }else
        return 0;
}

void adminLogin(){

        int access;
        char password[ADMIN_PASS_SIZE];
        label:
        system("cls");
        printf("\t\t\t\tBank Management System (Admin panel)\n");
        printf("\t\t\t-------------------------------------------------\n\n\n");
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
            printf("\nWrongPassWord\n");
            printf("\nPress 1 to reset password\n");
            printf("\nPress 2 to retry");
            printf("\n\nInput: ");
            scanf("%d", &key);
                if(key==1){
                    adminPassReset(); //reset password
                }
                else if(key==2)
                    goto label;
                else
                    goto label;
        }
}

void adminAccessOption(){
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


void adminPassReset(){
    char pass[ADMIN_PASS_SIZE], pass2[ADMIN_PASS_SIZE];
    char super[50];
    label:
    system("cls");
    FILE *fp = fopen("adminpass.txt", "w");
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
            fclose(fp);
            printf("\t\t\t\tBank Management System (password reset)\n");
            printf("\t\t\t-------------------------------------------------\n\n\n");
            printf("Password didn't match. try again");
            delay();
            goto passInput;
        }
    }else{
        system("cls");
        fclose(fp);
        printf("\n\nSuper key didnt match (super key is in top of the program define section)...");
        delay(); // 3 sec delay
        goto label;
    }


}

void forntInterface(){

    int loginSelection = 1;
    mainlabel:
    system("cls");
    printf("\t\t\t\tBank Management System\n");
    printf("\t\t\t-----------------------------------\n\n\n");
    printf("\n\n\nLogin As: \n");
    printf("----------\n");
    printf("\n1.Admin\n");
    printf("\n2.User\n");
    printf("\n0.EXIT");
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


void user(){
    printf("User login");
}

int main(){


    forntInterface();


    return 0;
}










