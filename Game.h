//Copyright 2015 Roger Bassons
#include <SDL2/SDL.h>
#include "Ball.h"

class Game {
 public:
	Game();
	~Game();

	void initVideo();
	void play();
	void show();

	bool isEnded() const;
 private:
	unsigned int screenWidth_;
	unsigned int screenHeight_;
	
	SDL_Window *win_;
	SDL_Renderer *ren_;

	bool end_;
	bool onePlayer_;

	Ball ball_;
	int ballSize_; // ball is square
	
	Paddle p1_,p2_;

	unsigned int bounces_;

	void getUserInput();
	void updateGame();

	int padHeight_;
	void moveAutomaticallyP2();
};
	
	
