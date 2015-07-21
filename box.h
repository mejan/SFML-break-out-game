/**
*the box object
*
*this is the class the player should destroy.
*/

#ifndef _BOX_H_
#define _BOX_H_

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class box: public sf::Sprite{//public relation to Sprite.
	public:
		/**
		*default constructor loads a texture
		*and sets the origin.
		*sets health to 1.
		*/
		box();
		/**
		*constructor that takes input as where it should load the texture from
		*and how mutch health the box should have.
		*/
		box(std::string txt, int h);
		//just for show destroctor.
		~box();
		/**
		*returns the current health of the box.
		*/
		int getLife() const;
		/**
		*lessens the health of the box with 1.
		*/
		void loseLife();


	private:
		//members that makes it easyer to read the code.
		static const short int originX = 35;
		static const short int originY = 15;

		int hp; //box health points
		sf::Texture bTexture; //the texture of the box.
};

#endif /*_BOX_H_*/