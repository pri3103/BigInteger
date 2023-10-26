#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"

void display(struct BigInteger b1) 
{ 
    struct node *temporary=b1.l;
    if (b1.sign==0)
    {
        printf("-");
    }
    while(temporary!=NULL)
    {
        printf("%d",temporary->info);
        temporary=temporary->next;
    }
    printf("\n");
}

struct BigInteger allocate(int count)
 {
    struct BigInteger b ;
    b.size = 0;
    b.sign = 1;
    b.count = count;
    b.l = NULL;
    return b;
}

int length (struct node *b)
{
    int l=0;
    while (b)
    {
        l++;
        b=b->next;
    }
    return l;
}

struct node* NewNode(int val)
{
    struct node* newnode=(struct node*)malloc(sizeof(struct node));
    newnode->info=val;
    newnode->next=NULL;
    return newnode;
}

struct BigInteger initialize(char *str) 
{ 
    struct BigInteger b = allocate (strlen(str));
    int len = strlen(str);
    b.size = len;
    if (str[0] == '-') 
    {
        b.sign = 0;
        b.size--; // Decrease size if the number is negative
    }
    
    for (int i = 0; i < len; i++) 
    {
        char c = str[len - i -1];
        if (c >= '0' && c <= '9') 
        {
            int d = c - '0';
            struct node *temporary = (struct node *)malloc(sizeof(struct node));
            temporary->info = d;
            temporary->next = b.l;
            b.l = temporary; // Update the linked l
        }
    }
    return b;
}

struct node* reverse(struct node *head) 
{
    struct node *curr = head;
    struct node *nxt = NULL;
    struct node *prev = NULL;
    
    while (curr) {
        nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
    }
    
    return prev;
}

struct BigInteger dupl(struct BigInteger b1) 
{
    struct BigInteger ret;
    ret.count = b1.count;
    ret.size = b1.size;
    ret.sign = b1.sign;
    ret.l = NULL; 
    struct node *current = b1.l;
    struct node *prev = NULL;
    struct node *newDigits = NULL;

    while (current) 
    {
        struct node *newNode = NewNode(current->info);
        if (!prev) 
        {
            ret.l = newNode;  
        } 
        else 
        {
            prev->next = newNode; 
        }
        prev = newNode;
        current = current->next;
    }

    return ret;
}

int is_null(struct BigInteger a)
{
    struct node *n = duplicate(a.l);
    while (n)
    {
        if (n->info != 0)
        {
            return 1;
        }
        n=n->next;
    }
    return 0;
}

int comp(struct BigInteger b1,struct BigInteger b2)
{
    struct node *head1=reverse(duplicate(b1.l));
    struct node *head2=reverse(duplicate(b2.l));
    while (head1->info == 0)
    {
        head1=head1->next;
    }
    while (head2->info == 0)
    {
        head2=head2->next;
    }
    while (head1)
    {
        if (head1->info > head2->info)
        {
            return 1;
        }
        else if (head1->info < head2->info)
        {
            return 2;
        }
        else 
        {
            return 0;
        }
        head1=head1->next;
        head2=head2->next;
    }
}

struct node* duplicate(struct node *b1) 
{
    struct node *l = NULL; 
    struct node *current = b1;
    struct node *prev = NULL;
    struct node *newDigits = NULL;

    while (current) 
    {
        struct node *newNode = NULL;
        newNode = NewNode(current->info);
        if (!prev) 
        {
            l= newNode;  
        }
        else 
        {
            prev->next = newNode; 
        }
        prev = newNode;
        current = current->next;
    }

    return l;
}

void push(struct node** head, int info)
{
    struct node* new_node = NewNode(info);
    new_node->next = (*head);
    (*head) = new_node;
}

struct node* empty_l(int size)
{
    struct node* head = NULL;
    while (size--)
        push(&head, 0);
    return head;
}

struct BigInteger add(struct BigInteger b1,struct BigInteger b2)
{
    if (!b1.size || (is_null(b1)==0))
    {
        return b2;
    }
    if (!b2.size || (is_null(b2)==0))
    {
        return b1;
    }
    
