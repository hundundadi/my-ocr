///////////////////////////////////////////////////////////////////////
// File:        otsuthr.h
// Description: Simple Otsu thresholding for binarizing images.简单的Otsu二值化图像的阈值。
// Author:      Ray Smith
//
// (C) Copyright 2008, Google Inc.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
///////////////////////////////////////////////////////////////////////

#ifndef TESSERACT_CCMAIN_OTSUTHR_H_
#define TESSERACT_CCMAIN_OTSUTHR_H_

#include "image.h"

#include <vector> // for std::vector

struct Pix;

namespace tesseract {

const int kHistogramSize = 256; // The size of a histogram of pixel values.像素值直方图的大小。

// Computes the Otsu threshold(s) for the given image rectangle, making one
// for each channel. Each channel is always one byte per pixel.
// Returns an array of threshold values and an array of hi_values, such
// that a pixel value >threshold[channel] is considered foreground if
// hi_values[channel] is 0 or background if 1. A hi_value of -1 indicates
// that there is no apparent foreground. At least one hi_value will not be -1.
// The return value is the number of channels in the input image, being
// the size of the output thresholds and hi_values arrays.

/**
 * 计算给定图像矩形的Otsu阈值(s)，为每个通道创建一个。每个通道总是每像素一个字节。
 * 返回一个阈值数组和一个hi_values数组，这样，如果hi_values[channel]为0，像素值>阈值[channel]被认为是前景，
 * 如果hi_values[channel]为1，则被认为是背景。
 * hi_value为-1表示没有明显的前台。至少有一个hi_value不为-1。
 * 返回值是输入图像中的通道数，即输出阈值和hi_values数组的大小。
 */
int OtsuThreshold(Image src_pix, int left, int top, int width, int height,
                  std::vector<int> &thresholds,
                  std::vector<int> &hi_values);

// Computes the histogram for the given image rectangle, and the given
// single channel. Each channel is always one byte per pixel.
// Histogram is always a kHistogramSize(256) element array to count
// occurrences of each pixel value.
/**
 * 计算给定的图像矩形的直方图，以及给定的单个通道。
 * 每个通道总是每像素一个字节。
 * 直方图总是一个k直方图大小(256)元素数组，用来计数每个像素值的出现次数。
 */
void HistogramRect(Image src_pix, int channel, int left, int top, int width, int height,
                   int *histogram);

// Computes the Otsu threshold(s) for the given histogram.
// Also returns H = total count in histogram, and
// omega0 = count of histogram below threshold.
int OtsuStats(const int *histogram, int *H_out, int *omega0_out);

} // namespace tesseract.

#endif // TESSERACT_CCMAIN_OTSUTHR_H_
