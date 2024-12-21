#include "struct.h"
#include "fun.h"

int main(int argc,char* argv[]){
    //Declare the hash_table
    main_node_t *hash_table[27]={NULL};
    //pointer for files list
    file_node_t *file = NULL;

    int create = 0,update = 0;

    //validation of the CLA's
   if(validate(argv,&file)==e_failure){
    return e_failure;
   }

   //if list is empty
   if(file==NULL){
    return e_failure;
   }

    int choice;
    char word[NAMELENGTH];
    char save_file[NAMELENGTH];
    while(choice!=6){
        printf("\n1.Create Database\n2.Search Word\n3.Save to file\n4.Display Database\n5.Update Database\n6.Exit\n\n");
        printf("Enter choice: ");
        scanf(" %d",&choice);
        switch(choice){
            //create data base once
            case 1: if(create_data_base(hash_table,file)!=e_failure && create == 0){
                create = 1;
            }
            else{
                printf("\nINFO: Data base already created\n");
            }
            break;
            
            //search a word
            case 2: printf("Enter the word to search: ");
            scanf("%s",word);
            search_word(hash_table,word);
            break;

            //to save to file
            case 3: printf("Enter file name where to be saved: ");
            scanf("%s",save_file);
            save_to_file(hash_table,save_file);
            break;

            //print the database
            case 4: print(hash_table);
            break;

            //to update data base
            case 5: 
            //cannot update after create
            if(create!=1){
            printf("Enter the file name using which data base to be created: ");
            scanf("%s",save_file);

            if(update == 0 && update_data_base(hash_table,save_file)!=e_failure){
                update = 1;
            }
            else{
                printf("\nINFO: Data base already updated\n");
            }
        }
        else{
            printf("\nINFO: update after create cannot be done\n");
        }
            break;

            case 6: exit(0);
            break;

            default: printf("\nINFO: Invalid choice!\n");
        }
    }
}