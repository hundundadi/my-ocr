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
#include "imageprocess.h"

ImageProcess::ImageProcess()
{
    m_path = "";
}
void ImageProcess::setPath(QString &path)
{
    m_path = path;
}

bool ImageProcess::mainProcess(QString &imagePath)
{
    qDebug() << __func__ ;
    clock_t start,finish;
    double totaltime;
    //开始时间
    start=clock();
    //opencv加载图片
    qDebug() << "opencv 加载图片 ";

    IplImage *pSrc = cvLoadImage(imagePath.toLocal8Bit().data(),CV_LOAD_IMAGE_GRAYSCALE);
    if(!pSrc)
    {
        qDebug() << "opencv 加载图片 "<< imagePath<< " 失败";
        return false;
    }
    //临时图片
    IplImage *pTemp = cvCreateImage(cvGetSize(pSrc),pSrc->depth,pSrc->nChannels);
    //目标图片
    IplImage *pDst = cvCreateImage(cvGetSize(pSrc),pSrc->depth,pSrc->nChannels);
    //图片二值化
    qDebug() << "图片二值化 ";
    //中值滤波
    //medianBlur(cvarrToMat(pDst), cvarrToMat(pDst), 3);
    //cvSaveImage((m_path+"/medianBlur_result.png").toLocal8Bit().data(),pDst);

    cvThreshold(pSrc,pDst,245,255, THRESH_BINARY_INV);
//    cvThreshold(pSrc,pDst,1,255, THRESH_OTSU);
//    cvThreshold(pSrc,pDst,128,128, THRESH_BINARY);
    cvSaveImage((m_path+"/threshold_result.png").toLocal8Bit().data(),pDst);

    //双边带滤波
    //bilateralFilter(cvarrToMat(pDst), cvarrToMat(pDst),3,3,3);
    //cvSaveImage((m_path+"/bilateralFilter_result.png").toLocal8Bit().data(),pDst);
    //图像细化
    qDebug() << "图像细化 ";
//    IplImage imgTmp = IplImage(thinImage(cvarrToMat(pTemp)));
//    pDst = cvCloneImage(&imgTmp);
//    Mat inputImage = cvarrToMat(pTemp);
//    Mat outputImage;
//    thinImage(inputImage,outputImage);
//    //inputImage.convertTo(inputImage, CV_32FC1);
//    IplImage imgTmp = IplImage(outputImage);
//    pDst = cvCloneImage(&imgTmp);

    //thinImage(pTemp,pDst);
    for (int i=0; i<pDst->height; ++i)
    {
        for (int j=0; j<pDst->width; ++j)
        {
            if(i >= 0 && i <= 4)
                CV_IMAGE_ELEM(pDst,uchar,i,j) = 0;
            if(i >= 42 && i <= 45)
                CV_IMAGE_ELEM(pDst,uchar,i,j) = 0;
            if(CV_IMAGE_ELEM(pDst,uchar,i,j) == 1)
                CV_IMAGE_ELEM(pDst,uchar,i,j) = 255;
        }
    }
    cvSaveImage((m_path+"/thin_result.png").toLocal8Bit().data(),pDst);

    IplImage *d1=cvLoadImage((m_path+"/thin_result.png").toLocal8Bit().data(),0);
    //图像扩展
    qDebug() << "图像扩展 ";
    dilateImage(d1);

//    IplImage *ms=cvLoadImage((m_path+"/Img_dilate.jpg").toLocal8Bit().data(),0);
//    IplImage *pa = cvCreateImage(cvGetSize(ms),ms->depth,ms->nChannels);
//    IplImage *pb = cvCreateImage(cvGetSize(ms),ms->depth,ms->nChannels);

//    //图像二值化
//    qDebug() << "图片二值化 ";
//    cvThreshold(ms,pa,128,1,CV_THRESH_BINARY);
//    cvSaveImage((m_path+"/threshold_again.jpg").toLocal8Bit().data(),pTemp);
//    //图像细化
//    qDebug() << "图像细化 ";
//    thinImage(pa,pb);
//    for (int i=0; i<pb->height; ++i)
//    {
//        for (int j=0; j<pb->width; ++j)
//        {
//            if(CV_IMAGE_ELEM(pb,uchar,i,j)==1)
//                CV_IMAGE_ELEM(pb,uchar,i,j)= 255;
//        }
//    }
//    cvSaveImage((m_path+"/thin_again.jpg").toLocal8Bit().data(),pb);

//    IplImage *d2=cvLoadImage((m_path+"/thin_again.jpg").toLocal8Bit().data(),0);
//    qDebug() << "图像扩展 ";
//    dilateImage(d2);


    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;

    qDebug()<<"Total time:"<<totaltime<<endl;
    cvReleaseImage(&pSrc);
    cvReleaseImage(&pTemp);
    cvReleaseImage(&pDst);
//    cvReleaseImage(&d1);
//    cvReleaseImage(&ms);
//    cvReleaseImage(&pa);
//    cvReleaseImage(&pb);
//    cvReleaseImage(&d2);

    //cvWaitKey();

}


void ImageProcess::thresholdImage(IplImage *srcImage,IplImage *dstImage_out)
{

}

