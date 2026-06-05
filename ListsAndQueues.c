#include "ListsAndQueues.h"

int main(){

    TList *s=NULL;
    TList *a=NULL;
    TList *b=NULL;

    TQueue *Q=NULL;

    DList *D=NULL;

    Word *W=NULL;

    int choice;

    do{

        printf("\n======================================");
        printf("\n               MENU");
        printf("\n======================================");

        printf("\n1  - getPersonality");
        printf("\n2  - getDatePersonality");
        printf("\n3  - getInfoByDates");
        printf("\n4  - getInfoByDates2");
        printf("\n5  - sortWord");
        printf("\n6  - sortWord2");
        printf("\n7  - sortPersonality");
        printf("\n8  - deletepersonality");
        printf("\n9  - updatePersonality");
        printf("\n10 - similarPersonality");
        printf("\n11 - countPersonality");
        printf("\n12 - palindromeName");
        printf("\n13 - mergeNodes");
        printf("\n14 - merge2Nodes");
        printf("\n15 - addPersonality");
        printf("\n16 - addEvents");
        printf("\n17 - sName");
        printf("\n18 - ageP");
        printf("\n19 - toQueue");
        printf("\n0  - Exit");

        printf("\n\nChoice : ");

        scanf("%d",&choice);

        getchar();

        /* =================================================== */
        /* 1 getPersonality */
        /* =================================================== */

        if(choice==1){

            FILE *f=fopen("ourdata.txt","r");

            if(f==NULL){

                printf("\nFile not found.\n");
            }

            else{

                s=getPersonality(f);

                fclose(f);

                printf("\nFirst list created.\n");

                printList(s);
            }
        }

        /* =================================================== */
        /* 2 getDatePersonality */
        /* =================================================== */

        else if(choice==2){

            FILE *f=fopen("ourdata.txt","r");

            if(f==NULL){

                printf("\nFile not found.\n");
            }

            else{

                a=getDatePersonality(f);

                fclose(f);

                printf("\nDate list created.\n");

                printList(a);
            }
        }/* =================================================== */
        /* 3 getInfoByDates */
        /* =================================================== */

        else if(choice==3){
              if(s==NULL){

              printf("\nLoad list first using option 1.\n");
               }
            Edate d;

            printf("\nEnter birth date in format DD MM YYYY");

            scanf("%d%d%d",
            &d.day,
            &d.month,
            &d.year);

            getchar();

            getInfoByDates(s,&d);
        }

        /* =================================================== */
        /* 4 getInfoByDates2 */
        /* =================================================== */

        else if(choice==4){
             if(a==NULL){

             printf("\nLoad list first using option 2.\n");
             }
            Edate d;

            printf("Enter death date day month year : ");

            scanf("%d%d%d",
            &d.day,
            &d.month,
            &d.year);

            getchar();

            getInfoByDates2(a,d);
        }

        /* =================================================== */
        /* 5 sortWord */
        /* =================================================== */

        else if(choice==5){

            if(s==NULL){

             printf("\nLoad list first using option 1.\n");
            }

             else{

              s=sortWord(s);
  
              printf("\nAlphabetically sorted.\n");

                printList(s);
              }
            }

        /* =================================================== */
        /* 6 sortWord2 */
        /* =================================================== */

        else if(choice==6){
            if(s==NULL){

             printf("\nLoad list first using option 1.\n");
            }
            s=sortWord2(s);
            printf("\nSorted by character count.\n");

            printList(s);
        }

        /* =================================================== */
        /* 7 sortPersonality */
        /* =================================================== */

        else if(choice==7){
            if(a==NULL){

             printf("\nLoad list first using option 2.\n");
            }

            a=sortPersonality(a);

            printf("\nSorted by age.\n");

            printList(a);
        }

        /* =================================================== */
        /* 8 deletepersonality */
        /* =================================================== */

        else if(choice==8){
            if(s==NULL){

             printf("\nLoad list first using option 1.\n");
            }
            if(a==NULL){

             printf("\nLoad list first using option 2.\n");
            }
            char name[100];

            printf("Enter name to delete : ");

            fgets(name,sizeof(name),stdin);

            name[strcspn(name,"\n")]=0;

            FILE *f=fopen("ourdata.txt","r");

            if(f!=NULL){

                s=deletepersonality(f,s,a,name);

                fclose(f);

                printf("\nDeleted.\n");
            }

            printf("\nDeleted successfully.\n");

            printf("\nUpdated list:\n");
            printList(s);
        }

        /* =================================================== */
        /* 9 updatePersonality */
        /* =================================================== */

        else if(choice==9){
            if(s==NULL ){

             printf("\nLoad list first using option 1.\n");
            }
            if(a==NULL ){

             printf("\nLoad list first using option 2.\n");
            }
        
            char name[100];

            char definition[255];

            char DoB[20];

            char DoD[20];

            printf("Enter name : ");

            fgets(name,sizeof(name),stdin);

            name[strcspn(name,"\n")]=0;

            printf("Enter definition : ");

            fgets(definition,sizeof(definition),stdin);

            definition[strcspn(definition,"\n")]=0;

            printf("Enter birth date dd/mm/yyyy : ");

            fgets(DoB,sizeof(DoB),stdin);

            DoB[strcspn(DoB,"\n")]=0;

            printf("Enter death date dd/mm/yyyy : ");

            fgets(DoD,sizeof(DoD),stdin);

            DoD[strcspn(DoD,"\n")]=0;

            FILE *f=fopen("ourdata.txt","r");

            if(f!=NULL){
                s=updatePersonality( f, s, a, name, definition, DoB, DoD);

                fclose(f);

                printf("\nUpdated.\n");
            }
        }

        /* =================================================== */
        /* 10 similarPersonality */
        /* =================================================== */

        else if(choice==10){
            if(a==NULL ){

             printf("\nLoad list first using option 2.\n");
            }
            char word[100];

            printf("Enter personality name : ");

            fgets(word,sizeof(word),stdin);

            word[strcspn(word,"\n")]=0;

            TList *similar=
            similarPersonality(a,word);printList(similar);
        }

        /* =================================================== */
        /* 11 countPersonality */
        /* =================================================== */

        else if(choice==11){
             if(a==NULL ){

             printf("\nLoad list first using option 2.\n");
            }
            Edate d;

            printf("Enter date day month year : ");

            scanf("%d%d%d",&d.day,&d.month,&d.year);

            getchar();

            TList *result=countPersonality(a,&d);

            printList(result);
        }

        /* =================================================== */
        /* 12 palindromeName */
        /* =================================================== */

        else if(choice==12){
             if(s==NULL ){printf("\nLoad list first using option 1.\n");
            }
             if(a==NULL ){

             printf("\nLoad list first using option 2.\n");
            }
            W=palindromeName(s,a);

            printf("\nPalindrome words :\n");

            printWords(W);
        }

        /* =================================================== */
        /* 13 mergeNodes */
        /* =================================================== */

        else if(choice==13){
            if(s==NULL ){

             printf("\nLoad list first using option 1.\n");
            }
             if(a==NULL ){

             printf("\nLoad list first using option 2.\n");
            }
            D=mergeNodes(s,a);

            printDList(D);
        }

        /* =================================================== */
        /* 14 merge2Nodes */
        /* =================================================== */

        else if(choice==14){
              if(s==NULL ){

             printf("\nLoad list first using option 1.\n");
            }
             if(a==NULL ){

             printf("\nLoad list first using option 2.\n");
            }
            TList *merged = merge2Nodes(s,a);

            printf("\nMerged circular list :\n");

            printList(merged);

            b=merged;
        }

        /* =================================================== */
        /* 15 addPersonality */
        /* =================================================== */

        else if(choice==15){
            
            char name[100];

            char DoB[20];

            char DoD[20];

            printf("Enter name : ");

            fgets(name,sizeof(name),stdin);

            name[strcspn(name,"\n")]=0;

            printf("Enter birth date dd/mm/yyyy : ");

            fgets(DoB,sizeof(DoB),stdin);

            DoB[strcspn(DoB,"\n")]=0;

            printf("Enter death date dd/mm/yyyy : ");

            fgets(DoD,sizeof(DoD),stdin);

            DoD[strcspn(DoD,"\n")]=0;

            s=addPersonality(s,a,name,DoB,DoD);

            printf("\nPersonality added.\n");
        }

        /* =================================================== */
        /* 16 addEvents */
        /* =================================================== */

        else if(choice==16){

            char name[100];

            Edate d;

            printf("Enter event name : ");

            fgets(name,sizeof(name),stdin);

            name[strcspn(name,"\n")]=0;

            printf("Enter date day month year : ");

            scanf("%d%d%d",
            &d.day,
            &d.month,
            &d.year);

            getchar();

            b=addEvents(b,name,d);

            printf("\nEvent added.\n");
        }

        /* =================================================== */
        /* 17 sName */
        /* =================================================== */

        else if(choice==17){

            Q=sName(s);

            printf("\nQueue sorted by word count :\n");

            printQueue(Q);
        }

        /* =================================================== */
        /* 18 ageP */
        /* =================================================== */

        else if(choice==18){

            Q=ageP(a);

            printf("\nQueue sorted by age :\n");

            printQueue(Q);
        }

        /* =================================================== */
        /* 19 toQueue */
        /* =================================================== */

        else if(choice==19){

            Q=toQueue(b);

            printf("\nConverted to queue :\n");

            printQueue(Q);
        }

    }while(choice!=0);

    return 0;
}