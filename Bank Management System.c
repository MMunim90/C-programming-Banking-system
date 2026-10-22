#include<stdio.h>
#include<string.h>

void create_account();
void deposit_money();
void withdraw_money();
void check_balance();

typedef struct {
    char name[50];
    int acc_no;
    float balance;
} Account;


int main()
{
    while (1)
    {
        int choice;
        int close;

        printf("\n\n*** Bank Management System ***");
        printf("\n1. Create Account");
        printf("\n2. Deposit Money");
        printf("\n3. Withdraw Money");
        printf("\n4. Check Balance");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create_account();
            break;
        case 2:
            deposit_money();
            break;
        case 3:
            withdraw_money();
            break;
        case 4:
            check_balance();
            break;
        case 5:
            printf("\nAre you sure you want to close the program? 1. Yes  2. No: ");
            scanf("%d", &close);
            if(close == 1){
                printf("\nClosing the Bank, Thanks for your visit.\n");
                return 0;
            }
            else{
                printf("\nPlease wait... Returning to the options\n");
                break;
            }
        default:
            printf("\nInvalid choice!");
            break;
        }
    }
}


void create_account(){
    Account acc;
    FILE *file = fopen("Account.dat", "ab+");
    if(file == NULL){
        printf("\nUnable to open file!!!");
        return;
    }

    getchar();

    printf("\nEnter your name: ");
    fgets(acc.name, sizeof(acc.name), stdin);

    int index = strcspn(acc.name, "\n");
    acc.name[index] = '\0';

    printf("\nEnter your account number: ");
    scanf("%d", &acc.acc_no);
    
    acc.balance = 0;

    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);
    printf("\nAccount created successfully!");
}

void deposit_money(){
    printf("\nDeposit Money");
}

void withdraw_money(){
    printf("\nWithdraw Money");
}

void check_balance(){
    printf("\nCheck Balance");
}