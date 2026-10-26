#include <stdio.h>
#include <string.h>

void create_account();
void deposit_money();
void withdraw_money();
void check_balance();
void change_pin();

const char *ACCOUNT_FILE = "Account.dat";
typedef struct
{
    char name[50];
    int acc_no;
    int pin;
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
        printf("\n5. Change PIN");
        printf("\n6. Exit");
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
            change_pin();
            break;
        case 6:
            printf("\nAre you sure you want to close the program? 1. \033[32mYes\033[0m  2. \033[31mNo\033[0m: ");
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
            printf("\n\033[31mInvalid choice!\033[0m");
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
        printf("\n\033[31mUnable to open file!!!\033[0m");
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
            printf("\n\033[31mThis account number is already available. Try with another one.\033[0m");
            fclose(file);
            return;
        }
    }

    acc.acc_no = acc_n;

    printf("Enter 5 digit secret PIN: ");
    scanf("%d", &acc.pin);

    acc.balance = 0;

    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);
    printf("\n\033[32mAccount created successfully!\033[0m");
}

void deposit_money()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL)
    {
        printf("\n\033[31mUnable to open file!!!\033[0m");
        return;
    }

    int check;
    int acc_no;
    float deposit_money;
    Account acc_r;
    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);
    printf("Is your account number correct? 1. \033[32mYes\033[0m  2. \033[31mNo\033[0m: ");
    scanf("%d", &check);
    if (check == 1)
    {
        printf("Enter amount to deposit: ");
        scanf("%f", &deposit_money);

        while (fread(&acc_r, sizeof(acc_r), 1, file))
        {
            if (acc_r.acc_no == acc_no)
            {
                acc_r.balance += deposit_money;
                fseek(file, -sizeof(acc_r), SEEK_CUR);
                fwrite(&acc_r, sizeof(acc_r), 1, file);
                fclose(file);
                printf("\n\033[32mSuccessfully deposited %.2f Taka. New balance is %.2f Taka.\033[0m", deposit_money, acc_r.balance);
                return;
            }
        }

        fclose(file);
        printf("\n\033[31mMoney could not be deposited as the Account No: %d was not found in our records.\033[0m\n", acc_no);
    }
    else
    {
        printf("\nPlease wait... Returning to the options\n");
        return;
    }
}

void withdraw_money()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL)
    {
        printf("\n\033[31mUnable to open file!!!\033[0m");
        return;
    }

    int acc_no;
    int secret_pin;
    float withdraw_money;
    Account acc_r;
    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);
    printf("Enter your account secret PIN: ");
    scanf("%d", &secret_pin);
    printf("Enter the amount you want to withdraw: ");
    scanf("%f", &withdraw_money);

    while (fread(&acc_r, sizeof(acc_r), 1, file))
    {
        if (acc_r.acc_no == acc_no)
        {
            if (acc_r.pin == secret_pin)
            {
                if (acc_r.balance >= withdraw_money)
                {
                    acc_r.balance -= withdraw_money;
                    fseek(file, -sizeof(acc_r), SEEK_CUR);
                    fwrite(&acc_r, sizeof(acc_r), 1, file);
                    printf("\n\033[32mSuccessfully withdrawn %.2f Taka. Remaining balance is %.2f Taka.\033[0m", withdraw_money, acc_r.balance);
                }
                else
                {
                    printf("\n\033[31mInsufficient balance!\033[0m");
                }
            }
            else
            {
                printf("\n\033[31mSecret PIN doesn't match!\033[0m");
            }
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("\n\033[31mMoney could not be withdrawn as the Account No: %d was not found in our records.\033[0m\n", acc_no);
}

void check_balance()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb");
    if (file == NULL)
    {
        printf("\n\033[31mUnable to open file!!!\033[0m");
        return;
    }

    int acc_no;
    int secret_pin;
    Account acc_read;
    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);
    printf("Enter your account secret PIN: ");
    scanf("%d", &secret_pin);

    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_read.acc_no == acc_no)
        {
            if (acc_read.pin == secret_pin)
            {
                printf("\nYour current balance is %.2f Taka", acc_read.balance);
            }
            else
            {
                printf("\n\033[31mSecret PIN doesn't match!\033[0m");
            }
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("\n\033[31mAccount No: %d was not found.\033[0m\n", acc_no);
}

void change_pin()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL)
    {
        printf("\n\033[31mUnable to open file!!!\033[0m");
        return;
    }

    int acc_no;
    int current_pin;
    int new_secret_pin;
    Account acc_r;
    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);
    printf("Enter your current PIN: ");
    scanf("%d", &current_pin);
    printf("Enter 5 digit new secret PIN: ");
    scanf("%d", &new_secret_pin);

    if (current_pin == new_secret_pin)
    {
        fclose(file);
        printf("\n\033[31mCurrent PIN and new secret PIN is same.\033[0m\n");
        return;
    }

    while (fread(&acc_r, sizeof(acc_r), 1, file))
    {
        if (acc_r.acc_no == acc_no)
        {
            if (acc_r.pin == current_pin)
            {
                acc_r.pin = new_secret_pin;
                fseek(file, -sizeof(acc_r), SEEK_CUR);
                fwrite(&acc_r, sizeof(acc_r), 1, file);
                printf("\n\033[32mPIN change successfully!\033[0m");
            }
            else
            {
                printf("\n\033[31mCurrent PIN doesn't match!\033[0m");
            }
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("\n\033[31mAccount No: %d was not found in our records.\033[0m\n", acc_no);
}