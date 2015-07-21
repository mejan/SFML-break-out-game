#ifndef _STEEL_BOX_H_
#define _STEEL_BOX_H_

#include "box.h"

class steelBox: public box{//public relation to bax class
	public:
		/**
		*uses the box class construct with string and int.
		*string is where it will find the texture
		*the int is the health points this object should have.
		*/
		steelBox();
		//default destructor just for show.
		~steelBox();
	private:
		//hp the steel box will have.
		static const short int hp = 2;
};

#endif /*_STEEL_BOX_H_*/