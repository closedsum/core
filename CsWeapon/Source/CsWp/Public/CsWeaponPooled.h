// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Pool/CsPooledObject.h"
#include "Types/CsTypes_Weapon.h"

class ICsWeapon;

// NCsWeapon::NData::IData
namespace NCsWeapon {
	namespace NData {
		struct IData; } }

struct CSWP_API FCsWeaponPooled : public FCsPooledObject
{
private:

	typedef FCsPooledObject Super;

#define DataType NCsWeapon::NData::IData

public:

	static const FCsWeaponPooled Empty;

protected:

	/** Reference to interface of type: ICsWeapon. */
	ICsWeapon* Weapon;

	/** Does the Projectile implement a script interface of type: ICsWeapon. */
	bool bScriptWeapon;

// Script
#pragma region
public:

	/**
	* Delegate type for getting the Data of type: NCsWeapon::NData::IData a Weapon is using.
	*  The Weapon implements a script interface of type: ICsWeapon.
	*
	* @param Object		A Weapon of type: ICsWeapon.
	* return Data		Data the Weapon is using.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(DataType* /*Data*/, FScript_GetData, UObject* /*Object*/);

	/** Delegate for getting the Data of type: NCsWeapon::NData::IData a Weapon of using. 
		 The Projectile implements a script interface of type: ICsProjectile. */
	FScript_GetData Script_GetData_Impl;

	/**
	* Delegate type for getting the current state of a Weapon.
	*  The Projectile implements a script interface of type: ICsWeapon.
	*
	* @param Object			A Projectile of type: ICsWeapon.
	* return CurrentState	Current state of the Weapon.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(const FECsWeaponState& /*CurrentState*/, FScript_GetCurrentState, UObject* /*Object*/);

	/** Delegate for getting the current state of a Weapon. 
		 The Weapon implements a script interface of type: ICsWeapon. */
	FScript_GetCurrentState Script_GetCurrentState_Impl;

#pragma endregion Script

public:

	FCsWeaponPooled();

	virtual ~FCsWeaponPooled() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetInterface(ICsPooledObject* InInterface) override;

	virtual void SetObject(UObject* InObject) override;

	virtual void Reset() override;

#pragma endregion TCsInterfaceObject

// ICsWeapon
#pragma region
public:

	DataType* GetData() const;

	const FECsWeaponState& GetCurrentState() const;

#pragma endregion ICsWeapon

public:

	void SetPooledObject(const FCsPooledObject& PooledObject);

	FORCEINLINE void SetScriptWeapon()
	{
		bScriptWeapon = true;
	}

	FORCEINLINE const bool& IsScriptWeapon() const 
	{
		return bScriptWeapon;
	}

	FORCEINLINE ICsWeapon* GetWeapon() const
	{
		return Weapon;
	}

	FORCEINLINE void SetWeapon(ICsWeapon* InWeapon)
	{
		Weapon = InWeapon;
	}

#undef DataType
};