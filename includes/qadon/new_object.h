#define NEW_OBJECT_H
#ifndef NEW_OBJECT_H
#include "../../../includes/objects/game_object.h"
#include "../../../includes/engines/input_engine.h"
class new_object : public GameObject
{
public:
new_object();
void update(InputEngine& input_enigne) override;
};
#endif
