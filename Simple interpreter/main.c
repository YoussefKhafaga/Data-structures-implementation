#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXSIZE 100
typedef union
{
    float fData;
    char  cData;
} Item;
typedef struct
{
    int top;
    Item items[MAXSIZE];
} Stack;
typedef struct
{
    struct Node* left;
    struct Node* right;
    char *variable;
    float data;
} Node;
typedef struct {
    char *variableName;
    float value;
}heap;
void display(heap arr[100],int n);
int add(heap arr[100],int n,float value,char *variable);
void heapify(heap arr[100],int n);

int add(heap arr[100],int n,float value,char *variable)
{
    arr[n].variableName=(char*)malloc(strlen(variable)+1);
    strcpy(arr[n].variableName,variable);
    arr[n].value=value;
    n++;
    return n;
}
void siftUp(heap arr[], int n, int i)
{

    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    heap temp;
    if (l < n && arr[l].value > arr[largest].value)
        largest = l;
    if (r < n && arr[r].value > arr[largest].value)
        largest = r;
    if (largest != i)
    {
        temp=arr[i];
        arr[i]=arr[largest];
        arr[largest]=temp;
        siftUp(arr, n, largest);
    }
}
void heapSort(heap arr[], int n)
{
    heap temp;
    for (int i = n / 2 - 1; i >= 0; i--)
        siftUp(arr, n, i);

    for (int i=n-1; i>0; i--)
    {
        temp=arr[0];
        arr[0]=arr[i];
        arr[i]=temp;

        siftUp(arr, i, 0);
    }
}
void display(heap arr[100],int n)
{
    int i;
    for(i=0; i<n;i++)
    {
        if((int)arr[i].value==arr[i].value)
            printf("%s = %d\n",arr[i].variableName,(int)arr[i].value);
        else
    printf("%s = %.2f\n",arr[i].variableName,arr[i].value);
    }
}
Node* newNode(char *word,float k);
Node* search(Node* root, char* key);
Node* insert(Node* root,char *word,float k);
int max(int x,int y );
int height(Node* root);
int count(Node* root);
Node *root=NULL;
int g=0;
heap arr[100];
Node* newNode(char *word,float k)
{
    Node* n=malloc(sizeof(Node));
    n->variable=(char*)malloc(strlen(word)+1);
    strcpy(n->variable,word);
    n->data=k;
    n->left=NULL;
    n->right=NULL;
    return n;
}
Node* insert(Node* root,char *word,float k)
{
    if(root==NULL)
        return newNode(word,k);
        if(stricmp(root->variable,word)==0)
            root=newNode(word,k);
    else if(stricmp(word,root->variable) < 0)
        root->left= insert(root->left,word,k);
    else
        root->right=insert(root->right,word,k);
    return root;
}
Node* search(Node* root, char *key)
{
    if (root == NULL)
        return NULL;
    else if (stricmp(root->variable,key)==0)
        return root;
    else if (stricmp(root->variable,key)>0)
        return search(root->left, key);
    else
        return search(root->right, key);
}
void inOrderTraverse(Node *root)
{
    if(root)
    {
        inOrderTraverse(root->left);
        if((int)root->data==root->data)
        printf("%s = %d\n",root->variable,(int)root->data);
        else
        printf("%s = %.2f\n",root->variable,root->data);
        inOrderTraverse(root->right);
    }
}
int max(int x,int y )
{
    return x>y?x:y;
}
int height(Node* root)
{
    if(root==NULL)
        return -1;
    else
        return 1 + max(height(root->left),height(root->right));
}
int count(Node* root)
{
    if(root==NULL)
        return 0;
    else
        return 1+count(root->left)+count(root->right);
}
Stack * initialize()
{
    Stack *s=malloc(sizeof(Stack));
    s->top=-1;
    return s;
}
int isEmpty(Stack *s)
{
    if(s->top==-1)
        return 1;
    else
        return 0;
}
int isFull(Stack *s)
{
    if (s->top==MAXSIZE-1)
        return 1;
    else
        return 0;
}
Item top(Stack *s)
{
    return s->items[s->top];
}
Item pop(Stack *s)
{
    if(isEmpty(s))
    {
        printf("Stack is empty\n");
        exit(-1);
    }
    else
        return s->items[s->top--];
}
void push(Stack *s, Item val)
{
    if (isFull(s))
        printf("Stack is full");
    else
        s->items[++s->top]=val;
}
int isoperator(char c)
{
    if(c=='^'||c=='/'||c=='*'||c=='+'||c=='-')
        return 1;
    else
        return 0;
}
int precedence(char c)
{
    switch(c)
    {
    case '+':
    case '-':
        return 1;
        break;
    case '*':
    case '/':
        return 2;
        break;
    case '^':
        return 3;
    }

}
float evaluatePostfix(char* postfix)
{
    Stack *s = initialize();
    Item itemx;
    char foo[100];
    strcpy(foo,postfix);
    char *token = strtok(foo, " ");
    while (token!='\0')
    {
        if(token[0]=='^'||token[0]=='*'||token[0]=='/'||token[0]=='+'||(token[0]=='-'&&!atof(token)))
        {
            float a, b;
            a=pop(s).fData;
            b=pop(s).fData;
            switch(token[0])
            {
            case '+':
                itemx.fData= a+b;
                push(s,itemx);
                break;
            case '-':
                itemx.fData=b-a;
                push(s,itemx);
                break;
            case '*':
                itemx.fData=a*b;
                push(s,itemx);
                break;
            case '/':
                itemx.fData=b/a;
                push(s,itemx);
                break;
            case '^':
                itemx.fData=pow(b,a);
                push(s,itemx);
                break;
            }
        }
        else
        {
            itemx.fData=atof(token);
            push(s,itemx);
        }
        token=strtok(NULL," ");
    }
    return pop(s).fData;
}
void infixToPostfix(char *infix,char *postfix)
{
    Stack *s = initialize();
    Item c;
    int i=0,j=0,p=0;
    char *word;
    word=malloc(20);
    int flag=0;
    char *searchedvariable;
    searchedvariable=(char*)malloc(20);
    char *searchVariable;
    searchVariable=malloc(20);
    float z;
    while(infix[i]!='=')
    {
        if((infix[i+1]=='=')&&(infix[i]==' '))
            break;
        word[p++]=infix[i++];
    }
    word[p]='\0';
    Node *n;
    n=(Node*)malloc(sizeof(Node));
    int m=0,o=0;
   for(i;i<strlen(infix);i++)
    {
        c.cData=infix[i];
        if(infix[i]=='(')
        {
            push(s,c);
        }
        else if(infix[i]=='=') continue;
        else if(infix[i]==')')
        {
            while(!isEmpty(s)&& top(s).cData!='(')
            {
                postfix[j++]=pop(s).cData;
                postfix[j++]=' ';
            }
            pop(s);
        }
        else if(infix[i]=='^'||infix[i]=='*'||infix[i]=='/'||infix[i]=='+'|| ((infix[i]=='-')&&(isdigit(infix[i-1]))) || ( ( infix[i]=='-' ) && ( infix[i-1]==' ' ) && ( isdigit(infix[i-2] ) ) ) || ((infix[i]=='-')&&(isalpha(infix[i-1]))) || ( ( infix[i]=='-' ) && ( infix[i-1]==' ' ) && ( isalpha(infix[i-2] ) ) ))        {
            while(!isEmpty(s)&&precedence(infix[i])<=precedence(top(s).cData) && top(s).cData!='(')
            {
                postfix[j++]=pop(s).cData;
                postfix[j++]=' ';

            }
                push(s,c);
        }
        else if (isalpha(infix[i]))
        {
            m=0;o=0;
            while(isalpha(infix[i]))
            {
                searchedvariable[m++]=infix[i++];
            }
            i--;
            searchedvariable[m]='\0';
            n=search(root,searchedvariable);
            z=n->data;
            snprintf(searchVariable,50,"%0.2f",z);
            while(searchVariable[o])
            {
                postfix[j++]=searchVariable[o++];
            }
            postfix[j++]=' ';
        }
        else
        {
            postfix[j++]=infix[i];
            if(!isdigit(infix[i+1])&&infix[i+1]!=' '&&infix[i+1]!='.'){
            postfix[j++]=' ';
            }
        }
    }
    while(!isEmpty(s))
        {postfix[j++]=pop(s).cData;
        postfix[j++]=' ';}
        postfix[j]='\0';
    float value=evaluatePostfix(postfix);
    root=insert(root,word,value);
    g=add(arr,g,value,word);
}
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
void equalValidation(char *c)
{
    int k=0;
    for(int i=0; i<strlen(c); i++)
    {
        if(c[i] == '=')
        {
            k++;
        }
    }
    if(k!=1)
    {
        printf("Error\nThe equal sign is missing");
        exit(0);
    }
}
void symbolValidation(char *c)
{
    int i,k;
    for(i=0; i<strlen(c); i++)
    {
        if(isdigit(c[i])||c[i] == '=' ||c[i] == '+' ||c[i] == '-' ||c[i] == '/' ||c[i] == '*' ||c[i] == '^'||c[i] == '(' ||c[i] == ')' || c[i]==' ')
        {
            k=1;
        }
        else
            k=0;
    }
    if(!k)
    {
        printf("Error\nThere is a wrong symbol");
        exit(0);
    }

}
void oneVariableValidation(char *c)
{

    int i,j,k=1;
    for(i=0; i<strlen(c); i++)
    {
        if (c[i]=='=')
            break;
        else if(c[i]==' '||c[i] == '+' ||c[i] == '-' ||c[i] == '/' ||c[i] == '*' ||c[i] == '^'||c[i] == '(' ||c[i] == ')')
        {
            for(j=i+1; j<strlen(c)-i; j++)
            {
                if (c[j]=='=')
                    break;
                else if(isalpha(c[j]))
                    k=0;
            }
        }
    }
    if(!k)
    {
        printf("Error\nThere is two variables in the left hand side");
        exit(0);
    }
}
void loadFile()
{
    FILE *f=fopen("src.txt","r");
    if(!f)
        printf("----File not found----\n");
    char *infix;
    infix=malloc(50);
    char *postfix;
    postfix=malloc(50);
    while(!feof(f))
    {
        fgets(infix,100,f);
        replaceNewLineBySpace(infix);
        equalValidation(infix);
        oneVariableValidation(infix);
        symbolValidation(infix);
        infixToPostfix(infix,postfix);
    }
}
int main(int argc, char**argv)
{
    loadFile();
    printf("Ordered by variable name using binary trees \n");
    inOrderTraverse(root);
    printf("--------------------------------------------\n");
    printf("Ordered by value using heaps \n");
    heapSort(arr,g);
    display(arr,g);
    return 0;
}
