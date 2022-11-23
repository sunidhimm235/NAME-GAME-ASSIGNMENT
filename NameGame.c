// include libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Using the trie data structure to implement ths assignment
typedef struct TrieNode TrieNode;

// TrieNode struct
struct TrieNode {
    TrieNode * children[26]; // array of pointers to TrieNodes
    int subtreeSum; // sum of all the mangos eaten by the orangutans with a particular name prefix
    int nodeTotal; // number of mangos eaten by the orangutan with the name represented by the node
};

// This function creates a new TrieNode
TrieNode * createTrieNode() {
    TrieNode * newNode = (TrieNode *) malloc(sizeof(TrieNode));
    newNode->subtreeSum = 0;
    newNode->nodeTotal = 0;

    // initialize all the children to NULL
    for (int i = 0; i < 26; i++) {
        newNode->children[i] = NULL;
    }

    // return the new TrieNode
    return newNode;
}

// This function inserts a new node into the trie
void insert(TrieNode * DataOfOrangutans, char * name, int num) {
    TrieNode * temp_trie = DataOfOrangutans;

    // iterate through the name
    for (int i = 0; i < strlen(name); i++) {
        int index = tolower(name[i]) - 'a';

        // if the child at the index is NULL, create a new TrieNode
        if (temp_trie->children[index] == NULL) {
            temp_trie->children[index] = createTrieNode();
        }

        temp_trie = temp_trie->children[index];
        // update the subtreeSum of the current TrieNode
        temp_trie->subtreeSum += num;
    }

    // update the nodeTotal
    temp_trie->nodeTotal = num;
}

// This function changes the name presented in the trie with a new name in the trie and update the number of mangos eaten
void change(TrieNode * DataOfOrangutans, char * oldName, char * newName) {
    
    // find the num of mangoes eaten by the old name
    TrieNode * temp_trie = DataOfOrangutans;
    int num = 0;
    for (int i = 0; i < strlen(oldName); i++) {
        int index = tolower(oldName[i]) - 'a';

        // if the child at the index is NULL, return
        if (temp_trie->children[index] == NULL) {
            return;
        }

        temp_trie = temp_trie->children[index];
        num = temp_trie->nodeTotal;
    }
    
    // subtract the num of mangoes eaten by the old name from the subtreeSum of the old name
    temp_trie->subtreeSum -= num;
    temp_trie->nodeTotal = 0;
    temp_trie = DataOfOrangutans;

    // subtract the num of mangoes eaten by the old name from the subtreeSum of the trie
    for (int i = 0; i < strlen(oldName)-1; i++) {
        int index = tolower(oldName[i]) - 'a';
        temp_trie = temp_trie->children[index];
        temp_trie->subtreeSum -= num;
    }

    // add the num of mangoes eaten by the old name to the subtreeSum of the new name
    temp_trie = DataOfOrangutans;
    for (int i = 0; i < strlen(newName); i++) {
        int index = tolower(newName[i]) - 'a';

        // if the child at the index is NULL, create a new TrieNode
        if (temp_trie->children[index] == NULL) {
            temp_trie->children[index] = createTrieNode();
        }


        temp_trie = temp_trie->children[index];

        // update the subtreeSum of the current TrieNode
        temp_trie->subtreeSum += num;
    }

    // update the nodeTotal
    temp_trie->nodeTotal = num;
}

// This function returns the number of mangos eaten by the orangutans with a particular name prefix
void print(TrieNode * DataOfOrangutans, char * word_prefix) {
    TrieNode * temp_trie = DataOfOrangutans;

    // iterate through the word_prefix
    for (int i = 0; i < strlen(word_prefix); i++) {
        int index = tolower(word_prefix[i]) - 'a';
        if (temp_trie->children[index] == NULL) {
            printf("0");
            return;
        }
        temp_trie = temp_trie->children[index];
    }

    // print the subtreeSum
    printf("%d", temp_trie->subtreeSum);
}


int main() {

    // take input for the number of orangutans and the number of events
    int numOrangutans, numEvents;
    scanf("%d %d", &numOrangutans, &numEvents);

    // create the trie to store the data of the orangutans
    TrieNode * DataOfOrangutans = createTrieNode();

    // take input until the number of events is reached
    for (int i = 0; i < numEvents; i++) {

        // take input for the event
        int event = 0;
        scanf("%d", &event);

        // if the event is 1, take input for the name and the number of mangos eaten
        if (event == 1) {
            char name[21];
            int num;
            scanf("%s %d", name, &num);
            // insert the name and the number of mangos eaten into the trie
            insert(DataOfOrangutans, name, num);
        }
        else if (event == 2) {// if the event is 2, take input for the old name and the new name and change the name
            char oldName[21];
            char newName[21];
            int num;
            scanf("%s %s", oldName, newName);
            // change the name in the trie
            change(DataOfOrangutans, oldName, newName);
        }
        else if (event == 3) { // if the event is 3, take input for the prefix and print the number of mangos eaten by the orangutans with a particular name prefix
            char prefix[21];
            scanf("%s", prefix);
            // print the number of mangos eaten by the orangutans with a particular name prefix
            print(DataOfOrangutans, prefix);
            printf("\n");
        }
    }

    // free the memory allocated for the trie
    free(DataOfOrangutans);

    return 0;
}
