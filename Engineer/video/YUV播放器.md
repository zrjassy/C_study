[TOC]

# 视觉媒体通信：YUV格式原始视频的播放显示

姓名：张锐

学号：18010100420

## 一、技术原理

### 1、YUV数据存储格式

YUV，分为三个分量，“Y”表示明亮度，也就是灰度值；而“U”和“V” 表示的则是色度，作用是描述影像色彩及饱和度，用于指定像素的颜色。

YUV码流的主流的采样方式有三种，YUV4:4:4，YUV4:2:2，YUV4:2:0。读取以YUV形式保存的视频文件最重要的一点就是如何根据其采样格式来从码流中还原每个像素点的YUV值，因为只有正确地还原了每个像素点的YUV值，才能通过YUV与RGB的转换公式提取出每个像素点RGB值，然后显示出来。

* YUV 4:4:4采样，每一个Y对应一组UV分量。
* YUV 4:2:2采样，每两个Y共用一组UV分量。 
* YUV 4:2:0采样，每四个Y共用一组UV分量。  

很显然，YUV数据存储的优点就是可以压缩图片的数据量，节省内存。如使用YUV 4:2:0 的采样方式，一帧图像的数据大小为 height * width * 1.5 bit；而RGB数据则为height * width * 3 bit。

YUV按照存储格式的不同分为三类，平面，半平面和打包格式三种格式。其中本次实践视频所采用的`I420`就是一种平面格式。

平面的YUV格式，就是YUV三种分量分别单独的连续存储，不交叉。先连续存储所有像素点的Y，紧接着存储所有像素点的U，随后是所有像素点的V。

一帧图像的存储如下图所示：

![image-20210328160811259](/home/jassy/project/YUV.png) 

### 2、YUV与RGB的转换

转换公式如下：

```txt
 R = Y + 1.402 *（V-128）
 G = Y – 0.34414 *（U –128） – 0.71414 *（V –128）
 B = Y + 1.772 *（U – 128）
 
 Y = 0.299R + 0.587G + 0.114B
 U = -0.147R - 0.289G + 0.436B
 V = 0.615R - 0.515G - 0.100B
```

## 二、实现过程

本次作业采用了两种方式来实现YUV原始视频的播放显示

### 1、采用opencv库实现YUV原始视频的播放显示

编程环境：Python3.8，Pycharm2020

第三方库：cv2，numpy

#### （1）读取YUV原始视频数据，保存至数组中留待后续处理。

​	通过文件读取函数，先读取 H * W 大小的Y数据，再读取  H/2 * W/2 大小的U数据，最后再读取H/2 * W/2 大小的V数据。

```python
def readYUV(file, height, width, start_frame, fps):
    """
    :param file: 待处理 YUV 视频的名字
    :param height: YUV 视频中图像的高
    :param width: YUV 视频中图像的宽
    :param start_frame: 起始帧
    :param fps: 帧率
    :return: None
    """
    H = height
    W = width
    uv_H = H // 2
    uv_W = W // 2

    fp = open(file, 'rb')
    fp.seek(0, 2)  # 设置文件指针到文件流的尾部 + 偏移 0
    fp_end = fp.tell()  # 获取文件尾指针位置

    frame_size = height * width * 3 // 2  # 一帧图像所含的像素个数
    num_frame = fp_end // frame_size  # 计算 YUV 文件包含图像数
    print("This yuv file has {} frame images!".format(num_frame))
    fp.seek(frame_size * start_frame, 0)  # 设置文件指针到文件流的起始位置 + 偏移 frame_size * startframe

    Y = np.zeros((num_frame, H, W), np.uint8)
    U = np.zeros((num_frame, uv_H, uv_W), np.uint8)
    V = np.zeros((num_frame, uv_H, uv_W), np.uint8)

    # 从YUV文件中获取每一帧图像上每一个像素的YUV值
    for i in range(num_frame):
        for m in range(H):
            for n in range(W):
                Y[i, m, n] = ord(fp.read(1))
        for m in range(uv_H):
            for n in range(uv_W):
                U[i, m, n] = ord(fp.read(1))
        for m in range(uv_H):
            for n in range(uv_W):
                V[i, m, n] = ord(fp.read(1))
        print('读取第{}帧图像'.format(i + 1))
        
    image = []
    # 将YUV转换成RGB并播放
    for i in range(num_frame):
        # 通过yuv2rgb函数将YUV数据转换成RGB数据
        rgb = yuv2rgb(Y[i, :, :], U[i, :, :], V[i, :, :])
        image.append(rgb)
    for i in range(num_frame):
        # 显示
        cv2.imshow('test', image[i])
        # 当按下 Q 键时退出
        if cv2.waitKey(1) & 0xFF == ord('q'):
            cv2.destroyAllWindows()
            break
        # 保持 1/fps 秒
        time.sleep(1 / fps)
```

