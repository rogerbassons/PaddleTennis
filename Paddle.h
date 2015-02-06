//Copyright 2015 Roger Bassons
#include <SDL2/SDL.h>

class Paddle {
 public:
	Paddle();
	void setSize(int width, int height);
	void setPosition(int x, int y);
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;

	void accelerateUp();
	void accelerateDown();
	void stop();
	void move(int max);
	
	void draw(SDL_Renderer *ren) const;

 private:
	SDL_Rect p_;
	int move_,speed_;
};
	
