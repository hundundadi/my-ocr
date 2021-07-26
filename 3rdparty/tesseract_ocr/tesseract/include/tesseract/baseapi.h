///////////////////////////////////////////////////////////////////////
// File:        baseapi.h
// Description: Simple API for calling tesseract.
// Author:      Ray Smith
//
// (C) Copyright 2006, Google Inc.
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

#ifndef TESSERACT_API_BASEAPI_H_
#define TESSERACT_API_BASEAPI_H_

#ifdef HAVE_CONFIG_H
#  include "config_auto.h" // DISABLED_LEGACY_ENGINE
#endif

#include "export.h"
#include "pageiterator.h"
#include "publictypes.h"
#include "resultiterator.h"
#include "unichar.h"

#include "3rdparty/tesseract_ocr/tesseract/include/tesseract/version.h"

#include <cstdio>
#include <tuple>  // for std::tuple
#include <vector> // for std::vector

struct Pix;
struct Pixa;
struct Boxa;

namespace tesseract {

class PAGE_RES;
class ParagraphModel;
class BLOCK_LIST;
class ETEXT_DESC;
struct OSResults;
class UNICHARSET;

class Dawg;
class Dict;
class EquationDetect;
class PageIterator;
class ImageThresholder;
class LTRResultIterator;
class ResultIterator;
class MutableIterator;
class TessResultRenderer;
class Tesseract;

// Function to read a std::vector<char> from a whole file.
// Returns false on failure.
using FileReader = bool (*)(const char *filename, std::vector<char> *data);

using DictFunc = int (Dict::*)(void *, const UNICHARSET &, UNICHAR_ID,
                               bool) const;
using ProbabilityInContextFunc = double (Dict::*)(const char *, const char *,
                                                  int, const char *, int);

/**
 * Base class for all tesseract APIs.
 * Specific classes can add ability to work on different inputs or produce
 * different outputs.
 * This class is mostly an interface layer on top of the Tesseract instance
 * class to hide the data types so that users of this class don't have to
 * include any other Tesseract headers.
 * 所有tesseract api的基类。
 * 特定的类可以添加处理不同输入或产生不同输出的能力。
 * 该类主要是Tesseract实例类之上的一个接口层，用来隐藏数据类型，
 * 这样该类的用户就不必包含任何其他Tesseract头文件。
 */
class TESS_API TessBaseAPI {
public:
  TessBaseAPI();
  virtual ~TessBaseAPI();
  // Copy constructor and assignment operator are currently unsupported.
  //目前不支持复制构造函数和赋值操作符。
  TessBaseAPI(TessBaseAPI const &) = delete;
  TessBaseAPI &operator=(TessBaseAPI const &) = delete;

  /**
   * Returns the version identifier as a static string. Do not delete.
   * 以静态字符串的形式返回版本标识符。不能删除。
   */
  static const char *Version();

  /**
   * If compiled with OpenCL AND an available OpenCL
   * device is deemed faster than serial code, then
   * "device" is populated with the cl_device_id
   * and returns sizeof(cl_device_id)
   * otherwise *device=nullptr and returns 0.
   * 如果使用OpenCL编译，并且一个可用的OpenCL设备被认为比串行代码更快，
   * 那么“device”将被cl_device_id填充并返回sizeof(cl_device_id)，否则*device=nullptr并返回0。
   */
  static size_t getOpenCLDevice(void **device);

  /**
   * Set the name of the input file. Needed for training and
   * reading a UNLV zone file, and for searchable PDF output.
   * 设置输入文件的名称。需要训练和读取UNLV区域文件，以及可搜索的PDF输出。
   */
  void SetInputName(const char *name);
  /**
   * These functions are required for searchable PDF output.
   * We need our hands on the input file so that we can include
   * it in the PDF without transcoding. If that is not possible,
   * we need the original image. Finally, resolution metadata
   * is stored in the PDF so we need that as well.
   * 获取输入文件名
   * 可搜索PDF输出需要这些功能。
   * 我们需要亲手处理输入文件，这样我们就可以在不转码的情况下将其包含在PDF中。如果这是不可能的，我们需要原始图像。
   * 最后，分辨率元数据存储在PDF中，所以我们也需要它。
   */
  const char *GetInputName();
  // Takes ownership of the input pix.
  // 设置输入图形
  void SetInputImage(Pix *pix);
  // 获取输入图形
  Pix *GetInputImage();
  int GetSourceYResolution();
  const char *GetDatapath();

  /**
   * Set the name of the bonus output files. Needed only for debugging.
   * 设置额外的输出文件名称。仅用于调试。
   */
  void SetOutputName(const char *name);

  /**
   * Set the value of an internal "parameter."
   * Supply the name of the parameter and the value as a string, just as
   * you would in a config file.
   * Returns false if the name lookup failed.
   * Eg SetVariable("tessedit_char_blacklist", "xyz"); to ignore x, y and z.
   * Or SetVariable("classify_bln_numeric_mode", "1"); to set numeric-only mode.
   * SetVariable may be used before Init, but settings will revert to
   * defaults on End().
   *
   * Note: Must be called after Init(). Only works for non-init variables
   * (init variables should be passed to Init()).
   *
   * 设置内部“参数”的值。
   * 以字符串形式提供参数名和值，就像在配置文件中那样。
   * 如果名称查找失败，返回false。
   * 如SetVariable(“tessedit_char_blacklist”、“xyz”);忽略x y z。
   * 或SetVariable("classify_bln_numeric_mode"， "1");设置数字模式。
   * SetVariable可以在Init之前使用，但是在End()时设置将恢复为默认值。
   * 注意:必须在Init()之后调用。只适用于非初始化变量(初始化变量应该传递给init())。
   *
   */
  bool SetVariable(const char *name, const char *value);
  bool SetDebugVariable(const char *name, const char *value);

  /**
   * Returns true if the parameter was found among Tesseract parameters.
   * Fills in value with the value of the parameter.
   * 如果在Tesseract参数中找到该参数，则返回true。
   * 用参数的值填充value。
   */
  bool GetIntVariable(const char *name, int *value) const;
  bool GetBoolVariable(const char *name, bool *value) const;
  bool GetDoubleVariable(const char *name, double *value) const;

