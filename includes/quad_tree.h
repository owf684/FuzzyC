#include <memory>
#include <list>
#include <vector>
#include <iostream>
#include <iterator>

#define TOP_LEFT_QUAD 0
#define BOTTOM_LEFT_QUAD 1
#define TOP_RIGHT_QUAD 2
#define BOTTOM_RIGHT_QUAD 3
#define MAX_LAYERS 8


// book keeping for data getting added

template <typename T>
struct item_locator {
    T item;
    std::list<T>* item_list_ref;
    typename std::list<T>::iterator item_it;
    bool in_quad_tree;
};

struct Point {
    float x;
    float y;

    Point(float x_in, float y_in) {x = x_in; y = y_in;}
    Point() { x = 0; y = 0; }
};


template <typename T>
class QuadTree 
{

    public:
        int layer; // root is 0
        // Constructors
        QuadTree() // create unit quad tree
        {
            width = 1;
            height = 1;
            area = 1;
        }

        // points defined by user
        QuadTree(Point top_left_in, Point bottom_right_in){
            top_left = top_left_in;
            bottom_right = bottom_right_in;
            top_left.x -= 100;
            top_left.y -= 100;
            bottom_right.x += 100;
            bottom_right.y += 100;
            width = bottom_right.x - top_left.x;
            height = bottom_right.y - top_left.y;
            area = width*height;

            // Populate children with nulls
            for(int i = 0; i < 4; i++)
           {
                children.push_back(NULL);
            }

        }


        /*
        * Function: bool contains(T& item)
        *
        * Arguments: T& item
        *
        * Assumptions: This function assumes that argument item has the functions getX(), getY(), getWidth(), getHeight()
        * These get functions are necessary. Please update object and include these functions.
        *
        * Purpose: This functions determines whether object item can be contained within any given Quadrant.
        * returns true if it can and false if it cant
        */
        bool contains(T& item)
        {
            return ( item->getX() >= top_left.x && item->getX() < bottom_right.x &&
                     item->getX() + item->getWidth() > top_left.x && item->getX() + item->getWidth() <= bottom_right.x &&

                     item->getY() >= top_left.y && item->getY() < bottom_right.y &&
                     item->getY() + item->getHeight() > top_left.y && item->getY() + item->getHeight() <= bottom_right.y );

        }
        bool contains(typename std::list<T>::iterator& item)
        {
            return ( (*item)->getX() >= top_left.x && (*item)->getX() < bottom_right.x &&
                     (*item)->getX() + (*item)->getWidth() > top_left.x && (*item)->getX() + (*item)->getWidth() <= bottom_right.x &&

                     (*item)->getY() >= top_left.y && (*item)->getY() < bottom_right.y &&
                     (*item)->getY() + (*item)->getHeight() > top_left.y && (*item)->getY() + (*item)->getHeight() <= bottom_right.y );

        }

        /*
        * Function: void insert(T& item)
        *
        * Arguments: T& item
        *
        * Purpose: This inserts item into
        * the smallest quadrant available
        */
        bool insert(T& item, QuadTree<T>* parent, item_locator<T>& item_locator)
        {
            layer = parent->layer+1;

            if (item == nullptr) return false;

            if (!contains(item)) return false;

            // insert into parent if it can't contain it anymore
            if ( layer >= MAX_LAYERS)
            {
                items.push_back(item);
                item_locator.item = item;
                item_locator.item_list_ref = &items;
                item_locator.item_it = std::prev(items.end());
                return true;
            }

            float mid_x = (top_left.x + bottom_right.x) / 2.0;
            float mid_y = (top_left.y + bottom_right.y) / 2.0;

            // left quadrant
            if (item->getX() < mid_x)

                // top left quadrant
                if (item->getY() < mid_y)
                {
                    if (children[TOP_LEFT_QUAD] == NULL)
                        children[TOP_LEFT_QUAD] = new QuadTree( top_left, Point ( mid_x, mid_y) );

                    children[TOP_LEFT_QUAD]->insert(item, this, item_locator);

                // bottom left quadrant
                } else {
                    if (children[BOTTOM_LEFT_QUAD] == NULL)
                        children[BOTTOM_LEFT_QUAD] = new QuadTree( Point(top_left.x, mid_y ), Point( mid_x, bottom_right.y ) );

                    children[BOTTOM_LEFT_QUAD]->insert(item, this, item_locator);
                }
            // right quadrant
            else {

                 // top right quadrant
                if (item->getY() < mid_y)
                {
                    if (children[TOP_RIGHT_QUAD] == NULL )
                        children[TOP_RIGHT_QUAD] = new QuadTree( Point( mid_x, top_left.y ) , Point( bottom_right.x, mid_y ) );

                    children[TOP_RIGHT_QUAD]->insert(item, this,item_locator);

                // bottom right quadrant
                } else {

                    if (children[BOTTOM_RIGHT_QUAD] == NULL)
                        children[BOTTOM_RIGHT_QUAD] = new QuadTree( Point( mid_x, mid_y ), bottom_right );

                    children[BOTTOM_RIGHT_QUAD]->insert(item, this,item_locator);
                }

            }
        }

