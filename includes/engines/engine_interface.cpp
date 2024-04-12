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
#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif



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
                    object_handler.generate_object(selected_object,snapped_position);


                } else {object_handler.generate_object(selected_object,ImGui::GetMousePos());}
            
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
                for (auto& objects : graphics_engine.render_buffer)
                {
                    if (objects->collider.in_rect(ImGui::GetMousePos().x, ImGui::GetMousePos().y))
                    {
                        auto it = std::find(graphics_engine.render_buffer.begin(),graphics_engine.render_buffer.end(),objects);
                        if (it != graphics_engine.render_buffer.end())
                        {
                            graphics_engine.render_buffer.erase(it);
                            break;
                        }
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
    if (ImGui::Button("New Scene"))
    {

    }
    ImGui::SameLine();

    if (ImGui::Button("Remove Scene"))
    {

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
