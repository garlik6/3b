#include <stdio.h>
#include <malloc.h>

typedef struct Item {
    char c;
    struct Item *next;
}Item;

typedef enum { false, true } bool;

void deleteList(struct Item *pItem);

void Drop_List(Item *pItem);


int getList(Item ** pptr)
{
    char buf[81],*str;
    Item head = {'*',NULL};
    Item *last = &head;
    int n, rc = 1;
    do {
        n = scanf("%80[^\n]",buf);
        if(n < 0){
            deleteList(head.next);
            head.next = NULL;
            rc = 0;
            continue;
        }
        if(n > 0){
            for(str = buf; *str != '\0'; ++str)
            {
                last->next = (Item *)malloc(sizeof(Item));
                last = last->next;
                last->c = *str;
            }
            last->next = NULL;
        }else
            scanf("%*c");
    } while(n > 0);
    *pptr = head.next;
    return rc;
}

void deleteList(Item *pItem) {
    Item *pItem_buf=pItem;
    while (pItem_buf!=NULL){
        pItem_buf=pItem->next;
        free(pItem);
        pItem=pItem_buf;
    }
}

void Three_simbol_check(Item ** pItem)
{ Item *pList1=*pItem;
    Item head = {'*',NULL};
    Item *pList2=&head;
    Item * BUF;
    int FLAG1,FLAG2;
    while (pList1!=NULL) {
        FLAG1=0;
        FLAG2=0;
        while (pList1->c == ' ') {
            BUF = pList1->next;
            free(pList1);
            if(BUF==NULL) break;
            pList1=BUF;
        }

        if(BUF==NULL) break;

        BUF = pList1;

        for (int i = 0; i < 3; i++) {

            {
                if(pList1==NULL || pList1->c==' ')
                    FLAG1++;
                if(pList1!=NULL)pList1 = pList1->next;
            }
        }

        if (( pList1 == NULL || pList1->c == ' ' ) && FLAG1 == 0) {
            pList1 = BUF;
            pList2->next = pList1;
            for (int i = 0; i <3; i++) {
                pList2 = pList2->next;
                if(pList1!=NULL)pList1=pList1->next;
            }
            if( pList2!=NULL && pList2->next!=NULL) {
                pList2 = pList2->next;
                FLAG2++;
            }
            else
            if(pList2!=NULL)pList2->next=NULL;
        } else FLAG1++;

        if(pList1==NULL)
            break;

        if(FLAG1!=0)pList1 = BUF;

        while ( pList1->c!=' ') {
            BUF = pList1->next;
            free(pList1);
            if(BUF==NULL)
                break;
            pList1=BUF;
        }
        if (FLAG2!=0)pList1=pList1->next;
    }
//    if(pList2->c==' ')
//        pList2=NULL;
//    else
    pList2->next=NULL;
    *pItem=head.next;
}

int main() {
    Item *List;
    while (getList(&List)!=0){
        Three_simbol_check(&List);
        Drop_List(List);
        deleteList(List);
    }
    return 0;
}

void Drop_List(Item *pItem) {
    char c;

    while(pItem!=NULL)
    {
        c=pItem->c;
        printf("%c",c);
        pItem=pItem->next;
    }
    printf("\n");
}