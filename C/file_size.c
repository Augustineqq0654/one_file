#include<stdio.h>
#include<stdlib.h>
long fsize(FILE *fp);
int main(){
    long size = 0;
    FILE *fp = NULL;
    char filename[30] = "demo.txt";
    if( (fp = fopen(filename, "rb")) == NULL ){ //以二进制方式打开文件
        printf("Failed to open %s...", filename);
        exit(0);
    }
    printf("%ld\n", fsize(fp));
    return 0;
}
long fsize(FILE *fp){
    long n;
    fpos_t fpos; //当前位置
    fgetpos(fp, &fpos); //获取当前位置
    fseek(fp, 0, SEEK_END);
    n = ftell(fp);
    fsetpos(fp,&fpos); //恢复之前的位置
    return n;
}