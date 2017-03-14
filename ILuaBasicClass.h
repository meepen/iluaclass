#ifndef ILUABASECLASS_H
#define ILUABASECLASS_H

#include "ILuaClass.h"

// Warning: all user data information MUST be stored outside of this class. If it's in this class it will break everything.
template <typename T>
class ILuaBasicClass : public ILuaClass
{
public:
	static ILuaClass<T> null()
	{
		ILuaClass<T> inst;
		inst.ud = nullptr;
		return inst;
	}

	bool IsValid()
	{
		return ud != nullptr;
	}

public: // virtual override

	virtual T *GetData() override
	{
		return reinterpret_cast<T *>(ud->data);
	}

	virtual void SetData(T *data) override
	{
		ud->data = data;
	}

	virtual size_t SizeOfUserData() override
	{
		return sizeof T;
	}

public:
	typedef T ContentType;
	ContentType *Contents() { return reinterpret_cast<ContentType *>(ud->data); }

public:
	UserData *ud;
};

#endif // ILUABASECLASS_H