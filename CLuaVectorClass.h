#ifndef CLUAINTERFACE_H
#define CLUAINTERFACE_H
#include "ILuaBase.h"
#include <algorithm>
#include <vector>

struct Vector
{
	float x, y, z;
};

class CLuaVectorClass : public ILuaClass<Vector>
{
public:
	typedef size_t UserDataContents;

public:
	virtual Vector *GetData() override;
	virtual void SetData(Vector *data) override
	{
		*GetData() = *data;
	}

public:
	void Init(Vector *data);

public:
	UserDataContents *Contents() { return reinterpret_cast<UserDataContents *>(ud->data); }
};

static_assert(sizeof CLuaVectorClass == sizeof ILuaClass<void *>, "Class added extra data - not allowed!");

extern void BlankLuaVectorClass(ILuaClass<Vector> *);

#endif // CLUAINTERFACE_H