#include <stdio.h>
#include <stdlib.h>

#define FILENAME "filename.txt"
/**
* 文件复制函数
* @param fSource 要复制的原文件
* @param offsetSource 原文件的位置偏移（相对文件开头），也就是从哪里开始复制
* @param len 要复制的内容长度，小于0表示复制offsetSource后边的所有内容
* @param fTarget 目标文件，也就是将文件复制到哪里
* @param offsetTarget 目标文件的位置偏移，也就是复制到目标文件的什么位置
* @return 成功复制的字节数
**/
long fcopy(FILE *fSource, long offsetSource, long len, FILE *fTarget, long offsetTarget){
	int bufferLen = 1024*4; // 缓冲区长度
	char *buffer = (char*)malloc(bufferLen); // 开辟缓存
	int readCount; // 每次调用fread()读取的字节数
	long nBytes = 0; //总共复制了多少个字节
	int n = 0; //需要调用多少次fread()函数
	int i; //循环控制变量
	
	fseek(fSource, offsetSource, SEEK_SET);
	fseek(fTarget, offsetTarget, SEEK_SET);
	
	if(len<0)
	{ //复制所有内容
		while( (readCount=fread(buffer, 1, bufferLen, fSource)) > 0 )
		{
			nBytes += readCount;
			fwrite(buffer, readCount, 1, fTarget);
		}
	}else
	{ //复制len个字节的内容
		n = (int)ceil((double)((double)len/bufferLen));
		for(i=1; i<=n; i++)
		{
			if(len-nBytes < bufferLen){ bufferLen = len-nBytes; }
			readCount = fread(buffer, 1, bufferLen, fSource);
			fwrite(buffer, readCount, 1, fTarget);
			nBytes += readCount;
		}
	}
	fflush(fTarget);
	free(buffer);
	
	return nBytes;
}

/**
* 向文件中插入内容
* @param fp 要插入内容的文件
* @param buffer 缓冲区，也就是要插入的内容
* @param offset 偏移量（相对文件开头），也就是从哪里开始插入
* @param len 要插入的内容长度
* @return 成功返回0失败返回-1
**/
int finsert(FILE *fp, long offset, void *buffer, int len){
	long fileSize = fsize(fp);
	FILE *fpTemp; //临时文件
	
	if(offset>fileSize || offset<0 || len<0){ //插入错误
		return -1;
	}
	
	if(offset == fileSize)
	{ //在文件末尾插入
		fseek(fp, offset, SEEK_SET);
		if(!fwrite(buffer, len, 1, fp)){
			return -1;
		}
	}
	
	if(offset < fileSize)
	{ //从开头或者中间位置插入
		fpTemp = tmpfile();
		fcopy(fp, 0, offset, fpTemp, 0);
		fwrite(buffer, len, 1, fpTemp);
		fcopy(fp, offset, -1, fpTemp, offset+len);
		freopen(FILENAME, "wb+",fp);
		fcopy(fpTemp, 0, -1, fp, 0);
		fclose(fpTemp);
	}
	
	return 0;
}

int fdelete(FILE *fp, long offset, int len){
	long fileSize = getFileSize(fp);
	FILE *fpTemp;
	
	if(offset>fileSize || offset<0 || len<0){ //错误
		return -1;
	}
	
	fpTemp = tmpfile();
	fcopy(fp, 0, offset, fpTemp, 0); //将前offset字节的数据复制到临时文件
	fcopy(fp, offset+len, -1, fpTemp, offset); //将offset+len之后的所有内容都复制到临时文件
	freopen(FILENAME, "wb+",fp); //重新打开文件
	fcopy(fpTemp, 0, -1, fp, 0);
	fclose(fpTemp);
	
	return 0;
}