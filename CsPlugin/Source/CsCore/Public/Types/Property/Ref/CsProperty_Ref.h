// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/CsProperty.h"

#pragma once

template<typename ValueType>
struct TCsProperty_Ref : ICsProperty
{
public:
	ValueType DefaultValue;
	ValueType* Value;
	ValueType Last_Value;
protected:
	bool bDirty;
public:
	TMulticastDelegate<void(const ValueType&)> OnChange_Event;

public:
	TCsProperty_Ref()
	{
		bDirty = false;
		OnChange_Event.Clear();
	}
	virtual ~TCsProperty_Ref() {}

	FORCEINLINE virtual void UpdateIsDirty()
	{
		bDirty = *Value != Last_Value;
		Last_Value = *Value;

		if (bDirty)
			OnChange_Event.Broadcast(*Value);
	}

	FORCEINLINE TCsProperty_Ref& operator=(const ValueType& B)
	{
		*Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE bool operator==(const ValueType& B) const
	{
		return *Value == B;
	}

	FORCEINLINE bool operator!=(const ValueType& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Init(ValueType* InValue)
	{
		Value	   = InValue;
		Last_Value = *Value;
	}

	FORCEINLINE void Set(ValueType* inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Set(const ValueType& inValue)
	{
		*Value = inValue;
		UpdateIsDirty();
	}

	FORCEINLINE const ValueType& Get() const { return *Value; }

	FORCEINLINE void Clear()
	{
		bDirty = false;
	}

	void ResetValue()
	{
		Value = nullptr;
		Last_Value = DefaultValue;
		bDirty = false;
	}

	void Reset()
	{
		ResetValue();

		OnChange_Event.Clear();
	}

	FORCEINLINE bool HasChanged() { return bDirty; }

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();
		Clear();
	}
};