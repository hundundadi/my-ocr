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
static QString projectPath = "/media/wangcong/workspace/wangcong/workspace/qt_workspace/project/test/my-ocr";



void writeFile(QString  inputStr,QString filePath)
{

    ofstream fout;
    qDebug() << "filePath.toLocal8Bit().data() : " << filePath.toLocal8Bit().data() ;

    fout.open(filePath.toLocal8Bit().data() );
    fout <<  inputStr.toLocal8Bit().data() ;
    fout << flush;
    fout.close();
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

//    QString langPath = "/data/home/wangcong/wangcong/workspace/qt_workspace/SourceCode/tessdata_best";
//    //QString langPath = "/usr/share/deepin-ocr/tesslangs";
//    QList<Languages> langs;
//    langs.append(Languages::CHI_SIM);
//    TessOcrUtils::instance()->setLanguages(langs);
//    TessOcrUtils::instance()->setLanguagesPath(langPath);
    QString filePath = projectPath+"/Resource/HybridLanguage";
    QString srcPath = filePath + "/picture3-42.png";
    //QString srcPaht = filePath + "/ChiSim_ChiTra_Eng.png";
    ImageProcess *imageProcess = new ImageProcess ();
    imageProcess->CutPics(srcPath,filePath);
    imageProcess->setPath(filePath);
    srcPath = filePath + "/test.png";
    qDebug() << "srcPath: " << srcPath;
    //imageProcess->ThinImage(srcPath,filePath); //细化效果不行
    imageProcess->ThinImage1(srcPath,filePath);
    imageProcess->ThinImage2(srcPath,filePath);
    srcPath = filePath + "/ThinImage1.png";
    imageProcess->DilationImage1(srcPath,filePath);
    srcPath = filePath + "/ThinImage2.png";
    imageProcess->mainProcess(srcPath);

//    RecognitionResult t_Result = TessOcrUtils::instance()->getRecogitionResult(filePath + "/Sharp_pic2.jpg");
//    RecognitionResult t_Result = TessOcrUtils::instance()->getRecogitionResult(filePath + "/thin_result.png");

//    qDebug() << "t_Result.flag: " << t_Result.flag;
//    qDebug() << "t_Result.errorCode: " << t_Result.errorCode;
//    qDebug() << "t_Result.message: " << t_Result.message;
//    qDebug() << "t_Result.resultType: " << t_Result.resultType;
//    qDebug() << "t_Result.result: \n" << t_Result.result;
//    writeFile(t_Result.result,filePath+"/Result_Optimizing/ChiSim_ChiTra_Eng.txt");
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
