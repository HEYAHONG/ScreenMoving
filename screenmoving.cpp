#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <stdlib.h>
#define time 200 //定义检测时间（单位：ms）
using namespace cv;
int main(int argc,char * argv[])
{
VideoCapture video;//打开视频
 if(argc <2) video.open(0);
 else {
	video.open(argv[1]);
	if(!video.isOpened()) video.open(atoi(argv[1]));
	else if(!video.isOpened()) {
					printf(" 打开视频失败\n");
					return 255;
					}
	}

Mat frame, curr, prev, curr64f, prev64f;
Point2d shift;//移动点保存
double  dis;// 距离变量
cv::namedWindow("video",cv::WINDOW_NORMAL); // 创建窗口
while(1)
	{
	video >> frame;
	
	cv::imshow("video",frame); // 显示读取的图像
	if(frame.empty()) {
			printf("视频读取失败\n");
			continue;
			}

	prev=curr.clone(); //保存以前的图像
	cvtColor(frame, curr, COLOR_RGB2GRAY);//转化为灰度图，保存当前图像。
	if(prev.empty()) continue;
	
	prev.convertTo(prev64f, CV_64F);//转化为phaseCorrelate需要的格式
        curr.convertTo(curr64f, CV_64F);
	
	shift = phaseCorrelate(prev64f, curr64f);//计算移动坐标
	dis  = cv::sqrt( shift.x*shift.x + shift.y*shift.y);// 计算移动距离
	waitKey(1);
	if(waitKey(time-1)==27) break;
	printf("x移动速度：%lf，y移动速度：%lf，移动速度：%lf \n",shift.x/time*1000,shift.y/time*1000,dis/time*1000);//输出移动速度( 像素/s)

	}


}
