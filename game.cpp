#include "game.h"

game::game(){
	window.create(sf::VideoMode(windowWidth, windowHight), "The Game");
	window.setKeyRepeatEnabled(0);
	window.setFramerateLimit(maxFramesPerSecond);
	//Setting up walls.
	setUpWalls();
	//set up the Text
	setUpText();

	meny = new gui;
	newGame();
	execute();
}
//dealocate the memory of the class.
game::~game(){
	delete meny;
	delete ball;
	delete fPlayer;
	deleteBoxes();
}

void game::execute(){
	sf::Time time;
	sf::Clock renderClock, updateClock;
	while (window.isOpen())
	{
		//gets the time that gone since the clock been reset or initated.
		time = renderClock.getElapsedTime();
		float fFps=1000000/time.asMicroseconds();
		//save fps to the text objec..
        s<<fFps<<" fps";
        fps.setString(s.str());
        s.str("");
		renderClock.restart();

		const sf::Int64 frameTime = 1000000/60;
		sf::Clock c;
		sf::Time t=c.getElapsedTime();
		sf::Int64 nextFrameTime=t.asMicroseconds()+frameTime;

		int loops = 0;
		while( t.asMicroseconds() < nextFrameTime && loops < maxFrameSkip)
		{
			//Read events
			events();
			//Update time to use in getting smother movement of ball and gameover/win text.
			updateTime=updateClock.restart().asMilliseconds();
			//Update Logic
			update();

			t=c.getElapsedTime();
			loops++;
		}
		// Render
		render();
	}
}

void game::events(){
	if(meny->getShowMeny()){//if meny should be showed.
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){//if up arrow is pushed.
			meny->setMarktedOnMeny(1);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){//if down arrow is pushed.
			meny->setMarktedOnMeny(0);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
			meny->setChoiceDone();
			meny->getPlay();
		}
		if(!meny->getPlay()){//if quit is choicen in the meny.
			window.close();
		}
	}else { //if meny is not on.
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){//if left arrow pushed.
			fPlayer->setLeft(1);
		} else{
			fPlayer->setLeft(0);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){//if right arrow pushed.
			fPlayer->setRight(1);
		} else{
			fPlayer->setRight(0);
		}
		//check the extra lifes and set it to the extraLife text object.
		s<<"Lifes: " << fPlayer->getLife();
		extraLife.setString(s.str());
		s.str("");
	}
	//kollar om fönstret ska stängas.
	sf::Event event;
	while(window.pollEvent(event)){
		if(event.type == sf::Event::Closed){
			window.close();
		}
	}
}

void game::update(){
	if(meny->getShowMeny()){//if meny is on.
		meny->guiUpdate();//calls meny memeber function guiUpdate.
		resetGame(); // resets the game over and over.
	} else { //if meny is off.
		ball->movementOfBall(updateTime);//move the ball with updatetime clock.
		//Player pad movement.
		if(fPlayer->getLeft()){//if player pad should move left.
			fPlayer->moveLeft();//move player pad left.
		}
		if(fPlayer->getRight()){//if player pad should move right.
			fPlayer->moveRight();//move player pad right.
		}

		if(boxesIsEmpty()){ //vector with boxes is empty
			meny->winner(updateTime);//call winning text.
		}

		if(ball->checkIfDead()){//check if ball is dead(position under player pad).
			fPlayer->loseLife();//removes a extra life.
			if(fPlayer->getLife() >= 0){//if extra life is more/= to 0.
				delete ball;//delete old ball
				ball = new bounceBall();//alocate new ball.
			}else{
				meny->gameOver(updateTime);//show gameover text object.
			}
		}
		collition();//check if ball collide with something.
	} 
}

void game::render(){
	window.clear(); //clears the widnow.
	if(meny->getShowMeny()){//if meny on.
		window.draw(*meny);//draw background for meny.
		window.draw(meny->getStart());//draw start text object.
		window.draw(meny->getQuit());//draw quit text object.
	} else {//if meny off.
		window.draw(backGrund);//draw game background.
		window.draw(fps);//draw fps text object.
		window.draw(extraLife); //draw extralife text object.
		window.draw(*fPlayer); //draw the player pad object.
		drawBoxes(); //member function drawing all boxes.
		window.draw(*ball); //draw the ball object.
		if(fPlayer->getLife() < 0){//check if the player lost.
			window.draw(meny->getGameOver()); //draw gameover text object.
		}
		if(boxesIsEmpty()){//check if all boxes is gone.
			window.draw(meny->getWin());//draw winning text object.
		}
	}
	window.display(); //display what been drawn in the window.
}

