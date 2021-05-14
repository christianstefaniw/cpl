typedef struct
{
    size_t cap;
    size_t len;
    char *buffer;
} growable_buf;

void init_growable_buff(growable_buf *buf_g, size_t cap);
void insert_growable_buff(growable_buf *buf_g, char elem);
void free_growable_buff(growable_buf *buf_g);
int count_characters(const char *str, char character);
int index_at(char *value, char find);
