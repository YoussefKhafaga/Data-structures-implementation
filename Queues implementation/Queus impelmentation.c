#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char *name;
    int starting_time;
    int remaining_time;
} Process;
typedef struct Node
{
    Process data;
    struct Node* next;
} Node;
typedef struct
{
    Node *head;
    Node *tail;
}  Queue;
Queue* init ()
{
    Queue *q=malloc(sizeof(Queue));
    q->head=NULL;
    q->tail=NULL;
    return q;
}
void enqueue(Queue *q,Process val)
{
    Node *n=malloc(sizeof(Node));
    n->next=NULL;
    n->data=val;
    if (q->head==NULL)
        q->head=q->tail=n;
    else
    {
        q->tail->next=n;
        q->tail=n;
    }
}
Process dequeue(Queue *q)
{
    Process val;
    if(q->head)
    {
        Node*temp=malloc(sizeof(Node));
        temp->next=NULL;
        val=q->head->data;
        temp=q->head;
        q->head=temp->next;
        free(temp);
        if(q->head==NULL)
            q->tail=NULL;
    }
    return val;

}

int isempty(Queue *q)
{
    return q->head==NULL?-1:0;
}
void destroy (Queue *q)
{
    free(q);
}
void RoundRobin(char* filename)
{
    int i=0,n,count=0,j;
    Queue *q=init();
    FILE *f=fopen(filename,"r");
    char *x;
    x=malloc(100);
    Process *p,res;
    p=malloc(100*sizeof(Process));
    fscanf(f,"%[^=]=",x);
    fscanf(f,"%s",x);
    while(!feof(f))
    {
        p[count].name=malloc(20);
        fscanf(f,"%s",p[count].name);
        fscanf(f,"%d",&p[count].starting_time);
        fscanf(f,"%d",&p[count].remaining_time);
        count++;
    }
    fclose(f);
    for(i=0; i<atoi(x); i++)
    {
        for(j=0; j<count; j++)
        {

            if(p[j].starting_time==i)
            {
                enqueue(q,p[j]);
            }
        }
        if(isempty(q)==-1)
        {
            printf("idle (%d-->%d)\n",i,i+1);
        }
       else if (isempty(q)!=-1)
        {  res=dequeue(q);
        res.remaining_time--;
            if(res.remaining_time==0)
            {
                printf("%s (%d-->%d) %s aborts\n",res.name,i,i+1,res.name);
            }
            else
            {
                printf("%s (%d-->%d)\n",res.name,i,i+1);
                enqueue(q,res);

            }
        }
    }
        printf("stop\n");
        destroy(q);
        free(x);
        free(p);
    }

int main()
{
    //char filename[261];
    //puts("Enter file name or Ctrl+Z to exit:");
    //puts("----------------------------------");
    //while(fgets(filename, 260, stdin) != NULL)
    //{
    //    filename[strlen(filename)-1]='\0';
        if(fopen("a.txt","r"))
            RoundRobin("a.txt");
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("Enter file name or Ctrl+Z to exit:");
    //}

    return 0;
}
