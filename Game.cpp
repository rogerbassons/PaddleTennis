//Copyright 2015 Roger Bassons
#include "Game.h"

Game::Game() {
	bounces_ = 0;
	end_ = false;
	
	win_ = NULL;
	ren_ = NULL;

	screenWidth_ = 1024;
	screenHeight_ = 768;
	ballSize_ = 15;

	ball_.setSize(ballSize_); 
	ball_.launch(screenWidth_,screenHeight_);

	padWidth_ = 20;
	int padHeight = 100;
	p1_.setSize(padWidth_,padHeight);
	p2_.setSize(padWidth_,padHeight);

	int x,y;
	y = screenHeight_/2-padHeight/2;
	x = screenWidth_-padWidth_-5;
	p1_.setPosition(x,y);

	x = 5;
	p2_.setPosition(x,y);

	onePlayer_ = true;
}

Game::~Game() {
	if (ren_ != NULL) 
		SDL_DestroyRenderer(ren_);
	if (win_ != NULL) 
		SDL_DestroyWindow(win_);
}

void Game::initVideo() {
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		throw SDL_GetError();

	win_ = SDL_CreateWindow("Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,screenWidth_,screenHeight_,SDL_WINDOW_SHOWN);
	if (win_ == NULL) {
		SDL_Quit();
		throw SDL_GetError();
	}

	ren_ = SDL_CreateRenderer(win_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren_ == NULL) {
		SDL_DestroyWindow(win_);
		SDL_Quit();
		throw SDL_GetError();
	}

}

bool Game::isEnded() const {
	return end_;
}

void Game::play() {
	getUserInput();
	updateGame();
}

void Game::getUserInput() {
	SDL_Event e;
	while(SDL_PollEvent(&e) != 0 ) {
		if (e.type == SDL_QUIT)
			end_ = true;
		else if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_ESCAPE) 
				end_ = true;
			else if (e.key.keysym.sym == SDLK_UP)
				p1_.accelerateUp();
			else if (e.key.keysym.sym == SDLK_DOWN)
				p1_.accelerateDown();
			else if (not onePlayer_ and e.key.keysym.sym == SDLK_w)
				p2_.accelerateUp();
			else if (not onePlayer_ and e.key.keysym.sym == SDLK_s)
				p2_.accelerateDown();
			else if (e.key.keysym.sym == SDLK_1)
				onePlayer_ = not onePlayer_;
		} else if (e.type == SDL_KEYUP) {
			if (e.key.keysym.sym == SDLK_UP)
				p1_.stop();
			else if (e.key.keysym.sym == SDLK_DOWN)
				p1_.stop();
			else if (not onePlayer_ and e.key.keysym.sym == SDLK_w)
				p2_.stop();
			else if (not onePlayer_ and e.key.keysym.sym == SDLK_s)
				p2_.stop();
		}
	}
}

void Game::moveAutomaticallyP2() {
	int paddleY = p2_.getY();
	int ballY = ball_.getY();
	if (ballY > paddleY+padWidth_)
		p2_.accelerateDown();
	else if (ballY < paddleY-padWidth_)
		p2_.accelerateUp();
	else
		p2_.stop();
}

void Game::updateGame() {
	if (onePlayer_) 
		moveAutomaticallyP2();

	p2_.move(screenHeight_);
	p1_.move(screenHeight_);


	int winner;
	bool collided = ball_.move(screenWidth_,screenHeight_,p2_,p1_,winner);
	if (collided)
		bounces_++;

	if (winner == 0 or winner == 1) {
		bounces_ = 0;
		ball_.launch(screenWidth_,screenHeight_);
	} else if (bounces_ == 10) {
		bounces_ = 0;
		ball_.moreSpeed();
	}
}

void Game::show() {
	SDL_SetRenderDrawColor(ren_,0,0,0,255);
	SDL_RenderClear(ren_);
	
	SDL_SetRenderDrawColor(ren_,255,255,255,255);
	SDL_RenderDrawLine(ren_,screenWidth_/2,0,screenWidth_/2,screenHeight_);
	
	ball_.draw(ren_);
	p1_.draw(ren_);
	p2_.draw(ren_);
	
	SDL_RenderPresent(ren_);
}
