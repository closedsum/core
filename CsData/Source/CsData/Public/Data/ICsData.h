// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "Containers/CsInterfaceObject.h"

#include "ICsData.generated.h"

namespace NCsData
{
	struct CSDATA_API IData : public ICsGetInterfaceMap
	{
	public:

		static const FName Name;

	public:

		virtual ~IData(){}
	};
}

using CsDataType = NCsData::IData;

UINTERFACE(Blueprintable)
class CSDATA_API UCsData : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSDATA_API ICsData : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	virtual CsDataType* _getIData() const = 0;

	/**
	*
	*
	* @param LoadFlags
	* return
	*/
	virtual bool IsValid(const int32& LoadFlags) = 0;

	/**
	*
	*
	* @param LoadFlags
	*/
	virtual void Load(const int32& LoadFlags) = 0;

	virtual void TopLoad() = 0;

	/**
	*
	*
	*
	*/
	virtual void Unload() = 0;

	/**
	*
	*
	* return
	*/
	virtual bool IsLoaded() const = 0;
};

// FCsData
#pragma region

struct CSDATA_API FCsData : public TCsInterfaceObject<ICsData>
{
private:

	using Super = TCsInterfaceObject<ICsData>;

public:

	static const FCsData Empty;

	// Script
#pragma region

public:

	DECLARE_DELEGATE_RetVal_OneParam(CsDataType* /*Data*/, FScript_getIData, UObject* /*Object*/);

	FScript_getIData Script_getIData_Impl;

	/**
	* Delegate type for checking whether a Data is valid for the given Load Flags.
	*  The Data implements a script interface of type: ICsData and the UClass
	*  associated with the Object have ImplementsInterface(UCsData::StaticClass()) == true.
	*
	* @param Object		Object->GetClass() that implements the interface: ICsData.
	* @param LoadFlags	Subsets of a Data to test whether they have actually loaded.
	* return			Whether the subsets of Data have successful loaded or not.
	*/
	DECLARE_DELEGATE_RetVal_TwoParams(bool /*IsValid*/, FScript_IsValid, UObject* /*Object*/, const int32& /*LoadFlags*/);

	/** Delegate type for checking whether a Data is valid for the given Load Flags. 
		 The Data implements a script interface of type: ICsData and the UClass
		 associated with the Object have ImplementsInterface(UCsData::StaticClass()) == true. */
	FScript_IsValid Script_IsValid_Impl;
	
	/**
	* Delegate type for loading a Data with the given Load Flags.
	*  The Data implements a script interface of type: ICsData and the UClass
	*  associated with the Object have ImplementsInterface(UCsData::StaticClass()) == true.
	*
	* @param Object		Object->GetClass() that implements the interface: ICsData.
	* @param LoadFlags	Subsets of a Data to test whether they have actually loaded.
	*/
	DECLARE_DELEGATE_TwoParams(FScript_Load, UObject* /*Object*/, const int32& /*LoadFlags*/);

	/** Delegate type for loading a Data with the given Load Flags.
		 The Data implements a script interface of type: ICsData and the UClass
		 associated with the Object have ImplementsInterface(UCsData::StaticClass()) == true. */
	FScript_Load Script_Load_Impl;

	/**
	* Delegate type for "Top" loading a Data with the given Load Flags.
	*  The Data implements a script interface of type: ICsData and the UClass
	*  associated with the Object have ImplementsInterface(UCsData::StaticClass()) == true.
	*
	* @param Object		Object->GetClass() that implements the interface: ICsData.
	*/
	DECLARE_DELEGATE_OneParam(FScript_TopLoad, UObject* /*Object*/);

	/** Delegate type for "Top" loading a Data with the given Load Flags.
		 The Data implements a script interface of type: ICsData and the UClass
		 associated with the Object have ImplementsInterface(UCsData::StaticClass()) == true. */
	FScript_TopLoad Script_TopLoad_Impl;

	/**
	* Delegate type for unloading a Data.
	*  The Data implements a script interface of type: ICsData and the UClass
	*  associated with the Object have ImplementsInterface(UCsData::StaticClass()) == true.
	*
	* @param Object		Object->GetClass() that implements the interface: ICsData.
	*/
	DECLARE_DELEGATE_OneParam(FScript_Unload, UObject* /*Object*/);

	/** Delegate type for unloading a Data.
		 The Data implements a script interface of type: ICsData and the UClass
		 associated with the Object have ImplementsInterface(UCsData::StaticClass()) == true. */
	FScript_Unload Script_Unload_Impl;

	/**
	* Delegate type to determine if a Data is loaded.
	*  The Data implements a script interface of type: ICsData and the UClass
	*  associated with the Object have ImplementsInterface(UCsData::StaticClass()) == true.
	*
	* @param Object		Object->GetClass() that implements the interface: ICsData.
	* return			Whether the data is loaded or not.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(bool /*IsLoaded*/, FScript_IsLoaded, UObject* /*Object*/);

	/** Delegate type for unloading a Data.
		 The Data implements a script interface of type: ICsData and the UClass
		 associated with the Object have ImplementsInterface(UCsData::StaticClass()) == true. */
	FScript_IsLoaded Script_IsLoaded_Impl;

#pragma endregion Script

public:

	FCsData() :
		Super(),
		Script_getIData_Impl(),
		Script_IsValid_Impl(),
		Script_Load_Impl(),
		Script_TopLoad_Impl(),
		Script_Unload_Impl(),
		Script_IsLoaded_Impl()
	{
	}

	virtual ~FCsData() {}

	// TCsInterfaceObject
#pragma region
public:

	virtual void Reset() override
	{
		Super::Reset();

		Script_IsValid_Impl.Unbind();
		Script_Load_Impl.Unbind();
		Script_TopLoad_Impl.Unbind();
		Script_Unload_Impl.Unbind();
		Script_IsLoaded_Impl.Unbind();
	}

#pragma endregion TCsInterfaceObject

	// ICsData
#pragma region
public:

	FORCEINLINE CsDataType* _getIData() const
	{
		if (bScript)
			return Script_getIData_Impl.Execute(Object);
		return Interface->_getIData();
	}

	FORCEINLINE bool _IsValid(const int32& LoadFlags)
	{
		if (bScript)
			return Script_IsValid_Impl.Execute(Object, LoadFlags);
		else
			return Interface->IsValid(LoadFlags);
	}

	FORCEINLINE void Load(const int32& LoadFlags)
	{
		if (bScript)
			Script_Load_Impl.Execute(Object, LoadFlags);
		else
			Interface->Load(LoadFlags);
	}

	FORCEINLINE void TopLoad()
	{
		if (bScript)
			Script_TopLoad_Impl.Execute(Object);
		else
			Interface->TopLoad();
	}

	FORCEINLINE void Unload()
	{
		if (bScript)
			Script_Unload_Impl.Execute(Object);
		else
			Interface->Unload();
	}

	FORCEINLINE bool IsLoaded()
	{
		if (bScript)
			return Script_IsLoaded_Impl.Execute(Object);
		else
			return Interface->IsLoaded();
	}

#pragma endregion ICsData
};

#pragma endregion FCsData