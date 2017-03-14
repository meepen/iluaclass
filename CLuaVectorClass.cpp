#include "CLuaVectorClass.h"
#include <array>
#include <sstream>
#include "lua.hpp"
#include "CLuaInterface.h"

extern unsigned char VectorClass;
static std::vector<Vector> vector_array;
static std::vector<int> free_vector_indices = { 0 };

Vector *CLuaVectorClass::GetData()
{
	return &vector_array[*Contents()];
}

void CLuaVectorClass::Init(Vector *data)
{
	size_t empty_index = free_vector_indices.back();
	free_vector_indices.pop_back();

	if (free_vector_indices.size() <= empty_index)
	{
		free_vector_indices.push_back(empty_index + 1);
		if (empty_index + 1 > vector_array.size())
			vector_array.resize(1 + vector_array.size() * 2);
	}

	vector_array[empty_index] = *data;

	*Contents() = empty_index;
}

static Vector vector_origin{ 0, 0, 0 };
void BlankLuaVectorClass(ILuaClass<Vector> *ptr)
{
	auto inst = new (ptr) CLuaVectorClass;
	inst->Init(&vector_origin);
}

static int Vector___tostring(lua_State *state)
{
	// this is bad mmkay pls update when u change it so coroutines do things
	auto v = g_Lua.GetLuaUserData<Vector>(VectorClass, 1)->GetData();
	std::stringstream stream;
	
	stream << "Vector " << v->x << " " << v->y << " " << v->z;

	lua_pushstring(state, stream.str().c_str());
	return 1;
}

LuaMetaTableIndex VectorMetaTable[] = {
	{ "__tostring", Vector___tostring },
	{ 0, 0 }
};