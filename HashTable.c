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

/* Delete ht_item*/
void del_ht_item(ht_item* i){
    free(i->key);
    free(i->value);
    free(i);
}

/* Delete Hash Table*/
void del_ht(Hash_Table* ht){
    for(int i = 0; i<ht->size; i++){
        ht_item* item = ht->items[i];
        if(item != NULL){
            del_ht_item(item);
        }
    }
    free(ht->items);
    free(ht);
}


/*Hash Function*/


/*Add Item to Hash Table*/