        /*
        * Function: void search(T& item, std::list<T*>& item_list)
        *
        * Arguments: T& item, std::list<T*> &item_list
        *
        * Purpose: This function recurses through the quad
        * tree and finds the item by locating the smallest
        * possible quadrant it can fit into. The items list of
        * given quadrant is then inserted into list item_list
        */
        void search(T& item, std::list<T>& item_list, QuadTree<T>* parent)
        {

            layer = parent->layer+1;

            if (item == nullptr) return;

            if (!contains(item) ) return;

            // insert into parent if it can't contain it anymore
            if (layer >= MAX_LAYERS)
            {
                item_list.insert(item_list.end(), items.begin(), items.end());
                //parent->search_nearby(item_list);
                return;
            }

            float mid_x = (top_left.x + bottom_right.x) / 2.0;
            float mid_y = (top_left.y + bottom_right.y) / 2.0;

            // left quadrant
            if (item->getX() < mid_x) {

                // top left quadrant
                if (item->getY() < mid_y)
                {
                    if (children[TOP_LEFT_QUAD] != NULL)
                        children[TOP_LEFT_QUAD]->search(item, item_list, this);
                // bottom left quadrant
                } else {
                    if (children[BOTTOM_LEFT_QUAD] != NULL)
                        children[BOTTOM_LEFT_QUAD]->search(item, item_list, this);

                }
            // right quadrant
            } else {

                 // top right quadrant
                if (item->getY() < mid_y)
                {
                    if (children[TOP_RIGHT_QUAD] != NULL)
                        children[TOP_RIGHT_QUAD]->search(item, item_list, this);

                // bottom right quadrant
                } else {
                    if (children[BOTTOM_RIGHT_QUAD] != NULL)
                        children[BOTTOM_RIGHT_QUAD]->search(item, item_list, this);
                }

            }

        }

        /*
        * Function: void search_nearby(std::list<T*>& item_list
        *
        * Arguments: std::list<T*>& item_list
        *
        * Purpose: This function searches the children and the childrens
        * children for items list larger than 0. These lists are then
        * inserted into list item_list
        *
        * Note: might not be needed... foolish dumb ass
        */
        void search_nearby(std::list<T>& item_list)
        {
            for ( int i = 0; i < 4; i ++ )
            {
                if (children[i] != nullptr)
                {
                    item_list.insert(item_list.end(),children[i]->items.begin(), children[i]->items.end());
                    children[i]->search_nearby(item_list);

                }
            }
        }


        /*
        * Function: void clear()
        *
        * Purpose: This functions recursively clears the item list
        * of the parent and all of the children quads till there is
        * nothing left
        */
        void clear()
        {
           
            items.clear();

            for(int i = 0; i < 4; ++i)
            {
                if (children[i] != NULL)
                    children[i]->clear();
                    return;
            }
            
        }

