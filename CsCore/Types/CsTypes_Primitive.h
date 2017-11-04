// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"

#include "CsTypes_Primitive.generated.h"
#pragma once

// Enum Union
#pragma region

#pragma endregion Enum Union

// Primitive Types
#pragma region

template<typename T>
struct FCsPrimitiveType
{
public:
	T Value;
	T Last_Value;
protected:
	bool IsDirty;

public:
	FCsPrimitiveType(){}
	virtual ~FCsPrimitiveType(){}

	FCsPrimitiveType& operator=(const T& B)
	{
		Value   = B;
		IsDirty = Value != Last_Value;
		return *this;
	}

	bool operator==(const T& B) const
	{
		return Value == B;
	}

	bool operator!=(const T& B) const
	{
		return !(*this == B);
	}

	virtual void Set(const T &inValue)
	{
		Value   = inValue;
		IsDirty = Value != Last_Value;
	}

	T Get() { return Value; }

	virtual void Clear()
	{
		Last_Value = Value;
		IsDirty	   = false;
	}

	void Reset()
	{
		Value	   = T<>;
		Last_Value = Value;
		IsDirty	   = false;
	}

	bool HasChanged() { return IsDirty; }

};

struct FCsPrimitiveType_Int32 : FCsPrimitiveType<int32>
{
	FCsPrimitiveType_Int32(){}
	~FCsPrimitiveType_Int32(){}
};

typedef FCsPrimitiveType_Int32 TCsInt32;

struct FCsPrimitiveType_Float : FCsPrimitiveType<float>
{
	FCsPrimitiveType_Float(){}
	~FCsPrimitiveType_Float(){}

	FCsPrimitiveType_Float& operator=(const float& B)
	{
		Value = B;
		IsDirty = Value != Last_Value;
		return *this;
	}

	FORCEINLINE friend bool operator==(const float &Lhs, const FCsPrimitiveType_Float &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsPrimitiveType_Float &Lhs, const float &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const float &Lhs, const FCsPrimitiveType_Float &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsPrimitiveType_Float &Lhs, const float &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FCsPrimitiveType_Float& operator+=(const float& B)
	{
		Value += B;
		IsDirty = Value != Last_Value;
		return *this;
	}

	FCsPrimitiveType_Float& operator-=(const float& B)
	{
		Value -= B;
		IsDirty = Value != Last_Value;
		return *this;
	}

	FCsPrimitiveType_Float& operator*=(const float& B)
	{
		Value *= B;
		IsDirty = Value != Last_Value;
		return *this;
	}

	FORCEINLINE friend bool operator<(const FCsPrimitiveType_Float &Lhs, const float &Rhs)
	{
		return Lhs.Value < Rhs;
	}

	FORCEINLINE friend bool operator<(const float &Lhs, const FCsPrimitiveType_Float &Rhs)
	{
		return Lhs < Rhs.Value;
	}

	FORCEINLINE friend bool operator>(const FCsPrimitiveType_Float &Lhs, const float &Rhs)
	{
		return Lhs.Value > Rhs;
	}

	FORCEINLINE friend bool operator>(const float &Lhs, const FCsPrimitiveType_Float &Rhs)
	{
		return Lhs > Rhs.Value;
	}

	FORCEINLINE friend float operator/(const FCsPrimitiveType_Float &Lhs, const float &Rhs)
	{
		return Lhs.Value / Rhs;
	}

	FORCEINLINE friend float operator/(const float &Lhs, const FCsPrimitiveType_Float &Rhs)
	{
		return Lhs / Rhs.Value;
	}

	FORCEINLINE friend float operator*(const FCsPrimitiveType_Float &Lhs, const float &Rhs)
	{
		return Lhs.Value * Rhs;
	}

	FORCEINLINE friend float operator*(const float &Lhs, const FCsPrimitiveType_Float &Rhs)
	{
		return Lhs * Rhs.Value;
	}
};

typedef FCsPrimitiveType_Float TCsFloat;

#define CS_AXES 3
#define CS_AXIS_X 0
#define CS_AXIS_Y 1
#define CS_AXIS_Z 2
#define CS_AXES_ALL 3

struct FCsPrimitiveType_FVector : public FCsPrimitiveType<FVector>
{

protected:
	bool IsDirtys[CS_AXES];

public:

