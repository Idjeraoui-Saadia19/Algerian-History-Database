#ifndef TREES_H
#define TREES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Stack.h"

/* -------------------- STRUCTURES -------------------- */



typedef struct TTree {
    char name[100];
    char description[255];
    Edate dob;
    Edate dod;
    struct TTree *left;
    struct TTree *right;
} TTree;

/* -------------------- NODE CREATION -------------------- */

TTree* createTreeNode(char name[], char desc[], Edate dob, Edate dod){
    TTree *node = (TTree*)malloc(sizeof(TTree));
    if(!node) return NULL;

    strcpy(node->name, name);
    strcpy(node->description, desc);
    node->dob = dob;
    node->dod = dod;

    node->left = node->right = NULL;

    return node;
}

/* -------------------- INSERT BST -------------------- */

TTree* insertBST(TTree *root, TTree *node){

    if(root == NULL)
        return node;

    if(strcmp(node->name, root->name) < 0)
        root->left = insertBST(root->left, node);
    else
        root->right = insertBST(root->right, node);

    return root;
}

/* -------------------- STACK TO TREE -------------------- */

TTree* toTree(TStack *stk){

    TTree *root = NULL;
    TList *cur = stk->top;

    while(cur){

        TTree *node = createTreeNode(
            cur->name,
            cur->description,
            cur->dobearth,
            cur->dodeath
        );

        root = insertBST(root, node);
        cur = cur->next;
    }

    return root;
}

/* -------------------- FILE TO TREE -------------------- */

TTree* fillTree(FILE *f){

    TTree *root = NULL;
    char line[512];

    while(fgets(line, sizeof(line), f)){

        char name[100], desc[255] = "none";
        Edate dob, dod;

        char *eq = strchr(line, '=');
        char *op = strchr(line, '{');
        char *cl = strchr(line, '}');

        if(eq && op && cl){

            strncpy(name, line, eq - line);
            name[eq - line] = '\0';

            sscanf(op + 1, "%d/%d/%d-%d/%d/%d",
                   &dob.day, &dob.month, &dob.year,
                   &dod.day, &dod.month, &dod.year);

            TTree *node = createTreeNode(name, desc, dob, dod);
            root = insertBST(root, node);
        }
    }

    return root;
}

/* -------------------- SEARCH -------------------- */

TTree* getInfoNameTree(TTree *tr, char *name){

    if(!tr) return NULL;

    if(strcmp(tr->name, name) == 0){
        printf("%s\n%s\n", tr->name, tr->description);
        return tr;
    }

    if(strcmp(name, tr->name) < 0)
        return getInfoNameTree(tr->left, name);

    return getInfoNameTree(tr->right, name);
}

/* -------------------- INSERT INTO BST -------------------- */

TTree* addNameBST(TTree *tr, char *name, char *DoB, char *DoD){

    Edate dob, dod;

    sscanf(DoB, "%d-%d-%d", &dob.day, &dob.month, &dob.year);
    sscanf(DoD, "%d-%d-%d", &dod.day, &dod.month, &dod.year);

    TTree *node = createTreeNode(name, (char*)"none", dob, dod);

    return insertBST(tr, node);
}

/* -------------------- MIN NODE -------------------- */

TTree* minValueNode(TTree *node){
    TTree *current = node;

    while(current && current->left)
        current = current->left;

    return current;
}

/* -------------------- DELETE -------------------- */

TTree* deleteNameBST(TTree *root, char *name){

    if(!root) return NULL;

    if(strcmp(name, root->name) < 0)
        root->left = deleteNameBST(root->left, name);

    else if(strcmp(name, root->name) > 0)
        root->right = deleteNameBST(root->right, name);

    else{

        if(!root->left){
            TTree *tmp = root->right;
            free(root);
            return tmp;
        }

        if(!root->right){
            TTree *tmp = root->left;
            free(root);
            return tmp;
        }

        TTree *tmp = minValueNode(root->right);strcpy(root->name, tmp->name);
        strcpy(root->description, tmp->description);
        root->dob = tmp->dob;
        root->dod = tmp->dod;

        root->right = deleteNameBST(root->right, tmp->name);
    }

    return root;
}/* -------------------- UPDATE -------------------- */

