#ifndef ILUACLASS_H
#define ILUACLASS_H

// Warning: all user data information MUST be stored outside of this class. If it's in this class it will break everything.
template <typename T>
class ILuaClass
{
public:


public: // virtual override

	virtual T *GetData() = 0;
	virtual void SetData(T *data) = 0;
	virtual bool IsValid()
	{
		return ud != nullptr;
	}

public:
	UserData *ud;
};


#endif // ILUACLASS_H