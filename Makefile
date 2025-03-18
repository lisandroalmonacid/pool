# Source files
SRCS = src/Game.cpp src/main.cpp src/physics.cpp src/SDLAux.cpp src/Texture.cpp \
       src/Objects/StaticObject.cpp src/Objects/Ball.cpp src/Objects/Cue.cpp \
       src/Objects/MessageBox.cpp src/Objects/Table.cpp src/Objects/TextBox.cpp \
       src/Scenes/MainMenuScene.cpp src/Scenes/PoolScene.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Compiler
CC = g++

# Compiler flags (-Wall enables all warnings, -g for debugging)
CFLAGS = -Wall -Wextra -g

# SDL2 paths (assuming you have SDL2 installed)
INCLUDE_PATHS = $(shell sdl2-config --cflags)
LIBRARY_PATHS = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf

# Executable name
OBJ_NAME = Pool

# Build target
all: $(OBJ_NAME)

$(OBJ_NAME): $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CFLAGS) -o $(OBJ_NAME)

# Compile source files into object files
%.o: %.cpp
	$(CC) -c $(INCLUDE_PATHS) $(CFLAGS) $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(OBJ_NAME)
