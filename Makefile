CXX = g++
CXXFLAGS= -std=c++20
LDFLAGS = -lstdc++ -lSDL2 
INCLUDES=./includes
ENGINES=./includes/engines
COMPONENTS=./includes/components
OBJECTS=./includes/objects
BUILD=./build
GAMEOBJECTS=./game_data/objects

all: fuzzy_test


fuzzy_test: main.o \
			graphics_engine.o \
			input_engine.o \
			sprite_engine.o \
			physics_engine.o \
			collision_engine.o\
			sprite_component.o \
			physics_component.o \
			collider_component.o \
			game_object.o \
			bird.o \
			test_platform.o

	$(CXX)  $(CXXFLAGS) $(LDFLAGS) -o fuzzy_test $(BUILD)/main.o \
									 $(BUILD)/graphics_engine.o \
									 $(BUILD)/input_engine.o \
									 $(BUILD)/sprite_engine.o \
									 $(BUILD)/physics_engine.o \
									 $(BUILD)/collision_engine.o\
									 $(BUILD)/sprite_component.o \
									 $(BUILD)/physics_component.o \
									 $(BUILD)/collider_component.o \
									 $(BUILD)/game_object.o \
									 $(BUILD)/bird.o \
									 $(BUILD)/test_platform.o
							

									 
main.o:
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(BUILD)/main.o

graphics_engine.o:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $(ENGINES)/graphics_engine.cpp -o $(BUILD)/graphics_engine.o

input_engine.o:
	$(CXX) $(CXXFLAGS) -c $(ENGINES)/input_engine.cpp -o $(BUILD)/input_engine.o

sprite_engine.o:
	$(CXX) $(CXXFLAGS) -c $(ENGINES)/sprite_engine.cpp -o $(BUILD)/sprite_engine.o

physics_engine.o:
	$(CXX) $(CXXFLAGS) -c $(ENGINES)/physics_engine.cpp -o $(BUILD)/physics_engine.o

collision_engine.o:
	$(CXX) $(CXXFLAGS) -c $(ENGINES)/collision_engine.cpp -o $(BUILD)/collision_engine.o
	
sprite_component.o:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $(COMPONENTS)/sprite_component.cpp -o $(BUILD)/sprite_component.o

physics_component.o:
	$(CXX) $(CXXFLAGS) -c $(COMPONENTS)/physics_component.cpp -o $(BUILD)/physics_component.o

collider_component.o:
	$(CXX) $(CXXFLAGS) -c $(COMPONENTS)/collider_component.cpp -o $(BUILD)/collider_component.o 

game_object.o:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $(OBJECTS)/game_object.cpp -o $(BUILD)/game_object.o

bird.o:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $(GAMEOBJECTS)/player_object/bird.cpp -o $(BUILD)/bird.o

test_platform.o:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $(GAMEOBJECTS)/environment_objects/test_platform.cpp -o $(BUILD)/test_platform.o

clean:
	rm -f ./$(BUILD)/*.o fuzzy_test
