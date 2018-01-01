// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"

#include "CsTypes_Primitive.generated.h"
#pragma once

// String
#pragma region

namespace ECsCachedString
{
	namespace Str
	{
		const FString Empty = TEXT("");
		const FString None = TEXT("None");
		const FString Json = TEXT(".json");
		const FString INVALID = TEXT("INVALID");
		const FString Dot = TEXT(".");
	}
}

#pragma endregion String

// Enum Union
#pragma region

#pragma endregion Enum Union

// Primitive Types
#pragma region

template<typename T>
struct TCsPrimitiveType
{
public:
	T DefaultValue;
	T Value;
	T Last_Value;
protected:
	bool IsDirty;
public:
	TMulticastDelegate<void, const T&> OnChange_Event;

public:
	TCsPrimitiveType(){}
	virtual ~TCsPrimitiveType(){}

	void SetDefaultValue(const T &inDefaultValue)
	{
		DefaultValue = inDefaultValue;
	}

	virtual void UpdateIsDirty()
	{
		IsDirty = Value != Last_Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	TCsPrimitiveType& operator=(const T& B)
	{
		Value = B;
		UpdateIsDirty();
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
		Value = inValue;
		UpdateIsDirty();
	}

	T Get() { return Value; }

	virtual void Clear()
	{
		Last_Value = Value;
		IsDirty	   = false;
	}

	void ResetValue()
	{
		Value	   = DefaultValue;
		Last_Value = Value;
		IsDirty	   = false;
	}

	void Reset()
	{
		ResetValue();

		OnChange_Event.Clear();
	}

	bool HasChanged() { return IsDirty; }

};

struct TCsPrimitiveType_Int32 : public TCsPrimitiveType<int32>
{
	TCsPrimitiveType_Int32()
	{
		DefaultValue = 0;
	}
	~TCsPrimitiveType_Int32(){}

	TCsPrimitiveType_Int32& operator=(const int32& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const int32 &Lhs, const TCsPrimitiveType_Int32 &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const TCsPrimitiveType_Int32 &Lhs, const int32 &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const int32 &Lhs, const TCsPrimitiveType_Int32 &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsPrimitiveType_Int32 &Lhs, const int32 &Rhs)
	{
		return !(Lhs == Rhs);
	}

	TCsPrimitiveType_Int32& operator+=(const int32& B)
	{
		Value += B;
		UpdateIsDirty();
		return *this;
	}

	TCsPrimitiveType_Int32& operator-=(const int32& B)
	{
		Value -= B;
		UpdateIsDirty();
		return *this;
	}

	TCsPrimitiveType_Int32& operator*=(const int32& B)
	{
		Value *= B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator<(const TCsPrimitiveType_Int32 &Lhs, const int32 &Rhs)
	{
		return Lhs.Value < Rhs;
	}

	FORCEINLINE friend bool operator<(const int32 &Lhs, const TCsPrimitiveType_Int32 &Rhs)
	{
		return Lhs < Rhs.Value;
	}

	FORCEINLINE friend bool operator>(const TCsPrimitiveType_Int32 &Lhs, const int32 &Rhs)
	{
		return Lhs.Value > Rhs;
	}

	FORCEINLINE friend bool operator>(const int32 &Lhs, const TCsPrimitiveType_Int32 &Rhs)
	{
		return Lhs > Rhs.Value;
	}

	FORCEINLINE friend float operator/(const TCsPrimitiveType_Int32 &Lhs, const int32 &Rhs)
	{
		return Lhs.Value / Rhs;
	}

	FORCEINLINE friend float operator/(const int32 &Lhs, const TCsPrimitiveType_Int32 &Rhs)
	{
		return Lhs / Rhs.Value;
	}

	FORCEINLINE friend float operator*(const TCsPrimitiveType_Int32 &Lhs, const int32 &Rhs)
	{
		return Lhs.Value * Rhs;
	}

	FORCEINLINE friend float operator*(const int32 &Lhs, const TCsPrimitiveType_Int32 &Rhs)
	{
		return Lhs * Rhs.Value;
	}
};

typedef TCsPrimitiveType_Int32 TCsInt32;

struct TCsPrimitiveType_Float : public TCsPrimitiveType<float>
{
	TCsPrimitiveType_Float()
	{
		DefaultValue = 0.0f;
	}
	~TCsPrimitiveType_Float(){}

	TCsPrimitiveType_Float& operator=(const float& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const float &Lhs, const TCsPrimitiveType_Float &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const TCsPrimitiveType_Float &Lhs, const float &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const float &Lhs, const TCsPrimitiveType_Float &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsPrimitiveType_Float &Lhs, const float &Rhs)
	{
		return !(Lhs == Rhs);
	}

	TCsPrimitiveType_Float& operator+=(const float& B)
	{
		Value += B;
		UpdateIsDirty();
		return *this;
	}

