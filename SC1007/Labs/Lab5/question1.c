#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode{
    int key;
    struct _listnode *next;
} ListNode;

// Using Linked List as Chain for Hash Table
typedef struct _linkedlist{
   int size;
   ListNode *head;
} HashTableNode;

// Hash Table
typedef struct _hashTable{
   int hSize; //size of hash table
   int nSize; //number of inserted keys
   HashTableNode *Table;
} HashTable;

// Hash Function
int Hash(int,int);

// Return Value when given key
ListNode* HashSearch(HashTable, int);
// Insert into Hash Table the Key
int HashInsert(HashTable *, int);

//In Practice, we will not do it
void HashPrint(HashTable);

int main()
{
    int opt;
    int size;

    int i;
    int key;

    //Create a HashTable
    HashTable Q3Hash;
    Q3Hash.hSize = 0; 
    Q3Hash.nSize = 0; 
    Q3Hash.Table = NULL;

    printf("============= Hash Table ============\n");
    printf("|1. Create a hash table             |\n");
    printf("|2. Insert a key to the hash table  |\n");
    printf("|3. Search a key in the hash table  |\n");
    printf("|4. Print the hash table            |\n");
    printf("|5. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=4){
        switch(opt){
        case 1:
            printf("Enter the size of hash table:\n");
            scanf("%d",&Q3Hash.hSize);

            Q3Hash.nSize = 0;

            Q3Hash.Table = (HashTableNode *) malloc(sizeof(HashTableNode)*(Q3Hash.hSize));

            for(i=0;i<Q3Hash.hSize;i++){
               Q3Hash.Table[i].head = NULL;
               Q3Hash.Table[i].size = 0;
            }
            printf("HashTable is created.\n");
            break;
        case 2: //Insertion
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);

            if(HashInsert(&Q3Hash,key))
                printf("%d is inserted.\n",key);
            else
                printf("%d is a duplicate. No key is inserted.\n",key);
            break;
        case 3: //Search
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            ListNode* node = HashSearch(Q3Hash, key);

            if(node!=NULL)
                printf("%d is found.\n",key);
            else
                printf("%d is not found.\n",key);
            break;
        case 4:
            HashPrint(Q3Hash);
            break;
        }

    printf("Enter selection: ");
    scanf("%d",&opt);
    }

    for(i=0;i<Q3Hash.hSize;i++)
    {
        while(Q3Hash.Table[i].head)
        {
            ListNode *temp;
            temp = Q3Hash.Table[i].head;
            Q3Hash.Table[i].head = Q3Hash.Table[i].head->next;
            free(temp);
        }
    }
    free(Q3Hash.Table);

    return 0;

}

int Hash(int key,int hSize)
{
    return key%hSize;
}

ListNode* HashSearch(HashTable Q3Hash, int key)
{
    // Determine the Hash Value
    int hash_value = Hash(key, Q3Hash.hSize);
    
    // Go to the correct index
    HashTableNode *HashIndexPtr = Q3Hash.Table;
    for (int i = 0; i < hash_value; i += 1)
    {
        HashIndexPtr += 1;
    }

    // Check Head
    ListNode* cursor = HashIndexPtr->head;
    while (cursor != NULL)
    {
        // Check Head First
        if (cursor->key == key)
        {
            return cursor;
        }
        cursor = cursor->next;
    }
    // Key not in Hash Table, Return NULL
    return cursor;
}

int HashInsert(HashTable* Q3HashPtr, int key)
{
    int size_HT = Q3HashPtr->hSize;
    int size_IK = Q3HashPtr->nSize;
    HashTableNode *target_index = Q3HashPtr->Table;

    // Determine the Hash Value
    int hash_value = Hash(key, size_HT);

    // Move to the Correct Hash Index
    while (hash_value != 0)
    {
        target_index = target_index + 1;
        hash_value -= 1;
    }

    // Insert the Key
    HashTableNode *insertPtr = target_index;
    ListNode *cursor = NULL, *next_node = NULL;
    ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
    newNode->key = key;
    newNode->next = NULL;
    if (insertPtr->head == NULL)
    {
        insertPtr->head = newNode;
    }
    else
    {
        cursor = insertPtr->head;
        next_node = cursor;
        if (cursor->key == key)
        {
            // Key is existing
            return 0;
        }
        while(cursor->next != NULL)
        {
            cursor = cursor->next;
            if (cursor->key == key)
            {
                // Key is existing
                return 0;
            }
        }
        newNode->next = next_node;
        insertPtr->head = newNode;
    }
    // Key is inserted
    return 1;

}

void HashPrint(HashTable Q3Hash)
{
    int i;
    ListNode *temp;
    for(i=0;i<Q3Hash.hSize;i++)
    {
        temp =Q3Hash.Table[i].head;
        printf("%d:  ",i);
        while(temp !=NULL)
        {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}