bool ImageProcess::thinImage(IplImage *srcImage, IplImage *dstImage_out)
{

    int maxIterations = -1;
    //获取图片大小
    CvSize size = cvGetSize(srcImage);
    //将src中的内容拷贝到dst中
    cvCopy(srcImage,dstImage_out);
    //记录迭代次数
    int count = 0;
    while (true)
    {
        count++;
        //限制次数并且迭代次数到达
        if(maxIterations != -1 && count > maxIterations) break;
        //用于标记需要删除的点
        vector<pair<int,int> > mFlag;
        //对点标记
        for (int i=0; i<size.height; ++i)
        {
            for (int j=0; j<size.width; ++j)
            {
                //如果满足四个条件，进行标记
                //  p9 p2 p3
                //  p8 p1 p4
                //  p7 p6 p5
                int p1 = CV_IMAGE_ELEM(dstImage_out,uchar,i,j);
                int p2 = (i == 0) ? 0 : CV_IMAGE_ELEM(dstImage_out,uchar,i-1,j);
                int p3 = (i == 0 || j == size.width - 1) ? 0 : CV_IMAGE_ELEM(dstImage_out,uchar,i-1,j+1);
                int p4 = (j == size.width - 1) ? 0 : CV_IMAGE_ELEM(dstImage_out,uchar,i,j+1);
                int p5 = (i == size.height - 1 || j == size.width - 1)?0:CV_IMAGE_ELEM(dstImage_out,uchar,i+1,j+1);
                int p6 = (i == size.height - 1) ? 0 : CV_IMAGE_ELEM(dstImage_out,uchar,i+1,j);
                int p7 = (i == size.height - 1 || j == 0) ? 0 : CV_IMAGE_ELEM(dstImage_out,uchar,i+1,j-1);
                int p8 = (j == 0) ? 0 : CV_IMAGE_ELEM(dstImage_out,uchar,i,j-1);
                int p9 = (i == 0 || j == 0) ? 0 : CV_IMAGE_ELEM(dstImage_out,uchar,i-1,j-1);

                if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9)<=6)
                {
                    int ap=0;
                    if (p2==0 && p3==1) ++ap;
                    if (p3==0 && p4==1) ++ap;
                    if (p4==0 && p5==1) ++ap;
                    if (p5==0 && p6==1) ++ap;
                    if (p6==0 && p7==1) ++ap;
                    if (p7==0 && p8==1) ++ap;
                    if (p8==0 && p9==1) ++ap;
                    if (p9==0 && p2==1) ++ap;

                    if (ap==1)
                    {
                        if (p2*p4*p6==0)
                        {
                            if (p4*p6*p8==0)
                            {
                                //标记
                                mFlag.push_back(make_pair(i,j));
                            }
                        }
                    }
                }
            }
        }

        //将标记的点删除
        for (vector<pair<int,int> >::iterator i=mFlag.begin(); i!=mFlag.end(); ++i)
        {
            CV_IMAGE_ELEM(dstImage_out,uchar,i->first,i->second) = 0;
        }

        //直到没有点满足，算法结束
        if (mFlag.size()==0)
        {
            break;
        }
        else
        {
            mFlag.clear();//将mFlag清空
        }

        //对点标记
        for (int i=0; i<size.height; ++i)
        {
            for (int j=0; j<size.width; ++j)
            {
                //如果满足四个条件，进行标记
                //  p9 p2 p3
                //  p8 p1 p4
                //  p7 p6 p5
                int p1 = CV_IMAGE_ELEM(dstImage_out,uchar,i,j);
                if(p1!=1) continue;
                int p2 = (i==0)?0:CV_IMAGE_ELEM(dstImage_out,uchar,i-1,j);
                int p3 = (i==0 || j==size.width-1)?0:CV_IMAGE_ELEM(dstImage_out,uchar,i-1,j+1);
                int p4 = (j==size.width-1)?0:CV_IMAGE_ELEM(dstImage_out,uchar,i,j+1);
                int p5 = (i==size.height-1 || j==size.width-1)?0:CV_IMAGE_ELEM(dstImage_out,uchar,i+1,j+1);
                int p6 = (i==size.height-1)?0:CV_IMAGE_ELEM(dstImage_out,uchar,i+1,j);
                int p7 = (i==size.height-1 || j==0)?0:CV_IMAGE_ELEM(dstImage_out,uchar,i+1,j-1);
                int p8 = (j==0)?0:CV_IMAGE_ELEM(dstImage_out,uchar,i,j-1);
                int p9 = (i==0 || j==0)?0:CV_IMAGE_ELEM(dstImage_out,uchar,i-1,j-1);

                if ((p2+p3+p4+p5+p6+p7+p8+p9)>=2 && (p2+p3+p4+p5+p6+p7+p8+p9)<=6)
                {
                    int ap=0;
                    if (p2==0 && p3==1) ++ap;
                    if (p3==0 && p4==1) ++ap;
                    if (p4==0 && p5==1) ++ap;
                    if (p5==0 && p6==1) ++ap;
                    if (p6==0 && p7==1) ++ap;
                    if (p7==0 && p8==1) ++ap;
                    if (p8==0 && p9==1) ++ap;
                    if (p9==0 && p2==1) ++ap;

                    if (ap==1)
                    {
                        if (p2*p4*p8==0)
                        {
                            if (p2*p6*p8==0)
                            {
                                //标记
                                mFlag.push_back(make_pair(i,j));
                            }
                        }
                    }
                }
            }
        }
        //删除
        for (vector<pair<int,int> >::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
        {
            CV_IMAGE_ELEM(dstImage_out,uchar,i->first,i->second) = 0;
        }

        //直到没有点满足，算法结束
        if (mFlag.size() == 0)
        {
            break;
        }
        else
        {
            mFlag.clear();//将mFlag清空
        }
    }
}

