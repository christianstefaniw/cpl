typedef struct
{
    node *program;
    node *curr_fn;
} scope;

#define PRNT "print"

void visit_func_call(node *n);
void run_user_defined_fn(node *n);
node *find_var(char *ident);
node *find_fn_dec(char *ident);
node *traverse(node *n);
void move_to_end_of_fn_dec(node *curr_node);
void eval(node *program);
