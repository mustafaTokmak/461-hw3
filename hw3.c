#include <stdio.h> 
#include <stdlib.h> 
#include<time.h> 

#include <string.h>
#include<stdio.h>
#include <stdint.h>



int tlb_queue[10];
int tlb_queue_size=0;
int head=-1;
int tail=-1;
int size=0;

int page_size = 32;
void swap(int total_number_of_bytes,char *buffer,char **page_table){
    int total_number_of_pages = total_number_of_bytes / page_size;
    char temp[page_size];
    int temp_index;
    int first_index =  rand() % total_number_of_pages;
    int second_index =  rand() % total_number_of_pages;
    
    //TODO check same 
    if(first_index == second_index){
        second_index = rand() % total_number_of_pages;
    }

    //printf("%d\n",page_table[first_index]);
    //printf("%d\n",page_table[second_index]);

    
    //printf("\n%d\n",page_table[first_index]);
    //printf("%d\n",page_table[second_index]);


    char *temp_add;
    temp_add = page_table[first_index];


    for(int i=0; i < page_size; i++){
        //temp[i] = buffer[first_index*pa+ge_size+i];
        temp[i] = *(page_table[first_index]+i);
        //printf("%c",temp[i]);
    }   
    //printf("\n\n");
    for(int i=0; i < page_size; i++){
        //buffer[first_index*page_size+i] = buffer[second_index*page_size+i];
        *(page_table[first_index]+i) = *(page_table[second_index]+i);
        //printf("%c",*((char*)page_table[first_index]+i));
    }
        page_table[first_index] = page_table[second_index];  

    //printf("\n\n");
    for(int i=0; i < page_size; i++){
        //buffer[second_index*page_size+i] = temp[i];
        *((char*)page_table[second_index]+i)= temp[i];
        //printf("%c",*((char*)page_table[second_index]+i));
    }
    //printf("\n\n");
    page_table[second_index] = temp_add;

}   

void create_read_list(){
    return;
}

void print_page_table(char **page_table,int total_number_of_pages){

    for(int i=0; i < total_number_of_pages; i++){
        printf("%d.page_address : %d\n",i,page_table[i]);
    }
}
void print_mem(char *arr,int numbytes){
    for(int i=0; i < numbytes; i++){
        printf("%c",arr[i]);
    }
}
//
int get_address(char **page_table,int index){
    int i = index % page_size;
    int page_no = index / page_size;
    char *address;
    address = (char*)page_table[page_no]+i;
    printf("%d,%c\n",address,*address);
    return (int)address;
}
int get_tlb_index(char **tlb ,char* address){
    for(int i=0;i<10;i++){
        if(tlb[i] == address){
            //hit
            return i;
        }
    }
    //miss
    return -1;
}
void enqueu(int index){
    head =  (head +1) %10;
    tlb_queue[head] = index;
    size++;
}
int dequeue(){
    head =  (head-1) %10;
    int index = tlb_queue[head];
    size--;
}


int update_tlb(int tlb_index,char **tlb ,char* address){

    int index;
    if(tlb_index == -1){
        if(tlb_queue_size<10){
            printf("tlb_queue_size :%d\n",tlb_queue_size);
            tlb[tlb_queue_size] = address;
            tlb_queue[tlb_queue_size] = tlb_queue_size;
            tlb_queue_size++;
            for(int i = 0;i<tlb_queue_size;i++){
                printf("tlb_queue[%d] : %d\n",i,tlb_queue[i]);
            }
        }
        else{
            int temp_queue[10];
            for(int i = 0;i<tlb_queue_size;i++){
                temp_queue[i] = tlb_queue[i];
                
            }
            tlb_queue[0] = tlb_queue[tlb_queue_size-1];
            for(int i = 0;i<tlb_queue_size;i++){
                tlb_queue[i+1] = temp_queue[i];
            }
            tlb[tlb_queue[0]] = address;
            for(int i = 0;i<tlb_queue_size;i++){
                printf("tlb_queue[%d] : %d\n",i,tlb_queue[i]);
            }
            //printf("tlb_queue[0] : %d\n",tlb_queue[0]);
            printf("tlb[tlb_queue[0]] : %d\n",tlb[tlb_queue[0]]);


            
        }
            
        return 0;
    }
    
    //UPDATE TLB QUEUE
    int temp_queue[10];
    for(int i = 0;i<tlb_queue_size;i++){
        temp_queue[i] = tlb_queue[i];
    }
    tlb_queue[0] = tlb_index;
    int j = 0;
    for(int i = 1;i<tlb_queue_size;i++){
        if(temp_queue[j]==tlb_index){
            j++;
            continue;
        }
        tlb_queue[i] = temp_queue[j];
        j++;
    }

    



    return 0;
}
#include <stdio.h>

main() {

    srand(time(0)); 
    int access[100];
    access[1]=0;
    for(int i=0;i<100;i++){
        access[i] = rand()% 280;

    }
 
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
    


    char **page_table;
    int total_number_of_bytes = numbytes;
    int total_number_of_pages = total_number_of_bytes / page_size;
    printf("total_number_of_bytes %d\n",total_number_of_bytes);
    printf("total_number_of_pages %d\n",total_number_of_pages);
    
    //page_table = malloc(total_number_of_pages * sizeof(char*));
    for(int i=0; i < total_number_of_pages; i++){
        page_table[i] = &arr[i*page_size];
    }
    printf("\n");
    print_page_table(page_table,total_number_of_pages);
        printf("\n");

    int second_index = total_number_of_pages-1;
    
    int index = 0;
    int page_no = index / page_size;
    char *address;
    address =     (char*)page_table[page_no]+index;
//    printf("%d\n", address);
  //  printf("address arr :  %c \n",*address);
    //char value = *(char*)address;
    
    index = 0;
    for(int i=0; i < 32; i++){
        address = (char*)page_table[page_no]+i;
        index = index + i;
        //printf("%c",*address);    
    }
    

    for(int i=0; i < 100; i++){
        swap(numbytes,arr,page_table);
    }
    print_page_table(page_table,total_number_of_pages);

    index = 0;
    

    
    
    address =(char*)page_table[page_no]+index;
    printf("%d,%c\n",address,*address);
    //char* add = malloc(sizeof(char*));
    int a = get_address(page_table,index);
    //char *value = (char*)(intptr_t)a;

    printf("%d\n",a);
    
    
    char *tlb[10];

    int hit =0;
    int miss = 0;
    char *page_address;

    for(int i=0;i<100;i++){
        int index = access[i] % page_size;
        int page_no =  access[i] / page_size;
        address =(char*)page_table[page_no]+index;
        page_address = (char*)page_table[page_no];
        
        int tlb_index = get_tlb_index(tlb,page_address);
        if(tlb_index > -1){
            hit++;
        }
        else{
            miss++;
        }
        update_tlb( tlb_index,tlb ,page_address);        
        for(int i = 0;i<tlb_queue_size;i++){
            printf("%d \n",tlb[0]);
        }
        printf("\n\n");
        

    }
    printf("hit :%d\n",hit);
    printf("miss :%d\n",miss);




    free(buffer);
    free(arr);


}