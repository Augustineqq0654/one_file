#include <stdio.h>
#include <stdlib.h>
int copyFile(char *fileRead, char *fileWrite);
int main(){
    char fileRead[100]; // 要复制的文件名
    char fileWrite[100]; // 复制后的文件名
// 获取用户输入
    printf("要复制的文件：");
    scanf("%s", fileRead);
    printf("将文件复制到：");
    scanf("%s", fileWrite);
// 进行复制操作
    if( copyFile(fileRead, fileWrite) ){
        printf("恭喜你，文件复制成功！\n");
    }else{
        printf("文件复制失败！\n");
    }
    return 0;
}
/**
* 文件复制函数
* @param fileRead 要复制的文件
* @param fileWrite 复制后文件的保存路径
* @return int 1: 复制成功；2: 复制失败
**/
int copyFile(char *fileRead, char *fileWrite){
    FILE *fpRead; // 指向要复制的文件
    FILE *fpWrite; // 指向复制后的文件
    int bufferLen = 1024*4; // 缓冲区长度
    char *buffer = (char*)malloc(bufferLen); // 开辟缓存
    int readCount; // 实际读取的字节数
    if( (fpRead=fopen(fileRead, "rb")) == NULL || (fpWrite=fopen(fileWrite, "wb")) == NULL ){
        printf("Cannot open file, \n");
        exit(0);
    }
// 不断从fileRead读取内容，放在缓冲区，再将缓冲区的内容写入fileWrite
    while( (readCount=fread(buffer, 1, bufferLen, fpRead)) > 0 ){
        fwrite(buffer, readCount, 1, fpWrite);
    }
    free(buffer);
    fclose(fpRead);
    fclose(fpWrite);
    return 1;
}