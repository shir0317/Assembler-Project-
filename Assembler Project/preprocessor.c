#include "preprocessor.h"
#include "data_structures/vector.h"
#include "data_structures/trie.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define AS_FILE_EXT ".as"
#define AM_FILE_EXT ".am"
#define MAX_MACRO_LEN 31
#define MAX_LINE_LEN 81
#define SPACE_CHARS "\t\n\f\r\v"
#define SKIP_SPACE_R(s,base) while(*s && isspace(*s) && base !=s) s++

struct macro {
    char m_name[MAX_MACRO_LEN + 1];
    Vector lines;
};
static void *line_ctor(const void *copy){
    const char * line = copy;
    return strcpy(malloc(strlen(line)+1), line);
    
}
static void line_dtor(void * item){
    free(item);
}
static void * macro_ctor(const void *copy){
    const struct Macro *copy1 = copy;
    struct macro new_macro = malloc(sizeof(struct macro ));
    strcpy(new_macro->m_name,copy1->m_name);
    new_macro->lines = new_vector(line_ctor , line_dtor);
    return new_macro;
}
static void macro_dtor(void * item){
    struct macro * macro = item;
    vector_destroy(&macro->lines);
    free((void*)macro);
}
enum preprocessor_line_detection {
    null_line,
    macro_definition,
    end_macro_definition,
    
}
const char *preprocess(const char *file_base_name) {
    char line_buff[MAX_LINE_LEN] = {0};
    size_t file_base_name_len;
    char *as_file_name;
    char *am_file_name;
    FILE *as_file;
    FILE *am_file;
    Vector macro_table;
    Trie macro_table_lookup;

    file_base_name_len = strlen(file_base_name);
    
    as_file_name = strcat(strcpy(malloc(file_base_name_len + strlen(AS_FILE_EXT) + 1), file_base_name), AS_FILE_EXT);
    am_file_name = strcat(strcpy(malloc(file_base_name_len + strlen(AM_FILE_EXT) + 1), file_base_name), AM_FILE_EXT);
    
    as_file = fopen(as_file_name, "r");
    am_file = fopen(am_file_name, "w");
    if(as_file == NULL || am_file == NULL){
        
    }
    while(fgets(line_buff, sizeof(line_buff), as_file)){
        
    }
   
    fclose(as_file);
    fclose(am_file);
    free(as_file_name);
    free(am_file_name);
    
    return am_file_name;
}

