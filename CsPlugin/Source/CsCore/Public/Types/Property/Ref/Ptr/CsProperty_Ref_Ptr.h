// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/CsProperty.h"

#pragma once

template<typename ClassType>
struct TCsProperty_Ref_Ptr : public ICsProperty
{
public:
	ClassType** Value;
	TWeakObjectPtr<ClassType> Last_Value;
protected:
	bool IsDirty;
public:
	TMulticastDelegate<void(ClassType*)> OnChange_Event;

public:
	TCsProperty_Ref_Ptr()
	{
		Value = nullptr;
		Last_Value = nullptr;
		IsDirty = false;
		OnChange_Event.Clear();
	}
	virtual ~TCsProperty_Ref_Ptr() {}

	FORCEINLINE virtual void UpdateIsDirty()
	{
		ClassType* _Last_Value = Last_Value.IsValid() ? Last_Value.Get() : nullptr;
		IsDirty				   = *Value != _Last_Value;
		Last_Value			   = *Value;

		if (IsDirty)
			OnChange_Event.Broadcast(*Value);
	}

	FORCEINLINE TCsProperty_Ref_Ptr& operator=(ClassType* B)
	{
		*Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE bool operator==(const ClassType*& B) const
	{
		return *Value == B;
	}

	FORCEINLINE bool operator!=(const ClassType*& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(ClassType** inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Set(ClassType* inValue)
	{
		*Value = inValue;
		UpdateIsDirty();
	}

	FORCEINLINE ClassType* Get() { return *Value; }

	FORCEINLINE void Clear()
	{
		IsDirty = false;
	}

	void ResetValue()
	{
		Value = nullptr;
		Last_Value = nullptr;
		IsDirty = false;
	}

	void Reset()
	{
		ResetValue();

		OnChange_Event.Clear();
	}

	FORCEINLINE bool HasChanged() { return IsDirty; }

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();
		Clear();
	}
};