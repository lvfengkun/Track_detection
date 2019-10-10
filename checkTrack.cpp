/*****    checkTrack.cpp      ******/
/*****    lvfengkun      ******/
/*****   2019/8/7      ******/

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <io.h>      
#include <string>    
#include <vector>    
#include <iostream>
#include "MainWindow.h"
#include <QString>
#include "MainWindow.h"
#include<fstream>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QtWidgets>
#include "mainwindow.h"
#include <QString>
#include <vector>
#include <iostream>
#include <string>
using namespace std;
using namespace cv;
//extern void display(QString qstr);
   
void getAllFilesAndFolders(string path, vector<string>& files, string format, vector<string>& names)
{
	intptr_t  hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) != -1) 
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name)); 
					names.push_back(fileinfo.name);
					getAllFilesAndFolders(p.assign(path).append("\\").append(fileinfo.name), files, format, names);
				}
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				names.push_back(fileinfo.name);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

void getAllFiles(string path, vector<string>& files, string format, vector<string>& names)
{
	intptr_t  hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
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
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

RNG rng(12345);

int checkTrack(QTextEdit *textEdit)
{
	ofstream file("cpp - home.txt");
	int n = 0;
	string format = "bmp";

	string checkPath = "crop_temp";
	string checkImgPath = "crop_temp_1";
	vector<string> checkFiles;
	vector<string> checkNames;
	getAllFiles(checkPath, checkFiles, format, checkNames); //读取图片给checkFiles
	int checkSize = checkFiles.size();
	int namesSize = checkNames.size();
	//cout << "check files are:" << endl;
	for (int i = 0; i < namesSize; i++)
	{
		string str;
		str= checkNames[i].substr(0, checkNames[i].rfind(".")) + " m" ;
		Mat src_gray;
		int thresh = 255; //阈值
		Mat src = imread(checkFiles[i]);//复制图片给src
		if (src.empty())//判断src是否为空
		{
			str= "Could not open or find the image!\n"  ;
			str=str+ checkFiles[i] ;
			return -1;
		}
		cvtColor(src, src_gray, COLOR_BGR2GRAY);//二值化
		blur(src_gray, src_gray, Size(3, 3)); //均值化
		Mat canny_output;
		Canny(src_gray, canny_output, thresh, thresh * 2);  //进行边缘处理，且canny_output为输出结果

		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE); //进行轮廓提取，检测所有轮廓并仅保存轮廓的拐点信息

		bool badTrack = false;
		for (size_t j = 0; j< contours.size(); j++)
		{
			/*double cArea = contourArea(contours[j]);
			if (cArea > 50)
				cout << cArea << endl;*/
			double cArea = contourArea(contours[j]);  //进行轮廓面积检测
			if (cArea < 100)
				continue;
			badTrack = true;
		}

		if (badTrack)
		{
			string savePath = checkImgPath + "\\" + checkNames[i];
			str=str+ "track has defects!" ;
			imwrite(savePath, canny_output);
			n++;
		}
		else
		{
			str = str + "track is good!";
		}
		file << str << endl;
	}
	cout<<n << endl;

	//system("pause");
	return 0;
}
