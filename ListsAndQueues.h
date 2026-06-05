#ifndef LIST_QUEUES
#define LIST_QUEUES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Edate{
    int day;
    int month;
    int year;
}Edate;

typedef struct DList{
    char name[50];
    char definition[255];
     Edate dobearth;
    Edate dodeath;
    struct DList* next;
    struct DList* prev;
}DList;

typedef struct TList{
    char name[100];
    char description[255];
     struct Edate dobearth;
     struct Edate dodeath;
    struct TList *next;
}TList;

typedef struct TQueue{
    TList *head,*tail;
}TQueue;

typedef struct Word{
    char word[100];
    struct Word *next;
}Word;


/* ================= REVERSE LIST ================= */

TList* reverseList(TList *head){

    TList *prev=NULL;
    TList *current=head;
    TList *next=NULL;

    while(current!=NULL){

        next=current->next;
        current->next=prev;

        prev=current;
        current=next;
    }

    return prev;
}


/* ================= PALINDROME ================= */

bool ispalindrome(char word[]){

    int i=0;
    int j=strlen(word)-1;

    while(i<j){

        if(word[i]!=word[j])
            return false;

        i++;
        j--;
    }

    return true;
}
/*display*/
void displayLL(TList *l){

    if(l == NULL){
        printf("List is empty.\n");
        return;
    }

    TList *p = l;

    while(p != NULL){

        printf("Name: %s\n", p->name);
        printf("Description: %s\n", p->description);
        printf("DOB: %d\n", p->dobearth.year);
        printf("DOD: %d\n", p->dodeath.year);
        printf("----------------------\n");

        p = p->next;
    }
}

void displayQ(TQueue *q){

    if(q == NULL || q->head == NULL){
        printf("Queue is empty.\n");
        return;
    }

    TQueue *tmp = q;
    TList *p = tmp->head;

    while(p != NULL){

        printf("Name: %s\n", p->name);
        printf("Description: %s\n", p->description);
        printf("DOB: %d\n", p->dobearth.year);
        printf("DOD: %d\n", p->dodeath.year);
        printf("----------------------\n");

        p = p->next;
    }
}

/* ================= COUNT WORDS ================= */

int countWords(char *name){

    int count=0;
    int inWord=0;

    for(int i=0 ; name[i]!='\0' ; i++){

        if(name[i]!=' ' && inWord==0){

            count++;
            inWord=1;
        }

        else if(name[i]==' ')
            inWord=0;
    }

    return count;
}


/* ================= CREATE NODE ================= */

TList* createNode(char name[],
                  char description[],
                  Edate dob,
                  Edate dod){

    TList *newNode=(TList*)malloc(sizeof(TList));

    if(newNode==NULL)
        return NULL;

    strcpy(newNode->name,name);
    strcpy(newNode->description,description);

    newNode->dobearth=dob;
    newNode->dodeath=dod;

    newNode->next=NULL;

    return newNode;
}


/* ================= INSERT BEGIN ================= */

TList* insertBegin(TList* head,
                   char *name,
                   char *description,
                   Edate DoB,
                   Edate DoD){

    TList *newhead=createNode(name,description,DoB,DoD);

    newhead->next=head;

    return newhead;
}


/* ================= INSERT NODE ================= */

TList* insertAnode(TList **head,
                   TList **tail,
                   TList *node){

    node->next=NULL;

    if(*head==NULL){

        *head=*tail=node;
    }

    else{

        (*tail)->next=node;
        *tail=node;
    }

    return *head;
}


/* ================= ENQUEUE ================= */

TList* enqueue(TQueue *Q,
               char *name,
               char *description,
               Edate DoB,
               Edate DoD){

    TList *newnode=createNode(name,description,DoB,DoD);

    if(Q->head==NULL){

        Q->head=Q->tail=newnode;
    }

    else{

        Q->tail->next=newnode;
        Q->tail=newnode;
    }

    return Q->head;
}


/* ================= DELETE ================= */

TList* deleteFromList(TList *head,char *name){

    TList *curr=head;
    TList *prev=NULL;

    while(curr!=NULL){

        if(strcmp(curr->name,name)==0){

            if(prev==NULL)
                head=curr->next;

            else
                prev->next=curr->next;

            free(curr);

            return head;
        }

        prev=curr;
        curr=curr->next;
    }

    return head;
}
/*================GETPERSONALITY========*/

