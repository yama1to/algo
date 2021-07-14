
#include <stdio.h>

void showlist(int number[],int length){
    printf("{%d",number[0]);
    for(int i = 1; i<length ;i++){
        printf(",%d",number[i]);
    }
    printf("}\n");
}



/* 値を入れ替える関数 */
void swap (int *x, int *y) {
  int temp;    // 値を一時保存する変数

  temp = *x;
  *x = *y;
  *y = temp;
}

/* pushdouwn操作 */
void pushdown (int array[], int first, int last) {
  int parent = first;   // 親
  int child = 2*parent;   // 左の子
  while (child <= last) {
    if ((child < last) && (array[child] < array[child+1])) {
       child++;   // 右の子の方が大きいとき、右の子を比較対象に設定
    }
    if (array[child] <= array[parent]) { break; }   // ヒープ済み
    swap(&array[child], &array[parent]);
    parent = child;
    child = 2* parent;
  }
}

/* ヒープソート */
void heapsort (int array[], int array_size) {
  int i;

  for (i = array_size/2; i >= 1; i--) {
    pushdown(array, i, array_size);   // 全体をヒープ化
  }
  for (i = array_size; i >= 2; i--) {
    swap(&array[1], &array[i]);   // 最大のものを最後に
    pushdown(array, 1, i-1);   // ヒープ再構築
  }
}
int main(void){
    //static int list[] = {8,4,10,12,5,18,6};
    static int list[] = { 0, 2, 1, 8, 5, 4, 7, 9, 10, 6, 3 };
    //int len = 7;
    int len = 11;
    showlist(list,len+1);
    heapsort(list,len );

    printf("After sort: ");
    for (int i = 2; i < len+1; i++) { printf("%d ", list[i]); }
    printf("\n");

    return 0;
}