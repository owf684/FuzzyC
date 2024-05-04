#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

class ColliderComponent{


    public:
    
    ColliderComponent();

    // custom rect type
    struct Box{
        int x;
        int y;
        int w;
        int h;
    };
    Box box;

    // bools for collision detection
    struct Is{
    bool down;
    bool up;
    bool left;
    bool right;
    };
    
    Is is;

    // return rough estimate of where the box collider is
    int left();
    int right();
    int top();
    int bottom();
    int center_x();
    int center_y();
    void reset();
    bool in_rect(float x, float y);

};

#endif