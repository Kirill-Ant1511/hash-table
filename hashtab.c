#include "hashtab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


unsigned long hash_function(char* str) {
  int counter = 0;
  for(int i = 0; str[i]; i++)
    counter += str[i];

  return counter % CAPACITY;
}

linked_list* allocate_list() {
  linked_list* list = (linked_list*) malloc(sizeof(linked_list*));
  return list;
}

linked_list* linked_insert(linked_list* list, ht_item* item) {
  if(!list) {
    linked_list* head = allocate_list();
    head->item = item;
    head->next = NULL;
    list = head;
    return list;
  }
  else if(!list->next) {
    linked_list* node = allocate_list();
    node->item = item;
    node->next = NULL;
    list->next = node;
    return list;
  }

  linked_list* temp = list;
  while(temp->next)
    temp = temp->next;
  

  linked_list* node = allocate_list();
  node->item = item;
  node->next = NULL;
  temp->next = node;
  return list;
}

ht_item* linked_remove(linked_list* list) {
  if(!list) {
    return NULL;
  } 
  else if(!list->next) {
    return NULL;
  }
  linked_list* node = list->next;
  linked_list* temp = list;
  list = node;
  ht_item* it = NULL;
  memcpy(temp->next, it, sizeof(ht_item));
  free(temp->item->key);
  free(temp->item->value);
  free(temp->item);
  free(temp);
  return it;
}

void free_linked(linked_list* list) {
  linked_list* temp = list;
  while(list) {
    temp = list;
    list = list->next;
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
  }
}

linked_list** create_overflow_bucket(hash_table* table) {
  linked_list** buckets = (linked_list**) calloc(table->size, sizeof(linked_list*));
  for(int i = 0; i < table->size; i++)
    buckets[i] = NULL;
  return buckets;
}

void free_overflow_bucket(hash_table* table) {
  linked_list** buckets = table->overflow_bucket;
  for(int i = 0; i < table->size; i++)
    free_linked(buckets[i]);
  free(buckets);
}

void handle_collisions(hash_table* table, unsigned long index, ht_item* item) {
  linked_list* head = table->overflow_bucket[index];
  if(head == NULL) {
    head = allocate_list();
    head->item = item;
    table->overflow_bucket[index] = head;
    return;
  }
  else {
    table->overflow_bucket[index] = linked_insert(head, item);
    return;
  }
}

ht_item* create_item(char* key, char* value) {
  ht_item *item = (ht_item*) malloc(sizeof(ht_item));
  item->key = (char*) malloc(strlen(key) + 1);
  item->value = (char*) malloc(strlen(value) + 1);
  
  strcpy(item->key, key);
  strcpy(item->value, value);
  
  return item;
}

hash_table* create_table(int size) {

  hash_table* table = (hash_table*) malloc(sizeof(hash_table));
  table->size = size;
  table->count = 0;
  table->items = (ht_item**) calloc(table->size, sizeof(ht_item));

  for(int i = 0; i < table->size; i++)
    table->items[i] = NULL;
  table->overflow_bucket = create_overflow_bucket(table);
  
  return table;
}

void free_item(ht_item* item) {
  free(item->key);
  free(item->value);
  free(item);
}

void free_table(hash_table* table) {
  for(int i = 0; i < table->size; i++) {
    ht_item* item = table->items[i];
    if(item != NULL) {
      free_item(item);
    }
  }
  free_overflow_bucket(table);
  free(table->items);
  free(table);
}

void ht_insert(hash_table* table, char* key, char* value) {
  unsigned long index = hash_function(key);
  ht_item* item = create_item(key, value);

  ht_item* current_item = table->items[index];
  if(current_item == NULL) {
    if(table->count > table->size) {
      printf("[ERROR] Hash table is full");
      free_item(item);
      return;
    }
    table->items[index] = item;
    table->count++;
    return;
  } else {
    if(strcmp(current_item->key, key) == 0){
      strcpy(table->items[index]->value, value);
      return;
    } else {
      handle_collisions(table, index, item);
      return;
    }
  }
}

char* ht_search(hash_table* table, char* key) {
  unsigned long index = hash_function(key);

  ht_item *item = table->items[index];
  linked_list* head = table->overflow_bucket[index];

  while(item != NULL) {
    if(strcmp(item->key, key) == 0) 
      return item->value;
    if(head == NULL) 
      return NULL;
    item = head->item;
    head = head->next;
    
  }
  return NULL;
}

void ht_delete(hash_table* table, char* key) {
  unsigned long index = hash_function(key);
  ht_item* item = table->items[index];
  linked_list* head = table->overflow_bucket[index];

  if(item == NULL) {
    return;
  }
  else {
    // Случай когда нету колизии
    if(head == NULL && strcmp(item->key, key) == 0) {
      table->items[index] = NULL;
      free_item(item);
      table->count--;
      return;
    } 
    else if(head != NULL) {
      if(strcmp(item->key, key) == 0) {
        free_item(item);
        linked_list* node = head;
        head = head->next;
        node->next = NULL;
        table->items[index] = create_item(node->item->key, node->item->value);
        free_linked(node);
        table->overflow_bucket[index] = head;
        return;
      }
    

      linked_list* curr = head;
      linked_list* prev = NULL;

      while(curr) {
        if(strcmp(curr->item->key, key) == 0) {
          if(prev == NULL) {
            free_linked(head);
            table->overflow_bucket[index] = NULL;
            return;
          } else {
            prev->next = curr->next;
            curr->next = NULL;
            free_linked(curr);
            table->overflow_bucket[index] = head;
            return;
          }
        }
        prev = curr;
        curr = curr->next;
      }
    }
  }
}

void print_search(hash_table* ht, char* key) {
  char* val;
  if((val = ht_search(ht, key)) == NULL) {
    printf("Key: %s does not exist\n", key);
    return;
  } else {
    printf("Key: %s, Value: %s\n", key, val);
  }
}

void print_table(hash_table* table) {
  printf("\n\n------------Hash Table---------------\n");
  for(int i = 0; i < table->size; i++) {
    if(table->items[i]) {
      printf("Index: %d, Key: %s, Value: %s\n", i, table->items[i]->key, table->items[i]->value);
      if(table->overflow_bucket[i]) {
        printf("\t>-Overflow Bucket Index: %d->\t", i);
        linked_list* head = table->overflow_bucket[i];
        while(head) {
          printf("Key: %s, Value: %s\n", head->item->key, head->item->value);
          head = head->next;
        }
        printf("---------------------------\n");
      }
    }
  }
  printf("Hash Table Info: \n Size: %i\n Count: %i\n", table->size, table->count);
  printf("---------------------------\n\n\n");
}
