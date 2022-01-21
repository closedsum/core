// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"

#include "CsWeaponOwner.generated.h"

UINTERFACE(Blueprintable)
class CSWP_API UCsWeaponOwner : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// NCsWeapon::NOwner::NEquip::NParams::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NOwner, NEquip, NParams, IParams);
// NCsWeapon::NOwner::NUnequip::NParams::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NOwner, NUnequip, NParams, IParams);

class CSWP_API ICsWeaponOwner
{
	GENERATED_IINTERFACE_BODY()

public:

#define EquipParamsType NCsWeapon::NOwner::NEquip::NParams::IParams
#define UnequipParamsType NCsWeapon::NOwner::NUnequip::NParams::IParams

	/**
	* 
	* 
	* @param Weapon
	*/
	virtual void EquipWeapon(const EquipParamsType* Params) = 0;

	/**
	* 
	* 
	* @param Weapon
	*/
	virtual void UnequipWeapon(const UnequipParamsType* Params) = 0;

#undef EquipParamsType
#undef UnequipParamsType
};