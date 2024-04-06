INCLUDES = ./includes/
ENGINES = ./includes/engines
COMPONENTS = ./includes/components
OBJECTS_LIB = ./includes/objects
GAMEOBJECTS = ./game_data/objects
IMGUI = ./includes/imgui-1.90.4-docking
CXX = g++
CXXFLAGS += -std=c++20 $(shell sdl2-config --cflags)
CXXFLAGS += -I$(IMGUI) -I$(IMGUI)/backends -I$(INCLUDES) -I$(OBJECTS_LIB) -I$(GAMEOBJECTS)
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

#LIBRARIES := $(patsubst $(GAMEOBJECTS)/%.cpp, $(GAMEOBJECTS)/lib%.so, $(wildcard $(GAMEOBJECTS)/*.cpp)) 


# Main target
all: fuzzy_engine

%.o: %.cpp
# Rule to compile object files
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(GAMEOBJECTS)/lib%.so: $(GAMEOBJECTS)/%.o
	$(CXX) $(CXXFLAGS) -shared -o $@ $^

# Rule to link the executable
fuzzy_engine: $(OBJECTS) #$(LIBRARIES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^


# Clean rule
clean:
	rm -rf $(OBJECTS) fuzzy_engine 
