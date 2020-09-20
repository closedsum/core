// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsInterfaceObject.h"
// Types
#include "CsTypes_Weapon.h"
#include "CsWeapon.generated.h"

UINTERFACE(Blueprintable)
class CSWP_API UCsWeapon : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsData_Weapon;

class CSWP_API ICsWeapon
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual ICsData_Weapon* GetData() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const FECsWeaponState& GetCurrentState() const = 0;
};

// FCsWeapon
#pragma region

struct CSWP_API FCsWeapon : public TCsInterfaceObject<ICsWeapon>
{
private:

	typedef TCsInterfaceObject<ICsWeapon> Super;

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
	DECLARE_DELEGATE_RetVal_OneParam(ICsData_Weapon* /*Data*/, FScript_GetData, UObject* /*Object*/);

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

	ICsData_Weapon* GetData();

	const FECsWeaponState& GetCurrentState();

#pragma endregion ICsWeapon
};

#pragma endregion FCsWeapon