    struct BigInteger res;
    struct node *itr=NULL; 
    struct node *resnode=NULL;
    res.size=0;
    res.sign=1;
    res.l=NULL;
    if (b1.sign == 0 && b2.sign == 1)
    {
        b1.sign=1;
        res=sub(b2,b1);
        return res;
    }
    if (b1.sign == 1 && b2.sign== 0)
    {
        b2.sign=1;
        res=sub(b1,b2);
        return res;
    }
    int l1=length(b1.l);
    int l2=length(b2.l);
    struct node *n1=NULL,*n2=NULL;
    if (l1>l2)
    {
        n1=duplicate(reverse(b1.l));
        n2=duplicate(reverse(b2.l));
    }
    else
    {
        n1=duplicate(reverse (b2.l));
        n2=duplicate(reverse (b1.l));
    }
    while ((n1!=NULL) && (n2!=NULL))
    {
        res.size++;
        int d=n1->info+n2->info;
        if (d>9)
        {
            d-=10;
            if (!n1->next)
            {
                n1->next=NewNode(1);
            }
            else
            {
                n1->next->info++;
            }    
        }
        if (!(resnode))
        {
            resnode=NewNode(d);
            itr=resnode;
            n1=n1->next;
            n2=n2->next;

        }
        else
        {
            itr->next=NewNode(d);
            itr=itr->next;
            n1=n1->next;
            n2=n2->next;
        }
    }
    while (n1)
    {
        res.size++;
        itr->next=NewNode(n1->info);
        itr=itr->next;
        n1=n1->next;
    }
    while (n2)
    {
        res.size++;
        itr->next=NewNode(n2->info);
        itr=itr->next;
        n2=n2->next;
    }
    res.count=res.size;
    if (b1.sign == 0 && b2.sign == 0)
    {
        res.sign=0;
    }
    res.l=reverse(resnode);
    return res;
}

struct BigInteger sub(struct BigInteger b1,struct BigInteger b2)
{
    if (!b1.size || (is_null(b1)==0))
    {
        b2.sign = 0;
        return b2;
    }
    if (!b2.size || (is_null(b2)==0))
    {
        return b1;
    }
    struct BigInteger res;
    struct node *resnode=NULL;
    res.size=0;
    res.sign=1;
    res.l=NULL;
    if (b1.sign == 0 && b2.sign == 1)
    {
        b1.sign=1;
        res=add(b2,b1);
        res.sign=0;
        return res;
    }
    if (b2.sign == 0)
    {
        b2.sign=1;
        res=add(b1,b2);
        return res;
    }
    int l1=length(b1.l);
    int l2=length(b2.l);
    struct node *h1=NULL;
    struct node *h2=NULL;
    if (l1<l2)
    {
        h1=reverse(b2.l);
        h2=reverse (b1.l);
    }
    else if (l1==l2)
    {
        if (comp(b1,b2)==2)
        {
            h1=reverse (b2.l);
            h2=reverse(b1.l);
            res.sign=0;
        }
        else
        {
            h1=reverse (b1.l);
            h2= reverse ( b2.l);
        } 
    }
    else
    {
        h1=  reverse ( b1.l);
        h2= reverse( b2.l);
    }
    struct node *itr = NULL; //(struct node)malloc(sizeof(struct node));
    while ((h1!=NULL) && (h2!=NULL))
    {
        res.size++;
        int d=h1->info-h2->info;
        if (d<0)
        {
            if (!h1->next)
            {
                res.sign=0;
                d=0;
            }
            else
            {
                if (h1->next->info <= 0)
                {
                    h1->next->info +=10;
                    h1->next->next->info --;
                }
                h1->next->info--;
                d+=10;
            }
        }
        if (!(resnode))
        {
            resnode=NewNode(d);
            itr=resnode;
            h1=h1->next;
            h2=h2->next;

        }
        else
        {
            itr->next=NewNode(d);
            itr=itr->next;
            h1=h1->next;
            h2=h2->next;
        }
    }
    while (h1)
    {
        res.size++;
        itr->next=NewNode(h1->info);
        itr=itr->next;
        h1=h1->next;
    }
    while (h2)
    {
        res.size++;
        itr->next=NewNode(h2->info);
        itr=itr->next;
        h2=h2->next;
    }
    res.count=res.size;
    if (l1<l2)
    {
        res.sign=0;
    }
    struct node *s=duplicate(resnode);
    struct node *x=s;
    while (s->next)
    {
        if (s->info < 0)
        {
            s->info+=10;
            s->next->info --;
        }
        s=s->next;
    }
    resnode=duplicate(x);
    res.l=reverse(resnode);
    return res;
}

