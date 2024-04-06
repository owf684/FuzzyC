#define MARIO_H
#ifndef MARIO_H
#include "../../../includes/objects/game_object.h"
#include "../../../includes/engines/input_engine.h"
class mario : public GameObject
{
public:
mario();
void update(InputEngine& input_enigne) override;
};
#endif
