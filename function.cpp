#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include<CL/cl.h>
#endif

//#ifdef __unix
//#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen(filename,mode))==NULL
//#endif

void judgeStatus(int status, const char *filename)
{
	switch (status)
	{
	case 0:
		printf("Success to open the file %s\n", filename);
		break;
	case ENOENT:
		printf("Open %s error!!!   --- No such file or directory.\n", filename);
		system("pause");
		exit(0);
	case EINVAL:
		printf("Open %s error!!!   --- The argument(s) is/are invalid.\n", filename);
		system("pause");
		exit(0);
	case EFBIG:
		printf("Open %s error!!!   --- The file %s is too large.\n", filename, filename);
		system("pause");
		exit(0);
	case ENOMEM:
		printf("Open %s error!!!   --- Not enough memory.\n", filename);
		system("pause");
		exit(0);
	case EACCES:
		printf("Open %s error!!!   --- The permission of %s denied.\n", filename, filename);
		system("pause");
		exit(0);
	case ENAMETOOLONG:
		printf("Open %s error!!!   --- The filename of %s is too long.\n", filename, filename);
		system("pause");
		exit(0);
	default:
		printf("Open %s error!!!\n", filename);
		system("pause");
		exit(0);
	}
}

char * loadSource(char *sourceName, size_t &fileSize)
{
	FILE *source;
//	int openStatus;
//    openStatus = fopen_s(&source, sourceName, "r");
//	judgeStatus(openStatus, sourceName);
	source = fopen(sourceName,"r");
    if(source == NULL){
    	printf("source is null");
    }
	fseek(source, 0, SEEK_END);
	fileSize = ftell(source);
	fseek(source, 0, SEEK_SET);
	char *sourcePointer = (char *)malloc(fileSize * sizeof(char));
	memset(sourcePointer, 0, fileSize * sizeof(char));
	fread(sourcePointer, fileSize, sizeof(char), source);

	return sourcePointer;
}