  /**
   * Returns the pointer to the string that represents the value of the
   * parameter if it was found among Tesseract parameters.
   * 如果在Tesseract参数中找到参数值，则返回表示该参数值的字符串的指针。
   */
  const char *GetStringVariable(const char *name) const;

#ifndef DISABLED_LEGACY_ENGINE //禁用遗留引擎

  /**
   * Print Tesseract fonts table to the given file
   * 打印Tesseract字体表到指定的文件。.
   */
  void PrintFontsTable(FILE* fp) const;

#endif

  /**
   * Print Tesseract parameters to the given file.
   */
  void PrintVariables(FILE *fp) const;

  /**
   * Get value of named variable as a string, if it exists.
   * 打印Tesseract参数到给定的文件。
   */
  bool GetVariableAsString(const char *name, std::string *val) const;

  /**
   * Instances are now mostly thread-safe and totally independent,
   * but some global parameters remain. Basically it is safe to use multiple
   * TessBaseAPIs in different threads in parallel, UNLESS:
   * you use SetVariable on some of the Params in classify and textord.
   * If you do, then the effect will be to change it for all your instances.
   *
   * Start tesseract. Returns zero on success and -1 on failure.
   * NOTE that the only members that may be called before Init are those
   * listed above here in the class definition.
   *
   * The datapath must be the name of the tessdata directory.
   * The language is (usually) an ISO 639-3 string or nullptr will default to
   * eng. It is entirely safe (and eventually will be efficient too) to call
   * Init multiple times on the same instance to change language, or just
   * to reset the classifier.
   * The language may be a string of the form [~]<lang>[+[~]<lang>]* indicating
   * that multiple languages are to be loaded. Eg hin+eng will load Hindi and
   * English. Languages may specify internally that they want to be loaded
   * with one or more other languages, so the ~ sign is available to override
   * that. Eg if hin were set to load eng by default, then hin+~eng would force
   * loading only hin. The number of loaded languages is limited only by
   * memory, with the caveat that loading additional languages will impact
   * both speed and accuracy, as there is more work to do to decide on the
   * applicable language, and there is more chance of hallucinating incorrect
   * words.
   * WARNING: On changing languages, all Tesseract parameters are reset
   * back to their default values. (Which may vary between languages.)
   * If you have a rare need to set a Variable that controls
   * initialization for a second call to Init you should explicitly
   * call End() and then use SetVariable before Init. This is only a very
   * rare use case, since there are very few uses that require any parameters
   * to be set before Init.
   *
   * If set_only_non_debug_params is true, only params that do not contain
   * "debug" in the name will be set.
   *
   * 实例现在大多是线程安全的，并且完全独立，
   * 但是一些全局参数仍然存在。基本上，在不同的线程中并行使用多个tessbaseapi是安全的，
   * 除非:你在classification和textord中的一些参数上使用SetVariable。
   * 如果您这样做，那么结果将是为您的所有实例更改它。
   *
   * 开始Tesseract。成功返回0，失败返回-1。
   * 注意，在Init之前可以调用的成员只有上面在类定义中列出的那些。
   *
   * datapath必须是识别语言库目录的名称。
   * language(通常)是ISO 639-3字符串，否则nullptr默认为eng。
   * 在同一个实例上多次调用Init来更改语言，或者只是重置分类器是完全安全的(最终也是有效的)。
   * 语言可以是形式为[~][+[~]]*的字符串，表示要加载多种语言。
   * Eg hin+eng将加载印地语和英语。
   * 语言可以在内部指定它们想要与一种或多种其他语言一起加载，所以~符号可以覆盖这一点。
   * 例如，如果hin被设置，而默认加载eng，那么hin+~eng将只强制加载hin。
   * 加载语言的数量仅受内存的限制，但需要注意的是，加载其他语言将影响速度和准确性，因为要确定适用的语言还有更多工作要做。
   * 而且产生不正确单词的几率也更大。
   * 警告:在更改语言时，所有Tesseract参数将被重置为默认值。
   * (不同语言之间可能会有所不同。)如果你很少需要设置一个变量来控制第二次Init调用的初始化，你应该显式地调用End()，然后在Init之前使用SetVariable。
   * 这只是一个非常罕见的用例，因为很少有使用需要在初始化之前设置任何参数。
   *
   * 如果set_only_non_debug_params为true，则只设置名称中不包含"debug"的参数。
   */
  int Init(const char *datapath, const char *language, OcrEngineMode mode,
           char **configs, int configs_size,
           const std::vector<std::string> *vars_vec,
           const std::vector<std::string> *vars_values,
           bool set_only_non_debug_params);
  int Init(const char *datapath, const char *language, OcrEngineMode oem) {
    return Init(datapath, language, oem, nullptr, 0, nullptr, nullptr, false);
  }
  int Init(const char *datapath, const char *language) {
    return Init(datapath, language, OEM_DEFAULT, nullptr, 0, nullptr, nullptr,
                false);
  }
  // In-memory version reads the traineddata file directly from the given
  // data[data_size] array, and/or reads data via a FileReader.
  //内存版本直接从给定的data[data_size]数组读取traineddata文件，并/或通过FileReader读取数据。
  int Init(const char *data, int data_size, const char *language,
           OcrEngineMode mode, char **configs, int configs_size,
           const std::vector<std::string> *vars_vec,
           const std::vector<std::string> *vars_values,
           bool set_only_non_debug_params, FileReader reader);

  /**
   * Returns the languages string used in the last valid initialization.
   * If the last initialization specified "deu+hin" then that will be
   * returned. If hin loaded eng automatically as well, then that will
   * not be included in this list. To find the languages actually
   * loaded use GetLoadedLanguagesAsVector.
   * The returned string should NOT be deleted.
   *
   * 返回在最后一个有效初始化中使用的语言字符串。
   * 如果最后一个初始化指定了"deu+hin"，那么它将被返回。
   * 如果hin自动加载eng，那么将不包括在这个列表中。
   * 要找到实际加载的语言，使用getloaddlanguagesasvector。
   * 返回的字符串不应该被删除。
   */
  const char *GetInitLanguagesAsString() const;

  /**
   * Returns the loaded languages in the vector of std::string.
   * Includes all languages loaded by the last Init, including those loaded
   * as dependencies of other loaded languages.
   * 返回std::string向量中加载的语言。
   * 包括由最后一个Init加载的所有语言，包括那些作为其他加载语言的依赖项加载的语言。
   */
  void GetLoadedLanguagesAsVector(std::vector<std::string> *langs) const;

