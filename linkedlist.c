// Linked List Assignment

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 20


struct Node
{
    int data;
    struct Node* next;

};  


struct LinkedList
{
    struct Node* head;
    struct Node* current;
    struct Node* tail;
};


void createLinkedList();
struct Node* createNode();

void addNodeParamSet(struct Node**);
void addNode(struct Node **, int);

int countNodes(struct Node*);
struct Node** travelList(struct Node**, int);

void deleteNodeParamSet(struct Node**);
int deleteNode(struct Node**, int);

void enterData(struct Node*);
void modifyListData(struct Node*);

 

int main()
{
    printf("\n******************************************" 
           "\n**\tLINKED LIST GENERATOR\t\t**"
           "\n******************************************\n\n");
    char cmd = 0;
    while(1)
    {
        printf("What do you want to do? \n"
               "Create new linked list(c), Exit program(e): ");
        scanf("%s", &cmd);
        
        while((cmd!='c')&&(cmd!='e'))
        {
            printf("Please enter valid command: ");
            scanf("%s", &cmd);
        }
        
        if(cmd=='c')
            createLinkedList();

        return 0;
    }
}


void createLinkedList()
{
    int num;
    printf("Enter number of nodes: ");
    scanf("%d", &num);
    
    struct Node *head = 0;
    addNode(&head, num);
 
    printf("\nList generated. Head at %p\n", head);
    char cmd = 0;
    while(cmd!='e')
    {
        printf("\nWhat next: add nodes(a), delete nodes(d), "
               "enter data(i), count nodes (c), exit (e): ");
        scanf("%s", &cmd);
        switch(cmd)
        {
            case 'a':
                addNodeParamSet(&head);
                break;
            case 'd':
                deleteNodeParamSet(&head);
                break;
            case 'i':
                modifyListData(head);
                break;
            case 'c': ;
                int count = countNodes(head);
                printf("There are %d nodes in the list.\n", count);
                break;
            case 'e':
                return;
            default:
                printf("Enter valid key.\n");
        }
    }
    
}


struct Node* createNode()
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = 0;
    node->next = 0;
    return node;
}


void addNode(struct Node** currentadd, int num)
{
    struct Node * buf;
    for(int i=num;i;i--)
    {
        buf = *currentadd;
        *currentadd = createNode();
        (*currentadd)->next = buf;
        currentadd = &((*currentadd)->next);
    }

    return;
}


int deleteNode(struct Node** currentadd, int num)
{
    int i=num;
    printf("DCurr at %p\n", *currentadd);
    for(i;(i&&(*currentadd));i--)
    {
        *currentadd = (*currentadd)->next;
    }
    printf("DCurr at %p\n", *currentadd);

    return (num-i);
}


void addNodeParamSet(struct Node** headadd)
{
    char cmd = 0;
    // int num = 0;         //num gets reinitialised to 0 before while loop.
    static int num = 0;     //don't know reason. 
    int nodenum = 0;

    struct Node ** currentadd;

    // Collect User Input for insertion parameters
    
    printf("How many nodes do you want to add: ");
    scanf("%d", &num);
    printf("Where do you want node to be appended from: "
           "front(h), end(t), middle(m), exit(e): ");
    scanf("%s", &cmd);

    while(cmd!='e')
    {
        switch(cmd)
        {
            case 'h':
                nodenum = 0;
                headadd = travelList(headadd, nodenum);
                addNode(headadd, num);

                printf("Added %d nodes at the front of list. "
                       "Head at %p\n", num, *headadd);

                cmd = 'e';
                break;

            case 'm':
                printf("After how many nodes from the front (ex: 4)"
                       "or from the end (ex: -4) should nodes be inserted: ");
                scanf("%d", &nodenum);
                
                int count = countNodes(*headadd);
                
                while(1)
                {
                    if(nodenum==0)
                    {
                        printf("Cannot enter 0. Please enter again: ");
                        scanf("%d", &nodenum);
                    }
                    else if ((nodenum>=count)||(-nodenum>=count))
                    {
                        printf("Length of list is %d. "
                               "Absolute value entered cannot be greater than this.\n"
                               "Please enter again: ", count);
                        scanf("%d", &nodenum);
                    }
                    else
                        break;                    
                }

                if(nodenum<0)
                {
                    nodenum = count-nodenum;
                }

                currentadd = travelList(headadd, nodenum);
                addNode(currentadd, num);

                printf("Added %d nodes in the middle of list. "
                       "Head at %p\n", num, *headadd);

                cmd = 'e';
                break;

            case 't': ;
                nodenum = -1;

                currentadd = travelList(headadd, nodenum);
                addNode(currentadd, num);
                
                printf("Added %d nodes at the end of list. "
                       "Head at %p\n", num, *headadd);
                
                cmd = 'e';
                break;

            case 'e':
                break;

            default:
                printf("Enter Valid Command: ");
                scanf("%s", &cmd);
        }


    }

    return;
}


