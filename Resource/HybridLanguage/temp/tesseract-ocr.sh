
#!/bin/bash
apps=(
    tesseract
)
echo "正在识别ThresholdImage_p1.png"
date +"%Y-%m-%d %H:%M:%S:%N"
tesseract ./ThresholdImage_p1.png ./p1_result -l chi_sim+eng
date +"%Y-%m-%d %H:%M:%S:%N"

echo "正在识别ThresholdImage_p2.png"
date +"%Y-%m-%d %H:%M:%S:%N"
tesseract ./ThresholdImage_p2.png ./p2_result -l chi_sim+eng
date +"%Y-%m-%d %H:%M:%S:%N"

echo "正在识别ThresholdImage_p3.png"
date +"%Y-%m-%d %H:%M:%S:%N"
tesseract ./ThresholdImage_p3.png ./p3_result -l chi_sim+eng
date +"%Y-%m-%d %H:%M:%S:%N"

echo "正在识别ThresholdImage_p4.png" 
date +"%Y-%m-%d %H:%M:%S:%N"
tesseract ./ThresholdImage_p4.png ./p4_result -l chi_sim+eng
date +"%Y-%m-%d %H:%M:%S:%N"