  /**
   * Returns the available languages in the sorted vector of std::string.
   * 返回std::string的排序向量中可用的语言。
   */
  void GetAvailableLanguagesAsVector(std::vector<std::string> *langs) const;

  /**
   * Init only the lang model component of Tesseract. The only functions
   * that work after this init are SetVariable and IsValidWord.
   * WARNING: temporary! This function will be removed from here and placed
   * in a separate API at some future time.
   *
   * 只初始化Tesseract的lang模型组件。
   * 只有SetVariable和IsValidWord在初始化之后才能工作。
   * 警告:暂时的!这个函数将从这里删除，并在将来的某个时候放在一个单独的API中。
   */
  int InitLangMod(const char *datapath, const char *language);

  /**
   * Init only for page layout analysis. Use only for calls to SetImage and
   * AnalysePage. Calls that attempt recognition will generate an error.
   * 初始化仅用于页面布局分析。仅用于调用SetImage和AnalysePage。尝试识别的调用将生成错误。
   */
  void InitForAnalysePage();

  /**
   * Read a "config" file containing a set of param, value pairs.
   * Searches the standard places: tessdata/configs, tessdata/tessconfigs
   * and also accepts a relative or absolute path name.
   * Note: only non-init params will be set (init params are set by Init()).
   *
   * 读取包含一组参数和值对的“配置”文件。
   * 搜索标准位置:tessdata/configs、tessdata/tessconfigs，并接受相对或绝对路径名。
   * 注意:只有非初始化参数会被设置(初始化参数由init()设置)。
   */
  void ReadConfigFile(const char *filename);
  /**
   * Same as above, but only set debug params from the given config file.
   * 与上面一样，但是只从给定的配置文件中设置调试参数。
   */
  void ReadDebugConfigFile(const char *filename);

  /**
   * Set the current page segmentation mode. Defaults to PSM_SINGLE_BLOCK.
   * The mode is stored as an IntParam so it can also be modified by
   * ReadConfigFile or SetVariable("tessedit_pageseg_mode", mode as string).
   *
   * 设置当前页面分段模式。默认为PSM_SINGLE_BLOCK。
   * 模式被存储为一个IntParam，因此它也可以被ReadConfigFile或SetVariable("tessedit_pageseg_mode"，"PSM_SINGLE_BLOCK")修改。
   */
  void SetPageSegMode(PageSegMode mode);

  /**
   * Return the current page segmentation mode.
   * 返回当前页面分段模式。
   */
  PageSegMode GetPageSegMode() const;

  /**
   * Recognize a rectangle from an image and return the result as a string.
   * May be called many times for a single Init.
   * Currently has no error checking.
   * Greyscale of 8 and color of 24 or 32 bits per pixel may be given.
   * Palette color images will not work properly and must be converted to
   * 24 bit.
   * Binary images of 1 bit per pixel may also be given but they must be
   * byte packed with the MSB of the first byte being the first pixel, and a
   * 1 represents WHITE. For binary images set bytes_per_pixel=0.
   * The recognized text is returned as a char* which is coded
   * as UTF8 and must be freed with the delete [] operator.
   *
   * Note that TesseractRect is the simplified convenience interface.
   * For advanced uses, use SetImage, (optionally) SetRectangle, Recognize,
   * and one or more of the Get*Text functions below.
   *
   * 从图像中识别矩形，并将结果作为字符串返回。
   * 可以为单个Init调用多次。
   * 目前没有错误检查。
   * 灰度为8，颜色为每像素24或32位。
   * 调色板上的彩色图像不能正常工作，必须转换为24位。
   * 也可以给出每像素1位的二进制图像，但它们必须以第一个字节的MSB为第一个像素进行字节打包，1表示WHITE。
   * 对于二进制图像，设置bytes_per_pixel=0。
   * 被识别的文本以char*的形式返回，该char*被编码为UTF8，必须使用delete[]操作符释放。
   * 注意，TesseractRect是简化的方便接口。
   * 对于高级用途，使用SetImage，(可选)SetRectangle, recognition，和一个或多个下面的Get*Text功能。
   */
  char *TesseractRect(const unsigned char *imagedata, int bytes_per_pixel,
                      int bytes_per_line, int left, int top, int width,
                      int height);

  /**
   * Call between pages or documents etc to free up memory and forget
   * adaptive data.
   * 调用页面或文档等以释放内存并忘记自适应数据。
   */
  void ClearAdaptiveClassifier();

  /**
   * @defgroup AdvancedAPI Advanced API
   * The following methods break TesseractRect into pieces, so you can
   * get hold of the thresholded image, get the text in different formats,
   * get bounding boxes, confidences etc.
   * 下面的方法将TesseractRect分割成几个部分，这样您就可以获得分割（阈值）图像、获得不同格式的文本、获得边界框、可信度等。
   */
  /* @{ */

  /**
   * Provide an image for Tesseract to recognize. Format is as
   * TesseractRect above. Copies the image buffer and converts to Pix.
   * SetImage clears all recognition results, and sets the rectangle to the
   * full image, so it may be followed immediately by a GetUTF8Text, and it
   * will automatically perform recognition.
   *
   * 提供一个让Tesseract识别的图像。格式如上面的TesseractRect。
   * 复制图像缓冲区并转换为图形。
   * SetImage清除所有的识别结果，并将矩形设置为完整的图像，因此它可能立即被一个GetUTF8Text紧随其后，它将自动执行识别。
   */
  void SetImage(const unsigned char *imagedata, int width, int height,
                int bytes_per_pixel, int bytes_per_line);

  /**
   * Provide an image for Tesseract to recognize. As with SetImage above,
   * Tesseract takes its own copy of the image, so it need not persist until
   * after Recognize.
   * Pix vs raw, which to use?
   * Use Pix where possible. Tesseract uses Pix as its internal representation
   * and it is therefore more efficient to provide a Pix directly.
   * 提供一个让Tesseract识别的图像。
   * 和上面的SetImage一样，Tesseract也有自己的图像副本，所以在recognition完成之前不需要持久化。
   * Pix vs raw，使用哪个?
   * 尽可能使用图片。Tesseract使用Pix作为其内部表示，因此直接提供一个Pix会更有效。
   */
  void SetImage(Pix *pix);

