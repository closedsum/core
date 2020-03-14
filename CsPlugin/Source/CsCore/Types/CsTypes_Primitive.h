// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsTypes_Enum.h"

#include "CsTypes_Primitive.generated.h"
#pragma once

// Property Types
#pragma region

#define CS_PRIMITIVE_TYPE_DEFAULT -1
#define CS_PRIMITIVE_TYPE_GET_DELEGATE -2

// Multi
#pragma region

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
	TMulticastDelegate<void, const ValueType&> OnChange_Event;
	TMulticastDelegate<void, const int32&, const ValueType&> OnChangeEX_Event;

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
		if (Index > CS_PRIMITIVE_TYPE_DEFAULT && Index < SIZE)
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
		return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? Value : Values[Index];
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
	FORCEINLINE bool HasChanged(const int32& Index) { return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? IsDirty : IsDirtys[Index]; }

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

template<typename ValueType, uint8 SIZE>
struct TCsIntegralType_MultiValue : public TCsProperty_Multi<ValueType, SIZE>
{
private:
	typedef TCsProperty_Multi<ValueType, SIZE> Super;

public:

	TCsIntegralType_MultiValue() : Super(){}
	~TCsIntegralType_MultiValue(){}

	void Add(const ValueType& inValue)
	{ 
		Value += inValue;
		UpdateIsDirty();
	}

	void Add(const int32& Index, const ValueType& inValue)
	{
		if (Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE)
		{
			Add(inValue);
		}
		else
		{
			Values[Index] += inValue;
			UpdateIsDirty(Index);
		}
	}

	void Subtract(const ValueType& inValue)
	{ 
		Value -= inValue;
		UpdateIsDirty();
	}

	void Subtract(const int32& Index, const ValueType& inValue)
	{
		if (Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE)
		{
			Subtract(inValue);
		}
		else
		{
			Values[Index] -= inValue;
			UpdateIsDirty(Index);
		}
	}

	ValueType Max()
	{
		ValueType max = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			max = (ValueType)FMath::Max(max, Values[I]);
		}
		return max;
	}

	ValueType Min()
	{
		ValueType min = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			min = (ValueType)FMath::Min(min, Values[I]);
		}
		return min;
	}
};

	// bool
#pragma region

template<uint8 SIZE>
struct TCsProperty_Multi_bool : public TCsProperty_Multi<bool, SIZE>
{
private:
	typedef TCsProperty_Multi<bool, SIZE> Super;

public:

	TCsProperty_Multi_bool() : Super()
	{
		DefaultValue = false;
	}
	~TCsProperty_Multi_bool(){}

	bool Or()
	{
		bool or = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			or |= Values[I];
		}
		return or;
	}

	bool And()
	{
		bool and = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			and& = Values[I];
		}
		return and;
	}
};

#pragma endregion bool

	// FString
#pragma region

template<uint8 SIZE>
struct TCsProperty_Multi_FString : public TCsProperty_Multi<FString, SIZE>
{
private:
	typedef TCsProperty_Multi<FString, SIZE> Super;

public:

	TCsProperty_Multi_FString() : Super()
	{
		DefaultValue = NCsCached::Str::Empty;
	}
	~TCsProperty_Multi_FString(){}
};

#pragma endregion FString

#define CS_FSTRING_ENUM_TWO_PARAMS 2
#define CS_FSTRING_ENUM_THREE_PARAMS 3
#define CS_FSTRING_ENUM_DEFAULT_VALUE 0
#define CS_FSTRING_ENUM_LOWER_VALUE 1
#define CS_FSTRING_ENUM_ALT_1_VALUE 2

	// FString_Enum_TwoParams
#pragma region

struct CSCORE_API TCsProperty_Multi_FString_Enum_TwoParams : public TCsProperty_Multi_FString<CS_FSTRING_ENUM_TWO_PARAMS>
{
private:
	typedef TCsProperty_Multi_FString<CS_FSTRING_ENUM_TWO_PARAMS> Super;

public:

	TCsProperty_Multi_FString_Enum_TwoParams() : Super()
	{
		DefaultValue = NCsCached::Str::Empty;
	}
	~TCsProperty_Multi_FString_Enum_TwoParams(){}

	TCsProperty_Multi_FString_Enum_TwoParams(const FString& inValue1, const FString& inValue2)
	{
		Value = inValue1;

		Values[CS_FSTRING_ENUM_DEFAULT_VALUE] = inValue1;
		Values[CS_FSTRING_ENUM_LOWER_VALUE] = inValue2;
	}

	FORCEINLINE friend bool operator==(const FString& Lhs, const TCsProperty_Multi_FString_Enum_TwoParams& Rhs)
	{
		const FString Lower = Lhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_TWO_PARAMS; ++I)
		{
			if (Rhs.Values[I] == Lhs || Rhs.Values[I] == Lower)
				return true;
		}
		return Rhs.Value == Lhs || Rhs.Value == Lower;
	}

	FORCEINLINE friend bool operator==(const TCsProperty_Multi_FString_Enum_TwoParams& Lhs, const FString& Rhs)
	{
		const FString Lower = Rhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_TWO_PARAMS; ++I)
		{
			if (Lhs.Values[I] == Rhs || Lhs.Values[I] == Lower)
				return true;
		}
		return Lhs.Value == Rhs || Lhs.Value == Lower;
	}

	FORCEINLINE friend bool operator!=(const FString& Lhs, const TCsProperty_Multi_FString_Enum_TwoParams& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsProperty_Multi_FString_Enum_TwoParams& Lhs, const FString& Rhs)
	{
		return !(Lhs == Rhs);
	}
};

#pragma endregion FString_Enum_TwoParams

	// FString_Enum_ThreeParams
#pragma region

struct CSCORE_API TCsProperty_Multi_FString_Enum_ThreeParams : public TCsProperty_Multi_FString<CS_FSTRING_ENUM_THREE_PARAMS>
{
private:
	typedef TCsProperty_Multi_FString<CS_FSTRING_ENUM_THREE_PARAMS> Super;

public:

	TCsProperty_Multi_FString_Enum_ThreeParams()
	{
		DefaultValue = NCsCached::Str::Empty;
	}
	~TCsProperty_Multi_FString_Enum_ThreeParams(){}

	TCsProperty_Multi_FString_Enum_ThreeParams(const FString& inValue1, const FString& inValue2, const FString& inValue3)
	{
		Value = inValue1;

		Values[CS_FSTRING_ENUM_DEFAULT_VALUE] = inValue1;
		Values[CS_FSTRING_ENUM_LOWER_VALUE]   = inValue2;
		Values[CS_FSTRING_ENUM_ALT_1_VALUE]   = inValue3;
	}
	
