#include "struct.h"
#include "fun.h"

int flag=0;

//validation function
Status validate(char** argv,file_node_t **head){
    //if no files are passed
    if(argv[1]==NULL){
        printf("ERROR: No files passed\n");
        return e_failure;
    }

    //check all files txt or not
    printf("\n");
    for(int i=1;argv[i]!=NULL;i++){
        if(check_file_txt(argv[i])==e_failure){
            printf("INFO: %s file is not a txt file\n",argv[i]);
            continue;
        }

        //to check file is present in directory
        FILE* fp = check_file_present(argv[i]);
        if(fp==NULL){
            printf("INFO: %s file not present\n",argv[i]);
            continue;
        }

        //to check if file is empty
        if(check_file_empty(fp)==e_failure){
            printf("INFO: %s file is empty, and will not be included\n",argv[i]);
            continue;
        }

        //to check file is repeated in the CLA
        if(file_repeated(*head,argv[i])==e_failure){
            printf("INFO: %s file is repeated\n",argv[i]);
            continue;
        }
        else{ 
            flag=1;
            //if all condition is passed insert to list
            insert_to_list(head,argv[i]);
        }
        //close the files
        fclose(fp);
    }
}

//to check file is txt or not
Status check_file_txt(char* file_name){
    //taking . address
    file_name = strchr(file_name,'.');
    if(file_name==NULL){
        return e_failure;
    }
    //comparing with .txt
    if(strcmp(file_name,".txt")!=0){
        return e_failure;
    }
}

//check if file is present or not
FILE* check_file_present(char* file_name){
    //opening the file in read mode
    FILE* fp = fopen(file_name,"r");
    return fp; 
}

//check file is empty or not
Status check_file_empty(FILE* fp){
    //taking the offset to end
    fseek(fp,0,SEEK_END);
    //printing the offset position
    if(ftell(fp)==0){
        return e_failure;
    } 
}

//check if file is repeated
Status file_repeated(file_node_t *head,char* file_name){
    while(head!=NULL){
        //checking the name in all nodes
        if(strcmp(head->f_name,file_name)==0){
            return e_failure;
        }
        head = head->link;
    }
}

//insert file names to list
Status insert_to_list(file_node_t **head, char* file_name){
    file_node_t *new = malloc(sizeof(file_node_t));
    if(new == NULL){
        return e_failure;
    }
    strcpy(new->f_name,file_name);
    new->link = NULL;

    if(*head == NULL){
        *head = new;
        return e_success;
    }
    file_node_t *temp = *head;
    while(temp->link){
        temp = temp->link;
    }
    temp->link = new;
    return e_success; 
}

//to print the list of names of files
void print_list(file_node_t *head)
{
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
    else
    {
	    while (head)		
	    {
		    printf("%s -> ", head -> f_name);
		    head = head -> link;
	    }

	    printf("NULL\n");
    }
}