	TCsPrimitiveType_Float& operator-=(const float& B)
	{
		Value -= B;
		UpdateIsDirty();
		return *this;
	}

	TCsPrimitiveType_Float& operator*=(const float& B)
	{
		Value *= B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator<(const TCsPrimitiveType_Float &Lhs, const float &Rhs)
	{
		return Lhs.Value < Rhs;
	}

	FORCEINLINE friend bool operator<(const float &Lhs, const TCsPrimitiveType_Float &Rhs)
	{
		return Lhs < Rhs.Value;
	}

	FORCEINLINE friend bool operator>(const TCsPrimitiveType_Float &Lhs, const float &Rhs)
	{
		return Lhs.Value > Rhs;
	}

	FORCEINLINE friend bool operator>(const float &Lhs, const TCsPrimitiveType_Float &Rhs)
	{
		return Lhs > Rhs.Value;
	}

	FORCEINLINE friend float operator/(const TCsPrimitiveType_Float &Lhs, const float &Rhs)
	{
		return Lhs.Value / Rhs;
	}

	FORCEINLINE friend float operator/(const float &Lhs, const TCsPrimitiveType_Float &Rhs)
	{
		return Lhs / Rhs.Value;
	}

	FORCEINLINE friend float operator*(const TCsPrimitiveType_Float &Lhs, const float &Rhs)
	{
		return Lhs.Value * Rhs;
	}

	FORCEINLINE friend float operator*(const float &Lhs, const TCsPrimitiveType_Float &Rhs)
	{
		return Lhs * Rhs.Value;
	}
};

typedef TCsPrimitiveType_Float TCsFloat;

#define CS_AXES_2D 2
#define CS_AXES_3D 3
#define CS_AXIS_X 0
#define CS_AXIS_Y 1
#define CS_AXIS_Z 2
#define CS_AXES_3D_ALL 3

struct TCsPrimitiveType_FVector2D : public TCsPrimitiveType<FVector2D>
{

protected:
	bool IsDirtys[CS_AXES_2D];

public:

	TCsPrimitiveType_FVector2D() 
	{
		DefaultValue = FVector2D::ZeroVector;
	}
	~TCsPrimitiveType_FVector2D() {}

	virtual void UpdateIsDirty() override
	{
		IsDirty = Value != Last_Value;
		IsDirtys[CS_AXIS_X] = Value.X != Last_Value.X;
		IsDirtys[CS_AXIS_Y] = Value.Y != Last_Value.Y;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	TCsPrimitiveType_FVector2D& operator=(const FVector2D& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FVector2D &Lhs, const TCsPrimitiveType_FVector2D &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const TCsPrimitiveType_FVector2D &Lhs, const FVector2D &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FVector2D &Lhs, const TCsPrimitiveType_FVector2D &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsPrimitiveType_FVector2D &Lhs, const FVector2D &Rhs)
	{
		return !(Lhs == Rhs);
	}

	TCsPrimitiveType_FVector2D& operator+=(const FVector2D& B)
	{
		Value += B;
		UpdateIsDirty();
		return *this;
	}

	TCsPrimitiveType_FVector2D& operator-=(const FVector2D& B)
	{
		Value -= B;
		UpdateIsDirty();
		return *this;
	}

	TCsPrimitiveType_FVector2D& operator*=(const FVector2D& B)
	{
		Value *= B;
		UpdateIsDirty();
		return *this;
	}

	virtual void Set(const FVector2D &inValue) override
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FVector2D GetAxes(const int32 &Axes)
	{
		FVector2D V = FVector2D::ZeroVector;

		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_X))
			V.X = Value.X;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Y))
			V.Y = Value.Y;
		return V;
	}

	virtual void Clear() override
	{
		Last_Value = Value;
		IsDirty = false;
		IsDirtys[CS_AXIS_X] = false;
		IsDirtys[CS_AXIS_Y] = false;
	}

	bool HasAxisChanged(const uint8 &Axis)
	{
		if (!IsDirty)
			return false;
		if (Axis < CS_AXIS_X || Axis > CS_AXIS_Y)
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
		return false;
	}
};

typedef TCsPrimitiveType_FVector2D TCsFVector2D;

struct TCsPrimitiveType_FVector : public TCsPrimitiveType<FVector>
{

protected:
	bool IsDirtys[CS_AXES_3D];

public:

	TCsPrimitiveType_FVector()
	{
		DefaultValue = FVector::ZeroVector;
	}
	~TCsPrimitiveType_FVector(){}