	FORCEINLINE friend bool operator==(const FString& Lhs, const TCsProperty_Multi_FString_Enum_ThreeParams& Rhs)
	{
		const FString Lower = Lhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_THREE_PARAMS; ++I)
		{
			if (Rhs.Values[I] == Lhs || Rhs.Values[I] == Lower)
				return true;
		}
		return Rhs.Value == Lhs || Rhs.Value == Lower;
	}

	FORCEINLINE friend bool operator==(const TCsProperty_Multi_FString_Enum_ThreeParams& Lhs, const FString& Rhs)
	{
		const FString Lower = Rhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_THREE_PARAMS; ++I)
		{
			if (Lhs.Values[I] == Rhs || Lhs.Values[I] == Lower)
				return true;
		}
		return Lhs.Value == Rhs || Lhs.Value == Lower;
	}

	FORCEINLINE friend bool operator!=(const FString& Lhs, const TCsProperty_Multi_FString_Enum_ThreeParams& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsProperty_Multi_FString_Enum_ThreeParams& Lhs, const FString& Rhs)
	{
		return !(Lhs == Rhs);
	}
};

#pragma endregion FString_Enum_ThreeParams

#pragma endregion MultiValue

// MultiRef
#pragma region

template<typename ValueType, uint8 SIZE = 1>
struct TCsProperty_MultiRef
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

	TCsProperty_MultiRef()
	{
		IsDirty = false;

		for (bool& b : IsDirtys)
		{
			b = false;
		}
		OnChange_Event.Clear();
		OnChangeEX_Event.Clear();
	}
	virtual ~TCsProperty_MultiRef(){}

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

	FORCEINLINE TCsProperty_MultiRef& operator=(const ValueType& B)
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

	FORCEINLINE bool operator==(const TCsProperty_MultiRef& B) const
	{
		for (uint8 I = 0; I < SIZE; ++I)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B;
	}

	FORCEINLINE bool operator!=(const TCsProperty_MultiRef& B) const
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
		if (Index > CS_PRIMITIVE_TYPE_DEFAULT & Index < SIZE)
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
		return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? Value : *(Values[Index]);
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
		return I <= CS_PRIMITIVE_TYPE_DEFAULT || I >= SIZE ? IsDirty : IsDirtys[I];
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

template<typename ValueType, uint8 SIZE>
struct TCsIntegralType_MultiRef : public TCsProperty_MultiRef<ValueType, SIZE>
{
private:
	typedef TCsProperty_MultiRef<ValueType, SIZE> Super;

public:

	TCsIntegralType_MultiRef() : Super(){}
	~TCsIntegralType_MultiRef(){}

	ValueType Max()
	{
		ValueType max = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			max = (ValueType)FMath::Max(max, *(Values[I]));
		}
		return max;
	}

	ValueType Min()
	{
		ValueType min = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			min = (ValueType)FMath::Min(min, *(Values[I]));
		}
		return min;
	}
};

template<uint8 SIZE>
struct TCsProperty_MultiRef_bool : public TCsProperty_MultiRef<bool, SIZE>
{
private:
	typedef TCsProperty_MultiRef<bool, SIZE> Super;

public:

	TCsProperty_MultiRef_bool() : Super()
	{
		DefaultValue = bool;
	}
	~TCsProperty_MultiRef_bool(){}

	bool Or()
	{
		bool or = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			or |= Values[I];
		}
		return or ;
	}

	bool And()
	{
		bool and = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			and& = Values[I];
		}
		return and;
	}
};

#pragma endregion MultiRef

// TArray
#pragma region

template<typename ValueType>
struct TCsProperty_TArray
{
public:
	ValueType DefaultValue;
	ValueType Value;
	ValueType Last_Value;

	TArray<ValueType> Values;
	TArray<ValueType> Last_Values;

protected:
	uint8 SIZE;
	bool IsDirty;

	TArray<bool> IsDirtys;
public:
	TBaseDelegate<ValueType, const int32&> GetDelegate;
	TBaseDelegate<const ValueType&, const int32&> Override_Get;
	TBaseDelegate<const ValueType&, const int32&> Override_Subscript_Const;
	TBaseDelegate<ValueType&, const int32&> Override_Subscript;
	TMulticastDelegate<void, const ValueType&> OnChange_Event;
	TMulticastDelegate<void, const int32&, const ValueType&> OnChangeArray_Event;

public:

	TCsProperty_TArray() 
	{
		SIZE = 0;
		IsDirty = false;
		IsDirtys.Reset();

		GetDelegate.Unbind();
		Override_Get.Unbind();
		Override_Subscript.Unbind();
		Override_Subscript_Const.Unbind();
		OnChange_Event.Clear();
		OnChangeArray_Event.Clear();
	}
	virtual ~TCsProperty_TArray() {}

	void SetDefaultValue(const ValueType& inDefaultValue)
	{
		DefaultValue = inDefaultValue;
	}

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
			OnChangeArray_Event.Broadcast(Index, Values[Index]);
	}

	FORCEINLINE TCsProperty_TArray& operator=(const TCsProperty_TArray& B)
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

	FORCEINLINE bool operator==(const TCsProperty_TArray& B) const
	{
		for (uint8 I = 0; I < SIZE; ++I)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B;
	}

	FORCEINLINE bool operator!=(const TCsProperty_TArray& B) const
	{
		return !(*this == B);
	}

	void Init(const uint8& inSIZE)
	{
		SIZE = inSIZE;
		Values.SetNumZeroed(SIZE, true);
		Last_Values.SetNumZeroed(SIZE, true);
		IsDirtys.SetNumZeroed(SIZE, true);
	}

	FORCEINLINE void Set(const ValueType& inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Set(const int32& Index, const ValueType& inValue)
	{
		if (Index > CS_PRIMITIVE_TYPE_DEFAULT & Index < SIZE)
		{
			Values[Index] = inValue;
			UpdateIsDirty(Index);
		}
		else
		{
			Set(inValue);
		}
	}

	FORCEINLINE ValueType& operator[](const int32& Index)
	{
		if (Override_Subscript.IsBound())
			return Override_Subscript.Execute(Index);
		return Values[Index];
	}

	FORCEINLINE const ValueType& operator[](const int32& Index) const
	{
		if (Override_Subscript_Const.IsBound())
			return Override_Subscript_Const.Execute(Index);
		return Values[Index];
	}

	FORCEINLINE const ValueType& Get() { return Value; }
	FORCEINLINE const ValueType& Get(const int32& Index)
	{
		if (Override_Get.IsBound())
			return Override_Get.Execute(Index);
		return Index <= CS_PRIMITIVE_TYPE_DEFAULT ? Value : Values[Index]; 
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
		IsDirtys[Index] = false;
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

		GetDelegate.Unbind();
		Override_Get.Unbind();
		Override_Subscript.Unbind();
		Override_Subscript_Const.Unbind();
		OnChange_Event.Clear();
		OnChangeEX_Event.Clear();
	}

	FORCEINLINE const bool& HasChanged() { return IsDirty; }
	FORCEINLINE const bool& HasChanged(const int32& Index) { return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? IsDirty : IsDirtys[Index]; }

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

template<typename ValueType>
struct TCsIntegralType_TArray : public TCsProperty_TArray<ValueType>
{
private:
	typedef TCsProperty_TArray<ValueType> Super;

public:

	TCsIntegralType_TArray() : Super(){}
	~TCsIntegralType_TArray() {}

	void Add(const ValueType& inValue)
	{
		Value += inValue;
		UpdateIsDirty();
	}

	void Add(const int32& Index, const ValueType& inValue)
	{
		if (Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE)
		{
			Add(inValue);
		}
		else
		{
			Values[Index] += inValue;
			UpdateIsDirty(Index);
		}
	}

	void Subtract(const ValueType& inValue)
	{
		Value -= inValue;
		UpdateIsDirty();
	}

	void Subtract(const int32& Index, const ValueType& inValue)
	{
		if (Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE)
		{
			Subtract(inValue);
		}
		else
		{
			Values[Index] -= inValue;
			UpdateIsDirty(Index);
		}
	}

	ValueType Max()
	{
		ValueType max = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			max = (ValueType)FMath::Max(max, Values[I]);
		}
		return max;
	}

	ValueType Min()
	{
		ValueType min = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			min = (ValueType)FMath::Min(min, Values[I]);
		}
		return min;
	}
};

