// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/CsProperty.h"

template<typename ValueType>
struct TCsProperty : public ICsProperty
{
public:
	ValueType DefaultValue;
	ValueType Value;
	ValueType Last_Value;
protected:
	bool bDirty;
public:
	TMulticastDelegate<void(const ValueType&)> OnChange_Event;

public:
	TCsProperty()
	{
		bDirty = false;
		OnChange_Event.Clear();
	}
	virtual ~TCsProperty(){}

	void SetDefaultValue(const ValueType& inDefaultValue)
	{
		DefaultValue = inDefaultValue;
	}

	FORCEINLINE virtual void UpdateIsDirty()
	{
		bDirty	   = Value != Last_Value;
		Last_Value = Value;

		if (bDirty)
			OnChange_Event.Broadcast(Value);
	}

	FORCEINLINE TCsProperty& operator=(const ValueType& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE bool operator==(const ValueType& B) const
	{
		return Value == B;
	}

	FORCEINLINE bool operator!=(const ValueType& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE virtual void Set(const ValueType& inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FORCEINLINE const ValueType& Get() { return Value; }

	FORCEINLINE virtual void Clear()
	{
		bDirty	= false;
	}

	void ResetValue()
	{
		Value	   = DefaultValue;
		Last_Value = Value;
		bDirty	   = false;
	}

	void Reset()
	{
		ResetValue();

		OnChange_Event.Clear();
	}

	FORCEINLINE bool HasChanged() { return bDirty; }
	FORCEINLINE void MarkDirty() { bDirty = true; }

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();
		Clear();
	}
};

#define CS_AXES_2D 2
#define CS_AXES_3D 3
#define CS_AXIS_X 0
#define CS_AXIS_Y 1
#define CS_AXIS_Z 2
#define CS_AXES_3D_ALL 3

#define CS_AXIS_ROLL 0
#define CS_AXIS_PITCH 1
#define CS_AXIS_YAW 2