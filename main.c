#include<stdio.h>

#include"hashtab.h"

int main() {
  hash_table* ht = create_table(CAPACITY);
  ht_insert(ht, "1", "First value");
  ht_insert(ht, "2", "Second value");
  ht_insert(ht, "3", "Third value");
  ht_insert(ht, "Hel", "Hellllls");
  ht_insert(ht, "Cau", "Caussss");
  print_search(ht, "Cau");
  print_search(ht, "2");
  print_search(ht, "Hel");
  print_table(ht);
  ht_delete(ht, "2");
  print_search(ht, "2");
  print_table(ht);
  free_table(ht);
  return 0;
}
