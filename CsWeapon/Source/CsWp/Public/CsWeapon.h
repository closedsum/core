// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
#include "Containers/CsInterfaceObject.h"
// Types
#include "CsMacro_Namespace.h"
#include "Types/CsTypes_Weapon.h"

#include "CsWeapon.generated.h"

UINTERFACE(Blueprintable)
class CSWP_API UCsWeapon : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// DataType (NCsWeapon::NData::IData)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)

class CSWP_API ICsWeapon
{
	GENERATED_IINTERFACE_BODY()

private:

	// Allow clearer names without name collisions
	struct _
	{
		using DataType = NCsWeapon::NData::IData;
	};

public:

	/**
	*/
	virtual UObject* GetWeaponOwner() const = 0;

	/**
	*
	*
	* return
	*/
	virtual _::DataType* GetData() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const FECsWeaponState& GetCurrentState() const = 0;
};

// FCsWeapon
#pragma region

// DataType (NCsWeapon::NData::IData)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)

struct CSWP_API FCsWeapon : public TCsInterfaceObject<ICsWeapon>
{
private:

	using Super = TCsInterfaceObject<ICsWeapon>;
	using DataType = NCsWeapon::NData::IData;

public:

	static const FCsWeapon Empty;

	// Script
#pragma region

public:

	/**
	* Delegate type for
	*
	* @param Object		Object->GetClass() that implements the interface: ICsWeapon.
	* return			.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UObject* /*WeaponOwner*/, FScript_GetWeaponOwner, UObject* /*Object*/);

	/** Delegate type for . 
		 The Data implements a script interface of type: ICsWeapon and the UClass
		 associated with the Object have ImplementsInterface(UCsWeapon::StaticClass()) == true. */
	FScript_GetWeaponOwner Script_GetWeaponOwner_Impl;

	/**
	* Delegate type for
	*
	* @param Object		Object->GetClass() that implements the interface: ICsWeapon.
	* return			.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(DataType* /*Data*/, FScript_GetData, UObject* /*Object*/);

	/** Delegate type for . 
		 The Data implements a script interface of type: ICsWeapon and the UClass
		 associated with the Object have ImplementsInterface(UCsWeapon::StaticClass()) == true. */
	FScript_GetData Script_GetData_Impl;
	
	/**
	* Delegate type for 
	*
	* @param Object		Object->GetClass() that implements the interface: ICsData.
	* return
	*/
	DECLARE_DELEGATE_RetVal_OneParam(const FECsWeaponState& /*State*/, FScript_GetCurrentState, UObject* /*Object*/);

	/** Delegate type for  */
	FScript_GetCurrentState Script_GetCurrentState_Impl;

#pragma endregion Script

public:

	FCsWeapon() :
		Super(),
		Script_GetWeaponOwner_Impl(),
		Script_GetData_Impl(),
		Script_GetCurrentState_Impl()
	{
	}

	virtual ~FCsWeapon() {}

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
		Script_GetCurrentState_Impl.Unbind();
	}

#pragma endregion TCsInterfaceObject

// ICsWeapon
#pragma region
public:

	UObject* GetWeaponOwner();

	DataType* GetData();

	const FECsWeaponState& GetCurrentState();

#pragma endregion ICsWeapon
};

#pragma endregion FCsWeapon