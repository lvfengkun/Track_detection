/*****    cropTrack.cpp      ******/
/*****    lvfengkun      ******/
/*****   2019/8/7      ******/

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <io.h>      
#include <string>    
#include <vector>    
#include <iostream>    
#include <opencv2/photo.hpp>
#include "MainWindow.h"

#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include<qdebug.h>
#include "mainwindow.h"
using namespace std;
using namespace cv;
extern int checkTrack(QTextEdit *textEdit);
void getAllFilesT(string path, vector<string>& files, string format, vector<string>& names)  //获取文件句柄函数（就是读取图片）
{
	//文件句柄
	intptr_t  hFile = 0;  //intptr_t为 long int 的别名（64位计算机）
	//文件信息
	struct _finddata_t fileinfo; //很少用的文件信息读取结构，在io.h中，_finddata_t用于存储文件的各类信息，fileinfo为指向该信息的指针
	string p; // string类很有意思的一个赋值函数:assign()，有很多重载版本
	if ((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))  //比较文件类型是否为文件夹
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					// folders, do nothing
					/*files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					names.push_back(fileinfo.name);
					getAllFiles(p.assign(path).append("\\").append(fileinfo.name), files, format, names);*/
				}
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				names.push_back(fileinfo.name);
			}
		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则返回-1
		_findclose(hFile);
	}
}

int cropTrack(string cropPath, QTextEdit *textEdit)
{
	string format = "bmp";
	int threshold_value = 22;
	int threshold_type = 0;
	int const max_binary_value = 255;
	string cropedImgPath = "crop_temp";
	vector<string> cropFiles; //声明一个向量用于储存文件句柄
	vector<string> cropNames; //声明一个变量用于存储文件名
	getAllFilesT(cropPath, cropFiles, format, cropNames);  //获取所有bmp文件的给corpFiles
	int checkSize = cropFiles.size(); //文件的大小，也是文件的字节数，这里可视为该向量的长度
	int namesSize = cropNames.size();
	//cout << "check files are:" << endl;

	int cropX = 0;
	int cropY = 350;
	int cropHeight = 1024;
	int cropWidth = 322;
	//截取部分，用于二值化
	for (int i = 0; i < namesSize; i++)
	{
		//cout << cropNames[i].substr(0, cropNames[i].rfind(".")) << " m" << endl;//substr为截取字符串函数，rfind为查找并返回“.”字符在字符串中的位置
		Mat src = imread(cropFiles[i]);   //声明一个Mat类将cropFiles[i]中的信息复制一份
		if (src.empty()) //判断该Mat类是否为空
		{
			cout << "Could not open or find the image!\n" << endl;
			cout << cropFiles[i] << endl;
			return -1;
		}
		
		Mat ROI(src, Rect(cropY, cropX, cropWidth, cropHeight)); //对src加掩膜
		Mat cropedImg;
		ROI.copyTo(cropedImg);//将掩膜复制到corpedImg中
		/*imshow("origin", src);*/
		Mat src_grayT, dst;
		
		cvtColor(cropedImg.clone(), src_grayT, COLOR_BGR2GRAY); //对截取部分进行颜色空间转换
		
		threshold(src_grayT, dst, threshold_value, max_binary_value, threshold_type); //进行二值化操作，有反光，此处应进行修改
		
		string savePath = cropedImgPath + "\\" + cropNames[i]; //赋予新的路径
		
		
		imwrite(savePath,dst); //写入目标文件夹
	}
	checkTrack(textEdit);
	//system("pause");
	return 0;
}

