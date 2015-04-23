binaryclock: binary.cpp 
	g++ -lncurses binary.cpp -o binaryclock
	
clean: 
	rm binaryclock
