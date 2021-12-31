void visit_func_call(node *n, node *program);
void run_user_defined_fn(node *n, node *program);
node *find_var(node *program, char *ident);
node *find_fn_dec(node *program, char *ident);
node *traverse(node *n, node *program);
void move_to_end_of_fn_dec(node *curr_node);
void eval(node *program);
