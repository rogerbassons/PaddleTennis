//Copyright 2015 Roger Bassons
#include <SDL2/SDL.h>
#include "Paddle.h"

class Ball {
 public:
	Ball();
	void setSize(int size);
	void setPosition(int x, int y);

	// move inside rectangle width*height
	bool move(int width, int height, const Paddle &left, const Paddle &right);
	void moreSpeed();
	
	
	void draw(SDL_Renderer *ren) const;

 private:
	SDL_Rect b_;
	int speed_;
	int dx_,dy_;
};
	
