#pragma once

typedef enum : unsigned int
{
	COMPONENT_NONE = 0,
	COMPONENT_SPRITE = 1 << 0,
	COMPONENT_BOX2DPHYSICS = 1 << 1,
	COMPONENT_INPUT = 1 << 2,
	COMPONENT_TOTAL = 1 << 3,
} ComponentType;