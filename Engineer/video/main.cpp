#include <iostream>
#include "src/SDL_video_player.h"

using namespace std;

int main(int argc, char *argv[])
{
    const char *file = "header/test_out.yuv";
    SDL_video_player player(file, 1000, 562, 24);
    player.video_play();
    return 0;
}