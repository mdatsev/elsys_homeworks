all: hexagon star sierpinski

hexagon.o: hexagon.cc
	g++ -c hexagon.cc

star.o: star.cc
	g++ -c star.cc

sierpinski.o: sierpinski.cc
	g++ -c sierpinski.cc

Axes.o: Axes.cc
	g++ -c Axes.cc

SVGTurtle.o: SVGTurtle.cc
	g++ -c SVGTurtle.cc

turtle_map.o: turtle_map.cc
	g++ -c turtle_map.cc

turtle.o: turtle.cc
	g++ -c turtle.cc

hexagon: hexagon.cc Axes.o SVGTurtle.o turtle_map.o turtle.o
	g++ -o hexagon hexagon.cc Axes.o SVGTurtle.o turtle_map.o turtle.o

star: star.cc Axes.o SVGTurtle.o turtle_map.o turtle.o
	g++ -o star star.cc Axes.o SVGTurtle.o turtle_map.o turtle.o

sierpinski: sierpinski.cc SVGTurtle.o turtle_map.o turtle.o
	g++ -o sierpinski sierpinski.cc SVGTurtle.o turtle_map.o turtle.o

clean:
	rm *.o