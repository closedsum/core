// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
//#include "CsTypes_Delegate.generated.h"
#pragma once

// Single
#pragma region

struct TCsDelegate_Static
{

};

template<typename ParamType>
struct TCsDelegate_Static_One_Param
{
private:
	typedef void(*FnPtr)(ParamType);

private:

	FnPtr Event;

public:

	TCsDelegate_Static_One_Param()
	{
		Event = nullptr;
	}
	~TCsDelegate_Static_One_Param(){}

	FORCEINLINE TCsDelegate_Static_One_Param& operator=(const TCsDelegate_Static_One_Param& B)
	{
		Event = B.Event;
		return *this;
	}

	FORCEINLINE void Bind(FnPtr e)
	{
		Event = e;
	}

	FORCEINLINE void Unbind()
	{
		Event = nullptr;
	}

	FORCEINLINE bool IsBound()
	{
		return Event != nullptr;
	}

	FORCEINLINE void Execute(ParamType p)
	{
		if (Event != nullptr)
			(*Event)(p);
	}
};

template<typename ParamType1, typename ParamType2>
struct TCsDelegate_Static_Two_Params
{
private:
	typedef void(*FnPtr)(ParamType1, ParamType2);

private:

	FnPtr Event;

public:

	TCsDelegate_Static_Two_Params()
	{
		Event = nullptr;
	}
	~TCsDelegate_Static_Two_Params() {}

	FORCEINLINE TCsDelegate_Static_Two_Params& operator=(const TCsDelegate_Static_Two_Params& B)
	{
		Event = B.Event;
		return *this;
	}

	FORCEINLINE void Bind(FnPtr e)
	{
		Event = e;
	}

	FORCEINLINE void Unbind()
	{
		Event = nullptr;
	}

	FORCEINLINE bool IsBound()
	{
		return Event != nullptr;
	}

	FORCEINLINE void Execute(ParamType1 p1, ParamType2 p2)
	{
		if (Event != nullptr)
			(*Event)(p1, p2);
	}
};

template<typename ParamType1, typename ParamType2, typename ParamType3>
struct TCsDelegate_Static_Three_Params
{
private:
	typedef void(*FnPtr)(ParamType1, ParamType2, ParamType3);

private:

	FnPtr Event;

public:

	TCsDelegate_Static_Three_Params()
	{
		Event = nullptr;
	}
	~TCsDelegate_Static_Three_Params() {}

	FORCEINLINE TCsDelegate_Static_Three_Params& operator=(const TCsDelegate_Static_Three_Params& B)
	{
		Event = B.Event;
		return *this;
	}

	FORCEINLINE void Bind(FnPtr e)
	{
		Event = e;
	}

	FORCEINLINE void Unbind()
	{
		Event = nullptr;
	}

	FORCEINLINE bool IsBound()
	{
		return Event != nullptr;
	}

	FORCEINLINE void Execute(ParamType1 p1, ParamType2 p2, ParamType3 p3)
	{
		if (Event != nullptr)
			(*Event)(p1, p2, p3);
	}
};

#pragma endregion Single

// Multicast
#pragma region

template<typename ParamType>
struct TCsMulticastDelegate_Static_RetAndBool_OneParam
{
private:
	typedef bool(*FnPtr)(ParamType);

private:

	TMap<FDelegateHandle, FnPtr> InvocationMap;

public:

	TCsMulticastDelegate_Static_RetAndBool_OneParam()
	{
		InvocationMap.Reset();
	}
	~TCsMulticastDelegate_Static_RetAndBool_OneParam() {}

	FORCEINLINE TCsMulticastDelegate_Static_RetAndBool_OneParam& operator=(const TCsMulticastDelegate_Static_RetAndBool_OneParam& B)
	{
		InvocationMap.Reset();

		TArray<FDelegateHandle> keys;
		B.InvocationMap.GetKeys(keys);

		for (const FDelegateHandle& key : keys)
		{
			InvocationMap.Add(key, B.InvocationMap[key]);
		}
		return *this;
	}

	FORCEINLINE FDelegateHandle Add(FnPtr e)
	{
		FDelegateHandle handle = FDelegateHandle(FDelegateHandle::EGenerateNewHandleType::GenerateNewHandle);
		InvocationMap.Add(handle, e);
		return handle;
	}

	FORCEINLINE bool Remove(const FDelegateHandle& handle)
	{
		return InvocationMap.Remove(handle);
	}

	FORCEINLINE void Clear()
	{
		InvocationMap.Reset();
	}

	FORCEINLINE bool IsBound()
	{
		return InvocationMap.Num() > 0;
	}

	FORCEINLINE bool Broadcast(ParamType p)
	{
		TArray<FDelegateHandle> keys;
		InvocationMap.GetKeys(keys);

		bool ret = true;

		for(const FDelegateHandle& key : keys)
		{
			ret &= (*InvocationMap[key])(p);
		}
		return (keys.Num() > 0) & ret;
	}
};

template<typename ParamType>
struct TCsMulticastDelegate_Static_RetOrBool_OneParam
{
private:
	typedef bool(*FnPtr)(ParamType);

private:

	TMap<FDelegateHandle, FnPtr> InvocationMap;

public:

	TCsMulticastDelegate_Static_RetOrBool_OneParam()
	{
		InvocationMap.Reset();
	}
	~TCsMulticastDelegate_Static_RetOrBool_OneParam() {}

	FORCEINLINE TCsMulticastDelegate_Static_RetOrBool_OneParam& operator=(const TCsMulticastDelegate_Static_RetOrBool_OneParam& B)
	{
		InvocationMap.Reset();

		TArray<FDelegateHandle> keys;
		B.InvocationMap.GetKeys(keys);

		for (const FDelegateHandle& key : keys)
		{
			InvocationMap.Add(key, B.InvocationMap[key]);
		}
		return *this;
	}

	FORCEINLINE FDelegateHandle Add(FnPtr e)
	{
		FDelegateHandle handle = FDelegateHandle(FDelegateHandle::EGenerateNewHandleType::GenerateNewHandle);
		InvocationMap.Add(handle, e);
		return handle;
	}

	FORCEINLINE bool Remove(const FDelegateHandle& handle)
	{
		return InvocationMap.Remove(handle);
	}

	FORCEINLINE void Clear()
	{
		InvocationMap.Reset();
	}

	FORCEINLINE bool IsBound()
	{
		return InvocationMap.Num() > 0;
	}

	FORCEINLINE bool Broadcast(ParamType p)
	{
		TArray<FDelegateHandle> keys;
		InvocationMap.GetKeys(keys);

		for (const FDelegateHandle& key : keys)
		{
			if ((*InvocationMap[key])(p))
				return true;
		}
		return false;
	}
};

#pragma endregion Multicast