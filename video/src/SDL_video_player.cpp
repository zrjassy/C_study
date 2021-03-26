#include <iostream>
#include "SDL_video_player.h"

int SDL_video_player::s_thread_exit=0; 

SDL_video_player::SDL_video_player(const char *file, int width, int height, int fps)
{
    window = NULL;                    // 窗口
    renderer = NULL;                  // 渲染
    texture = NULL;                   // 纹理
    timer_thread = NULL;              // 请求刷新线程
    pixformat = SDL_PIXELFORMAT_IYUV; // YUV420P，即是SDL_PIXELFORMAT_IYUV

    // 分辨率
    // 1. YUV的分辨率
    video_width = width;
    video_height = height;
    // 2.显示窗口的分辨率
    win_width = width;
    win_height = height;

    // YUV文件句柄
    video_fd = NULL;
    yuv_path = file;
    SCREEN_FPS = fps;
    SCREEN_TICKS_PER_FRAME = 1000 / fps;

    video_buff_len = 0;
    video_buf = NULL;

    // 测试的文件是YUV420P格式
    y_frame_len = video_width * video_height;
    u_frame_len = video_width * video_height / 4;
    v_frame_len = video_width * video_height / 4;
    yuv_frame_len = y_frame_len + u_frame_len + v_frame_len;

    // s_thread_exit = 0; // 退出标志 = 1则退出

    SDL_init();
}

SDL_video_player::~SDL_video_player()
{
    if (video_buf)
        free(video_buf);
    if (video_fd)
        fclose(video_fd);
    if (texture)
        SDL_DestroyTexture(texture);
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);

    SDL_Quit();
}

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
    // // // 创建请求刷新线程
    // timer_thread = SDL_CreateThread(refresh_video_timer,
    //                                 NULL,
    //                                 NULL);
}

int SDL_video_player::refresh_video_timer(void *data)
{
    while (!s_thread_exit)
    {
		//处理每帧数据
        SDL_Event event;
        event.type = REFRESH_EVENT;
        SDL_PushEvent(&event);
        SDL_Delay(floor(1000/50));
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
    timer_thread = SDL_CreateThread(refresh_video_timer,
                                    NULL,
                                    NULL);
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
        {
            s_thread_exit = 1;
        }
        else if (event.type == QUIT_EVENT)
        {
            break;
        }
    }
}