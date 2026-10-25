#include <stdio.h>
#include <string.h>

void create_account();
void deposit_money();
void withdraw_money();
void check_balance();

const char *ACCOUNT_FILE = "Account.dat";
typedef struct
{
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

        printf("\n\n*** Bank Management System ***\n");
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
            if (close == 1)
            {
                printf("\nClosing the Bank, Thanks for your visit.\n");
                return 0;
            }
            else
            {
                printf("\nPlease wait... Returning to the options\n");
                break;
            }
        default:
            printf("\nInvalid choice!");
            break;
        }
    }
}

void create_account()
{
    Account acc;
    FILE *file = fopen(ACCOUNT_FILE, "ab+");
    if (file == NULL)
    {
        printf("\nUnable to open file!!!");
        return;
    }

    getchar();

    printf("\nEnter your name: ");
    fgets(acc.name, sizeof(acc.name), stdin);

    int index = strcspn(acc.name, "\n");
    acc.name[index] = '\0';

    int acc_n;
    printf("Enter your account number: ");
    scanf("%d", &acc_n);

    while (fread(&acc, sizeof(acc), 1, file))
    {
        if (acc.acc_no == acc_n)
        {
            printf("\nThis account number is already available. Try with another one.");
            fclose(file);
            return;
        }
    }

    acc.acc_no = acc_n;

    acc.balance = 0;

    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);
    printf("\nAccount created successfully!");
}

void deposit_money()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL)
    {
        printf("\nUnable to open file!!!");
        return;
    }

    int acc_no;
    float deposit_money;
    Account acc_r;
    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);
    printf("Enter amount to deposit: ");
    scanf("%f", &deposit_money);
    
    while (fread(&acc_r, sizeof(acc_r), 1, file))
    {
        if(acc_r.acc_no == acc_no){
            acc_r.balance += deposit_money;
            fseek(file, -sizeof(acc_r), SEEK_CUR);
            fwrite(&acc_r, sizeof(acc_r), 1, file);
            fclose(file);
            printf("\nSuccessfully deposited %.2f Taka. New balance is %.2f Taka.", deposit_money, acc_r.balance);
            return;
        }
    }
    
    fclose(file);
    printf("\nMoney could not be deposited as the Account No: %d was not found in records.\n", acc_no);
}

void withdraw_money()
{
    printf("\nWithdraw Money");
}

void check_balance()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb");
    if (file == NULL)
    {
        printf("\nUnable to open file!!!");
        return;
    }

    int acc_no;
    Account acc_read;
    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);

    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_read.acc_no == acc_no)
        {
            printf("\nYour current balance is %.2f Taka", acc_read.balance);
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("\nAccount No: %d was not found.\n", acc_no);
}