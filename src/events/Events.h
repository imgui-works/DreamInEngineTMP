#pragma once

class Scene;

namespace Events
{
	class Events
	{
	public:
		Events(Scene* scene);
	};

#pragma region All Events Data
	struct OnProcessInputs
	{
		std::vector<InputEnum> inputs;
	};

	// Called when a new entity is created.
	struct OnEntityCreated
	{
		unsigned int entity_id;
	};

	// Called when an entity is about to be destroyed.
	struct OnEntityDestroyed
	{
		unsigned int entity_id;
	};

	// Called when a component is assigned (not necessarily created).
	template<typename T>
	struct OnComponentAssigned
	{
		unsigned int entity_id;
	};

	// Called when a component is removed
	template<typename T>
	struct OnComponentRemoved
	{
		unsigned int entity_id;
	};
#pragma endregion 

}
