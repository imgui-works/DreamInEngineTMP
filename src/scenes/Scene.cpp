//
// Created by ThomasBI on 30/01/2018.
//

// TODO: see if it works properly.. (testing ?)
#include <systems/System.h>

#include <scenes/Scene.h>
#include <scenes/SceneManager.h>
#include <utility>
#include "systems/BoxPhysicsSystem.h"
#include "systems/InputSystem.h"

Scene::Scene(SceneManager *sceneManager, std::string sceneName) : m_sceneManager(sceneManager), m_name(
	                                                                  std::move(sceneName)) {
	m_world = new b2World(b2Vec2(0.0, 9.81));
	add_system<BoxPhysicsSystem>(COMPONENT_SPRITE | COMPONENT_BOX2DPHYSICS);
	add_system<InputSystem>(COMPONENT_SPRITE | COMPONENT_INPUT);


//	//// @TEST: system mask well deserved & accessed through inheritance
//	printf("Bs = %d\n", get_system<BoxPhysicsSystem>()->Mask);
//	printf("Is = %d\n", get_system<InputSystem>()->Mask);
//
//	get_system<BoxPhysicsSystem>()->Mask = 10;
//
//	//// @TEST: should output the same as above
//	unsigned int i = 0;
//	for(auto &system : m_systems)
//	{
//		printf("S%d = %d\n", i++, system->Mask);
//	}
}

// TODO: solve inputs case (it is actually broken on purpose)
void Scene::update() {
	static int o = 0;
	for(auto &system : m_systems)
	{
		// @TEST: MODIFY BY REFERENCE a System's value !
		get_system<BoxPhysicsSystem>()->i = ++o;

		system->update();
	}

	// @TEST: System is modified by reference (and not by value !!)

	// TODO: put "timeStep=1.0f/60.0f" to fit the 60FPS refresh rate => realistic simulation
	m_world->Step(1.0 / 60.0, 8, 3);
}

void Scene::render() {
	for (auto &sprite : m_sprites.getVector()) {
		m_sceneManager->update_sprite(sprite);
		m_sceneManager->render_sprite(sprite);
	}
}

Scene::~Scene() {
	for (unsigned int i = 0; i < m_box_physique.getVector().size(); i++) {
		m_world->DestroyBody(m_box_physique.getVector()[i]->getBody());
	}
	m_sprites.kill();
	m_box_physique.kill();
	delete m_world;
	delete m_sceneManager;
}

void Scene::match(unsigned int entity_id, unsigned int entity_mask)
{
	for (auto system : m_systems)
	{
		if ((entity_mask & system->Mask) == system->Mask)
		{
			system->Entities.emplace(entity_id);
			printf("Entity with ID %d, registered to a system\n", entity_id);
		}
	}
}

// IMPORTANT: Unmatch the entity components BEFORE doing any entity_mask modifications !
void Scene::unmatch(unsigned int entity_id, unsigned int entity_mask)
{
	for (auto system : m_systems)
	{
		if ((entity_mask & system->Mask) == system->Mask)
		{
			system->Entities.erase(entity_id);
			printf("Entity with ID %d, UNregistered from a system\n", entity_id);
		}
	}
}

void Scene::add_sprite(unsigned int entity_id, Sprite *sprite) {
	m_sprites.add(sprite, entity_id);
}

void Scene::add_box_physics(Entity *entity, int x, int y, int w, int h, bool dyn) {
	m_box_physique.add(new BoxPhysics(), entity->id);
	m_box_physique.get(entity->id)->addRec(m_world, x, y, w, h, dyn);
	m_world->SetContactListener(m_box_physique.get(entity->id));
}

void Scene::add_input(Entity *entity) {
	m_inputs.add(new Input(), entity->id);
}

void Scene::setName(std::string name)
{
	m_name = name;
}

std::string Scene::getName() const
{
	return m_name;
}

b2World* Scene::getWorld() const
{
	return m_world;
}

ComponentStore<Entity>& Scene::getEntities()
{
	return m_entities;
}

ComponentStore<Sprite>& Scene::getSprites()
{
	return m_sprites;
}

ComponentStore<BoxPhysics>& Scene::getBoxPhysics()
{
	return m_box_physique;
}

ComponentStore<Input>& Scene::getInputs()
{
	return m_inputs;
}

//std::vector<InputEnum>& Scene::get_input_enums()
//{
//	return ...
//}

