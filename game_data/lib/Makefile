CXX = g++
IMGUI = ../../includes/imgui
INCLUDES= ../../includes/ 
ENGINES =../../includes/engines/ 
OBJECTSI = ../../includes/objects/
COMPONENTS = ../../includes/components/

CXXFLAGS = -std=c++20 -fPIC -I./lib $(shell sdl2-config --cflags)
CXXFLAGS += -I$(IMGUI) -I$(IMGUI)/backends -I$(INCLUDES) -I$(ENGINES) -I$(OBJECTSI) -I$(COMPONENTS)

SHARED=  -shared -std=c++20

OBJECT_LIB=../objects
SOURCES = 	$(wildcard $(OBJECT_LIB)/*.cpp) \
 			$(wildcard $(ENGINES)/*.cpp) \
           	$(wildcard $(COMPONENTS)/*.cpp) \
           	$(wildcard $(OBJECTS)/*.cpp) \
           	$(wildcard $(GAMEOBJECTS)/*.cpp) \
		   	$(wildcard $(IMGUI)/*.cpp) \
		   	$(IMGUI)/backends/imgui_impl_sdl2.cpp \
		   	$(IMGUI)/backends/imgui_impl_sdlrenderer2.cpp 

LIB_SOURCES := $(patsubst $(OBJECT_LIB)/%.cpp, %.so, $(SOURCES))
LIB_SOURCES := $(addprefix ./, $(LIB_SOURCES))

OBJECTS := $(patsubst $(OBJECT_LIB)/%.cpp, %.o, $(SOURCES))
OBJECTS := $(addprefix ./, $(OBJECTS))

lib: $(LIB_SOURCES)

	echo $(LIB_SOURCES)

$(LIB_SOURCES) : $(OBJECTS)

	$(CXX) $(SHARED) -o ./$@ $^

$(OBJECTS) : $(SOURCES)  # Change '$(SOURCES)' to '$<'

	$(CXX) $(CXXFLAGS) -c $< -o ./$@  


clean:
	rm -rf *.o *.so 