OBJS=main.o SDL_video_player.o
cc=g++
CFLAGS=-c

SDL_video_player:$(OBJS)
	@$(cc) -o zr $(OBJS) "-lSDL2"

main.o:main.cpp src/SDL_video_player.h
	@$(cc) $(CFLAGS) main.cpp "-lSDL2"

SDL_video_player.o : src/SDL_video_player.cpp src/SDL_video_player.h
	@$(cc) $(CFLAGS) src/SDL_video_player.cpp "-lSDL2"

.PHONY clean :
	@rm -f *.o 