  /**
   * Set the resolution of the source image in pixels per inch so font size
   * information can be calculated in results.  Call this after SetImage().
   * 以每英寸像素为单位设置源图像的分辨率，这样就可以在结果中计算字体大小信息。在SetImage()之后调用该函数。
   */
  void SetSourceResolution(int ppi);

  /**
   * Restrict recognition to a sub-rectangle of the image. Call after SetImage.
   * Each SetRectangle clears the recogntion results so multiple rectangles
   * can be recognized with the same image.
   * 将识别限制到图像的子矩形。SetImage后调用。
   * 每个SetRectangle都会清除识别结果，这样就可以用同一幅图像识别多个矩形。
   */
  void SetRectangle(int left, int top, int width, int height);

  /**
   * Get a copy of the internal thresholded image from Tesseract.
   * Caller takes ownership of the Pix and must pixDestroy it.
   * May be called any time after SetImage, or after TesseractRect.
   * 从Tesseract获取内部阈值图像的副本
   * 调用者取得的所有权，并必须pixDestroy它。可以在SetImage或TesseractRect之后的任何时间调用。
   */
  Pix *GetThresholdedImage();

  /**
   * Get the result of page layout analysis as a leptonica-style
   * Boxa, Pixa pair, in reading order.
   * Can be called before or after Recognize.
   * 得到的页面布局分析结果为leptonica-style的Boxa, Pixa对，按读取顺序排列。可以在识别之前或之后调用。
   */
  Boxa *GetRegions(Pixa **pixa);

  /**
   * Get the textlines as a leptonica-style
   * Boxa, Pixa pair, in reading order.
   * Can be called before or after Recognize.
   * If raw_image is true, then extract from the original image instead of the
   * thresholded image and pad by raw_padding pixels.
   * If blockids is not nullptr, the block-id of each line is also returned as
   * an array of one element per line. delete [] after use. If paraids is not
   * nullptr, the paragraph-id of each line within its block is also returned as
   * an array of one element per line. delete [] after use.
   *
   * 将文本行按阅读顺序排列为轻体型Boxa、Pixa对。
   * 可以在识别之前或之后调用。
   * 如果raw_image为真，则从原始图像中提取，而不是从分割（阈值）图像中提取，并通过raw_padding像素填充。
   * 如果blockids不是nullptr，则每行的block-id也会作为每行一个元素的数组返回。使用后通过delete[]释放。
   * 如果paraids不是nullptr，则块中每行的段落id也会作为每行一个元素的数组返回。使用后通过delete[]释放。
   */
  Boxa *GetTextlines(bool raw_image, int raw_padding, Pixa **pixa,
                     int **blockids, int **paraids);
  /*
   Helper method to extract from the thresholded image. (most common usage)
   辅助方法提取的分割（阈值）图像。(最常见的用法)
*/
  Boxa *GetTextlines(Pixa **pixa, int **blockids) {
    return GetTextlines(false, 0, pixa, blockids, nullptr);
  }

  /**
   * Get textlines and strips of image regions as a leptonica-style Boxa, Pixa
   * pair, in reading order. Enables downstream handling of non-rectangular
   * regions.
   * Can be called before or after Recognize.
   * If blockids is not nullptr, the block-id of each line is also returned as
   * an array of one element per line. delete [] after use.
   * 获得文本行和带状图像区域作为 leptonica-style 的Boxa, Pixa对，按阅读顺序。
   * 允许对非矩形区域进行下游处理。
   * 可以在识别之前或之后调用。
   * 如果blockids不是nullptr，则每行的block-id也会作为每行一个元素的数组返回。使用后通过delete[]释放。
   */
  Boxa *GetStrips(Pixa **pixa, int **blockids);

  /**
   * Get the words as a leptonica-style
   * Boxa, Pixa pair, in reading order.
   * Can be called before or after Recognize.
   * 把单词按阅读顺序排列成leptonica-style的Boxa, Pixa对。可以在识别之前或之后调用。
   */
  Boxa *GetWords(Pixa **pixa);

  /**
   * Gets the individual connected (text) components (created
   * after pages segmentation step, but before recognition)
   * as a leptonica-style Boxa, Pixa pair, in reading order.
   * Can be called before or after Recognize.
   * Note: the caller is responsible for calling boxaDestroy()
   * on the returned Boxa array and pixaDestroy() on cc array.
   * 获取单个连接(文本)组件(在页面分割步骤之后创建，但在识别之前创建)，
   * 作为leptonica-style的Boxa, Pixa对，按阅读顺序排列。
   * 可以在识别之前或之后调用。注意:调用者负责对返回的Boxa数组调用boxaDestroy()，对cc数组调用pixaDestroy()。
   */
  Boxa *GetConnectedComponents(Pixa **cc);

  /**
   * Get the given level kind of components (block, textline, word etc.) as a
   * leptonica-style Boxa, Pixa pair, in reading order.
   * Can be called before or after Recognize.
   * If blockids is not nullptr, the block-id of each component is also returned
   * as an array of one element per component. delete [] after use.
   * If blockids is not nullptr, the paragraph-id of each component with its
   * block is also returned as an array of one element per component. delete []
   * after use. If raw_image is true, then portions of the original image are
   * extracted instead of the thresholded image and padded with raw_padding. If
   * text_only is true, then only text components are returned.
   *
   * 获得给定级别的组件(块，文本行，单词等)，如leptonica-style的Boxa, Pixa对，按阅读顺序。
   * 可以在识别之前或之后调用。
   * 如果blockids不是nullptr，每个组件的block-id也会作为每个组件一个元素的数组返回。使用后删除[]。
   * 如果blockids不是nullptr，则每个组件的段落id及其block也会作为每个组件一个元素的数组返回。使用后删除[]。
   * 如果raw_image为真，则提取原始图像的一部分，而不是阈值图像，并用raw_padding填充。如果text_only为真，则只返回文本组件。
   */
  Boxa *GetComponentImages(PageIteratorLevel level, bool text_only,
                           bool raw_image, int raw_padding, Pixa **pixa,
                           int **blockids, int **paraids);
  // Helper function to get binary images with no padding (most common usage).
  //帮助函数获得没有填充的二进制图像(最常见的用法)。
  Boxa *GetComponentImages(const PageIteratorLevel level, const bool text_only,
                           Pixa **pixa, int **blockids) {
    return GetComponentImages(level, text_only, false, 0, pixa, blockids,
                              nullptr);
  }

