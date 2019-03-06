//
// Created by ThomasBI on 30/01/2018.
//

#ifndef DREAMINENGINE_SCENE_H
#define DREAMINENGINE_SCENE_H

#include <string>
#include <unordered_map>
#include <list>

#include <components/BoxPhysics.h>
#include <entities/Entity.h>
#include <utils/ComponentStore.h>
#include <components/Sprite.h>
#include <components/Input.h>
#include <utils/InputEnum.h>

#include <utils/types.h>
#include <events/Events.h>
#include <events/EventSubscriber.h>
#include <set>

template<typename T>
TypeIndex getTypeIndex()
{
	return std::type_index(typeid(T));
}

class SceneManager;

// WARN: ONLY CALL System (predefine) in .h -> Implementation in .cpp 'cause not polymorphic use needed from scene
class System;

class Scene {
public:
	Scene(SceneManager *sceneManager, std::string sceneName);

	void update();

	void render();

	void add_sprite(unsigned int entity_id, Sprite* sprite);

	void add_box_physics(Entity *entity, int x, int y, int w, int h, bool dyn);

	void add_input(Entity *entity);

	void setName(std::string name);

	std::string getName() const;

	b2World* getWorld() const;

	ComponentStore<Entity>& getEntities();

	ComponentStore<Sprite>& getSprites();

	ComponentStore<BoxPhysics>& getBoxPhysics();

	ComponentStore<Input>& getInputs();

	~Scene();

	/**
	* Subscribe to an event.
	*/
	template<typename T>
	inline void subscribe(EventSubscriber<T>* subscriber)
	{
		auto index = getTypeIndex<T>();
		auto found = subscribers.find(index);
		if (found == subscribers.end())
		{
			std::vector<BaseEventSubscriber*> subList;
			subList.push_back(subscriber);

			subscribers.insert({ index, subList });
		}
		else
		{
			found->second.push_back(subscriber);
		}
	}

	/**
	* Unsubscribe from an event.
	*/
	template<typename T>
	inline void unsubscribe(EventSubscriber<T>* subscriber)
	{
		auto index = getTypeIndex<T>();
		auto found = subscribers.find(index);
		if (found != subscribers.end())
		{
			found->second.erase(std::remove(found->second.begin(), found->second.end(), subscriber), found->second.end());
			if (found->second.size() == 0)
			{
				subscribers.erase(found);
			}
		}
	}

	/**
	* Unsubscribe from all events. Don't be afraid of the void pointer, just pass in your subscriber as normal.
	*/
	inline void unsubscribeAll(void* subscriber)
	{
		for (auto kv : subscribers)
		{
			/*kv.second.erase(std::remove(kv.second.begin(), kv.second.end(), subscriber), kv.second.end());
			if (kv.second.size() == 0)
			{
			subscribers.erase(kv.first);
			}*/
		}
	}

	/**
	* Emit an event. This will do nothing if there are no subscribers for the event type.
	*/
	template<typename T>
	inline void emit(const T& event)
	{
		auto found = subscribers.find(getTypeIndex<T>());
		if (found != subscribers.end())
		{
			for (auto* base : found->second)
			{
				auto* sub = reinterpret_cast<EventSubscriber<T>*>(base);
				sub->receive(this, event);
			}
		}
	}

	// TODO: Check if the specified type is derived from "System" (Base class)
	/* System Management */
	template<typename TSystem>
	inline bool add_system(unsigned int filter = 0)
	{
		// Find type index
		const TypeIndex type_index_system = getTypeIndex<TSystem>();

		// Check type existence
		bool system_type_exists = false;
		for(auto &system_type_iterator : m_system_types)
		{
			// System exists IF type found
			if (system_type_iterator.first == type_index_system) system_type_exists = true;
		}

		// If type already (found) exists => System already exists => Error message
		if(system_type_exists)
		{
			printf("Error: System Already Exists\n");
			return false;
		}

		// System not exists => Create & Add system to system list
		auto system = new TSystem(this);
		system->Mask = filter; // TODO: add the requirement (mask) filter !?!

		// Create System & Reference to it
		m_systems.push_back(system);
		m_system_types[type_index_system] = m_systems.back(); // TODO: see if a double pointer is useful and/or better or not for non-copying the object => VERY IMPORTANT: DO TESTS about this case !!!!!!!!

		// Find all matching entities for the created System
		match_entities<TSystem>();

		return true;
	}

	template<typename TSystem>
	inline TSystem *get_system()
	{
		// Find type index
		return (TSystem*)m_system_types[getTypeIndex<TSystem>()];
	}

	// @return unsigned int : number of different systems matched ?
	void match(unsigned int entity_id, unsigned int entity_mask);

	void unmatch(unsigned int entity_id, unsigned int entity_mask);

	// Find all matching entities for a freshly created System type
	// TEST: test if it works
	template<typename TSystem>
	void match_entities()
	{
		// TODO: check if "auto" needs to have a "delete" for deleting a pointer
		auto system = get_system<TSystem>();
		for(auto entity : getEntities().getVector()) // loop over all entities
		{
			if ((entity->mask & system->Mask) == system->Mask) // entity meets the system (component) requirements
			{
				system->Entities.insert(entity->id);
			}
		}
	}

	// Clear all matching entities for a specific System type.
	// NOTE: useless ?
	template<typename TSystem>
	void unmatch_entities()
	{
		auto &system = get_system<TSystem>();
		system.Entities.clear();
	}

	// @TODO: Find a way to improve this method which will SLOW DOWN (A LOT) the program
	/* Get all Matching Entities for a given system */
	template<typename TSystem>
	inline std::set<unsigned int>& matching_entities()
	{
		return ( (TSystem*)get_system<TSystem>())->Entities; // Get a system Set of entity matches
	}

	std::list<System*> m_systems; // system list

private:
	// Scene data
	SceneManager* m_sceneManager = nullptr;
	std::string m_name;

	// Box2D
	b2World* m_world;

	// Scene entities
	ComponentStore<Entity> m_entities;
	// Scene components
	ComponentStore<BoxPhysics> m_box_physique;
	ComponentStore<Sprite> m_sprites;
	ComponentStore<Input> m_inputs;

	// Subscribers' list
	std::unordered_map<TypeIndex, std::vector<BaseEventSubscriber*>, std::hash<TypeIndex>> subscribers;

	// NOTE: this one below is an improvement..
	//std::unordered_map<std::type_index, unsigned int> m_system_requirements; // System components/masks requirements (for entity matching)
	//std::unordered_map<std::type_index, std::set<unsigned int>> m_matching_entities;
	/* TODO: checkt this line, maybe it's useless now */ std::unordered_map<std::type_index, System*> m_system_types; // <index_of_system_type, ptr_to_system_in_memory>
};

#endif //DREAMINENGINE_SCENE_H
