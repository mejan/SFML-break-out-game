#include "bounceball.h"
#include <random>
#include <chrono>

bounceBall::bounceBall() : latestCollidedObject(0) {
	//loading Texture for the ball and sets it's possitions and origin.
	if(!bBTexture.loadFromFile("images/bounceboll.png")){
		std::cerr << "Failed loading bounce boll" << std::endl;
	}
	this->setTexture(bBTexture);
	this->setOrigin(originX, originY);
	this->setPosition(startPosX, startPosY);
	//seed random generator
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator (seed);
	if(generator()%2==0){//if generator gives even value.
		ballDirection.x = -0.3f;
	}else{
		ballDirection.x = 0.3f;
	}
	if(generator()%2==0){
		ballDirection.y = -0.3f;
	}else{
		ballDirection.y = 0.3f;
	}
}

bounceBall::~bounceBall(){}
//moving the ball with the frame time and it's direction/speed.
void bounceBall::movementOfBall(sf::Int32& update){
	this->move(ballDirection.x*update, ballDirection.y*update);
}
//if the ball goes lower then 800 px on y axel it's decleard dead.
bool bounceBall::checkIfDead(){
	sf::Vector2f yPos = this->getPosition();
	yPos.y += 10;
	if(yPos.y > deadBallPos){
		return true;
	}
	return false;
}
//to set direction and speed of ball on y axel.
void bounceBall::setBallDirectionY(float y){
	ballDirection.y = y;
}
//to set direction and speed of ball on x axel.
void bounceBall::setBallDirectionX(float x){
	ballDirection.x = x;
}
//gets the balls direction/speed on y axel.
double bounceBall::getBallDirectionY() const{
	return ballDirection.y;
}
//gets the ball direction/speed on x axel.
double bounceBall::getBallDirectionX() const{
	return ballDirection.x;
}
/**
*checks where and how the balls collides with a other object and desides
*the new direction/speed that it should have.
*/
bool bounceBall::shallCollideWith(sf::Sprite& s, sf::Int32 update) {
	//checks if the ball hits some object.
	sf::FloatRect Ball = this->getGlobalBounds();
	sf::FloatRect collObject = s.getGlobalBounds();
	if (Ball.intersects(collObject) && &s != this->latestCollidedObject){
		//Save reference
		this->latestCollidedObject = &s;

		//let o be the centrum of collObject.
		sf::Vector2f o = sf::Vector2f(collObject.left+collObject.width/2,collObject.top+collObject.height/2);
		//om will be a vector from o to center of the ball.
		sf::Vector2f om = sf::Vector2f(Ball.left+Ball.width/2-o.x, Ball.top+Ball.height/2-o.y);
		//scale down om to cub dimentions and think of the ball as a kub.
		om.x/=collObject.width;
		om.y/=collObject.height;

		//reflect the ball acordning to the angle of om.
		float angle=atan2(om.y,om.x);

		if ( angle >= M_PI/4 && angle <= 3*M_PI/4){ //hit on the bottom of object.
			this->setBallDirectionY( this->getBallDirectionY() * (-1) );//change direction/speed        
			float u = collObject.top + collObject.height - Ball.top;
			this->move(0, 0.2*u*update);
			return true;
		}

		if ( angle <= -M_PI/4 && angle >= -3*M_PI/4){ //hit on top of object.
			this->setBallDirectionY( this->getBallDirectionY() * (-1) );//change direction/speed
			float u = Ball.top + Ball.height - collObject.top;
			this->move(0,-0.2*u*update);
			return true;
		}

		if ( angle < -3*M_PI/4 || angle > 3*M_PI/4){ //hit right side of object.
			this->setBallDirectionX( this->getBallDirectionX() * (-1) );//change direction/speed
			float u = Ball.left + Ball.width - collObject.left;
			this->move(-0.2*u*update,0);
			return true;
		}

		if ( angle < M_PI/4 || angle > -M_PI/4){ //hit left side of object.
			this->setBallDirectionX( this->getBallDirectionX() * (-1) );//change direction/speed
			float u = collObject.left + collObject.width - Ball.left;
			this->move(0.2*u*update,0);
			return true;
		}
	}
	return false;
}