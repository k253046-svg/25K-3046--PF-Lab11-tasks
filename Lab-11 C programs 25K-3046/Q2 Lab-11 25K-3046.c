#include <stdio.h>
#include <string.h>

#define MAX 50

struct Transaction {
    char type[10];
    char date[12];
    float amount;
};
struct Account {
    char name[50];
    int accNumber;
    char accType[20];
    float balance;
    char creationDate[12];
    char lastTransactionDate[12];
    float interestRate;
    int minBalance;
    struct Transaction transactions[100];
    int transactionCount;
};

void inputAccount(struct Account *a) {
    int i;
    printf("Enter account holder name: ");
    scanf(" %[^\n]", a->name);
    printf("Enter account number: ");
    scanf("%d", &a->accNumber);
    printf("Enter account type (Savings/Current/Fixed Deposit): ");
    scanf(" %[^\n]", a->accType);

    if (strcmp(a->accType, "Savings") == 0) { a->minBalance = 1000; a->interestRate = 4.0; }
    else if (strcmp(a->accType, "Current") == 0) { a->minBalance = 5000; a->interestRate = 0.0; }
    else if (strcmp(a->accType, "Fixed Deposit") == 0) { a->minBalance = 10000; a->interestRate = 7.0; }
    else { printf("Invalid type! Defaulting to Savings.\n"); strcpy(a->accType, "Savings"); a->minBalance=1000; a->interestRate=4.0; }

    do {
        printf("Enter initial balance (minimum $%d): ", a->minBalance);
        scanf("%f", &a->balance);
        if (a->balance < a->minBalance) printf("Balance too low! Try again.\n");
    } while (a->balance < a->minBalance);

    printf("Enter account creation date (DD-MM-YYYY): ");
    scanf(" %[^\n]", a->creationDate);
    strcpy(a->lastTransactionDate, a->creationDate);
    a->transactionCount = 0;
}

void addTransaction(struct Account *a) {
    int choice;
    float amt;
    char date[12];

    printf("Transaction type 1.Deposit 2.Withdrawal: ");
    scanf("%d", &choice);

    if (choice != 1 && choice != 2) { printf("Invalid transaction type.\n"); return; }

    printf("Enter amount: ");
    scanf("%f", &amt);
    printf("Enter transaction date (DD-MM-YYYY): ");
    scanf(" %[^\n]", date);

    if (choice == 2 && a->balance - amt < a->minBalance) { printf("Cannot withdraw. Minimum balance requirement.\n"); return; }

    if (choice == 1) strcpy(a->transactions[a->transactionCount].type, "Deposit");
    else strcpy(a->transactions[a->transactionCount].type, "Withdrawal");

    a->transactions[a->transactionCount].amount = amt;
    strcpy(a->transactions[a->transactionCount].date, date);
    a->transactionCount++;

    if (choice == 1) a->balance += amt;
    else a->balance -= amt;

    strcpy(a->lastTransactionDate, date);
    printf("Transaction completed.\n");
}

void displayAccount(struct Account a) {
    int i;
    printf("\nName: %s\nAccount Number: %d\nAccount Type: %s\nBalance: $%.2f\nInterest Rate: %.2f%%\nMinimum Balance: $%d\nCreation Date: %s\nLast Transaction Date: %s\n",
           a.name, a.accNumber, a.accType, a.balance, a.interestRate, a.minBalance, a.creationDate, a.lastTransactionDate);

    printf("Transaction History:\n");
    if (a.transactionCount == 0) printf("No transactions yet.\n");
    else {
        for (i=0; i<a.transactionCount; i++)
            printf("%s of $%.2f on %s\n", a.transactions[i].type, a.transactions[i].amount, a.transactions[i].date);
    }
}

int main() {
    struct Account accounts[MAX];
    int n, i, choice, accNum, found;

    printf("Enter number of accounts: ");
    scanf("%d", &n);

    for (i=0; i<n; i++) {
        printf("\n--- Account %d ---\n", i+1);
        inputAccount(&accounts[i]);
    }
    do {
        printf("\nMenu:\n1.Display Account\n2.Add Transaction\n3.Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter account number: ");
            scanf("%d", &accNum);
            found = 0;
            for (i=0; i<n; i++) {
                if (accounts[i].accNumber == accNum) {
                    displayAccount(accounts[i]);
                    found = 1;
                    break;
                }
            }
            if (!found) printf("Account not found.\n");
        }
        else if (choice == 2) {
            printf("Enter account number: ");
            scanf("%d", &accNum);
            found = 0;
            for (i=0; i<n; i++) {
                if (accounts[i].accNumber == accNum) {
                    addTransaction(&accounts[i]);
                    found = 1;
                    break;
                }
            }
            if (!found) printf("Account not found.\n");
        }
        else if (choice == 3) printf("Exiting program.\n");
        else printf("Invalid choice.\n");
    } while (choice != 3);

    return 0;
}

