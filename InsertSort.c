
#include <stdio.h>

void showlist(int number[],int length){
    printf("{%d",number[0]);
    for(int i = 1; i<length ;i++){
        printf(",%d",number[i]);
    }
    printf("}\n");
}

void insertsort(int number[], int len){
    int temp,t,e;
    for(int i=1; i<len;i++){
        t = 0;
        showlist(number,len);
        while(number[t]<number[i])t++;

        for(int j=i;j>t;j--){
            temp = number[j];
            number[j] = number[j-1];
            number[j-1] = temp;
        }
            
        
    }
}

int main(void){
    static int list[] = {8,4,10,12,5,18,6};
    int len = 7;
    showlist(list,len);
    insertsort(list,len );
    showlist(list,len );

    return 0;
}