#include "assembler.h"
#include "lexer.h"
#include <stdio.h>
#include "data_structures/vector.h"
#include "data_structures/trie.h"
#include <string.h>

#define MAX_LINE_LEN 81

struct symbol {
    enum{
        sym_extern,
        sym_entry, /*it is declared as entry , but must be defined later in the file.*/
        sym_code,
        sym_data,
        sym_entry_code,
        sym_entry_data
    }sym_type;
    int address;
    char *sym_name;
};
            
struct object_file{
    Vector code_section;
    Vector data_section;
    Vector symbol_table;
    Trie symbol_table_lookup;
};


static int assembler_compiler(FILE *am_file, struct object_file *obj){
    char line_buffer[MAX_LINE_LEN] = {0};
    ast ast;
    struct symbol local_sym = {0};
    while(fgets(line_buffer,sizeof(line_buffer),am_file)){
        ast = lexer_get_ast(line_buffer);
        switch (ast.ast_opt){
                if (ast.ast_opt <= ast_dir && ast.label_name[0] != '\0'){
                    strcpy (
                }
                                                                        
            case ast_syntax_error:
                break;
            case ast_comment: case ast_null:
                break;
            case ast_inst:
                break;
            case ast_dir:
                break;
                
                
                
        }
    }
    
    
}