struct TCsIntegralType_TArray_uint8 : public TCsIntegralType_TArray<uint8>
{
private:
	typedef TCsIntegralType_TArray<uint8> Super;

public:

	TCsIntegralType_TArray_uint8() : Super()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TArray_uint8(){}
};

struct TCsIntegralType_TArray_float : public TCsIntegralType_TArray<float>
{
private:
	typedef TCsIntegralType_TArray<float> Super;

public:

	TCsIntegralType_TArray_float() : Super()
	{
		DefaultValue = 0.0f;
	}
	~TCsIntegralType_TArray_float() {}
};

struct TCsProperty_TArray_bool : public TCsProperty_TArray<bool>
{
private:
	typedef TCsProperty_TArray<bool> Super;

public:

	TCsProperty_TArray_bool() : Super()
	{
		DefaultValue = false;
	}
	~TCsProperty_TArray_bool() {}

	bool Or()
	{
		bool or = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			or |= Values[I];
		}
		return or ;
	}

	bool And()
	{
		bool and = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			and &= Values[I];
		}
		return and;
	}
};

#pragma endregion TArray

// TArrayRef
#pragma region

template<typename ValueType>
struct TCsProperty_TArrayRef
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

	TCsProperty_TArrayRef() 
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
	virtual ~TCsProperty_TArrayRef() {}

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

	FORCEINLINE TCsProperty_TArrayRef& operator=(const TCsProperty_TArrayRef& B)
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

	FORCEINLINE bool operator==(const TCsProperty_TArrayRef& B) const
	{
		for (uint8 I = 0; I < SIZE; ++I)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B;
	}

	FORCEINLINE bool operator!=(const TCsProperty_TArrayRef& B) const
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
		if (Index > CS_PRIMITIVE_TYPE_DEFAULT && Index < SIZE)
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
		return Index <= CS_PRIMITIVE_TYPE_DEFAULT ? Value : *(Values[Index]); 
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
		return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? IsDirty : IsDirtys[Index];
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

template<typename ValueType>
struct TCsIntegralType_TArrayRef : public TCsProperty_TArrayRef<ValueType>
{
private:
	typedef TCsProperty_TArrayRef<ValueType> Super;

public:

	TCsIntegralType_TArrayRef() : Super(){}
	~TCsIntegralType_TArrayRef() {}

	ValueType Max()
	{
		ValueType max = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			max = (ValueType)FMath::Max(max, *(Values[I]));
		}
		return max;
	}

	ValueType Min()
	{
		ValueType min = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			min = (ValueType)FMath::Min(min, *(Values[I]));
		}
		return min;
	}
};

struct TCsIntegralType_TArrayRef_uint8 : public TCsIntegralType_TArrayRef<uint8>
{
private:
	typedef TCsIntegralType_TArrayRef<uint8> Super;

public:

	TCsIntegralType_TArrayRef_uint8() : Super()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TArrayRef_uint8() {}
};

struct TCsIntegralType_TArrayRef_int32 : public TCsIntegralType_TArrayRef<int32>
{
private:
	typedef TCsIntegralType_TArrayRef<int32> Super;

public:

	TCsIntegralType_TArrayRef_int32() : Super()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TArrayRef_int32() {}
};

struct TCsIntegralType_TArrayRef_float : public TCsIntegralType_TArrayRef<float>
{
private:
	typedef TCsIntegralType_TArrayRef<float> Super;

public:

	TCsIntegralType_TArrayRef_float() : Super()
	{
		DefaultValue = 0.0f;
	}
	~TCsIntegralType_TArrayRef_float() {}
};

struct TCsProperty_TArrayRef_bool : public TCsProperty_TArrayRef<bool>
{
private:
	typedef TCsProperty_TArrayRef<bool> Super;

public:

	TCsProperty_TArrayRef_bool() : Super()
	{
		DefaultValue = false;
	}
	~TCsProperty_TArrayRef_bool() {}

	bool Or()
	{
		bool or = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			or |= *(Values[I]);
		}
		return or ;
	}

	bool And()
	{
		bool and = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			and &= *(Values[I]);
		}
		return and;
	}
};

#pragma endregion TArrayRef

// TMap
#pragma region

template<typename KeyType, typename ValueType>
struct TCsProperty_TMap
{
public:
	ValueType DefaultValue;
	ValueType Value;
	ValueType Last_Value;

	TMap<KeyType, ValueType> Values;
	TMap<KeyType, ValueType> Last_Values;

protected:
	bool IsDirty;

	TMap<KeyType, bool> IsDirtys;
public:
	TBaseDelegate<ValueType, const KeyType&> GetDelegate;
	TMulticastDelegate<void, const ValueType&> OnChange_Event;
	TMulticastDelegate<void, const KeyType&, const ValueType&> OnChangeMap_Event;

public:

	TCsProperty_TMap() 
	{
		Values.Reset();
		Last_Values.Reset();

		IsDirty = false;
		IsDirtys.Reset();

		GetDelegate.Unbind();
		OnChange_Event.Clear();
		OnChangeMap_Event.Clear();
	}
	virtual ~TCsProperty_TMap() {}

	void SetDefaultValue(const ValueType& InDefaultValue)
	{
		DefaultValue = InDefaultValue;
	}

	void Init(const KeyType& Key)
	{
		Values.Add(Key, DefaultValue);
		Last_Values.Add(Key, DefaultValue);
		IsDirtys.Add(Key, false);
	}

	FORCEINLINE virtual void UpdateIsDirty()
	{
		IsDirty		= Value != Last_Value;
		Last_Value	= Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FORCEINLINE virtual void UpdateIsDirty(const KeyType& Key)
	{
		IsDirtys[Key]	 = Values[Key] != Last_Values[Key];
		Last_Values[Key] = Values[Key];

		if (IsDirtys[Key])
			OnChangeMap_Event.Broadcast(Key, Values[Key]);
	}

	FORCEINLINE TCsProperty_TMap& operator=(const TCsProperty_TMap& B)
	{
		Value = B.Value;
		UpdateIsDirty();

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			Values[Key] = B.Values[Key];
			UpdateIsDirty(Key);
		}
		return *this;
	}