Mat ImageProcess::ThinImage2_sub(const Mat &src, const int maxIterations)
{
    assert(src.type() == CV_8UC1);
    cv::Mat dst;
    int width  = src.cols;
    int height = src.rows;
    src.copyTo(dst);
    int count = 0;  //记录迭代次数
    while (true)
    {
        count++;
        if (maxIterations != -1 && count > maxIterations) //限制次数并且迭代次数到达
            break;
        std::vector<uchar *> mFlag; //用于标记需要删除的点
        //对点标记
        for (int i = 0; i < height ;++i)
        {
            uchar * p = dst.ptr<uchar>(i);
            for (int j = 0; j < width; ++j)
            {
                //如果满足四个条件，进行标记
                //  p9 p2 p3
                //  p8 p1 p4
                //  p7 p6 p5
                uchar p1 = p[j];
                if (p1 != 1) continue;
                uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);
                uchar p8 = (j == 0) ? 0 : *(p + j - 1);
                uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);
                uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - dst.step + j + 1);
                uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);
                uchar p6 = (i == height - 1) ? 0 : *(p + dst.step + j);
                uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + dst.step + j + 1);
                uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);
                if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)
                {
                    int ap = 0;
                    if (p2 == 0 && p3 == 1) ++ap;
                    if (p3 == 0 && p4 == 1) ++ap;
                    if (p4 == 0 && p5 == 1) ++ap;
                    if (p5 == 0 && p6 == 1) ++ap;
                    if (p6 == 0 && p7 == 1) ++ap;
                    if (p7 == 0 && p8 == 1) ++ap;
                    if (p8 == 0 && p9 == 1) ++ap;
                    if (p9 == 0 && p2 == 1) ++ap;

                    if (ap == 1 && p2 * p4 * p6 == 0 && p4 * p6 * p8 == 0)
                    {
                        //标记
                        mFlag.push_back(p+j);
                    }
                }
            }
        }

        //将标记的点删除
        for (std::vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
        {
            **i = 0;
        }

        //直到没有点满足，算法结束
        if (mFlag.empty())
        {
            break;
        }
        else
        {
            mFlag.clear();//将mFlag清空
        }

        //对点标记
        for (int i = 0; i < height; ++i)
        {
            uchar * p = dst.ptr<uchar>(i);
            for (int j = 0; j < width; ++j)
            {
                //如果满足四个条件，进行标记
                //  p9 p2 p3
                //  p8 p1 p4
                //  p7 p6 p5
                uchar p1 = p[j];
                if (p1 != 1) continue;
                uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);
                uchar p8 = (j == 0) ? 0 : *(p + j - 1);
                uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);
                uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - dst.step + j + 1);
                uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);
                uchar p6 = (i == height - 1) ? 0 : *(p + dst.step + j);
                uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + dst.step + j + 1);
                uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);

                if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)
                {
                    int ap = 0;
                    if (p2 == 0 && p3 == 1) ++ap;
                    if (p3 == 0 && p4 == 1) ++ap;
                    if (p4 == 0 && p5 == 1) ++ap;
                    if (p5 == 0 && p6 == 1) ++ap;
                    if (p6 == 0 && p7 == 1) ++ap;
                    if (p7 == 0 && p8 == 1) ++ap;
                    if (p8 == 0 && p9 == 1) ++ap;
                    if (p9 == 0 && p2 == 1) ++ap;

                    if (ap == 1 && p2 * p4 * p8 == 0 && p2 * p6 * p8 == 0)
                    {
                        //标记
                        mFlag.push_back(p+j);
                    }
                }
            }
        }

        //将标记的点删除
        for (std::vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
        {
            **i = 0;
        }

        //直到没有点满足，算法结束
        if (mFlag.empty())
        {
            break;
        }
        else
        {
            mFlag.clear();//将mFlag清空
        }
    }
    return dst;
}

void ImageProcess::ThinImage_sub1(Mat &pSrc, Mat &pDst)
{
    int rows = pSrc.rows;
    int cols = pSrc.cols;
    pSrc.copyTo(pDst);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(pSrc.at<float>(i, j) == 1.0f) {
                /// get 8 neighbors
                /// calculate C(p)
                int neighbor0 = (int) pSrc.at<float>( i-1, j-1);
                int neighbor1 = (int) pSrc.at<float>( i-1, j);
                int neighbor2 = (int) pSrc.at<float>( i-1, j+1);
                int neighbor3 = (int) pSrc.at<float>( i, j+1);
                int neighbor4 = (int) pSrc.at<float>( i+1, j+1);
                int neighbor5 = (int) pSrc.at<float>( i+1, j);
                int neighbor6 = (int) pSrc.at<float>( i+1, j-1);
                int neighbor7 = (int) pSrc.at<float>( i, j-1);
                int C = int(~neighbor1 & ( neighbor2 | neighbor3)) +
                        int(~neighbor3 & ( neighbor4 | neighbor5)) +
                        int(~neighbor5 & ( neighbor6 | neighbor7)) +
                        int(~neighbor7 & ( neighbor0 | neighbor1));
                if(C == 1) {
                    /// calculate N
                    int N1 = int(neighbor0 | neighbor1) +
                            int(neighbor2 | neighbor3) +
                            int(neighbor4 | neighbor5) +
                            int(neighbor6 | neighbor7);
                    int N2 = int(neighbor1 | neighbor2) +
                            int(neighbor3 | neighbor4) +
                            int(neighbor5 | neighbor6) +
                            int(neighbor7 | neighbor0);
                    int N = min(N1,N2);
                    if ((N == 2) || (N == 3)) {
                        /// calculate criteria 3
                        int c3 = ( neighbor1 | neighbor2 | ~neighbor4) & neighbor3;
                        if(c3 == 0) {
                            pDst.at<float>( i, j) = 0.0f;
                        }
                    }
                }
            }
        }
    }
}

