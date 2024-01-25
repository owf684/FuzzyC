#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H



class ColliderComponent{


    public:
    
    ColliderComponent();

    // custom rect type
    struct {
        int x;
        int y;
        int w;
        int h;
    } box;

    // bools for collision detection
    struct{
    bool down;
    bool up;
    bool left;
    bool right;
    } is;

    // return rough estimate of where the box collider is
    int left();
    int right();
    int top();
    int bottom();
    int center_x();
    int center_y();
    void reset();
    private:

};








#endif