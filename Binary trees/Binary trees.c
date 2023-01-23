#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char word[50];
    struct  Node* left;
    struct Node*right;
} Node;
Node* newNode(char *v);
Node* insert(Node* root,char *word);
Node* searh(Node* root, char *word, Node **parent);
Node* successor(Node** parent, Node *root);
Node* predecessor(Node** parent, Node *root);
void searchSentence(Node* root);
int max(int x,int y );
int height(Node* root);
int count(Node* root);
void screen(Node* root);


void load()
{
    Node *data;
    Node *root=NULL;
    data = malloc(100000000);
    char loadArray[50];
    FILE *f=fopen("EN-US-Dictionary.txt","r+");
    int i=0;
    while(!feof(f))
    {
        fscanf(f,"%s",loadArray);
        /*fgets(loadArray,50,f);
        loadArray[strlen(loadArray)-1]='\0';*/
        strcpy(data[i].word,loadArray);
        insert(root, data[i].word);
        root=data[0].word;
        i++;
    }
    screen(root);
    fclose(f);
}
Node* newNode(char *word)
{
    Node* n=malloc(sizeof(Node));
    strcpy(n->word,word);
    n->left=NULL;
    n->right=NULL;
    return n;
}
Node* insert(Node* root,char *word)
{
    if(root==NULL)
        return newNode(word);
    else if(strcasecmp(word, root->word) < 0)
        root->left= insert(root->left,word);
    else
        root->right=insert(root->right,word);
    return root;
}
Node* search(Node* root, char *word, Node **parent)
{
    if(root==NULL)
        return NULL;
    Node *SRword = root;
    while (SRword)
    {
        if (strcasecmp(SRword->word, word) == 0)
            return SRword;
        else if (strcasecmp(word, SRword->word) < 0)
        {
            *parent = SRword;
            SRword = SRword->left;
        }
        else if (strcasecmp(word, SRword->word) > 0)
        {
            *parent = SRword;
            SRword = SRword->right;
        }
    }

    return SRword;

}

void searchSentence(Node *root)
{
    char phrase[500];
    puts("Enter the sentence");
    fgets(phrase, 500, stdin);
    phrase[strlen(phrase)-1] = '\0';
    Node *temp;
    Node *parent;
    char *token = strtok(phrase, " ");
    while (token != NULL)
    {
        temp = search(root, token, &parent);
        if (temp)
            printf("%s - Correct\n", token);
        else
        {
            printf("%s - InCorrect - Suggestion : %s", token, (*parent).word);
            if (successor(&parent, root))
                printf("\t%s", successor(&parent, root));
            if (predecessor(&parent, root))
                printf("\t%s\n", predecessor(&parent, root));
        }
        token = strtok(NULL, " ");
    }

}
Node* successor(Node** parent, Node *root)
{
    Node* successorSug;
    while(root)
    {
        if(strcasecmp((*parent)->word,root->word)<0)
        {
            successorSug = root;
            root=root->left;
        }
        else
            root=root->right;
    }
    return successorSug;
}
Node* predecessor(Node** parent, Node *root)
{
    Node* predecessorSug;
    while(root)
    {
        if(strcasecmp((*parent)->word,root->word)>0)
        {
            predecessorSug = root;
            root=root->right;
        }
        else
            root=root->left;
    }
    return predecessorSug;
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
void screen(Node* root)
{
    int counter = count(root);
    int high = height(root);
    printf("Dictionary Loaded Successfully....!\n");
    printf(".................\n");
    printf("Size = %d\n",counter);
    printf(".................\n");
    printf("Height = %d\n",high);
    printf(".................\n");
    searchSentence(root);

}
int main()
{
    load();
    return 0;
}