	FCsPrimitiveType_FVector(){}
	~FCsPrimitiveType_FVector(){}

	FCsPrimitiveType_FVector& operator=(const FVector& B)
	{
		Value = B;
		IsDirty = Value != Last_Value;
		IsDirtys[CS_AXIS_X] = Value.X != Last_Value.X;
		IsDirtys[CS_AXIS_Y] = Value.Y != Last_Value.Y;
		IsDirtys[CS_AXIS_Z] = Value.Z != Last_Value.Z;
		return *this;
	}

	virtual void Set(const FVector &inValue) override 
	{
		Value = inValue;
		IsDirty = Value != Last_Value;
		IsDirtys[CS_AXIS_X] = Value.X != Last_Value.X;
		IsDirtys[CS_AXIS_Y] = Value.Y != Last_Value.Y;
		IsDirtys[CS_AXIS_Z] = Value.Z != Last_Value.Z;
	}

	FVector GetAxes(const int32 &Axes)
	{
		FVector V = FVector::ZeroVector;

		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_X))
			V.X = Value.X;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Y))
			V.Y = Value.Y;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Z))
			V.Z = Value.Z;
		return V;
	}

	virtual void Clear() override
	{
		Last_Value = Value;
		IsDirty = false;
		IsDirtys[CS_AXIS_X] = false;
		IsDirtys[CS_AXIS_Y] = false;
		IsDirtys[CS_AXIS_Z] = false;
	}

	bool HasAxisChanged(const uint8 &Axis)
	{
		if (!IsDirty)
			return false;
		if (Axis < CS_AXIS_X || Axis > CS_AXIS_Z)
			return true;
		return IsDirtys[Axis];
	}

	bool HasAxesChanged(const int32 &Axes)
	{
		if (!IsDirty)
			return false;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_X) && IsDirtys[CS_AXIS_X])
			return true;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Y) && IsDirtys[CS_AXIS_Y])
			return true;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Z) && IsDirtys[CS_AXIS_Z])
			return true;
		return false;
	}
};

typedef FCsPrimitiveType_FVector TCsFVector;

#define CS_AXIS_ROLL 0
#define CS_AXIS_PITCH 1
#define CS_AXIS_YAW 2


struct FCsPrimitiveType_FRotator : public FCsPrimitiveType<FRotator>
{

protected:
	bool IsDirtys[CS_AXES];

public:

	FCsPrimitiveType_FRotator(){}
	~FCsPrimitiveType_FRotator(){}

	FCsPrimitiveType_FRotator& operator=(const FRotator& B)
	{
		Value = B;
		IsDirty = Value != Last_Value;
		IsDirtys[CS_AXIS_ROLL] = Value.Roll != Last_Value.Roll;
		IsDirtys[CS_AXIS_PITCH] = Value.Pitch != Last_Value.Pitch;
		IsDirtys[CS_AXIS_YAW] = Value.Yaw != Last_Value.Yaw;
		return *this;
	}

	virtual void Set(const FRotator &inValue) override
	{
		Value = inValue;
		IsDirty = Value != Last_Value;
		IsDirtys[CS_AXIS_ROLL] = Value.Roll != Last_Value.Roll;
		IsDirtys[CS_AXIS_PITCH] = Value.Pitch != Last_Value.Pitch;
		IsDirtys[CS_AXIS_YAW] = Value.Yaw != Last_Value.Yaw;
	}

