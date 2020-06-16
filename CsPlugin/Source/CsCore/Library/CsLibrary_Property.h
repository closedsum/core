// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"

class CSCORE_API FCsLibrary_Property
{
public:

	/**
	*/
	template<typename T>
	static T* FindPropertyByNameForInterfaceChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName, const FString& InterfaceName)
	{
		T* Property = Cast<T>(Struct->FindPropertyByName(PropertyName));
		Property	= Property ? Property : Cast<T>(Struct->CustomFindProperty(PropertyName));

		checkf(Property, TEXT("%s: Failed to find Propery: %s when emulating interface: %s."), *Context, *(PropertyName.ToString()), *InterfaceName);

		return Property;
	}
};