TList* getPersonality(FILE *f)
{
    char buffer[512];
    char name[50];
    char definition[255];

    Edate dobearth = {-1,-1,-1};
    Edate dodeath = {-1,-1,-1};

    TList *head = NULL;
    TList *tail = NULL;

    while (fgets(buffer, sizeof(buffer), f))
    {
        char *E = strchr(buffer, '=');

        if (E != NULL)
        {
            // extract name
            strncpy(name, buffer, E - buffer);
            name[E - buffer] = '\0';

            // extract definition
            strcpy(definition, E + 1);
            definition[strcspn(definition, "\n")] = '\0';

            // FIX: assign returned node
            TList *newnode = createNode(name, definition, dobearth, dodeath);

            if (head == NULL)
            {
                head = tail = newnode;
            }
            else
            {
                tail->next = newnode;
                tail = newnode;
            }
        }
    }

    return head;
}
/*===============GETDATEPERSONALITY=============*/
TList* getDatePersonality(FILE *f){

    char buffer[512];
    char name[50];
    char definition[255] = "none";

    Edate dobearth;
    Edate dodeath;

    TList *head = NULL;
    TList *tail = NULL;

    // read file line by line
    while(fgets(buffer, sizeof(buffer), f)){

        // we search for '='
        char *E = strchr(buffer, '=');

        // if '=' exists then it is a personality line
        if(E != NULL){

            // we copy everything before '='
            
            strncpy(name, buffer, E - buffer);

            // add string terminator
            name[E - buffer] = '\0';


            // ---------------- FIND '{' ----------------
            //
            // we know that dates begin at '{'
            char *D = strchr(E + 1, '{');

            // if no dates exist skip line
            if(D == NULL)
                continue;


            // we extract dates now 

            sscanf(D,"{%d/%d/%d-%d/%d/%d}",&dobearth.day,&dobearth.month,&dobearth.year,&dodeath.day,&dodeath.month,&dodeath.year);

            TList *newnode =createNode(name,definition,dobearth,dodeath);

            if(head == NULL){
                head = tail = newnode;
            }
            else{
                tail->next = newnode;
                tail = newnode;
            }
        }
    }

    return head;
}

/* ================= GET INFO BY DATE ================= */
void getInfoByDates(TList *s,Edate *DoB){

    TList *p=s;

    while(p!=NULL){

        if(p->dobearth.day==DoB->day &&
           p->dobearth.month==DoB->month &&
           p->dobearth.year==DoB->year){

            printf("\nName : %s\n",p->name);

            printf("Definition : %s\n",
                   p->description);

            printf("Date of Birth : %d/%d/%d\n",
                   p->dobearth.day,
                   p->dobearth.month,
                   p->dobearth.year);

            printf("Date of Death : %d/%d/%d\n",
                   p->dodeath.day,
                   p->dodeath.month,
                   p->dodeath.year);
        }

        p=p->next;
    }
}
/* ================= GETINFODATE2 ================= */
void getInfoByDates2(TList *s, Edate DoD){

    int found = 0;

    while(s != NULL){

        if(s->dodeath.day == DoD.day &&
           s->dodeath.month == DoD.month &&
           s->dodeath.year == DoD.year){

            printf("\nName: %s", s->name);
            printf("\nDescription: %s", s->description);

            printf("\nBirth: %d/%d/%d",
                   s->dobearth.day,
                   s->dobearth.month,
                   s->dobearth.year);printf("\nDeath: %d/%d/%d\n",
                   s->dodeath.day,
                   s->dodeath.month,
                   s->dodeath.year);

            found = 1;
        }

        s = s->next;
    }

    if(!found)
        printf("\nNo personality found.\n");
}
/*=====================AGE ==================*/
int P_age(TList *p){
    if(p->dobearth.year==-1 || p->dodeath.year==-1){
        return -1;
    }
    int Bdays=p->dobearth.year*365+p->dobearth.month*30+p->dobearth.day;
    int Ddays=p->dodeath.year*365+p->dodeath.month*30+p->dodeath.day;

    return Ddays-Bdays;
}


/* ================= SWAP DATA ================= */

