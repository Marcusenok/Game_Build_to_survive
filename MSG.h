#pragma once
#include"House.h"

enum class MsgType { Create };

struct MSG
{
	MsgType type;
	Bilding* sender;
	union
	{
		struct {
			Bilding* new_object;
		} create;
	};

	MSG();
};
