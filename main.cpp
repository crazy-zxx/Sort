#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

#define MAXSIZE 1024
typedef int KeyType;
typedef struct {
    KeyType key;
    //InfoType otherInfo;
} RedType;
typedef struct {
    RedType r[MAXSIZE + 1];
    int length;
} SqList;

//全局变量，排序序列
SqList L;

//生成随机数列，用来排序使用
void initSqList(SqList &L) {

    do {
        printf("输入序列长度(0<length<%d)：", MAXSIZE);
        scanf("%d", &L.length);
    } while (L.length > MAXSIZE || L.length < 1);

    srand(time(NULL));
    //r[1 ... length]随机赋值[-MAXSIZE/2,MAXSIZE/2]
    for (int i = 1; i <= L.length; ++i) {
        L.r[i].key = (rand() % (MAXSIZE + 1)) - ((MAXSIZE + 1) / 2);
    }
}

//手动输入序列
void inputSqList(SqList &L) {

    do {
        printf("输入序列长度(0<length<%d)：", MAXSIZE);
        scanf("%d", &L.length);
    } while (L.length > MAXSIZE || L.length < 1);

    printf("输入序列：");
    //r[1 ... length]手动赋值
    for (int i = 1; i <= L.length; ++i) {
        scanf("%d", &L.r[i].key);
    }
}

//打印序列
void printSqList(SqList L) {
    for (int i = 1; i <= L.length; ++i) {
        printf("%d ", L.r[i].key);
    }
    printf("\n");
}

//直接插入排序
void InsertSort(SqList &L) {

    int i, j;
    for (i = 2; i <= L.length; ++i) {
        //倒着比较
        if (L.r[i].key < L.r[i - 1].key) {                  //当前 i < i-1 ,需要前移
            L.r[0] = L.r[i];                                //放置哨兵，做比较判断和结束查找用
            L.r[i] = L.r[i - 1];                            //移动 i-1 => i

            for (j = i - 2; L.r[0].key < L.r[j].key; --j) { //继续判断i-2及之前，查找插入位置，并右移 大于 插入值的
                L.r[j + 1] = L.r[j];
            }

            L.r[j + 1] = L.r[0];                            //插入位置
        }
        //打印每趟的序列结果
        printSqList(L);
    }
}

//折半插入（二分插入）排序
void BInsertSort(SqList &L) {

    for (int i = 2; i <= L.length; ++i) {
        L.r[0] = L.r[i];                        //保存需插入值

        //在[1，i-1]中折半查找 i 的插入位置
        int low = 1, high = i - 1, mid;
        while (low <= high) {                   //low <= high
            mid = (low + high) / 2;
            if (L.r[0].key < L.r[mid].key) {    //在前半部分
                high = mid - 1;
            } else {                            //在后半部分
                low = mid + 1;
            }
        }
        for (int j = i - 1; j > high; --j) {    //移动[high+1,i-1] 至 [high+2,i]
            L.r[j + 1] = L.r[j];
        }
        L.r[high + 1] = L.r[0];                 //在 high+1 插入

        //打印每趟的序列结果
        printSqList(L);
    }

}

//希尔提供的增量序列，即{N/2, (N / 2)/2, ..., 1}
void initDelta(SqList L, int delta[], int &len) {

    len = 0;
    delta[len] = L.length / 2;
    while (len++,delta[len-1]!=0 && delta[len-1]!=1){
        delta[len] = delta[len - 1] / 2;
    }

}

//打印增量序列
void printDelta(int delta[], int len) {
    for (int i = 0; i < len; ++i) {
        printf("%d ", delta[i]);
    }
    printf("\n");
}

//一趟希尔插入，即为直接插入
void ShellInsert(SqList &L, int dk) {

    int i, j;
    for (i = dk + 1; i <= L.length; ++i) {      //跨过一个当前增量长度，从 dk+1 开始，间隔当前增量向前比较
        if (L.r[i].key < L.r[i - dk].key) {     //当前 i 小于间隔增量dk 的前一个 i-dk，需要前插
            L.r[0] = L.r[i];
            for (j = i - dk;
                 j > 0 && L.r[0].key < L.r[j].key; j -= dk) {   //继续向前比较，每次间隔增量dk(此处为了代码简洁，重复比较了一次上边的 i 和 i-dk)
                L.r[j + dk] = L.r[j];           //比插入值 大的 统统间隔增量dk 右移
            }
            L.r[j + dk] = L.r[0];               //在 j+dk 处插入
        }
    }
}

//希尔排序，需要提供增量序列
void ShellSort(SqList &L, int delta[], int len) {

    for (int i = 0; i < len; ++i) {     //按增量序列，进行len趟希尔插入
        ShellInsert(L, delta[i]);

        //打印每趟排序结果
        printSqList(L);
    }

}

//TODO


int menu() {
    int select = 0;
    printf("***************************************\n");
    printf("1.自动生成数据\n");
    printf("2.手动输入数据\n");
    printf("0.退出\n");
    printf("***************************************\n");
    printf("输入所需操作编号：");
    scanf("%d", &select);
    switch (select) {
        case 0:
            return 0;
        case 1:
            initSqList(L);
            break;
        case 2:
            inputSqList(L);
            break;
    }

    printf("***************************************\n");
    printf("1.直接插入排序\n");
    printf("2.折半插入排序\n");
    printf("3.希尔排序\n");
    printf("4.排序\n");
    printf("5.排序\n");
    printf("6.排序\n");
    printf("7.排序\n");
    printf("8.排序\n");
    printf("0.退出\n");
    printf("***************************************\n");
    printf("输入所需操作编号：");
    scanf("%d", &select);
    printf("***************************************\n");
    printf("原数列：");
    printSqList(L);
    switch (select) {
        case 0:
            return 0;
        case 1:
            InsertSort(L);
            break;
        case 2:
            BInsertSort(L);
            break;
        case 3:
            int delta[MAXSIZE], len;
            initDelta(L, delta, len);
            printDelta(delta, len);
            ShellSort(L, delta, len);
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
    }

    return 1;
}

int main() {

    if ('s') {

    }
    while (menu()) {}

    return 0;
}