void swapData(TList *a,TList *b){

    TList temp=*a;

    strcpy(a->name,b->name);
    strcpy(a->description,b->description);
    a->dobearth=b->dobearth;
    a->dodeath=b->dodeath;

    strcpy(b->name,temp.name);
    strcpy(b->description,temp.description);
    b->dobearth=temp.dobearth;
    b->dodeath=temp.dodeath;
}
/* ================= SWAP WORD ================= */

void swapWord(Word *a,Word *b){

    char temp[100];

    strcpy(temp,a->word);
    strcpy(a->word,b->word);
    strcpy(b->word,temp);
}
/* ================= INSERT WORD ================= */
Word* insertword(Word **head,
                 Word **tail,
                 char word[]){

    Word *newword=(Word*)malloc(sizeof(Word));

    strcpy(newword->word,word);

    newword->next=NULL;

    if(*head==NULL){

        *head=*tail=newword;
    }

    else{

        (*tail)->next=newword;
        *tail=newword;
    }

    return *head;
}

/* ================= SORT WORD LIST ================= */
Word* sortwordlist(Word *head){

    Word *g=head;

    while(g!=NULL){

        Word *j=g->next;

        while(j!=NULL){

            if(strlen(g->word)<strlen(j->word))
                swapWord(g,j);

            j=j->next;
        }

        g=g->next;
    }

    return head;
}
/* ================= SORT WORD ================= */

TList* sortWord(TList *head){

    TList *p=head;

    while(p!=NULL){

        TList *q=p->next;

        while(q!=NULL){

            if(strcmp(p->name,q->name)>0)
                swapData(p,q);

            q=q->next;
        }

        p=p->next;
    }

    return head;
}
/* ================= SORT WORD2 ================= */

TList* sortWord2(TList *head){

    TList *p=head;

    while(p!=NULL){

        TList *q=p->next;

        while(q!=NULL){

            if(strlen(p->name)>strlen(q->name))
                swapData(p,q);

            q=q->next;
        }

        p=p->next;
    }

    return head;
}
/* ================= SORT PERSONALITY ================= */
TList* sortPersonality(TList *head){

    TList *p = head;

    while(p != NULL){

        TList *q = p->next;

        while(q != NULL){

            if(P_age(p) > P_age(q))
                swapData(p, q);

            q = q->next;
        }

        p = p->next;
    }

    return head;
}
/*==========DELETEPERSONALITY============*/
TList* deletepersonality(FILE *f,
                         TList *s,
                         TList *a,
                         char *name){

    TList *temp,*tempe;
    TList *prev,*preve;

    // ---------------- DELETE FROM LIST s ----------------

    temp = s;
    prev = NULL;

    while(temp != NULL &&
          strcmp(temp->name, name) != 0){

        prev = temp;
        temp = temp->next;
    }

    // personality found
    if(temp != NULL){

        // first node
        if(prev == NULL)
            s = temp->next;

        // middle/end node
        else
            prev->next = temp->next;

        free(temp);
    }


    tempe = a;
    preve = NULL;

    while(tempe != NULL &&
          strcmp(tempe->name, name) != 0){

        preve = tempe;
        tempe = tempe->next;
    }

    // personality found
    if(tempe != NULL){

        // first node
        if(preve == NULL)
            a = tempe->next;

        // middle/end node
        else
            preve->next = tempe->next;

        free(tempe);
    }


    // we copy every line except the personality
    //
    FILE *tempFile = fopen("temp.txt", "w");if(tempFile == NULL)
        return s;

    rewind(f);

    char buffer[512];

    while(fgets(buffer, sizeof(buffer), f)){

        // we check if line starts with personality name
        if(strncmp(buffer,
                   name,
                   strlen(name)) != 0){

            fputs(buffer, tempFile);
        }
    }

    fclose(f);
    fclose(tempFile);


    // ---------------- REPLACE OLD FILE ----------------
    //
    remove("data.txt");

    rename("temp.txt", "data.txt");


    // return updated list
    return s;
}