	FORCEINLINE bool operator==(const TCsProperty_TMap& B) const
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			if (Values[Key] != B.Values[Key])
				return false;
		}
		return Value == B;
	}

	FORCEINLINE bool operator!=(const TCsProperty_TMap& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(const ValueType& InValue)
	{
		Value = InValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Set(const KeyType& Key, const ValueType& InValue)
	{
		Values[Key] = InValue;
		UpdateIsDirty(Key);
	}

	FORCEINLINE ValueType& operator[](const KeyType& Key)
	{
		return Values[Key];
	}

	FORCEINLINE const ValueType& operator[](const KeyType& Key) const
	{
		return Values[Key];
	}

	FORCEINLINE const ValueType& Get() { return Value; }
	FORCEINLINE const ValueType& Get(const KeyType& Key) { return Values[Key]; }

	FORCEINLINE ValueType GetEX(const KeyType& Key) { return GetDelegate.Execute(Key); }

	FORCEINLINE void Clear()
	{
		IsDirty	= false;

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			IsDirtys[Key] = false;
		}
	}

	FORCEINLINE void Clear(const KeyType& Key)
	{
		IsDirtys[Key] = false;
	}

	void ResetValues()
	{
		Value	   = DefaultValue;
		Last_Value = Value;
		IsDirty	   = false;

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			Values[Key]	     = Value;
			Last_Values[Key] = Value;
			IsDirtys[Key]    = false;
		}
	}

	void Reset()
	{
		ResetValues();

		GetDelegate.Unbind();
		OnChange_Event.Clear();
		OnChangeMap_Event.Clear();
	}

	FORCEINLINE bool HasChanged() { return IsDirty; }
	FORCEINLINE bool HasChanged(const KeyType& Key) { return IsDirtys[Key]; }

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			UpdateIsDirty(Key);
		}
		Clear();
	}

	FORCEINLINE void Resolve(const KeyType& Key)
	{
		UpdateIsDirty(Key);
		Clear(Key);
	}
};

template<typename KeyType, typename ValueType>
struct TCsIntegralType_TMap : public TCsProperty_TMap<KeyType, ValueType>
{
private:
	typedef TCsProperty_TMap<KeyType, ValueType> Super;

public:

	TCsIntegralType_TMap() : Super(){}
	~TCsIntegralType_TMap() {}

	FORCEINLINE void Add(const ValueType& InValue)
	{
		Value += InValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Add(const KeyType& Key, const ValueType& InValue)
	{
		Values[Key] += InValue;
		UpdateIsDirty(Key);
	}

	FORCEINLINE void Subtract(const ValueType& InValue)
	{
		Value -= InValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Subtract(const KeyType& Key, const ValueType& InValue)
	{
		Values[Index] -= inValue;
		UpdateIsDirty(Index);
	}

	FORCEINLINE ValueType Max()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		ValueType max = Values[Keys[0]];

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			max = (KeyType)FMath::Max(max, Values[Keys[I]]);
		}
		return max;
	}

	FORCEINLINE ValueType Min()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		ValueType min = Values[Keys[0]];

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			min = (ValueType)FMath::Min(min, Values[Keys[I]]);
		}
		return min;
	}
};

template<typename KeyType>
struct TCsIntegralType_TMap_uint8 : public TCsIntegralType_TMap<KeyType, uint8>
{
private:
	typedef TCsIntegralType_TMap<KeyType, uint8> Super;

public:

	TCsIntegralType_TMap_uint8() : Super()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TMap_uint8() {}
};

template<typename KeyType>
struct TCsIntegralType_TMap_float : public TCsIntegralType_TMap<KeyType, float>
{
private:
	typedef TCsIntegralType_TMap<KeyType, float> Super;

public:

	TCsIntegralType_TMap_float() : Super()
	{
		DefaultValue = 0.0f;
	}
	~TCsIntegralType_TMap_float() {}
};

template<typename KeyType>
struct TCsProperty_TMap_bool : public TCsProperty_TMap<KeyType, bool>
{
private:
	typedef TCsProperty_TMap<KeyType, bool> Super;

public:

	TCsProperty_TMap_bool() : Super()
	{
		DefaultValue = false;
	}
	~TCsProperty_TMap_bool() {}

	FORCEINLINE bool Or()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		bool or = Values[Keys[0]];

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			or |= Values[Keys[I]];
		}
		return or ;
	}

	FORCEINLINE bool And()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		bool and = Values[Keys[0]];

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			and& = Values[Keys[I]];
		}
		return and;
	}
};

#pragma endregion TMap

// TMapRef
#pragma region

template<typename KeyType, typename ValueType>
struct TCsProperty_TMapRef
{
public:
	ValueType DefaultValue;
	ValueType Value;
	ValueType Last_Value;

	TMap<KeyType, ValueType*> Values;
	TMap<KeyType, ValueType> Last_Values;

protected:
	bool IsDirty;

	TMap<KeyType, bool> IsDirtys;
public:
	TBaseDelegate<ValueType, const KeyType&> GetDelegate;
	TBaseDelegate<const ValueType&, const KeyType&> Override_Get;
	TBaseDelegate<const ValueType&, const KeyType&> Override_Subscript;
	TMulticastDelegate<void, const ValueType&> OnChange_Event;
	TMulticastDelegate<void, const KeyType&, const ValueType&> OnChangeMap_Event;
public:

	TCsProperty_TMapRef() 
	{
		Values.Reset();
		Last_Values.Reset();

		IsDirty = false;
		IsDirtys.Reset();

		GetDelegate.Unbind();
		Override_Get.Unbind();
		Override_Subscript.Unbind();
		OnChange_Event.Clear();
		OnChangeMap_Event.Clear();
	}
	virtual ~TCsProperty_TMapRef() {}

	void SetDefaultValue(const ValueType& InDefaultValue)
	{
		DefaultValue = InDefaultValue;
	}

	void Init(const KeyType& Key)
	{
		Values.Add(Key, nullptr);
		Last_Values.Add(Key, DefaultValue);
		IsDirtys.Add(Key, false);
	}

	FORCEINLINE virtual void UpdateIsDirty()
	{
		IsDirty		= Value != Last_Value;
		Last_Value	= Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FORCEINLINE virtual void UpdateIsDirty(const KeyType& Key)
	{
		IsDirtys[Key]	 = *(Values[Key]) != Last_Values[Key];
		Last_Values[Key] = *(Values[Key]);

		if (IsDirtys[Key])
			OnChangeMap_Event.Broadcast(Key, *(Values[Key]));
	}

	FORCEINLINE TCsProperty_TMapRef& operator=(const TCsProperty_TMapRef& B)
	{
		Value = B.Value;
		UpdateIsDirty();

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			*(Values[Key]) = *(B.Values[Key]);
			UpdateIsDirty(Key);
		}
		return *this;
	}

