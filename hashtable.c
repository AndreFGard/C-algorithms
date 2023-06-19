#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLENGTH 35
#define MAXKEYS 1000

struct node{
    struct node *next;
    char word[MAXLENGTH + 1];
};


unsigned int hashF(const char *word)
{

    char wordlower[MAXLENGTH];
    int i = 0;
    while (word[i] != '\0')
    {
        wordlower[i] = tolower(word[i]);
        i++;
    }
    //end string
    wordlower[i] = word[i]; 
    // TODO: Improve this hash function
    char letter;
    letter = 'a';
    letter = wordlower[0];
    unsigned int sum, w;
    w = sum = i = 0;
    while (letter != '\0')
    {
        w += letter * (i * i + 3);
        sum += letter * 3  * (46 - i) * w ;
        i++;
        letter = wordlower[i];
    }
    return sum % (MAXKEYS - 1);
}


int isIn(char *word, struct node *hashTable[]){
    // isIn returns the hashcode of the word if it's in the table and 0 otherwise
    int hashCode = hashF(word);
    if ((hashTable[hashCode]) == NULL)
    {
        return 0;
    }
    // if the slot is populated, search for the word there
    struct node *cursor = hashTable[hashCode];
    while (cursor->next != NULL)
    {
        if (!strcasecmp(cursor->word, word)){
            puts("found");
        }
        // append word to the output buffer
        printf("%s, ", cursor->word);
    }
    // print output buffer
    puts("");
    free(cursor);
}


int addWord(char *word, struct node *hashTable[]){
    struct node *cursor;
    int hashCode = hashF(word), nodesFollowedCount = 0; 
    // if the slot is populated already, be it by a duplicate or not, move till the last node of the slot
    cursor = hashTable[hashCode];
    if (hashTable[hashCode] != NULL)
    {
        // go to the last node in the slot. If there's only one, we'll do nothing.
        nodesFollowedCount++;
        while (cursor->next != NULL)
        {
            cursor = cursor->next;
            nodesFollowedCount++;
        }

        cursor->next = malloc(sizeof(struct node));
        // move to the just allocated new node
        cursor = cursor->next;
    }
    else {
        // allocate slot if it was not already and update cursor for readability 
        cursor = hashTable[hashCode] = malloc(sizeof(struct node));
    }

    // copy given word to the current node's word attribute
    strcpy(cursor->word, word);
    cursor->next = NULL;
    //Friendly printf("in slot %d, followed %d nodes and stored %s\n", hashCode, nodesFollowedCount, cursor->word);    
    //CSV printf("%d,%d\n", hashCode, nodesFollowedCount);   
}


int itemsInSlot(int hashCode, struct node *hashTable[]){
    if (hashTable[hashCode] == NULL){
        return 0;
    }
    
    // there is at least one node
    int itemCount = 1;
    struct node *cursor = hashTable[hashCode];
    while (cursor->next != NULL){
        cursor = cursor->next;
        // printf("%d, ", itemCount);
        itemCount++;
    }

    // printf("%d, ", itemCount);
    // reached last node
    return itemCount;

}

int showItemsInSlot(int hashCode, struct node *hashTable[]){
    if (hashTable[hashCode] == NULL){
        return 1;
    }

    struct node *cursor = hashTable[hashCode];
    printf("%s, ", cursor->word);
    while (cursor->next != NULL)
    {
        cursor = cursor->next;
        // append word to the output buffer
        printf("%s, ", cursor->word);
    }
    
    // print output buffer
    puts(" ");
    return 0;
}


int loadFileIntoHashTable(FILE *file, struct node *hashTable[]){
    char word[MAXLENGTH];
    while(fscanf(file, "%s", &word) == 1)           /* from the input stream, read one word untill a whitespace is reached (conversion  */
    {                                               /* specifier s) and store it in the address of word while the n of matched elements */
        addWord(word, hashTable);                   /* This is UNSAFE, we should add buffer overflow protection                         */
    }

    return 0;

}



int showItemsInSlots(int slots[], int slotsSize, struct node *hashTable[]){
    // print items in many slots at once
    for (int i = 0; i < slotsSize - 1; i++)
    {
        showItemsInSlot(slots[i], hashTable);
    }

}

int main(int argc, char *argv[]){

    //Dprintf("hashcode %d", hashF("aveia"));
    char *filename = "words.txt";
    if (argc != 2)
    {
        printf("Usage: ./main textfile.txt\nWhere text.file is a file of whitespace separated words of max length %d\n", MAXLENGTH);
    }
    else
    {
        char *filename = argv[1];
    }


    FILE *file = fopen(filename, "r");
    if (file == NULL){
        puts("Couldn't open file\n");
        return 1;
    }
        struct node *hashTable[MAXKEYS] = {NULL};
        puts("slot,followedNodes");
        loadFileIntoHashTable(file, hashTable);
    fclose(file);

    int overusedSlots[5] = {0, 423, 45, 957};

    //showItemsInSlots(overusedSlots, 5, hashTable);
    showItemsInSlot(0, hashTable);
    printf("%d, ", itemsInSlot(0, hashTable));
   



    
}