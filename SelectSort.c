#include <stdio.h>

void showlist(int number[],int length){
    printf("{%d",number[0]);
    for(int i = 1; i<length ;i++){
        printf(",%d",number[i]);
    }
    printf("}\n");
}

void selectsort(int number[],int len){
    int argmin,temp;
    argmin = 0;
    for(int i=0;i<len;i++){
        for(int j=i;j<len;j++){
            if(number[j] < number[argmin]){
                argmin = j;
            }
        }
        temp = number[i];
        number[i] = number[argmin]; 
        number[argmin] = temp;
        
        showlist(number,len );
    }

}

int main(void){
    static int list[] = {8,4,10,12,5,18,6};
    int len = 7;
    showlist(list,len);
    selectsort(list,len );
    showlist(list,len );

    return 0;
}