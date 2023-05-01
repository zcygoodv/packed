# packed

## 免责声明

涉及到的所有技术仅用来学习交流，严禁用于非法用途。否则产生的一切后果自行承担。

## 介绍

可打包指定目录下的文件及文件夹，目录下的文件夹会打包为zip各式。并通过socket上传至服务端。

**(1)参数**

packed.exe -h

``` 
SYNOPSIS
        .\packed.exe [-sp <SourcePath>] [-fs <FileSize>] [-fn <FileName>] [-flt <FileLessThan>]
                     [-fgt <FileGreaterThan>] [-dlt <DirLessThan>] [-alt <AllLessThan>]
```

**(2)参数说明**

```
"-sp", "-SP", "--SourcePath"
指定打包目录

"-fs", "-FS", "--FileSize"
只查看文件大小，不进行打包，默认为off，开启需指定为on

"-fn", "-FS", "--FileSize"
指定文件或文件夹名称,如有多个用逗号隔开。比如："1.txt,1234"

"-flt", "-FLT", "--FileLessThan"
筛选小于自定义大小的文件，单位KB

-fgt", "-FGT", "--FileGreaterThan"
筛选大于自定义大小的文件，单位KB

"-dlt", "-DLT", "--DirLessThan"
筛选大于自定义大小的文件夹，单位KB

"-alt", "-ALT", "--AllLessThan"
筛选大于自定义大小的文件和文件夹，单位KB
```

**(3)用法**

1、查看C:\Users\Administrator\Desktop目录下的所有文件(文件夹)名称及大小，不进行打包。

```
packed.exe -sp "C:\Users\Administrator\Desktop" -fs "on"
```

2、打包C:\Users\Administrator\Desktop目录下的文件及文件夹(默认打包条件：文件小于10M,文件夹小于40M)。

```
packed.exe -sp "C:\Users\Administrator\Desktop"
```

3、打包C:\Users\Administrator\Desktop目录下，小于5KB(单位KB)的所有文件。

```
packed.exe -sp "C:\Users\Administrator\Desktop" -flt 5
```

4、打包C:\Users\Administrator\Desktop目录下，大于10M(单位KB)的所有文件。

```
packed.exe -sp "C:\Users\Administrator\Desktop" -fgt 10240
```

5、打包C:\Users\Administrator\Desktop目录下，大于5KB(单位KB)且小于50KB(单位KB)的所有文件。

```
packed.exe -sp "C:\Users\Administrator\Desktop" -fgt 5 -flt 50
```

6、打包C:\Users\Administrator\Desktop目录下，小于60M(单位KB)的文件夹。

```
packed.exe -sp "C:\Users\Administrator\Desktop" -dlt 61440
```

7、打包C:\Users\Administrator\Desktop目录下，小于60M(单位KB)的文件和文件夹。

```
packed.exe -sp "C:\Users\Administrator\Desktop" -alt 61440
```

8、打包C:\Users\Administrator\Desktop目录下，文件名为1.txt的文件

```
packed.exe -sp "C:\Users\Administrator\Desktop" -fn "1.txt"
```

9、打包C:\Users\Administrator\Desktop目录下，文件名为1.txt的文件和名称为1234的目录

```
packed.exe -sp "C:\Users\Administrator\Desktop" -fn "1.txt,1234"
```

## 参考

客户端ip修改：https://blog.csdn.net/challenglistic/article/details/128242047

服务端代码逻辑：https://blog.csdn.net/qigaohua/article/details/102794593

服务端搭建：https://blog.csdn.net/explore_world/article/details/88551349
