//
// Created by ThomasBI on 30/01/2018.
//

#ifndef DREAMINENGINE_PLAYERCONTROL_H
#define DREAMINENGINE_PLAYERCONTROL_H

#include <systems/System.h>

class PlayerControl : public System
{
	PlayerControl(Scene* scene);

	void update() override;
};

#endif //DREAMINENGINE_PLAYERCONTROL_H
