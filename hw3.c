#include <stdio.h> 
#include <stdlib.h> 
#include<time.h> 

#include <string.h>
#include<stdio.h>

int page_size = 4096;
void swap(int total_number_of_bytes,char *buffer,int *page_table){
    int total_number_of_pages = total_number_of_bytes / page_size;
    char temp[page_size];
    int temp_index;
    int first_index = rand() % total_number_of_pages;
    int second_index = rand() % total_number_of_pages;

    
    int temp_add = page_table[first_index];
    page_table[first_index] = page_table[second_index];
    page_table[second_index] = temp_add;



    for(int i=0; i < page_size; i++){
        temp[i] = buffer[first_index*page_size+i];
    }

    for(int i=0; i < page_size; i++){
        buffer[first_index*page_size+i] = buffer[second_index*page_size+i];
    }

    for(int i=0; i < page_size; i++){
        buffer[second_index*page_size+i] = temp[i];
    }
   
    for(int i=0; i < page_size; i++){
        temp[i] = buffer[first_index*page_size+i];
    }
}

void create_read_list(){
    return;
}
void print_page_table(int *page_table,int total_number_of_pages){

    for(int i=0; i < total_number_of_pages; i++){
        printf("%d.page_address : %d\n",i,page_table[i]);
    }
}
void print_mem(char *arr,int numbytes){
    for(int i=0; i < numbytes; i++){
        printf("%c",arr[i]);
    }
}

#include <stdio.h>

main() {
    srand(time(0)); 

    /*FILE *fp;
   char buff[255];

   fp = fopen("password.txt", "r");
   fscanf(fp, "%s", buff);
   printf("1 : %s\n", buff );

   fgets(buff, 255, (FILE*)fp);
   printf("2: %s\n", buff );
   
   fclose(fp);
     */
    
    
    /* declare a file pointer */
    FILE    *infile;
    char    *buffer;
    long    numbytes;
    
    
    /* open an existing file for reading */
    infile = fopen("test.txt", "r");
    
    /* quit if the file does not exist */
    if(infile == NULL)
        return 1;
    
    /* Get the number of bytes */
    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);
    printf("%d\n",numbytes/page_size);
    
    if( numbytes % page_size != 0 ){
        numbytes = ((numbytes / page_size) + 1) * page_size;
    }
    /* reset the file position indicator to 
    the beginning of the file */
    fseek(infile, 0L, SEEK_SET);	
    
    /* grab sufficient memory for the 
    buffer to hold the text */
    buffer = (char*)calloc(numbytes, sizeof(char));	
    
    /* memory error */
    if(buffer == NULL)
        return 1;
    
    /* copy all the text into the buffer */
    fread(buffer, sizeof(char), numbytes, infile);
    
    char *arr;
    arr = malloc(numbytes * sizeof(char));
    for(int i=0; i<numbytes;i++){
        arr[i] = buffer[i];
    }


    /* confirm we have read the file by
    outputing it to the console */
    //printf("The file called test.dat contains this text\n\n%d\n", sizeof(char) );
    


    int *page_table;
    int total_number_of_bytes = numbytes;
    int total_number_of_pages = total_number_of_bytes / page_size;
    printf("total_number_of_bytes %d\n",total_number_of_bytes);
    printf("total_number_of_pages %d\n",total_number_of_pages);
    
    page_table = malloc(total_number_of_pages * sizeof(int));
    for(int i=0; i < total_number_of_pages; i++){
        page_table[i] = arr + (i*page_size);
    }
    printf("\n");
    print_page_table(page_table,total_number_of_pages);
    int second_index = total_number_of_pages-1;
    
    int index = 0;
    int page_no = index / page_size;
    int address = 1 ;
    address = page_table[page_no]+index;

    printf("%d\n", address);
    printf("address arr :  %d \n",arr);

    //char value = *(char*)address;
    char value = "";
    printf("page arr :  %c \n",value );
    
    

    for(int i=0; i < 100;i++){
        index = index + i;
        address = page_table[page_no] + index; 
        //char* pointer = address;
        //printf("%d", *pointer );

    }
    printf("\narr:\n");

    index = 0;
    for(int i=0; i < 100;i++){
        index = index + i;
        printf("%d  ", &arr[page_no*page_size+index]);

    }
    printf("\n");

        
    for(int i=0; i < 100; i++){
        swap(numbytes,arr,page_table);
    }
    
    /*
    address = page_table[page_no] + index ;
    printf("abc: %c\n", &address );
    printf("arr: %c\n", arr[page_no*page_size+index]);

     */
    
    
    print_page_table(page_table,total_number_of_pages);
    

    /* free the memory we used for the buffer */

    free(buffer);


}