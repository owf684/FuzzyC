/* Name of Program: collider_component
*
*  Purpose: this contains all relevant 
*  data and functions needed for detecting
*  collisions with other objects
*  This program does not handle collision 
*  detection. This is done in the collision 
*  engine 
*
*  Author: Christopher Corona
*
*  Version: v0.1.0
*
*  Assumptions: None 
*
*/

#include "collider_component.h"

// Constructor
ColliderComponent::ColliderComponent()
{
    is.down = false;
    is.up = false;
    is.right = false;
    is.left = false;
}

/* Function: top()
*
*  Purpose: This function
*  returns the y coordinate 
*  of the collider box. 
*  Which is by default the top
*  of the box
*
*/

int ColliderComponent::top()
{
    return box.y;
}

/* Function: bottom()
*
*  Purpose: This function
*  returns the y coordinate
*  of the collider boxes bottom
*
*/

int ColliderComponent::bottom()
{
    return box.y+box.h;
}

/* Function: left()
*
*  Purpose: This function
*  returns the x coordinate
*  of the collider box
*  which is by defualt
*  the left side
*
*/

int ColliderComponent::left()
{
    return box.x;
}

/* Function: right()
*
* Purpose: This function 
* returns the x coordinate
* of the collider box's 
* right side
*
*/

int ColliderComponent::right()
{
    return box.x + box.w;
}

/* Function: center_x()
*
* Purpose: This function 
* returns the center x
* coordinate of the of 
* the colliders box
*
*/

int ColliderComponent::center_x()
{
    return box.x + (box.w/2);
}

/* Function: center_y()
*
* Purpose: This function 
* returns the center y 
* coordinate of the box
* colliders
*/

int ColliderComponent::center_y()
{
    return box.y + (box.h/2);
}

/* Function: reset()
* 
*  Purpose: This function
*  sets all the is struct
*  variables false
*/

void ColliderComponent::reset()
{
    is.down = false;
    is.up = false;
    is.right = false;
    is.left = false;    
}


/* Function: in_rect()
*
* Purpose: This function
* returns true if given x, y coords
* are with in the boxes rect
*/

bool ColliderComponent::in_rect(float x, float y)
{
    if ( x > left() && x < right())
    {   
        if (y > top() && y < bottom())
        {
            return true;
        }
    }

    return false;
}