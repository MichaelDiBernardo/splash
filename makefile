##
#   makefile for CS314 A3
#
#  I've set this up to let me work at home on my mac laptop and still
#  compile on the undergrad servers. The setup is simple, but it works.
#
#  Michael DiBernardo (p8m5, 63359053)

#MACOS COMPILE: COMMENT BOTH LINES OUT IF YOU'RE NOT COMPILING
#IN MACOS
CPPFLAGS = -Wall -D __mac -O2
LDFLAGS = -Wall -framework OpenGL -framework GLUT -D __mac

#UNCOMMENT FOR LINUX COMPILE
#LDFLAGS = -lGL -lGLU -lglut
#CPPFLAGS = -D __linux

#UNCOMMENT FOR DEBUGGING AND WARNINGS
#Using this will require you to make clean and rebuild
#CPPFLAGS += -g -D __debug -Wall

OBJS    = Animation.o Basics.o BodyPartNode.o BoxNode.o CameraNode.o ChaserAgent.o ColorSpec.o Config.o DinoNode.o DinoState.o DotNode.o EndgameRenderer.o Engine.o EngineInput.o EnvironmentalLightNode.o FadeRenderer.o Format.o Frame.o FrameSequence.o GameplayRenderer.o HUDNode.o IslandNode.o JointNode.o Level.o MenuRenderer.o ObjNode.o objreader.o Orientation.o PowerupNode.o PropNode.o PropNodeFactory.o PropSpec.o readtex.o Renderer.o Scene.o SceneNode.o SettingNode.o SpikeNode.o SplashscreenRenderer.o TexturedScreenRenderer.o Timer.o TranslationNode.o Utils2D.o WinscreenRenderer.o Main.o
TARGET = game

all: $(OBJS)
	g++ $(LDFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -f *.o
	rm -f $(TARGET)