void ImageProcess::ThinImage_sub2(Mat &pSrc, Mat &pDst)
{
    int rows = pSrc.rows;
    int cols = pSrc.cols;
    pSrc.copyTo( pDst);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if (pSrc.at<float>( i, j) == 1.0f) {
                /// get 8 neighbors
                /// calculate C(p)
                int neighbor0 = (int) pSrc.at<float>( i-1, j-1);
                int neighbor1 = (int) pSrc.at<float>( i-1, j);
                int neighbor2 = (int) pSrc.at<float>( i-1, j+1);
                int neighbor3 = (int) pSrc.at<float>( i, j+1);
                int neighbor4 = (int) pSrc.at<float>( i+1, j+1);
                int neighbor5 = (int) pSrc.at<float>( i+1, j);
                int neighbor6 = (int) pSrc.at<float>( i+1, j-1);
                int neighbor7 = (int) pSrc.at<float>( i, j-1);
                int C = int(~neighbor1 & ( neighbor2 | neighbor3)) +
                        int(~neighbor3 & ( neighbor4 | neighbor5)) +
                        int(~neighbor5 & ( neighbor6 | neighbor7)) +
                        int(~neighbor7 & ( neighbor0 | neighbor1));
                if(C == 1) {
                    /// calculate N
                    int N1 = int(neighbor0 | neighbor1) +
                            int(neighbor2 | neighbor3) +
                            int(neighbor4 | neighbor5) +
                            int(neighbor6 | neighbor7);
                    int N2 = int(neighbor1 | neighbor2) +
                            int(neighbor3 | neighbor4) +
                            int(neighbor5 | neighbor6) +
                            int(neighbor7 | neighbor0);
                    int N = min(N1,N2);
                    if((N == 2) || (N == 3)) {
                        int E = (neighbor5 | neighbor6 | ~neighbor0) & neighbor7;
                        if(E == 0) {
                            pDst.at<float>(i, j) = 0.0f;
                        }
                    }
                }
            }
        }
    }
}

