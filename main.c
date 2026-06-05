#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "list_queues.h"
#include "stacks.h"
#include "bst.h"
#include "recursion.h"

#define FILE_NAME "ourdata"

/* ================= GLOBALS ================= */

TList *s=NULL, *a=NULL, *b=NULL, *merged=NULL;
TQueue *Q=NULL;
DList *D=NULL;
Word *W=NULL;

TStack *stk=NULL;
TTree *root=NULL;

SplitStacks split;   

bool listsReady=false;
bool stackReady=false;

/* ================= LOAD LISTS ================= */

void loadLists(){
    if(listsReady) return;

    FILE *f=fopen(FILE_NAME,"r");
    if(!f){
        printf("\nERROR: file missing\n");
        return;
    }

    s=getPersonality(f);
    rewind(f);
    a=getDatePersonality(f);

    fclose(f);
    listsReady=true;

    printf("\nLists loaded.\n");
}

/* ================= MAIN ================= */

int main(){

    int m, c;

    do{
        printf("\n==============================");
        printf("\n  DATA STRUCTURE PROJECT");
        printf("\n==============================");
        printf("\n1 Lists & Queues");
        printf("\n2 Stacks");
        printf("\n3 BST");
        printf("\n4 Recursion");
        printf("\n0 Exit");
        printf("\nChoice: ");
        scanf("%d",&m);
        getchar();

        /* ================================================= */
        /* 1 LISTS */
        /* ================================================= */
        if(m==1){

            loadLists();

            do{
                printf("\n--- LIST MODULES ---");

                printf("\n1 getPersonality");
                printf("\n2 getDatePersonality");
                printf("\n3 getInfoByDates");
                printf("\n4 getInfoByDates2");

                printf("\n5 sortWord");
                printf("\n6 sortWord2");
                printf("\n7 sortPersonality");

                printf("\n8 deletepersonality");
                printf("\n9 updatePersonality");

                printf("\n10 similarPersonality");
                printf("\n11 countPersonality");
                printf("\n12 palindromeName");

                printf("\n13 mergeNodes");
                printf("\n14 merge2Nodes");

                printf("\n15 addPersonality");
                printf("\n16 addEvents");

                printf("\n17 sName");
                printf("\n18 ageP");
                printf("\n19 toQueue");

                printf("\n0 Back");
                printf("\nChoice: ");
                scanf("%d",&c);
                getchar();

                if(c==5) s=sortWord(s);
                else if(c==6) s=sortWord2(s);
                else if(c==7) a=sortPersonality(a);

                else if(c==13) D=mergeNodes(s,a);
                else if(c==14) merged=merge2Nodes(s,a);

                else if(c==17) Q=sName(s);
                else if(c==18) Q=ageP(a);
                else if(c==19) Q=toQueue(merged);

            }while(c!=0);
        }

        /* ================================================= */
        /* 2 STACKS */
        /* ================================================= */
        else if(m==2){

            if(!stk) stk=createStack();

            do{
                printf("\n--- STACK MODULES ---");

                printf("\n1 toStack");
                printf("\n2 getInfoPersonality");
                printf("\n3 sortNameStack");
                printf("\n4 deleteName");
                printf("\n5 updateStack");

                printf("\n6 addNameStack");
                printf("\n7 definitionStack");

                printf("\n8 pronunciationStack");
                printf("\n9 getSmallest");

                printf("\n10 continuousSearch");
                printf("\n11 isPersonalityKilled");

                printf("\n12 recRevStack");

                printf("\n0 Back");
                printf("\nChoice: ");
                scanf("%d",&c);
                getchar();

                if(c==1) stk=toStack(merged);

                else if(c==7) stk=definitionStack(stk);

                /* ✅ FIX HERE */
                else if(c==8){
                    split = pronunciationStack(stk);   // CORRECT
                    printf("\nShort stack ready\n");
                }

                else if(c==9)
                    printf("%s\n", getSmallest(stk));

                else if(c==10)
                    continuousSearch(stk);

                else if(c==12)
                    stk=recRevStack(stk);

            }while(c!=0);
        }

        /* ================================================= */
        /* 3 BST */
        /* ================================================= */
        else if(m==3){

            do{
                printf("\n--- BST MODULES ---");

                printf("\n1 toTree");
                printf("\n2 fillTree");
                printf("\n3 getInfoNameTree");

                printf("\n7 inorder");
                printf("\n8 preorder");
                printf("\n9 postorder");

                printf("\n13 successor");
                printf("\n14 mirror");
                printf("\n15 balanced");

                printf("\n0 Back");
                printf("\nChoice: ");
                scanf("%d",&c);
                getchar();

                if(c==1) root=toTree(stk);

                else if(c==7) traversalBSTinOrder(root);
                else if(c==8) traversalBSTpreOrder(root);
                else if(c==9) traversalBSTpostOrder(root);

                else if(c==14) root=BSTMirror(root);
                else if(c==15) printf("%d\n",isBalancedBST(root));

            }while(c!=0);
        }

        /* ================================================= */
        /* 4 RECURSION */
        /* ================================================= */
        else if(m==4){

            do{
                printf("\n--- RECURSION ---");

                printf("\n1 countOccurence");
                printf("\n2 removeOccurence");
                printf("\n3 replaceOccurence");
                printf("\n4 namePermutation");
                printf("\n5 subseqName");

                printf("\n6 longestSubyear");
                printf("\n7 distinctSubseqWord");
                printf("\n8 isPalindromeWord");

                printf("\n0 Back");
                printf("\nChoice: ");
                scanf("%d",&c);
                getchar();

                if(c==4){
                    char n[100];
                    scanf("%s",n);
                    namePermutation(n);
                }

                else if(c==7){
                    char w[100];
                    scanf("%s",w);
                    printf("%d\n",distinctSubseqWord(w));
                }

                else if(c==8){
                    char w[100];
                    scanf("%s",w);
                    printf("%d\n",isPalindromeWord(w));
                }

            }while(c!=0);
        }

    }while(m!=0);

    return 0;
}