	FORCEINLINE bool operator==(const TCsProperty_TMapRef& B) const
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			if (*(Values[Key]) != *(B.Values[Key]))
				return false;
		}
		return Value == B;
	}

	FORCEINLINE bool operator!=(const TCsProperty_TMapRef& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(const ValueType& InValue)
	{
		Value = InValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Set(const KeyType& Key, ValueType* InValue)
	{
		Values[Key] = InValue;
		UpdateIsDirty(Key);
	}

	FORCEINLINE const ValueType& operator[](const KeyType& Key)
	{
		return *(Values[Key]);
	}

	FORCEINLINE const ValueType& Get() { return Value; }
	FORCEINLINE const ValueType& Get(const KeyType& Key) { return *(Values[Key]); }

	FORCEINLINE ValueType GetEX(const KeyType& Key) { return GetDelegate.Execute(Key); }

	FORCEINLINE void Clear()
	{
		IsDirty = false;

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			IsDirtys[Key] = false;
		}
	}

	FORCEINLINE void Clear(const KeyType& Key)
	{
		IsDirtys[Key] = false;
	}

	void ResetValues()
	{
		Value = DefaultValue;
		Last_Value = Value;
		IsDirty = false;

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			Values[Key] = nullptr;
			Last_Values[Key] = Value;
			IsDirtys[Key] = false;
		}
	}

	void Reset()
	{
		ResetValues();

		GetDelegate.Unbind();
		OnChange_Event.Clear();
		OnChangeMap_Event.Clear();
	}

	FORCEINLINE bool HasChanged() { return IsDirty; }
	FORCEINLINE bool HasChanged(const KeyType& Key) { return IsDirtys[Key]; }

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			UpdateIsDirty(Key);
		}
		Clear();
	}

	FORCEINLINE void Resolve(const KeyType& Key)
	{
		UpdateIsDirty(Key);
		Clear(Key);
	}
};

template<typename KeyType, typename ValueType>
struct TCsIntegralType_TMapRef : public TCsProperty_TMapRef<KeyType, ValueType>
{
private:
	typedef TCsProperty_TMapRef<KeyType, ValueType> Super;

public:

	TCsIntegralType_TMapRef() : Super(){}
	~TCsIntegralType_TMapRef() {}

	FORCEINLINE ValueType Max()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		ValueType max = *(Values[Keys[0]]);

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			max = (ValueType)FMath::Max(max, *(Values[Keys[I]]));
		}
		return max;
	}

	FORCEINLINE ValueType Min()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		ValueType min = *(Values[Keys[0]]);

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			min = (ValueType)FMath::Min(min, *(Values[Keys[I]]));
		}
		return min;
	}
};

template<typename KeyType>
struct TCsIntegralType_TMapRef_uint8 : public TCsIntegralType_TMapRef<KeyType, uint8>
{
private:
	typedef TCsIntegralType_TMapRef<KeyType, uint8> Super;

public:

	TCsIntegralType_TMapRef_uint8() : Super()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TMapRef_uint8() {}
};

template<typename KeyType>
struct TCsIntegralType_TMapRef_int32 : public TCsIntegralType_TMapRef<KeyType, int32>
{
private:
	typedef TCsIntegralType_TMapRef<KeyType, int32> Super;

public:

	TCsIntegralType_TMapRef_int32() : Super()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TMapRef_int32() {}
};

template<typename KeyType>
struct TCsIntegralType_TMapRef_float : public TCsIntegralType_TMapRef<KeyType, float>
{
private:
	typedef TCsIntegralType_TMapRef<KeyType, float> Super;

public:

	TCsIntegralType_TMapRef_float() : Super()
	{
		DefaultValue = 0.0f;
	}
	~TCsIntegralType_TMapRef_float() {}
};

template<typename KeyType>
struct TCsProperty_TMapRef_bool : public TCsProperty_TMapRef<KeyType, bool>
{
private:
	typedef TCsProperty_TMapRef<KeyType, bool> Super;

public:

	TCsProperty_TMapRef_bool() : Super()
	{
		DefaultValue = false;
	}
	~TCsProperty_TMapRef_bool() {}

	FORCEINLINE bool Or()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		bool or = *(Values[Keys[0]]);

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			or |= *(Values[Keys[I]]);
		}
		return or ;
	}

	FORCEINLINE bool And()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		bool and = *(Values[Keys[0]]);

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			and& = *(Values[Keys[I]]);
		}
		return and;
	}
};

#pragma endregion TMapRef

#pragma endregion Property Types

// MemberType
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsMemberType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsMemberType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsMemberType)

struct CSCORE_API EMCsMemberType : public TCsEnumStructMap<FECsMemberType, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsMemberType, FECsMemberType, uint8)
};

namespace NCsMemberType
{
	typedef FECsMemberType Type;

	extern CSCORE_API const Type Bool;
	extern CSCORE_API const Type Uint8;
	extern CSCORE_API const Type Int32;
	extern CSCORE_API const Type Enum;
	extern CSCORE_API const Type EnumClass;
	extern CSCORE_API const Type EnumNamespaced;
	extern CSCORE_API const Type Float;
	extern CSCORE_API const Type String;
	extern CSCORE_API const Type Name;
	extern CSCORE_API const Type Vector;
	extern CSCORE_API const Type Rotator;
	extern CSCORE_API const Type Color;
	extern CSCORE_API const Type Object;
	extern CSCORE_API const Type Actor;
	extern CSCORE_API const Type Pawn;
	extern CSCORE_API const Type ActorComponent;
	extern CSCORE_API const Type SceneComponent;
	extern CSCORE_API const Type PrimitiveComponent;
	extern CSCORE_API const Type StaticMeshComponent;
	extern CSCORE_API const Type SkeletalMeshComponent;
}

#pragma endregion MemberType

#define CS_DECLARE_AND_DEFINE_CONST_INTEGRAL_VALUE(Type, Integral, Value) const Type Integral = 1; \
																		  Type* ptr = (Type*)(&Integral); \
																		  *ptr = Value;

// Blueprint Property Types
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsBpProperty_bool
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property bool")
	bool DefaultValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property bool")
	bool Value;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property bool")
	bool Last_Value;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property bool")
	bool IsDirty;
public:
	TMulticastDelegate<void, const bool&> OnChange_Event;

