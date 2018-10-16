#ifndef DREAMINENGINE_INPUTSYSTEM_H
#define DREAMINENGINE_INPUTSYSTEM_H

#include "System.h"

class InputSystem : public System, public EventSubscriber<Events::OnProcessInputs> {
public :
	InputSystem(Scene* scene);

	void update() override;

	void receive(Scene* scene, const Events::OnProcessInputs& event) override;

	~InputSystem();

private:
	bool m_key_repeat;

	std::vector<InputEnum> m_input_instructions;
};



#endif