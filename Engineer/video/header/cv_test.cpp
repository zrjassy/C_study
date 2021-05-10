#include<opencv2/opencv.hpp>

using namespace cv; //命名程序存储空间
int main(){
	VideoCapture capture(0);//调用摄像头
	while(1){
	Mat frame;
	capture>>frame;//读取当前帧
	imshow("摄像头视频", frame);//显式当前帧
	waitKey(30);//控制每秒钟播放帧数
	}
}