public:
	FCsBpProperty_bool() :
		DefaultValue(false),
		Value(false),
		Last_Value(false),
		IsDirty(false)
	{
	}
	~FCsBpProperty_bool() {}

	void SetDefaultValue(const bool& inDefaultValue)
	{
		DefaultValue = inDefaultValue;
	}

	FORCEINLINE void UpdateIsDirty()
	{
		IsDirty = Value != Last_Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FORCEINLINE FCsBpProperty_bool& operator=(const bool& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE bool operator==(const bool& B) const
	{
		return Value == B;
	}

	FORCEINLINE bool operator!=(const bool& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(const bool& inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FORCEINLINE const bool& Get() { return Value; }

	FORCEINLINE void Clear()
	{
		Last_Value = Value;
		IsDirty = false;
	}

	void ResetValue()
	{
		Value = DefaultValue;
		Last_Value = Value;
		IsDirty = false;
	}

	void Reset()
	{
		ResetValue();

		OnChange_Event.Clear();
	}

	FORCEINLINE bool HasChanged() { return IsDirty; }
	FORCEINLINE void MarkDirty() { IsDirty = true; }

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();
		Clear();
	}
};

#pragma endregion Blueprint Property Types

// Vector Types
#pragma region

// TODO: Look at FIntPoint, FVector ... etc for proper setup

USTRUCT(BlueprintType)
struct CSCORE_API FCsUint8Point
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UInt8Point")
	uint8 X; // 8 bits
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UInt8Point")
	uint8 Y; // 8 bits

	FCsUint8Point()
	{
		Reset();
	}
	~FCsUint8Point(){}

	FORCEINLINE FCsUint8Point& operator=(const FCsUint8Point& B)
	{
		X = B.X;
		Y = B.Y;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsUint8Point& B) const
	{
		return X == B.X && Y == B.Y;
	}

	FORCEINLINE bool operator!=(const FCsUint8Point& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		X = 0;
		Y = 0;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("X=%d Y=%d"), X, Y);
	}

	bool InitFromString(const FString& InSourceString)
	{
		X = Y = 0;

		// The initialization is only successful if the X and Y values can all be parsed from the string
		const bool bSuccessful = FParse::Value(*InSourceString, TEXT("X="), X) & FParse::Value(*InSourceString, TEXT("Y="), Y);

		return bSuccessful;
	}

	FORCEINLINE uint32 GetBits() const
	{
		return 8 // X
			 + 8;// Y
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsUint8MatrixDimension
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Uint8MatrixDimension")
	uint8 RowSpan; // 8 bits
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Uint8MatrixDimension")
	uint8 ColumnSpan; // 8 bits

	FCsUint8MatrixDimension()
	{
		Reset();
	}

	FCsUint8MatrixDimension(const uint8& InRowSpan, const uint8& InColumnSpan)
	{
		RowSpan	   = InRowSpan;
		ColumnSpan = InColumnSpan;
	}
	~FCsUint8MatrixDimension() {}

	FORCEINLINE FCsUint8MatrixDimension& operator=(const FCsUint8MatrixDimension& B)
	{
		RowSpan	   = B.RowSpan;
		ColumnSpan = B.ColumnSpan;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsUint8MatrixDimension& B) const
	{
		return RowSpan == B.RowSpan && ColumnSpan == B.ColumnSpan;
	}

	FORCEINLINE bool operator!=(const FCsUint8MatrixDimension& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		RowSpan	   = 0;
		ColumnSpan = 0;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("RowSpan=%d ColumnSpan=%d"), RowSpan, ColumnSpan);
	}

	bool InitFromString(const FString& InSourceString)
	{
		RowSpan = ColumnSpan = 0;

		// The initialization is only successful if the RowSpan and Y values can all be parsed from the string
		const bool bSuccessful = FParse::Value(*InSourceString, TEXT("RowSpan="), RowSpan) & FParse::Value(*InSourceString, TEXT("ColumnSpan="), ColumnSpan);

		return bSuccessful;
	}

	FORCEINLINE void Set(const uint8& InRowSpan, const uint8& InColumnSpan)
	{
		RowSpan    = InRowSpan;
		ColumnSpan = InColumnSpan;
	}

	FORCEINLINE uint8 GetRow(const int32& Index)
	{
		return (Index / RowSpan) % RowSpan;
	}

	FORCEINLINE uint8 GetColumn(const int32& Index)
	{
		return Index % RowSpan;
	}

	FORCEINLINE uint16 GetSize()
	{
		return RowSpan * ColumnSpan;
	}

	FORCEINLINE uint32 GetBits() const
	{
		return 8 // RowSpan
			 + 8;// ColumnSpan
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsUint8MatrixCoordinate
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Uint8MatrixCoordinate")
	uint8 Row; // 8 bits
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Uint8MatrixCoordinate")
	uint8 Column; // 8 bits

	FCsUint8MatrixCoordinate()
	{
		Reset();
	}
	~FCsUint8MatrixCoordinate() {}

	FORCEINLINE FCsUint8MatrixCoordinate& operator=(const FCsUint8MatrixCoordinate& B)
	{
		Row    = B.Row;
		Column = B.Column;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsUint8MatrixCoordinate& B) const
	{
		return Row == B.Row && Column == B.Column;
	}

	FORCEINLINE bool operator!=(const FCsUint8MatrixCoordinate& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		Row	   = 0;
		Column = 0;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("Row=%d Column=%d"), Row, Column);
	}

	bool InitFromString(const FString& InSourceString)
	{
		Row = Column = 0;

		// The initialization is only successful if the RowSpan and Y values can all be parsed from the string
		const bool bSuccessful = FParse::Value(*InSourceString, TEXT("Row="), Row) & FParse::Value(*InSourceString, TEXT("Column="), Column);

		return bSuccessful;
	}

	FORCEINLINE void Set(const uint8& InRow, const uint8& InColumn)
	{
		Row    = InRow;
		Column = InColumn;
	}

	FORCEINLINE uint32 GetBits() const
	{
		return 8 // Row
			 + 8;// Column
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsVectorFlag
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector")
	bool X; // 1 bits
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector")
	bool Y; // 1 bits
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector")
	bool Z; // 1 bits

	FCsVectorFlag()
	{
		Reset();
	}
	~FCsVectorFlag() {}

	FORCEINLINE FCsVectorFlag& operator=(const FCsVectorFlag& B)
	{
		X = B.X;
		Y = B.Y;
		Z = B.Z;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsVectorFlag& B) const
	{
		return X == B.X && Y == B.Y && Z == B.Z;
	}

	FORCEINLINE bool operator!=(const FCsVectorFlag& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		X = false;
		Y = false;
		Z = false;
	}
	
	FString ToString() const
	{
		return FString::Printf(TEXT("X=%s Y=%s Z=%s"), (*ToString_Internal(X)), (*ToString_Internal(Y)), (*ToString_Internal(Z)));
	}
	
private:

	const FString& ToString_Internal(const bool& Value) const 
	{
		return Value ? NCsCached::Str::True : NCsCached::Str::False;
	}

public:

	bool InitFromString(const FString& InSourceString)
	{
		X = Y = Z = false;

		// The initialization is only successful if the X, Y and Z values can all be parsed from the string
		const bool bSuccessful = InitFromString_Internal(InSourceString, NCsCached::Str::XEquals, X) & 
								 InitFromString_Internal(InSourceString, NCsCached::Str::YEquals, Y) &
								 InitFromString_Internal(InSourceString, NCsCached::Str::ZEquals, Z);

		return bSuccessful;
	}

private:

	bool InitFromString_Internal(const FString& InSourceString, const FString& SearchString, bool& Value)
	{
		FString Bool;
		FParse::Value(*InSourceString, *SearchString, Bool);

		Bool = Bool.ToLower();

		if (Bool == NCsCached::Str::_true || Bool == NCsCached::Str::One)
		{
			Value = true;
			return true;
		}
		if (Bool == NCsCached::Str::_false || Bool == NCsCached::Str::Zero)
		{
			Value = false;
			return true;
		}
		return false;
	}

public:

	FORCEINLINE void Set(const bool& InX, const bool& InY, const bool& InZ)
	{
		X = InX;
		Y = InY;
		Z = InZ;
	}

	FORCEINLINE void ApplyLock(FVector& V)
	{
		V.X = X ? 0.0f : V.X;
		V.Y = Y ? 0.0f : V.Y;
		V.Z = Z ? 0.0f : V.Z;
	}

	FORCEINLINE uint32 GetBits() const
	{
		return 1 // X
			 + 1 // Y
			 + 1;// Z
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsRotatorFlag
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator")
	bool Roll; // 1 bits
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator")
	bool Pitch; // 1 bits
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator")
	bool Yaw; // 1 bits

	FCsRotatorFlag()
	{
		Reset();
	}
	~FCsRotatorFlag() {}

	FCsRotatorFlag& operator=(const FCsRotatorFlag& B)
	{
		Roll  = B.Roll;
		Pitch = B.Pitch;
		Yaw   = B.Yaw;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsRotatorFlag& B) const
	{
		return Roll == B.Roll && Pitch == B.Pitch && Yaw == B.Yaw;
	}

	FORCEINLINE bool operator!=(const FCsRotatorFlag& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		Roll = false;
		Pitch = false;
		Yaw = false;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("R=%s P=%s Y=%s"), (*ToString_Internal(Roll)), (*ToString_Internal(Pitch)), (*ToString_Internal(Yaw)));
	}

private:

	const FString& ToString_Internal(const bool& Value) const
	{
		return Value ? NCsCached::Str::True : NCsCached::Str::False;
	}

public:

	bool InitFromString(const FString& InSourceString)
	{
		Roll = Pitch = Yaw = false;

		// The initialization is only successful if the Roll, Pitch and Yaw values can all be parsed from the string
		const bool bSuccessful = InitFromString_Internal(InSourceString, NCsCached::Str::RollEquals, Roll) &
								 InitFromString_Internal(InSourceString, NCsCached::Str::PitchEquals, Pitch) &
								 InitFromString_Internal(InSourceString, NCsCached::Str::YawEquals, Yaw);

		return bSuccessful;
	}

private:

	bool InitFromString_Internal(const FString& InSourceString, const FString& SearchString, bool& Value)
	{
		FString Bool;
		FParse::Value(*InSourceString, *SearchString, Bool);

		Bool = Bool.ToLower();

		if (Bool == NCsCached::Str::_true || Bool == NCsCached::Str::One)
		{
			Value = true;
			return true;
		}
		if (Bool == NCsCached::Str::_false || Bool == NCsCached::Str::Zero)
		{
			Value = false;
			return true;
		}
		return false;
	}

public:

	FORCEINLINE void Set(const bool& InRoll, const bool& InPitch, const bool& InYaw)
	{
		Roll = InRoll;
		Pitch = InPitch;
		Yaw = InYaw;
	}

	FORCEINLINE void ApplyLock(FRotator& R)
	{
		R.Roll = Roll ? 0.0f : R.Roll;
		R.Pitch = Pitch ? 0.0f : R.Pitch;
		R.Yaw = Yaw ? 0.0f : R.Yaw;
	}

	FORCEINLINE uint32 GetBits() const
	{
		return 1 // Roll
			 + 1 // Pitch
			 + 1;// Yaw
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsOptionalVectorInterval
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector")
	FVector Vector; // 3 x 64 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector", meta = (InlineEditConditionToggle))
	bool bIntervalX; // 1 bit
	UPROPERTY(EditAnywhere, Category = "Vector", meta = (editcondition = "bIntervalX"))
	FFloatInterval IntervalX; // 2 x 16 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector", meta = (InlineEditConditionToggle))
	bool bIntervalY; // 1 bit
	UPROPERTY(EditAnywhere, Category = "Vector", meta = (editcondition = "bIntervalX"))
	FFloatInterval IntervalY; // 2 x 16 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector", meta = (InlineEditConditionToggle))
	bool bIntervalZ;
	UPROPERTY(EditAnywhere, Category = "Vector", meta = (editcondition = "bIntervalX"))
	FFloatInterval IntervalZ;

	FCsOptionalVectorInterval()
	{
		Reset();
	}
	~FCsOptionalVectorInterval() {}

	FORCEINLINE FCsOptionalVectorInterval& operator=(const FCsOptionalVectorInterval& B)
	{
		Vector = B.Vector;
		// X
		bIntervalX = B.bIntervalX;
		IntervalX.Min = B.IntervalX.Min;
		IntervalX.Max = B.IntervalX.Max;
		// Y
		bIntervalY = B.bIntervalY;
		IntervalY.Min = B.IntervalY.Min;
		IntervalY.Max = B.IntervalY.Max;
		// Z
		bIntervalZ = B.bIntervalZ;
		IntervalZ.Min = B.IntervalZ.Min;
		IntervalZ.Max = B.IntervalZ.Max;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsOptionalVectorInterval& B) const
	{
		return	Vector == B.Vector && 
				bIntervalX == B.bIntervalX && 
				IntervalX.Min == B.IntervalX.Min &&
				IntervalX.Max == B.IntervalX.Max &&
				bIntervalY == B.bIntervalY &&
				IntervalY.Min == B.IntervalY.Min &&
				IntervalY.Max == B.IntervalY.Max &&
				bIntervalZ == B.bIntervalZ &&
				IntervalZ.Min == B.IntervalZ.Min &&
				IntervalZ.Max == B.IntervalZ.Max;
	}

	FORCEINLINE bool operator!=(const FCsOptionalVectorInterval& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		Vector = FVector::ZeroVector;
		// X
		bIntervalX = false;
		IntervalX.Min = 0.0f;
		IntervalX.Max = 0.0f;
		// Y
		bIntervalY = false;
		IntervalY.Min = 0.0f;
		IntervalY.Max = 0.0f;
		// Z
		bIntervalZ = false;
		IntervalZ.Min = 0.0f;
		IntervalZ.Max = 0.0f;
	}

	FORCEINLINE uint32 GetBits() const
	{
		return  (3 * 64) // Vector
			   + 1 // bIntervalX
			   + (2 * 64) // IntervalX
			   + 1 // bIntervalY
			   + (2 * 64) // IntervalY
			   + 1 // bIntervalZ
			   + (2 * 64); // IntervalZ
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}

	void Seed()
	{
		Vector.X = bIntervalX ? FMath::RandRange(IntervalX.Min, IntervalX.Max) : Vector.X;
		Vector.Y = bIntervalY ? FMath::RandRange(IntervalY.Min, IntervalY.Max) : Vector.Y;
		Vector.Z = bIntervalZ ? FMath::RandRange(IntervalZ.Min, IntervalZ.Max) : Vector.Z;
	}

	FORCEINLINE const FVector& Get()
	{
		return Vector;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsOptionalRotatorInterval
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator")
	FRotator Rotator; // 3 x 64 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator", meta = (InlineEditConditionToggle))
	bool bIntervalRoll; // 1 bit
	UPROPERTY(EditAnywhere, Category = "Rotator", meta = (editcondition = "bIntervalRoll"))
	FFloatInterval IntervalRoll; // 2 x 16 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator", meta = (InlineEditConditionToggle))
	bool bIntervalPitch; // 1 bit
	UPROPERTY(EditAnywhere, Category = "Rotator", meta = (editcondition = "bIntervalPitch"))
	FFloatInterval IntervalPitch; // 2 x 16 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator", meta = (InlineEditConditionToggle))
	bool bIntervalYaw;
	UPROPERTY(EditAnywhere, Category = "Rotator", meta = (editcondition = "bIntervalYaw"))
	FFloatInterval IntervalYaw;

	FCsOptionalRotatorInterval()
	{
		Reset();
	}
	~FCsOptionalRotatorInterval() {}

	FORCEINLINE FCsOptionalRotatorInterval& operator=(const FCsOptionalRotatorInterval& B)
	{
		Rotator = B.Rotator;
		// Roll
		bIntervalRoll = B.bIntervalRoll;
		IntervalRoll.Min = B.IntervalRoll.Min;
		IntervalRoll.Max = B.IntervalRoll.Max;
		// Pitch
		bIntervalPitch = B.bIntervalPitch;
		IntervalPitch.Min = B.IntervalPitch.Min;
		IntervalPitch.Max = B.IntervalPitch.Max;
		// Yaw
		bIntervalYaw = B.bIntervalYaw;
		IntervalYaw.Min = B.IntervalYaw.Min;
		IntervalYaw.Max = B.IntervalYaw.Max;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsOptionalRotatorInterval& B) const
	{
		return	Rotator == B.Rotator &&
				bIntervalRoll == B.bIntervalRoll &&
				IntervalRoll.Min == B.IntervalRoll.Min &&
				IntervalRoll.Max == B.IntervalRoll.Max &&
				bIntervalPitch == B.bIntervalPitch &&
				IntervalPitch.Min == B.IntervalPitch.Min &&
				IntervalPitch.Max == B.IntervalPitch.Max &&
				bIntervalYaw == B.bIntervalYaw &&
				IntervalYaw.Min == B.IntervalYaw.Min &&
				IntervalYaw.Max == B.IntervalYaw.Max;
	}

	FORCEINLINE bool operator!=(const FCsOptionalRotatorInterval& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		Rotator = FRotator::ZeroRotator;
		// Roll
		bIntervalRoll = false;
		IntervalRoll.Min = 0.0f;
		IntervalRoll.Max = 0.0f;
		// Pitch
		bIntervalPitch = false;
		IntervalPitch.Min = 0.0f;
		IntervalPitch.Max = 0.0f;
		// Yaw
		bIntervalYaw = false;
		IntervalYaw.Min = 0.0f;
		IntervalYaw.Max = 0.0f;
	}

	FORCEINLINE uint32 GetBits() const
	{
		return  (3 * 64) // Rotator
				+ 1 // bIntervalRoll
				+ (2 * 64) // IntervalRoll
				+ 1 // bIntervalPitch
				+ (2 * 64) // IntervalPitch
				+ 1 // bIntervalYaw
				+ (2 * 64); // IntervalYaw
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}

	void Seed()
	{
		Rotator.Roll = bIntervalRoll ? FMath::RandRange(IntervalRoll.Min, IntervalRoll.Max) : Rotator.Roll;
		Rotator.Pitch = bIntervalPitch ? FMath::RandRange(IntervalPitch.Min, IntervalPitch.Max) : Rotator.Pitch;
		Rotator.Yaw = bIntervalYaw ? FMath::RandRange(IntervalYaw.Min, IntervalYaw.Max) : Rotator.Yaw;
	}

	FORCEINLINE const FRotator& Get()
	{
		return Rotator;
	}
};

#pragma endregion Vector Types

// String
#pragma region

enum class ECsStringCompare : uint8
{
	Equals					UMETA(DisplayName = "Equals"),
	StartsWith				UMETA(DisplayName = "Starts With"),
	EndsWith				UMETA(DisplayName = "Ends With"),
	Contains				UMETA(DisplayName = "Contains"),
	ECsStringCompare_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsStringCompare : public TCsEnumMap<ECsStringCompare>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsStringCompare, ECsStringCompare)
};

namespace NCsStringCompare
{
	typedef ECsStringCompare Type;

	namespace Ref
	{
		extern CSCORE_API const Type Equals;
		extern CSCORE_API const Type StartsWith;
		extern CSCORE_API const Type EndsWith;
		extern CSCORE_API const Type Contains;
		extern CSCORE_API const Type ECsStringCompare_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	FORCEINLINE const FString& ToString(const Type& EType)
	{
		return EMCsStringCompare::Get().ToString(EType);
	}

	FORCEINLINE const Type& ToType(const FString& String)
	{
		return EMCsStringCompare::Get().ToType(String);
	}

	FORCEINLINE bool Compare(const FString& Source, const FString& String, const Type& EType)
	{
		if (EType == Type::Equals) { return Source == String; }
		if (EType == Type::StartsWith) { return Source.StartsWith(String); }
		if (EType == Type::EndsWith) { return Source.EndsWith(String); }
		if (EType == Type::Contains) { return Source.Contains(String); }
		return false;
	}
}

#pragma endregion String

USTRUCT(BlueprintType)
struct CSCORE_API FCsData_ShortCode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data_ShortCode")
	uint8 Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data_ShortCode")
	FName ShortCode;

public:
	FCsData_ShortCode()
	{
		Type = UINT8_MAX;
		ShortCode = CS_INVALID_SHORT_CODE;
	}
	virtual ~FCsData_ShortCode() {}

	FORCEINLINE FCsData_ShortCode& operator=(const FCsData_ShortCode& B)
	{
		Type = B.Type;
		ShortCode = B.ShortCode;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsData_ShortCode& B) const
	{
		if (Type != B.Type)
			return false;
		if (ShortCode != B.ShortCode)
			return false;
		return true;
	}

	FORCEINLINE bool operator!=(const FCsData_ShortCode& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE bool IsValid()
	{
		if (Type == UINT8_MAX)
			return false;
		if (ShortCode == CS_INVALID_SHORT_CODE)
			return false;
		return true;
	}
};