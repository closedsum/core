// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#define CS_PROPERTY_MULTI_TYPE_DEFAULT -1

template<typename ValueType, uint8 SIZE = 1>
struct TCsProperty_Multi
{
public:
	ValueType DefaultValue;
	ValueType Value;
	ValueType Last_Value;

	ValueType Values[SIZE];
	ValueType Last_Values[SIZE];
protected:
	bool IsDirty;

	bool IsDirtys[SIZE];
public:
	TMulticastDelegate<void(const ValueType&)> OnChange_Event;
	TMulticastDelegate<void(const int32&, const ValueType&)> OnChangeEX_Event;

public:

	TCsProperty_Multi()
	{
		IsDirty = false;

		for (bool& b : IsDirtys)
		{
			b = false;
		}
		OnChange_Event.Clear();
		OnChangeEX_Event.Clear();
	}
	virtual ~TCsProperty_Multi(){}

	FORCEINLINE virtual void UpdateIsDirty()
	{
		IsDirty		= Value != Last_Value;
		Last_Value	= Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FORCEINLINE virtual void UpdateIsDirty(const int32& Index)
	{
		IsDirtys[Index]		= Values[Index] != Last_Values[Index];
		Last_Values[Index]	= Values[Index];

		if (IsDirtys[Index])
			OnChangeEX_Event.Broadcast(Index, Values[Index]);
	}

	FORCEINLINE TCsProperty_Multi& operator=(const TCsProperty_Multi& B)
	{
		Value = B.Value;
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Values[I] = B.Values[I];
			UpdateIsDirty(I);
		}
		return *this;
	}

	FORCEINLINE bool operator==(const TCsProperty_Multi& B) const
	{
		for (uint8 I = 0; I < SIZE; ++I)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B.Value;
	}

	FORCEINLINE bool operator!=(const TCsProperty_Multi& B) const
	{
		return !(*this == B);
	}

	void Set(const ValueType& inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	void Set(const int32& Index, const ValueType& inValue)
	{
		if (Index > CS_PROPERTY_MULTI_TYPE_DEFAULT && Index < SIZE)
		{
			Values[Index] = inValue;
			UpdateIsDirty(Index);
		}
		else
		{
			Set(inValue);
		}
	}

	FORCEINLINE const ValueType& Get() { return Value; }

	FORCEINLINE const ValueType& Get(const int32& Index)
	{
		return Index <= CS_PROPERTY_MULTI_TYPE_DEFAULT || Index >= SIZE ? Value : Values[Index];
	}

	FORCEINLINE void Clear()
	{
		IsDirty	= false;

		for (uint8 I = 0; I < SIZE; ++I)
		{
			IsDirtys[I] = false;
		}
	}

	FORCEINLINE void Clear(const int32& Index)
	{
		IsDirtys[Index]	= false;
	}

	void ResetValues()
	{
		Value = DefaultValue;
		Last_Value = Value;
		IsDirty = false;

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Values[I] = Value;
			Last_Values[I] = Value;
			IsDirtys[I] = false;
		}
	}

	void Reset()
	{
		ResetValues();

		OnChange_Event.Clear();
		OnChangeEX_Event.Clear();
	}

	FORCEINLINE bool HasChanged() { return IsDirty; }
	FORCEINLINE bool HasChanged(const int32& Index) { return Index <= CS_PROPERTY_MULTI_TYPE_DEFAULT || Index >= SIZE ? IsDirty : IsDirtys[Index]; }

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; ++I)
		{
			UpdateIsDirty(I);
		}
		Clear();
	}

	FORCEINLINE void Resolve(const int32& Index)
	{
		UpdateIsDirty(Index);
		Clear(Index);
	}
};