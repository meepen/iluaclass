#ifndef CLUABASE_H
#define CLUABASE_H

#include "ILuaBase.h"
#include <vector>

class CLuaInterface : public ILuaBase
{
	bool ValidClassID(unsigned char typenum) { return typenum < name_ids.size(); }

	virtual ILuaClass<void *> *GetLuaUserDataUnknown(unsigned char typenum, int stack = 0) override;
	virtual unsigned char CreateClassTypeUnknown(LuaClassInitializer initializer, LuaMetaTableIndex *metafuncs, size_t userdata_length, const char *name) override;
	virtual ILuaClass<void *> *CreateClassInstanceUnknown(unsigned char typenum) override;
	virtual const char *UserDataTypeName(unsigned char typenum) override;
	virtual size_t UserDataTypes() override;

public:
	CLuaInterface();

	lua_State *state;
	std::vector<const char *> name_ids;
	std::vector<LuaClassInitializer> class_initializers;
	std::vector<size_t> class_ud_lengths;

};

extern CLuaInterface g_Lua;

#endif // CLUABASE_H