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
#ifndef TESSOCRUTILS_H
#define TESSOCRUTILS_H
//本项目的文件
#include "3rdparty/tesseract_ocr/tesseract/include/tesseract/baseapi.h"

//dtk的类

//qt的类
#include <QDebug>
#include <QException>
#include <QFileInfo>
#include <QImage>
#include <QLocale>
//其他库
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>

/**
 * @brief 返回结果字符串的类型
 */
enum ResultType{
    ResultString = 1,      //纯字符串结果
    ResultHTML = 2,        //HTML文本
    ResultXML = 3          //XML文本
};

/**
 * @brief 返回识别过程中的错误码
 */
enum ErrorCode{
    OK = 1,                //成功
    UKNOW = -1,            //未知错误
    OCRPNULL = 101,        //文件路径为空
    OCRRTNULL = 102,       //结果字符串类型不存在
    OCRINIF = 103,         //ocr三方库初始化失败
    OCRLIF = 104,          //OCR加载图片失败
    OCRRIF = 105           //OCR识别图片失败
};

/**
 * @brief 现今支持的语言包类型
 */
enum Languages{
    CHI_SIM=1,      //简体中文
    CHI_TRA=2,      //繁体中文
    ENG=3           //英文
};

/**
 * @brief ocr识别的返回结果
 */
struct RecognitionResult{

    /**
     * @brief 识别是否成功
     */
    bool flag;

    /**
     * @brief 识别返回的消息，如果识别失败发生的错误通过此字段返回
     */
    QString message;

    /**
     * @brief 返回的错误码
     */
    ErrorCode errorCode;

    /**
     * @brief 返回字符串结果的类型
     */
    ResultType resultType;

    /**
     * @brief 返回的字符串结果
     */
    QString result;

    RecognitionResult(){
        flag = false;
        message.clear();
        errorCode = ErrorCode::UKNOW;
        resultType = ResultType::ResultString;
        result.clear();
    }
};

/**
 * @brief ocr接口工具
 */
class TessOcrUtils
{
public:
    TessOcrUtils();
    ~TessOcrUtils();

    static TessOcrUtils *instance();

    /**
     * @brief 传入待识别图片的路径和想得到的返回结果类型，获取识别结果
     * @param 图片路径
     * @param 返回的字符串结果类型
     * @return resultType类型的字符串结果
     */
     RecognitionResult getRecogitionResult(const QString imagePath,const ResultType resultType);

    /**
     * @brief 传入待识别图片的路径，获取纯字符串的识别结果
     * @param 图片路径
     * @return 识别的字符串结果
     */
     RecognitionResult getRecogitionResult(const QString imagePath);

    /**
     * @brief 传入待识别图片和想得到的返回结果类型，获取识别结果
     * @param 图片路径
     * @param 返回的字符串结果类型
     * @return resultType类型的字符串结果
     */
     RecognitionResult getRecogitionResult(QImage *image,const ResultType resultType);

    /**
     * @brief 传入待识别图片，获取纯字符串的识别结果
     * @param 图片路径
     * @return 识别的字符串结果
     */
     RecognitionResult getRecogitionResult(QImage *image);

private :

     /**
      * @brief 设置当前使用的语言包路径
      * @param 语言包路径
      * @return
      */
      bool setLanguagesPath(const QString langsPath);

    /**
     * @brief 判断指定的结果类型是否存在
     * @param 指定的类型
     * @return 存在返回true
     */
     bool isExistsResultType(ResultType resultType);

    /**
     * @brief 判断指定的语言包类型是否存在
     * @param 指定的类型
     * @return 存在返回true
     */
     bool isExistsLanguage(Languages lang);

     /**
      * @brief 获取当前使用的语言包
      * @param 需要使用的语言包
      * @return
      */
     QString getLanguages();

    /**
     * @brief 根据传入的枚举，获取相应的语言包字符串
     * @param 语言包的枚举
     * @return 语言包的字符串
     */
     QString getLangStr(Languages lang);

    /**
     * @brief 获取纯字符串的识别结果
     * @param 需识别的图片
     * @param 返回的字符串结果类型
     * @return 返回识别结果
     */
     RecognitionResult getRecogitionResult(Pix * image,ResultType resultType);

    /**
     * @brief 设置返回结果,内部使用
     * @param 错误码
     * @param 错误消息
     * @param 结果类型
     */
     void setResult(ErrorCode errCode, const QString errMessage,const ResultType resultType,RecognitionResult &result);


     /**
      * @brief 获取系统当前的语言
      * @return
      */
     Languages getSystemLang();

     /**
      * @brief 语言包路径m_image
      */
      QString m_sTessdataPath;

     /**
      * @brief 语言包
      */
     QString m_sLangs;

     //static tesseract::TessBaseAPI *t_Tesseract;

     static TessOcrUtils *m_tessOcrUtils;

};

#endif // TESSOCRUTILS_H
