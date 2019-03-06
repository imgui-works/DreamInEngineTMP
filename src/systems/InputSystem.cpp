#include "systems/InputSystem.h"

InputSystem::InputSystem(Scene* scene) : System(scene), m_key_repeat(false)
{
	scene->subscribe(this); // <=> m_scene->subscribe(this);
}

void InputSystem::update()
{
	if (m_input_instructions.empty()) return; // do not process inputs if there is no input, lol

	auto &inputs = m_scene->getInputs();
	auto &sprites = m_scene->getSprites();

	for (std::unordered_map<unsigned int, unsigned int>::iterator it = inputs.getMap().begin(); it != inputs.getMap().end(); ++it) {
		auto itSprite = sprites.getMap().find(it->first);
		if (itSprite != sprites.getMap().end()) {
			Sprite* sprite = sprites.get(itSprite->first);
			Input* input = inputs.get(itSprite->first);

			for (int i = 0; i < m_input_instructions.size(); i++) {
				if (m_input_instructions[i] == input->m_up)
					sprite->Position.y -= input->m_speed_up;
				if (m_input_instructions[i] == input->m_down)
					sprite->Position.y += input->m_speed_down;
				if (m_input_instructions[i] == input->m_right)
					sprite->Position.x += input->m_speed_right;
				if (m_input_instructions[i] == input->m_left)
					sprite->Position.x -= input->m_speed_left;
			}
		}
	}

	if (!m_key_repeat)
	{
		m_input_instructions.clear(); // Reset instructions set -> no key repeat !
	}
}

void InputSystem::receive(Scene* scene, const Events::OnProcessInputs& event)
{
	m_input_instructions = event.inputs;
}

InputSystem::~InputSystem()
{
	m_scene->unsubscribe(this);
}
