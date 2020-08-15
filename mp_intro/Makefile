intro : main.o PNG.o HSLAPixel.o lodepng.o intro.o
	clang++ intro.o main.o PNG.o HSLAPixel.o lodepng.o -o intro

intro.o : intro.cpp intro.h cs225/PNG.h
	clang++ -c intro.cpp

main.o : main.cpp intro.h cs225/PNG.h cs225/HSLAPixel.h cs225/lodepng/lodepng.h
	clang++ -c main.cpp

PNG.o : cs225/PNG.cpp cs225/PNG.h cs225/HSLAPixel.h cs225/lodepng/lodepng.h
	clang++ -c cs225/PNG.cpp

HSLAPixel.o : cs225/HSLAPixel.cpp cs225/HSLAPixel.h
	clang++ -c cs225/HSLAPixel.cpp

lodepng.o : cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	clang++ -c cs225/lodepng/lodepng.cpp

clean :
	rm intro *.o