TTree* updateNameBST(TTree *tr, char *name, char *s, char *DoB, char *DoD){

    if(!tr) return NULL;

    if(strcmp(tr->name, name) == 0){

        strcpy(tr->description, s);

        sscanf(DoB, "%d-%d-%d", &tr->dob.day, &tr->dob.month, &tr->dob.year);
        sscanf(DoD, "%d-%d-%d", &tr->dod.day, &tr->dod.month, &tr->dod.year);

        return tr;
    }

    if(strcmp(name, tr->name) < 0)
        return updateNameBST(tr->left, name, s, DoB, DoD);

    return updateNameBST(tr->right, name, s, DoB, DoD);
}

/* -------------------- TRAVERSALS -------------------- */

void traversalBSTinOrder(TTree *tr){
    if(!tr) return;

    traversalBSTinOrder(tr->left);
    printf("%s\n", tr->name);
    traversalBSTinOrder(tr->right);
}

void traversalBSTpreOrder(TTree *tr){
    if(!tr) return;

    printf("%s\n", tr->name);
    traversalBSTpreOrder(tr->left);
    traversalBSTpreOrder(tr->right);
}

void traversalBSTpostOrder(TTree *tr){
    if(!tr) return;

    traversalBSTpostOrder(tr->left);
    traversalBSTpostOrder(tr->right);
    printf("%s\n", tr->name);
}

/* -------------------- HEIGHT & SIZE -------------------- */

int height(TTree *tr){
    if(!tr) return 0;

    int l = height(tr->left);
    int r = height(tr->right);

    return (l > r ? l : r) + 1;
}

int size(TTree *tr){
    if(!tr) return 0;

    return 1 + size(tr->left) + size(tr->right);
}

void heightSizeBST(TTree *tr){
    printf("Height: %d\n", height(tr));
    printf("Size: %d\n", size(tr));
}

/* -------------------- LCA -------------------- */

TTree* lowestCommonAncestor(TTree *tr, char *w1, char *w2){

    if(!tr) return NULL;

    if(strcmp(tr->name, w1) > 0 && strcmp(tr->name, w2) > 0)
        return lowestCommonAncestor(tr->left, w1, w2);

    if(strcmp(tr->name, w1) < 0 && strcmp(tr->name, w2) < 0)
        return lowestCommonAncestor(tr->right, w1, w2);

    return tr;
}

/* -------------------- RANGE COUNT -------------------- */

int countNodesRange(TTree *tr, int l, int h){

    if(!tr) return 0;

    int c = 0;

    if(tr->dob.year >= l && tr->dob.year <= h)
        c = 1;

    return c +
        countNodesRange(tr->left, l, h) +
        countNodesRange(tr->right, l, h);
}

/* -------------------- SUCCESSOR -------------------- */

TTree* inOrderSuccessor(TTree *tr, char *word){

    TTree *succ = NULL;

    while(tr){

        if(strcmp(word, tr->name) < 0){
            succ = tr;
            tr = tr->left;
        }
        else
            tr = tr->right;
    }

    return succ;
}

/* -------------------- MIRROR -------------------- */

TTree* BSTMirror(TTree *tr){

    if(!tr) return NULL;

    TTree *tmp = tr->left;
    tr->left = BSTMirror(tr->right);
    tr->right = BSTMirror(tmp);

    return tr;
}

/* -------------------- BALANCE CHECK -------------------- */

int isBalancedUtil(TTree *tr, int *h){

    if(!tr) return 1;

    int lh = 0, rh = 0;

    int l = isBalancedUtil(tr->left, &lh);
    int r = isBalancedUtil(tr->right, &rh);

    *h = (lh > rh ? lh : rh) + 1;

    if(abs(lh - rh) > 1) return 0;

    return l && r;
}

bool isBalancedBST(TTree *tr){
    int h = 0;
    return isBalancedUtil(tr, &h);
}

/* -------------------- MERGE BST -------------------- */

void insertAll(TTree **root, TTree *tr){

    if(tr == NULL)
        return;

    TTree *node = createTreeNode(tr->name,tr->description,tr->dob,tr->dod
    );

    *root = insertBST(*root, node);

    insertAll(root, tr->left);
    insertAll(root, tr->right);
}

TTree* BTSMerge(TTree *t1, TTree *t2){

    TTree *root = NULL;

    insertAll(&root, t1);
    insertAll(&root, t2);

    return root;
}
#endif