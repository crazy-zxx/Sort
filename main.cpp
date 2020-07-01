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
    while (len++, delta[len - 1] != 0 && delta[len - 1] != 1) {
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

//冒泡排序
void BubbleSort(SqList &L) {

    for (int i = 1; i < L.length; ++i) {            // length-1 趟冒泡
        for (int j = 1; j <= L.length - i; ++j) {   // 每次从[1,L.length-1]依次两两比较找出最大的，放在右边
            if (L.r[j].key > L.r[j + 1].key) {      //前大后小，交换
                RedType temp = L.r[j];
                L.r[j] = L.r[j + 1];
                L.r[j + 1] = temp;
            }
        }
        //打印每趟结果
        printSqList(L);
    }
}

//改进冒泡排序
void BubbleSortPro(SqList &L) {

    for (int i = 1; i < L.length; ++i) {

        int exchange = 0;     //交换标志，每趟初始默认有序无需交换

        for (int j = 1; j <= L.length - i; ++j) {
            if (L.r[j].key > L.r[j + 1].key) {
                RedType temp = L.r[j];
                L.r[j] = L.r[j + 1];
                L.r[j + 1] = temp;
                exchange = 1;       //发生交换，修改标志
            }
        }
        if (!exchange) {      //如果当前一趟没有发生交换，说明已经有序
            break;
        }
        //打印每趟结果
        printSqList(L);
    }

}

//快速排序一次划分
int Partition(SqList &L, int low, int high) {

    //可以改进随机值位置为枢纽可以相对避免左右一长一短的极端情况
    //但是要保证两端向中间交替扫描，需要通过交换 该随机位置 与 最左端位置 的数据实现
//    srand(time(NULL));
//    int pos = (rand() % (high - low +1)) + low;  //[low,high]中的任意值
//    RedType temp=L.r[pos];
//    L.r[pos]=L.r[low];
//    L.r[low]=temp;

    //以最左值为枢纽
    L.r[0] = L.r[low];
    int key = L.r[low].key;

    while (low < high) {        //两端向中间交替扫描
        while (low < high && L.r[high].key > key) high--;   //先从右向左，找小于枢纽的交换
        L.r[low] = L.r[high];
        while (low < high && L.r[low].key < key) low++;     //再从左向右，找大于枢纽的交换
        L.r[high] = L.r[low];
    }
    L.r[low] = L.r[0];      //将枢纽值插入中间，最终形成左小右大序列

    return low;     //返回枢纽位置
}

//快速排序
void QSort(SqList &L, int low, int high) {
    if (low < high) {
        int keyPos = Partition(L, low, high);    //划分，获取枢纽位置

        //打印每趟结果
        printSqList(L);

        QSort(L, low, keyPos - 1);          //对左子表递归排序
        QSort(L, keyPos + 1, high);          //对右子表递归排序

    }
}

//调用快速排序
void QuickSort(SqList &L) {
    QSort(L, 1, L.length);
}

//简单选择排序
void SelectSort(SqList &L) {

    for (int i = 1; i < L.length; ++i) {
        L.r[0] = L.r[i];        //保存 i 值，以备用于交换 i 与 min 处值
        int min = i;            //记录最小值下标，默认 i 处值最小

        for (int j = i + 1; j <= L.length; ++j) {   //从[i,L.length]区间
            if (L.r[j].key < L.r[min].key) {        //找出最小值下标
                min = j;
            }
        }
        if (min != i) {             //找到比 i 处更小的值，交换位置，将该值值交换到 i 处
            L.r[i] = L.r[min];
            L.r[min] = L.r[0];
        }

        //打印每趟结果
        printSqList(L);
    }
}

//调整为大顶堆
void HeapAdjustBigger(SqList &L, int s, int m) {

    RedType temp = L.r[s];      //备份当前堆顶元素，以备交换

    for (int i = 2 * s; i <= m; i *= 2) {           //比较s的左(i)右(i+1)孩子大小
        if (i < m && L.r[i].key < L.r[i + 1].key) { //取二孩子中最大值，若无右孩子，默认左孩子是孩子中的最大值
            i++;
        }
        if (temp.key >= L.r[i].key) {               //比较s与其孩子中的最大值，若s大，结束比较（由于是从下往上调整，若根大于孩子，那么其所有孩子已经比其更小，无须再向下找）
            break;
        }
        L.r[s] = L.r[i];            //否则，s取其孩子最大值
        s = i;                      //继续深入下一层，比较s孩子的孩子，寻找最大值
    }

    L.r[s] = temp;      //将最大值插入为堆顶
}

//堆排序(大顶堆)
void HeapSort(SqList &L) {
    for (int i = L.length / 2; i > 0; --i) {      //调整为大顶堆，从N/2开始，调整其与左右孩子
        HeapAdjustBigger(L, i, L.length);

        //打印每趟结果
        printSqList(L);
    }
    for (int i = 1; i < L.length; ++i) {        //取出堆顶元素，将[1,L.length-i]重新调整为大顶堆
        RedType temp = L.r[1];                  //将堆顶与最后一个交换，使不再参与调整
        L.r[1] = L.r[L.length - i + 1];
        L.r[L.length - i + 1] = temp;

        HeapAdjustBigger(L, 1, L.length - i);

        //打印每趟结果
        printSqList(L);
    }
}

//归并两个有序序列为一个有序序列

//二路归并

//调用二路归并



//基数排序




int menu() {
    int select = 0;
    printf("***************************************\n");
    printf("1.自动生成数据\n");
    printf("2.手动输入数据\n");
    printf("0.退出！\n");
    do {
        printf("输入所需操作编号(0-2)：");
        scanf("%d", &select);
    } while (select < 0 || select > 2);
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
    printf("4.冒泡排序\n");
    printf("5.改进冒泡排序\n");
    printf("6.快速排序\n");
    printf("7.简单选择排序\n");
    printf("8.堆排序\n");
    printf("0.退出\n");
    do {
        printf("输入所需操作编号(0-8)：");
        scanf("%d", &select);
    } while (select < 0 || select > 8);

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
            BubbleSort(L);
            break;
        case 5:
            BubbleSortPro(L);
            break;
        case 6:
            QuickSort(L);
            break;
        case 7:
            SelectSort(L);
            break;
        case 8:
            HeapSort(L);
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
