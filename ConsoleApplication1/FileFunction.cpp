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
	�ļ�����
*/
void CopyFiles(char* SourceFile, char* NewFile)
{
	ifstream in;
	ofstream out;
	in.open(SourceFile, ios::binary);//��Դ�ļ�
	if (in.fail())//��Դ�ļ�ʧ��
	{
		cout << "Error 1: Fail to open the source file." << endl;
		in.close();
		out.close();
	}
	out.open(NewFile, ios::binary);//����Ŀ���ļ� 
	if (out.fail())//�����ļ�ʧ��
	{
		cout << "Error 2: Fail to create the new file." << endl;
		out.close();
		in.close();
	}
	else//�����ļ�
	{
		out << in.rdbuf();
		out.close();
		in.close();
	}
}
/*
	������ǰ�ļ����µ��ļ�
*/
void GetFileNames(string path, vector<string>& files)
{
	//�ļ����
	intptr_t hFile = 0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do {
			//���ļ�����·������vector��
			files.push_back(p.assign(path).append("\\").append(fileinfo.name));
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}


/*
	�����ļ���
*/
void CreateFolder(std::string folderPath)
{
	//�ļ�������
	//char folderName[] = folderPath;

	// �ļ��в������򴴽��ļ���
	if (_access(folderPath.data(), 0) == -1)
	{
		_mkdir(folderPath.data());
	}
}
/*
	��������ļ���
*/
std::string GetRandomFileName(int sz) //sz: �ַ����ĳ���
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
	��ȡ��ǰ���������ļ���
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
	�ж��Ƿ�ΪĿ¼
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
		return FALSE; /** ��������ҵ���һ���ļ�����ôû��Ŀ¼ */
	}
	else
	{
		FindClose(hFile);
		return TRUE;
	}

}


/*
	ɾ���ļ���
*/
BOOL DeleteDirectory(const char* DirName)
{
	//    CFileFind tempFind;        //����һ��CFileFind�����������������
	char szCurPath[MAX_PATH];        //���ڶ���������ʽ
	_snprintf(szCurPath, MAX_PATH, "%s//*.*", DirName);    //ƥ���ʽΪ*.*,����Ŀ¼�µ������ļ�
	WIN32_FIND_DATAA FindFileData;
	ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATAA));
	HANDLE hFile = FindFirstFileA(szCurPath, &FindFileData);
	BOOL IsFinded = TRUE;
	while (IsFinded)
	{
		IsFinded = FindNextFileA(hFile, &FindFileData);    //�ݹ������������ļ�
		if (strcmp(FindFileData.cFileName, ".") && strcmp(FindFileData.cFileName, "..")) //�������"." ".."Ŀ¼
		{
			std::string strFileName = "";
			strFileName = strFileName + DirName + "//" + FindFileData.cFileName;
			std::string strTemp;
			strTemp = strFileName;
			if (IsDirectory(strFileName.c_str())) //�����Ŀ¼����ݹ�ص���
			{
				//printf("Ŀ¼Ϊ:%s/n", strFileName.c_str());
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
	if (bRet == 0) //ɾ��Ŀ¼
	{
		//printf("ɾ��%sĿ¼ʧ�ܣ�/n", DirName);
		return FALSE;
	}
	return TRUE;
}

/*ɾ���ļ�*/
int  DeleteFiles(const char* fileName)
{
	int flag = remove(fileName);
	return flag;
}

/*��ȡ�ļ���С*/
int readFiles(const char* fileName)
{
	int g_filesize; //��ȡ�ļ���С
	//���ļ�
	FILE* read = fopen(fileName, "rb");
	if (!read) {
		perror("file open failed: \n");
		return false;

	}
	//��ȡ�ļ���С
	fseek(read, 0, SEEK_END);
	g_filesize = ftell(read);
	fseek(read, 0, SEEK_SET);
	cout << "�ļ���СΪ: " << g_filesize << "B " << g_filesize/1024 << "KB\n";
	fclose(read);
	return g_filesize;
}

//��ȡ�ļ���С�ĺ���������ֵ��KBΪ��λ
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


long getFileSize(string path)//�ݹ���Ĵ���
{
	//�ļ����
	intptr_t hFile = 0;
	vector<string> files;

	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string p;
	long filesize = 0;
	int i = 0;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{

			if ((fileinfo.attrib & _A_SUBDIR))//�ж��Ƿ����ļ��� 
			{
				//�����Ŀ¼,�ݹ���Ҳ��ۻ�size
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
					filesize += getFileSize(p.assign(path).append("\\").append(fileinfo.name));
				}

			}
			else
			{
				//������ǣ�ֱ���ۼ�size
				filesize += get_length(path + "\\" + fileinfo.name);
			}


		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}

	return filesize;
}