#### （2）YUV数据与RGB数据转换

```python
def yuv2rgb(y, u, v):
    """
    :param y: y分量
    :param u: u分量
    :param v: v分量
    :return: rgb格式数据
    """
    rows, cols = y.shape[:2]
    # 创建r,g,b分量
    r = np.zeros((rows, cols), np.uint8)
    g = np.zeros((rows, cols), np.uint8)
    b = np.zeros((rows, cols), np.uint8)

    for i in range(rows):
        for j in range(int(cols)):
            r[i, j] = max(0, min(255, y[i, j] + 1.402 * (v[i // 2, j // 2] - 128)))
            g[i, j] = max(0, min(255, y[i, j] - 0.34414 * (u[i // 2, j // 2] - 128) - 0.71414 * (v[i // 2, j // 2] - 128)))
            b[i, j] = max(0, min(255, y[i, j] + 1.772 * (u[i // 2, j // 2] - 128)))
    # cv2中显示图像数据是按照BＧR的顺序显示的，因此这里需要调整一下。
    rgb = cv2.merge([b, g, r])
    return rgb
```

#### （3）RGB图像显示

在`readYUV`函数的最后，将YUV转换成RGB数据并显示

```python
    image = []
    # 将YUV转换成RGB并播放
    for i in range(num_frame):
        # 通过yuv2rgb函数将YUV数据转换成RGB数据
        rgb = yuv2rgb(Y[i, :, :], U[i, :, :], V[i, :, :])
        image.append(rgb)
    for i in range(num_frame):
        # 显示
        cv2.imshow('test', image[i])
        # 当按下 Q 键时退出
        if cv2.waitKey(1) & 0xFF == ord('q'):
            cv2.destroyAllWindows()
            break
        # 保持 1/fps 秒
        time.sleep(1 / fps)
```

最终程序运行时发现，YUV与RGB数据之间的转换效率太低，需要花费很长的时间去进行。可以采用cv2的一个函数去快速转换。

```python
def yuv2rgb(y, u, v):
    """
    :param y: y分量
    :param u: u分量
    :param v: v分量
    :return: rgb格式数据
    """
	img = np.concatenate((y.reshape(-1), u.reshape(-1), v.reshape(-1)))
	img = img.reshape((height * 3 // 2, width)).astype('uint8')
    # 选择转换格式 COLOR_YUV2BGR_I420
	bgr_img = cv2.cvtColor(img, cv2.COLOR_YUV2BGR_I420)
```

### 2、采用SDL2库实现YUV原始视频的播放显示

编程环境：C++，VScode

第三方库：SDL2

#### （1）SDL使用流程

SDL_Init():初始化SDL系统
SDL_GreateWindow():创建窗口SDL_Window
SDL_GreateRenderer():创建渲染器SDL_Renderer
SDL_GreateTexture():创建纹理SDL_Texture
SDL_UpdateTexture():设置纹理的数据
SDL_RenderCopy():将纹理的数据拷贝给渲染器
SDL_RenderPresent():显示
SDL_Delay():工具函数，用于延时。
SDL_Quit():退出SDL系统

<img src="/home/jassy/project/SDL.png" alt="image-20210328165810260" style="zoom:50%;" /> 

#### （2）YUV播放显示实现

为了后续播放器的制作，我将SDL的使用封装成了一个对象以供后续使用。

定义SDL_video_player对象

```c++
class SDL_video_player
{
public:
    SDL_video_player(const char *file = NULL, int width = 0, int height = 0, int fps = 0);
    ~SDL_video_player();
    SDL_Thread *timer_thread; // 请求刷新线程
    void video_play();

private:
    // SDL
    SDL_Event event;        // 事件
    SDL_Rect rect;          // 矩形
    SDL_Window *window;     // 窗口
    SDL_Renderer *renderer; // 渲染
    SDL_Texture *texture;   // 纹理
    uint32_t pixformat;     // YUV420P，即是SDL_PIXELFORMAT_IYUV

    // 分辨率
    // 1. YUV的分辨率
    int video_width;
    int video_height;
    // 2.显示窗口的分辨率
    int win_width;
    int win_height;
    static int fps;

    // YUV文件句柄
    FILE *video_fd;
    const char *yuv_path;
	
    // 初始化SDL组件函数
    void SDL_init();
    // 退出标志 = 1则退出
    static int s_thread_exit;
    static int refresh_video_timer(void *data);

    //读取数据后先把放到buffer里面
    size_t video_buff_len;
    uint8_t *video_buf;

    // 一帧数据大小
    uint32_t yuv_frame_len;
    /* data */
};

```