/*=================== UPDATEPERSONALITY===============*/
TList* updatePersonality(FILE *f, TList *s, TList *a, char *name, char *definition, char *DoB, char *DoD){
  
  Edate tempDD;
  Edate tempDB;
  sscanf(DoB ,"%d/%d/%d",&tempDD.day,&tempDD.month,&tempDD.year);
  sscanf(DoD ,"%d/%d/%d",&tempDB.day,&tempDB.month,&tempDB.year);
  TList *current = s ;
  while (current != NULL){
    if (strcmp(current->name , name)==0){
        strcpy(current->name,name );
        strcpy(current->description,definition);
        current->dobearth.day=tempDD.day;
        current->dobearth.month=tempDD.month;
        current->dobearth.year=tempDD.year;
  }
  current = current->next;
}
 current = a;
 while (current != NULL){
    if (strcmp(current->name , name)==0){
        strcpy(current->name,name );
        strcpy(current->description,definition);
        current->dobearth.day=tempDD.day;
        current->dobearth.month=tempDD.month;
        current->dobearth.year=tempDD.year;
  }
  current = current->next;
 }
  f = fopen ("data.txt","r");
  FILE *tempe = fopen ("temp.txt","w");

  char buffer[255];
  char Name[65];
    
  while(fgets(buffer,sizeof(buffer),f)){
     sscanf(buffer, "%[^=]", Name);
     if (strcmp(Name,name)==0){
      
     fprintf(tempe, "%s=%s{%d/%d/%d-%d/%d/%d}\n",name ,definition,tempDB.day,tempDB.month,tempDB.year,tempDD.day,tempDD.month,tempDD.year  );
     }
     else{
        fputs(buffer,tempe);
     }
   }

 fclose(tempe);
 fclose(f);
  remove("data.txt");
  rename("temp.txt", "data.txt");
  return s;
}
/*=========similarpersonalities===== */
TList* similarPersonality(TList *s, char *word){

    TList *head = NULL;
    TList *tail = NULL;

    TList *temp = s;

    int birthYear;
    int deathYear;

    int found = 0;

 
    // we search for the personality whose name = word
    //
    while(temp != NULL){

        if(strcmp(temp->name, word) == 0){

            birthYear = temp->dobearth.year;
            deathYear = temp->dodeath.year;

            found = 1;
            break;
        }

        temp = temp->next;
    }

    //check if  personality not found
    if(found == 0)
        return NULL;


    // we search for simsilar personalities
    temp = s;

    while(temp != NULL){

        // avoid adding the same personality itself
        if(strcmp(temp->name, word) != 0){

            if(temp->dobearth.year == birthYear  &&

               temp->dodeath.year == deathYear){

                TList *newnode =
                createNode(temp->name,
                           temp->description,
                           temp->dobearth,
                           temp->dodeath);


                if(head == NULL){

                    head = tail = newnode;
                }

                else{

                    tail->next = newnode;
                    tail = newnode;
                }
            }
        }

        temp = temp->next;
    }return head;
}
/*=================== COUNT PERSONALITY =============*/
TList* countPersonality(TList *s, Edate *prt){
 TList *Person=NULL;
 TList *current=s;
 while(current!=NULL){
    if ((current->dobearth.day == prt->day && 
        current->dobearth.month == prt->month && 
        current->dobearth.year == prt->year)  &&
        (current->dodeath.day == prt->day && 
        current->dodeath.month == prt->month && 
        current->dodeath.year == prt->year)){
       Person=insertBegin(Person,current->name,current->description,current->dobearth,current->dodeath);
    }
  current = current->next ;
 }
 return Person ;
}
/* ================= PALINDROME P ================= */

Word* palindromeNameP(TList *head){

    TList *h=head;

    Word *p=NULL;
    Word *t=NULL;

    char line[255];

    while(h!=NULL){

        strcpy(line,h->description);

        char *word=strtok(line," ,.-\n\t");

        while(word!=NULL){

            if(ispalindrome(word))
                insertword(&p,&t,word);

            word=strtok(NULL," ,.-\n\t");
        }

        h=h->next;
    }

    return p;
}


/* ================= PALINDROME E ================= */

Word* palindromeNameE(TList *head){

    TList *h=head;

    Word *q=NULL;
    Word *t=NULL;

    char line[255];

    while(h!=NULL){

        strcpy(line,h->description);

        char *word=strtok(line," ,.-\n\t");

        while(word!=NULL){if(ispalindrome(word))
                insertword(&q,&t,word);

            word=strtok(NULL," ,.-\n\t");
        }

        h=h->next;
    }

    return q;
}


/* ================= MERGE WORDS ================= */

Word* merge(Word *l1,Word *l2){

    if(l1==NULL)
        return l2;

    if(l2==NULL)
        return l1;

    Word *temp=l1;

    while(temp->next!=NULL)
        temp=temp->next;

    temp->next=l2;

    return l1;
}