	FRotator GetAxes(const int32 &Axes)
	{
		FRotator V = FRotator::ZeroRotator;

		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_ROLL))
			V.Roll = Value.Roll;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_PITCH))
			V.Pitch = Value.Pitch;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_YAW))
			V.Yaw = Value.Yaw;
		return V;
	}

	virtual void Clear() override
	{
		Last_Value = Value;
		IsDirty = false;
		IsDirtys[CS_AXIS_ROLL] = false;
		IsDirtys[CS_AXIS_PITCH] = false;
		IsDirtys[CS_AXIS_YAW] = false;
	}

	bool HasAxisChanged(const uint8 &Axis)
	{
		if (!IsDirty)
			return false;
		if (Axis < CS_AXIS_PITCH || Axis > CS_AXIS_ROLL)
			return true;
		return IsDirtys[Axis];
	}

	bool HasAxesChanged(const int32 &Axes)
	{
		if (!IsDirty)
			return false;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_ROLL) && IsDirtys[CS_AXIS_ROLL])
			return true;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_PITCH) && IsDirtys[CS_AXIS_PITCH])
			return true;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_YAW) && IsDirtys[CS_AXIS_YAW])
			return true;
		return false;
	}
};

typedef FCsPrimitiveType_FRotator TCsFRotator;

template<typename T>
struct FCsPrimitiveType_Ref
{
public:
	T* Value;
	T Last_Value;
protected:
	bool IsDirty;

public:
	FCsPrimitiveType_Ref(){}
	virtual ~FCsPrimitiveType_Ref(){}

	FCsPrimitiveType_Ref& operator=(const T& B)
	{
		Value = B;
		IsDirty = Value != Last_Value;
		return *this;
	}

	bool operator==(const T& B) const
	{
		return Value == B;
	}

	bool operator!=(const T& B) const
	{
		return !(*this == B);
	}

	void Set(T* inValue)
	{
		Value   = inValue;
		IsDirty = *Value != Last_Value;
	}

	void Set(const T &inValue)
	{
		*Value  = inValue;
		IsDirty = *Value != Last_Value;
	}

	T Get() { return *Value; }

	virtual T GetDefaultValue() { return T(); }

	void Clear()
	{
		Last_Value = *Value;
		IsDirty	   = false;
	}

	void Reset()
	{
		Value	   = GetDefaultValue();
		Last_Value = *Value;
		IsDirty	   = false;
	}

	bool IsChanged() 
	{ 
		IsDirty = *Value != Last_Value;
		return IsDirty;
	}

	bool HasChanged() { return IsDirty; }
};

struct FCsPrimitiveType_Ref_Int32 : FCsPrimitiveType_Ref<int32>
{
	virtual int32 GetDefaultValue() override
	{
		return 0;
	}
};

typedef FCsPrimitiveType_Ref_Int32 TCsInt32_Ref;

struct FCsPrimitiveType_Ref_Float : FCsPrimitiveType_Ref<float>
{
	FCsPrimitiveType_Ref_Float(){}
	~FCsPrimitiveType_Ref_Float(){}

	virtual float GetDefaultValue() override
	{
		return 0.0f;
	}
};

typedef FCsPrimitiveType_Ref_Float TCsFloat_Ref;

#define CS_PRIMITIVE_TYPE_DEFAULT -1

// DON'T USE int64 for U
template<typename T, typename U = int32, uint8 SIZE = 1>
struct FCsPrimitiveType_MultiValue
{
public:
	T Value;
	T Last_Value;

	T Values[SIZE];
	T Last_Values[SIZE];
protected:
	bool IsDirty;

	bool IsDirtys[SIZE];
public:

	FCsPrimitiveType_MultiValue(){}
	virtual ~FCsPrimitiveType_MultiValue(){}

	FCsPrimitiveType_MultiValue& operator=(const T& B)
	{
		Value  = B;
		IsDirty = Value != Last_Value;

		for (uint8 I = 0; I < SIZE; I++)
		{
			Values[I] = B.Values[I];
			IsDirtys[I] = Values[I] != Last_Values[I];
		}
		return *this;
	}

