#include"../Bildins/House.h"
#include"../Bildins/Sawmill.h"
#include"../Bildins/HuntersHouse.h"
#include"../Bildins/Kitchen.h"
#include"../Bildins/Hospital.h"

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
