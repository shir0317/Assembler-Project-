#ifndef __TRIE_H_
#define __TRIE_H_

typedef struct trie * Trie;

Trie trie();


const char * trie_insert(Trie trie,const char *string,void * end_of_str_ctx);

void * trie_exists(Trie trie,const char *string);


void trie_delete(Trie trie,const char  *string);


void trie_destroy(Trie * trie);







/*.*/
#endif