        /*
        * Function: remove(T& item, QuadTree<T>* parent)
        *
        * Arguments = T& item, QuadTree<T>* parent
        *
        * Purpose: this function remove item from
        * it's containing quad recursively
        */
        void remove( typename std::list<T>::iterator& item, QuadTree<T>* parent)
        {
            // convert item to const iterator
            layer = parent->layer+1;

            if (!contains(item)) return;
            // insert into parent if it can't contain it anymore
            if (layer >= MAX_LAYERS)
            {
                typename std::list<T>::const_iterator c_item = item;
                items.remove(*c_item);
                return;
            }


            float mid_x = (top_left.x + bottom_right.x) / 2.0;
            float mid_y = (top_left.y + bottom_right.y) / 2.0;

            // left quadrant
            if ((*item)->getX() < mid_x)

                // top left quadrant
                if ((*item)->getY() < mid_y)
                {
                    if (children[TOP_LEFT_QUAD] != NULL)
                        children[TOP_LEFT_QUAD]->remove(item, this);
                // bottom left quadrant
                } else {
                    if (children[BOTTOM_LEFT_QUAD]!= NULL)
                        children[BOTTOM_LEFT_QUAD]->remove(item, this);
                }
            // right quadrant
            else {
                 // top right quadrant
                if ((*item)->getY() < mid_y)
                {
                    if (children[TOP_RIGHT_QUAD] != NULL)
                        children[TOP_RIGHT_QUAD]->remove(item, this);

                // bottom right quadrant
                } else {
                    if (children[BOTTOM_RIGHT_QUAD] != NULL)
                        children[BOTTOM_RIGHT_QUAD]->remove(item, this);
                }
            }
        }

    protected:
        float width;
        float height;
        float area;
        Point top_left;
        Point bottom_right;
        std::vector<QuadTree*> children;
        std::list<T>items;
};





// Wrapper for the QuadTree
template <typename T>
class QuadTreeContainer {


    public:
    QuadTree<T> root;
    std::list<item_locator<T> > items;

    QuadTreeContainer(Point top_left, Point bottom_right) : root(top_left, bottom_right)
    {
    }


    void insert(T& item)
    {
        item_locator<T> new_locator;
        if ( root.insert(item, &root,new_locator) )
            new_locator.in_quad_tree = true;
            items.push_back(new_locator);
    }

    void remove(typename std::list< item_locator<T> >::iterator& old_locator)
    {
        // remove from quad tree
        if (old_locator->in_quad_tree)
            old_locator->item_list_ref->erase(old_locator->item_it);

        // erase from item container list
        items.erase(old_locator);
    }

    void reinsert(typename std::list< item_locator<T> >::iterator& old_locator)
    {
        // remove from quad tree
        //root.remove(item, &root);

        if (old_locator->in_quad_tree)
            old_locator->item_list_ref->erase(old_locator->item_it);
        // insert back into the tree
        if (root.insert( old_locator->item, &root, *old_locator) )
            old_locator->in_quad_tree = true;
        else old_locator->in_quad_tree = false;
        

        

    }
    void search(T& item, std::list<T>& items_found)
    {
        root.search(item, items_found, &root);
        return;
    }

    // consider maybe remove this return! seems to be incredibly taxing to copy all that memory
    std::list<T> search(typename std::list< T >::iterator& item)
    {
        std::list<T> items_found;
        root.search((*item), items_found, &root);
        return items_found;
    }

    int size()
    {
        return items.size();
    }

    void clear()
    {
        root.clear();
        items.clear();
    }
    typename std::list< item_locator<T>>::iterator begin()
    {
        return items.begin();
    }

    typename std::list< item_locator<T>>::iterator end()
    {
        return items.end();
    }
    typename std::list< item_locator<T>>::iterator front()
    {
        return items.front();
    }
    typename std::list< item_locator<T>>::iterator back()
    {
        return items.back();
    }

    void pop_back()
    {
        auto item = std::prev(items.end());
        /*insert call to root.remove(item) */
        items.pop_back();
    }

    void pop_front()
    {
        auto item = items.begin();
        /*insert call to root.remove(item) */
        items.pop_front();
    }
};
