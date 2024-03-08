// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Value/CsProperty_Value.h"
#include "Types/CsTypes_Macro.h"

struct FCsProperty_FRotator : public TCsProperty<FRotator>
{
private:
	typedef TCsProperty<FRotator> Super;

protected:
	bool bDirtys[CS_AXES_3D];

public:

	FCsProperty_FRotator() : Super()
	{
		for (bool& b : bDirtys)
		{
			b = false;
		}
		DefaultValue = FRotator::ZeroRotator;
	}
	~FCsProperty_FRotator() {}

	virtual void UpdateIsDirty() override
	{
		bDirty = Value != Last_Value;
		bDirtys[CS_AXIS_ROLL] = Value.Roll != Last_Value.Roll;
		bDirtys[CS_AXIS_PITCH] = Value.Pitch != Last_Value.Pitch;
		bDirtys[CS_AXIS_YAW] = Value.Yaw != Last_Value.Yaw;

		if (bDirty)
			OnChange_Event.Broadcast(Value);
	}

	FCsProperty_FRotator& operator=(const FRotator& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FRotator& Lhs, const FCsProperty_FRotator& Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsProperty_FRotator& Lhs, const FRotator& Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FRotator& Lhs, const FCsProperty_FRotator& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_FRotator& Lhs, const FRotator& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FCsProperty_FRotator& operator+=(const FRotator& B)
	{
		Value += B;
		UpdateIsDirty();
		return *this;
	}

	FCsProperty_FRotator& operator-=(const FRotator& B)
	{
		Value -= B;
		UpdateIsDirty();
		return *this;
	}

	virtual void Set(const FRotator& inValue) override
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FRotator GetAxes(const int32& Axes)
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
		bDirty = false;
		bDirtys[CS_AXIS_ROLL] = false;
		bDirtys[CS_AXIS_PITCH] = false;
		bDirtys[CS_AXIS_YAW] = false;
	}

	bool HasAxisChanged(const uint8& Axis)
	{
		if (!bDirty)
			return false;
		if (Axis < CS_AXIS_PITCH || Axis > CS_AXIS_ROLL)
			return true;
		return bDirtys[Axis];
	}

	bool HasAxesChanged(const int32& Axes)
	{
		if (!bDirty)
			return false;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_ROLL) & bDirtys[CS_AXIS_ROLL])
			return true;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_PITCH) & bDirtys[CS_AXIS_PITCH])
			return true;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_YAW) & bDirtys[CS_AXIS_YAW])
			return true;
		return false;
	}
};

typedef FCsProperty_FRotator TCsFRotator;