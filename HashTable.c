#include <stdlib.h>
#include "HashTable.h"

#define PRIME_1 97081
#define PRIME_2 78893

static ht_item DELETED_HT_ITEM = {NULL, NULL};

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


/*Hash Function
    char* s - the string of text to be converted into a hash
    int p - a prime number thats greater than the ASCII alphabet size (128)
    int m - size of hash table*/
static int ht_hash(const char* s, const int p, const int m){
    long hash = 0;
    const int len_s = strlen(s);  
    for(int i = 0;i<len_s;i++){
        hash += (long)pow(p, len_s-(i+1) * s[i]);
        hash = hash % m;
    }  
    return (int)hash;
}

/*Double Hash For Collisions*/
static int ht_get_hash(const char* s, const int num_buckets, const int attempts){
    const int hash_a = ht_hash(s, PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, PRIME_2, num_buckets);
    return (hash_a + (attempts * (hash_b + 1))) % num_buckets;
}

/*Add Item to Hash Table*/
void ht_insert(Hash_Table* ht, const char* key, const char* value){
    ht_item* item = ht_new_item(key, value);
    
    int index = ht_get_hash(item->key, ht->size, 0);
    ht_item* cur_item = ht->items[index];
    
    int i = 1;
    while(cur_item != NULL){
        if(cur_item != &DELETED_HT_ITEM){
            if(strcmp(cur_item->key, key) == 0){
                index = ht_get_hash(item->key, ht->size, i);
                cur_item = ht->items[index];
                i++;  
            }
        }
    }
    ht->items[index] = item;
    ht->count++;
}

/*Search the Hash Table

*/
char* ht_search(Hash_Table* ht, const char* key){
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while(item != NULL){
        if(strcmp(item->key, key) == 0){
            return item->value;
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    return NULL;
}

/*Delete item from Hash Table*/
void delete_item(Hash_Table* ht, char const* key){
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while(item != NULL){
        if(item != &DELETED_HT_ITEM){
            if(strcmp(item->key, key) == 0){
                ht_del_item(item);
                ht->items[index] = &DELETED_HT_ITEM;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    ht->count--;
}
