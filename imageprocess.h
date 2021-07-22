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
#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

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
#include <time.h>


using namespace std;
using namespace cv;

enum adaptiveMethod{meanFilter,gaaussianFilter,medianFilter};

/**
 * @brief The ImageProcess class 用来对图像进行一些预处理，处理完成之后再进行图像识别
 * Mat转IplImage
 * 注意：浅拷贝 - 同样只是创建图像头，而没有复制数据
 *  Mat M;
 *  IplImage img = M;
 *  IplImage img = IplImage(M);
 * 深拷贝
 *  cv::Mat img2;
 *  IplImage imgTmp = img2;
 *  IplImage *input = cvCloneImage(&imgTmp);
 *
 * IplImage转Mat
 * 使用Mat的构造函数：Mat::Mat(const IplImage* img, bool copyData=false);
 * 默认情况下copyData为false
 * IplImage* srcImg = cvLoadImage("Lena.jpg");
 * 注意：以下三种效果一致，均为浅拷贝
 *  Mat M(srcImg);
 *  Mat M(srcImg, false);
 *  Mat M = srcImg;
 *  注意：当将参数copyData设为true后，则为深拷贝（复制整个图像数据）
 *  Mat M(srcImg, true);
 * 深拷贝
 *  Mat inputImage = cvarrToMat(pTemp);
 */
class ImageProcess
{
public:
    ImageProcess();

    void setPath(QString &path);

    /**
     * @brief mainProcess 图像处理入口
     * @param imagePath 图像路径
     * @return false：处理失败  true：处理成功
     */
    bool mainProcess(QString &imagePath);

    /**
     * @brief ThresholdImage 局部二值化
     * 原理：图像分割成100张小图分别进行自适应二值化，然后将100张图片重组为一张
     * @param path
     * @param fileTarget
     */
    void ThresholdImage(QString path, QString fileTarget);


    /**
     * @brief ThinImage1 细化方法一
     * @param path
     * @param fileTarget
     */
    void ThinImage1(const QString &path,const QString &fileTarget);


    /**
     * @brief ThinImage2 细化方法二
     * @param path
     * @param fileTarget
     */
    void ThinImage2(const QString &path,const QString &fileTarget);

    /**
     * @brief ThinImage3 细化方法三
     * @param path 原图片路径
     * @param fileTarget 保存的位置
     */
    void ThinImage3(const QString &path,const QString &fileTarget);

    /**
     * @brief DilationImage1
     * @param path
     * @param fileTarget
     */
    void DilationImage1(const QString &path,const QString &fileTarget);

    /**
     * @brief ErosionImage1
     * @param path
     * @param fileTarget
     */
    void ErosionImage1(const QString &path,const QString &fileTarget);

//    bool mainProcessImage(QString &imagePath);

private:

    void AdaptiveThreshold(cv::Mat& src, cv::Mat& dst, double Maxval, int Subsize, double c, adaptiveMethod method = meanFilter);


    void AdaptiveThereshold(Mat &src,Mat &dst);

    /*************************图像细化*************************/
    /**
     * @brief thinImage  图像细化 方法一
     * @param srcImage
     * @param dstImage_out
     */
    bool thinImage(IplImage *srcImage,IplImage *dstImage_out);

    /**
     * @brief 对输入图像进行细化  方法二
     * @param src为输入图像,用cvThreshold函数处理过的8位灰度图像格式，元素中只有0与1,1代表有元素，0代表为空白
     * @param maxIterations限制迭代次数，如果不进行限制，默认为-1，代表不限制迭代次数，直到获得最终结果
     * @return 为对src细化后的输出图像,格式与src格式相同，元素中只有0与1,1代表有元素，0代表为空白
     */
    cv::Mat ThinImage2_sub(const cv::Mat & src, const int maxIterations = -1);

    /**
     * @brief ThinImage3  图像细化处理 方法三 （ThinImage、ThinSubiteration1、ThinSubiteration2）
     * @param inputImage
     * @return
     */
    void ThinImage3_sub1(Mat & pSrc, Mat & pDst);
    void ThinImage3_sub2(Mat & pSrc, Mat & pDst);

    /**
     * @brief gThin 图像细化方法四
     * @param src
     * @param dst
     * @param intera
     */
    void ThinImage1_sub(cv::Mat& src, cv::Mat& dst, int intera);/*这里传入参数，分别为两个*/
    /********************************************************/

    /*************************图像扩展膨胀*************************/
    /**
     * @brief dilateImage  图像扩展
     * @param srcImage
     */
    bool dilateImage(IplImage *srcImage);

    //膨胀
    void DilationImage1_sub1(Mat &src,Mat &dst_diolate,int dilation_size);
    //腐蚀
    void ErosionImage1_sub1(Mat &src,Mat &dst_erosion,int erosion_size);

    /********************************************************/

    /*************************图像分割*************************/
    vector<Mat> cutPics( IplImage *img);
    /********************************************************/



    /**
     * @brief QImageToIplImage QImage转换成IplImage
     * @param qImage
     * @return
     */
    IplImage *QImageToIplImage(const QImage * qImage);

    /**
     * @brief IplImageToQImage  IplImage转换成QImage
     * @param img
     * @return
     */
    QImage *IplImageToQImage( IplImage *img);


    void merageImages(vector<Mat> images,Mat &dst,int cut_rows,int cut_cols);
    //传入一个整数获取对应的opencv中的图像类型
    QString getImgType(int imgTypeInt);


    QString m_path;




};

#endif // IMAGEPROCESS_H
