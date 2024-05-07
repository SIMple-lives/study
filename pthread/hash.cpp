#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define HASHNUM 13
#define HASH(key) key % HASHNUM

typedef struct HashNode {
  int value;
  int key;
  struct HashNode* next;
}Hnode,*Hlist;

struct HashTable {
  pthread_mutex_t mutex;
  Hlist head;
};

typedef struct{
  struct HashTable table[HASHNUM];
}hash_lock_t;

void hashInit(hash_lock_t* bucket);
int getValue(hash_lock_t* bucket, int key);
void insert(hash_lock_t* bucket, int key,int value);
int setKey(hash_lock_t* bucket,int key, int new_key);

void hashInit(hash_lock_t* bucket) {
  //perror("This function is not implemented");
  for(int i=0;i<HASHNUM;i++)
  {
    pthread_mutex_init(&bucket->table[i].mutex, NULL);
    bucket->table[i].head = NULL;
  }
}

int getValue(hash_lock_t* bucket, int key) {
  //perror("This function is not implemented");
  int hashIndex = HASH(key) ;
  pthread_mutex_lock(&bucket->table[hashIndex].mutex);
  Hlist node = bucket->table[hashIndex].head;
  while(node != NULL)
  {
    if(node->key == key)
    {
      pthread_mutex_unlock(&bucket->table[hashIndex].mutex);
      return node->value;
    }
    node = node->next;
  }
  pthread_mutex_unlock(&bucket->table[hashIndex].mutex);
  return -1;
}

void insert(hash_lock_t* bucket, int key, int value) {
    int hashIndex = HASH(key);
    pthread_mutex_lock(&bucket->table[hashIndex].mutex);
    Hlist current = bucket->table[hashIndex].head;
    Hlist previous = NULL;
    while (current != NULL) 
    {
        if (current->key == key) 
        {
            current->value = value;
            pthread_mutex_unlock(&bucket->table[hashIndex].mutex);
            return;
        }
        previous = current;
        current = current->next;
    }
    Hlist newNode = (Hlist)malloc(sizeof(Hnode));
    if (newNode == NULL) 
    {
        perror("Memory allocation error");
        pthread_mutex_unlock(&bucket->table[hashIndex].mutex);
        return;
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    if (previous == NULL) 
    {
        bucket->table[hashIndex].head = newNode;
    } 
    else 
    {
        previous->next = newNode;
    }
    pthread_mutex_unlock(&bucket->table[hashIndex].mutex);
}


int setKey(hash_lock_t* bucket, int key, int new_key) {
    int hashIndex = HASH(key);
    pthread_mutex_lock(&bucket->table[hashIndex].mutex);
    Hlist current = bucket->table[hashIndex].head;
    Hlist prev = NULL;
    int value = -1; // Default value if key is not found
    while (current != NULL) {
        if (current->key == key) {
            // Retrieve the value associated with the original key
            value = current->value;

            // Update the key
            current->key = new_key;

            // Remove the node with the original key
            if (prev == NULL) {
                bucket->table[hashIndex].head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current); // Free the memory of the old node
            pthread_mutex_unlock(&bucket->table[hashIndex].mutex);
            break;
        }
        prev = current;
        current = current->next;
    }

    // If key is not found, return -1
    pthread_mutex_unlock(&bucket->table[hashIndex].mutex);

    // Insert a new node with the updated key and retrieved value
    if (value != -1) {
        insert(bucket, new_key, value);
        return 0;
    }
    return -1;
}

