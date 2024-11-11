#include <stdlib.h>
#include "HashTable.h"

/*Create Hash Table*/
Hash_Table* ht_new(int s){
    Hash_Table* ht = malloc(sizeof(Hash_Table));

    ht->size = s;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item));
    return ht;
}

/*Create Hash Table Item*/
static ht_item* ht_new_item(const char* k, const char* v){
    ht_item* i = malloc(sizeof(ht_item));

    i->key = strdup(k);
    i->value = strdup(v);

    return i;
} 

/*Hash Function*/


/*Add Item to Hash Table*/
