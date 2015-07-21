comp: main.cpp box.h box.cpp player.h player.cpp game.h game.cpp bounceball.h bounceball.cpp steelBox.h steelBox.cpp gui.h gui.cpp
	#compile and then run the program
	g++ main.cpp box.cpp player.cpp game.cpp bounceball.cpp steelBox.cpp gui.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system -std=c++0x
	export LD_LIBRARY_PATH=/usr/local/lib && ./game
run: game
	#run already compiled program.
	export LD_LIBRARY_PATH=/usr/local/lib && ./game