/* ================= PALINDROME NAME ================= */

Word* palindromeName(TList *l1,TList *l2){

    Word *h=palindromeNameP(l1);
    Word *k=palindromeNameE(l2);

    return sortwordlist(merge(h,k));
}


/* ================= MERGE NODES ================= */

DList* mergeNodes(TList *s,TList *a){

    TList *p=s;
    TList *q=a;

    DList *head=NULL;
    DList *tail=NULL;

    while(p!=NULL && q!=NULL){

        DList *newnode=
        (DList*)malloc(sizeof(DList));

        if(p->dobearth.year==-1){

            strcpy(newnode->name,p->name);
            strcpy(newnode->definition,
                   p->description);

            newnode->dobearth=q->dobearth;
            newnode->dodeath=q->dodeath;
        }

        else{

            strcpy(newnode->name,q->name);
            strcpy(newnode->definition,
                   q->description);

            newnode->dobearth=p->dobearth;
            newnode->dodeath=p->dodeath;
        }

        newnode->next=NULL;
        newnode->prev=tail;

        if(head==NULL)
            head=newnode;

        else
            tail->next=newnode;

        tail=newnode;

        p=p->next;
        q=q->next;
    }

    return head;
}


/* ================= MERGE2 NODES ================= */

TList* merge2Nodes(TList *s,TList *a){

    TList *h=s;

    TList *k=NULL;
    TList *t=NULL;

    while(h!=NULL){

        TList *p=a;

        while(p!=NULL){

            if(strcmp(h->name,p->name)==0){

                TList *node=
                createNode(h->name,
                           h->description,
                           p->dobearth,
                           p->dodeath);

                insertAnode(&k,&t,node);
            }p=p->next;
        }

        h=h->next;
    }

    return k;
}


/* ================= CREATE EVENT ================= */

TList* createEvent(char name[],
                   char description[],
                   Edate date){

    TList *event=
    (TList*)malloc(sizeof(TList));

    strcpy(event->name,name);
    strcpy(event->description,description);

    event->dobearth=date;

    event->dodeath.day=-1;
    event->dodeath.month=-1;
    event->dodeath.year=-1;

    event->next=NULL;

    return event;
}
/*================== ADD PERSONALITY =============*/
TList* addPersonality(TList *s, TList *a, char *name, char *DoB, char *DoD){

 TList* current ;
 // add the personality to the first list that contains only dates and definitions .
 current = s;
  while (current !=NULL){
    current = current->next;
  }
  TList *p=(TList*)malloc(sizeof(TList));
  strcpy(p->name,name);
  strcpy(p->description, "");// ther's no definition in the function parameters.
  p->dobearth.day = -1;
  p->dobearth.month = -1;
  p->dobearth.year = -1;

  p->dodeath.day = -1;
  p->dodeath.month = -1;
  p->dodeath.year = -1;

  current ->next=p;
  p->next=NULL;

  current = a;
 while (current !=NULL){
    current = current->next;
 }
 // conversion of dates from string to Edate so we can save them in the date field in the node .
 Edate tempDD;
  Edate tempDB;
  sscanf(DoB ,"%d/%d/%d",&tempDD.day,&tempDD.month,&tempDD.year);
  sscanf(DoD ,"%d/%d/%d",&tempDB.day,&tempDB.month,&tempDB.year);
 // adding the personality to the third list that contains name with dates .
  TList *q=(TList*)malloc(sizeof(TList));
  strcpy(q->name,name);
  strcpy(q->description, "");
  q->dobearth=tempDB;
  q->dodeath=tempDD;
  current ->next=q;
  q->next=NULL;

 // adding te personaliyt into the file (appending );
  
 FILE *f=fopen("data.txt","a");
 if (f!=NULL){
    fprintf(f,"%s=  :{%s-%s}",name,DoB,DoD);
    fclose(f);
 }
 return s;
} 


/* ================= ADD EVENTS ================= */

TList* addEvents(TList *b,
                 char *namEvente,
                 Edate date){

    char desc[255]="-------none--------";

    TList *newEvent=
    createEvent(namEvente,desc,date);

    if(b==NULL)
        return newEvent;

    TList *h=b;

    while(h->next!=NULL)
        h=h->next;

    h->next=newEvent;

    FILE *f=fopen("data.txt","a");

    if(f!=NULL){

        fprintf(f,
        "%s:%s{%d/%d/%d}\n",
        namEvente,
        desc,
        date.day,
        date.month,
        date.year);

        fclose(f);
    }

    return b;
}


