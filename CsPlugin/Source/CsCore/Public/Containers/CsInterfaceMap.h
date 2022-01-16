// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

/**
* Map of interfaces for an object. This stores the memory offsets for each "slice"
* or interface of the object.
* If storing "unique based sliced" interfaces, those interfaces do NOT route back to same
* root / top level object.
*/
struct CSCORE_API FCsInterfaceMap
{
private:

	void* Root;

	/** */
	FName RootName;

	/** */
	TMap<FName, void*> Interfaces;

	/** */
	bool bUniqueBasedSlices;

	/** */
	TMap<FName, void*> InterfacesByUniqueBasedSliceRootName;

public:

	FCsInterfaceMap() :
		Root(nullptr),
		RootName(NAME_None),
		Interfaces(),
		bUniqueBasedSlices(false),
		InterfacesByUniqueBasedSliceRootName()
	{
	}

	/**
	*
	*
	* @param InName
	*/
	template<typename RootType>
	FORCEINLINE void SetRoot(RootType* InRoot)
	{
		static_assert(!std::is_abstract<RootType>(), "FCsInterfaceMap::SetRoot: RootType IS abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, RootType>(), "FCsInterfaceMap::SetRoot: RootType is NOT a child of: ICsGetInterfaceMap.");

		Root	 = InRoot;
		RootName = RootType::Name;
	}

	template<typename RootType>
	FORCEINLINE RootType* GetRoot()
	{
		static_assert(!std::is_abstract<RootType>(), "FCsInterfaceMap::GetRoot: RootType IS abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, RootType>(), "FCsInterfaceMap::SetRoot: RootType is NOT a child of: ICsGetInterfaceMap.");

		checkf(RootName == RootType::Name, TEXT("FCsInterfaceMap::GetRoot: Root is NOT of type: %s."), *(RootType::Name.ToString()));

		return static_cast<RootType*>(Root);
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

	FORCEINLINE const TMap<FName, void*>& GetInterfaces() const { return Interfaces; }

	FORCEINLINE void SetUniqueBasedSlices()
	{
		bUniqueBasedSlices = true;
	}

	FORCEINLINE bool HasUniqueBasedSlices() const
	{
		return bUniqueBasedSlices;
	}

	/**
	*/
	FORCEINLINE bool HasUniqueBasedRootName(const FName& Name)
	{
		checkf(Name != NAME_None, TEXT("FCsInterfaceMap::HasUniqueBasedRootName: Name: None is NOT Valid."));

		return InterfacesByUniqueBasedSliceRootName.Find(Name) != nullptr;
	}

	FORCEINLINE const TMap<FName, void*>& GetInterfacesByUniqueBasedSliceRootName() const { return InterfacesByUniqueBasedSliceRootName; }

	/**
	* Add a reference to the interface or slice of the root structure.
	*
	* @param Interface	Pointer to the InterfaceType of the root structure
	*/
	template<typename InterfaceType>
	void Add(InterfaceType* Interface)
	{
		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::Add: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "FCsInterfaceMap::Add: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Root, TEXT("FCsInterfaceMap::Add: Root is NULL."));

		checkf(RootName != NAME_None, TEXT("FCsInterfaceMap::Add: RootName: None is NOT Valid."));

		checkf(Interface, TEXT("FCsInterfaceMap::Add: Interface is NULL."));

		checkf(InterfaceType::Name != NAME_None, TEXT("FCsInterfaceMap::Add: InterfaceName: None is NOT Valid."));

		Interfaces.Add(InterfaceType::Name, Interface);
	}

	/**
	* Add a reference to the interface or slice of the root structure.
	*
	* @param UniqueBasedRootName	Name of the structure that is implementing the interface.
	* @param Interface				Pointer to the InterfaceType of the root structure
	*/
	template<typename InterfaceType>
	void Add(const FName& UniqueBasedRootName, InterfaceType* Interface)
	{
		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::Add: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "FCsInterfaceMap::Add: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Root, TEXT("FCsInterfaceMap::Add: Root is NULL."));

		checkf(RootName != NAME_None, TEXT("FCsInterfaceMap::Add: RootName: None is NOT Valid."));

		checkf(bUniqueBasedSlices, TEXT("FCsInterfaceMap::Add: bUniqueBasedSlices MUST be true if adding a Unique Based Slice."));

		checkf(UniqueBasedRootName != NAME_None, TEXT("FCsInterfaceMap::Add: UniqueBasedRootName: None is NOT Valid."));

		checkf(Interface, TEXT("FCsInterfaceMap::Add: Interface is NULL."));

		checkf(InterfaceType::Name != NAME_None, TEXT("FCsInterfaceMap::Add: InterfaceName: None is NOT Valid."));

		Interfaces.Add(InterfaceType::Name, Interface);
		InterfacesByUniqueBasedSliceRootName.Add(UniqueBasedRootName, Interface);
	}

	/**
	* Get a reference to the interface or slice of the root structure.
	*
	* return	Reference to the InterfaceType
	*/
	template<typename InterfaceType>
	FORCEINLINE InterfaceType* Get()
	{
		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::Get: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "FCsInterfaceMap::Get: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(InterfaceType::Name != NAME_None, TEXT("FCsInterfaceMap::Get: InterfaceType::Name: None is NOT Valid."));

		void** Ptr = Interfaces.Find(InterfaceType::Name);

		checkf(Ptr, TEXT("FCsInterfaceMap::Get: Failed to find InterfaceType with InterfaceType::Name: %s."), *(InterfaceType::Name.ToString()));

		checkf(((InterfaceType*)(*Ptr))->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::Get: InterfaceMap for Ptr does NOT point to this."));

		return (InterfaceType*)(*Ptr);
	}

	/**
	* Get a reference to the interface or slice of the root structure.
	*
	* return	Reference to the InterfaceType
	*/
	template<typename InterfaceType>
	FORCEINLINE const InterfaceType* Get() const
	{
		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::Get: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "FCsInterfaceMap::Get: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(InterfaceType::Name != NAME_None, TEXT("FCsInterfaceMap::Get: InterfaceType::Name: None is NOT Valid."));

		void* const* Ptr = Interfaces.Find(InterfaceType::Name);

		checkf(Ptr, TEXT("FCsInterfaceMap::Get: Failed to find InterfaceType with InterfaceType::Name: %s."), *(InterfaceType::Name.ToString()));

		checkf(((const InterfaceType*)(*Ptr))->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::Get: InterfaceMap for Ptr does NOT point to this."));

		return (const InterfaceType*)(*Ptr);
	}

	/**
	* Get a reference to the interface or slice of the root structure.
	*
	* @param InterfaceName	Name of the interface structure.
	* return				Raw pointer to an interface.
	*/
	FORCEINLINE void* Get(const FName& InterfaceName)
	{
		checkf(InterfaceName != NAME_None, TEXT("FCsInterfaceMap::Get: InterfaceName: None is NOT Valid."));

		void** Ptr = Interfaces.Find(InterfaceName);

		checkf(Ptr, TEXT("FCsInterfaceMap::Get: Failed to find Interface with InterfaceName: %s."), *(InterfaceName.ToString()));

		return *Ptr;
	}

	/**
	* Safely get a reference to the interface or slice of the root structure.
	*
	* return	Reference to the InterfaceType
	*/
	template<typename InterfaceType>
	FORCEINLINE InterfaceType* GetSafe()
	{
		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::GetSafe: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "FCsInterfaceMap::GetSafe: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(InterfaceType::Name != NAME_None, TEXT("FCsInterfaceMap::GetSafe: InterfaceType::Name: None is NOT Valid."));

		void** Ptr = Interfaces.Find(InterfaceType::Name);

		if (Ptr)
		{
			checkf(((InterfaceType*)(*Ptr))->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::GetSafe: InterfaceMap for Ptr does NOT point to this."));

			return (InterfaceType*)(*Ptr);
		}
		return nullptr;
	}

	/**
	* Safely get a reference to the interface or slice of the root structure.
	*
	* return	Reference to the InterfaceType
	*/
	template<typename InterfaceType>
	FORCEINLINE const InterfaceType* GetSafe() const
	{
		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::GetSafe: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "FCsInterfaceMap::GetSafe: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(InterfaceType::Name != NAME_None, TEXT("FCsInterfaceMap::GetSafe: InterfaceType::Name: None is NOT Valid."));

		void * const* Ptr = Interfaces.Find(InterfaceType::Name);

		if (Ptr)
		{
			checkf(((const InterfaceType*)(*Ptr))->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::GetSafe: InterfaceMap for Ptr does NOT point to this."));

			return (const InterfaceType*)(*Ptr);
		}
		return nullptr;
	}

	/**
	* Check whether the object implements the interface: InterfaceType
	*
	* return Whether the objects implements the interface: InterfaceType.
	*/
	template<typename InterfaceType>
	FORCEINLINE bool Implements() const
	{
		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::Implements: InterfaceType is NOT abstract.");

		return Interfaces.Find(InterfaceType::Name) != nullptr;
	}

	/**
	* Check whether the object implements the interface with 
	* name: InterfaceName
	*
	* @param InterfaceName
	* return				Whether the objects implements the interface with the given name.
	*/
	FORCEINLINE bool Implements(const FName& InterfaceName) const
	{
		checkf(InterfaceName != NAME_None, TEXT("FCsInterfaceMap::Implements: InterfaceName: None is NOT Valid."));

		return Interfaces.Find(InterfaceName) != nullptr;
	}

	/**
	* Check whether the object implements the interface: InterfaceType
	*
	* @param Context	The calling context.
	* return			Whether the objects implements the interface: InterfaceType.
	*/
	template<typename InterfaceType>
	FORCEINLINE bool ImplementsChecked(const FString& Context) const
	{
		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::Implements: InterfaceType is NOT abstract.");

		checkf(Interfaces.Find(InterfaceType::Name) != nullptr, TEXT("%s: %s does NOT implement interface: %s."), *(RootName.ToString()), *(InterfaceType::Name.ToString()));

		return true;
	}

	/**
	* Check whether the object is of type: DerivedType.
	* 
	* return Whether the object is of type: DerivedType
	*/
	template<typename DerivedType>
	FORCEINLINE bool Is() const
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType IS abstract.");

		return bUniqueBasedSlices ? InterfacesByUniqueBasedSliceRootName.Find(DerivedType::Name) != nullptr : DerivedType::Name == RootName;
	}

	/**
	* Perform the operation static_cast<DerivedType*>(Interface) with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context.
	* @param Interface	Interface to cast from.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface)).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE DerivedType* StaticCastChecked(const FString& Context, InterfaceType* Interface)
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::StaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::StaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Interface, TEXT("%s: Interface is NULL."), *Context);

		if (bUniqueBasedSlices)
		{
			checkf(InterfacesByUniqueBasedSliceRootName.Find(DerivedType::Name), TEXT("%s: Failed to find Interface with Root Name: %s."), *Context, *(DerivedType::Name.ToString()));

			checkf((InterfaceType*)(*(InterfacesByUniqueBasedSliceRootName.Find(DerivedType::Name))) == Interface, TEXT("%s: this does NOT contain a reference to Interface of type: %s."), *Context, *(InterfaceType::Name.ToString()));

			DerivedType* DerivedPtr = static_cast<DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

			return DerivedPtr;
		}
		else
		{
			checkf(DerivedType::Name == RootName, TEXT("%s: this does NOT route to DerivedType (%s != %s)."), *Context, *(DerivedType::Name.ToString()), *(RootName.ToString()));

			checkf(Get<InterfaceType>() == Interface, TEXT("%s: this does NOT contain a reference to Interface of type: %s."), *Context, *(InterfaceType::Name.ToString()));

			DerivedType* DerivedPtr = static_cast<DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

			return DerivedPtr;
		}
	}

	/**
	* Perform the operation static_cast<DerivedType*>(Interface) with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context.
	* @param Interface	Interface to cast from.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface)).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE const DerivedType* StaticCastChecked(const FString& Context, const InterfaceType* Interface) const
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::StaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::StaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Interface, TEXT("%s: Interface is NULL."), *Context);

		if (bUniqueBasedSlices)
		{
			checkf(InterfacesByUniqueBasedSliceRootName.Find(DerivedType::Name), TEXT("%s: Failed to find Interface with Root Name: %s."), *Context, *(DerivedType::Name.ToString()));

			checkf((InterfaceType*)(*(InterfacesByUniqueBasedSliceRootName.Find(DerivedType::Name))) == Interface, TEXT("%s: this does NOT contain a reference to Interface of type: %s."), *Context, *(InterfaceType::Name.ToString()));

			const DerivedType* DerivedPtr = static_cast<const DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

			return DerivedPtr;
		}
		else
		{
			checkf(DerivedType::Name == RootName, TEXT("%s: this does NOT route to DerivedType (%s != %s)."), *Context, *(DerivedType::Name.ToString()), *(RootName.ToString()));

			checkf(Get<InterfaceType>() == Interface, TEXT("%s: this does NOT contain a reference to Interface of type: %s."), *Context, *(InterfaceType::Name.ToString()));

			const DerivedType* DerivedPtr = static_cast<const DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

			return DerivedPtr;
		}
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context.
	* return			Interface casted to DerivedType 
	*					(static_cast<DerivedType*>("Interface associated with InterfaceType")).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE DerivedType* StaticCastChecked(const FString& Context)
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::StaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::StaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		if (bUniqueBasedSlices)
		{
			void** Ptr = InterfacesByUniqueBasedSliceRootName.Find(DerivedType::Name);

			checkf(Ptr, TEXT("%s: Failed to find Interface with Root Name: %s."), *Context, *(DerivedType::Name.ToString()));

			InterfaceType* Interface = (InterfaceType*)(*Ptr);

			checkf(Interface->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for Inteface does NOT point to this."), *Context);

			DerivedType* DerivedPtr = static_cast<DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

			return DerivedPtr;
		}
		else
		{
			checkf(DerivedType::Name == RootName, TEXT("%s: this does NOT route to DerivedType (%s != %s)."), *Context, *(DerivedType::Name.ToString()), *(RootName.ToString()));

			InterfaceType* Interface = Get<InterfaceType>();
			DerivedType* DerivedPtr  = static_cast<DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

			return DerivedPtr;
		}
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context.
	* return			Interface casted to DerivedType 
	*					(static_cast<DerivedType*>("Interface associated with InterfaceType")).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE const DerivedType* StaticCastChecked(const FString& Context) const
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::StaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::StaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		if (bUniqueBasedSlices)
		{
			void* const* Ptr = InterfacesByUniqueBasedSliceRootName.Find(DerivedType::Name);

			checkf(Ptr, TEXT("%s: Failed to find Interface with Root Name: %s."), *Context, *(DerivedType::Name.ToString()));

			const InterfaceType* Interface = (const InterfaceType*)(*Ptr);

			checkf(Interface->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for Inteface does NOT point to this."), *Context);

			const DerivedType* DerivedPtr = static_cast<const DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

			return DerivedPtr;
		}
		else
		{
			checkf(DerivedType::Name == RootName, TEXT("%s: this does NOT route to DerivedType (%s != %s)."), *Context, *(DerivedType::Name.ToString()), *(RootName.ToString()));

			const InterfaceType* Interface = Get<InterfaceType>();
			const DerivedType* DerivedPtr  = static_cast<const DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

			return DerivedPtr;
		}
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks.
	* DerivedType is NOT abstract.
	*
	* return			Interface casted to DerivedType
	*					(static_cast<DerivedType*>("Interface associated with InterfaceType")).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE DerivedType* StaticCastChecked()
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::StaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "FCsInterfaceMap::StaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		if (bUniqueBasedSlices)
		{
			void** Ptr = InterfacesByUniqueBasedSliceRootName.Find(DerivedType::Name);

			checkf(Ptr, TEXT("FCsInterfaceMap::StaticCastChecked: Failed to find Interface with Root Name: %s."), *(DerivedType::Name.ToString()));

			InterfaceType* Interface = (InterfaceType*)(*Ptr);

			checkf(Interface->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::StaticCastChecked: InterfaceMap for Inteface does NOT point to this."));

			DerivedType* DerivedPtr = static_cast<DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::StaticCastChecked: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."));

			return DerivedPtr;
		}
		else
		{
			checkf(DerivedType::Name == RootName, TEXT("FCsInterfaceMap::StaticCastChecked: this does NOT route to DerivedType (%s != %s)."), *(DerivedType::Name.ToString()), *(RootName.ToString()));

			InterfaceType* Interface = Get<InterfaceType>();
			DerivedType* DerivedPtr = static_cast<DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::StaticCastChecked: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."));

			return DerivedPtr;
		}
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks.
	* DerivedType is NOT abstract.
	*
	* return			Interface casted to DerivedType
	*					(static_cast<DerivedType*>("Interface associated with InterfaceType")).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE const DerivedType* StaticCastChecked() const
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::StaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "FCsInterfaceMap::StaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		if (bUniqueBasedSlices)
		{
			void* const* Ptr = InterfacesByUniqueBasedSliceRootName.Find(DerivedType::Name);

			checkf(Ptr, TEXT("FCsInterfaceMap::StaticCastChecked: Failed to find Interface with Root Name: %s."), *(DerivedType::Name.ToString()));

			const InterfaceType* Interface = (const InterfaceType*)(*Ptr);

			checkf(Interface->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::StaticCastChecked: InterfaceMap for Inteface does NOT point to this."));

			const DerivedType* DerivedPtr = static_cast<const DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::StaticCastChecked: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."));

			return DerivedPtr;
		}
		else
		{
			checkf(DerivedType::Name == RootName, TEXT("FCsInterfaceMap::StaticCastChecked: this does NOT route to DerivedType (%s != %s)."), *(DerivedType::Name.ToString()), *(RootName.ToString()));

			const InterfaceType* Interface = Get<InterfaceType>();
			const DerivedType* DerivedPtr = static_cast<const DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::StaticCastChecked: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."));

			return DerivedPtr;
		}
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>(Interface) with checks (for InterfaceMap).
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context.
	* @param Interface	Interface to cast from.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface)).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE DerivedType* SafeStaticCastChecked(const FString& Context, InterfaceType* Interface)
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::StaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::StaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		if (bUniqueBasedSlices)
		{
			void** Ptr = InterfacesByUniqueBasedSliceRootName.Find(DerivedType::Name);

			if (!Ptr)
				return nullptr;

			checkf((InterfaceType*)(*Ptr) == Interface, TEXT("%s: this does NOT contain a reference to Interface of type: %s."), *Context, *(InterfaceType::Name.ToString()));

			DerivedType* DerivedPtr = static_cast<DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

			return DerivedPtr;
		}
		else
		{
			if (DerivedType::Name != RootName)
				return nullptr;

			checkf(Get<InterfaceType>() == Interface, TEXT("%s: this does NOT contain a reference to Interface of type: %s."), *Context, *(InterfaceType::Name.ToString()));

			DerivedType* DerivedPtr = static_cast<DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

			return DerivedPtr;
		}
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>(Interface) with checks (for InterfaceMap).
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context.
	* @param Interface	Interface to cast from.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface)).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE const DerivedType* SafeStaticCastChecked(const FString& Context, const InterfaceType* Interface) const
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::StaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::StaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		if (bUniqueBasedSlices)
		{
			void* const* Ptr = InterfacesByUniqueBasedSliceRootName.Find(DerivedType::Name);

			if (!Ptr)
				return nullptr;

			checkf((InterfaceType*)(*Ptr) == Interface, TEXT("%s: this does NOT contain a reference to Interface of type: %s."), *Context, *(InterfaceType::Name.ToString()));

			const DerivedType* DerivedPtr = static_cast<const DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

			return DerivedPtr;
		}
		else
		{
			if (DerivedType::Name != RootName)
				return nullptr;

			checkf(Get<InterfaceType>() == Interface, TEXT("%s: this does NOT contain a reference to Interface of type: %s."), *Context, *(InterfaceType::Name.ToString()));

			const DerivedType* DerivedPtr = static_cast<const DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

			return DerivedPtr;
		}
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks (for InterfaceMap).
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context.
	* return			Interface casted to DerivedType 
	*					(static_cast<DerivedType*>("Interface associated with InterfaceType")).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE DerivedType* SafeStaticCastChecked(const FString& Context)
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::StaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::StaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		if (bUniqueBasedSlices)
		{
			void** Ptr = InterfacesByUniqueBasedSliceRootName.Find(DerivedType::Name);

			if (!Ptr)
				return nullptr;

			InterfaceType* Interface = (InterfaceType*)(*Ptr);

			checkf(Interface->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for Inteface does NOT point to this."), *Context);

			DerivedType* DerivedPtr = static_cast<DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

			return DerivedPtr;
		}
		else
		{
			if (DerivedType::Name != RootName)
				return nullptr;

			InterfaceType* Interface = Get<InterfaceType>();
			DerivedType* DerivedPtr  = static_cast<DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

			return DerivedPtr;
		}
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks (for InterfaceMap).
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context.
	* return			Interface casted to DerivedType 
	*					(static_cast<DerivedType*>("Interface associated with InterfaceType")).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE const DerivedType* SafeStaticCastChecked(const FString& Context) const
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::StaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::StaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		if (bUniqueBasedSlices)
		{
			void* const* Ptr = InterfacesByUniqueBasedSliceRootName.Find(DerivedType::Name);

			if (!Ptr)
				return nullptr;

			const InterfaceType* Interface = (const InterfaceType*)(*Ptr);

			checkf(Interface->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for Inteface does NOT point to this."), *Context);

			const DerivedType* DerivedPtr = static_cast<const DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

			return DerivedPtr;
		}
		else
		{
			if (DerivedType::Name != RootName)
				return nullptr;

			const InterfaceType* Interface = Get<InterfaceType>();
			const DerivedType* DerivedPtr  = static_cast<const DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

			return DerivedPtr;
		}
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks (for InterfaceMap).
	* DerivedType is NOT abstract.
	*
	* return			Interface casted to DerivedType
	*					(static_cast<DerivedType*>("Interface associated with InterfaceType")).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE DerivedType* SafeStaticCastChecked()
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::StaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "FCsInterfaceMap::StaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		if (bUniqueBasedSlices)
		{
			void** Ptr = InterfacesByUniqueBasedSliceRootName.Find(DerivedType::Name);

			if (!Ptr)
				return nullptr;

			InterfaceType* Interface = (InterfaceType*)(*Ptr);

			checkf(Interface->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::StaticCastChecked: InterfaceMap for Inteface does NOT point to this."));

			DerivedType* DerivedPtr = static_cast<DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::StaticCastChecked: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."));

			return DerivedPtr;
		}
		else
		{
			if (DerivedType::Name != RootName)
				return nullptr;

			InterfaceType* Interface = Get<InterfaceType>();
			DerivedType* DerivedPtr = static_cast<DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::StaticCastChecked: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."));

			return DerivedPtr;
		}
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks (for InterfaceMap).
	* DerivedType is NOT abstract.
	*
	* return			Interface casted to DerivedType
	*					(static_cast<DerivedType*>("Interface associated with InterfaceType")).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE const DerivedType* SafeStaticCastChecked() const
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::StaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "FCsInterfaceMap::StaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		if (bUniqueBasedSlices)
		{
			void* const* Ptr = InterfacesByUniqueBasedSliceRootName.Find(DerivedType::Name);

			if (!Ptr)
				return nullptr;

			const InterfaceType* Interface = (const InterfaceType*)(*Ptr);

			checkf(Interface->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::StaticCastChecked: InterfaceMap for Inteface does NOT point to this."));

			const DerivedType* DerivedPtr = static_cast<const DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::StaticCastChecked: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."));

			return DerivedPtr;
		}
		else
		{
			if (DerivedType::Name != RootName)
				return nullptr;

			const InterfaceType* Interface = Get<InterfaceType>();
			const DerivedType* DerivedPtr = static_cast<const DerivedType*>(Interface);

			checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::StaticCastChecked: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."));

			return DerivedPtr;
		}
	}

	/**
	* Perform the operation static_cast<DerivedType*>(Interface) with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context.
	* @param Interface	Interface to cast from.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface)).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE DerivedType* PureStaticCastChecked(const FString& Context, InterfaceType* Interface)
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(DerivedType::Name == RootName, TEXT("%s: this does NOT route to DerivedType (%s != %s)."), *Context, *(DerivedType::Name.ToString()), *(RootName.ToString()));

		checkf(Get<InterfaceType>() == Interface, TEXT("%s: this does NOT contain a reference to Interface of type: %s."), *Context, *(InterfaceType::Name.ToString()));

		DerivedType* DerivedPtr = static_cast<DerivedType*>(Interface);

		checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

		return DerivedPtr;
	}

	/**
	* Perform the operation static_cast<DerivedType*>(Interface) with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context.
	* @param Interface	Interface to cast from.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface)).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE const DerivedType* PureStaticCastChecked(const FString& Context, const InterfaceType* Interface) const
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(DerivedType::Name == RootName, TEXT("%s: this does NOT route to DerivedType (%s != %s)."), *Context, *(DerivedType::Name.ToString()), *(RootName.ToString()));

		checkf(Get<InterfaceType>() == Interface, TEXT("%s: this does NOT contain a reference to Interface of type: %s."), *Context, *(InterfaceType::Name.ToString()));

		const DerivedType* DerivedPtr = static_cast<const DerivedType*>(Interface);

		checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

		return DerivedPtr;
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context.
	* return			Interface casted to DerivedType 
	*					(static_cast<DerivedType*>("Interface associated with InterfaceType")).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE DerivedType* PureStaticCastChecked(const FString& Context)
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(DerivedType::Name == RootName, TEXT("%s: this does NOT route to DerivedType (%s != %s)."), *Context, *(DerivedType::Name.ToString()), *(RootName.ToString()));

		InterfaceType* Interface = Get<InterfaceType>();
		DerivedType* DerivedPtr  = static_cast<DerivedType*>(Interface);

		checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

		return DerivedPtr;
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context.
	* return			Interface casted to DerivedType 
	*					(static_cast<DerivedType*>("Interface associated with InterfaceType")).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE const DerivedType* PureStaticCastChecked(const FString& Context) const
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(DerivedType::Name == RootName, TEXT("%s: this does NOT route to DerivedType (%s != %s)."), *Context, *(DerivedType::Name.ToString()), *(RootName.ToString()));

		const InterfaceType* Interface = Get<InterfaceType>();
		const DerivedType* DerivedPtr  = static_cast<const DerivedType*>(Interface);

		checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

		return DerivedPtr;
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* return			Interface casted to DerivedType
	*					(static_cast<DerivedType*>("Interface associated with InterfaceType")).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE DerivedType* PureStaticCastChecked()
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "FCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(DerivedType::Name == RootName, TEXT("FCsInterfaceMap::PureStaticCastChecked: this does NOT route to DerivedType (%s != %s)."), *(DerivedType::Name.ToString()), *(RootName.ToString()));

		InterfaceType* Interface = Get<InterfaceType>();
		DerivedType* DerivedPtr = static_cast<DerivedType*>(Interface);

		checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::PureStaticCastChecked: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."));

		return DerivedPtr;
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* return			Interface casted to DerivedType
	*					(static_cast<DerivedType*>("Interface associated with InterfaceType")).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE const DerivedType* PureStaticCastChecked() const
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "FCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(DerivedType::Name == RootName, TEXT("FCsInterfaceMap::PureStaticCastChecked: this does NOT route to DerivedType (%s != %s)."), *(DerivedType::Name.ToString()), *(RootName.ToString()));

		const InterfaceType* Interface = Get<InterfaceType>();
		const DerivedType* DerivedPtr  = static_cast<const DerivedType*>(Interface);

		checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::PureStaticCastChecked: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."));

		return DerivedPtr;
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>(Interface) with checks (for InterfaceMap).
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context.
	* @param Interface	Interface to cast from.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface)).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE DerivedType* SafePureStaticCastChecked(const FString& Context, InterfaceType* Interface)
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		if (DerivedType::Name != RootName)
			return nullptr;

		checkf(Get<InterfaceType>() == Interface, TEXT("%s: this does NOT contain a reference to Interface of type: %s."), *Context, *(InterfaceType::Name.ToString()));

		DerivedType* DerivedPtr = static_cast<DerivedType*>(Interface);

		checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

		return DerivedPtr;
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>(Interface) with checks (for InterfaceMap).
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context.
	* @param Interface	Interface to cast from.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface)).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE const DerivedType* SafePureStaticCastChecked(const FString& Context, const InterfaceType* Interface) const
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		if (DerivedType::Name != RootName)
			return nullptr;

		checkf(Get<InterfaceType>() == Interface, TEXT("%s: this does NOT contain a reference to Interface of type: %s."), *Context, *(InterfaceType::Name.ToString()));

		const DerivedType* DerivedPtr = static_cast<const DerivedType*>(Interface);

		checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

		return DerivedPtr;
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks (for InterfaceMap).
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context.
	* return			Interface casted to DerivedType 
	*					(static_cast<DerivedType*>("Interface associated with InterfaceType")).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE DerivedType* SafePureStaticCastChecked(const FString& Context)
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		if (DerivedType::Name != RootName)
			return nullptr;

		InterfaceType* Interface = Get<InterfaceType>();
		DerivedType* DerivedPtr  = static_cast<DerivedType*>(Interface);

		checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

		return DerivedPtr;
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks (for InterfaceMap).
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context.
	* return			Interface casted to DerivedType 
	*					(static_cast<DerivedType*>("Interface associated with InterfaceType")).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE const DerivedType* SafePureStaticCastChecked(const FString& Context) const
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		if (DerivedType::Name != RootName)
			return nullptr;

		const InterfaceType* Interface = Get<InterfaceType>();
		const DerivedType* DerivedPtr  = static_cast<const DerivedType*>(Interface);

		checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("%s: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."), *Context);

		return DerivedPtr;
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks (for InterfaceMap).
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* return			Interface casted to DerivedType
	*					(static_cast<DerivedType*>("Interface associated with InterfaceType")).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE DerivedType* SafePureStaticCastChecked()
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "FCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		if (DerivedType::Name != RootName)
			return nullptr;

		InterfaceType* Interface = Get<InterfaceType>();
		DerivedType* DerivedPtr = static_cast<DerivedType*>(Interface);

		checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::PureStaticCastChecked: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."));

		return DerivedPtr;
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks (for InterfaceMap).
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* return			Interface casted to DerivedType
	*					(static_cast<DerivedType*>("Interface associated with InterfaceType")).
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE const DerivedType* SafePureStaticCastChecked() const
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "FCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "FCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		if (DerivedType::Name != RootName)
			return nullptr;

		const InterfaceType* Interface = Get<InterfaceType>();
		const DerivedType* DerivedPtr  = static_cast<const DerivedType*>(Interface);

		checkf(DerivedPtr->GetInterfaceMap() == this, TEXT("FCsInterfaceMap::PureStaticCastChecked: InterfaceMap for static_cast<DerivedType*>(Interface) does NOT point to this."));

		return DerivedPtr;
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
	* @param Interface	The object that implements the interface: ICsGetInterfaceMap.
	* return			Interface Map
	*/
	template<typename InterfaceType>
	FORCEINLINE FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, InterfaceType* Interface)
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
	* @param Interface	The object that implements the interface: ICsGetInterfaceMap.
	* return			Interface Map
	*/
	template<typename InterfaceType>
	FORCEINLINE const FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, const InterfaceType* Interface)
	{
		static_assert(std::is_abstract<InterfaceType>(), "NCsInterfaceMap::GetInterfaceMapChecked: InterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::GetInterfaceMapChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Interface, TEXT("%: Interface is NULL."), *Context);

		const FCsInterfaceMap* InterfaceMap = Interface->GetInterfaceMap();

		checkf(InterfaceMap, TEXT("%s: InterfaceMap is NULL. Interface failed to propertly implement method: GetInterfaceMap for interface: ICsGetInterfaceMap."), *Context);

		checkf(Interface == InterfaceMap->Get<InterfaceType>(), TEXT("%s: InterfaceMap does NOT contain a reference to Interface."));

		return InterfaceMap;
	}

	/**
	* Get the Interface Map from an Object with checks.
	* Object should implement the interface: ICsGetInterfaceMap.
	*
	* @param Context	The calling context
	* @param Object		The object that implements the interface: ICsGetInterfaceMap.
	* return			Interface Map
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, DerivedType* Object)
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
	* Perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: ICsGetInterfaceMap.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface))
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE DerivedType* StaticCastChecked(const FString& Context, InterfaceType* Interface)
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "NCsInterfaceMap::StaticCastChecked: InterfaceType is NOT abstarct.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::StaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Interface, TEXT("%: Interface is NULL."), *Context);

		FCsInterfaceMap* InterfaceMap = GetInterfaceMapChecked<InterfaceType>(Context, Interface);

		return InterfaceMap->StaticCastChecked<DerivedType, InterfaceType>(Context, Interface);
	}
	
	/**
	* Perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: ICsGetInterfaceMap.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface))
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE const DerivedType* StaticCastChecked(const FString& Context, const InterfaceType* Interface)
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "NCsInterfaceMap::StaticCastChecked: InterfaceType is NOT abstarct.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::StaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Interface, TEXT("%: Interface is NULL."), *Context);

		const FCsInterfaceMap* InterfaceMap = GetInterfaceMapChecked<InterfaceType>(Context, Interface);

		return InterfaceMap->StaticCastChecked<DerivedType, InterfaceType>(Context, Interface);
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks (for InterfaceMap).
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: ICsGetInterfaceMap.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface))
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE DerivedType* SafeStaticCastChecked(const FString& Context, InterfaceType* Interface)
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "NCsInterfaceMap::StaticCastChecked: InterfaceType is NOT abstarct.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::StaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Interface, TEXT("%: Interface is NULL."), *Context);

		FCsInterfaceMap* InterfaceMap = GetInterfaceMapChecked<InterfaceType>(Context, Interface);

		return InterfaceMap->SafeStaticCastChecked<DerivedType, InterfaceType>(Context, Interface);
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks (for InterfaceMap).
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: ICsGetInterfaceMap.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface))
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE const DerivedType* SafeStaticCastChecked(const FString& Context, const InterfaceType* Interface)
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::StaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "NCsInterfaceMap::StaticCastChecked: InterfaceType is NOT abstarct.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::StaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Interface, TEXT("%: Interface is NULL."), *Context);

		const FCsInterfaceMap* InterfaceMap = GetInterfaceMapChecked<InterfaceType>(Context, Interface);

		return InterfaceMap->SafeStaticCastChecked<DerivedType, InterfaceType>(Context, Interface);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: ICsGetInterfaceMap.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface))
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE DerivedType* PureStaticCastChecked(const FString& Context, InterfaceType* Interface)
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "NCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT abstarct.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Interface, TEXT("%: Interface is NULL."), *Context);

		FCsInterfaceMap* InterfaceMap = GetInterfaceMapChecked<InterfaceType>(Context, Interface);

		return InterfaceMap->PureStaticCastChecked<DerivedType, InterfaceType>(Context, Interface);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: ICsGetInterfaceMap.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface))
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE const DerivedType* PureStaticCastChecked(const FString& Context, const InterfaceType* Interface)
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "NCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT abstarct.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Interface, TEXT("%: Interface is NULL."), *Context);

		const FCsInterfaceMap* InterfaceMap = GetInterfaceMapChecked<InterfaceType>(Context, Interface);

		return InterfaceMap->PureStaticCastChecked<DerivedType, InterfaceType>(Context, Interface);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks (for InterfaceMap).
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: ICsGetInterfaceMap.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface))
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE DerivedType* SafePureStaticCastChecked(const FString& Context, InterfaceType* Interface)
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "NCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT abstarct.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Interface, TEXT("%: Interface is NULL."), *Context);

		FCsInterfaceMap* InterfaceMap = GetInterfaceMapChecked<InterfaceType>(Context, Interface);

		return InterfaceMap->SafePureStaticCastChecked<DerivedType, InterfaceType>(Context, Interface);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks (for InterfaceMap).
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: ICsGetInterfaceMap.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface))
	*/
	template<typename DerivedType, typename InterfaceType>
	FORCEINLINE const DerivedType* SafePureStaticCastChecked(const FString& Context, const InterfaceType* Interface)
	{
		static_assert(!std::is_abstract<DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType IS abstract.");

		static_assert(std::is_base_of<InterfaceType, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: InterfaceType.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, DerivedType>(), "NCsInterfaceMap::PureStaticCastChecked: DerivedType is NOT a child of: ICsGetInterfaceMap.");

		static_assert(std::is_abstract<InterfaceType>(), "NCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT abstarct.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "NCsInterfaceMap::PureStaticCastChecked: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Interface, TEXT("%: Interface is NULL."), *Context);

		const FCsInterfaceMap* InterfaceMap = GetInterfaceMapChecked<InterfaceType>(Context, Interface);

		return InterfaceMap->SafePureStaticCastChecked<DerivedType, InterfaceType>(Context, Interface);
	}

	/**
	* Get another interface from Interface with checks.
	* Interface should implement the interface: ICsGetInterfaceMap
	* in order to get the appropriate memory offset (slice).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The call context
	* @param Interface	Interface that implements the interface: ICsGetInterfaceMap.
	* return
	*/
	template<typename OtherInterfaceType, typename InterfaceType>
	FORCEINLINE OtherInterfaceType* GetInterfaceChecked(const FString& Context, InterfaceType* Interface)
	{
		static_assert(std::is_abstract<OtherInterfaceType>(), "NCsInterfaceMap::GetInterfaceChecked: OtherInterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, OtherInterfaceType>(), "NCsInterfaceMap::GetInterfaceChecked: OtherInterfaceType is NOT a child of: ICsGetInterfaceMap.");

		FCsInterfaceMap* InterfaceMap = GetInterfaceMapChecked<InterfaceType>(Context, Interface);

		return InterfaceMap->Get<OtherInterfaceType>();
	}

	/**
	* Get another interface from Interface with checks.
	* Interface should implement the interface: ICsGetInterfaceMap
	* in order to get the appropriate memory offset (slice).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The call context
	* @param Interface	Interface that implements the interface: ICsGetInterfaceMap.
	* return
	*/
	template<typename OtherInterfaceType, typename InterfaceType>
	FORCEINLINE const OtherInterfaceType* GetInterfaceChecked(const FString& Context, const InterfaceType* Interface)
	{
		static_assert(std::is_abstract<OtherInterfaceType>(), "NCsInterfaceMap::GetInterfaceChecked: OtherInterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, OtherInterfaceType>(), "NCsInterfaceMap::GetInterfaceChecked: OtherInterfaceType is NOT a child of: ICsGetInterfaceMap.");

		const FCsInterfaceMap* InterfaceMap = GetInterfaceMapChecked<InterfaceType>(Context, Interface);

		return InterfaceMap->Get<OtherInterfaceType>();
	}

	/**
	* Safely get another interface from Interface with checks (for InterfaceMap).
	* Interface should implement the interface: ICsGetInterfaceMap
	* in order to get the appropriate memory offset (slice).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The call context
	* @param Interface	Interface that implements the interface: ICsGetInterfaceMap.
	* return
	*/
	template<typename OtherInterfaceType, typename InterfaceType>
	FORCEINLINE OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, InterfaceType* Interface)
	{
		static_assert(std::is_abstract<OtherInterfaceType>(), "NCsInterfaceMap::GetSafeInterfaceChecked: OtherInterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, OtherInterfaceType>(), "NCsInterfaceMap::GetSafeInterfaceChecked: OtherInterfaceType is NOT a child of: ICsGetInterfaceMap.");

		FCsInterfaceMap* InterfaceMap = GetInterfaceMapChecked<InterfaceType>(Context, Interface);

		return InterfaceMap->GetSafe<OtherInterfaceType>();
	}

	/**
	* Safely get another interface from Interface with checks (for InterfaceMap).
	* Interface should implement the interface: ICsGetInterfaceMap
	* in order to get the appropriate memory offset (slice).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The call context
	* @param Interface	Interface that implements the interface: ICsGetInterfaceMap.
	* return
	*/
	template<typename OtherInterfaceType, typename InterfaceType>
	FORCEINLINE const OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, const InterfaceType* Interface)
	{
		static_assert(std::is_abstract<OtherInterfaceType>(), "NCsInterfaceMap::GetSafeInterfaceChecked: OtherInterfaceType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, OtherInterfaceType>(), "NCsInterfaceMap::GetSafeInterfaceChecked: OtherInterfaceType is NOT a child of: ICsGetInterfaceMap.");

		const FCsInterfaceMap* InterfaceMap = GetInterfaceMapChecked<InterfaceType>(Context, Interface);

		return InterfaceMap->GetSafe<OtherInterfaceType>();
	}

	/**
	* Check whether the Interface implements the interface: OtherInterfaceType.
	*
	* @param Context	The calling context.
	* @param Interface	Interface that implements the interface: ICsGetInterfaceMap
	* return			Whether the Interface implements the interface: OtherInterfaceType.
	*/
	template<typename OtherInterfaceType, typename InterfaceType>
	FORCEINLINE bool Implements(const FString& Context, const InterfaceType* Interface)
	{
		FCsInterfaceMap* InterfaceMap = GetInterfaceMapChecked<InterfaceType>(Context, Interface);

		return InterfaceMap->Implements<OtherInterfaceType>();
	}

	/**
	* Check whether the Interface implements the interface: OtherInterfaceType.
	*
	* @param Context	The calling context.
	* @param Interface	Interface that implements the interface: ICsGetInterfaceMap
	* return			Whether the Interface implements the interface: OtherInterfaceType.
	*/
	template<typename OtherInterfaceType, typename InterfaceType>
	FORCEINLINE bool ImplementsChecked(const FString& Context, const InterfaceType* Interface)
	{
		FCsInterfaceMap* InterfaceMap = GetInterfaceMapChecked<InterfaceType>(Context, Interface);

		check(InterfaceMap->ImplementsChecked<OtherInterfaceType>(Context));

		return true;
	}

	/**
	*/
	template<typename InterfaceType>
	FORCEINLINE bool HasUniqueBasedSlices(const FString& Context, const InterfaceType* Interface)
	{
		FCsInterfaceMap* InterfaceMap = GetInterfaceMapChecked<InterfaceType>(Context, Interface);

		return InterfaceMap->HasUniqueBasedSlices();
	}
}