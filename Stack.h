#ifndef STACK_H
#define STACK_H
#include "list_queues.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ================= STRUCTURES ================= */



typedef struct TStack{
    TList *top;
} TStack;

typedef struct {
    TStack *shortS;
    TStack *longS;
} SplitStacks;




/* ================= STACK BASICS ================= */

TStack* createStack(){
    TStack *stk = (TStack*)malloc(sizeof(TStack));
    if(!stk) return NULL;
    stk->top = NULL;
    return stk;
}

TStack* push(TStack *stk, TList *node){
    node->next = stk->top;
    stk->top = node;
    return stk;
}

TList* pop(TStack *stk){
    if(!stk || !stk->top) return NULL;

    TList *p = stk->top;
    stk->top = p->next;
    p->next = NULL;
    return p;
}

bool isEmpty(TStack *stk){
    return (stk->top == NULL);
}


/* ================= TO STACK ================= */

TStack* toStack(TList *merged){
    TStack *stk = createStack();

    while(merged){
        TList *tmp = merged;
        merged = merged->next;
        push(stk, tmp);
    }
    return stk;
}

/* ================= REVERSE STACK ================= */

TStack* reversestack(TStack *stk){
    TStack *newstk = createStack();

    while(!isEmpty(stk)){
        push(newstk, pop(stk));
    }
    return newstk;
}

/* ================= GET INFO ================= */

TStack* getInfoPersonality(TStack *stk, char *name){
    TList *cur = stk->top;

    while(cur){
        if(strcmp(cur->name, name) == 0){
            printf("%s\n%s\n%d-%d-%d\n%d-%d-%d\n",
                cur->name,
                cur->description,
                cur->dobearth.day, cur->dobearth.month, cur->dobearth.year,
                cur->dodeath.day, cur->dodeath.month, cur->dodeath.year);
            break;
        }
        cur = cur->next;
    }
    return stk;
}

/* ================= SWAP DATA ================= */

void swapData(TList *a, TList *b){
    char n[100], d[255];
    Edate dob, dod;

    strcpy(n, a->name);
    strcpy(d, a->description);
    dob = a->dobearth;
    dod = a->dodeath;

    strcpy(a->name, b->name);
    strcpy(a->description, b->description);
    a->dobearth = b->dobearth;
    a->dodeath = b->dodeath;

    strcpy(b->name, n);
    strcpy(b->description, d);
    b->dobearth = dob;
    b->dodeath = dod;
}

/* ================= SORT BY NAME ================= */

TStack* sortNameStack(TStack *s){
    for(TList *i = s->top; i; i = i->next){
        for(TList *j = i->next; j; j = j->next){
            if(strcmp(i->name, j->name) > 0){
                swapData(i, j);
            }
        }
    }
    return s;
}

/* ================= DELETE ================= */

TStack* deleteName(TStack *stk, char *name){
    TList *cur = stk->top, *prev = NULL;

    while(cur){
        if(strcmp(cur->name, name) == 0){
            if(prev) prev->next = cur->next;
            else stk->top = cur->next;

            free(cur);
            return stk;
        }
        prev = cur;
        cur = cur->next;
    }
    return stk;
}

/* ================= UPDATE ================= */

TStack* updateStack(TStack *stk, char *name, char *def, char *DoB, char *DoD){
    TList *cur = stk->top;

    while(cur){
        if(strcmp(cur->name, name) == 0){
            strcpy(cur->description, def);

            sscanf(DoB, "%d-%d-%d",
                &cur->dobearth.day,
                &cur->dobearth.month,
                &cur->dobearth.year);

            sscanf(DoD, "%d-%d-%d",
                &cur->dodeath.day,
                &cur->dodeath.month,
                &cur->dodeath.year);

            return stk;
        }
        cur = cur->next;
    }
    return stk;
}

/* ================= ADD SORTED ================= */

TStack* addNameStack(TStack *stk, char *name, char *def, char *DoB, char *DoD){
    TList *node = (TList*)malloc(sizeof(TList));

    strcpy(node->name, name);
    strcpy(node->description, def);

    sscanf(DoB, "%d-%d-%d",
        &node->dobearth.day,
        &node->dobearth.month,
        &node->dobearth.year);

    sscanf(DoD, "%d-%d-%d",
        &node->dodeath.day,
        &node->dodeath.month,
        &node->dodeath.year);

    node->next = NULL;

    if(!stk->top || strcmp(name, stk->top->name) < 0){
        node->next = stk->top;
        stk->top = node;
        return stk;
    }

    TList *cur = stk->top;

    while(cur->next && strcmp(cur->next->name, name) < 0)
        cur = cur->next;

    node->next = cur->next;
    cur->next = node;

    return stk;
}

/* ================= WORD COUNT ================= */

static int wordCount(char *s){
    int c = 0, in = 0;

    for(int i = 0; s[i]; i++){
        if(s[i] != ' ' && !in){
            in = 1;
            c++;
        }
        if(s[i] == ' ') in = 0;
    }
    return c;
}

/* ================= SORT BY DESCRIPTION ================= */

TStack* definitionStack(TStack *stk){
    for(TList *i = stk->top; i; i = i->next){
        for(TList *j = i->next; j; j = j->next){
            if(wordCount(i->description) > wordCount(j->description)){
                swapData(i, j);
            }
        }
    }
    return stk;
}

/* ================= SHORT / LONG SPLIT ================= */

SplitStacks pronunciationStack(TStack *stk){
    SplitStacks res;
    res.shortS = createStack();
    res.longS = createStack();

    TList *cur = stk->top;

    while(cur){
        TList *tmp = cur;
        cur = cur->next;

        if(strlen(tmp->description) < 50)
            push(res.shortS, tmp);
        else
            push(res.longS, tmp);
    }

    return res;
}

/* ================= SMALLEST ================= */

char* getSmallest(TStack *stk){
    if(!stk->top) return NULL;

    TList *cur = stk->top;
    TList *min = cur;

    while(cur){
        if(strlen(cur->description) < strlen(min->description))
            min = cur;
        cur = cur->next;
    }

    return min->description;
}

/* ================= OVERLAP SEARCH ================= */

void continuousSearch(TStack *stk){
    for(TList *i = stk->top; i; i = i->next){
        for(TList *j = i->next; j; j = j->next){
            if(i->dodeath.year >= j->dobearth.year){
                printf("%s overlaps %s\n", i->name, j->name);
            }
        }
    }
}

/* ================= KILLED CHECK ================= */

bool isPersonalityKilled(char *word){
    return strstr(word, "killed") != NULL;
}

/* ================= RECURSIVE REVERSE ================= */

TList* insertBottom(TList *top, TList *node){
    if(!top){
        node->next = NULL;
        return node;
    }

    top->next = insertBottom(top->next, node);
    return top;
}

TStack* recRevStack(TStack *stk){
    if(!stk->top) return stk;

    TList *node = pop(stk);
    recRevStack(stk);

    stk->top = insertBottom(stk->top, node);

    return stk;
}

#endif;