#include "struct.h"
#include "fun.h"

sub_node_t *sub = NULL;

//to create database
Status create_data_base(main_node_t **hash,file_node_t *file){
    //looping till all files are completed
    while(file!=NULL){
        //opening file
       FILE *fp = open_file(file->f_name);
       char words[NAMELENGTH];
       while(fscanf(fp,"%s",words)==1){
        //generating the index
       int index = generate_index(words);
       //adding to database
       if(main_node(hash,index,words,file->f_name)==e_failure){
        return e_failure;
       }     
      }
       file=file->link;
    }
    printf("\nINFO: Database created successfully\n");
    return e_success;
}

//opening file in read mode
FILE* open_file(char* file_name){
    FILE* fp = fopen(file_name,"r");
    return fp;
}

//generating the index
int generate_index(char* words){
    //taking first character of the word
    char ch = words[0];
    int index;
    switch(ch){
        //for alphabets the index is from 0-25
        case 'a' ... 'z': index = ch-'a';
        break;
        case 'A' ... 'Z': index = ch-'A';
        break;
        //for characters other than alphabet the index is 26
        default: index = 26;
    }
    return index;
}

//to create database
Status main_node(main_node_t **hash, int index, char *word, char *file) {
    if (hash[index] != NULL) {
        main_node_t *temp = hash[index];

        // Check if the word already exists
        while (temp != NULL) {
            if (strcmp(temp->word, word) == 0) {
                // Traverse sublist for file entries
                sub_node_t *sub_temp = temp->sub_link;
                while (sub_temp != NULL) {
                    if (strcmp(sub_temp->f_name, file) == 0) {
                        sub_temp->w_count++;
                        return e_success; // Word and file found, count updated
                    }
                    if (sub_temp->link == NULL) 
                    break;
                    sub_temp = sub_temp->link;
                }
                
                // Add a new sub-node if file is not found
                sub_temp->link = malloc(sizeof(sub_node_t));
                if (sub_temp->link == NULL) {
                    printf("Memory allocation failed");
                    return e_failure;
                }
                sub_temp = sub_temp->link;
                strcpy(sub_temp->f_name, file);
                sub_temp->w_count = 1;
                sub_temp->link = NULL;

                temp->f_count++; // Increment file count for the word
                return e_success;
            }
            temp = temp->link;
        }

        // Word not found, add a new main node at the end
        temp = hash[index];
        while (temp->link != NULL) {
            temp = temp->link;
        }

        temp->link = malloc(sizeof(main_node_t));
        if (temp->link == NULL) {
            printf("Memory allocation failed");
            return e_failure;
        }

        temp = temp->link;
        strcpy(temp->word, word);
        temp->f_count = 1;
        temp->link = NULL;

        sub_node_t *sub_temp = temp->sub_link = malloc(sizeof(sub_node_t));
        if (sub_temp == NULL) {
            printf("Memory allocation failed");
            return e_failure;
        }
        strcpy(sub_temp->f_name, file);
        sub_temp->w_count = 1;
        sub_temp->link = NULL;

    } else {
        // First node in the list
        hash[index] = malloc(sizeof(main_node_t));
        if (hash[index] == NULL) {
            printf("Memory allocation failed");
            return e_failure;
        }
        strcpy(hash[index]->word, word);
        hash[index]->f_count = 1;
        hash[index]->link = NULL;

        sub_node_t *sub_temp = hash[index]->sub_link = malloc(sizeof(sub_node_t));
        if (sub_temp == NULL) {
            printf("Memory allocation failed");
            return e_failure;
        }
        strcpy(sub_temp->f_name, file);
        sub_temp->w_count = 1;
        sub_temp->link = NULL;
    }
    return e_success;
}

//to search a word in database
Status search_word(main_node_t **hash,char* word){
    //generate index
    int index = generate_index(word);
    //if the index is null then no word
    if(hash[index]==NULL){
        printf("\nINFO: Word not found!\n");
    }
    //if not null search for the word
    else{
        main_node_t *main_temp = hash[index];
        while(main_temp!=NULL){
            //if word found
            if(strcmp(word,main_temp->word)==0){
              sub_node_t *sub_temp =  main_temp->sub_link;
              //print main node details
              printf("\n[%d] %s %d",index,word,main_temp->f_count);

              while(sub_temp!=NULL){
                //print subnode details
                printf(" %s %d",sub_temp->f_name,sub_temp->w_count);
                sub_temp = sub_temp->link;
              }
              printf("\n\n");
              return e_success;
            }
            main_temp = main_temp->link;
        }
        //if no word is found in database
        printf("\nINFO: Word not found!\n\n");
    }
}

//save to file
Status save_to_file(main_node_t **hash,char* save_file){

    //check file is txt
    if(check_file_txt(save_file)==e_failure){
        return e_failure;
    }

    //check file present or not
    FILE* fp = fopen(save_file,"w");
    if(fp==NULL){
        printf("\nINFO: File not found!\n");
        return e_failure;
    }
    //print details to file 
    else{
    int i=0;
    main_node_t **temp = hash;
    for(int i=0;i<27;i++){
        if(temp[i]!=NULL){
            main_node_t *MT = temp[i];
            while(MT!=NULL){
              fprintf(fp,"#[%d],",i);
              fprintf(fp,"%s,",MT->word); 
              fprintf(fp,"%d,",MT->f_count);
              sub_node_t *ST = MT->sub_link;

              while(ST!=NULL){
                fprintf(fp,"%s,",ST->f_name);
                fprintf(fp,"%d",ST->w_count);
                if(ST->link!=NULL)
                fprintf(fp,",");
                ST=ST->link;
              }

              MT = MT->link; 
              fprintf(fp,"#\n"); 
            } 
        }
    }
  } 
    fclose(fp); 
    printf("\nINFO: Data saved successfully\n");
}

//printing the details on terminal
void print(main_node_t **hash){
    int i=0;
    main_node_t **temp = hash;
    printf("\nINFO: Displaying data in formate\n");
    printf("[index] word file_count file_name word_count...\n\n");
    for(int i=0;i<27;i++){
        if(temp[i]!=NULL){
            main_node_t *MT = temp[i];
            while(MT!=NULL){
              printf("[%d] ",i);
              printf("%s ",MT->word); 
              printf("%d ",MT->f_count);
              sub_node_t *ST = MT->sub_link;
              while(ST!=NULL){
                printf("%s ",ST->f_name);
                printf("%d ",ST->w_count);
                ST=ST->link;
              }
              MT = MT->link; 
              printf("\n"); 
            } 
        }
    }
}