	virtual void UpdateIsDirty() override
	{
		IsDirty = Value != Last_Value;
		IsDirtys[CS_AXIS_X] = Value.X != Last_Value.X;
		IsDirtys[CS_AXIS_Y] = Value.Y != Last_Value.Y;
		IsDirtys[CS_AXIS_Z] = Value.Z != Last_Value.Z;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	TCsPrimitiveType_FVector& operator=(const FVector& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FVector &Lhs, const TCsPrimitiveType_FVector &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const TCsPrimitiveType_FVector &Lhs, const FVector &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FVector &Lhs, const TCsPrimitiveType_FVector &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsPrimitiveType_FVector &Lhs, const FVector &Rhs)
	{
		return !(Lhs == Rhs);
	}

	TCsPrimitiveType_FVector& operator+=(const FVector& B)
	{
		Value += B;
		UpdateIsDirty();
		return *this;
	}

	TCsPrimitiveType_FVector& operator-=(const FVector& B)
	{
		Value -= B;
		UpdateIsDirty();
		return *this;
	}

	TCsPrimitiveType_FVector& operator*=(const FVector& B)
	{
		Value *= B;
		UpdateIsDirty();
		return *this;
	}

	virtual void Set(const FVector &inValue) override 
	{
		Value = inValue;
		UpdateIsDirty();
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

typedef TCsPrimitiveType_FVector TCsFVector;

#define CS_AXIS_ROLL 0
#define CS_AXIS_PITCH 1
#define CS_AXIS_YAW 2


struct TCsPrimitiveType_FRotator : public TCsPrimitiveType<FRotator>
{

protected:
	bool IsDirtys[CS_AXES_3D];

public:

	TCsPrimitiveType_FRotator()
	{
		DefaultValue = FRotator::ZeroRotator;
	}
	~TCsPrimitiveType_FRotator(){}

	virtual void UpdateIsDirty() override
	{
		IsDirty = Value != Last_Value;
		IsDirtys[CS_AXIS_ROLL] = Value.Roll != Last_Value.Roll;
		IsDirtys[CS_AXIS_PITCH] = Value.Pitch != Last_Value.Pitch;
		IsDirtys[CS_AXIS_YAW] = Value.Yaw != Last_Value.Yaw;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	TCsPrimitiveType_FRotator& operator=(const FRotator& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FRotator &Lhs, const TCsPrimitiveType_FRotator &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const TCsPrimitiveType_FRotator &Lhs, const FRotator &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FRotator &Lhs, const TCsPrimitiveType_FRotator &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsPrimitiveType_FRotator &Lhs, const FRotator &Rhs)
	{
		return !(Lhs == Rhs);
	}

	TCsPrimitiveType_FRotator& operator+=(const FRotator& B)
	{
		Value += B;
		UpdateIsDirty();
		return *this;
	}

	TCsPrimitiveType_FRotator& operator-=(const FRotator& B)
	{
		Value -= B;
		UpdateIsDirty();
		return *this;
	}

	virtual void Set(const FRotator &inValue) override
	{
		Value = inValue;
		UpdateIsDirty();
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

typedef TCsPrimitiveType_FRotator TCsFRotator;

struct TCsPrimitiveType_FString : public TCsPrimitiveType<FString>
{
public:

	TCsPrimitiveType_FString()
	{
		DefaultValue = ECsCachedString::Str::Empty;
	}
	~TCsPrimitiveType_FString() {}

	TCsPrimitiveType_FString& operator=(const FString& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FString &Lhs, const TCsPrimitiveType_FString &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const TCsPrimitiveType_FString &Lhs, const FString &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FString &Lhs, const TCsPrimitiveType_FString &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsPrimitiveType_FString &Lhs, const FString &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

typedef TCsPrimitiveType_FString TCsFString;

struct TCsPrimitiveType_FLinearColor : public TCsPrimitiveType<FLinearColor>
{
public:

	TCsPrimitiveType_FLinearColor()
	{
		DefaultValue = FLinearColor::White;
	}
	~TCsPrimitiveType_FLinearColor() {}

	TCsPrimitiveType_FLinearColor& operator=(const FLinearColor& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FLinearColor &Lhs, const TCsPrimitiveType_FLinearColor &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const TCsPrimitiveType_FLinearColor &Lhs, const FLinearColor &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FLinearColor &Lhs, const TCsPrimitiveType_FLinearColor &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsPrimitiveType_FLinearColor &Lhs, const FLinearColor &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

typedef TCsPrimitiveType_FLinearColor TCsFLinearColor;

// Ref
#pragma region

template<typename T>
struct TCsPrimitiveType_Ref
{
public:
	T DefaultValue;
	T* Value;
	T Last_Value;
protected:
	bool IsDirty;
public:
	TMulticastDelegate<void, const T&> OnChange_Event;

public:
	TCsPrimitiveType_Ref(){}
	virtual ~TCsPrimitiveType_Ref(){}

	void SetDefaultValue(const T &inDefaultValue)
	{
		DefaultValue = inDefaultValue;
	}

	virtual void UpdateIsDirty()
	{
		IsDirty = *Value != Last_Value;

		if (IsDirty)
			OnChange_Event.Broadcast(*Value);
	}

	TCsPrimitiveType_Ref& operator=(const T& B)
	{
		*Value = B;
		UpdateIsDirty();
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
		UpdateIsDirty();
	}

	void Set(const T &inValue)
	{
		*Value  = inValue;
		UpdateIsDirty();
	}

	T Get() { return *Value; }

	void Clear()
	{
		Last_Value = *Value;
		IsDirty	   = false;
	}

	void ResetValue()
	{
		Value	   = nullptr;
		Last_Value = DefaultValue;
		IsDirty	   = false;
	}

	void Reset()
	{
		ResetValue();

		OnChange_Event.Clear();
	}

	bool IsChanged() 
	{ 
		IsDirty = *Value != Last_Value;
		return IsDirty;
	}

	bool HasChanged() { return IsDirty; }
};

struct TCsPrimitiveType_Ref_Int32 : public TCsPrimitiveType_Ref<int32>
{
	TCsPrimitiveType_Ref_Int32() {}
	~TCsPrimitiveType_Ref_Int32() {}

	FORCEINLINE friend bool operator==(const int32 &Lhs, const TCsPrimitiveType_Ref_Int32 &Rhs)
	{
		return Lhs == *(Rhs.Value);
	}

	FORCEINLINE friend bool operator==(const TCsPrimitiveType_Ref_Int32 &Lhs, const int32 &Rhs)
	{
		return *(Lhs.Value) == Rhs;
	}

	FORCEINLINE friend bool operator!=(const int32 &Lhs, const TCsPrimitiveType_Ref_Int32 &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsPrimitiveType_Ref_Int32 &Lhs, const int32 &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator<(const TCsPrimitiveType_Ref_Int32 &Lhs, const int32 &Rhs)
	{
		return (*Lhs.Value) < Rhs;
	}

	FORCEINLINE friend bool operator<(const int32 &Lhs, const TCsPrimitiveType_Ref_Int32 &Rhs)
	{
		return Lhs < (*Rhs.Value);
	}

	FORCEINLINE friend bool operator>(const TCsPrimitiveType_Ref_Int32 &Lhs, const int32 &Rhs)
	{
		return (*Lhs.Value) > Rhs;
	}

	FORCEINLINE friend bool operator>(const int32 &Lhs, const TCsPrimitiveType_Ref_Int32 &Rhs)
	{
		return Lhs > (*Rhs.Value);
	}
};

typedef TCsPrimitiveType_Ref_Int32 TCsInt32_Ref;

struct TCsPrimitiveType_Ref_Float : public TCsPrimitiveType_Ref<float>
{
	TCsPrimitiveType_Ref_Float(){}
	~TCsPrimitiveType_Ref_Float(){}

	FORCEINLINE friend bool operator==(const float &Lhs, const TCsPrimitiveType_Ref_Float &Rhs)
	{
		return Lhs == *(Rhs.Value);
	}

	FORCEINLINE friend bool operator==(const TCsPrimitiveType_Ref_Float &Lhs, const float &Rhs)
	{
		return *(Lhs.Value) == Rhs;
	}

	FORCEINLINE friend bool operator!=(const float &Lhs, const TCsPrimitiveType_Ref_Float &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsPrimitiveType_Ref_Float &Lhs, const float &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator<(const TCsPrimitiveType_Ref_Float &Lhs, const float &Rhs)
	{
		return (*Lhs.Value) < Rhs;
	}

	FORCEINLINE friend bool operator<(const float &Lhs, const TCsPrimitiveType_Ref_Float &Rhs)
	{
		return Lhs < (*Rhs.Value);
	}

	FORCEINLINE friend bool operator>(const TCsPrimitiveType_Ref_Float &Lhs, const float &Rhs)
	{
		return (*Lhs.Value) > Rhs;
	}

	FORCEINLINE friend bool operator>(const float &Lhs, const TCsPrimitiveType_Ref_Float &Rhs)
	{
		return Lhs > (*Rhs.Value);
	}
};

typedef TCsPrimitiveType_Ref_Float TCsFloat_Ref;

#pragma endregion Ref

#define CS_PRIMITIVE_TYPE_DEFAULT -1
#define CS_PRIMITIVE_TYPE_GET_DELEGATE -2

// MultiValue
#pragma region

// DON'T USE int64 for U
template<typename T, typename U = int32, uint8 SIZE = 1>
struct TCsPrimitiveType_MultiValue
{
public:
	T DefaultValue;
	T Value;
	T Last_Value;

	T Values[SIZE];
	T Last_Values[SIZE];
protected:
	bool IsDirty;

	bool IsDirtys[SIZE];
public:
	TMulticastDelegate<void, const T&> OnChange_Event;
	TMulticastDelegate<void, const U&, const T&> OnChangeEX_Event;

public:

	TCsPrimitiveType_MultiValue(){}
	virtual ~TCsPrimitiveType_MultiValue(){}

	virtual void UpdateIsDirty()
	{
		IsDirty = Value != Last_Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	virtual void UpdateIsDirtys(const int64 &Index)
	{
		IsDirtys[Index] = Values[Index] != Last_Values[Index];

		if (IsDirtys[Index])
			OnChangeEX_Event.Broadcast((U)(int32)Index, Values[Index]);
	}

	TCsPrimitiveType_MultiValue& operator=(const T& B)
	{
		Value = B;
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; I++)
		{
			Values[I] = B.Values[I];
			UpdateIsDirtys(I);
		}
		return *this;
	}

	bool operator==(const TCsPrimitiveType_MultiValue& B) const
	{
		for (uint8 I = 0; I < SIZE; I++)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B;
	}

	bool operator!=(const TCsPrimitiveType_MultiValue& B) const
	{
		return !(*this == B);
	}

	void Set(const T &inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	void Set(const U &Index, const T &inValue)
	{
		Set((int64)Index, inValue);
	}

	void Set(const int64 &Index, const T &inValue)
	{
		if (Index > CS_PRIMITIVE_TYPE_DEFAULT && Index < SIZE)
		{
			Values[Index] = inValue;
			UpdateIsDirtys(Index);
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

	void ResetValues()
	{
		Value = DefaultValue;
		Last_Value = Value;
		IsDirty = false;

		for (uint8 I = 0; I < SIZE; I++)
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

	bool HasChanged() { return IsDirty; }
	bool HasChanged(const U &Index) { return HasChanged((int64)Index); }
	bool HasChanged(const int64 &Index) { return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? IsDirty : IsDirtys[Index]; }
};

template<typename T, typename U, uint8 SIZE>
struct TCsIntegralType_MultiValue : public TCsPrimitiveType_MultiValue<T, U, SIZE>
{
	TCsIntegralType_MultiValue(){}
	~TCsIntegralType_MultiValue(){}

	void Add(const T &inValue) 
	{ 
		Value += inValue;
		UpdateIsDirty();
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
			Values[Index] += inValue;
			UpdateIsDirtys(Index);
		}
	}

	void Subtract(const T &inValue) 
	{ 
		Value -= inValue;
		UpdateIsDirty();
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
			Values[Index] -= inValue;
			UpdateIsDirtys(Index);
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
struct TCsPrimitiveType_MultiValue_bool : public TCsPrimitiveType_MultiValue<bool, U, SIZE>
{
	TCsPrimitiveType_MultiValue_bool()
	{
		DefaultValue = false;
	}
	~TCsPrimitiveType_MultiValue_bool(){}

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
struct TCsPrimitiveType_MultiValue_FString : public TCsPrimitiveType_MultiValue<FString, U, SIZE>
{
	TCsPrimitiveType_MultiValue_FString()
	{
		DefaultValue = ECsCachedString::Str::Empty;
	}
	~TCsPrimitiveType_MultiValue_FString(){}
};

#define CS_FSTRING_ENUM_TWO_PARAMS 2
#define CS_FSTRING_ENUM_THREE_PARAMS 3
#define CS_FSTRING_ENUM_DEFAULT_VALUE 0
#define CS_FSTRING_ENUM_LOWER_VALUE 1
#define CS_FSTRING_ENUM_ALT_1_VALUE 2

struct TCsPrimitiveType_MultiValue_FString_Enum_TwoParams : public TCsPrimitiveType_MultiValue_FString<int32, CS_FSTRING_ENUM_TWO_PARAMS>
{
	TCsPrimitiveType_MultiValue_FString_Enum_TwoParams()
	{
		DefaultValue = ECsCachedString::Str::Empty;
	}
	~TCsPrimitiveType_MultiValue_FString_Enum_TwoParams(){}

	TCsPrimitiveType_MultiValue_FString_Enum_TwoParams(const FString &inValue1, const FString &inValue2)
	{
		Value = inValue1;

		Values[CS_FSTRING_ENUM_DEFAULT_VALUE] = inValue1;
		Values[CS_FSTRING_ENUM_LOWER_VALUE] = inValue2;
	}

	FORCEINLINE friend bool operator==(const FString &Lhs, const TCsPrimitiveType_MultiValue_FString_Enum_TwoParams &Rhs)
	{
		const FString Lower = Lhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_TWO_PARAMS; I++)
		{
			if (Rhs.Values[I] == Lhs || Rhs.Values[I] == Lower)
				return true;
		}
		return Rhs.Value == Lhs || Rhs.Value == Lower;
	}

	FORCEINLINE friend bool operator==(const TCsPrimitiveType_MultiValue_FString_Enum_TwoParams &Lhs, const FString &Rhs)
	{
		const FString Lower = Rhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_TWO_PARAMS; I++)
		{
			if (Lhs.Values[I] == Rhs || Lhs.Values[I] == Lower)
				return true;
		}
		return Lhs.Value == Rhs || Lhs.Value == Lower;
	}

	FORCEINLINE friend bool operator!=(const FString &Lhs, const TCsPrimitiveType_MultiValue_FString_Enum_TwoParams &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsPrimitiveType_MultiValue_FString_Enum_TwoParams &Lhs, const FString &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

struct TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams : public TCsPrimitiveType_MultiValue_FString<int32, CS_FSTRING_ENUM_THREE_PARAMS>
{
	TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams()
	{
		DefaultValue = ECsCachedString::Str::Empty;
	}
	~TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams(){}

	TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams(const FString &inValue1, const FString &inValue2, const FString &inValue3)
	{
		Value = inValue1;

		Values[CS_FSTRING_ENUM_DEFAULT_VALUE] = inValue1;
		Values[CS_FSTRING_ENUM_LOWER_VALUE]   = inValue2;
		Values[CS_FSTRING_ENUM_ALT_1_VALUE]   = inValue3;
	}
	
	FORCEINLINE friend bool operator==(const FString &Lhs, const TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams &Rhs)
	{
		const FString Lower = Lhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_THREE_PARAMS; I++)
		{
			if (Rhs.Values[I] == Lhs || Rhs.Values[I] == Lower)
				return true;
		}
		return Rhs.Value == Lhs || Rhs.Value == Lower;
	}

	FORCEINLINE friend bool operator==(const TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams &Lhs, const FString &Rhs)
	{
		const FString Lower = Rhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_THREE_PARAMS; I++)
		{
			if (Lhs.Values[I] == Rhs || Lhs.Values[I] == Lower)
				return true;
		}
		return Lhs.Value == Rhs || Lhs.Value == Lower;
	}

	FORCEINLINE friend bool operator!=(const FString &Lhs, const TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams &Lhs, const FString &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

#pragma endregion MultiValue

// MultiRefValue
#pragma region

// DON'T USE int64 for U
template<typename T, typename U = int32, uint8 SIZE = 1>
struct TCsPrimitiveType_MultiRefValue
{
public:
	T DefaultValue;
	T Value;
	T Last_Value;

	T* Values[SIZE];
	T Last_Values[SIZE];
protected:
	bool IsDirty;

	bool IsDirtys[SIZE];
public:
	TMulticastDelegate<void, const T&> OnChange_Event;
	TMulticastDelegate<void, const U&, const T&> OnChangeEX_Event;

public:

	TCsPrimitiveType_MultiRefValue(){}
	virtual ~TCsPrimitiveType_MultiRefValue(){}

	virtual void UpdateIsDirty()
	{
		IsDirty = Value != Last_Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	virtual void UpdateIsDirtys(const int64 &Index)
	{
		IsDirtys[Index] = *(Values[Index]) != Last_Values[Index];

		if (IsDirtys[Index])
			OnChangeEX_Event.Broadcast((U)(int32)Index, *(Values[Index]));
	}

	TCsPrimitiveType_MultiRefValue& operator=(const T& B)
	{
		Value = B;
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; I++)
		{
			Values[I] = B.Values[I];
			UpdateIsDirtys(I);
		}
		return *this;
	}

	bool operator==(const TCsPrimitiveType_MultiRefValue& B) const
	{
		for (uint8 I = 0; I < SIZE; I++)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B;
	}

	bool operator!=(const TCsPrimitiveType_MultiRefValue& B) const
	{
		return !(*this == B);
	}

	void Set(T &inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	void Set(const U &Index, T* inValue)
	{
		Set((int64)Index, inValue);
	}

	void Set(const int64 &Index, T* inValue)
	{
		if (Index > CS_PRIMITIVE_TYPE_DEFAULT && Index < SIZE)
		{
			Values[Index] = inValue;
			UpdateIsDirtys(Index);
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

	void ResetValues()
	{
		Value = DefaultValue;
		Last_Value = Value;
		IsDirty = false;

		for (uint8 I = 0; I < SIZE; I++)
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

	bool HasChanged() { return IsDirty; }

	bool HasChanged(const U &Index) 
	{ 
		const int32 I = (int32)Index;
		return I <= CS_PRIMITIVE_TYPE_DEFAULT || I >= SIZE ? IsDirty : IsDirtys[I];
	}
};

template<typename T, typename U, uint8 SIZE>
struct TCsIntegralType_MultiRefValue : public TCsPrimitiveType_MultiRefValue<T, U, SIZE>
{
	TCsIntegralType_MultiRefValue(){}
	~TCsIntegralType_MultiRefValue(){}

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
struct TCsPrimitiveType_MultiRefValue_bool : public TCsPrimitiveType_MultiRefValue<bool, U, SIZE>
{
	TCsPrimitiveType_MultiRefValue_bool()
	{
		DefaultValue = bool;
	}
	~TCsPrimitiveType_MultiRefValue_bool(){}

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

#pragma endregion MultiRefValue

// TArrayValue
#pragma region

// DON'T USE int64 for U
template<typename T, typename U = int32>
struct TCsPrimitiveType_TArrayValue
{
public:
	T DefaultValue;
	T Value;
	T Last_Value;

	TArray<T> Values;
	TArray<T> Last_Values;

protected:
	uint8 SIZE;
	bool IsDirty;

	TArray<bool> IsDirtys;
public:
	TBaseDelegate<T, const U&> GetDelegate;
	TMulticastDelegate<void, const T&> OnChange_Event;
	TMulticastDelegate<void, const U&, const T&> OnChangeEX_Event;

public:

	TCsPrimitiveType_TArrayValue() {}
	virtual ~TCsPrimitiveType_TArrayValue() {}

	void SetDefaultValue(const T& inDefaultValue)
	{
		DefaultValue = inDefaultValue;
	}

	virtual void UpdateIsDirty()
	{
		IsDirty = Value != Last_Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	virtual void UpdateIsDirtys(const int64 &Index)
	{
		IsDirtys[Index] = Values[Index] != Last_Values[Index];

		if (IsDirtys[Index])
			OnChangeEX_Event.Broadcast((U)Index, Values[Index]);
	}

	TCsPrimitiveType_TArrayValue& operator=(const T& B)
	{
		Value = B;
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; I++)
		{
			Values[I] = B.Values[I];
			UpdateIsDirtys(I);
		}
		return *this;
	}

	bool operator==(const TCsPrimitiveType_TArrayValue& B) const
	{
		for (uint8 I = 0; I < SIZE; I++)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B;
	}

	bool operator!=(const TCsPrimitiveType_TArrayValue& B) const
	{
		return !(*this == B);
	}

	void Init(const uint8 &inSIZE)
	{
		SIZE = inSIZE;
		Values.SetNumZeroed(SIZE, true);
		Last_Values.SetNumZeroed(SIZE, true);
		IsDirtys.SetNumZeroed(SIZE, true);
	}

	void Set(const T &inValue)
	{
		Value = inValue;
		UpdateIsDirty();
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
			Values[Index] = inValue;
			UpdateIsDirtys(Index);
		}
		else
		{
			Set(inValue);
		}
	}

	T Get() { return Value; }
	T Get(const U &Index) { return Get((int64)Index); }
	T Get(const int64 &Index){ return Index <= CS_PRIMITIVE_TYPE_DEFAULT ? Value : Values[Index]; }

	T GetEX(const U &Index) { return GetDelegate.Execute(Index); }

	void Clear()
	{
		Last_Value = Value;
		IsDirty = false;

		for (uint8 I = 0; I < SIZE; I++)
		{
			Last_Values[I] = Values[I];
			IsDirtys[I] = false;
		}
	}

	void ResetValues()
	{
		Value = DefaultValue;
		Last_Value = Value;
		IsDirty = false;

		for (uint8 I = 0; I < SIZE; I++)
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
		OnChange_Event.Clear();
		OnChangeEX_Event.Clear();
	}

	bool HasChanged() { return IsDirty; }
	bool HasChanged(const U &Index) { return HasChanged((int64)Index); }
	bool HasChanged(const int64 &Index) { return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? IsDirty : IsDirtys[Index]; }
};

template<typename T, typename U>
struct TCsIntegralType_TArrayValue : public TCsPrimitiveType_TArrayValue<T, U>
{
	TCsIntegralType_TArrayValue() {}
	~TCsIntegralType_TArrayValue() {}

	void Add(const T &inValue)
	{
		Value += inValue;
		UpdateIsDirty();
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
			Values[Index] += inValue;
			UpdateIsDirtys(Index);
		}
	}

	void Subtract(const T &inValue)
	{
		Value -= inValue;
		UpdateIsDirty();
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
			Values[Index] -= inValue;
			UpdateIsDirtys(Index);
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

template<typename U>
struct TCsIntegralType_TArrayValue_uint8 : public TCsIntegralType_TArrayValue<uint8, U>
{
	TCsIntegralType_TArrayValue_uint8()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TArrayValue_uint8(){}
};

template<typename U>
struct TCsIntegralType_TArrayValue_float : public TCsIntegralType_TArrayValue<float, U>
{
	TCsIntegralType_TArrayValue_float()
	{
		DefaultValue = 0.0f;
	}
	~TCsIntegralType_TArrayValue_float() {}
};

template<typename U>
struct TCsPrimitiveType_TArrayValue_bool : public TCsPrimitiveType_TArrayValue<bool, U>
{
	TCsPrimitiveType_TArrayValue_bool() 
	{
		DefaultValue = false;
	}
	~TCsPrimitiveType_TArrayValue_bool() {}

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

#pragma endregion TArrayValue

// TArrayRefValue
#pragma region

// DON'T USE int64 for U
template<typename T, typename U = int32>
struct TCsPrimitiveType_TArrayRefValue
{
public:
	T DefaultValue;
	T Value;
	T Last_Value;

	TArray<T*> Values;
	TArray<T> Last_Values;

protected:
	uint8 SIZE;
	bool IsDirty;

	TArray<bool> IsDirtys;
public:
	TBaseDelegate<T, const U&> GetDelegate;
	TMulticastDelegate<void, const T&> OnChange_Event;
	TMulticastDelegate<void, const U&, const T&> OnChangeEX_Event;
public:

	TCsPrimitiveType_TArrayRefValue() {}
	virtual ~TCsPrimitiveType_TArrayRefValue() {}

	void SetDefaultValue(const T& inDefaultValue)
	{
		DefaultValue = inDefaultValue;
	}

	virtual void UpdateIsDirty()
	{
		IsDirty = Value != Last_Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	virtual void UpdateIsDirtys(const int64 &Index)
	{
		IsDirtys[Index] = *(Values[Index]) != Last_Values[Index];

		if (IsDirtys[Index])
			OnChangeEX_Event.Broadcast((U)Index, *(Values[Index]));
	}

	TCsPrimitiveType_TArrayRefValue& operator=(const T& B)
	{
		Value = B;
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; I++)
		{
			Values[I] = B.Values[I];
			UpdateIsDirtys(I);
		}
		return *this;
	}

	bool operator==(const TCsPrimitiveType_TArrayRefValue& B) const
	{
		for (uint8 I = 0; I < SIZE; I++)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B;
	}

	bool operator!=(const TCsPrimitiveType_TArrayRefValue& B) const
	{
		return !(*this == B);
	}

	void Init(const uint8 &inSIZE)
	{
		SIZE = inSIZE;
		Values.SetNum(SIZE, true);

		for (uint8 I = 0; I < SIZE; I++)
		{
			Values[I] = nullptr;
		}
		Last_Values.SetNumZeroed(SIZE, true);
		IsDirtys.SetNumZeroed(SIZE, true);
	}

	void Set(T &inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	void Set(const U &Index, T* inValue)
	{
		Set((int64)Index, inValue);
	}

	void Set(const int64 &Index, T* inValue)
	{
		if (Index > CS_PRIMITIVE_TYPE_DEFAULT && Index < SIZE)
		{
			Values[Index] = inValue;
			UpdateIsDirtys(Index);
		}
		else
		{
			Set(*inValue);
		}
	}

	T Get() { return Value; }
	T Get(const U &Index) { return Get((int64)Index); }
	T Get(const int64 &Index){ return Index <= CS_PRIMITIVE_TYPE_DEFAULT ? Value : *(Values[Index]); }

	T GetEX(const U &Index) { return GetDelegate.Execute(Index); }

	void Clear()
	{
		Last_Value = Value;
		IsDirty = false;

		for (uint8 I = 0; I < SIZE; I++)
		{
			Last_Values[I] = *(Values[I]);
			IsDirtys[I] = false;
		}
	}

	void ResetValues()
	{
		Value = DefaultValue;
		Last_Value = Value;
		IsDirty = false;

		for (uint8 I = 0; I < SIZE; I++)
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
		OnChangeEX_Event.Clear();
	}

	bool HasChanged() { return IsDirty; }

	bool HasChanged(const U &Index)
	{
		const int32 I = (int32)Index;
		return I <= CS_PRIMITIVE_TYPE_DEFAULT || I >= SIZE ? IsDirty : IsDirtys[I];
	}
};

template<typename T, typename U>
struct TCsIntegralType_TArrayRefValue : public TCsPrimitiveType_TArrayRefValue<T, U>
{
	TCsIntegralType_TArrayRefValue() {}
	~TCsIntegralType_TArrayRefValue() {}

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

template<typename U>
struct TCsIntegralType_TArrayRefValue_uint8 : public TCsIntegralType_TArrayRefValue<uint8, U>
{
	TCsIntegralType_TArrayRefValue_uint8() 
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TArrayRefValue_uint8() {}
};

template<typename U>
struct TCsIntegralType_TArrayRefValue_int32 : public TCsIntegralType_TArrayRefValue<int32, U>
{
	TCsIntegralType_TArrayRefValue_int32()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TArrayRefValue_int32() {}
};

template<typename U>
struct TCsIntegralType_TArrayRefValue_float : public TCsIntegralType_TArrayRefValue<float, U>
{
	TCsIntegralType_TArrayRefValue_float()
	{
		DefaultValue = 0.0f;
	}
	~TCsIntegralType_TArrayRefValue_float() {}
};

template<typename U>
struct TCsPrimitiveType_TArrayRefValue_bool : public TCsPrimitiveType_TArrayRefValue<bool, U>
{
	TCsPrimitiveType_TArrayRefValue_bool() 
	{
		DefaultValue = false;
	}
	~TCsPrimitiveType_TArrayRefValue_bool() {}

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

#pragma endregion TArrayRefValue

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
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

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