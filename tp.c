#include<stdio.h>
#include<string.h>

typedef struct node {
    int n;
    char ip[100];
} pro;

pro ar[80];
int num[15];
int p = 0;  // Counter for productions with left recursion
int x;      // the number of production 

void add(int i, char newNonTerminal, int r) {
    char recursive[100] = "";
    char nonRecursive[100] = "";
    char temp[100];
    strcpy(temp, ar[i].ip + 3); // Skip the 'A->'
    
    char *token = strtok(temp, "|");
    
    // Create a string from the char newNonTerminal
    char newNonTerminalStr[2] = {newNonTerminal, '\0'};
    
    // Split into recursive and non-recursive parts
    while (token != NULL) {
        if (token[0] == ar[i].ip[0]) {  // Check if it's recursive (A->Ad, A->Ae, etc.)
            strcat(recursive, token + 1);  // Skip 'A' in recursive
            strcat(recursive, newNonTerminalStr);
            strcat(recursive, "|");
        } else {
            strcat(nonRecursive, token);
            strcat(nonRecursive, newNonTerminalStr);
            strcat(nonRecursive, "|");
        }
        token = strtok(NULL, "|");
    }

    // Remove the last '|'
    nonRecursive[strlen(nonRecursive) - 1] = '\0';
    recursive[strlen(recursive) - 1] = '\0';

    // Update the original production with the non-recursive part
    sprintf(ar[i].ip, "%c->%s", ar[i].ip[0], nonRecursive);

    // Create the new production for the recursive part
    sprintf(ar[r].ip, "%c->%s|ε", newNonTerminal, recursive);
}

int main() {
    printf(" Enter the number of productions of your grammaire : ");
    scanf("%d", &x);

    printf(" Enter the productions : \n");
    for (int i = 0; i < x; i++) {
        ar[i].n = i;
        printf(" Production %d: ", i + 1);
        scanf("%s", ar[i].ip);
    }

    // Detect and store the productions with left recursion
    for (int i = 0; i < x; i++) {
        if (ar[i].ip[0] == ar[i].ip[3]) {  // Direct left recursion check
            num[p] = ar[i].n;
            p++;
        }
    }

    char newNonTerminal = 'X';  // Start new non-terminal as 'X' for replacing left recursion
    for (int i = 0; i < p; i++) {
        int j = num[i];
        add(j, newNonTerminal, x);  // Add a new production to remove left recursion
        ar[x].n = x;                // Assign the new production number
        newNonTerminal++;           // Move to the next non-terminal letter (e.g., Y, Z, etc.)
        x++;                        // Increment the number of productions
    }
// if dose not exist rec push to another one 
    printf(" AFTER REMOVING LEFT RECURSION:\n");
    for (int i = 0; i < x; i++) {
        printf(" %d %s\n", ar[i].n, ar[i].ip);
    }

    return 0;
}