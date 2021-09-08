// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#define CS_PROPERTY_MULTI_REF_TYPE_DEFAULT -1

template<typename ValueType, uint8 SIZE = 1>
struct TCsProperty_Multi_Ref
{
public:
	ValueType DefaultValue;
	ValueType Value;
	ValueType Last_Value;

	ValueType* Values[SIZE];
	ValueType Last_Values[SIZE];
protected:
	bool IsDirty;

	bool IsDirtys[SIZE];
public:
	TMulticastDelegate<void, const ValueType&> OnChange_Event;
	TMulticastDelegate<void, const int32&, const ValueType&> OnChangeEX_Event;

public:

	TCsProperty_Multi_Ref()
	{
		IsDirty = false;

		for (bool& b : IsDirtys)
		{
			b = false;
		}
		OnChange_Event.Clear();
		OnChangeEX_Event.Clear();
	}
	virtual ~TCsProperty_Multi_Ref(){}

	FORCEINLINE virtual void UpdateIsDirty()
	{
		IsDirty = Value != Last_Value;
		Value	= Last_Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FORCEINLINE virtual void UpdateIsDirty(const int32& Index)
	{
		IsDirtys[Index]		= *(Values[Index]) != Last_Values[Index];
		Last_Values[Index]	= *(Values[Index]);

		if (IsDirtys[Index])
			OnChangeEX_Event.Broadcast((U)(int32)Index, *(Values[Index]));
	}

	FORCEINLINE TCsProperty_Multi_Ref& operator=(const ValueType& B)
	{
		Value = B;
		UpdateIsDirty;

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Values[I] = B.Values[I];
			UpdateIsDirty(I);
		}
		return *this;
	}

	FORCEINLINE bool operator==(const TCsProperty_Multi_Ref& B) const
	{
		for (uint8 I = 0; I < SIZE; ++I)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B;
	}

	FORCEINLINE bool operator!=(const TCsProperty_Multi_Ref& B) const
	{
		return !(*this == B);
	}

	void Set(const ValueType& inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	void Set(const int32& Index, ValueType* inValue)
	{
		if (Index > CS_PROPERTY_MULTI_REF_TYPE_DEFAULT && Index < SIZE)
		{
			Values[Index] = inValue;
			UpdateIsDirty(Index);
		}
		else
		{
			Set(*inValue);
		}
	}

	FORCEINLINE const ValueType& Get() { return Value; }

	FORCEINLINE const ValueType& Get(const int32& Index)
	{
		return Index <= CS_PROPERTY_MULTI_REF_TYPE_DEFAULT || Index >= SIZE ? Value : *(Values[Index]);
	}

	FORCEINLINE void Clear()
	{
		IsDirty	= false;

		for (uint8 I = 0; I < SIZE; ++I)
		{
			IsDirtys[I]	= false;
		}
	}

	FORCEINLINE void Clear(const int32& Index)
	{
		Last_Values[Index] = *(Values[Index]);
		IsDirtys[Index]	   = false;
	}

	void ResetValues()
	{
		Value = DefaultValue;
		Last_Value = Value;
		IsDirty = false;

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Values[I] = nullptr;
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

	FORCEINLINE bool HasChanged(const int32& Index)
	{ 
		const int32 I = (int32)Index;
		return I <= CS_PROPERTY_MULTI_REF_TYPE_DEFAULT || I >= SIZE ? IsDirty : IsDirtys[I];
	}

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