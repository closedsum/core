// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "UObject/NameTypes.h"

#pragma once

struct CSCORE_API FCsInterfaceMap
{
private:

	TMap<FName, void*> Interfaces;

public:

	FCsInterfaceMap() :
		Interfaces()
	{
	}

	template<typename InterfaceType>
	void Add(InterfaceType* Interface)
	{
		checkf(Interface, TEXT("FCsInterfaceMap::Add: Interface is NULL."));

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::Add: InterfaceType MUST be abstract.");

		Interfaces.Add(InterfaceType::Name, Interface);
	}

	template<typename InterfaceType>
	InterfaceType* Get()
	{
		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::Get: InterfaceType MUST be abstract.");

#if WITH_EDITOR
		void* Ptr = Interfaces.Find(InterfaceType::Name);

		checkf(Ptr, TEXT("FCsInterfaceMap::Get: Failed to find InterfaceType with Name: %s."), *(InterfaceType::Name.ToString()));

		return (InterfaceType*)Ptr;
#else
		return (InterfaceType*)Interfaces[InterfaceType::Name];
#endif // #if WITH_EDITOR
	}
};

struct CSCORE_API ICsGetInterfaceMap
{
	virtual ~ICsGetInterfaceMap() {}

	virtual FCsInterfaceMap* GetInterfaceMap() = 0;
};