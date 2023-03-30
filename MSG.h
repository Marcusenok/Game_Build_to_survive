#include"House.h"
#include"Sawmill.h"
#include"HuntersHouse.h"
#include"Kitchen.h"
#include"Hospital.h"

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
