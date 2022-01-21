// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Value/CsProperty_Value.h"

#pragma once

struct FCsProperty_FVector2D : public TCsProperty<FVector2D>
{
private:
	typedef TCsProperty<FVector2D> Super;

protected:
	bool bDirtys[CS_AXES_2D];

public:

	FCsProperty_FVector2D() : Super()
	{
		for (bool& b : bDirtys)
		{
			b = false;
		}
		DefaultValue = FVector2D::ZeroVector;
	}
	~FCsProperty_FVector2D() {}

	virtual void UpdateIsDirty() override
	{
		bDirty = Value != Last_Value;
		bDirtys[CS_AXIS_X] = Value.X != Last_Value.X;
		bDirtys[CS_AXIS_Y] = Value.Y != Last_Value.Y;

		if (bDirty)
			OnChange_Event.Broadcast(Value);
	}

	FCsProperty_FVector2D& operator=(const FVector2D& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FVector2D& Lhs, const FCsProperty_FVector2D& Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsProperty_FVector2D& Lhs, const FVector2D& Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FVector2D& Lhs, const FCsProperty_FVector2D& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_FVector2D& Lhs, const FVector2D& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend FVector2D operator-(const FVector2D& Lhs, const FCsProperty_FVector2D& Rhs)
	{
		return Lhs - Rhs.Value;
	}

	FORCEINLINE friend FVector2D operator-(const FCsProperty_FVector2D& Lhs, const FVector2D& Rhs)
	{
		return Lhs.Value - Rhs;
	}

	FCsProperty_FVector2D& operator+=(const FVector2D& B)
	{
		Value += B;
		UpdateIsDirty();
		return *this;
	}

	FCsProperty_FVector2D& operator-=(const FVector2D& B)
	{
		Value -= B;
		UpdateIsDirty();
		return *this;
	}

	FCsProperty_FVector2D& operator*=(const FVector2D& B)
	{
		Value *= B;
		UpdateIsDirty();
		return *this;
	}

	virtual void Set(const FVector2D& inValue) override
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FVector2D GetAxes(const int32& Axes)
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
		bDirty = false;
		bDirtys[CS_AXIS_X] = false;
		bDirtys[CS_AXIS_Y] = false;
	}

	bool HasAxisChanged(const uint8& Axis)
	{
		if (!bDirty)
			return false;
		if (Axis < CS_AXIS_X || Axis > CS_AXIS_Y)
			return true;
		return bDirtys[Axis];
	}

	bool HasAxesChanged(const int32& Axes)
	{
		if (!bDirty)
			return false;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_X) & bDirtys[CS_AXIS_X])
			return true;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Y) & bDirtys[CS_AXIS_Y])
			return true;
		return false;
	}
};

typedef FCsProperty_FVector2D TCsFVector2D;