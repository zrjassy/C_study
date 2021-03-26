#include <iostream>
#include "src/SDL_video_player.h"

using namespace std;

int main(int argc, char *argv[])
{
    const char *file = "resources/BasketballDrill_832x480_50.yuv";
    SDL_video_player player(file, 832, 480, 50);
    player.video_play();
    return 0;
}