/* ================= SORT NAME TO QUEUE ================= */

TQueue* sName(TList *s){

    TQueue *q = (TQueue*)malloc(sizeof(TQueue));
    q->head = NULL;
    q->tail = NULL;

    if(s == NULL)
        return q;

    TList *sorted = NULL;
    TList *current = s;

    while(current != NULL){

        TList *nextNode = current->next;
        current->next = NULL;  

        if(sorted == NULL  ||
           countWords(current->name) < countWords(sorted->name)){

            current->next = sorted;
            sorted = current;
        }
        else{
            TList *temp = sorted;

            while(temp->next != NULL &&
                  countWords(temp->next->name) <= countWords(current->name)){
                temp = temp->next;
            }

            current->next = temp->next;
            temp->next = current;
        }

        current = nextNode;
    }

    current = sorted;

    while(current != NULL){

        enqueue(q,
                current->name,
                current->description,
                current->dobearth,
                current->dodeath);

        current = current->next;
    }

    return q;
}
/*==============PAGE=======================*/
TQueue* ageP(TList *a){

    TQueue *q = (TQueue*)malloc(sizeof(TQueue));

    q->head = NULL;
    q->tail = NULL;

    if(a == NULL)
        return q;

    TList *sorted = NULL;
    TList *current = a;

    while(current != NULL){

        TList *nextNode = current->next;
        current->next = NULL;// insert at beginning
        if(sorted == NULL ||
           P_age(current) < P_age(sorted)){

            current->next = sorted;
            sorted = current;
        }

        // insert in middle/end
        else{

            TList *temp = sorted;

            while(temp->next != NULL &&
                  P_age(temp->next) <= P_age(current)){

                temp = temp->next;
            }

            current->next = temp->next;
            temp->next = current;
        }

        current = nextNode;
    }

    current = sorted;

    while(current != NULL){

        enqueue(q,
                current->name,
                current->description,
                current->dobearth,
                current->dodeath);

        current = current->next;
    }

    return q;
}
/* ================= TO QUEUE ================= */

TQueue* toQueue(TList *merged){

    TQueue *Q=
    (TQueue*)malloc(sizeof(TQueue));

    Q->head=NULL;
    Q->tail=NULL;

    TList *p=merged;

    while(p!=NULL){

        enqueue(Q,
                p->name,
                p->description,
                p->dobearth,
                p->dodeath);

        p=p->next;
    }

    return Q;
}



/*===============DISPLAY FUNCTIONS ===============================*/
void printList(TList *head){

    if(head==NULL){

        printf("\nList is empty.\n");
        return;
    }

    while(head!=NULL){

        printf("\n============================\n");

        printf("Name : %s\n",head->name);

        printf("Description : %s\n",
               head->description);

        printf("Birth : %d/%d/%d\n",
               head->dobearth.day,
               head->dobearth.month,
               head->dobearth.year);

        printf("Death : %d/%d/%d\n",
               head->dodeath.day,
               head->dodeath.month,
               head->dodeath.year);

        head=head->next;
    }
}

void printQueue(TQueue *Q){

    if(Q==NULL || Q->head==NULL){

        printf("\nQueue is empty.\n");
        return;
    }

    TList *p=Q->head;

    while(p!=NULL){

        printf("\n%s\n",p->name);

        p=p->next;
    }
}

void printWords(Word *head){

    if(head==NULL){

        printf("\nNo palindrome words.\n");
        return;
    }

    while(head!=NULL){

        printf("%s\n",head->word);

        head=head->next;
    }
}

void printDList(DList *head){

    if(head==NULL){

        printf("\nDoubly list empty.\n");
        return;
    }

    while(head!=NULL){

        printf("\n============================\n");

        printf("Name : %s\n",head->name);

        printf("Definition : %s\n",
               head->definition);
 
        printf("Birth : %d/%d/%d\n",
               head->dobearth.day,
               head->dobearth.month,
               head->dobearth.year);

        printf("Death : %d/%d/%d\n",
               head->dodeath.day,
               head->dodeath.month,
               head->dodeath.year);

        head=head->next;
    }
}
#endif
