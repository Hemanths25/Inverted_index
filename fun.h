//validation part
Status validate(char** argv,file_node_t **head);
Status check_file_txt(char* file_name);
FILE* check_file_present(char* file_name);
Status check_file_empty(FILE* fp);
Status file_repeated(file_node_t *head,char* file_name);
Status insert_to_list(file_node_t **head, char* file_name);
void print_list(file_node_t *head);

//create database
Status create_data_base(main_node_t **hash,file_node_t *file);
FILE* open_file(char* file_name);
int generate_index(char* words);
Status main_node(main_node_t **hash,int index,char* word,char* file);

//search word
Status search_word(main_node_t **hash,char* word);

//save and print
Status save_to_file(main_node_t **hash,char* save_file);
void print(main_node_t **hash);

//update database
Status update_data_base(main_node_t **hash,char* save_file);