void ImageProcess::ThinImage1_sub(Mat &src, Mat &dst, int intera)
{
    //这里先用判断语句看看图像通道数是否正确，这里必须使用单通道得图像
    if(src.type()!=CV_8UC1)
    {
        printf("只能处理二值或灰度图像\n");
        return;
    }
    //非原地操作时候，copy src到dst
    //对图片进行拷贝
    if(dst.data!=src.data)
    {
        src.copyTo(dst);
    }

    int i, j, n;/*这里定义三个变量变量n是一个循环迭代的作用,
    变量i、j是遍历像素的判断条件*/
    int width, height;//定义两个变量，接收图片的宽度与高度
    width = src.cols -1;//这里-1我的理解是为了便于处理矩阵的边缘数值
    //之所以减1，是方便处理8邻域，防止越界
    height = src.rows -1;
    int step = src.step;//这里是Mat的一个属性，叫做step，我会在最下边对他进行讲解
    int  p2,p3,p4,p5,p6,p7,p8,p9;//定义7个变量，接收待会遍历图像矩阵的数值
    uchar* img;//定义一个无符号指针，是为了接收待会Mat图片的地址，这个地方我会放在下边进行讲解
    bool ifEnd;/*定义一个布尔类型的变量，是为了下边判断是否满足循环条件，不满足会
    改变布尔值，供循环条件判断
    */
    int A1;//定义一个变量。是为了统计8邻域中0、1的对数，一对则记为1，两对则记为2，这个变量最后是判断是否满足像素去除条件的
    cv::Mat tmpimg;/*定义一个中间图片模板变量，这里是把dst的值拷贝给temp,然后遍历的是temp的值，找到要删除的值。但是遍历之后是在dst中改的
        */
    //n表示迭代次数
    for(n = 0; n<intera; n++)
    {
        dst.copyTo(tmpimg);
        ifEnd = false;
        img = tmpimg.data;
        for(i = 1; i < height; i++)//开始行扫描
        {
            img += step;//把每次遍历每行step的值记录给指针img,
            for(j =1; j<width; j++)//开始遍历图片的列，
            {
                uchar* p = img + j;//这里是刚才img的值加上j的值，然后赋值给指针p
                A1 = 0;//对A1变量的值进行初始化
                if( p[0] > 0)//这里是开始zhang并行算法的第一步，判断目标值是否满足执行条件
                {
                    if(p[-step]==0&&p[-step+1]>0) /*p2,p3 01模式，P[-step]表示的是值p[0]上边的一个数值,P[-step+1]表示是P[-step]下一个数值*/
                    {
                        A1++;
                    }
                    if(p[-step+1]==0&&p[1]>0) //p3,p4 01模式p[1]表示的是P[0]的下一个数，下边的以此类推，下边的应该都可以理解了吧我感觉
                    {
                        A1++;
                    }
                    if(p[1]==0&&p[step+1]>0) //p4,p5 01模式
                    {
                        A1++;
                    }
                    if(p[step+1]==0&&p[step]>0) //p5,p6 01模式
                    {
                        A1++;
                    }
                    if(p[step]==0&&p[step-1]>0) //p6,p7 01模式
                    {
                        A1++;
                    }
                    if(p[step-1]==0&&p[-1]>0) //p7,p8 01模式
                    {
                        A1++;
                    }
                    if(p[-1]==0&&p[-step-1]>0) //p8,p9 01模式
                    {
                        A1++;
                    }
                    if(p[-step-1]==0&&p[-step]>0) //p9,p2 01模式
                    {
                        A1++;
                    }
                    //这里是
                    p2 = p[-step]>0?1:0;
                    p3 = p[-step+1]>0?1:0;
                    p4 = p[1]>0?1:0;
                    p5 = p[step+1]>0?1:0;
                    p6 = p[step]>0?1:0;
                    p7 = p[step-1]>0?1:0;
                    p8 = p[-1]>0?1:0;
                    p9 = p[-step-1]>0?1:0;
                    if((p2+p3+p4+p5+p6+p7+p8+p9)>1 && (p2+p3+p4+p5+p6+p7+p8+p9)<7  &&  A1==1)
                    {
                        if((p2==0||p4==0||p6==0)&&(p4==0||p6==0||p8==0)) //p2*p4*p6=0 && p4*p6*p8==0
                        {
                            dst.at<uchar>(i,j) = 0; //满足删除条件，设置当前像素为0
                            ifEnd = true;
                        }
                    }
                }
            }
        }

        dst.copyTo(tmpimg);
        img = tmpimg.data;
        for(i = 1; i < height; i++)
        {
            img += step;
            for(j =1; j<width; j++)
            {
                A1 = 0;
                uchar* p = img + j;
                if( p[0] > 0)
                {
                    if(p[-step]==0&&p[-step+1]>0) //p2,p3 01模式
                    {
                        A1++;
                    }
                    if(p[-step+1]==0&&p[1]>0) //p3,p4 01模式
                    {
                        A1++;
                    }
                    if(p[1]==0&&p[step+1]>0) //p4,p5 01模式
                    {
                        A1++;
                    }
                    if(p[step+1]==0&&p[step]>0) //p5,p6 01模式
                    {
                        A1++;
                    }
                    if(p[step]==0&&p[step-1]>0) //p6,p7 01模式
                    {
                        A1++;
                    }
                    if(p[step-1]==0&&p[-1]>0) //p7,p8 01模式
                    {
                        A1++;
                    }
                    if(p[-1]==0&&p[-step-1]>0) //p8,p9 01模式
                    {
                        A1++;
                    }
                    if(p[-step-1]==0&&p[-step]>0) //p9,p2 01模式
                    {
                        A1++;
                    }
                    p2 = p[-step]>0?1:0;
                    p3 = p[-step+1]>0?1:0;
                    p4 = p[1]>0?1:0;
                    p5 = p[step+1]>0?1:0;
                    p6 = p[step]>0?1:0;
                    p7 = p[step-1]>0?1:0;
                    p8 = p[-1]>0?1:0;
                    p9 = p[-step-1]>0?1:0;
                    if((p2+p3+p4+p5+p6+p7+p8+p9)>1 && (p2+p3+p4+p5+p6+p7+p8+p9)<7  &&  A1==1)
                    {
                        if((p2==0||p4==0||p8==0)&&(p2==0||p6==0||p8==0)) //p2*p4*p8=0 && p2*p6*p8==0
                        {
                            dst.at<uchar>(i,j) = 0; //满足删除条件，设置当前像素为0
                            ifEnd = true;
                        }
                    }
                }
            }
        }

        //如果两个子迭代已经没有可以细化的像素了，则退出迭代
        if(!ifEnd) break;
    }
    //imshow("thin",dst);
}
/*
bool ImageProcess::dilateImage(IplImage *srcImage)
{
    IplImage *m1;
    m1 = srcImage;

    if(m1 == NULL)
    {
        qDebug() << "图片膨胀失败";
        return false;
    }


    //IplConvKernel *mymodel;
    //mymodel=cvCreateStructuringElementEx(3,3,1,1,CV_SHAPE_ELLIPSE);


    IplImage *img_dilate = cvCreateImage(cvGetSize(m1),m1->depth,m1->nChannels);
    //IplImage *img_dilate = cvCreateImage(cvGetSize(m1),8,1);
    cvDilate(m1,img_dilate,NULL,1);

    cvSaveImage((m_path+"/Img_dilate.jpg").toLocal8Bit().data(),img_dilate);

    Mat le = imread((m_path+"/Img_dilate.jpg").toLocal8Bit().data());
    Mat sharpenedLe;
    Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cv::filter2D(le, sharpenedLe, le.depth(), kernel);

    IplImage fimg=IplImage(sharpenedLe);
    cvSaveImage((m_path+"/Sharp_pic2.jpg").toLocal8Bit().data(),&fimg);
}
*/

bool ImageProcess::dilateImage(IplImage *srcImage)
{
    IplImage *m1;
    m1 = srcImage;

    if(m1 == NULL)
    {
        qDebug() << "图片膨胀失败";
        return false;
    }

    IplImage *img_dilate = cvCreateImage(cvGetSize(m1),m1->depth,m1->nChannels);
    cvDilate(m1,img_dilate,NULL,1);
    cvSaveImage((m_path+"/Sharp_pic1.png").toLocal8Bit().data(),img_dilate);
    Mat sharpenedLe;
    Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cv::filter2D(cvarrToMat(img_dilate), sharpenedLe, img_dilate->depth, kernel);

    IplImage fimg=IplImage(sharpenedLe);
    cvSaveImage((m_path+"/Sharp_pic2.png").toLocal8Bit().data(),&fimg);
}

void ImageProcess::DilationImage1_sub1(Mat &src,Mat &dst_diolate,int dilation_size)
{
    // dst = Mat::zeros(src.size(), src.type());
      int erosion_type = MORPH_CROSS;
      Mat ele = getStructuringElement(erosion_type,
          Size(2 * dilation_size + 1, 2 * dilation_size + 1),
          Point(dilation_size, dilation_size));
      dilate(src, dst_diolate, ele);
}

void ImageProcess::DilationImage1_sub2(Mat &src,Mat &dst_erosion,int erosion_size)
{
    int erosion_type = MORPH_CROSS;
        Mat element = getStructuringElement(erosion_type,
            Size(2 * erosion_size + 1, 2 * erosion_size + 1),
            Point(erosion_size, erosion_size));
        ///膨胀操作
        erode(src, dst_erosion, element);
}

