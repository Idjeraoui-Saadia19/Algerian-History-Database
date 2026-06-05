
#include "recursion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* reuse your File struct */
typedef struct File {
    char line[256];
    struct File *next;
} File;


File* createNode(char *text){
    File *n = (File*)malloc(sizeof(File));
    strcpy(n->line, text);
    n->next = NULL;
    return n;
}


File* buildSample(){
    File *head = createNode("alex born 1990");
    head->next = createNode("bob killed 2000");
    head->next->next = createNode("alex died 2020");
    head->next->next->next = createNode("charlie alive");
    return head;
}

/* ---- display ---- */
void display(File *f){
    printf("\n--- FILE CONTENT ---\n");
    while(f){
        printf("%s\n", f->line);
        f = f->next;
    }
    printf("--------------------\n");
}

/* ============================================================
   MAIN MENU
   ============================================================ */

int main(){

    File *f = buildSample();

    int choice;
    char name[100], word[100], d1[100], d2[100];

    do{
        printf("\n========= MENU =========\n");
        printf("1. Display file\n");
        printf("2. Count occurrences\n");
        printf("3. Remove occurrence\n");
        printf("4. Replace occurrence\n");
        printf("5. Name permutation\n");
        printf("6. Subsequence of word\n");
        printf("7. Check palindrome\n");
        printf("8. Distinct subsequences\n");
        printf("9. Date overlap check\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice){

            case 1:
                display(f);
                break;

            case 2:
                printf("Enter word: ");
                scanf("%s", name);
                printf("Count = %d\n", countOccurence(f, name));
                break;

            case 3:
                printf("Enter word to remove: ");
                scanf("%s", name);
                f = removeOccurence(f, name);
                break;

            case 4:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter DoB: ");
                scanf("%s", d1);
                printf("Enter DoD: ");
                scanf("%s", d2);
                f = replaceOccurence(f, name, d1, d2);
                break;

            case 5:
                printf("Enter name: ");
                scanf("%s", name);
                namePermutation(name);
                break;

            case 6:
                printf("Enter word: ");
                scanf("%s", word);
                subseqName(word);
                break;

            case 7:
                printf("Enter word: ");
                scanf("%s", word);
                if(isPalindromeWord(word))
                    printf("Palindrome\n");
                else
                    printf("Not palindrome\n");
                break;

            case 8:
                printf("Enter word: ");
                scanf("%s", word);
                printf("Result = %d\n", distinctSubseqWord(word));
                break;

            case 9:
                printf("Enter date1: ");
                scanf("%s", d1);
                printf("Enter date2: ");
                scanf("%s", d2);
                longestSubyear(d1, d2);
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice\n");
        }

    }while(choice != 0);

    return 0;
}