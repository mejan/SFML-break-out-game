/**
*bounceBall class the ball movement functions.
*
*this is the class for a ball that can change the direktion.
*and is supose to always be moving.
*/
#ifndef _BOUNCE_BOLL_H_
#define _BOUNCE_BOLL_H_

#include <SFML/Graphics.hpp>
#include <iostream> //for cess massages.
#include <math.h> //for M_PI and atan2()

class bounceBall: public sf::Sprite{ //public relation to sprite in SFML.
	public:
		/**
		*Constructor that loads texture to the ball set it's origin
		*and start position.
		*and randomly chose 1 of four start directions.
		*/
		bounceBall();
		/**
		*do not have a function just there for show.
		*/
		~bounceBall();
		/**
		*moves the ball, with a clock to make it smother.
		*/
		void movementOfBall(sf::Int32& update);
		/**
		*returns that the ball is dead if it's under the window.
		*returns true if ball 800 px from window top.
		*returns false if above.
		*/
		bool checkIfDead();
		/**
		*change the Y axel direction/speed of ball with this function
		*Input float.
		*/
		void setBallDirectionY(float y);
		/**
		*change the X axel direction/speed of ball with this function
		*Input float.
		*/
		void setBallDirectionX(float x);
		/**
		*retruns the Y axel direction/speed.
		*/
		double getBallDirectionY() const;
		/**
		*returns the X axel direction/speed.
		*/
		double getBallDirectionX() const;
		/**
		*Input sprite, if ball collide with sprite it will bounce on it.
		*and return true.
		*else return false and continue in old direction/speed.
		*/
		bool shallCollideWith(sf::Sprite& s, sf::Int32 update);

	private:
		//makes code easyer to read.
		static const short int startPosX = 600;
		static const short int startPosY = 400;
		static const short int originX = 10;
		static const short int originY = 10;
		static const short int deadBallPos = 800;

		//member Objects.
		sf::Texture bBTexture;
		sf::Vector2f ballDirection;
		sf::Sprite* latestCollidedObject;
};

#endif /*_BOUNCE_BOLL_H_*/