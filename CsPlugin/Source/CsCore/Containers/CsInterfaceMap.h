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
	void Add(const FName& Name, InterfaceType* Interface)
	{
		Interfaces.Add(Name, Interface);
	}

	template<typename InterfaceType>
	InterfaceType* Get()
	{
		return (InterfaceType*)Interfaces[InterfaceType::Name];
	}
};

struct CSCORE_API ICsGetInterfaceMap
{
	virtual ~ICsGetInterfaceMap() {}

	virtual FCsInterfaceMap* GetInterfaceMap() = 0;
};