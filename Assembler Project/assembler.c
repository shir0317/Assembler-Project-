#include "assembler.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include "data_structures/vector.h"
#include "data_structures/trie.h"
#include <string.h>

#define MAX_LINE_LEN 81
#define BASE_ADDR 100

enum sym_type {
    sym_extern,
    sym_entry,
    sym_code,
    sym_data,
    sym_entry_code,
    sym_entry_data
};

struct symbol {
    enum sym_type sym_type;
    unsigned int address;
    char sym_name[MAX_LABEL_LEN + 1];
};

struct missing_symbol {
    char symbol_name[MAX_LABEL_LEN + 1];
    unsigned int *machine_word;
};

struct extern_call {
    char extern_name[MAX_LABEL_LEN + 1];
    Vector call_addresses;
};

struct object_file {
    Vector code_section;
    Vector data_section;
    Vector symbol_table;
    Vector extern_calls;
    Vector missing_symbol_table;
    Trie symbol_table_lookup;
};

static void *ctor_mem_word(const void *copy) {
    return memcpy(malloc(sizeof(unsigned int)), copy, sizeof(unsigned int));
}

static void dtor_mem_word(void *item) {
    free(item);
}

static void *ctor_symbol(const void *copy) {
    return memcpy(malloc(sizeof(struct symbol)), copy, sizeof(struct symbol));
}

static void dtor_symbol(void *item) {
    free(item);
}

static void *ctor_extern_call(const void *copy) {
    const struct extern_call *c = copy;
    struct extern_call *new_extern = malloc(sizeof(struct extern_call));
    strcpy(new_extern->extern_name, c->extern_name);
    vector_init(&(new_extern->call_addresses), sizeof(unsigned int), NULL, NULL);
    return new_extern;
}

static void dtor_extern_call(void *item) {
    struct extern_call *ec = item;
    vector_destroy(&(ec->call_addresses));
    free(ec);
}

static int assembler_compiler(FILE *am_file, struct object_file *obj) {
    char line_buffer[MAX_LINE_LEN] = {0};
    ast ast;
    struct extern_call extern_call_sym = {0};
    struct missing_symbol m_symbol = {0};
    struct symbol local_sym = {0};
    struct symbol *find_sym;
    unsigned int extern_call_addr = 0;
    unsigned int line_counter = 1;
    unsigned int machine_word = 0;
    int i;
    unsigned int *just_inserted_m_word;

    while (fgets(line_buffer, sizeof(line_buffer), am_file)) {
        ast = lexer_get_ast(line_buffer);

        switch (ast.ast_opt) {
            case ast_label:
                if (ast.label_name[0] != '\0') {
                    strcpy(local_sym.sym_name, ast.label_name);
                    find_sym = trie_exists(obj->symbol_table_lookup, ast.label_name);
                    if (find_sym) {
                        if (find_sym->sym_type != sym_entry) {
                            /* ERROR: REDEF */
                        } else {
                            find_sym->sym_type = sym_entry_code;
                            find_sym->address = (unsigned int) vector_get_item_count(obj->code_section) + BASE_ADDR;
                        }
                    } else {
                        local_sym.sym_type = sym_code;
                        local_sym.address = (unsigned int) vector_get_item_count(obj->code_section) + BASE_ADDR;
                        trie_insert(obj->symbol_table_lookup, local_sym.sym_name, vector_insert(obj->symbol_table, &local_sym));
                    }
                }
                break;

            case ast_inst:
                // ... (same as before)

            case ast_dir:
                // ... (same as before)

            default:
                // Handle other cases or do nothing
                break;
        }
        line_counter++;
    }
}

int assembler(int file_count, char **file_names) {
    return 0;
}
