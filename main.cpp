#include "CLuaInterface.h"
#include "CLuaVectorClass.h"
#include "lua.hpp"

unsigned char VectorClass;
extern LuaMetaTableIndex VectorMetaTable[];

int main()
{

	VectorClass = g_Lua.CreateClassType<Vector>(
		BlankLuaVectorClass, VectorMetaTable, sizeof CLuaVectorClass::UserDataContents, "Vector"
	);
	auto state = g_Lua.state;


	lua_pushglobaltable(state);
	lua_pushstring(state, "print");
	lua_gettable(state, -2);
	auto vector_origin = g_Lua.CreateClassInstance<Vector>(VectorClass);
	Vector vector_zero{ 0, 0, 0 };
	vector_origin->SetData(&vector_zero);
	lua_call(state, 1, 0);


}