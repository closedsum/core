// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Types/CsTypes_Load.h"
#include "Containers/CsInterfaceObject.h"
#include "CsData.generated.h"

UINTERFACE(Blueprintable)
class UCsData : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsData
{
	GENERATED_IINTERFACE_BODY()

public:
	
	/**
	*
	*
	* return
	*/
	virtual const FECsDataType& GetType() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const FName& GetShortCode() const = 0;

	/**
	*
	*
	* @param LoadFlags
	* return
	*/
	virtual bool IsValid(const ECsLoadFlags& LoadFlags = ECsLoadFlags::All) = 0;

	/**
	*
	*
	* @param LoadFlags
	*/
	virtual void Load(const ECsLoadFlags& LoadFlags = ECsLoadFlags::All) = 0;

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

struct CSCORE_API FCsData : public TCsInterfaceObject<ICsData>
{
private:

	typedef TCsInterfaceObject<ICsData> Super;

public:

	static const FCsData Empty;

	// Script
#pragma region
public:

	/**
	* Delegate type for getting the Type associated with a Data.
	*  The Data implements a script interface of type: ICsData and the UClass
	*  associated with the Object have ImplementsInterface(UCsData::StaticClass()) == true.
	*
	* @param Object		Object->GetClass() that implements the interface: ICsData.
	* return Cache		The cache associated with the Pooled Object.
	*/
	DECLARE_DELEGATE_TwoParams(FScript_GetType, UObject* /*Object*/, FECsDataType& /*OutDatatType*/);

	/** Delegate for getting the Type associated with a Data.
		 The Data implements a script interface of type: ICsData. */
	FScript_GetType Script_GetType_Impl;
	
private:

	FECsDataType Internal_Script_GetType_OutDataType;

public:

	/**
	* Delegate type for getting the Short Code associated with a Data.
	*  The Short Code a unique FName associated with a Data.
	*  The Data implements a script interface of type: ICsData and the UClass
	*  associated with the Object have ImplementsInterface(UCsData::StaticClass()) == true.
	*
	* @param Object		Object->GetClass() that implements the interface: ICsData.
	* @param Payload	A "blob" of parameters to pass in when allocating a Pooled Object.
	*/
	DECLARE_DELEGATE_TwoParams(FScript_GetShortCode, UObject* /*Object*/, FName& /*OutShortCode*/);

	/** Delegate type for getting the Short Code associated with a Data.
		 The Data implements a script interface of type: ICsData and the UClass
		 associated with the Object have ImplementsInterface(UCsData::StaticClass()) == true. */
	FScript_GetShortCode Script_GetShortCode_Impl;

private:

	FName Internal_Script_GetShortCode_OutShortCode;

public:

	/**
	* Delegate type for checking whether a Data is valid for the given Load Flags.
	*  The Data implements a script interface of type: ICsData and the UClass
	*  associated with the Object have ImplementsInterface(UCsData::StaticClass()) == true.
	*
	* @param Object		Object->GetClass() that implements the interface: ICsData.
	* @param LoadFlags	Subsets of a Data to test whether they have actually loaded.
	* return			Whether the subsets of Data have successful loaded or not.
	*/
	DECLARE_DELEGATE_RetVal_TwoParams(bool /*IsValid*/, FScript_IsValid, UObject* /*Object*/, const ECsLoadFlags& /*LoadFlags*/);

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
	DECLARE_DELEGATE_TwoParams(FScript_Load, UObject* /*Object*/, const ECsLoadFlags& /*LoadFlags*/);

	/** Delegate type for loading a Data with the given Load Flags.
		 The Data implements a script interface of type: ICsData and the UClass
		 associated with the Object have ImplementsInterface(UCsData::StaticClass()) == true. */
	FScript_Load Script_Load_Impl;

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
		Script_GetType_Impl(),
		Script_GetShortCode_Impl(),
		Script_IsValid_Impl(),
		Script_Load_Impl(),
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

		Script_GetType_Impl.Unbind();
		Script_GetShortCode_Impl.Unbind();
		Script_IsValid_Impl.Unbind();
		Script_Load_Impl.Unbind();
		Script_Unload_Impl.Unbind();
		Script_IsLoaded_Impl.Unbind();
	}

#pragma endregion TCsInterfaceObject

	// ICsData
#pragma region
public:

	FORCEINLINE const FECsDataType& GetType()
	{
		if (bScript)
		{
			Script_GetType_Impl.Execute(Object, Internal_Script_GetType_OutDataType);
			return Internal_Script_GetType_OutDataType;
		}
		return Interface->GetType();
	}

	FORCEINLINE const FName& GetShortCode()
	{
		if (bScript)
		{
			Script_GetShortCode_Impl.Execute(Object, Internal_Script_GetShortCode_OutShortCode);
			return Internal_Script_GetShortCode_OutShortCode;
		}
		return Interface->GetShortCode();
	}

	FORCEINLINE bool IsValid(const ECsLoadFlags& LoadFlags = ECsLoadFlags::All)
	{
		if (bScript)
			return Script_IsValid_Impl.Execute(Object, LoadFlags);
		else
			return Interface->IsValid(LoadFlags);
	}

	FORCEINLINE void Load(const ECsLoadFlags& LoadFlags = ECsLoadFlags::All)
	{
		if (bScript)
			Script_Load_Impl.Execute(Object, LoadFlags);
		else
			Interface->Load();
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