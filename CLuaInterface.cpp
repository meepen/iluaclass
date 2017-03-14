#include "CLuaInterface.h"
#include "lua.hpp"
#include <cstdint>

template <typename T>
constexpr T *offset(void *base, uintptr_t offset)
{
	return reinterpret_cast<T *>(offset + uintptr_t(base));
}

CLuaInterface::CLuaInterface()
{
	state = luaL_newstate();
	luaL_openlibs(state);
}

unsigned char CLuaInterface::CreateClassTypeUnknown(LuaClassInitializer initializer, LuaMetaTableIndex *metafuncs, size_t userdata_length, const char *name)
{
	luaL_newmetatable(state, name);
	while (metafuncs && metafuncs->name)
	{
		lua_pushstring(state, metafuncs->name);
		lua_pushcfunction(state, metafuncs->fn);
		lua_settable(state, -3);
		metafuncs++;
	}

	lua_pushstring(state, "__index");
	lua_gettable(state, -2);
	if (lua_type(state, -1) != LUA_TNIL)
	{
		lua_pop(state, 1);
		lua_pushstring(state, "__index");
		lua_pushvalue(state, -2);
		lua_settable(state, -3);
	}
	else
		lua_pop(state, 1);

	lua_pop(state, 1);


	class_initializers.push_back(initializer);
	name_ids.push_back(name);
	class_ud_lengths.push_back(userdata_length);
	return name_ids.size() - 1;
}

ILuaClass<void *> *CLuaInterface::GetLuaUserDataUnknown(unsigned char typenum, int stack)
{
	if (!ValidClassID(typenum))
	{
		return nullptr;
	}

	UserData *ud = reinterpret_cast<UserData *>(luaL_checkudata(state, stack, name_ids[typenum]));
	ILuaClass<void *> *inst = offset<ILuaClass<void *>>(ud->data, class_ud_lengths[typenum]);
	class_initializers[typenum](inst);
	inst->ud = ud;

	return inst;
}

ILuaClass<void *> *CLuaInterface::CreateClassInstanceUnknown(unsigned char type)
{
	if (!ValidClassID(type))
	{
		return nullptr;
	}


	UserData *ud = reinterpret_cast<UserData *>(lua_newuserdata(state, sizeof UserData + class_ud_lengths[type] + sizeof ILuaClass<void *>));
	ud->data = &ud[1];

	ILuaClass<void *> *inst = offset<ILuaClass<void *>>(ud->data, class_ud_lengths[type]);
	inst->ud = ud;

	class_initializers[type](
		inst
	);

	luaL_newmetatable(state, name_ids[type]);
	lua_setmetatable(state, -2);

	return inst;
}

const char *CLuaInterface::UserDataTypeName(unsigned char typenum)
{
	return name_ids[typenum];
}

size_t CLuaInterface::UserDataTypes()
{
	return name_ids.size();
}

CLuaInterface g_Lua;