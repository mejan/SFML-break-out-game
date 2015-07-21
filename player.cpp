#include "player.h"


player::player(){
	//try to load texture, sets origin, lifes position and right left bool value to 0.
	if(!pTexture.loadFromFile("images/player.png")){
		std::cerr << "Failed to load Player texture" << std::endl;
	}
	this->setTexture(pTexture);
	this->setOrigin(originX ,originY);
	moveState.left = 0;
	moveState.right = 0;
	lifes = 3;
	this->setPosition(startPositionX, startPositionY);
}

player::~player(){}
//sets the left bool value in the struct.
void player::setLeft(bool L){
	moveState.left = L;
}
//sets the right bool value in the struct.
void player::setRight(bool R){
	moveState.right = R;
}
//moves the player pad to the left with 1.2 pixels,
//and check so it does not go to far.
void player::moveLeft() {
	sf::Vector2f currentPos = this->getPosition();
	if(currentPos.x >= maxLeft){
		this->move(-1.2f, 0.f);
	}
}
//moves the player pad to right with 1.2 pixels,
//and check so it does not go to far.
void player::moveRight() {
	sf::Vector2f currentPos = this->getPosition();
	if(currentPos.x <= maxRight){
		this->move(1.2f, 0.f);
	}
}
//gets the struct left value.
bool player::getLeft() const{
	return moveState.left;
}
//gets the struct right value.
bool player::getRight() const{
	return moveState.right;
}
//returns the players lifes (extra lifes).
short int player::getLife() const{
	return lifes;
}
//decreas the players extra lifes with one.
void player::loseLife(){
	if( lifes > -1 ){
		lifes--;
	}
}