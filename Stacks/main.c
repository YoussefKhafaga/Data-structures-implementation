#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#include <ctype.h>
#include <math.h>
typedef union
{
    char cData;
    float fData;

} item;
typedef struct
{
    item ar[MAX];
    int surface;
} stack;

stack *intialization()
{
    stack *s=malloc(sizeof(stack));
    s->surface=0;
    return s;
}
void push(stack *s,item value)
{
    s->surface++;
    s->ar[s->surface]=value;
}

item pop(stack *s)
{
    return s->ar[s->surface--];
}

item top(stack *s)
{
    return s->ar[s->surface];
}
int isempty(stack *s)
{
    return s->surface==0?0:1;
}
int priority(char c)
{
    switch(c)
    {
        case '^':
        {
            return 3;
            break;
        }
        case '*':
        {
            return 2;
            break;
        }
        case '/':
        {
            return 2;
            break;
        }
        case '%':
        {
            return 2;
            break;
        }
        case '+': {
            return 1;
            break ;
        }
        case '-': {
        return 1;
        break ;
        }
        default :
            return 0;
    }
}

void infixtopostfix(char *infix,char *postfix)
{
    stack *s=intialization();
    item myitem;
    int flag=0,o,k;
    char *token;
    char tok[2];
    tok[1]='\0';
    token=malloc(100);
    token=strtok(infix," ");
    while (token)
    {
        if (token[0]=='(') {
            myitem.cData=token[0]; push(s,myitem);  }
        else if (token[0]==')')
        {
            while (top(s).cData!='(')
            {
                tok[0]=pop(s).cData;
                strcat(postfix,tok);
                strcat(postfix," ");
            }
            pop(s).cData;

        }
       else if (token[0]=='+' || token[0]=='-' && !atof(token) || token[0]=='*' || token[0]=='/' || token[0]=='^')
        {
            if (!isempty(s)|| top(s).cData=='(') { myitem.cData=token[0]; push(s,myitem); strcat(postfix," "); }
            else {
            o=priority(token[0]);
            k=priority(top(s).cData);
            if(o==k) {tok[0]=pop(s).cData;   strcat(postfix,tok);    strcat(postfix," ");    myitem.cData=token[0]; push(s,myitem);}
            if (o>k) {myitem.cData=token[0]; push(s,myitem);}
            if (k>o) {
                while (isempty(s)&&top(s).cData!='(')
                {
                    tok[0]=pop(s).cData;
                    strcat(postfix,tok);
                    strcat(postfix," ");
                }
                myitem.cData=token[0];
                push(s,myitem);
            }
            }
        }

        else {  if (flag==0) {strcpy(postfix,token); strcat(postfix," "); token=strtok(NULL," "); flag++; continue;}
            strcat(postfix,token);
            strcat(postfix," ");
        }

        token=strtok(NULL," ");

    }
    while(isempty(s)){tok[0]=pop(s).cData; strcat(postfix,tok); strcat(postfix," ");}
}

float evaluatepostfix(char *postfix)
{
    stack *s=intialization();
    item myitem;
    float w,t;
    char op;
    char *token;
    token=malloc(MAX);
    token=strtok(postfix," ");
    while (token)
    {

        if (token[0]=='+' || token[0]=='-' && !atof(token) || token[0]=='*' || token[0]=='/' || token[0]=='^' )
        {
            op=token[0];
            w=pop(s).fData;
            t=pop(s).fData;

            switch (op)
            {
                case '+':
                {
                    myitem.fData=w+t;
                    push(s,myitem);
                    token=strtok(NULL," ");
                    break;
                }
                case '-':
                {
                    myitem.fData=t-w;
                    push (s,myitem);
                    token=strtok(NULL," ");
                    break;
                }
                case '*':
                {
                    myitem.fData=t*w;
                    push(s,myitem);
                    token=strtok(NULL," ");
                    break;
                }
                case '^':
                {
                    myitem.fData=pow(t,w);
                    push(s,myitem);
                    token=strtok(NULL," ");
                    break;
                }
                default :
                {
                    myitem.fData=t/w;
                    push(s,myitem);
                    token=strtok(NULL," ");
                    break;
                }
            }
        }
        else
        {
            myitem.fData=atof(token);
            push(s,myitem);
            token=strtok(NULL," ");
        }

    }
    return top(s).fData;
}
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
int main(int argc, char**argv)
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";
    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        infixtopostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);
        float result = evaluatepostfix(postfixExpr);
        printf("Result: %.2f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}
