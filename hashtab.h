// Hash Table 
#define CAPACITY 50000 // Размер хэш-таблицы

typedef struct ht_item ht_item;
typedef struct hash_table hash_table;
typedef struct linked_list linked_list;

// Структура элемента хэш-таблицы
struct ht_item {
  char* key;
  char* value;
};

struct hash_table {
  ht_item** items; // Массив элементов
  linked_list** overflow_bucket; // Этот список используется для обработки коллизий
  unsigned int size; // Размер таблицы 
  unsigned int count; // Количество не пустых элементов
};


// Это хэш-функция которая будет выполнять хэширование наших данных
unsigned long hash_function(char* str);
// Функция создания элемента таблицы 
ht_item* create_item(char* key, char* value);
// Функция создания хэш-таблицы
hash_table* create_table(int size);
// Функция освобождения выделенной памяти для элементов
void free_item(ht_item* item);
// Функция освобождения выделенной памяти для таблицы
void free_table(hash_table* table);
// Функция вставки элемента в хэш-таблицу
void ht_insert(hash_table* table, char* key, char* value);
//Функция поиска значения по ключу
char* ht_search(hash_table* table, char* key);
// Функция удаления элемента из таблицы
void ht_delete(hash_table* table, char* key);
// Функция обработки колизии
void handle_collisions(hash_table* table, ht_item* item);
// Функция вывода поиска
void print_search(hash_table* table, char* key);
// Функция вывода таблицы 
void print_table(hash_table* table);


// Linked List
struct linked_list {
  ht_item* item;
  linked_list* next;
};

// Функция выделения памяти для списка 
linked_list* allocate_list();
// Функция добавления элемента в список 
linked_list* linked_insert(linked_list* list, ht_item* item);
// Функция удаления списка 
ht_item* linked_remove(linked_list* list);
// Функция освобождения выделенной памяти для списка
void free_linked(linked_list* list);
// Функция выделения памяти для списка в таблице
linked_list* create_overflow_bucket(hash_table* table);
// Функция освобождения памяти для односвязного спика
void free_overflow_bucket(hash_table* table);