	bool operator==(const FCsPrimitiveType_MultiValue& B) const
	{
		for (uint8 I = 0; I < SIZE; I++)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B;
	}

	bool operator!=(const FCsPrimitiveType_MultiValue& B) const
	{
		return !(*this == B);
	}

	void Set(const T &inValue)
	{
		Value   = inValue;
		IsDirty = Value != Last_Value;
	}

	void Set(const U &Index, const T &inValue)
	{
		Set((int64)Index, inValue);
	}

	void Set(const int64 &Index, const T &inValue)
	{
		const int64 I = (int64)Index;

		if (Index > CS_PRIMITIVE_TYPE_DEFAULT && Index < SIZE)
		{
			Values[Index]   = inValue;
			IsDirtys[Index] = Values[Index] != Last_Values[Index];
		}
		else
		{
			Set(inValue);
		}
	}

	T Get() { return Value; }
	T Get(const U &Index) { return Get((int64)Index); }

	T Get(const int64 &Index)
	{
		return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? Value : Values[Index];
	}

	void Clear()
	{
		Last_Value = Value;
		IsDirty	   = false;

		for (uint8 I = 0; I < SIZE; I++)
		{
			Last_Values[I] = Values[I];
			IsDirtys[I]	   = false;
		}
	}

	virtual T GetDefaultValue() { return T(); }

	void Reset()
	{
		Value	   = GetDefaultValue();
		Last_Value = Value;
		IsDirty	   = false;

		for (uint8 I = 0; I < SIZE; I++)
		{
			Values[I]      = Value;
			Last_Values[I] = Value;
			IsDirtys[I]	   = false;
		}
	}

	bool HasChanged() { return IsDirty; }
	bool HasChanged(const U &Index) { return HasChanged((int64)Index); }
	bool HasChanged(const int64 &Index) { return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? IsDirty : IsDirtys[Index]; }
};

template<typename T, typename U, uint8 SIZE>
struct FCsIntegralType_MultiValue : FCsPrimitiveType_MultiValue<T, U, SIZE>
{
	FCsIntegralType_MultiValue(){}
	~FCsIntegralType_MultiValue(){}

	virtual T GetDefaultValue() override
	{
		return (T)0;
	}

	void Add(const T &inValue) 
	{ 
		Value  += inValue; 
		IsDirty = Value != Last_Value;
	}

	void Add(const U &Index, const T &inValue) { Add((int64)Index, inValue); }

	void Add(const int64 &Index, const T &inValue)
	{
		if (Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE)
		{
			Add(inValue);
		}
		else
		{
			Values[Index]  += inValue;
			IsDirtys[Index] = Values[Index] != Last_Values[Index];
		}
	}

	void Subtract(const T &inValue) 
	{ 
		Value  -= inValue;
		IsDirty = Value != Last_Value;
	}

	void Subtract(const U &Index, const T &inValue) { Subtract((int64)Index, inValue); }

	void Subtract(const int64 &Index, const T &inValue)
	{
		if (Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE)
		{
			Subtract(inValue);
		}
		else
		{
			Values[Index]  -= inValue;
			IsDirtys[Index] = Values[Index] != Last_Values[Index];
		}
	}

	T Max()
	{
		T max = Values[0];

		for (uint8 I = 1; I < SIZE; I++)
		{
			max = (T)FMath::Max(max, Values[I]);
		}
		return max;
	}

	T Min()
	{
		T min = Values[0];

		for (uint8 I = 1; I < SIZE; I++)
		{
			min = (T)FMath::Min(min, Values[I]);
		}
		return min;
	}
};

template<typename U, uint8 SIZE>
struct FCsPrimitiveType_MultiValue_bool : FCsPrimitiveType_MultiValue<bool, U, SIZE>
{
	FCsPrimitiveType_MultiValue_bool(){}
	~FCsPrimitiveType_MultiValue_bool(){}

	virtual bool GetDefaultValue() override
	{
		return false;
	}

