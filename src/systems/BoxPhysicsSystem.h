//
// Created by ThomasBI on 06/03/2018.
//

#ifndef DREAMINENGINE_BOXPHYSICSSYSTEM_H
#define DREAMINENGINE_BOXPHYSICSSYSTEM_H

#include "System.h"

class BoxPhysicsSystem : public System {
public:
	BoxPhysicsSystem(Scene* scene);

	void update() override;

	int i = 0;
};


#endif //DREAMINENGINE_BOXPHYSICSSYSTEM_H
