#include <stdio.h>
#include <stdlib.h>
#include "LinkList.h"

int main()
{
    int a[] = {1,2,3,4,5,6,7,8};
    LinkList* list = createByArr(a, 0, sizeof(a)/sizeof(int));
    insert(list, createNode(0), 0);
    list = reverseList(list);
    LinkNode* p = NULL;
    int len = 0;
    for(p = list->head; p != NULL; p = p->next) {
        len++;
        printf("NO %d element is: %d\n", len, p->data);
    }
    LinkNode* del = removeList(list, 3);
    p = get(list, 3);
    free(del);
    printf("NO %d element is: %d\n", 0, p->data);

    return 0;
}
