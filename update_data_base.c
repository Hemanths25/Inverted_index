#include "struct.h"
#include "fun.h"

//check file is valid for updation
Status check_valid_file(FILE* fp){
    int key=0;
    char line[100];
    //taking one line from the file
    fscanf(fp,"%[^\n]\n",line);
        int i=0;
        //checking is '#' is present
        while(line[i]!=0){
            if(line[i]=='#'){
                key++;
            }
            i++;
        }
        
        //if '#' is not present invalid file
        if(key!=2){
            return e_failure;
        }
    //rewinding the offset
    rewind(fp);
}

//Updating to database
Status update_data_base(main_node_t **hash,char* save_file){
    
    //checking the file is txt or not
    if(check_file_txt(save_file)==e_failure){
        printf("ERROR: %s file is not a txt file\n",save_file);
        return e_failure;
    }

    //checking file is present or not
    FILE *fp = check_file_present(save_file);
    if(fp == NULL){
        printf("ERROR: %s file is not found\n",save_file);
        return e_failure;
    }

    //check file is valid or not
    if(check_valid_file(fp)==e_failure){
        printf("ERROR: %s file is not a valid file for update\n",save_file);
        return e_failure;
    }

    int index, file_count;
    char word[NAMELENGTH];

    //run the loop till we read 3 words
    while(fscanf(fp," #[%d],%[^,],%d", &index, word, &file_count) == 3){

        // Allocate new main_node_t
        main_node_t *new_node = malloc(sizeof(main_node_t));

        new_node->f_count = file_count;
        strcpy(new_node->word, word);
        new_node->link = NULL;
        new_node->sub_link = NULL;

        // Insert into hash table
        if(hash[index] == NULL){
            hash[index] = new_node;
        }else{
            main_node_t *temp = hash[index];
            while (temp->link) {
                temp = temp->link;
            }
            temp->link = new_node;
        }

        // Read sub-nodes (file details)
        sub_node_t **sub_ptr = &(new_node->sub_link);
        for(int i = 0; i < file_count; i++){
            sub_node_t *sub_node = malloc(sizeof(sub_node_t));

            fscanf(fp,",%[^,],%d", sub_node->f_name, &sub_node->w_count);

            sub_node->link = NULL;
            *sub_ptr = sub_node;
            sub_ptr = &(sub_node->link);
        }

        // Skip '#' at the end of the line
        char end_marker;
        if (fscanf(fp,"#") != 0) {
        // Do nothing, just advance the pointer
        }
    }
    //close the file
    fclose(fp);
    printf("\nINFO: Data base updated successfully\n");
    return e_success;
}