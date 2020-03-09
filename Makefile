# starting Flags 
CXXFLAGS = -Wall -std=c++11 -O2 -DNO_FREETYPE -I $(HOME)/libs/include -I Code -I Code/Point -I Code/Polygon -I Code/commands

# what must be done 
all: main.exe

# ending flags
Last = -L $(HOME)/libs/lib -l PNGwriter -l png

# location of includes
Point_h = ./Code/Point/Point.hh
Polygon_h = ./Code/Polygon/Polygon.hh
commmands_h = ./Code/commands/commands.hh

# Erase all .o documents of all directories recursively (and main.exe as well)
current_dir := Code
directories := . $(shell find $(current_dir) -type d)
search := *.o main.exe
erase := $(foreach DIR,$(directories),$(addprefix $(DIR)/,$(search)))

# make clean
clean:
	rm -f $(erase)

# What must main.exe link
main.exe: ./Code/main.o ./Code/Point/Point.o ./Code/Polygon/Polygon.o ./Code/Polygon/Convexhull.o
main.exe: ./Code/Polygon/extras.o ./Code/Polygon/Intersection.o ./Code/commands/commands1.o  
main.exe: ./Code/commands/commands2.o ./Code/commands/commands3.o ./Code/commands/errors.o
main.exe: ./Code/commands/files.o  ./Code/commands/pictures.o

main.exe:
	$(CXX) $^ -o $@ $(Last)


# Dependencies
./Code/main.o: ./Code/main.cc $(Point_h) $(Polygon_h) $(commands_h)

./Code/Point/Point.o: ./Code/Point/Point.cc $(Point_h)

./Code/Polygon/Polygon.o: ./Code/Polygon/Polygon.cc $(Polygon_h) $(Point_h)

./Code/Polygon/Convexhull.o: ./Code/Polygon/Convexhull.cc $(Polygon_h) $(Point_h)

./Code/Polygon/extras.o: ./Code/Polygon/extras.cc $(Polygon_h) $(Point_h)

./Code/Polygon/Intersection.o: ./Code/Polygon/Intersection.cc $(Polygon_h) $(Point_h)

./Code/commands/commands1.o: ./Code/commands/commands1.cc $(Point_h) $(Polygon_h) $(commands_h)

./Code/commands/commands2.o: ./Code/commands/commands2.cc $(Point_h) $(Polygon_h) $(commands_h)

./Code/commands/commands3.o: ./Code/commands/commands3.cc $(Point_h) $(Polygon_h) $(commands_h)

./Code/commands/errors.o: ./Code/commands/errors.cc $(Point_h) $(Polygon_h) $(commands_h)

./Code/commands/files.o: ./Code/commands/files.cc $(Point_h) $(Polygon_h) $(commands_h)

./Code/commands/pictures.o: ./Code/commands/pictures.cc $(Point_h) $(Polygon_h) $(commands_h)