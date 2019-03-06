//
// Created by ThomasBI on 30/01/2018.
//

#ifndef DREAMINENGINE_SYSTEM_H
#define DREAMINENGINE_SYSTEM_H

#include <scenes/Scene.h>
#include <set>

class System /*: public Requires<Position, Velocity>*/ {
public:
	System(Scene* scene) : m_scene(scene), Mask(0) /*, m_type(getTypeIndex<System>())*/
	{

	}

	virtual void update() = 0;

	unsigned int Mask;

	std::set<unsigned int> Entities;

protected:
	Scene * m_scene;
	// TypeIndex m_type;
	//std::set<unsigned int> entities; // <=> matching entities (required components) for this system
	//unsigned int m_mask;
	std::string m_name;
};

#endif //DREAMINENGINE_SYSTEM_H
