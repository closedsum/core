// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Value/CsProperty_Value.h"

#pragma once

struct FCsProperty_FVector : public TCsProperty<FVector3d>
{
private:
	typedef TCsProperty<FVector3d> Super;

protected:
	bool bDirtys[CS_AXES_3D];

public:

	FCsProperty_FVector() : Super()
	{
		for (bool& b : bDirtys)
		{
			b = false;
		}
		DefaultValue = FVector3d::ZeroVector;
	}
	~FCsProperty_FVector(){}

	virtual void UpdateIsDirty() override
	{
		bDirty = Value != Last_Value;
		bDirtys[CS_AXIS_X] = Value.X != Last_Value.X;
		bDirtys[CS_AXIS_Y] = Value.Y != Last_Value.Y;
		bDirtys[CS_AXIS_Z] = Value.Z != Last_Value.Z;

		if (bDirty)
			OnChange_Event.Broadcast(Value);
	}

	FCsProperty_FVector& operator=(const FVector3d& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FVector3d& Lhs, const FCsProperty_FVector& Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsProperty_FVector& Lhs, const FVector3d& Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FVector3d& Lhs, const FCsProperty_FVector& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_FVector& Lhs, const FVector3d& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FCsProperty_FVector& operator+=(const FVector3d& B)
	{
		Value += B;
		UpdateIsDirty();
		return *this;
	}

	FCsProperty_FVector& operator-=(const FVector3d& B)
	{
		Value -= B;
		UpdateIsDirty();
		return *this;
	}

	FCsProperty_FVector& operator*=(const FVector3d& B)
	{
		Value *= B;
		UpdateIsDirty();
		return *this;
	}

	virtual void Set(const FVector3d& inValue) override 
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FVector3d GetAxes(const int32& Axes)
	{
		FVector3d V = FVector3d::ZeroVector;

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
		bDirty = false;
		bDirtys[CS_AXIS_X] = false;
		bDirtys[CS_AXIS_Y] = false;
		bDirtys[CS_AXIS_Z] = false;
	}

	bool HasAxisChanged(const uint8& Axis)
	{
		if (!bDirty)
			return false;
		if (Axis < CS_AXIS_X || Axis > CS_AXIS_Z)
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
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Z) & bDirtys[CS_AXIS_Z])
			return true;
		return false;
	}
};

typedef FCsProperty_FVector TCsFVector;