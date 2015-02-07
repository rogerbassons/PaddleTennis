//Copyright 2015 Roger Bassons
#include "Ball.h"
#include <cmath>
#include <random>

Ball::Ball() {
	b_.x = b_.y = b_.w = b_.h = 0;
	launchSpeed_ = 6;
	dx_ = launchSpeed_;
	dy_ = 0;
}

void Ball::setSize(int size) {
	b_.w = b_.h = size;
}

void Ball::setLaunchSpeed(int speed) {
	launchSpeed_ = speed;
}

int Ball::getX() const {
	return b_.x;
}

int Ball::getY() const {
	return b_.y;
}

int Ball::randomAngle(int min, int max) const {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(min,max);
	return dist(mt);
}

int Ball::randomDirection() const {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist1(0,1);
	int direction = dist1(mt);
	if (direction == 0)
		direction = -1;
	return direction;
}

void Ball::launch(int width, int height) {
	b_.x = width/2 - b_.w/2;
	b_.y = height/2 - b_.h;
	
	int angle = randomAngle(0,360);
	int direction = randomDirection();
	dx_ = direction * launchSpeed_ * cos(angle * M_PI/180.0);               
	dy_ = launchSpeed_ * sin(angle * M_PI/180.0);
	if (dx_ == 0)
		dx_ = launchSpeed_;
}

bool Ball::hasCollidedWithAnyPaddle(int width, int height, const Paddle &left, const Paddle &right) {
	bool collided = false;
	if (dx_ < 0 and b_.x < width/2) {
		if (b_.x >= left.getX() and b_.x <= left.getX() + left.getWidth()) {
			
			if (b_.y >= left.getY() and b_.y <= left.getY() + left.getHeight())
				collided = true;
			
			else if (b_.y + b_.h >= left.getY() and b_.y + b_.h <= left.getY() + left.getHeight())
				collided = true;
			
		}
	} else if (dx_ > 0 and b_.x > width/2) {
		if (b_.x + b_.w >= right.getX() and b_.x + b_.w <= right.getX() + right.getWidth()) {
			
			if (b_.y >= right.getY() and b_.y <= right.getY() + right.getHeight())
				collided = true;
			
			else if (b_.y + b_.h >= right.getY() and b_.y + b_.h <= right.getY() + right.getHeight())
				collided = true;
			
		}
	}
	return collided;
}

bool Ball::move(int width, int height, const Paddle &left, const Paddle &right, int &winner) {
	winner = -1;
	
	int nextX = b_.x + dx_;
	int nextY = b_.y + dy_;
	
	if (nextX > width) {
		winner = 1;
	} else if (nextX + b_.w < 0) {
		winner = 0;
	} else if (nextY < 0) {
		dy_ *= -1;
		nextY = 0;
	} else if (nextY + b_.h > height) {
		dy_ *= -1;
		nextY = height - b_.h;
	}
	
	b_.x = nextX;
	b_.y = nextY;

	bool collided = hasCollidedWithAnyPaddle(width,height,left,right);
	if (collided) {
		dx_ *= -1;
	}
	
	return collided;
}

void Ball::moreSpeed() {
	dx_++;
	dy_++;
}

void Ball::draw(SDL_Renderer *ren) const {
	SDL_SetRenderDrawColor(ren,255,255,255,255);
	SDL_RenderFillRect(ren,&b_);
}
	
