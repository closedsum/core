// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "UObject/NameTypes.h"

#pragma once

/**
*
*/
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

	/**
	*
	*
	* @param InName
	*/
	FORCEINLINE void SetRootName(const FName& InName)
	{
		RootName = InName;
	}

	/**
	*
	*
	* return
	*/
	FORCEINLINE const FName& GetRootName() const
	{
		return RootName;
	}

	/**
	* Add a reference to the interface or slice of the root structure.
	*
	* @param Interface	Pointer to the InterfaceType of the root structure
	*/
	template<typename InterfaceType>
	void Add(InterfaceType* Interface)
	{
		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::Add: InterfaceType MUST be abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "FCsInterfaceMap::Add: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Interface, TEXT("FCsInterfaceMap::Add: Interface is NULL."));

		checkf(InterfaceType::Name != NAME_None, TEXT("FCsInterfaceMap::Add: InterfaceName: None is NOT Valid."));

		Interfaces.Add(InterfaceType::Name, Interface);
	}

	/**
	* Get a reference to the interface or slice of the root structure.
	*
	* return	Reference to the InterfaceType
	*/
	template<typename InterfaceType>
	InterfaceType* Get()
	{
		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::Get: InterfaceType MUST be abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "FCsInterfaceMap::Get: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(InterfaceType::Name != NAME_None, TEXT("FCsInterfaceMap::Get: InterfaceType::Name None is NOT Valid."));

		void** Ptr = Interfaces.Find(InterfaceType::Name);

		checkf(Ptr, TEXT("FCsInterfaceMap::Get: Failed to find InterfaceType with InterfaceType::Name: %s."), *(InterfaceType::Name.ToString()));

		return (InterfaceType*)(*Ptr);
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

/**
*
*/
namespace NCsInterfaceMap
{
	/**
	* Get the Interface Map from an Object with checks.
	* Object should implement the interface: ICsGetInterfaceMap.
	*
	* @param Context	The calling context
	* @param Object		The object to get the interface map from
	* return			Interface Map
	*/
	template<typename InterfaceType>
	FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, InterfaceType* Interface)
	{
		static_assert(std::is_abstract<InterfaceType>(), "NCsInterfaceMap::GetInterfaceMapChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::GetInterfaceMapChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Interface, TEXT("%: Interface is NULL."), *Context);

		FCsInterfaceMap* InterfaceMap = Interface->GetInterfaceMap();

		checkf(InterfaceMap, TEXT("%s: InterfaceMap is NULL. Interface failed to propertly implement method: GetInterfaceMap for interface: ICsGetInterfaceMap."), *Context);

		checkf(Interface == InterfaceMap->Get<InterfaceType>(), TEXT("%s: InterfaceMap does NOT contain a reference to Interface."));

		return InterfaceMap;
	}

	/**
	* Get the Interface Map from an Object with checks.
	* Object should implement the interface: ICsGetInterfaceMap.
	*
	* @param Context	The calling context
	* @param Object		The object to get the interface map from
	* return			Interface Map
	*/
	template<typename DerivedType, typename InterfaceType>
	FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, DerivedType* Object)
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::GetInterfaceMapChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::GetInterfaceMapChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "NCsInterfaceMap::GetInterfaceMapChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::GetInterfaceMapChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Object, TEXT("%: Object is NULL."), *Context);

		FCsInterfaceMap* InterfaceMap = Object->GetInterfaceMap();

		checkf(InterfaceMap, TEXT("%s: InterfaceMap is NULL. Object failed to propertly implement method: GetInterfaceMap for interface: ICsGetInterfaceMap."), *Context);

		return InterfaceMap;
	}

	/**
	*
	*
	* @param Context	The calling context
	* @param Interface
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface))
	*/
	template<typename DerivedType, typename InterfaceType>
	DerivedType* StaticCastChecked(const FString& Context, InterfaceType* Interface)
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "NCsInterfaceMap::StaticCastChecked: InterfaceType is NOT abstarct.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::StaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Interface, TEXT("%: Interface is NULL."), *Context);

		DerivedType* Ptr = static_cast<DerivedType*>(Interface);

#if !UE_BUILD_SHIPPING
		FCsInterfaceMap* InterfaceMap1 = GetInterfaceMapChecked<InterfaceType>(Context, Interface);
		FCsInterfaceMap* InterfaceMap2 = GetInterfaceMapChecked<DerivedType, InterfaceType>(Context, Ptr);

		checkf(InterfaceMap1->GetRootName() == DerivedType::Name, TEXT("%s: InterfaceMap for Interface does NOT route to DerivedType."), *Context);
		checkf(InterfaceMap2->GetRootName() == DerivedType::Name, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT route to DerivedType."), *Context);

		checkf(InterfaceMap1 == InterfaceMap2, TEXT("%s: InterfaceMaps do NOT match between Interface and the result of static_cast<DerivedType*>(Interface)."), *Context);

		checkf(Interface == InterfaceMap2->Get<InterfaceType>(), TEXT("%s: InterfaceMap from static_cast<DerivedType*>(Interface) does NOT reference Interface."), *Context);
#endif // #if !UE_BUILD_SHIPPING

		return Ptr;
	}
	
	/**
	* Get another interface from Interface with checks.
	* Interface should implement the interface: ICsGetInterfaceMap
	* in order to get the appropriate memory offset (slice).
	*
	* @param Context	The call context
	* @param Interface
	* return
	*/
	template<typename OtherInterfaceType, typename InterfaceType>
	OtherInterfaceType* GetInterfaceChecked(const FString& Context, InterfaceType* Interface)
	{
		static_assert(std::is_abstract<OtherInterfaceType>(), "NCsInterfaceMap::GetInterfaceChecked: OtherInterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, OtherInterfaceType>(), "NCsInterfaceMap::GetInterfaceChecked: OtherInterfaceType is NOT a child of: ICsGetInterfaceMap.");

		FCsInterfaceMap* InterfaceMap = GetInterfaceMapChecked<InterfaceType>(Context, Interface);

		return InterfaceMap->Get<OtherInterfaceType>();
	}
}