IplImage *ImageProcess::QImageToIplImage(const QImage *qImage)
{
    int width = qImage->width();
    int height = qImage->height();
    CvSize Size;
    Size.height = height;
    Size.width = width;
    IplImage *IplImageBuffer = cvCreateImage(Size, IPL_DEPTH_8U, 3);
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            QRgb rgb = qImage->pixel(x, y);
            cvSet2D(IplImageBuffer, y, x, CV_RGB(qRed(rgb), qGreen(rgb), qBlue(rgb)));
        }
    }
    return IplImageBuffer;
}

QImage *ImageProcess::IplImageToQImage(IplImage *image)
{
    QImage *result = nullptr;
    if (image){
        uchar * qImageBuffer = nullptr;
        int width = image->width;
        int widthStep = image->widthStep;
        int height = image->height;
        QImage::Format format = QImage::Format_Invalid;
        if (IPL_DEPTH_8U == image->depth && 3 == image->nChannels){
            qImageBuffer = (uchar *) malloc(width * height * 4 * sizeof(uchar));
            uchar *QImagePtr = qImageBuffer;
            const uchar *iplImagePtr = (const uchar *) image->imageData;
            format = QImage::Format_RGB32;
            if (!qImageBuffer){
                qDebug() << "Insufficient memory for image buffer!" << endl;
                return result;
            }
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    QImagePtr[0] = iplImagePtr[0];
                    QImagePtr[1] = iplImagePtr[1];
                    QImagePtr[2] = iplImagePtr[2];
                    QImagePtr[3] = 0;

                    QImagePtr += 4;
                    iplImagePtr += 3;
                }
                iplImagePtr += widthStep-3*width;
            }
        } else {
            qDebug("Image format is not supported: depth=%d and %d channels\n", image->depth, image->nChannels);
            return result;
        }
        if (qImageBuffer){
            QImage *result = new QImage(qImageBuffer, image->width, image->height, format);
        }
    } else {
        qDebug() << "Image pointer is NULL" << endl;
    }
    return result;


}

QString ImageProcess::getImgType(int imgTypeInt)
{
    int numImgTypes = 35; // 7 base types, with five channel options each (none or C1, ..., C4)

    int enum_ints[] =       {CV_8U,  CV_8UC1,  CV_8UC2,  CV_8UC3,  CV_8UC4,
                             CV_8S,  CV_8SC1,  CV_8SC2,  CV_8SC3,  CV_8SC4,
                             CV_16U, CV_16UC1, CV_16UC2, CV_16UC3, CV_16UC4,
                             CV_16S, CV_16SC1, CV_16SC2, CV_16SC3, CV_16SC4,
                             CV_32S, CV_32SC1, CV_32SC2, CV_32SC3, CV_32SC4,
                             CV_32F, CV_32FC1, CV_32FC2, CV_32FC3, CV_32FC4,
                             CV_64F, CV_64FC1, CV_64FC2, CV_64FC3, CV_64FC4};

    QString enum_strings[] = {"CV_8U",  "CV_8UC1",  "CV_8UC2",  "CV_8UC3",  "CV_8UC4",
                             "CV_8S",  "CV_8SC1",  "CV_8SC2",  "CV_8SC3",  "CV_8SC4",
                             "CV_16U", "CV_16UC1", "CV_16UC2", "CV_16UC3", "CV_16UC4",
                             "CV_16S", "CV_16SC1", "CV_16SC2", "CV_16SC3", "CV_16SC4",
                             "CV_32S", "CV_32SC1", "CV_32SC2", "CV_32SC3", "CV_32SC4",
                             "CV_32F", "CV_32FC1", "CV_32FC2", "CV_32FC3", "CV_32FC4",
                             "CV_64F", "CV_64FC1", "CV_64FC2", "CV_64FC3", "CV_64FC4"};

    for(int i=0; i<numImgTypes; i++)
    {
        if(imgTypeInt == enum_ints[i]) return enum_strings[i];
    }
    return "unknown image type";
}

vector<Mat> ImageProcess::cutPics(IplImage *img)
{
    Mat srcImg;
    srcImg=cvarrToMat(img);
    int cut_rows = 10, cut_cols = 10;
    vector<Mat> ceilImg;
    int height = srcImg.rows;
    int width = srcImg.cols;
    int ceil_height = (int)(height / cut_rows);
    int ceil_width = (int)(width / cut_cols);
    int ceil_down_height = height - (cut_rows - 1)*ceil_height;
    int ceil_right_width = width - (cut_cols - 1)*ceil_width;

    for (int i = 0; i<cut_rows - 1; i++)
        for (int j = 0; j<cut_cols; j++)
        {
            if (j<cut_cols - 1)
            {
                Rect rect(j*ceil_width, i*ceil_height, ceil_width, ceil_height);
                cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
                ceilImg.push_back(srcImg(rect));
                //ceilImg.push_back(new IplImage(srcImg(rect)));
            }
            else
            {
                Rect rect((cut_cols - 1)*ceil_width, i*ceil_height, ceil_right_width, ceil_height);
                ceilImg.push_back(srcImg(rect));
            }
        }

    for (int i = 0; i<cut_cols; i++)
    {
        if (i<cut_cols - 1)
        {
            Rect rect(i*ceil_width, (cut_rows - 1)*ceil_height, ceil_width, ceil_down_height);
            ceilImg.push_back(srcImg(rect));
        }
        else   //右下角这个图像块
        {
            Rect rect((cut_cols - 1)*ceil_width, (cut_rows - 1)*ceil_height, ceil_right_width, ceil_down_height);
            ceilImg.push_back(srcImg(rect));
        }
    }
}

