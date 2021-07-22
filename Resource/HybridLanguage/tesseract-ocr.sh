
#!/bin/bash
apps=(
    tesseract
)
echo "正在识别picture1.png"
date +"%Y-%m-%d %H:%M:%S:%N"
tesseract ./picture1.png ./Result_Original/p1_result -l chi_sim+eng
date +"%Y-%m-%d %H:%M:%S:%N"

echo "正在识别picture2.png"
date +"%Y-%m-%d %H:%M:%S:%N"
tesseract ./picture2.png ./Result_Original/p2_result -l chi_sim+eng
date +"%Y-%m-%d %H:%M:%S:%N"

echo "正在识别picture3.png"
date +"%Y-%m-%d %H:%M:%S:%N"
tesseract ./picture3.png ./Result_Original/p3_result -l chi_sim+eng
date +"%Y-%m-%d %H:%M:%S:%N"

echo "正在识别picture4.png" 
date +"%Y-%m-%d %H:%M:%S:%N"
tesseract ./picture4.png ./Result_Original/p4_result -l chi_sim+eng
date +"%Y-%m-%d %H:%M:%S:%N"