#define _CRT_SECURE_NO_WARNINGS
#include "FileFunction.h"
#include "unistd.h"
#include "dirent.h"
#include <stdlib.h>
#include <atlstr.h>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <tchar.h>
#include <psapi.h>
#include <typeinfo>
#include <iostream>
#include <vector>
#include <random>
#include <iostream>
#include <io.h>
#include <direct.h>
#include <fstream>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


using namespace std;



/*
	文件拷贝
*/
void CopyFiles(char* SourceFile, char* NewFile)
{
	ifstream in;
	ofstream out;
	in.open(SourceFile, ios::binary);//打开源文件
	if (in.fail())//打开源文件失败
	{
		cout << "Error 1: Fail to open the source file." << endl;
		in.close();
		out.close();
	}
	out.open(NewFile, ios::binary);//创建目标文件 
	if (out.fail())//创建文件失败
	{
		cout << "Error 2: Fail to create the new file." << endl;
		out.close();
		in.close();
	}
	else//复制文件
	{
		out << in.rdbuf();
		out.close();
		in.close();
	}
}
/*
	遍历当前文件夹下的文件
*/
void GetFileNames(string path, vector<string>& files)
{
	//文件句柄
	intptr_t hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do {
			//把文件绝对路径存入vector中
			files.push_back(p.assign(path).append("\\").append(fileinfo.name));
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}


/*
	创建文件夹
*/
void CreateFolder(std::string folderPath)
{
	//文件夹名称
	//char folderName[] = folderPath;

	// 文件夹不存在则创建文件夹
	if (_access(folderPath.data(), 0) == -1)
	{
		_mkdir(folderPath.data());
	}
}
/*
	创建随机文件名
*/
std::string GetRandomFileName(int sz) //sz: 字符串的长度
{
	static constexpr char CCH[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string ret;

	ret.resize(sz);
	std::mt19937 rng(std::random_device{}());
	for (int i = 0; i < sz; ++i)
	{
		uint32_t x = rng() % (sizeof(CCH) - 1);
		ret[i] = CCH[x];
	}
	return ret;
}
/*
	获取当前进程所在文件夹
*/
std::string GetExeFilePath() {
	string::size_type pos;
	CHAR lp[MAX_PATH];
	GetModuleFileNameA(NULL, lp, MAX_PATH); /*C:\Users\zcy\Desktop\ctest\ConsoleApplication1\x64\Release\*/
	std::string path = lp;
	pos = path.rfind("\\");
	return path.substr(0, pos + 1);
}


/*
	判断是否为目录
*/
BOOL IsDirectory(const char* pDir)
{
	char szCurPath[500];
	ZeroMemory(szCurPath, 500);
	sprintf_s(szCurPath, 500, "%s//*", pDir);
	WIN32_FIND_DATAA FindFileData;
	ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATAA));

	HANDLE hFile = FindFirstFileA(szCurPath, &FindFileData); /**< find first file by given path. */

	if (hFile == INVALID_HANDLE_VALUE)
	{
		FindClose(hFile);
		return FALSE; /** 如果不能找到第一个文件，那么没有目录 */
	}
	else
	{
		FindClose(hFile);
		return TRUE;
	}

}


/*
	删除文件夹
*/
BOOL DeleteDirectory(const char* DirName)
{
	//    CFileFind tempFind;        //声明一个CFileFind类变量，以用来搜索
	char szCurPath[MAX_PATH];        //用于定义搜索格式
	_snprintf(szCurPath, MAX_PATH, "%s//*.*", DirName);    //匹配格式为*.*,即该目录下的所有文件
	WIN32_FIND_DATAA FindFileData;
	ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATAA));
	HANDLE hFile = FindFirstFileA(szCurPath, &FindFileData);
	BOOL IsFinded = TRUE;
	while (IsFinded)
	{
		IsFinded = FindNextFileA(hFile, &FindFileData);    //递归搜索其他的文件
		if (strcmp(FindFileData.cFileName, ".") && strcmp(FindFileData.cFileName, "..")) //如果不是"." ".."目录
		{
			std::string strFileName = "";
			strFileName = strFileName + DirName + "//" + FindFileData.cFileName;
			std::string strTemp;
			strTemp = strFileName;
			if (IsDirectory(strFileName.c_str())) //如果是目录，则递归地调用
			{
				//printf("目录为:%s/n", strFileName.c_str());
				DeleteDirectory(strTemp.c_str());
			}
			else
			{
				DeleteFileA(strTemp.c_str());
			}
		}
	}
	FindClose(hFile);

	BOOL bRet = RemoveDirectoryA(DirName);
	if (bRet == 0) //删除目录
	{
		//printf("删除%s目录失败！/n", DirName);
		return FALSE;
	}
	return TRUE;
}

/*删除文件*/
int  DeleteFiles(const char* fileName)
{
	int flag = remove(fileName);
	return flag;
}

/*获取文件大小*/
int readFiles(const char* fileName)
{
	int g_filesize; //获取文件大小
	//打开文件
	FILE* read = fopen(fileName, "rb");
	if (!read) {
		perror("file open failed: \n");
		return false;

	}
	//获取文件大小
	fseek(read, 0, SEEK_END);
	g_filesize = ftell(read);
	fseek(read, 0, SEEK_SET);
	cout << "文件大小为: " << g_filesize << "B " << g_filesize/1024 << "KB\n";
	fclose(read);
	return g_filesize;
}

//获取文件大小的函数，返回值以KB为单位
long get_length(string filePath) {
	long sizeKB = 0;

	ifstream fin(filePath);
	if (fin.is_open())
	{
		fin.seekg(0, ios::end);
		long size = fin.tellg();
		if (size == 0) {
			sizeKB = 0;
		}
		else {
			sizeKB = size;
		}
		fin.close();
	}
	return sizeKB;
}


long getFileSize(string path)//递归核心代码
{
	//文件句柄
	intptr_t hFile = 0;
	vector<string> files;

	//文件信息
	struct _finddata_t fileinfo;
	string p;
	long filesize = 0;
	int i = 0;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{

			if ((fileinfo.attrib & _A_SUBDIR))//判断是否是文件夹 
			{
				//如果是目录,递归查找并累积size
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
					filesize += getFileSize(p.assign(path).append("\\").append(fileinfo.name));
				}

			}
			else
			{
				//如果不是，直接累加size
				filesize += get_length(path + "\\" + fileinfo.name);
			}


		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}

	return filesize;
}