Mat ImageProcess::CutPics(QString path, QString fileTarget)
{
    Mat bigImage;
    //分割图片
    int cut_rows = 10, cut_cols = 10; //将一张图片切割为10*10小图片
    Mat srcImg = imread(path.toLocal8Bit().data());
    vector<Mat> ceilImg;
    int height = srcImg.rows;
    int width = srcImg.cols;
    int ceil_height = (int)(height / cut_rows);
    int ceil_width = (int)(width / cut_cols);
    int ceil_down_height = height - (cut_rows - 1)*ceil_height;
    int ceil_right_width = width - (cut_cols - 1)*ceil_width;
    for (int i = 0; i<cut_rows - 1; i++)
        for (int j = 0; j<cut_cols; j++)
        {
            if (j<cut_cols - 1)
            {
                Rect rect(j*ceil_width, i*ceil_height, ceil_width, ceil_height);
                ceilImg.push_back(srcImg(rect));
            }
            else
            {
                Rect rect((cut_cols - 1)*ceil_width, i*ceil_height, ceil_right_width, ceil_height);
                ceilImg.push_back(srcImg(rect));
            }
        }
    for (int i = 0; i<cut_cols; i++)
    {
        if (i<cut_cols - 1)
        {
            Rect rect(i*ceil_width, (cut_rows - 1)*ceil_height, ceil_width, ceil_down_height);
            ceilImg.push_back(srcImg(rect));
        }
        else   //右下角这个图像块
        {
            Rect rect((cut_cols - 1)*ceil_width, (cut_rows - 1)*ceil_height, ceil_right_width, ceil_down_height);
            ceilImg.push_back(srcImg(rect));
        }
    }

    Mat dst,dst1,dst2,dst3,dst4;
    vector<Mat> images;

    //对每张小图片进行滤波，二值化处理
    for (int i = 0; i < ceilImg.size(); i++)
    {
        cvtColor(ceilImg[i], dst1, COLOR_BGR2GRAY);
        //dst = ceilImg[i];
        //高斯滤波
        GaussianBlur(dst1,dst2, Size(7,7), 0);
        //threshold(dst1,dst3,127,255,THRESH_OTSU | THRESH_BINARY);
        //自适应阈值分割
//        adaptiveThreshold(dst1,dst4,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,9,5);
        adaptiveThreshold(dst1,dst,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,11,2);
//        GaussianBlur(dst,dst, Size(3,3), 0);
        images.push_back(dst.clone());
    }

    //将这些小图片重新合成一张大图
    vector<vector<Mat>> ceilImags;
    vector<Mat> r_Images;
    for (int i = 0; i < 10;i++)
    {
        for (int j = 0; j < 10; j++)
        {
            r_Images.push_back(images[i*10+j]);
        }
        ceilImags.push_back(r_Images);
        r_Images.clear();
    }
    vector<Mat> rowImags;
    Mat rowImag;
    for (int i = 0; i < 10; i++)
    {
        hconcat( ceilImags[i], rowImag);
        rowImags.push_back(rowImag.clone());
    }
    vconcat(rowImags,bigImage);
    //GaussianBlur(bigImage,bigImage, Size(3,3), 0);
    threshold(bigImage,bigImage,1,255,THRESH_BINARY_INV);

    QString fpath = fileTarget + "/test.png";
    imwrite(fpath.toLocal8Bit().data(), bigImage);
    //imshow("bigImage", bigImage);

    return bigImage;
}

void ImageProcess::ThinImage(const QString &path, const QString &fileTarget)
{
    qDebug() << "start: " << __func__;
    Mat inputarray = imread(path.toLocal8Bit().data());
    //imshow("inputarray1", inputarray);
    //waitKey(0);
    //inputarray = inputarray(Rect(10, 10, inputarray.cols - 20, inputarray.rows - 20));
    threshold(inputarray, inputarray, 100, 255, CV_THRESH_BINARY);
    //imshow("inputarray2", inputarray);
    //waitKey(0);
    //qDebug() << "theType1: " << getImgType(inputarray.type());
    Mat outputarray(inputarray.rows,inputarray.cols,CV_32FC1);

    bool bDone = false;
    int rows = inputarray.rows;
    int cols = inputarray.cols;

    inputarray.convertTo(inputarray, CV_32FC1);
    inputarray.copyTo(outputarray);
    //qDebug() << "theType2: " << getImgType(inputarray.type());
    //imshow("inputarray3", inputarray);
    //waitKey(0);
    //outputarray.convertTo(outputarray, CV_32FC1);

    /// pad source
    Mat p_enlarged_src = Mat(rows + 2, cols + 2, CV_32FC1);
    for (int i = 0; i < (rows + 2); i++) {
        p_enlarged_src.at<float>(i, 0) = 0.0f;
        p_enlarged_src.at<float>(i, cols + 1) = 0.0f;
    }
    for (int j = 0; j < (cols + 2); j++) {
        p_enlarged_src.at<float>(0, j) = 0.0f;
        p_enlarged_src.at<float>(rows + 1, j) = 0.0f;
    }
    //imshow("p_enlarged_src1", p_enlarged_src);
    //waitKey(0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (inputarray.at<float>(i, j) >= 20.0f) {
                p_enlarged_src.at<float>(i + 1, j + 1) = 1.0f;
            }
            else{
                p_enlarged_src.at<float>(i + 1, j + 1) = 0.0f;
            }
        }
    }
    //imshow("p_enlarged_src2", p_enlarged_src);
    //waitKey(0);
    /// start to thin
    Mat p_thinMat1 = Mat::zeros(rows + 2, cols + 2, CV_32FC1);
    Mat p_thinMat2 = Mat::zeros(rows + 2, cols + 2, CV_32FC1);
    Mat p_cmp = Mat::zeros(rows + 2, cols + 2, CV_8UC1);

    while (bDone != true) {
        /// sub-iteration 1
        ThinImage_sub1(p_enlarged_src, p_thinMat1);
        /// sub-iteration 2
        //ThinImage_sub2(p_thinMat1, p_thinMat2);
        /// compare
        compare(p_enlarged_src, p_thinMat1, p_cmp, CV_CMP_EQ);
        /// check
        int num_non_zero = countNonZero(p_cmp);
        if (num_non_zero == (rows + 2) * (cols + 2)) {
            bDone = true;
        }
        /// copy
        p_thinMat1.copyTo(p_enlarged_src);
    }
    //imshow("p_thinMat1", p_thinMat1);
    //imshow("p_cmp", p_cmp);
    //imshow("p_enlarged_src3", p_enlarged_src);
    //waitKey(0);
    // copy result
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            outputarray.at<float>(i, j) = p_enlarged_src.at<float>(i + 1, j + 1);
        }
    }
    //imshow("inputarray4", inputarray);
    //imshow("p_enlarged_src4", p_enlarged_src);
    //imshow("ThinImage", outputarray);
    imshow("ThinImage", outputarray);
    waitKey(0);
    QString fpath = fileTarget + "/ThinImage.png";
    imwrite(fpath.toLocal8Bit().data(), outputarray);
    qDebug() << "end: " << __func__;

}

