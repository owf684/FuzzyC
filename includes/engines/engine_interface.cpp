/* Program: Engine Interface
*
* Pupose: The engine_interface builds the IMGUI windows used to interface with the game engine.
* It also provides all the engine interface logic for every feature seen in the UI
*
* Author: Christopher Corona
*
* Version: v0.1.0
*
* TODO:
*/

#include "engine_interface.h"
#include "interface_globals.h"
#include "engine_globals.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "bird.h"
#include "tinyxml2.h"
#include <cstdlib> // for atof function

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

using namespace tinyxml2;


bool stringToBool(const char* str) {
    if (std::strcmp(str, "true") == 0 || std::strcmp(str, "yes") == 0 || std::strcmp(str, "1") == 0) {
        return true;
    } else if (std::strcmp(str, "false") == 0 || std::strcmp(str, "no") == 0 || std::strcmp(str, "0") == 0) {
        return false;
    }
    // If the string doesn't match any recognized value, you might want to handle that case accordingly
    // Here, we'll return false as a default
    return false;
}

// Constructors 
EngineInterface::EngineInterface()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;


    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(graphics_engine.window, graphics_engine.renderer);
    ImGui_ImplSDLRenderer2_Init(graphics_engine.renderer);

    // update scenes vector
    for (const auto& entry : std::filesystem::directory_iterator("./game_data/scenes"))
    {
        if (entry.path().extension() == ".xml") {
            available_scenes.push_back(entry.path().string()); 
            available_scene_names.push_back(entry.path().filename().replace_extension(""));
        }
    }

}

/* Function: update
* 
*  Purpose: Calls the ImGUI
*  draw logic. To add more ui
*  simpy place imgui code
*  in between the frame and draw calls
*/
void EngineInterface::update()
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    main_menu();


    ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

}


/* Function: main_menu
*
* Purpose: This function calls
* the sub-menu functions that make
* up the main menu
*/
void EngineInterface::main_menu(){

    engine_controls();
    scene_controls();
    object_contorls();
    camera_controls();
    // non-viewable menus at engine startup 
    if (show_add_object_menu) add_object_menu();

}

/* Function: engine_controls
*
* Purpose: This function draws the engine 
* controls window and contains the engine controls
* logic 
*/
void EngineInterface::engine_controls(){
    ImGui::Begin("Engine Controls");
    
    // first line -- button controls
    if (play_pause){
        if (ImGui::Button("Pause"))
        {
            play_pause = false;
        }
    } else {
        if (ImGui::Button("Play")) {
            play_pause = true;
        }
    }
    
    ImGui::SameLine();
    if (ImGui::Button("Rebuild"))
    {
        system("make clean; make all; ./restart_engine.sh&");
    }

    // second line -- fps controls
    ImGui::SetNextItemWidth(128);
    ImGui::SliderFloat("FPS",&frames_per_second_f,60.0,120.0);

    // third line -- grid controls
    ImGui::SetNextItemWidth(128);
    ImGui::SliderInt("Grid Size", &graphics_engine.grid_size, 8, 128);
    ImGui::SameLine();
    ImGui::Checkbox("View Grid", &view_grid);
    ImGui::SameLine();
    ImGui::Checkbox("Snap to Grid", &snap_to_grid);

    // fourth line -- move world controls
    ImGui::SetNextItemWidth(128);
    ImGui::SliderInt("Move Speed",&scroll_engine.move_speed,1,32);
    ImGui::SameLine();
    ImGui::Checkbox("Move World", &move_world_enabled);
    ImGui::SameLine();
    if ( ImGui::Button("Set to Zero") )
    {
        set_to_zero = true;
    }

    ImGui::End();
}

