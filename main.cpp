/*

* Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.

*

* Author:     wangcong <wangcong@uniontech.com>

*

* Maintainer: wangcong <wangcong@uniontech.com>

*

* This program is free software: you can redistribute it and/or modify

* it under the terms of the GNU General Public License as published by

* the Free Software Foundation, either version 3 of the License, or

* any later version.

*

* This program is distributed in the hope that it will be useful,

* but WITHOUT ANY WARRANTY; without even the implied warranty of

* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the

* GNU General Public License for more details.

*

* You should have received a copy of the GNU General Public License

* along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include <QCoreApplication>
#include <tessocrutils.h>
#include <QLocale>
#include <fstream>
#include "imageprocess.h"

using namespace std;
/**
 * @brief 当前项目的路径
 */
static QString projectPath = "/media/wangcong/workspace/wangcong/workspace/qt_workspace/project/my-ocr";





void writeFile(QString  inputStr,QString filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
    {
        qDebug() << "can't open " << filePath ;
    }
    QTextStream stream(&file);
    stream<<inputStr<<"\n";
    file.close();
}

void testOcrUtilsImage(){
//    QString langPath = "/data/home/wangcong/wangcong/workspace/qt_workspace/SourceCode/tessdata_best";
//    //QString langPath = "/usr/share/deepin-ocr/tesslangs";
//    QList<Languages> langs;
//    langs.append(Languages::CHI_SIM);
//    langs.append(Languages::ENG);
//    TessOcrUtils::instance()->setLanguages(langs);
//    TessOcrUtils::instance()->setLanguagesPath(langPath);
    QString filePath = projectPath+"/Resource/HybridLanguage";
    QImage* t_image = new QImage(filePath + "/ChiSim_ChiTra_Eng.png");
    RecognitionResult t_Result = TessOcrUtils::instance()->getRecogitionResult(t_image);
    qDebug() << "t_Result.flag: " << t_Result.flag;
    qDebug() << "t_Result.errorCode: " << t_Result.errorCode;
    qDebug() << "t_Result.message: " << t_Result.message;
    qDebug() << "t_Result.resultType: " << t_Result.resultType;
    qDebug() << "t_Result.result: \n" << t_Result.result;
    writeFile(t_Result.result,filePath+"/Result_Optimizing/ChiSim_ChiTra_Eng.txt");

    //delete t_image;
}

void testOcrUtilsImagePath(){
    //配置识别的语言库
//    QString langPath = "/data/home/wangcong/wangcong/workspace/qt_workspace/SourceCode/tessdata_best";
//    //QString langPath = "/usr/share/deepin-ocr/tesslangs";
//    QList<Languages> langs;
//    langs.append(Languages::CHI_SIM);
//    TessOcrUtils::instance()->setLanguages(langs);
//    TessOcrUtils::instance()->setLanguagesPath(langPath);
    QString filePath1 = projectPath+"/Resource/HybridLanguage";
    QString srcPath = filePath1 + "/picture2.png";
    //QString srcPath = filePath + "/ChiSim_ChiTra_Eng.png";
     QString filePath = filePath1 + "/temp";
    //图像预处理
    ImageProcess *imageProcess = new ImageProcess ();
    //局部二值化
    QString thresholdImagepath = filePath + "/ThresholdImage.png";
    imageProcess->ThresholdImage(srcPath,thresholdImagepath);
    //细化方法一
    QString thinImage1path = filePath + "/ThinImage1.png";
    imageProcess->ThinImage1(thresholdImagepath,thinImage1path);
    //细化方法二
    QString thinImage2path = filePath + "/ThinImage2.png";
    imageProcess->ThinImage2(thresholdImagepath,thinImage2path);
    //细化方法三 此方法细化效果不理想
    //QString thinImage3path = filePath + "/ThinImage2.png";
    //imageProcess->ThinImage3(thresholdImagepath,thinImage3path);
    //膨胀
    QString dilationImage1path = filePath + "/DilationImage1.png";
    imageProcess->DilationImage1(thinImage2path,dilationImage1path);
    //二次处理
    imageProcess->setPath(filePath);
    imageProcess->mainProcess(srcPath);

    clock_t start,finish;
    double totaltime;
    //开始时间
    start=clock();
    //开始识别
    qDebug()<<"开始识别: "<< start;
    RecognitionResult t_Result = TessOcrUtils::instance()->getRecogitionResult(thresholdImagepath);
    finish=clock();
    qDebug()<<"识别结束: "<< finish;
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    qDebug()<<"OCR Total time:"<<totaltime;
    writeFile(t_Result.result,filePath1+"/Result_Optimizing/p2_result.txt");

//    //开始时间
//    start=clock();
//    //开始识别
//    qDebug()<<"开始识别: "<< start;
//    t_Result = TessOcrUtils::instance()->getRecogitionResult(thresholdImagepath);
//    finish=clock();
//    qDebug()<<"识别结束: "<< finish;
//    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
//    qDebug()<<"OCR Total time:"<<totaltime;
//    writeFile(t_Result.result,filePath+"/Result_Optimizing/thresholdImage_result.txt");

//    //开始时间
//    start=clock();
//    //开始识别
//    qDebug()<<"开始识别: "<< start;
//    t_Result = TessOcrUtils::instance()->getRecogitionResult(thinImage1path);
//    finish=clock();
//    qDebug()<<"识别结束: "<< finish;
//    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
//    qDebug()<<"OCR Total time:"<<totaltime;
//    writeFile(t_Result.result,filePath+"/Result_Optimizing/thinImage1_result.txt");


//    //开始时间
//    start=clock();
//    //开始识别
//    qDebug()<<"开始识别: "<< start;
//    t_Result = TessOcrUtils::instance()->getRecogitionResult(thinImage2path);
//    finish=clock();
//    qDebug()<<"识别结束: "<< finish;
//    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
//    qDebug()<<"OCR Total time:"<<totaltime;
//    writeFile(t_Result.result,filePath+"/Result_Optimizing/thinImage2_result.txt");


//    //开始时间
//    start=clock();
//    //开始识别
//    qDebug()<<"开始识别: "<< start;
//    t_Result = TessOcrUtils::instance()->getRecogitionResult(dilationImage1path);
//    finish=clock();
//    qDebug()<<"识别结束: "<< finish;
//    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
//    qDebug()<<"OCR Total time:"<<totaltime;
//    writeFile(t_Result.result,filePath+"/Result_Optimizing/dilationImage1_result.txt");


//    qDebug() << "t_Result.flag: " << t_Result.flag;
//    qDebug() << "t_Result.errorCode: " << t_Result.errorCode;
//    qDebug() << "t_Result.message: " << t_Result.message;
//    qDebug() << "t_Result.resultType: " << t_Result.resultType;
//    qDebug() << "t_Result.result: \n" << t_Result.result;
}


int main(int argc, char *argv[])
{
//    QLocale locale;
//    qDebug() << "QLocale::languageToString(): " <<QLocale::languageToString(locale.language());
//    qDebug() << "QLocale::countryToString(): " <<QLocale::countryToString(locale.country());
    //QLocale::languageToString():  "Chinese"
    //QLocale::countryToString():  "China"
    //QLocale::languageToString():  "English"
    //QLocale::countryToString():  "UnitedStates"


    QCoreApplication a(argc, argv);

    for (int i = 0;i < 1;i++)
    {
        qDebug() << "OCR output: " << i;
        testOcrUtilsImagePath();
        //testOcrUtilsImage();
    }
    //testOcrUtilsImage();
    //return a.exec();
    return 0;
}