	bool Or()
	{
		bool or = Values[0];

		for (uint8 I = 1; I < SIZE; I++)
		{
			or |= Values[I];
		}
		return or;
	}

	bool And()
	{
		bool and = Values[0];

		for (uint8 I = 1; I < SIZE; I++)
		{
			and &= Values[I];
		}
		return and;
	}
};

template<typename U, uint8 SIZE>
struct FCsPrimitiveType_MultiValue_FString : FCsPrimitiveType_MultiValue<FString, U, SIZE>
{
	FCsPrimitiveType_MultiValue_FString(){}
	~FCsPrimitiveType_MultiValue_FString(){}

	virtual FString GetDefaultValue() override
	{
		return TEXT("");
	}
};

#define CS_FSTRING_ENUM_TWO_PARAMS 2
#define CS_FSTRING_ENUM_THREE_PARAMS 3
#define CS_FSTRING_ENUM_DEFAULT_VALUE 0
#define CS_FSTRING_ENUM_LOWER_VALUE 1
#define CS_FSTRING_ENUM_ALT_1_VALUE 2

struct FCsPrimitiveType_MultiValue_FString_Enum_TwoParams : FCsPrimitiveType_MultiValue_FString<int32, CS_FSTRING_ENUM_TWO_PARAMS>
{
	FCsPrimitiveType_MultiValue_FString_Enum_TwoParams(){}
	~FCsPrimitiveType_MultiValue_FString_Enum_TwoParams(){}

	FCsPrimitiveType_MultiValue_FString_Enum_TwoParams(const FString &inValue1, const FString &inValue2)
	{
		Value = inValue1;

		Values[CS_FSTRING_ENUM_DEFAULT_VALUE] = inValue1;
		Values[CS_FSTRING_ENUM_LOWER_VALUE] = inValue2;
	}

