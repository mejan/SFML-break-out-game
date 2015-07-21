#ifndef _GUI_H_
#define _GUI_H_

#include <SFML/Graphics.hpp>
#include <iostream>

class gui:public sf::Sprite{
	public:
		/**
		*default construtor for the gui.
		*
		*loads background texture.
		*set showmeny to true.
		*set the meny to mark the start text.
		*setting up the diffrent text objects.
		*and sets the moving speed and direction of gameover and winning text objects.
		*/
		gui();
		//just for show destructor.
		~gui();
		/**
		*update the color change of the text objects(start and game over).
		*/
		void guiUpdate();
		/**
		*set witch text object is markt.
		*/
		void setMarktedOnMeny(bool markted);
		/**
		*sets that the user has choicen on the gui ("meny").
		*/
		void setChoiceDone();
		/**
		*moves the gameover text from roof to middel
		*when moved to the middel it
		*then sets that the meny should be shown again.
		*and set that user made choice to false again.
		*when the text is in the middel it sets showmeny to true.
		*/ 
		void gameOver(sf::Int32& update);
		/**
		*moves the winning text from roof to middel
		*when moved to the middel it
		*then sets that the meny should be shown again.
		*and set that user made choice to false again.
		*when the text is in the middel it sets showmeny to true.
		*/ 
		void winner(sf::Int32& update);
		/**
		*returns a bool value true aslong as quit Text object in gui is the choice.
		*/
		bool getPlay();
		/**
		*Returns true if the meny is suppose to shown if start or quit in gui
		*gets choicen then it will returns false.
		*And if start is markted and choicsend then showMeny member till be false.
		*/
		bool getShowMeny() const;
		/**
		*returns text object start.
		*/
		sf::Text getStart();
		/**
		*returns text object quit.
		*/
		sf::Text getQuit();
		/**
		*returns text object GameOver
		*/
		sf::Text getGameOver();
		/**
		*returns text object win
		*/
		sf::Text getWin();
		/**
		*resets the possition of GameOver text object.
		*/
		void newGameOver();
		/**
		*resets the possition of win text object.
		*/
		void newWin();

	private:
		static const short int startPosX = 500;
		static const short int startPosY = 200;
		static const short int quitPosX = 500;
		static const short int quitPosY = 240;
		static const short int textSize = 70;
		static const short int winLosePosX = 400;
		static const short int winLosePosY = -70;
		static const short int moveDone = 400;

		//this is the diffrent objects in the class.
		sf::Text start;
		sf::Text quit;
		sf::Text GameOver;
		sf::Text win;
		sf::Font font;
		sf::Vector2f movingText;
		sf::Texture backGround;

		//memeber showMeny
		bool showMeny;
		//member struct.
		struct startExit{
			bool marktedOnMeny;
			bool choiceDone;
		} choices;
};

#endif /*_GUI_H_*/