void ImageProcess::ThinImage1(const QString &path, const QString &fileTarget)
{
    qDebug() << "start: " << __func__;
    cv::Mat src = imread(path.toLocal8Bit().data());
    cvtColor(src,src,COLOR_BGR2GRAY);
    threshold(src,src,100,255,THRESH_BINARY);
    Mat dst;
    ThinImage1_sub(src,dst,12);
    imshow("ThinImage1",dst);
    waitKey(0);
    QString fpath = fileTarget + "/ThinImage1.png";
    imwrite(fpath.toLocal8Bit().data(), dst);
    qDebug() << "end: " << __func__;

}

void ImageProcess::ThinImage2(const QString &path, const QString &fileTarget)
{
    qDebug() << "start: " << __func__;
    //获取图像
    cv::Mat src = cv::imread(path.toLocal8Bit().data(), cv::IMREAD_GRAYSCALE);
    if (src.empty())
    {
        std::cout << "读取文件失败！" << std::endl;
        return;
    }
    //将原图像转换为二值图像
    cv::threshold(src, src, 128, 1, cv::THRESH_BINARY);
    //图像细化
    cv::Mat dst = ThinImage2_sub(src);
    //显示图像
    dst = dst * 255;
    //cv::namedWindow("src1", CV_WINDOW_AUTOSIZE);
    //cv::namedWindow("dst1", CV_WINDOW_AUTOSIZE);
    //cv::imshow("src1", src);
    cv::imshow("ThinImage2", dst);
    cv::waitKey(0);
    QString fpath = fileTarget + "/ThinImage2.png";
    imwrite(fpath.toLocal8Bit().data(), dst);
    qDebug() << "end: " << __func__;

}

void ImageProcess::DilationImage1(const QString &path, const QString &fileTarget)
{
    qDebug() << "start: " << __func__;
    Mat src, dst_diolate, dst_erosion;
    int erosion_size = 1;
    int dilation_size = 1;
    src = imread(path.toLocal8Bit().data());
    //namedWindow("Dilation Demo", CV_WINDOW_AUTOSIZE);
    //namedWindow("Erosion Demo", CV_WINDOW_AUTOSIZE);

    //cvMoveWindow("Dilation Demo", src.cols, 0);
    //cvMoveWindow("Erosion Demo", src.cols, 0);

    DilationImage1_sub1(src,dst_diolate,dilation_size);
    imshow("dst_diolate", dst_diolate);
    DilationImage1_sub2(src,dst_erosion,erosion_size);
    imshow("dst_erosion", dst_erosion);
    waitKey();
    QString fpath = fileTarget + "/DilationImage1_diolate.png";
    imwrite(fpath.toLocal8Bit().data(), dst_diolate);
    fpath = fileTarget + "/DilationImage1_erosion.png";
    imwrite(fpath.toLocal8Bit().data(), dst_erosion);
    qDebug() << "end: " << __func__;
}




enum adaptiveMethod{meanFilter,gaaussianFilter,medianFilter};

void AdaptiveThreshold(cv::Mat& src, cv::Mat& dst, double Maxval, int Subsize, double c, adaptiveMethod method = meanFilter){

    if (src.channels() > 1)
        cv::cvtColor(src, src, CV_RGB2GRAY);

    cv::Mat smooth;
    switch (method)
    {
    case  meanFilter:
        cv::blur(src, smooth, cv::Size(Subsize, Subsize));  //均值滤波
        break;
    case gaaussianFilter:
        cv::GaussianBlur(src, smooth, cv::Size(Subsize, Subsize),0,0); //高斯滤波
        break;
    case medianFilter:
        cv::medianBlur(src, smooth, Subsize);   //中值滤波
        break;
    default:
        break;
    }

    smooth = smooth - c;

    //阈值处理
    src.copyTo(dst);
    for (int r = 0; r < src.rows;++r){
        const uchar* srcptr = src.ptr<uchar>(r);
        const uchar* smoothptr = smooth.ptr<uchar>(r);
        uchar* dstptr = dst.ptr<uchar>(r);
        for (int c = 0; c < src.cols; ++c){
            if (srcptr[c]>smoothptr[c]){
                dstptr[c] = Maxval;
            }
            else
                dstptr[c] = 0;
        }
    }
 }
