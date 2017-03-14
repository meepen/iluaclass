#ifndef LUAINTERFACE_H
#define LUAINTERFACE_H
#include "UserData.h"
#include "ILuaClass.h"
#include <type_traits>


struct lua_State;
typedef int (*lua_CFunction)(lua_State *);
struct LuaMetaTableIndex
{
	const char *name;
	lua_CFunction fn;
};

struct lua_State;
typedef void(*LuaClassInitializer)(ILuaClass<void *> *);

class ILuaBase
{
public:
	template <typename T>
	ILuaClass<T> *GetLuaUserData(unsigned char typenum, int stack = 0)
	{
		return reinterpret_cast<ILuaClass<T> *>(GetLuaUserDataUnknown(typenum, stack));
	};

	template <typename T>
	unsigned char CreateClassType(void (*initializer)(ILuaClass<T> *), LuaMetaTableIndex *metafuncs, size_t userdata_length, const char *name)
	{
		return CreateClassTypeUnknown((LuaClassInitializer)initializer, metafuncs, userdata_length, name);
	}

	template <typename T>
	ILuaClass<T> *CreateClassInstance(unsigned char typenum)
	{
		return reinterpret_cast<ILuaClass<T> *>(CreateClassInstanceUnknown(typenum));
	}

private: 
	virtual ILuaClass<void *> *GetLuaUserDataUnknown(unsigned char typenum, int stack = 0) = 0;
	virtual unsigned char CreateClassTypeUnknown(LuaClassInitializer initializer, LuaMetaTableIndex *metafuncs, size_t userdata_length, const char *name) = 0;
	virtual ILuaClass<void *> *CreateClassInstanceUnknown(unsigned char typenum) = 0;

public:
	virtual const char *UserDataTypeName(unsigned char typenum) = 0;
	virtual size_t UserDataTypes() = 0;

};

#endif // LUAINTERFACE_H