void deleteNodeParamSet(struct Node** headadd)
{
    char cmd = 0;
    // int num = 0;
    static int num = 0;
    int nodenum = 0;
    int count = countNodes(*headadd);
    
    struct Node ** currentadd;

    // Collect User Input for deletion parameters
    
    while(1)
    {
        printf("How many nodes do you want to delete: ");
        scanf("%d", &num);
        if (num>=count)
        {
            printf("Length of list is %d. "
                    "This will delete entire list.\n"
                    "Do you want to proceed (y/n): ", count);
            char tmp = 0;
            scanf("%s", &tmp);
            if(tmp=='y')
            {
                num = deleteNode(headadd, num);

                printf("Deleted complete list. "
                       "Head at %p\n", *headadd);

                cmd = 'e';
                break;
            }
        }
        break;
    }   
    
    while(cmd!='e')
    {
        printf("Where do you want node to be deleted from: "
               "front(h), end(t), middle(m), exit(e): ");
        scanf("%s", &cmd);

        switch(cmd)
        {
            case 'h':
                nodenum = 0;
                headadd = travelList(headadd, nodenum);
                num = deleteNode(headadd, num);

                printf("Deleted %d node(s) from the front of list. "
                       "Head at %p\n", num, *headadd);

                cmd = 'e';
                break;

            case 'm':
                printf("After how many nodes from the front (ex: 4)"
                       "or from the end (ex: -4) should nodes be deleted: ");
                scanf("%d", &nodenum);
                while(1)
                {
                    if(nodenum==0)
                    {
                        // printf("Cannot enter 0. Please enter again: ");
                        // scanf("%d", &nodenum);
                        printf("Deleting from the front of list instead.");
                        break;
                    }
                    else if ((nodenum>=count)||(-nodenum>=count))
                    {
                        printf("Length of list is %d. "
                               "Absolute value entered cannot be greater than this.\n"
                               "Please enter again: ", count);
                        scanf("%d", &nodenum);
                    }
                    else
                        break;                    
                }

                if(nodenum<0)
                {
                    nodenum = count-nodenum;
                }
                
                currentadd = travelList(headadd, nodenum);
                num = deleteNode(currentadd, num);

                printf("Deleted %d node(s) in the middle of list. "
                       "Head at %p\n", num, *headadd);

                cmd = 'e';
                break;

            case 't': ;
                nodenum = count-num;

                currentadd = travelList(headadd, nodenum);
                num = deleteNode(currentadd, num);
                
                printf("Deleted %d nodes at the end of list. "
                       "Head at %p\n", num, *headadd);
                
                cmd = 'e';
                break;

            case 'e':
                break;

            default:
                printf("Enter Valid Command.\n");
        }
    }

    return;
}


void modifyListData(struct Node* head)
{

    return;
}


int countNodes(struct Node* head)
{
    int count = 1;
    struct Node * walk;
    walk = head;
    
    while(walk->next)
    {
        count++;
        walk = walk->next;
    }

    return count;
}


struct Node** travelList(struct Node** headadd, int nodes)
{
    struct Node **walk;
    walk = headadd;
    int count = nodes;
    struct Node* check = (*walk)->next;
    while((count--)&&check)
    {
        walk = &((*walk)->next);
        check = check->next;
    }
    return walk;
    
}


