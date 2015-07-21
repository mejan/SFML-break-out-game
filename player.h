#ifndef PLAYER_H_
#define PLAYER_H_
/**
*Player class, this is the pad the player controlls.
*
*here is how it moves and extra life implementation.
*/
#include <SFML/Graphics.hpp>
#include <iostream>

class player: public sf::Sprite {
public:
	/**
	*default constructor, sets a texture, orgin and position of the player pad.
	*also names how many extra lifes the user has.
	*/
	player();
	//destructor just for show.
	~player();
	/**
	*gets the bool value if it should move left.
	*/
	bool getLeft() const;
	/**
	*gets the bool value if it should move right.
	*/
	bool getRight() const;
	/**
	*sets bool value of left move.
	*/
	void setLeft(bool L);
	/**
	*sets bool value of right move.
	*/
	void setRight(bool R);
	/**
	*moves player pad to the left. Has a max see maxLeft for max left value.
	*/
	void moveLeft();
	/**
	*moves player pad to the right. Has a max see maxRight for the max right value.
	*/
	void moveRight();
	/**
	*return have many extra lifes the player has.
	*/
	short int getLife() const;
	/**
	*decreas the life of the player with 1.
	*/
	void loseLife();

private:
	static const short int startPositionX = 600;
	static const short int startPositionY = 785;
	static const short int originX = 50;
	static const short int originY = 15;
	static const short int maxLeft = -25;
	static const short int maxRight = 1225;
	//struct to keep left and right bool value.
	struct state{
		bool left;
		bool right;
	} moveState;
	//member to keep check on extra lifes.
	short int lifes;
	//texture object.
	sf::Texture pTexture;

};
#endif /* PLAYER_H_ */