  /**
   * Returns the scale factor of the thresholded image that would be returned by
   * GetThresholdedImage() and the various GetX() methods that call
   * GetComponentImages().
   * Returns 0 if no thresholder has been set.
   * 返回由GetThresholdedImage()和调用GetComponentImages()的各种GetX()方法返回的阈值图像的比例因子。如果未设置阈值，则返回0。
   */
  int GetThresholdedImageScaleFactor() const;

  /**
   * Runs page layout analysis in the mode set by SetPageSegMode.
   * May optionally be called prior to Recognize to get access to just
   * the page layout results. Returns an iterator to the results.
   * If merge_similar_words is true, words are combined where suitable for use
   * with a line recognizer. Use if you want to use AnalyseLayout to find the
   * textlines, and then want to process textline fragments with an external
   * line recognizer.
   * Returns nullptr on error or an empty page.
   * The returned iterator must be deleted after use.
   * WARNING! This class points to data held within the TessBaseAPI class, and
   * therefore can only be used while the TessBaseAPI class still exists and
   * has not been subjected to a call of Init, SetImage, Recognize, Clear, End
   * DetectOS, or anything else that changes the internal PAGE_RES.
   * 在SetPageSegMode设置的模式下运行页面布局分析。
   * 可以选择在Recognize之前调用，以只访问页面布局结果。
   * 返回结果的迭代器。如果merge_similar_words为真，单词将在适合与行识别器一起使用的地方组合。
   * 如果您希望使用AnalyseLayout查找文本行，然后希望使用外部行识别器处理文本行片段，则使用。
   * 如果出现错误或空白页，返回nullptr。
   * 返回的迭代器必须在使用后删除。
   * 警告!这个类指向保存在TessBaseAPI类中的数据，因此只能在TessBaseAPI类仍然存在并且没有被Init、SetImage、Recognize、Clear、End DetectOS或任何其他改变内部PAGE_RES的调用时使用。
   */
  PageIterator *AnalyseLayout();
  PageIterator *AnalyseLayout(bool merge_similar_words);

  /**
   * Recognize the image from SetAndThresholdImage, generating Tesseract
   * internal structures. Returns 0 on success.
   * Optional. The Get*Text functions below will call Recognize if needed.
   * After Recognize, the output is kept internally until the next SetImage.
   * 从SetAndThresholdImage中识别图像，生成Tesseract内部结构。成功时返回0。
   * 可选的。如果需要，下面的Get*Text函数将调用Recognize。
   * 在recognition之后，输出将在内部保存，直到下一个SetImage。
   *
   */
  int Recognize(ETEXT_DESC *monitor);

  /**
   * Methods to retrieve information after SetAndThresholdImage(),
   * Recognize() or TesseractRect(). (Recognize is called implicitly if needed.)
   * 在SetAndThresholdImage()、Recognize()或TesseractRect()之后检索信息的方法。(如果需要，则隐式调用Recognize。)
   */

  /**
   * Turns images into symbolic text.
   *
   * filename can point to a single image, a multi-page TIFF,
   * or a plain text list of image filenames.
   *
   * retry_config is useful for debugging. If not nullptr, you can fall
   * back to an alternate configuration if a page fails for some
   * reason.
   *
   * timeout_millisec terminates processing if any single page
   * takes too long. Set to 0 for unlimited time.
   *
   * renderer is responible for creating the output. For example,
   * use the TessTextRenderer if you want plaintext output, or
   * the TessPDFRender to produce searchable PDF.
   *
   * If tessedit_page_number is non-negative, will only process that
   * single page. Works for multi-page tiff file, or filelist.
   *
   * Returns true if successful, false on error.
   *
   * 将图像转换为符号文本。
   * filename可以指向单个图像、多页TIFF或图像文件名的纯文本列表。
   * Retry_config对于调试非常有用。如果不是nullptr，那么如果页面由于某种原因失败，您可以退回到备用配置。
   * 如果任何单个页面花费的时间太长，timeout_milliseconds将终止处理。设置为0表示无限时间。
   * Renderer负责创建输出。例如，如果您想要明文输出，可以使用TessTextRenderer，或者使用TessPDFRender来生成可搜索的PDF。
   * 如果tessedit_page_number是非负数，则只处理该单页。工作多页tiff文件，或文件列表。
   * 成功返回true，错误返回false。
   *
   */
  bool ProcessPages(const char *filename, const char *retry_config,
                    int timeout_millisec, TessResultRenderer *renderer);
  // Does the real work of ProcessPages.
  bool ProcessPagesInternal(const char *filename, const char *retry_config,
                            int timeout_millisec, TessResultRenderer *renderer);

  /**
   * Turn a single image into symbolic text.
   *
   * The pix is the image processed. filename and page_index are
   * metadata used by side-effect processes, such as reading a box
   * file or formatting as hOCR.
   *
   * See ProcessPages for descriptions of other parameters.
   * 将单个图像转换为符号文本。
   * pix就是处理后的图像。
   * filename和page_index是副作用处理使用的元数据，例如读取框文件或格式化为hOCR。
   * 有关其他参数的描述，请参见ProcessPages。
   */
  bool ProcessPage(Pix *pix, int page_index, const char *filename,
                   const char *retry_config, int timeout_millisec,
                   TessResultRenderer *renderer);

  /**
   * Get a reading-order iterator to the results of LayoutAnalysis and/or
   * Recognize. The returned iterator must be deleted after use.
   * WARNING! This class points to data held within the TessBaseAPI class, and
   * therefore can only be used while the TessBaseAPI class still exists and
   * has not been subjected to a call of Init, SetImage, Recognize, Clear, End
   * DetectOS, or anything else that changes the internal PAGE_RES.
   *
   * 获取LayoutAnalysis和/或Recognize结果的读取顺序迭代器。返回的迭代器必须在使用后删除。
   * 警告!这个类指向保存在TessBaseAPI类中的数据，因此只能在TessBaseAPI类仍然存在并且没有被Init、SetImage、Recognize、Clear、End DetectOS或任何其他改变内部PAGE_RES的调用时使用。
   */
  ResultIterator *GetIterator();

