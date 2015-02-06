main: main.o Game.o Ball.o Paddle.o
	g++ -o PaddleTennis -Wall -lSDL2 -lSDL2_image main.o Game.o Ball.o Paddle.o

main.o: main.cpp
	g++ -c main.cpp

Game.o: Game.cpp
	g++ -c Game.cpp

Ball.o: Ball.cpp
	g++ -c -std=c++11 Ball.cpp

Paddle.o: Paddle.cpp
	g++ -c Paddle.cpp

clean:
	rm *.o && rm PaddleTennis