*　在`SDL_init()`函数中完成SDL各个组件的声明初始化操作；
* 在`video_play()`函数中读取YUV文件并播放。
* 在`refresh_video_timer()`函数中完成刷新操作和帧率控制

```c++
void SDL_video_player::SDL_init()
{
    //创建窗口
    window = SDL_CreateWindow("YUV Player",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              video_width,
                              video_height,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        fprintf(stderr, "SDL: could not create window, err:%s\n", SDL_GetError());
    }
    // 基于窗口创建渲染器
    renderer = SDL_CreateRenderer(window, -1, 0);
    // 基于渲染器创建纹理
    texture = SDL_CreateTexture(renderer,
                                pixformat,
                                SDL_TEXTUREACCESS_STREAMING,
                                video_width,
                                video_height);
    // 分配空间
    video_buf = (uint8_t *)malloc(yuv_frame_len);
    if (!video_buf)
    {
        fprintf(stderr, "Failed to alloce yuv frame space!\n");
    }
    // 打开YUV文件
    video_fd = fopen(yuv_path, "rb");
    if (!video_fd)
    {
        fprintf(stderr, "Failed to open yuv file\n");
    }
}

int SDL_video_player::refresh_video_timer(void *data)
{
    while (!s_thread_exit)
    {
        //处理每帧数据
        SDL_Event event;
        event.type = REFRESH_EVENT;
        SDL_PushEvent(&event);
        // 帧率控制
        SDL_Delay(floor(1000 / fps));
    }
    s_thread_exit = 0;
    //push quit event
    SDL_Event event;
    event.type = QUIT_EVENT;
    SDL_PushEvent(&event);
    return 0;
}

void SDL_video_player::video_play()
{
    timer_thread = SDL_CreateThread(refresh_video_timer, NULL, NULL);
    while (1)
    {
        // 收取SDL系统里面的事件
        SDL_WaitEvent(&event);

        if (event.type == REFRESH_EVENT) // 画面刷新事件
        {
            video_buff_len = fread(video_buf, 1, yuv_frame_len, video_fd);
            if (video_buff_len <= 0)
            {
                fprintf(stderr, "Failed to read data from yuv file!\n");
                s_thread_exit = 1;
            }
            // 设置纹理的数据 video_width = 320， plane
            // 此处的video_width与文件存储格式有关
            SDL_UpdateTexture(texture, NULL, video_buf, video_width);
            // 显示区域，可以通过修改w和h进行缩放
            rect.x = 0;
            rect.y = 0;
            float w_ratio = win_width * 1.0 / video_width;
            float h_ratio = win_height * 1.0 / video_height;
            // 320x240 怎么保持原视频的宽高比例
            rect.w = video_width * w_ratio;
            rect.h = video_height * h_ratio;
            // 清除当前显示
            SDL_RenderClear(renderer);
            // 将纹理的数据拷贝给渲染器
            SDL_RenderCopy(renderer, texture, NULL, &rect);
            // 显示
            SDL_RenderPresent(renderer);
        }
        else if (event.type == SDL_WINDOWEVENT)
        {
            //If Resize
            SDL_GetWindowSize(window, &win_width, &win_height);
            printf("SDL_WINDOWEVENT win_width:%d, win_height:%d\n", win_width,
                   win_height);
        }
        else if (event.type == SDL_QUIT) //退出事件
            s_thread_exit = 1;
        else if (event.type == QUIT_EVENT)
            break;
    }  
}
```

## 三、实现结果

### 1、采用opencv库实现YUV原始视频的播放显示

<img src="/home/jassy/project/a.png" alt="2021-03-28 16-53-19 的屏幕截图" style="zoom:50%;" />  <img src="/home/jassy/project/b.png" alt="2021-03-28 16-53-21 的屏幕截图" style="zoom:50%;" />

### 2、采用SDL2库实现YUV原始视频的播放显示

(采用另外的YUV文件)

### <img src="/home/jassy/project/d.png" alt="2021-03-28 17-21-09 的屏幕截图" style="zoom:50%;" /><img src="/home/jassy/project/c.png" alt="2021-03-28 17-19-28 的屏幕截图" style="zoom:50%;" />

## 四、总结

第一次大作业完成了播放YUV文件的操作，为后续播放其他类型视频做基础。由于YUV文件的存储格式有很多种，因此后续我还需要继续更改完善`SDL_video_player`模块，为后续使用ffmpeg解码做准备。