  /**
   * Get a mutable iterator to the results of LayoutAnalysis and/or Recognize.
   * The returned iterator must be deleted after use.
   * WARNING! This class points to data held within the TessBaseAPI class, and
   * therefore can only be used while the TessBaseAPI class still exists and
   * has not been subjected to a call of Init, SetImage, Recognize, Clear, End
   * DetectOS, or anything else that changes the internal PAGE_RES.
   *
   * 获取LayoutAnalysis和/或Recognize结果的可变迭代器。
   * 返回的迭代器必须在使用后删除。
   * 警告!这个类指向保存在TessBaseAPI类中的数据，因此只能在TessBaseAPI类仍然存在并且没有被Init、SetImage、Recognize、Clear、End DetectOS或任何其他改变内部PAGE_RES的调用时使用。
   */
  MutableIterator *GetMutableIterator();

  /**
   * The recognized text is returned as a char* which is coded
   * as UTF8 and must be freed with the delete [] operator.
   *
   * 被识别的文本返回为字符*，编码为UTF8，必须使用delete[]操作符释放。
   */
  char *GetUTF8Text();

  size_t GetNumberOfTables() const;

  /// Return the i-th table bounding box coordinates
  ///
  /// Gives the (top_left.x, top_left.y, bottom_right.x, bottom_right.y)
  /// coordinates of the i-th table.
  ///
  /// 返回第i个表边界框坐标
  ///给出了(top_left。x, top_left。y, bottom_right。X, bottom_right.y)第i表的坐标。
  std::tuple<int, int, int, int> GetTableBoundingBox(
      unsigned
          i ///< Index of the table, for upper limit \see GetNumberOfTables() 表的索引，上限\参见GetNumberOfTables()
  );

  /// Get bounding boxes of the rows of a table
  /// return values are (top_left.x, top_left.y, bottom_right.x, bottom_right.y)
  ///
  /// 获取表返回值行的边界框是(top_left。x, top_left。y, bottom_right。x, bottom_right.y)
  ///
  std::vector<std::tuple<int, int, int, int> > GetTableRows(
      unsigned
          i ///< Index of the table, for upper limit \see GetNumberOfTables()
  );

  /// Get bounding boxes of the cols of a table
  /// return values are (top_left.x, top_left.y, bottom_right.x, bottom_right.y)
  ///
  /// 获取表cols的边界框
  /// 返回值是(top_left。x, top_left。y, bottom_right。x, bottom_right.y)
  std::vector<std::tuple<int, int, int, int> > GetTableCols(
      unsigned
          i ///< Index of the table, for upper limit \see GetNumberOfTables()
  );

  /**
   * Make a HTML-formatted string with hOCR markup from the internal
   * data structures.
   * page_number is 0-based but will appear in the output as 1-based.
   * monitor can be used to
   *  cancel the recognition
   *  receive progress callbacks
   * Returned string must be freed with the delete [] operator.
   *
   * 从内部数据结构中制作一个带有hOCR标记的html格式字符串。
   * Page_number是基于0的，但在输出中将显示为基于1的。
   * monitor可以用来
   * 取消识别
   * 获得进步回调
   * 返回的字符串必须使用delete[]操作符释放。
   *
   */
  char *GetHOCRText(ETEXT_DESC *monitor, int page_number);

  /**
   * Make a HTML-formatted string with hOCR markup from the internal
   * data structures.
   * page_number is 0-based but will appear in the output as 1-based.
   * Returned string must be freed with the delete [] operator.
   *
   * 从内部数据结构中制作一个带有hOCR标记的html格式字符串。
   * Page_number是基于0的，但是在输出中将显示为基于1的。
   * 返回的字符串必须使用delete[]操作符释放。
   */
  char *GetHOCRText(int page_number);

  /**
   * Make an XML-formatted string with Alto markup from the internal
   * data structures.
   *
   * 从内部数据结构中生成带有Alto标记的xml格式字符串。
   */
  char *GetAltoText(ETEXT_DESC *monitor, int page_number);

  /**
   * Make an XML-formatted string with Alto markup from the internal
   * data structures.
   *
   * 从内部数据结构中生成带有Alto标记的xml格式字符串。
   */
  char *GetAltoText(int page_number);

  /**
   * Make a TSV-formatted string from the internal data structures.
   * page_number is 0-based but will appear in the output as 1-based.
   * Returned string must be freed with the delete [] operator.
   *
   *
   * 从内部数据结构生成tsv格式的字符串。
   * Page_number是基于0的，但是在输出中将显示为基于1的。
   * 返回的字符串必须使用delete[]操作符释放。
   *tsv 是Tab-separated values的缩写，是一种存储表格数据的简单文本格式。
   */
  char *GetTSVText(int page_number);

  /**
   * Make a box file for LSTM training from the internal data structures.
   * Constructs coordinates in the original image - not just the rectangle.
   * page_number is a 0-based page index that will appear in the box file.
   * Returned string must be freed with the delete [] operator.
   *
   * 根据内部数据结构制作一个用于LSTM训练的框文件。
   * 在原始图像中构造坐标-不仅仅是矩形。
   * Page_number是一个基于0的页索引，它将出现在框文件中。
   * 返回的字符串必须使用delete[]操作符释放。
   *
   * 长短期记忆网络（LSTM，Long Short-Term Memory）是一种时间循环神经网络，
   * 是为了解决一般的RNN（循环神经网络）存在的长期依赖问题而专门设计出来的，所有的RNN都具有一种重复神经网络模块的链式形式。
   * 在标准RNN中，这个重复的结构模块只有一个非常简单的结构，例如一个tanh层。
   */
  char *GetLSTMBoxText(int page_number);

  /**
   * The recognized text is returned as a char* which is coded in the same
   * format as a box file used in training.
   * Constructs coordinates in the original image - not just the rectangle.
   * page_number is a 0-based page index that will appear in the box file.
   * Returned string must be freed with the delete [] operator.
   *
   * 被识别的文本以char*的形式返回，它的编码格式与训练中使用的框文件相同。
   * 在原始图像中构造坐标-不仅仅是矩形。
   * Page_number是一个基于0的页索引，它将出现在框文件中。
   * 返回的字符串必须使用delete[]操作符释放。
   */
  char *GetBoxText(int page_number);

