#ifndef __SDL_VIDEO_PLAYER_H__
#define __SDL_VIDEO_PLAYER_H__

#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <SDL2/SDL.h>
#ifdef __cplusplus
};
#endif

//自定义消息类型
#define REFRESH_EVENT (SDL_USEREVENT + 1) // 请求画面刷新事件
#define QUIT_EVENT (SDL_USEREVENT + 2)    // 退出事件

//定义YUV格式
#define YUV_FORMAT SDL_PIXELFORMAT_IYUV

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

    void SDL_init();
    // 退出标志 = 1则退出
    static int s_thread_exit;
    static int refresh_video_timer(void *data);

    //读取数据后先把放到buffer里面
    size_t video_buff_len;
    uint8_t *video_buf;

    // 测试的文件是YUV420P格式
    uint32_t yuv_frame_len;
    /* data */
};

#endif