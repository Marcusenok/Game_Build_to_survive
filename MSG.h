#pragma once
#include"House.h"

enum class MsgType { Create };

struct MSG
{
	MsgType type;
	House* sender;
	union
	{
		struct {
			House* new_object;
		} create;
	};

	MSG();
};
