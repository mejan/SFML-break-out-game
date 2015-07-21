#include "gui.h"
//sets show meny to 1
gui::gui():showMeny(1){
	//sets the diffrent text objects.
	if(!backGround.loadFromFile("images/meny.png")){
		std::cerr << "Failed to load Player texture" << std::endl;
	}
	this->setTexture(backGround);
	
	choices.marktedOnMeny = 1;
	choices.choiceDone = 0;

	font.loadFromFile("images/Halo.ttf");
	
	start.setFont(font);
	start.setColor(sf::Color::Yellow);
	start.setCharacterSize(textSize);
	start.setPosition(startPosX, startPosY);
	start.setString("Start");

	quit.setFont(font);
	quit.setColor(sf::Color::Red);
	quit.setCharacterSize(textSize);
	quit.setPosition(quitPosX, quitPosY);
	quit.setString("Quit");

	GameOver.setFont(font);
	GameOver.setColor(sf::Color::Red);
	GameOver.setCharacterSize(textSize);
	GameOver.setPosition(winLosePosX, winLosePosY);
	GameOver.setString("Game Over");

	win.setFont(font);
	win.setColor(sf::Color::Yellow);
	win.setCharacterSize(textSize);
	win.setPosition(winLosePosX, winLosePosY);
	win.setString("Winning!");

	//moving speed and direction for the text(win and gameover).
	movingText.y = 0.3f;
	movingText.x = 0.f;
}

gui::~gui(){}
//sets colors for when texts objects is marked.
void gui::guiUpdate(){
	if(choices.marktedOnMeny){
		start.setColor(sf::Color::Yellow);
		quit.setColor(sf::Color::Red);
	}else{
		start.setColor(sf::Color::Red);
		quit.setColor(sf::Color::Yellow);
	}
}
//sets what is markted on the meny of the text objects.
void gui::setMarktedOnMeny(bool markted){
	choices.marktedOnMeny = markted;
}
//this says that the users or program has made it's choice.
void gui::setChoiceDone(){
	choices.choiceDone = 1;
}

//when the player loses this make a text object
//with the text "game over" fall down and then go to the meny again.
void gui::gameOver(sf::Int32& update){
	GameOver.move(movingText.x, movingText.y*update);
	sf::Vector2f tmp = GameOver.getPosition();
	if(tmp.y >= moveDone){ //when the text is in the right possition.
		showMeny = 1; //set showMeny to true
		choices.choiceDone = 0;//and set choiceDone to false.
		GameOver.setPosition(winLosePosX, winLosePosY); //reset the possition of the gameover text.
	}
}
//when the player wins this make a text object to fall down
//with the text winning! and go back to meny again.
void gui::winner(sf::Int32& update){
	win.move(movingText.x, movingText.y*update);
	sf::Vector2f tmp = win.getPosition();
	if(tmp.y >= moveDone){
		showMeny = 1;
		choices.choiceDone = 0;
		win.setPosition(winLosePosX, winLosePosY); //reset possition of winner text.
	}
}
//check what text object is choicen when the player make a choice.
//and returns false when the player choice to quit other wise true.
bool gui::getPlay(){
	if(choices.choiceDone && choices.marktedOnMeny){
		showMeny = 0;
	} else if(choices.choiceDone && !choices.marktedOnMeny){
		return 0;
	}
	return 1;
}
//returns bool value of showMeny.
bool gui::getShowMeny() const{
	return showMeny;
}
//resets the position of gameover text object.
void gui::newGameOver(){
	GameOver.setPosition(winLosePosX, winLosePosY);
}
//resets the position of winning text object.
void gui::newWin(){
	win.setPosition(winLosePosX, winLosePosY);
}
//return start text object.
sf::Text gui::getStart(){
	return start;
}
//return quit text object.
sf::Text gui::getQuit(){
	return quit;
}
//return gameover text object.
sf::Text gui::getGameOver(){
	return GameOver;
}
//returns win text object.
sf::Text gui::getWin(){
	return win;
}