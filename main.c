#include<stdio.h>

#include"hashtab.h"

int main() {
  hash_table* ht = create_table(5);
  ht_insert(ht, "1", "First value");
  ht_insert(ht, "2", "Second value");
  ht_insert(ht, "3", "Third value");
  print_search(ht, "1");
  print_search(ht, "2");
  print_search(ht, "5");
  print_table(ht);
  free_table(ht);
  return 0;
}
