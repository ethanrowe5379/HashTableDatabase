/*ht_item
    consists of two char arrays which store the key and the value
    Key will be used to create the hash value
    Value will be return when searched.*/
typedef struct{
    char* key;
    char* value;
}ht_item;

/*ht
    This structure contains the Hash Table itself
    int size - the size of the ht_item array
    int count - the number of items in ht_item array
    ht_item** items - An array of items which is declaring an pointer to a pointer (an array)
*/
typedef struct{
    int size;
    int count;
    ht_item** items;
}Hash_Table;

