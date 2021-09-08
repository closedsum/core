// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"
#include "Containers/CsInterfaceObject.h"
// Types
#include "Types/CsTypes_Macro.h"

#include "CsBeam.generated.h"

UINTERFACE(Blueprintable)
class CSBEAM_API UCsBeam : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// NCsBeam::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsBeam, NData, IData)

class CSBEAM_API ICsBeam
{
	GENERATED_IINTERFACE_BODY()

#define DataType NCsBeam::NData::IData

public:

	/**
	* The Data the beam is currently using.
	*
	* return Data that implements the interface: DataType (NCsBeam::NData::IData).
	*/
	virtual DataType* GetData() const = 0;

	/**
	* The object that "owns" the beam.
	*
	* return Owner of the beam.
	*/
	virtual UObject* GetOwner() const = 0;

	/**
	* The object that started the process of launching / activating the beam.
	*
	* return Instigator of the beam.
	*/
	virtual UObject* GetInstigator() const = 0;

#undef DataType
};


// FCsBeam
#pragma region

// NCsBeam::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsBeam, NData, IData)

struct CSBEAM_API FCsBeam : public TCsInterfaceObject<ICsBeam>
{
private:

	typedef TCsInterfaceObject<ICsBeam> Super;

#define DataType NCsBeam::NData::IData

public:

	static const FCsBeam Empty;

	// Script
#pragma region

public:

	/**
	* Delegate type for
	*
	* @param Object		Object->GetClass() that implements the interface: ICsBeam.
	* return			.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(DataType* /*Data*/, FScript_GetData, UObject* /*Object*/);

	/** Delegate type for . 
		 The Data implements a script interface of type: ICsWeapon and the UClass
		 associated with the Object have ImplementsInterface(UCsBeam::StaticClass()) == true. */
	FScript_GetData Script_GetData_Impl;
	
	/**
	* Delegate type for 
	*
	* @param Object		Object->GetClass() that implements the interface: ICsData.
	* return
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UObject* /*Owner*/, FScript_GetOwner, UObject* /*Object*/);

	/** Delegate type for  */
	FScript_GetOwner Script_GetOwner_Impl;

	/**
	* Delegate type for
	*
	* @param Object		Object->GetClass() that implements the interface: ICsData.
	* return
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UObject* /*Owner*/, FScript_GetInstigator, UObject* /*Object*/);

	/** Delegate type for  */
	FScript_GetInstigator Script_GetInstigator_Impl;

#pragma endregion Script

public:

	FCsBeam() :
		Super(),
		Script_GetData_Impl(),
		Script_GetOwner_Impl(),
		Script_GetInstigator_Impl()
	{
	}

	virtual ~FCsBeam() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetObject(UObject* InObject) override;

#pragma endregion TCsInterfaceObject

// TCsInterfaceObject
#pragma region
public:

	virtual void Reset() override
	{
		Super::Reset();

		Script_GetData_Impl.Unbind();
		Script_GetOwner_Impl.Unbind();
		Script_GetInstigator_Impl.Unbind();
	}

#pragma endregion TCsInterfaceObject

// ICsBeam
#pragma region
public:

	DataType* GetData()
	{
		if (bScript)
			return Script_GetData_Impl.Execute(Object);
		return Interface->GetData();
	}

	UObject* GetOwner();

	UObject* GetInstigator();

#pragma endregion ICsBeam

#undef DataType
};

#pragma endregion FCsBeam