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



// debugging
const char* items_2[] = {"A","B","C","D"};

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


    // Our state

    //ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}
void EngineInterface::update()
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    main_menu();


    ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

}




void EngineInterface::main_menu(){

    engine_controls();
    scene_controls();
    object_contorls();

    // non-viewable menus at engine startup 
    if (show_add_object_menu) add_object_menu();

}


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
    ImGui::SliderFloat("FPS",&frames_per_second_f,60.0,120.0);


    
    ImGui::End();
}


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

        }

        ImGui::Checkbox("Place Objects", &place_object_enabled);
        
        if (place_object_enabled)
        {
            if (input_engine.left_click && !already_placed) //bug here when clicking on other menu items objects are placed!
            {
                already_placed = true;
                object_handler.generate_object("Chris",ImGui::GetMousePos());
            
            } else if (!input_engine.left_click && already_placed)
            {
                already_placed = false;
            }
        } 

    ImGui::End();
}


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


void EngineInterface::object_view_inteface(){

}


// Non-Viewable Menus at Engine Startup

void EngineInterface::add_object_menu()
{

    ImGui::Begin("Add a New Object");
        ImGui::InputText("Object Name", object_info.object_name,IM_ARRAYSIZE(object_info.object_name));
        
        const char* items[] = {"Background","Mid-Background","Mid-Foreground","ForeGround"};
        ImGui::Combo("Draw Layer", &object_info.draw_layer_index,items,IM_ARRAYSIZE(items));

        if (ImGui::BeginCombo("Default Sprite",object_info.defaut_sprite))
        {

            for (auto&asset_item : object_info.available_assets)
            {
                bool is_selected = (object_info.defaut_sprite == asset_item.c_str());

                if (ImGui::Selectable(asset_item.c_str(), is_selected))
                {
                    object_info.defaut_sprite = asset_item.c_str();
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
            object_util.create_object_files(object_info.object_name,object_info.defaut_sprite);
            object_util.add_object(object_info.object_name);
            system("make all; ./restart_engine.sh&");
        
            // process data 
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            show_add_object_menu = false;
            // don't process data;
        }
    ImGui::End();
}