/* Function: object_controls
*
* Purpose: This function draws the 
* object controls window and contrains
* the object controls logic
*/
void EngineInterface::object_contorls(){
    ImGui::Begin("Object Controls");
        if (ImGui::Button("Add Object"))
        {
            show_add_object_menu = true;
            // iterate through directory and get asset bmp files and load them into asset vector
            object_info.available_assets.clear();
            for (const auto& entry : std::filesystem::directory_iterator("./game_data/assets"))
            {
                if (entry.path().extension() == ".bmp") {
                    object_info.available_assets.push_back(entry.path().string()); 
                }
            }
        }
        ImGui::SameLine();
 
        if (ImGui::Button("Remove Object"))
        {
            object_util.remove_object(selected_object);
            system("make all; ./restart_engine.sh&");
        }
                
        if (ImGui::BeginCombo("object library",selected_object))
        {
    
            for (auto&objs: object_util.obj_lib)
            {
                bool is_selected = (selected_object == objs.c_str());

                if (ImGui::Selectable(objs.c_str(), is_selected))
                {
                    selected_object = objs.c_str();
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
        }

        ImGui::Checkbox("Make Object Placeable", &place_object_enabled);
        
        if (place_object_enabled)
        {
            if (input_engine.left_click && !already_placed && selected_object != NULL) //bug here when clicking on other menu items objects are placed!
            {

                already_placed = true;

                // snap object to grid logic 
                if (snap_to_grid)
                {
                    // do some simple maths
                    int x_ref = ImGui::GetMousePos().x;
                    int x_pos = ImGui::GetMousePos().x;
                    int y_ref = ImGui::GetMousePos().y;
                    int y_pos = ImGui::GetMousePos().y;

                    // calculate x position factors
                    int x_remainder = (x_pos ) % graphics_engine.grid_size;
                    float grids_on_screen_xdim = scroll_engine.accumulated_x / graphics_engine.grid_size ;              // numbers of grids
                    float fractional_grid_size_on_screen_xdim = (grids_on_screen_xdim - int(grids_on_screen_xdim));    // size of the last grid
                    int grid_offset_xdim = fractional_grid_size_on_screen_xdim*graphics_engine.grid_size;              // used to adjust the x_pos

                    // calculate the snapped x position
                    x_pos = x_pos - x_remainder + grid_offset_xdim;

                    // shift x_position if scrolled left and initial snap was off by a grid size in the -x direction
                    if (x_ref < x_pos)
                    {
                        x_pos -= graphics_engine.grid_size;
                    // shift x_position if scrolled right and initial snap was off by a grid size in the +x direction
                    } else if (x_ref - x_pos > graphics_engine.grid_size)
                    {
                        x_pos += graphics_engine.grid_size;
                    }
                   
                    // calculate y position factors
                    int y_remainder = (y_pos ) % graphics_engine.grid_size;
                    float grids_on_screen_ydim = scroll_engine.accumulated_y / graphics_engine.grid_size;
                    float fractional_grid_size_on_screen_ydim = (grids_on_screen_ydim - int(grids_on_screen_ydim));
                    int grid_offset_ydim = fractional_grid_size_on_screen_ydim*graphics_engine.grid_size;

                    // calculate the snapped y position
                    y_pos = y_pos - y_remainder + grid_offset_ydim;

                    // shift y position if scrolled down and initial snap was off by a grid size in the +y direction
                    if (y_ref < y_pos)
                    {
                        y_pos -= graphics_engine.grid_size;
                    
                    // shift y position if scrolled up and initial snap was off by a grid size in the -y direction
                    } else if(y_ref - y_pos > graphics_engine.grid_size)
                    {
                        y_pos += graphics_engine.grid_size;
                    }
                    
                    // save snapped positions 
                    ImVec2 snapped_position(x_pos,y_pos);

                    // create new object
                    object_handler.generate_object(selected_object,snapped_position, false);


                } else {object_handler.generate_object(selected_object,ImGui::GetMousePos(), false);}
            
            } else if (!input_engine.left_click && already_placed)
            {
                already_placed = false;
            }
        } 

        ImGui::SameLine();
        ImGui::Checkbox("Enable Object Eraser", &erase_object_enabled);
        
        if (erase_object_enabled)
        {
            if (input_engine.right_click)
            {
                for (auto objects = graphics_engine.render_buffer.begin(); objects != graphics_engine.render_buffer.end(); objects++)
                {   
                    if ((*objects)->collider.in_rect(ImGui::GetMousePos().x, ImGui::GetMousePos().y))
                    {
                        graphics_engine.render_buffer.remove(objects);
                        break;
                    }
                }
            }
        }


    ImGui::End();
}

/* Function: scene_controls
*
* Purpose: This function draws the scene controls
* window and contains the scene controls logic
*/
void EngineInterface::scene_controls(){
    ImGui::Begin("Scene Controls");
    
    ImGui::InputText("Scene Name", scene_name,IM_ARRAYSIZE(scene_name));

    if (ImGui::Button("Clear Scene"))
    {
        graphics_engine.render_buffer.clear();
    }
    ImGui::SameLine();

    if (ImGui::Button("Remove Scene"))
    {
        std::string remove_scene_cmd = "rm " + std::string(selected_scene);
        system(remove_scene_cmd.c_str());

         // update scenes vector
         available_scenes.clear();
         available_scene_names.clear();
        for (const auto& entry : std::filesystem::directory_iterator("./game_data/scenes"))
        {
            if (entry.path().extension() == ".xml") {
                    available_scenes.push_back(entry.path().string()); 
                    available_scene_names.push_back(entry.path().filename().replace_extension(""));

            }
        }
        selected_scene = NULL;
    }

    ImGui::SameLine();
    if (ImGui::Button("Save Scene"))
    {
        // create xml scene
        // Create a new XML document
        XMLDocument doc;

        // Create a declaration (<?xml version="1.0"?>)
        XMLDeclaration* declaration = doc.NewDeclaration();
        doc.InsertFirstChild(declaration);

        // Create a root element
        XMLElement* root = doc.NewElement("scene");
        doc.InsertEndChild(root);

        // Create book elements and add them to the root
        XMLElement* EngineControls = doc.NewElement("engine_controls");
        EngineControls->SetAttribute("frames_per_second", frames_per_second_f);
        EngineControls->SetAttribute("grid_size", graphics_engine.grid_size);
        EngineControls->SetAttribute("view_grid", view_grid);
        EngineControls->SetAttribute("snap_to_grid",snap_to_grid );
        EngineControls->SetAttribute("move_speed", scroll_engine.move_speed);
        EngineControls->SetAttribute("move_world",move_world_enabled);

        root->InsertEndChild(EngineControls);

        XMLElement* SceneControls = doc.NewElement("scene_controls");
        SceneControls->SetAttribute("scene_color_w",scene_color.w);
        SceneControls->SetAttribute("scene_color_x",scene_color.x);
        SceneControls->SetAttribute("scene_color_y",scene_color.y);
        SceneControls->SetAttribute("scene_color_z",scene_color.z);
      
        root->InsertEndChild(SceneControls);

        XMLElement* CameraControls = doc.NewElement("camera_controls");
        CameraControls->SetAttribute("x_axis_left_threshold",scroll_engine.left_x_scroll_threshold);
        CameraControls->SetAttribute("x_axis_right_threshold",scroll_engine.right_x_scroll_threshold);
        CameraControls->SetAttribute("y_axis_up_scroll_threshold",scroll_engine.up_y_scroll_threshold);
        CameraControls->SetAttribute("y_axis_down_scroll_threshold",scroll_engine.down_y_scroll_threshold);

        root->InsertEndChild(CameraControls);

        //XMLElement* root2 = doc.NewElement("objects");
        //doc.InsertEndChild(root2);

        XMLElement* ObjectList = doc.NewElement("object_list");

        int i = 0;
        std::string object_name;       
        for(auto& game_objects : graphics_engine.render_buffer)
        {   
            object_name = "game_object_" + std::to_string(i);
            XMLElement* object = doc.NewElement(object_name.c_str());
            object->SetAttribute("object_name",game_objects->object_name.c_str());
            object->SetAttribute("x_position",game_objects->physics.position.x-int(scroll_engine.accumulated_x));
            object->SetAttribute("y_position",game_objects->physics.position.y-int(scroll_engine.accumulated_y));
            object->SetAttribute("camera_active",game_objects->camera.camera_active);
            ObjectList->InsertEndChild(object);
            i += 1;

        }
        //ObjectList->SetAttribute("itemCount", graphics_engine.render_buffer.size());
        ObjectList->SetAttribute("itemCount",float(graphics_engine.render_buffer.size()));

        root->InsertEndChild(ObjectList);

        // Save the XML document to a file
        std::string scene_name_and_dir= "./game_data/scenes/"  + std::string(scene_name) + ".xml";

        if (doc.SaveFile(scene_name_and_dir.c_str()) == XML_SUCCESS) { 
            std::cout << "XML document created successfully." << std::endl;
        } else {
            std::cout << "Error saving XML document." << std::endl;
        }


                // update scenes vector
         available_scenes.clear();
         available_scene_names.clear();
        for (const auto& entry : std::filesystem::directory_iterator("./game_data/scenes"))
        {
            if (entry.path().extension() == ".xml") {
                    available_scenes.push_back(entry.path().string()); 
                    available_scene_names.push_back(entry.path().filename().replace_extension(""));

            }
        }
        selected_scene = NULL;
        
        }

        ImGui::SetNextItemWidth(256);
        
       if (ImGui::BeginCombo("available scenes",selected_scene))
        {

            int i = 0;
            for (auto&scenes : available_scenes)
            {
                bool is_selected = (selected_scene == scenes.c_str());

                if (ImGui::Selectable(scenes.c_str(), is_selected))
                {
                    selected_scene = scenes.c_str();
                    std::strcpy(scene_name ,available_scene_names[i].c_str());
                    
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
                i++;
            }
            ImGui::EndCombo();

            
        }
       
        ImGui::SameLine();
        if (ImGui::Button("Load Scene"))
        {
            if (selected_scene != NULL)
            {
            // pause the engine
            play_pause = false;

            // clear the render buffer 
            graphics_engine.render_buffer.clear();

            // clear accumulated x&y
            scroll_engine.accumulated_x = 0;
            scroll_engine.accumulated_y = 0;

            // open scene xml file
            XMLDocument scene;
            scene.LoadFile(selected_scene);  
            XMLElement* root = scene.RootElement();

            // load engine controls
            XMLElement* engine_controls_element = root->FirstChildElement("engine_controls");
           
            frames_per_second_f = std::atof(engine_controls_element->Attribute("frames_per_second"));
            graphics_engine.grid_size = std::atoi(engine_controls_element->Attribute("grid_size"));
            const char* true_str = "true";
            view_grid = stringToBool(engine_controls_element->Attribute("view_grid"));
            snap_to_grid = stringToBool(engine_controls_element->Attribute("snap_to_grid"));
            scroll_engine.move_speed = std::atoi(engine_controls_element->Attribute("move_speed"));
            move_world_enabled = stringToBool(engine_controls_element->Attribute("move_world"));


            // load scene controls
            XMLElement* scene_controls_element = root->FirstChildElement("scene_controls");
            scene_color.w = std::atof(scene_controls_element->Attribute("scene_color_w"));
            scene_color.x = std::atof(scene_controls_element->Attribute("scene_color_x"));
            scene_color.y = std::atof(scene_controls_element->Attribute("scene_color_y"));
            scene_color.z = std::atof(scene_controls_element->Attribute("scene_color_z"));


            // load camera controls
            XMLElement* camera_controls_element = root->FirstChildElement("camera_controls");
            scroll_engine.left_x_scroll_threshold = std::atof(camera_controls_element->Attribute("x_axis_left_threshold"));
            scroll_engine.right_x_scroll_threshold = std::atof(camera_controls_element->Attribute("x_axis_right_threshold"));
            scroll_engine.up_y_scroll_threshold = std::atof(camera_controls_element->Attribute("y_axis_up_scroll_threshold"));
            scroll_engine.down_y_scroll_threshold = std::atof(camera_controls_element->Attribute("y_axis_down_scroll_threshold"));


            XMLElement* objectList = root->FirstChildElement("object_list");
            
            int i = 0;
            std::string object_name = "game_object_" + std::to_string(i);

            XMLElement * gameObject = objectList->FirstChildElement("game_object_0");
            
            float xPos, yPos;
            bool cameraActive;
            // load objects 
            while (gameObject != nullptr)

            {   //std::cout << gameObject << std::endl;
                // Access the attributes of the game_object element
                const char* objectName = gameObject->Attribute("object_name");
                xPos = std::atof(gameObject->Attribute("x_position"));
                yPos = std::atof(gameObject->Attribute("y_position"));
                //std::cout << "xPos= " << xPos << " yPos " << yPos << std::endl;
                gameObject->QueryBoolAttribute("camera_active", &cameraActive);
                object_handler.generate_object(objectName,ImVec2(xPos,yPos), cameraActive);
                ++i;
                std::string object_name = "game_object_" + std::to_string(i);
                gameObject = objectList->FirstChildElement(object_name.c_str());

            }
            }
        }
        
        ImGui::ColorPicker3("Scene Color", (float*) &scene_color);

        ImGui::End();
}


/* Function: object_view_interface
*
* Purpose: undecided. coming soon
*/
void EngineInterface::object_view_inteface(){

}

/**************************************/
// Non-Viewable Menus at Engine Startup
/**************************************/

/* Function: add_object_menu
*
* Purpose: This function draws the add_object_menu()
* for this window to appear the show_add_object_menu
* flag must be set true
*/
void EngineInterface::add_object_menu()
{

    ImGui::Begin("Add a New Object");
        ImGui::InputText("Object Name", object_info.object_name,IM_ARRAYSIZE(object_info.object_name));
        
        const char* items[] = {"Background","Mid-Background","Mid-Foreground","ForeGround"};
        ImGui::Combo("Draw Layer", &object_info.draw_layer_index,items,IM_ARRAYSIZE(items));

        if (ImGui::BeginCombo("Default Sprite",object_info.default_sprite))
        {

            for (auto&asset_item : object_info.available_assets)
            {
                bool is_selected = (object_info.default_sprite == asset_item.c_str());

                if (ImGui::Selectable(asset_item.c_str(), is_selected))
                {
                    object_info.default_sprite = asset_item.c_str();
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        if (ImGui::Button("Save"))
        {
            show_add_object_menu = false;
            object_util.create_object_files(object_info.object_name,object_info.default_sprite);
            object_util.add_object(object_info.object_name);
            system("make all; ./restart_engine.sh&");
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            show_add_object_menu = false;
            // don't process data;
        }
    ImGui::End();
}

/* Function: camera_controls
*
* Purpose: This function draws the camera controls
* window and contains the camera controls logic
*/
void EngineInterface::camera_controls(){
    ImGui::Begin("Camera Controls");
    ImGui::Checkbox("Select Object to Follow",&select_follow_object);
    if (select_follow_object)
    {
        if (input_engine.left_click)
            {
                for (auto& objects : graphics_engine.render_buffer)
                {
                    if (objects->collider.in_rect(ImGui::GetMousePos().x, ImGui::GetMousePos().y))
                    {
                        objects->camera.camera_active = true;
                        select_follow_object = false;
                    } else {
                        objects->camera.camera_active = false;
                    }
                }
            } 

    }
    ImGui::SetNextItemWidth(128);
    ImGui::SliderFloat("x-axis left scroll threshold",&scroll_engine.left_x_scroll_threshold,graphics_engine.width/2,graphics_engine.width);
    ImGui::SetNextItemWidth(128);
    ImGui::SliderFloat("x-axis right scroll threshold",&scroll_engine.right_x_scroll_threshold,0,graphics_engine.width/2);
    ImGui::SetNextItemWidth(128);
    ImGui::SliderFloat("y-axis up scroll threshold",&scroll_engine.up_y_scroll_threshold,0,graphics_engine.height/2);
    ImGui::SetNextItemWidth(128);
    ImGui::SliderFloat("y-axis down scroll threshold",&scroll_engine.down_y_scroll_threshold,graphics_engine.height/2,graphics_engine.height);
    ImGui::End();
}
