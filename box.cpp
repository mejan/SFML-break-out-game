#include "box.h"

box::box():hp(1){
	//try to load texture and set it.
	if(!bTexture.loadFromFile("images/orgBox.png")){
		std::cerr << "Failed to load standard box texture" << std::endl;
	}
	this->setTexture(bTexture);
	//set the origin on the box.
	this->setOrigin(originX, originY);
}

box::box(std::string txt, int h):hp(h){
	//try and load a texture, then sets it and sets the origin.
	if(!bTexture.loadFromFile(txt)){
		std::cerr << "Failed loading box texture" << std::endl;
	}
	this->setTexture(bTexture);
	this->setOrigin(originX, originY);
}

box::~box(){}

//return private member hp (health points).
int box::getLife() const{
	return hp;
}

//if hp is bigger then 0 lessen it with 1.
void box::loseLife(){
	if(hp>0){
		hp--;
	}
}