  /**
   * The recognized text is returned as a char* which is coded in the same
   * format as a WordStr box file used in training.
   * page_number is a 0-based page index that will appear in the box file.
   * Returned string must be freed with the delete [] operator.
   *
   * 被识别的文本以char*的形式返回，它的编码格式与训练中使用的WordStr框文件相同。
   * Page_number是一个基于0的页索引，它将出现在框文件中。
   * 返回的字符串必须使用delete[]操作符释放。
   */
  char *GetWordStrBoxText(int page_number);

  /**
   * The recognized text is returned as a char* which is coded
   * as UNLV format Latin-1 with specific reject and suspect codes.
   * Returned string must be freed with the delete [] operator.
   *
   * 识别的文本以char*的形式返回，它被编码为UNLV格式Latin-1，带有特定的拒绝和可疑代码。
   * 返回的字符串必须使用delete[]操作符释放。
   * Latin1是ISO-8859-1的别名，有些环境下写作Latin-1。
   * ISO-8859-1编码是单字节编码，向下兼容ASCII，其编码范围是0x00-0xFF，0x00-0x7F之间完全和ASCII一致，0x80-0x9F之间是控制字符，0xA0-0xFF之间是文字符号。
   */
  char *GetUNLVText();

  /**
   * Detect the orientation of the input image and apparent script (alphabet).
   * orient_deg is the detected clockwise rotation of the input image in degrees
   * (0, 90, 180, 270)
   * orient_conf is the confidence (15.0 is reasonably confident)
   * script_name is an ASCII string, the name of the script, e.g. "Latin"
   * script_conf is confidence level in the script
   * Returns true on success and writes values to each parameter as an output
   *
   * 检测输入图像和明显的脚本(字母)的方向。
   * Orient_deg是检测到的输入图像顺时针旋转的角度
   * (0,90, 180, 270)
   * Orient_conf为置信度(15.0为合理置信度)
   * script_name是一个ASCII字符串，脚本的名称。“拉丁”
   * Script_conf是脚本中的信任级别
   * 成功时返回true，并将值写入每个参数作为输出
   */
  bool DetectOrientationScript(int *orient_deg, float *orient_conf,
                               const char **script_name, float *script_conf);

  /**
   * The recognized text is returned as a char* which is coded
   * as UTF8 and must be freed with the delete [] operator.
   * page_number is a 0-based page index that will appear in the osd file.
   *
   * 被识别的文本以char*的形式返回，该char*被编码为UTF8，必须使用delete[]操作符释放。
   * Page_number是将出现在osd文件中的基于0的页索引。
   */
  char *GetOsdText(int page_number);

  /**
   * Returns the (average) confidence value between 0 and 100.
   * 返回0到100之间的(平均)置信值。
   */
  int MeanTextConf();
  /**
   * Returns all word confidences (between 0 and 100) in an array, terminated
   * by -1.  The calling function must delete [] after use.
   * The number of confidences should correspond to the number of space-
   * delimited words in GetUTF8Text.
   *
   * 返回以-1结束的数组中的所有单词置信度(0到100之间)。
   * 调用函数必须在使用后delete[]。
   * 置信度的数量应该对应于GetUTF8Text中空格分隔的单词的数量。
   */
  int *AllWordConfidences();

#ifndef DISABLED_LEGACY_ENGINE  //禁用遗留引擎
  /**
   * Applies the given word to the adaptive classifier if possible.
   * The word must be SPACE-DELIMITED UTF-8 - l i k e t h i s , so it can
   * tell the boundaries of the graphemes.
   * Assumes that SetImage/SetRectangle have been used to set the image
   * to the given word. The mode arg should be PSM_SINGLE_WORD or
   * PSM_CIRCLE_WORD, as that will be used to control layout analysis.
   * The currently set PageSegMode is preserved.
   * Returns false if adaption was not possible for some reason.
   *
   * 如果可能的话，将给定的单词应用于自适应分类器。
   * 该词必须是空格分隔的UTF-8 - l i k th i s，因此它可以告诉字素的边界。
   * 假设SetImage/SetRectangle已经被用来将图像设置为给定的单词。模式参数应该是PSM_SINGLE_WORD或PSM_CIRCLE_WORD，因为这将用于控制布局分析。
   * 当前设置的PageSegMode被保留。
   * 如果由于某种原因不能适应，则返回false。
   */
  bool AdaptToWordStr(PageSegMode mode, const char *wordstr);
#endif //  ndef DISABLED_LEGACY_ENGINE

  /**
   * Free up recognition results and any stored image data, without actually
   * freeing any recognition data that would be time-consuming to reload.
   * Afterwards, you must call SetImage or TesseractRect before doing
   * any Recognize or Get* operation.
   *
   * 释放识别结果和任何存储的图像数据，而不释放任何重新加载耗时的识别数据。
   * 然后，你必须在执行任何识别或获取*操作之前调用SetImage或TesseractRect。
   */
  void Clear();

  /**
   * Close down tesseract and free up all memory. End() is equivalent to
   * destructing and reconstructing your TessBaseAPI.
   * Once End() has been used, none of the other API functions may be used
   * other than Init and anything declared above it in the class definition.
   *
   * 关闭tesseract并释放所有内存。End()等价于解构和重构TessBaseAPI。
   * 一旦使用了End()，除了Init和类定义中在它上面声明的任何其他API函数都不能使用。
   */
  void End();

  /**
   * Clear any library-level memory caches.
   * There are a variety of expensive-to-load constant data structures (mostly
   * language dictionaries) that are cached globally -- surviving the Init()
   * and End() of individual TessBaseAPI's.  This function allows the clearing
   * of these caches.
   *
   * 清除任何库级内存缓存。
   * 有各种加载开销大的常量数据结构(主要是语言字典)被全局缓存——单独的TessBaseAPI的Init()和End()仍然存在。这个函数允许清除这些缓存。
   **/
  static void ClearPersistentCache();

  /**
   * Check whether a word is valid according to Tesseract's language model
   * @return 0 if the word is invalid, non-zero if valid.
   * @warning temporary! This function will be removed from here and placed
   * in a separate API at some future time.
   * 根据Tesseract的语言模型检查一个单词是否有效
   * @return 0表示无效，非0表示有效。
   * @warning 暂时!这个函数将从这里删除，并在将来的某个时候放在一个单独的API中。
   */
  int IsValidWord(const char *word) const;
  // Returns true if utf8_character is defined in the UniCharset.
  bool IsValidCharacter(const char *utf8_character) const;

