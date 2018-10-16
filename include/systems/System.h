//
// Created by ThomasBI on 30/01/2018.
//

#ifndef DREAMINENGINE_SYSTEM_H
#define DREAMINENGINE_SYSTEM_H

#include <scenes/Scene.h>

class System {
public:
	System(Scene* scene) : m_scene(scene)/*, m_type(getTypeIndex<System>())*/
	{

	}

	virtual void update() = 0;

protected:
	Scene* m_scene;
	// TypeIndex m_type;
};

#endif //DREAMINENGINE_SYSTEM_H
