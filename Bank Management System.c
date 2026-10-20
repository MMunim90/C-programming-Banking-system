#include<stdio.h>
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
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
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
    
    return 0;
}