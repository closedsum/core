// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#define CS_PROPERTY_TARRAY_REF_TYPE_DEFAULT -1

template<typename ValueType>
struct TCsProperty_TArray_Ref
{
public:
	ValueType DefaultValue;
	ValueType Value;
	ValueType Last_Value;

	TArray<ValueType*> Values;
	TArray<ValueType> Last_Values;

protected:
	uint8 SIZE;
	bool IsDirty;

	TArray<bool> IsDirtys;
public:
	TBaseDelegate<ValueType, const int32&> GetDelegate;
	TBaseDelegate<const ValueType&, const int32&> Override_Get;
	TBaseDelegate<const ValueType&, const int32&> Override_Subscript;
	TMulticastDelegate<void, const ValueType&> OnChange_Event;
	TMulticastDelegate<void, const int32&, const ValueType&> OnChangeArray_Event;
public:

	TCsProperty_TArray_Ref()
	{
		SIZE = 0;
		IsDirty = false;
		IsDirtys.Reset();

		GetDelegate.Unbind();
		Override_Get.Unbind();
		Override_Subscript.Unbind();
		OnChange_Event.Clear();
		OnChangeArray_Event.Clear();
	}
	virtual ~TCsProperty_TArray_Ref() {}

	void SetDefaultValue(const ValueType& inDefaultValue)
	{
		DefaultValue = inDefaultValue;
	}

	FORCEINLINE virtual void UpdateIsDirty()
	{
		IsDirty	   = Value != Last_Value;
		Last_Value = Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FORCEINLINE virtual void UpdateIsDirty(const int32& Index)
	{
		IsDirtys[Index]		= *(Values[Index]) != Last_Values[Index];
		Last_Values[Index]	= *(Values[Index]);

		if (IsDirtys[Index])
			OnChangeArray_Event.Broadcast(Index, *(Values[Index]));
	}

	FORCEINLINE TCsProperty_TArray_Ref& operator=(const TCsProperty_TArray_Ref& B)
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

	FORCEINLINE bool operator==(const TCsProperty_TArray_Ref& B) const
	{
		for (uint8 I = 0; I < SIZE; ++I)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B;
	}

	FORCEINLINE bool operator!=(const TCsProperty_TArray_Ref& B) const
	{
		return !(*this == B);
	}

	void Init(const uint8& inSIZE)
	{
		SIZE = inSIZE;
		Values.SetNum(SIZE, true);

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Values[I] = nullptr;
		}
		Last_Values.SetNumZeroed(SIZE, true);
		IsDirtys.SetNumZeroed(SIZE, true);
	}

	FORCEINLINE const uint8& Num() { return SIZE; }

	FORCEINLINE void Set(ValueType& inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Set(const int32& Index, ValueType* inValue)
	{
		if (Index > CS_PROPERTY_TARRAY_REF_TYPE_DEFAULT && Index < SIZE)
		{
			Values[Index] = inValue;
			UpdateIsDirty(Index);
		}
		else
		{
			Set(*inValue);
		}
	}

	FORCEINLINE const ValueType& operator[](const int32& Index)
	{
		if (Override_Subscript.IsBound())
			return Override_Subscript.Execute(Index);
		return *(Values[Index]);
	}

	FORCEINLINE const ValueType& Get() { return Value; }
	FORCEINLINE const ValueType& Get(const int32& Index)
	{
		if (Override_Get.IsBound())
			return Override_Get.Execute(Index);
		return Index <= CS_PROPERTY_TARRAY_REF_TYPE_DEFAULT ? Value : *(Values[Index]);
	}

	FORCEINLINE ValueType GetEX(const int32& Index) { return GetDelegate.Execute(Index); }

	FORCEINLINE void Clear()
	{
		IsDirty = false;

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
			Values[I] = nullptr;
			Last_Values[I] = Value;
			IsDirtys[I] = false;
		}
	}

	void Reset()
	{
		ResetValues();

		GetDelegate.Unbind();
		OnChange_Event.Clear();
		OnChangeArray_Event.Clear();
	}

	FORCEINLINE const bool& HasChanged() { return IsDirty; }

	FORCEINLINE const bool& HasChanged(const int32& Index)
	{
		return Index <= CS_PROPERTY_TARRAY_REF_TYPE_DEFAULT || Index >= SIZE ? IsDirty : IsDirtys[Index];
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