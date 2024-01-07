#OBJS specifies which files to compile as part of the project
OBJS = src\Game.cpp src\Game.h src\globals.h src\main.cpp src\physics.cpp src\physics.h src\SDLAux.cpp src\SDLAux.h src\Texture.cpp src\Texture.h src\types.h src\Objects\Ball.cpp src\Objects\Ball.h src\Objects\Cue.cpp src\Objects\Cue.h src\Objects\GameObject.h src\Objects\MessageBox.cpp src\Objects\MessageBox.h src\Objects\Table.cpp src\Objects\Table.h src\Objects\TextBox.cpp src\Objects\TextBox.h src\Scenes\MainMenuScene.cpp src\Scenes\MainMenuScene.h src\Scenes\PoolScene.cpp src\Scenes\PoolScene.h src\Scenes\Scene.h src\Scenes\SDL2.dll src\Scenes\SDL2_image.dll src\Scenes\SDL2_ttf.dll

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IE:\SDL\SDL2-2.26.2\i686-w64-mingw32\include\SDL2 -IE:\SDL\SDL2_image-2.6.3\i686-w64-mingw32\include\SDL2 -IE:\SDL\SDL2_ttf-2.20.2\i686-w64-mingw32\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LE:\SDL\SDL2-2.26.2\i686-w64-mingw32\lib -LE:\SDL\SDL2_image-2.6.3\i686-w64-mingw32\lib -LE:\SDL\SDL2_ttf-2.20.2\i686-w64-mingw32\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w -Wl,-subsystem,windows -g

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Pool

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)