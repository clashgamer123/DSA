#include"dictionary.h"
#include<cmath>

// Define an array of entries of length = size of hash table .
// key -> hashvalue -> entry[hashvalue].value ;
// value -> hashvalue -> entry[hashvalue].key ;

double k = (pow(5,0.5)-1)/2 ;
int p = 31 ;
#define TOMBSTONE (char*)0xabcdabcdabcdabcd

Dictionary :: Dictionary()
{
    N = DICT_SIZE ;
    entry = new Entry[N] ;
}

// hashvalue
// k*s[0] + p(k*s[1] + p(k*s[2] + ...))   
int Dictionary :: hashValue( char key[])
{
    int hash_val = 0;
    int n = strlen(key) ;
    double frac_part = 0 ;
    for (int i = n; i>1 ; i--)
    {
        frac_part += k*key[i-1] ;
        frac_part*=p ;
        frac_part = frac_part - int(frac_part) ;
    }
    frac_part = (frac_part + k*key[0]) ;
    frac_part -= int(frac_part) ;
    hash_val = int((this->N)*frac_part) ;
    return hash_val ;
}

int Dictionary :: findFreeIndex( char key[] )
{
    int i = this->hashValue(key) ;
    int check = 0;

    do
    {
        if(entry[i].key!=nullptr) { i = (i+1)%N ; check++ ; } 
        else { break ; }
    }        
    while ( check!=N ) ;
    if (check == N) { return -1 ;}
    return i ;
}

Entry* Dictionary :: get( char key[] )
{
    int i = hashValue(key) ;
    int check = 0;
    do
    {
        if(entry[i].key == nullptr) { return NULL ;}
        if(entry[i].key == key) { break ;}
        if(entry[i].key!=key) { i = (i+1)%N ;}
        check++ ;
    }
    while(check!=N) ;

    if (check == N) { return NULL ;}
    
    return &entry[i] ;
}

bool Dictionary :: put( Entry e)
{
    int i = findFreeIndex(e.key) ;
    if( i == -1 ) { return false ;}
    entry[i].key = e.key ;
    entry[i].value = e.value ;
    return true ;
}

bool Dictionary :: remove( char key[] )
{
    Entry* check = this->get(key) ;
    if (check == NULL) 
    {
        return false ;
    }
    (*check).key = TOMBSTONE ;
    return true ;
}


