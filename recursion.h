#ifndef RECURSION_H
#define RECURSION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list_queues.h"
#include "stacks.h"



typedef struct File {
    char line[256];
    struct File *next;
} File;

/* ============================================================
   1. COUNT OCCURRENCES (RECURSIVE)
   ============================================================ */

int countOccurence(File *f, char *name){
    if(f == NULL)
        return 0;

    int found = (strstr(f->line, name) != NULL) ? 1 : 0;

    return found + countOccurence(f->next, name);
}

/* ============================================================
   2. REMOVE OCCURRENCES (RECURSIVE)
   ============================================================ */

File* removeOccurence(File *f, char *word){

    if(f == NULL)
        return NULL;

    f->next = removeOccurence(f->next, word);

    if(strstr(f->line, word)){
        File *tmp = f->next;
        free(f);
        return tmp;
    }

    return f;
}

/* ============================================================
   3. REPLACE OCCURRENCES (RECURSIVE)
   ============================================================ */

File* replaceOccurence(File *f, char *name, char *DoB, char *DoD){

    if(f == NULL)
        return NULL;

    if(strstr(f->line, name)){
        char newLine[256];
        snprintf(newLine, sizeof(newLine), "%s %s %s", name, DoB, DoD);
        strcpy(f->line, newLine);
    }

    f->next = replaceOccurence(f->next, name, DoB, DoD);

    return f;
}

/* ============================================================
   4. PERMUTATIONS OF NAME (RECURSIVE)
   ============================================================ */

void swap(char *a, char *b){
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void permute(char *name, int l, int r){
    if(l == r){
        printf("%s\n", name);
        return;
    }

    for(int i = l; i <= r; i++){
        swap(&name[l], &name[i]);
        permute(name, l + 1, r);
        swap(&name[l], &name[i]);
    }
}

void namePermutation(char *name){
    int len = strlen(name);
    permute(name, 0, len - 1);
}

/* ============================================================
   5. SUBSEQUENCES OF NAME (RECURSIVE)
   ============================================================ */

void subseqHelper(char *word, char *out, int i, int j){

    if(word[i] == '\0'){
        out[j] = '\0';
        printf("%s\n", out);
        return;
    }

    // include
    out[j] = word[i];
    subseqHelper(word, out, i + 1, j + 1);

    // exclude
    subseqHelper(word, out, i + 1, j);
}

void subseqName(char *word){
    char out[256];
    subseqHelper(word, out, 0, 0);
}

/* ============================================================
   6. OVERLAP OF DATES
   ============================================================ */

void longestSubyear(char *date1, char *date2){
    if(strcmp(date1, date2) > 0)
        printf("Overlap detected between %s and %s\n", date1, date2);
    else
        printf("No overlap\n");
}

/* ============================================================
   7. DISTINCT SUBSEQUENCES COUNT
   ============================================================ */

int distinctSubseqWord(char *event){

    if(*event == '\0')
        return 1;

    return 2 * distinctSubseqWord(event + 1);
}

/* ============================================================
   8. PALINDROME CHECK (RECURSIVE)
   ============================================================ */

bool isPalHelper(char *s, int l, int r){

    if(l >= r)
        return true;

    if(s[l] != s[r])
        return false;

    return isPalHelper(s, l + 1, r - 1);
}

bool isPalindromeWord(char *event){
    int len = strlen(event);
    return isPalHelper(event, 0, len - 1);
}


#endif