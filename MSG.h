#include"House.h"
#include"Sawmill.h"
#include"HuntersHouse.h"

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
