// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "UObject/NameTypes.h"

#pragma once

struct CSCORE_API FCsInterfaceMap
{
private:

	/** */
	FName RootName;

	/** */
	TMap<FName, void*> Interfaces;

public:

	FCsInterfaceMap() :
		RootName(NAME_None),
		Interfaces()
	{
	}

	FORCEINLINE void SetRootName(const FName& InName)
	{
		RootName = InName;
	}

	FORCEINLINE const FName& GetRootName() const
	{
		return RootName;
	}

	/**
	*
	*
	* @param Interface
	*/
	template<typename InterfaceType>
	void Add(InterfaceType* Interface)
	{
		checkf(Interface, TEXT("FCsInterfaceMap::Add: Interface is NULL."));

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::Add: InterfaceType MUST be abstract.");

		checkf(InterfaceType::Name != NAME_None, TEXT("FCsInterfaceMap::Add: InterfaceName: None is NOT Valid."));

		Interfaces.Add(InterfaceType::Name, Interface);
	}

	/**
	*
	*
	* return
	*/
	template<typename InterfaceType>
	InterfaceType* Get()
	{
		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::Get: InterfaceType MUST be abstract.");

		checkf(InterfaceType::Name != NAME_None, TEXT("FCsInterfaceMap::Get: InterfaceType::Name None is NOT Valid."));

#if WITH_EDITOR
		void** Ptr = Interfaces.Find(InterfaceType::Name);

		checkf(Ptr, TEXT("FCsInterfaceMap::Get: Failed to find InterfaceType with InterfaceType::Name: %s."), *(InterfaceType::Name.ToString()));

		return (InterfaceType*)(*Ptr);
#else
		return (InterfaceType*)Interfaces[InterfaceType::Name];
#endif // #if WITH_EDITOR
	}

	/**
	* Check whether the object implements the interface with 
	* name: InterfaceName
	*
	* @param InterfaceName
	* return Whether the objects implements the interface with the given name.
	*/
	bool Implements(const FName& InterfaceName)
	{
		return Interfaces.Find(InterfaceName) != nullptr;
	}
};