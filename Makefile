INCLUDES = ./includes/
ENGINES = ./includes/engines
COMPONENTS = ./includes/components
OBJECTS_LIB = ./includes/objects
GAMEOBJECTS = ./game_data/objects
IMGUI = ./includes/imgui
CXX = g++
CXXFLAGS += -std=c++20 $(shell sdl2-config --cflags)
CXXFLAGS += -I$(IMGUI) -I$(IMGUI)/backends -I$(INCLUDES) -I$(OBJECTS_LIB)
LDFLAGS = -lstdc++ -lSDL2
# List of source files
SOURCES := ./main.cpp \
		   $(wildcard $(ENGINES)/*.cpp) \
           $(wildcard $(COMPONENTS)/*.cpp) \
           $(wildcard $(OBJECTS_LIB)/*.cpp) \
           $(wildcard $(GAMEOBJECTS)/*.cpp) \
		   $(wildcard $(IMGUI)/*.cpp) \
		   $(IMGUI)/backends/imgui_impl_sdl2.cpp \
		   $(IMGUI)/backends/imgui_impl_sdlrenderer2.cpp

# List of object files
OBJECTS := $(patsubst %.cpp, %.o, $(SOURCES))

# Main target
all: fuzzy_engine

# Rule to compile object files
	$(CXX) $(CXXFLAGS) -c  $< -o $@

# Rule to link the executable
fuzzy_engine: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^


# Clean rule
clean:
	rm -rf $(OBJECTS) fuzzy_engine 
