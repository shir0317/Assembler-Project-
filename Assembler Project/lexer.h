#ifndef lexer_h
#define lexer_h
#define MAX_NUMBER_DATA 100
#define MAX_LABEL_LEN 31
struct ast {
    char ast_syntax_error[140];
    char label_name[MAX_LABEL_LEN +1];
    enum{
        ast_inst,
        ast_dir,
        ast_comment,
        ast_null,
        ast_syntax_error
    }ast_opt;
    union {
        struct {
            enum{
                ast_dir_extern,
                ast_dir_entry,
                ast_dir_string,
                ast_dir_data,
            }ast_dir_opt;
            union {
                char *label_name;
                char * string;
                struct {
                    int data [MAX_NUMBER_DATA];
                    int data_count;
                }data;
            }dir_operands;
            
        }ast_dir;
        struct {
            enum {
                ast_inst_mov,
                ast_inst_cmp,
                ast_inst_add,
                ast_inst_sub,
                ast_inst_lea,
                
                
                ast_inst_not,
                ast_inst_clr,
                ast_inst_inc,
                ast_inst_dec,
                ast_inst_jmp,
                ast_inst_bne,
                ast_inst_red,
                ast_inst_prn,
                ast_inst_jsr,
                
                
                ast_inst_rts,
                ast_inst_stop,
            
            }ast_inst_opt;
        }ast_inst;
        union {
            int const_number;
            int register_number;
            char *label;
        }inst_operands[2];
    }dir_or_inst;
};
typedef struct ast ast;
ast lexer_get_ast(char *line);

#endif