void game::fillBoxes(){
	for(size_t i = 0; i < boxRows; i++){
		std::vector<box*> tmp0;
		for(size_t j = 0; j < boxColums; j++){
			box* tmp1;
			if(i%2 == 0){//if i even then alocate new box.
				tmp1 = new box();
			}
			else{//else alocate new steel box.
				tmp1 = new steelBox();
			}
			tmp0.push_back(tmp1);
			tmp1->setPosition(j*positionChangeX+marginan, i*positionChangeY+marginan);
		}
		boxes.push_back(tmp0); //put pointers to box objects in the vector.
	}
}

void game::drawBoxes(){
	for(size_t i = 0; i < boxes.size(); i++){
		for(size_t j = 0; j < boxes[i].size(); j++){
			window.draw(*boxes[i][j]);//draw the box objec at row i and colum j.
		}
	}
}

void game::collition(){

	//kollar om bollen krockar med en låda.
	for(int i = 0; i < boxes.size(); i++){
		for(int j = 0; j < boxes[i].size(); j++){
			if (ball->shallCollideWith(*(boxes[i][j]), updateTime)) { //if ball collide with box.
				boxes[i][j]->loseLife();//the box loses  hp.
				if(boxes[i][j]->getLife() == 0){ //if box hp == 0 delete box.
					delete boxes[i][j];
					boxes[i].erase(boxes[i].begin()+j);
				}
				return; //end collide memeber function.
			}
		}
	}

	//check if ball collide with player if it does increase ball speed with 2%.
	if (ball->shallCollideWith(*fPlayer, updateTime)) {
		//increase speed by 2%.
        ball->setBallDirectionX(ball->getBallDirectionX() * 1.02f);
        ball->setBallDirectionY(ball->getBallDirectionY() * 1.02f);
        return;		
	}

	if(ball->shallCollideWith(rightWall, updateTime)){ //ball collide with right wall.
		return;
	}

	if(ball->shallCollideWith(leftWall, updateTime)){//ball collide with left wall.
		return;
	}
	if(ball->shallCollideWith(roofWall, updateTime)){ //ball collide with roof.
		return;
	}
}

void game::setUpWalls(){
	//load textures for wall members (sprite).
	if(!bgTexture.loadFromFile("images/backgrund.png")){
		std::cerr << "Failed loading backgrund" << std::endl;
	}
	backGrund.setTexture(bgTexture);

	if(!leftTexture.loadFromFile("images/leftRightSide.png")){
		std::cerr << "Failed loading left side texture" << std::endl;
	}
	leftWall.setTexture(leftTexture);

	if(!rightTexture.loadFromFile("images/leftRightSide.png")){
		std::cerr << "Failed loading right side texture" << std::endl;
	}
	rightWall.setTexture(rightTexture);

	if(!roofTexture.loadFromFile("images/roof.png")){
		std::cerr << "Failed loading roof texture" << std::endl;
	}
	roofWall.setTexture(roofTexture);
	//set position of wall sprites.
	leftWall.setPosition(posLeftX, posLeftY);
	rightWall.setPosition(posRightX, posRightY);
	roofWall.setPosition(posRoofX, posRoofY);
	//set origin for wall sprite.
	leftWall.setOrigin(originSidesX, originSidesY);
	rightWall.setOrigin(originSidesX, originSidesY);
	roofWall.setOrigin(originRoofX, originRoofY);
}

void game::setUpText(){
	//load font to text objects.
	font.loadFromFile("images/Halo.ttf");
	//setting up Fps text object..
	fps.setCharacterSize(textSize);
	fps.setColor(sf::Color::Red);
	fps.setFont(font);
	fps.setPosition(fpsPosX, fpsPosY);
	//setting up extra life text object.
	extraLife.setCharacterSize(textSize);
	extraLife.setColor(sf::Color::Red);
	extraLife.setFont(font);
	extraLife.setPosition(extraLifePosX, extraLifePosY);
}

void game::newGame(){
	//Create Sprites.
	fPlayer = new player();
	fillBoxes();
	ball = new bounceBall();
}

void game::resetGame(){
	//delete sprites.
	delete fPlayer;
	delete ball;
	deleteBoxes();
	//alocate new sprites.
	newGame();
}

void game::deleteBoxes(){
	//delete all dynamic boxes memory, and clears vectors size.
	for(size_t i = 0; i < boxes.size(); i++){
		for(size_t j = 0; j < boxes[i].size(); j++){
			delete boxes[i][j];
		}
		boxes[i].clear();
	}
	boxes.clear();
}

//if vector empty return true else false.
bool game::boxesIsEmpty(){
	if(boxes.size() == 0){
		return 1;
	} 
	for(int i = 0; i < boxes.size(); i++){
		if(boxes[i].size() == 0){
			boxes.erase(boxes.begin()+i);
		}
	}
	return 0;
}