/**
*The Game class, has all the objects and will check events, updates and draw/render
*for displaying the game for users.
*
*This class uses the other classes by dynamic memory, in the event
*the class checks for user input and set varibles accordently.
*Update will update the new positions of object and check if collides with
*each other.
*render is used to render all the dynamic objects to be displayed in the window.
*/

#ifndef _GAME_H_
#define _GAME_H_

#include "steelBox.h"
#include "player.h"
#include "bounceball.h"
#include "gui.h"

#include <vector>
#include <cstdlib>
#include <math.h>
#include <sstream>

class game{
	public:
		/**
		*Construtctor for the game set up the window size and titel, the 
		*key repeat disable. sets fps limit at 60 fps.
		*calls a private function called setUpWalls that prepare the walls that
		*the ball bounce on.
		*it calls setUpText, is there to prepare all the texts object this class has.
		*Direct new gui to the meny pointer.
		*It calls a private member function called newGame witch alocate dynamicly
		*all the objects in the game.
		*then it calls the public member function execute.
		*/
		game();
		/**
		*distructor just delete all the allocated memeory.
		*/
		~game();
		/**
		*Execute has som diffrent clock/timer to controll the fps will be right.
		*
		*The main thing about the member function is that it's a while that will
		*continue while window is open, and it checks for events of users/program 
		*these events are trigger diffrent viribles to change value.
		*
		*Then it will call update, update changes the possistions and looks for
		*collitions between objects and check if the that object should be removed.
		*
		*Then the private memberfunction render is called where it clears the screen
		*and then draws/render the objects positions and display it in the widniow.
		*/
		void execute();
		
	private:
		/**
		*Diffrent ints that is used to clear up what is getting set
		*in diffrent code bits so it's more clear.
		*/ 

		static const short int maxFramesPerSecond = 60;
		static const short int maxFrameSkip = 10;
		static const short int windowWidth = 1200;
		static const short int windowHight = 800;
		static const short int boxColums = 15;
		static const short int boxRows = 5;
		static const short int positionChangeX = 80;
		static const short int positionChangeY = 35;
		static const short int marginan = 40;
		static const short int originSidesX = 10;
		static const short int originSidesY = 400;
		static const short int originRoofY = 40;
		static const short int originRoofX = 600;
		static const short int posLeftX = -10;
		static const short int posLeftY = 400;
		static const short int posRightX = 1210;
		static const short int posRightY = 400;
		static const short int posRoofX = 600;
		static const short int posRoofY = -45;
		static const short int textSize  = 40;
		static const short int fpsPosX = 30;
		static const short int fpsPosY = 730;
		static const short int extraLifePosX = 1000;
		static const short int extraLifePosY = 730;
		
		/**
		*FillBoxes is filling the vector with the boxes in the top of the window
		*with dynmic memorys of a box class/subclass.
		*/
		void fillBoxes();
		/**
		*DrawBoxes is iterating the vector with boxes and call windows.draw();
		*to draw these for the window.
		*/
		void drawBoxes();
		/**
		*Events check what buttons the users pushes that can change something
		*inside the game, also check if the game window is shot down.
		*/
		void events();
		/**
		*Update is updating the obects positions, update the player pad,
		*accordently to events varible changes.
		*
		*It's the function that checks if player is dead or won.
		*
		*If the ball goes under the playerpad extra life will be decreast,
		*and if it's zero it will just show the gameover and the play has lost.
		*
		*If all boxes are gone will show the winning text.
		*/
		void update();
		/**
		*render starts with cleaning the window, then draw it again and there by
		*draw the objects that is left at there right possition.
		*after that displays it in the window.
		*/
		void render();
		/**
		*Collition checks if the ball collides with a other object and callas the 
		*balls direction changes member function when that happens.
		*
		*Also in case of the player pad collide with ball increases the ball
		*speed with 2%
		*
		*If the ball collide with a box the box losese hp when hp == 0
		*then delete that box.
		*
		*If a collidition to speed the program up as soon as a collition acour
		*and all changes is done for this collition then go back to execute loop.
		*/
		void collition();
		/**
		*Loads textures to the wall sprites, set the sprite position and it's 
		*origin.
		*/
		void setUpWalls();
		/**
		*SetUpText is used to load in the font for the text objects, set
		*the text size, Color and position.
		*/
		void setUpText();
		/**
		*newGame is where it allocates the dynamic memory for player calls
		*the fillBoxes memberfunction and alocate dynamic memory for the ball.
		*/
		void newGame();
		/**
		*deletes the alocated memory and then calles the newGame
		*member function.
		*/
		void resetGame();
		/**
		*dealocate the dynamic memory for the boxes.
		*/
		void deleteBoxes();
		/**
		*returns true if the vector is empty (no alocated memory left in vector)
		*else reuturns false.
		*/
		bool boxesIsEmpty();
		
		//members in class.
		sf::RenderWindow window;
		std::vector<std::vector<box*> >  boxes;
		player* fPlayer;
		bounceBall* ball;
		gui* meny;
		sf::Int32 updateTime;		
		sf::Sprite backGrund;
		sf::Sprite leftWall;
		sf::Sprite rightWall;
		sf::Sprite roofWall;
		sf::Text extraLife;
		sf::Text fps;
		sf::Font font;
		std::stringstream s;
		sf::Texture bgTexture;
		sf::Texture leftTexture;
		sf::Texture rightTexture;
		sf::Texture roofTexture;
};

#endif /*_GAME_H_*/