
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "trees.h"

/* ================= PRINT TREE NODE ================= */

void printNode(TTree *n){

    if(!n) return;

    printf("\n========================\n");

    printf("Name : %s\n",n->name);

    printf("Description : %s\n",
           n->description);

    printf("Birth : %d-%d-%d\n",
           n->dob.day,
           n->dob.month,
           n->dob.year);

    printf("Death : %d-%d-%d\n",
           n->dod.day,
           n->dod.month,
           n->dod.year);
}

/* ================= MAIN ================= */

int main(){

    TTree *root = NULL;

    TTree *root2 = NULL;

    int choice;

    do{

        printf("\n==================================");
        printf("\n              MENU");
        printf("\n==================================");

        printf("\n1  - Fill tree from file");
        printf("\n2  - Convert stack to tree");
        printf("\n3  - Search personality");
        printf("\n4  - Add personality");
        printf("\n5  - Delete personality");
        printf("\n6  - Update personality");

        printf("\n7  - InOrder traversal");
        printf("\n8  - PreOrder traversal");
        printf("\n9  - PostOrder traversal");

        printf("\n10 - Height and size");
        printf("\n11 - Lowest common ancestor");
        printf("\n12 - Count nodes in year range");
        printf("\n13 - InOrder successor");

        printf("\n14 - Mirror BST");
        printf("\n15 - Check balance");
        printf("\n16 - Merge BST");

        printf("\n0  - Exit");

        printf("\n\nChoice : ");

        scanf("%d",&choice);

        getchar();

        /* ====================================== */
        /* 1 FILL TREE */
        /* ====================================== */

        if(choice==1){

            FILE *f = fopen("data.txt","r");

            if(f==NULL){

                printf("\nFile not found.\n");
            }

            else{

                root = fillTree(f);

                fclose(f);

                printf("\nTree created.\n");
            }
        }

        /* ====================================== */
        /* 2 STACK TO TREE */
        /* ====================================== */

        else if(choice==2){

            TStack *stk =
            (TStack*)malloc(sizeof(TStack));

            stk->top = NULL;

            int n;

            printf("How many nodes : ");

            scanf("%d",&n);

            getchar();

            for(int i=0;i<n;i++){

                TList *node =
                (TList*)malloc(sizeof(TList));

                printf("\nName : ");

                fgets(node->name,
                      sizeof(node->name),
                      stdin);

                node->name[
                strcspn(node->name,"\n")] = 0;

                printf("Description : ");

                fgets(node->description,
                      sizeof(node->description),
                      stdin);

                node->description[
                strcspn(node->description,"\n")] = 0;

                printf("Birth d m y : ");

                scanf("%d%d%d",
                      &node->dobearth.day,
                      &node->dobearth.month,
                      &node->dobearth.year);

                getchar();

                printf("Death d m y : ");

                scanf("%d%d%d",
                      &node->dodeath.day,
                      &node->dodeath.month,
                      &node->dodeath.year);

                getchar();

                node->next = stk->top;
                stk->top = node;
            }

            root = toTree(stk);

            printf("\nTree created from stack.\n");
        }

        /* ====================================== */
        /* 3 SEARCH */
        /* ====================================== */

        else if(choice==3){

            char name[100];

            printf("Enter name : ");

            fgets(name,sizeof(name),stdin);name[strcspn(name,"\n")] = 0;
            TTree *r =
            getInfoNameTree(root,name);

            if(!r)
                printf("\nNot found.\n");
        }

        /* ====================================== */
        /* 4 ADD */
        /* ====================================== */

        else if(choice==4){

            char name[100];

            char dob[20];

            char dod[20];

            printf("Enter name : ");

            fgets(name,sizeof(name),stdin);

            name[strcspn(name,"\n")] = 0;

            printf("Enter birth date dd-mm-yyyy : ");

            fgets(dob,sizeof(dob),stdin);

            dob[strcspn(dob,"\n")] = 0;

            printf("Enter death date dd-mm-yyyy : ");

            fgets(dod,sizeof(dod),stdin);

            dod[strcspn(dod,"\n")] = 0;

            root =
            addNameBST(root,name,dob,dod);

            printf("\nInserted.\n");
        }

        /* ====================================== */
        /* 5 DELETE */
        /* ====================================== */

        else if(choice==5){

            char name[100];

            printf("Enter name : ");

            fgets(name,sizeof(name),stdin);

            name[strcspn(name,"\n")] = 0;

            root =
            deleteNameBST(root,name);

            printf("\nDeleted.\n");
        }

        /* ====================================== */
        /* 6 UPDATE */
        /* ====================================== */

        else if(choice==6){

            char name[100];

            char desc[255];

            char dob[20];

            char dod[20];

            printf("Enter name : ");

            fgets(name,sizeof(name),stdin);

            name[strcspn(name,"\n")] = 0;

            printf("Enter new description : ");

            fgets(desc,sizeof(desc),stdin);

            desc[strcspn(desc,"\n")] = 0;

            printf("Enter new birth date dd-mm-yyyy : ");

            fgets(dob,sizeof(dob),stdin);

            dob[strcspn(dob,"\n")] = 0;

            printf("Enter new death date dd-mm-yyyy : ");

            fgets(dod,sizeof(dod),stdin);

            dod[strcspn(dod,"\n")] = 0;

            updateNameBST(
                root,
                name,
                desc,
                dob,
                dod);

            printf("\nUpdated.\n");
        }

        /* ====================================== */
        /* 7 INORDER */
        /* ====================================== */

        else if(choice==7){

            printf("\n===== INORDER =====\n");

            traversalBSTinOrder(root);
        }

        /* ====================================== */
        /* 8 PREORDER */
        /* ====================================== */

        else if(choice==8){

            printf("\n===== PREORDER =====\n");

            traversalBSTpreOrder(root);
        }

        /* ====================================== */
        /* 9 POSTORDER */
        /* ====================================== */

        else if(choice==9){

            printf("\n===== POSTORDER =====\n");

            traversalBSTpostOrder(root);
        }

        /* ====================================== */
        /* 10 HEIGHT SIZE */
        /* ====================================== */

        else if(choice==10){

            heightSizeBST(root);
        }

        /* ====================================== */
        /* 11 LCA */
        /* ====================================== */

        else if(choice==11){

            char w1[100];
            char w2[100];

            printf("Enter first name : ");

            fgets(w1,sizeof(w1),stdin);

            w1[strcspn(w1,"\n")] = 0;

            printf("Enter second name : ");

            fgets(w2,sizeof(w2),stdin);

            w2[strcspn(w2,"\n")] = 0;

            TTree *lca =
            lowestCommonAncestor(
                root,
                w1,
                w2);

            if(lca){

                printf("\nLowest common ancestor : %s\n",
                       lca->name);
            }

            else{printf("\nNot found.\n");
            }
        }/* ====================================== */
        /* 12 RANGE COUNT */
        /* ====================================== */

        else if(choice==12){

            int l,h;

            printf("Enter lower year : ");
            scanf("%d",&l);

            printf("Enter higher year : ");
            scanf("%d",&h);

            getchar();

            int c =
            countNodesRange(root,l,h);

            printf("\nCount = %d\n",c);
        }

        /* ====================================== */
        /* 13 SUCCESSOR */
        /* ====================================== */

        else if(choice==13){

            char word[100];

            printf("Enter name : ");

            fgets(word,sizeof(word),stdin);

            word[strcspn(word,"\n")] = 0;

            TTree *s =
            inOrderSuccessor(root,word);

            if(s){

                printf("\nSuccessor : %s\n",
                       s->name);
            }

            else{

                printf("\nNo successor.\n");
            }
        }

        /* ====================================== */
        /* 14 MIRROR */
        /* ====================================== */

        else if(choice==14){

            root = BSTMirror(root);

            printf("\nTree mirrored.\n");
        }

        /* ====================================== */
        /* 15 BALANCED */
        /* ====================================== */

        else if(choice==15){

            if(isBalancedBST(root))
                printf("\nBalanced BST.\n");

            else
                printf("\nNot balanced.\n");
        }

        /* ====================================== */
        /* 16 MERGE BST */
        /* ====================================== */

        else if(choice==16){

            FILE *f = fopen("data2.txt","r");

            if(f==NULL){

                printf("\nSecond file not found.\n");
            }

            else{

                root2 = fillTree(f);

                fclose(f);

                root =
                BTSMerge(root,root2);

                printf("\nTrees merged.\n");
            }
        }

    }while(choice!=0);

    return 0;
}