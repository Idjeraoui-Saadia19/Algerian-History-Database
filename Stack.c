#include "Stack.h"
#include"ListsAndQueues.h"

int main(){

    TStack *stk = createStack();

    SplitStacks split;

    int choice;

    do{

        printf("\n====================================");
        printf("\n              MENU");
        printf("\n====================================");

        printf("\n1  - Push node");
        printf("\n2  - Pop node");
        printf("\n3  - Print stack");
        printf("\n4  - Reverse stack");
        printf("\n5  - Recursive reverse stack");
        printf("\n6  - Search personality");
        printf("\n7  - Sort by name");
        printf("\n8  - Delete personality");
        printf("\n9  - Update personality");
        printf("\n10 - Add sorted personality");
        printf("\n11 - Sort by description words");
        printf("\n12 - Split short/long descriptions");
        printf("\n13 - Get smallest description");
        printf("\n14 - Continuous search");
        printf("\n15 - Check killed word");
        printf("\n0  - Exit");

        printf("\n\nChoice : ");

        scanf("%d",&choice);

        getchar();

        /* ====================================== */
        /* 1 PUSH */
        /* ====================================== */

        if(choice==1){

            TList *node =
            (TList*)malloc(sizeof(TList));

            printf("Enter name : ");
            fgets(node->name,
                  sizeof(node->name),
                  stdin);

            node->name[
            strcspn(node->name,"\n")] = 0;

            printf("Enter description : ");
            fgets(node->description,
                  sizeof(node->description),
                  stdin);

            node->description[
            strcspn(node->description,"\n")] = 0;

            printf("Enter birth date d m y : ");

            scanf("%d%d%d",
                  &node->dobearth.day,
                  &node->dobearth.month,
                  &node->dobearth.year);

            getchar();

            printf("Enter death date d m y : ");

            scanf("%d%d%d",
                  &node->dodeath.day,
                  &node->dodeath.month,
                  &node->dodeath.year);

            getchar();

            node->next = NULL;

            push(stk,node);

            printf("\nNode pushed.\n");
        }

        /* ====================================== */
        /* 2 POP */
        /* ====================================== */

        else if(choice==2){

            TList *popped = pop(stk);

            if(popped){

                printf("\nPopped : %s\n",
                       popped->name);

                free(popped);
            }

            else{

                printf("\nStack empty.\n");
            }
        }

        /* ====================================== */
        /* 3 PRINT */
        /* ====================================== */

        else if(choice==3){

            printStack(stk);
        }

        /* ====================================== */
        /* 4 REVERSE STACK */
        /* ====================================== */

        else if(choice==4){

            stk = reversestack(stk);

            printf("\nStack reversed.\n");

            printStack(stk);
        }

        /* ====================================== */
        /* 5 RECURSIVE REVERSE */
        /* ====================================== */

        else if(choice==5){

            stk = recRevStack(stk);

            printf("\nRecursively reversed.\n");printStack(stk);
        }

        /* ====================================== */
        /* 6 SEARCH */
        /* ====================================== */

        else if(choice==6){

            char name[100];

            printf("Enter name : ");

            fgets(name,sizeof(name),stdin);

            name[strcspn(name,"\n")] = 0;

            getInfoPersonality(stk,name);
        }

        /* ====================================== */
        /* 7 SORT NAME */
        /* ====================================== */

        else if(choice==7){

            stk = sortNameStack(stk);

            printf("\nSorted by name.\n");printStack(stk);
        }

        /* ====================================== */
        /* 8 DELETE */
        /* ====================================== */

        else if(choice==8){

            char name[100];

            printf("Enter name to delete : ");

            fgets(name,sizeof(name),stdin);

            name[strcspn(name,"\n")] = 0;

            stk = deleteName(stk,name);

            printf("\nDeleted.\n");

            printStack(stk);
        }

        /* ====================================== */
        /* 9 UPDATE */
        /* ====================================== */

        else if(choice==9){

            char name[100];
            char def[255];
            char dob[20];
            char dod[20];

            printf("Enter name : ");

            fgets(name,sizeof(name),stdin);

            name[strcspn(name,"\n")] = 0;

            printf("Enter new definition : ");

            fgets(def,sizeof(def),stdin);

            def[strcspn(def,"\n")] = 0;

            printf("Enter new birth date dd-mm-yyyy : ");

            fgets(dob,sizeof(dob),stdin);

            dob[strcspn(dob,"\n")] = 0;

            printf("Enter new death date dd-mm-yyyy : ");

            fgets(dod,sizeof(dod),stdin);

            dod[strcspn(dod,"\n")] = 0;

            stk = updateStack(
                  stk,
                  name,
                  def,
                  dob,
                  dod);

            printf("\nUpdated.\n");
        }

        /* ====================================== */
        /* 10 ADD SORTED */
        /* ====================================== */

        else if(choice==10){

            char name[100];
            char def[255];
            char dob[20];
            char dod[20];

            printf("Enter name : ");

            fgets(name,sizeof(name),stdin);

            name[strcspn(name,"\n")] = 0;

            printf("Enter definition : ");

            fgets(def,sizeof(def),stdin);

            def[strcspn(def,"\n")] = 0;

            printf("Enter birth date dd-mm-yyyy : ");

            fgets(dob,sizeof(dob),stdin);

            dob[strcspn(dob,"\n")] = 0;

            printf("Enter death date dd-mm-yyyy : ");

            fgets(dod,sizeof(dod),stdin);

            dod[strcspn(dod,"\n")] = 0;

            stk = addNameStack(
                  stk,
                  name,
                  def,
                  dob,
                  dod);

            printf("\nInserted sorted.\n");

            printStack(stk);
        }

        /* ====================================== */
        /* 11 SORT DESCRIPTION */
        /* ====================================== */

        else if(choice==11){

            stk = definitionStack(stk);

            printf("\nSorted by description words.\n");

            printStack(stk);
        }

        /* ====================================== */
        /* 12 SPLIT STACKS */
        /* ====================================== */

        else if(choice==12){

            split = pronunciationStack(stk);

            printf("\n===== SHORT DESCRIPTIONS =====\n");

            printStack(split.shortS);

            printf("\n===== LONG DESCRIPTIONS =====\n");

            printStack(split.longS);
        }

        /* ====================================== */
        /* 13 SMALLEST */
        /* ====================================== */

        else if(choice==13){char *s = getSmallest(stk);

            if(s)
                printf("\nSmallest : %s\n",s);

            else
                printf("\nStack empty.\n");
        }

        /* ====================================== */
        /* 14 CONTINUOUS SEARCH */
        /* ====================================== */

        else if(choice==14){

            continuousSearch(stk);
        }

        /* ====================================== */
        /* 15 KILLED CHECK */
        /* ====================================== */

        else if(choice==15){

            char word[100];

            printf("Enter word : ");

            fgets(word,sizeof(word),stdin);word[strcspn(word,"\n")] = 0;

            if(isPersonalityKilled(word))
                printf("\nContains killed.\n");

            else
                printf("\nDoes not contain killed.\n");
        }

    }while(choice!=0);

    return 0;
}