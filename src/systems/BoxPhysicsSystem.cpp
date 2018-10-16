//
// Created by ThomasBI on 06/03/2018.
//

#include <systems/BoxPhysicsSystem.h>

BoxPhysicsSystem::BoxPhysicsSystem(Scene* scene) : System(scene)
{
}

void BoxPhysicsSystem::update()
{
	auto &boxs = m_scene->getBoxPhysics();
	auto &sprites = m_scene->getSprites();

	printf("i equals %d", i);

	// TODO: loop over this system's matching entities
	for (std::unordered_map<unsigned int, unsigned int>::iterator it = boxs.getMap().begin(); it != boxs.getMap().end(); ++it) {
		auto itSprite = sprites.getMap().find(it->first);
		if (itSprite != sprites.getMap().end()) {
			Sprite* sprite = sprites.get(itSprite->first);
			BoxPhysics* box = boxs.get(itSprite->first);

			// TODO: PB, solve the conflict between this update and external "sprite Position updates" (e.g. ImGui graphical position modification);
			// NOTE: the PB is that Box2D reset the sprite's position to its current Body => No sprite position update possible out of this class

			/*sprite->Position.x = (float) box->getBody()->GetPosition().x;
			sprite->Position.y = (float) box->getBody()->GetPosition().y;*/

			sprite->Position.x += (float)box->getBody()->GetLinearVelocity().x;
			sprite->Position.y += (float)box->getBody()->GetLinearVelocity().y;
			//std::cout << "LinearVelocity ( " << (float)box->getBody()->GetLinearVelocity().x << " ; " << (float)box->getBody()->GetLinearVelocity().y << " )" << std::endl;
		}
	}
}
