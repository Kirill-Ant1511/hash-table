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

void handle_collisions(hash_table* table, ht_item* item) {
  return;
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
      handle_collisions(table, item);
      return;
    }
  }
}

char* ht_search(hash_table* table, char* key) {
  unsigned long index = hash_function(key);

  ht_item *item = table->items[index];
  if(item != NULL) {
    if(strcmp(item->key, key) == 0) {
      return item->value;
    }
  }
  return NULL;
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
  for(int i = 0; i < table->size; i++) {
    if(table->items[i]) {
      printf("Index: %i, Key: %s, Value: %s\n\n", i, table->items[i]->key, table->items[i]->value);
    }
  }
  printf("Hash Table Info: \n Size: %i\n Count: %i\n", table->size, table->count);
} 