	FORCEINLINE friend bool operator==(const FString &Lhs, const FCsPrimitiveType_MultiValue_FString_Enum_TwoParams &Rhs)
	{
		const FString Lower = Lhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_TWO_PARAMS; I++)
		{
			if (Rhs.Values[I] == Lhs || Rhs.Values[I] == Lower)
				return true;
		}
		return Rhs.Value == Lhs || Rhs.Value == Lower;
	}

	FORCEINLINE friend bool operator==(const FCsPrimitiveType_MultiValue_FString_Enum_TwoParams &Lhs, const FString &Rhs)
	{
		const FString Lower = Rhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_TWO_PARAMS; I++)
		{
			if (Lhs.Values[I] == Rhs || Lhs.Values[I] == Lower)
				return true;
		}
		return Lhs.Value == Rhs || Lhs.Value == Lower;
	}

	FORCEINLINE friend bool operator!=(const FString &Lhs, const FCsPrimitiveType_MultiValue_FString_Enum_TwoParams &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsPrimitiveType_MultiValue_FString_Enum_TwoParams &Lhs, const FString &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

struct FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams : FCsPrimitiveType_MultiValue_FString<int32, CS_FSTRING_ENUM_THREE_PARAMS>
{
	FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams(){}
	~FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams(){}

	FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams(const FString &inValue1, const FString &inValue2, const FString &inValue3)
	{
		Value = inValue1;

		Values[CS_FSTRING_ENUM_DEFAULT_VALUE] = inValue1;
		Values[CS_FSTRING_ENUM_LOWER_VALUE]   = inValue2;
		Values[CS_FSTRING_ENUM_ALT_1_VALUE]   = inValue3;
	}
	
	FORCEINLINE friend bool operator==(const FString &Lhs, const FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams &Rhs)
	{
		const FString Lower = Lhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_THREE_PARAMS; I++)
		{
			if (Rhs.Values[I] == Lhs || Rhs.Values[I] == Lower)
				return true;
		}
		return Rhs.Value == Lhs || Rhs.Value == Lower;
	}

	FORCEINLINE friend bool operator==(const FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams &Lhs, const FString &Rhs)
	{
		const FString Lower = Rhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_THREE_PARAMS; I++)
		{
			if (Lhs.Values[I] == Rhs || Lhs.Values[I] == Lower)
				return true;
		}
		return Lhs.Value == Rhs || Lhs.Value == Lower;
	}

	FORCEINLINE friend bool operator!=(const FString &Lhs, const FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams &Lhs, const FString &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

// DON'T USE int64 for U
template<typename T, typename U = int32, uint8 SIZE = 1>
struct FCsPrimitiveType_MultiRefValue
{
public:
	T Value;
	T Last_Value;

	T* Values[SIZE];
	T Last_Values[SIZE];
protected:
	bool IsDirty;

	bool IsDirtys[SIZE];
public:

	FCsPrimitiveType_MultiRefValue(){}
	virtual ~FCsPrimitiveType_MultiRefValue(){}

	FCsPrimitiveType_MultiRefValue& operator=(const T& B)
	{
		Value   = B;
		IsDirty = Value != Last_Value;

		for (uint8 I = 0; I < SIZE; I++)
		{
			Values[I]   = B.Values[I];
			IsDirtys[I] = *(Values[I]) != Last_Values[I];
		}
		return *this;
	}

	bool operator==(const FCsPrimitiveType_MultiRefValue& B) const
	{
		for (uint8 I = 0; I < SIZE; I++)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B;
	}

	bool operator!=(const FCsPrimitiveType_MultiRefValue& B) const
	{
		return !(*this == B);
	}

	void Set(T &inValue)
	{
		Value   = inValue;
		IsDirty = Value != Last_Value;
	}

	void Set(const U &Index, T* inValue)
	{
		Set((int64)Index, inValue);
	}

	void Set(const int64 &Index, T* inValue)
	{
		if (Index > CS_PRIMITIVE_TYPE_DEFAULT && Index < SIZE)
		{
			Values[Index]   = inValue;
			IsDirtys[Index] = *(Values[Index]) != Last_Values[Index];
		}
		else
		{
			Set(*inValue);
		}
	}

	T Get() { return Value; }
	T Get(const U &Index) { return Get((int64)Index); }

	T Get(const int64 &Index)
	{
		return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? Value : *(Values[Index]);
	}

	void Clear()
	{
		Last_Value = Value;
		IsDirty	   = false;

		for (uint8 I = 0; I < SIZE; I++)
		{
			Last_Values[I] = *(Values[I]);
			IsDirtys[I]	   = false;
		}
	}

	virtual T GetDefaultValue() { return T(); }

	void Reset()
	{
		Value	   = GetDefaultValue();
		Last_Value = Value;
		IsDirty	   = false;

		for (uint8 I = 0; I < SIZE; I++)
		{
			Values[I]	   = nullptr;
			Last_Values[I] = Value;
			IsDirtys[I]	   = false;
		}
	}

	bool HasChanged() { return IsDirty; }

	bool HasChanged(const U &Index) 
	{ 
		const int32 I = (int32)Index;
		return I <= CS_PRIMITIVE_TYPE_DEFAULT || I >= SIZE ? IsDirty : IsDirtys[I];
	}
};

template<typename T, typename U, uint8 SIZE>
struct FCsIntegralType_MultiRefValue : FCsPrimitiveType_MultiRefValue<T, U, SIZE>
{
	FCsIntegralType_MultiRefValue(){}
	~FCsIntegralType_MultiRefValue(){}

	virtual T GetDefaultValue() override
	{
		return (T)0;
	}

	T Max()
	{
		T max = *(Values[0]);

		for (uint8 I = 1; I < SIZE; I++)
		{
			max = (T)FMath::Max(max, *(Values[I]));
		}
		return max;
	}

	T Min()
	{
		T min = *(Values[0]);

		for (uint8 I = 1; I < SIZE; I++)
		{
			min = (T)FMath::Min(min, *(Values[I]));
		}
		return min;
	}
};

template<typename U, uint8 SIZE>
struct FCsPrimitiveType_MultiRefValue_bool : FCsPrimitiveType_MultiRefValue<bool, U, SIZE>
{
	FCsPrimitiveType_MultiRefValue_bool(){}
	~FCsPrimitiveType_MultiRefValue_bool(){}

	virtual bool GetDefaultValue() override
	{
		return false;
	}

	bool Or()
	{
		bool or = Values[0];

		for (uint8 I = 1; I < SIZE; I++)
		{
			or |= Values[I];
		}
		return or ;
	}

	bool And()
	{
		bool and = Values[0];

		for (uint8 I = 1; I < SIZE; I++)
		{
			and &= Values[I];
		}
		return and;
	}
};

UENUM(BlueprintType)
namespace ECsMemberType
{
	enum Type
	{
		Bool				UMETA(DisplayName = "Bool"),
		Uint8				UMETA(DisplayName = "Uint8"),
		Int32				UMETA(DisplayName = "Int32"),
		Float				UMETA(DisplayName = "Float"),
		_FString			UMETA(DisplayName = "FString"),
		FName				UMETA(DisplayName = "FName"),
		FVector				UMETA(DisplayName = "FVector"),
		FRotator			UMETA(DisplayName = "FRotator"),
		FColor				UMETA(DisplayName = "FColor"),
		ECsMemberType_MAX	UMETA(Hidden),
	};
}

namespace ECsMemberType
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Bool = TCsString(TEXT("Bool"), TEXT("bool"));
		const TCsString Uint8 = TCsString(TEXT("Uint8"), TEXT("uint8"));
		const TCsString Int32 = TCsString(TEXT("Int32"), TEXT("int32"));
		const TCsString Float = TCsString(TEXT("Float"), TEXT("float"));
		const TCsString _FString = TCsString(TEXT("FString"), TEXT("fstring"));
		const TCsString FName = TCsString(TEXT("FName"), TEXT("fname"));
		const TCsString FVector = TCsString(TEXT("FVector"), TEXT("fvector"));
		const TCsString FRotator = TCsString(TEXT("FRotator"), TEXT("frotator"));
		const TCsString FColor = TCsString(TEXT("FColor"), TEXT("fcolor"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Bool) { return Str::Bool.Value; }
		if (EType == Type::Uint8) { return Str::Uint8.Value; }
		if (EType == Type::Int32) { return Str::Int32.Value; }
		if (EType == Type::Float) { return Str::Float.Value; }
		if (EType == Type::_FString) { return Str::_FString.Value; }
		if (EType == Type::FName) { return Str::FName.Value; }
		if (EType == Type::FVector) { return Str::FVector.Value; }
		if (EType == Type::FRotator) { return Str::FRotator.Value; }
		if (EType == Type::FColor) { return Str::FColor.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Bool) { return Type::Bool; }
		if (String == Str::Uint8) { return Type::Uint8; }
		if (String == Str::Int32) { return Type::Int32; }
		if (String == Str::Float) { return Type::Float; }
		if (String == Str::_FString) { return Type::_FString; }
		if (String == Str::FName) { return Type::FName; }
		if (String == Str::FVector) { return Type::FVector; }
		if (String == Str::FRotator) { return Type::FRotator; }
		if (String == Str::FColor) { return Type::FColor; }
		return Type::ECsMemberType_MAX;
	}
}

#define ECS_MEMBER_TYPE_MAX (uint8)ECsMemberType::ECsMemberType_MAX
typedef TEnumAsByte<ECsMemberType::Type> TCsMemberType;

#define CS_DECLARE_AND_DEFINE_CONST_INTEGRAL_VALUE(Type, Integral, Value) const Type Integral = 1; \
																		  Type* ptr = (Type*)(&Integral); \
																		  *ptr = Value;

#pragma endregion Primitive Types