  bool GetTextDirection(int *out_offset, float *out_slope);

  /**
   * Sets Dict::letter_is_okay_ function to point to the given function.
   * 设置Dict::letter_is_ok函数指向给定的函数。
   */
  void SetDictFunc(DictFunc f);

  /** Sets Dict::probability_in_context_ function to point to the given function.
   * 设置Dict::probability_in_context_ 函数指向给定的函数
   */
  void SetProbabilityInContextFunc(ProbabilityInContextFunc f);

  /**
   * Estimates the Orientation And Script of the image.
   * @return true if the image was processed successfully.
   *
   * 估计图像的方向和脚本。
   * @return 如果图像处理成功，则返回true。
   */
  bool DetectOS(OSResults *);

  /**
   * Return text orientation of each block as determined by an earlier run
   * of layout analysis.
   *
   * 返回由前一次布局分析确定的每个块的文本方向。
   */
  void GetBlockTextOrientations(int **block_orientation,
                                bool **vertical_writing);

  /**
   * This method returns the string form of the specified unichar.
   * 此方法返回指定unichar的字符串形式。
   */
  const char *GetUnichar(int unichar_id) const;

  /**
   * Return the pointer to the i-th dawg loaded into tesseract_ object.
   * 返回加载到tesseract_对象中的第i个dawg的指针。
   */
  const Dawg *GetDawg(int i) const;

  /**
   * Return the number of dawgs loaded into tesseract_ object.
   * 返回加载到tesseract_对象中的dawgs的数量。
   */
  int NumDawgs() const;

  Tesseract *tesseract() const {
    return tesseract_;
  }

  OcrEngineMode oem() const {
    return last_oem_requested_;
  }

  void set_min_orientation_margin(double margin);
  /* @} */

protected:
  /**
   * Common code for setting the image. Returns true if Init has been called.
   * 设置图像的常用代码。如果Init被调用，返回true。
   */
  bool InternalSetImage();

  /**
   * Run the thresholder to make the thresholded image. If pix is not nullptr,
   * the source is thresholded to pix instead of the internal IMAGE.
   *
   * 运行threshold命令生成分割图像。
   * 如果pix不是nullptr,源图像被分割为pix，而不是内部的IMAGE。
   */
  virtual bool Threshold(Pix **pix);

  /**
   * Find lines from the image making the BLOCK_LIST.
   * @return 0 on success.
   *
   * 从生成BLOCK_LIST的图像中找到行。
   * @return 0表示成功。
   */
  int FindLines();

  /**
   * Delete the pageres and block list ready for a new page.
   * 删除页面和阻止列表，为新页面做好准备。
   */
  void ClearResults();

  /**
   * Return an LTR Result Iterator -- used only for training, as we really want
   * to ignore all BiDi smarts at that point.
   * delete once you're done with it.
   *
   * 返回一个LTR结果迭代器——仅用于训练，因为我们真的想在这一点上忽略所有BiDi智能。
   * 一旦你用完它就删除。
   */
  LTRResultIterator *GetLTRIterator();

  /**
   * Return the length of the output text string, as UTF8, assuming
   * one newline per line and one per block, with a terminator,
   * and assuming a single character reject marker for each rejected character.
   * Also return the number of recognized blobs in blob_count.
   *
   * 返回输出文本字符串的长度，作为UTF8，假设每行一个换行符，每块一个换行符，并假设每个被拒绝的字符有一个字符拒绝标记。
   * 还返回blob_count中已识别的blob的数量。
   */
  int TextLength(int *blob_count) const;

  //// paragraphs.cpp ////////////////////////////////////////////////////
  void DetectParagraphs(bool after_text_recognition);

  const PAGE_RES *GetPageRes() const {
    return page_res_;
  }

protected:
  Tesseract *tesseract_;          ///< The underlying data object.底层数据对象。
  Tesseract *osd_tesseract_;      ///< For orientation & script detection.用于方向和脚本检测。
  EquationDetect *equ_detect_;    ///< The equation detector.方程探测器。
  FileReader reader_;             ///< Reads files from any filesystem.从任何文件系统读取文件。
  ImageThresholder *thresholder_; ///< Image thresholding module.图像分割模块。
  std::vector<ParagraphModel *> *paragraph_models_;
  BLOCK_LIST *block_list_;           ///< The page layout.页面布局。
  PAGE_RES *page_res_;               ///< The page-level data.页面等级的数据。
  std::string input_file_;           ///< Name used by training code.训练代码使用的名称。
  std::string output_file_;          ///< Name used by debug code.调试代码使用的名称。
  std::string datapath_;             ///< Current location of tessdata.识别文字库的当前位置。
  std::string language_;             ///< Last initialized language.最后一个初始化的语言。
  OcrEngineMode last_oem_requested_; ///< Last ocr language mode requested.请求的最后一个ocr语言模式。
  bool recognition_done_;            ///< page_res_ contains recognition data.Page_res_是否包含识别数据。

  /**
   * @defgroup ThresholderParams Thresholder Parameters  分割参数
   * Parameters saved from the Thresholder. Needed to rebuild coordinates.从分割器（阈值模块）保存的参数。需要用来重建坐标。
   */
  /* @{ */
  int rect_left_;
  int rect_top_;
  int rect_width_;
  int rect_height_;
  int image_width_;
  int image_height_;
  /* @} */

private:
  // A list of image filenames gets special consideration  需要特别考虑图像文件名列表
  bool ProcessPagesFileList(FILE *fp, std::string *buf,
                            const char *retry_config, int timeout_millisec,
                            TessResultRenderer *renderer,
                            int tessedit_page_number);
  // TIFF supports multipage so gets special consideration.  TIFF支持多页，因此需要特别考虑。
  bool ProcessPagesMultipageTiff(const unsigned char *data, size_t size,
                                 const char *filename, const char *retry_config,
                                 int timeout_millisec,
                                 TessResultRenderer *renderer,
                                 int tessedit_page_number);
}; // class TessBaseAPI.

/**
 * Escape a char string - remove &<>"' with HTML codes.
 * 转义一个字符字符串-删除&<>"'与HTML代码。
 */
std::string HOcrEscape(const char *text);

} // namespace tesseract

#endif // TESSERACT_API_BASEAPI_H_