int compare(struct BigInteger d,struct BigInteger b)
{
    struct BigInteger s = sub(dupl(d),dupl(b));
    //display(s);
    if (s.sign == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

struct BigInteger mul(struct BigInteger b1, struct BigInteger b2)
{
    if (!b1.size || (is_null(dupl(b1))==0))
    {
        return b1;
    }
    if (!b2.size || (is_null(dupl(b2))==0))
    {
        return b2;
    }
    struct node *first =b1.l;
    struct node *second =b2.l;
    int m =length (first) , n = length(second);
    struct BigInteger result = allocate (m + n + 1);
    struct node* res= empty_l(m + n + 1);
 
    struct node *second_ptr = second,*result_ptr1 = res, *result_ptr2, *first_ptr;
 
    while (second_ptr) 
    {
 
        int carry = 0;
 
        result_ptr2 = result_ptr1;
 
        first_ptr = first;
 
        while (first_ptr) 
        {
            int multi = first_ptr->info * second_ptr->info + carry;
            result_ptr2->info += multi % 10;
            carry = multi / 10 + result_ptr2->info / 10;
            result_ptr2->info = result_ptr2->info % 10;
 
            first_ptr = first_ptr->next;
            result_ptr2 = result_ptr2->next;
        }
        if (carry > 0) 
        {
            result_ptr2->info += carry;
        }
 
        result_ptr1 = result_ptr1->next;
        second_ptr = second_ptr->next;
        result.size++;
    }

    res=reverse(res);
    int s = res->info;
    s = s / 100;
    while (res->info == 0) 
    {
        struct node* temporary = res;
        res = res->next;
        free(temporary);
        result.size--;
    }
    res=reverse(res);
    result.l=res;

    if ((b1.sign == 0  && b2.sign == 1)) 
    {
        result.sign=0;
    }
    if ((b2.sign == 0  && b1.sign == 1))
    {
        result.sign=0;
    }
    return result;
}

struct BigInteger div1(struct BigInteger b1,struct BigInteger b2)
{
    struct BigInteger a1=dupl(b1);
    a1.sign=1;
    struct BigInteger a2=dupl(b2);
    a2.sign=1;
    long long int quotient=0;
    struct BigInteger q;
    if (!b1.size || (is_null(dupl(a1))==0))
    {
        q.l=NewNode(0);
        return q;
    }
    if (compare(dupl(a1),dupl(a2))==0)
    {
        q.l=NewNode(0);
        return q;
    }
    if (!b2.size || (is_null(dupl(a2))==0))
    {
        printf ("Division doesn't exist.\n");
        q.l=NewNode(0);
        return q;
    }
    struct BigInteger a=sub(dupl(a1),dupl(a2));
    int l=is_null(a);
    if (l==0)
    {
        q.l=NewNode(1);
        return q;
    }
    while (compare(dupl(a1),dupl(a2)))
    {
        quotient++;
        a1=sub(dupl(a1),dupl(a2));
    }      
    struct node *l= NewNode(quotient);
    q.l = duplicate(l);
    if ((b1.sign == 0  && b2.sign == 1)) 
    {
        q.sign=0;
    }
    if ((b2.sign == 0  && b1.sign == 1))
    {
        q.sign=0;
    }
    return q;
}

struct BigInteger mod(struct BigInteger b1,struct BigInteger b2)
{
    struct BigInteger m;
    if (!b1.size || (is_null(dupl(b1))==0))
    {
        m.l=NewNode(0);
        return m;
    }
    if (compare(dupl(b1),dupl(b2))==0)
    {
        return b2;
    }
    if (!b2.size || (is_null(dupl(b2))==0))
    {
        m.l=NewNode(0);
        return m;
    }
    struct BigInteger a1=dupl(b1);
    a1.sign=1;
    struct BigInteger a2=dupl(b2);
    a2.sign=1;
    struct BigInteger a=sub(dupl(a1),dupl(a2));
    int l=is_null(a);
    if (l==0)
    {
        m.l=NewNode(0);
        return m;
    }
    while (compare(dupl(a1),dupl(a2)))
    {
        a1=sub(dupl(a1),dupl(a2));
    }
    if (a1.l==NULL)
    {
        m.l=NewNode(0);
        return m;
    }
    m=dupl(a1);
    if (b1.sign == 0) 
    {
        m.sign=0;
    }
    return m;
}