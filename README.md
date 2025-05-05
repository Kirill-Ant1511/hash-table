# Структуры
- `ht_item` - структура элемента хэш-таблицы
- `hash_table` - структура для хэш-таблицы
- `linked_list` - структура для односвязного списка

# Функции Хэш-Таблице
- `hash_function` - хэш-функция для генерации индекса для элемента (**get**: char*; **out**: unsigned long)
- `create_table` - функция для создания хэш-таблицы (**get**: char*, char*; **out**: ht_item*)
- `free_item` - функция для освобождения выделенной паяти для элемента (**get**: ht_item*; **out**: void)
- `free_table` - функция для освобождения выделенной памяти для хэш-таблицы (**get**: hash_table*; **out**: void)
- `ht_insert` - функция для добавления элемента в хэш-таблицу (**get**: hash_table*, char*, char*; **out**: void)
- `ht_search` - функция для поиска элементов в хэш-таблице (**get**: hash_table*, char*; **out**: char*)
- `ht_delete` - функция для удаления элемента с хэш-таблице (**get**: hash_table*, char*; **out**: void)
- `handle_collision` - функция обработки коллизии (**get**: hash_table*, unsigned long, ht_item*; **out**: void)
- `print_search` - функция для вывода результатов поиска в хэш-таблице (**get**: hash_table*, char*; **out**: void)
- `print_table` - функция для вывода всех элементов хэш-таблицы (**get**: hash_table*; **out**: void)

# Функции односвязных списков
- `allocate_list` - функция для выделения памяти для списка (**get**: void; **out**: linked_list)
- `linked_insert` - функция для добавления элемента в список (**get**: linked_list*, ht_item*; **out**: linked_list*)
- `linked_remove` - функция для удаления элемента из списка (**get**: linked_list*; **out**: ht_item*)
- `free_linked` - функция для особождения выделенной памяти для списка (**get**: linked_list*; **out**: void)
- `create_overflow_bucket` - функция для создания односвязного списка в хэш-таблице в случае колизии (**get**: linked_list**; **out**: hash_table*)
- `free_overflow_bucket` - функция для очистки односвязного списка в хэш-таблице (**get**: hash_table*; **out**: void)

