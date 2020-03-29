#include<stdio.h>
#include<stdlib.h>


struct node
{
    int data;
    struct node* next;
};


struct node *create(int data)
{
    struct node *temp = (struct node *) malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}


void push(struct node** head, int data)
{
    struct node* temp = create(data);
    temp->next = (*head);
    (*head) = temp;
}

struct node* copyNode(struct node *list1)
{
    struct node* list2=NULL;
    struct node* temp1;
    temp1=list1;
    while(temp1!=NULL)
    {
        int n = temp1->data;
        temp1=temp1->next;
        push(&list2,n);
    }
    return list2;
}

void input(struct node** head, char* str)
{
    int i,j,k,l,m,n,p;
    for(i=0;str[i]!='\0';i++);
    k=i%4;
    l=i/4;
    n=0;
    for(j=0;j<k;j++)
    {
        n=n*10+(int)(str[j]-'0');
    }
    push(head,n);
    for(p=0;p<l;p++)
    {
        n=0;
        for(j=k;j<k+4;j++)
        {
            n=n*10+(int)(str[j]-'0');
        }
        k=k+4;
        push(head,n);
    }
}


struct node* add(struct node* first, struct node* second)
{
    struct node* res = NULL;
    struct node *temp, *prev = NULL;
    int carry = 0, sum;
    while (first != NULL || second != NULL)
    {
        sum = carry + (first? first->data: 0) + (second? second->data: 0);
        carry = (sum >= 10000)? 1 : 0;
        sum = sum % 10000;
        temp = create(sum);
        if(res == NULL)
            res = temp;
        else
            prev->next = temp;
        prev  = temp;
        if (first) first = first->next;
        if (second) second = second->next;
    }
    if (carry > 0)
      temp->next = create(carry);
    return res;
}

struct node* sub(struct node* first, struct node* second)
{
    struct node* res = NULL;
    struct node *temp, *prev = NULL;
    int diff, f=0, s=0, flag=0;
    while (first != NULL )
    {
        f = ((flag==0)?first->data:first->data-1);
        s = ((second)?second->data:0);
        if(s<=f)
        {
            diff = f-s;
            flag = 0;
        }
        else
        {
            diff = f + 10000 - s;
            flag = 1;
        }
        temp = create(diff);
        if(res == NULL)
            res = temp;
        else
            prev->next = temp;
        prev  = temp;
        if (first) first = first->next;
        if (second) second = second->next;
    }
    return res;
}


struct node* printList(struct node *node)
{
    struct node *node2 = NULL;
    struct node *node3 = NULL;
    node2=copyNode(node);
    while(node2 != NULL)
    {
        printf("%d", node2->data);
        node2 = node2->next;
    }
    printf("\n");
    node3=copyNode(node2);
    return node3;
}

void main()
{
    struct node* res1 = NULL;
    struct node* res2 = NULL;
    struct node* first = NULL;
    struct node* second = NULL;
    char str1[20],str2[20];
    int i,j;
    printf("\nEnter First Number :");
    scanf("%s",str1);
    printf("\nEnter Second Number :");
    scanf("%s",str2);
    input(&first,str1);
    input(&second,str2);
    res1 = add(first, second);
    res2 = sub(first, second);

    printf("First Number  : ");
    j=strlen(str1);
    for(i=0;i<35-j;i++)
        printf(" ");
    first=printList(first);

    printf("Second Number : ");
    j=strlen(str2);
    for(i=0;i<35-j;i++)
        printf(" ");
    second=printList(second);


    printf("SUM           : ");
    j=(strlen(str1)>strlen(str2))?strlen(str1):strlen(str2);
    for(i=0;i<35-j;i++)
        printf(" ");
    res1=printList(res1);

    printf("DIFFERENCE    : ");
    j=(strlen(str1)>strlen(str2))?strlen(str1):strlen(str2);
    for(i=0;i<35-j;i++)
        printf(" ");
    res2=printList(res2);

}
