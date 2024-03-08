// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "CsWeaponPooled.h"
#include "CsWp.h"

#include "CsWeapon.h"

const FCsWeaponPooled FCsWeaponPooled::Empty;

// TCsInterfaceObject
#pragma region

FCsWeaponPooled::FCsWeaponPooled() :
	Super(),
	Weapon(nullptr),
	bScriptWeapon(false),
	Script_GetData_Impl(),
	Script_GetCurrentState_Impl()
{
}

void FCsWeaponPooled::SetInterface(ICsPooledObject* InInterface)
{
	Super::SetInterface(InInterface);

	if (!Object)
	{
#if UE_BUILD_SHIPPING
		SetWeapon((ICsWeapon*)InInterface);
#else
		SetWeapon(dynamic_cast<ICsWeapon*>(InInterface));
#endif // #if UE_BUILD_SHIPPING
	}
}

void FCsWeaponPooled::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsWeapon
		{
			// Interface
			if (ICsWeapon* O = Cast<ICsWeapon>(Object))
			{
				SetWeapon(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsWeapon::StaticClass()))
			{
				SetScriptWeapon();
			}
			else
			{
				checkf(false, TEXT("FCsWeaponPooled:SetObject: Object: %s with Class; %s does NOT implement the interface: ICsWeapon."), *(Object->GetName()));
			}
		}
	}
}

void FCsWeaponPooled::Reset()
{
	Super::Reset();

	Weapon = nullptr;
	bScriptWeapon = false;

	Script_GetData_Impl.Unbind();
	Script_GetCurrentState_Impl.Unbind();
}

#pragma endregion TCsInterfaceObject

// ICsWeapon
#pragma region

#define DataType NCsWeapon::NData::IData
DataType* FCsWeaponPooled::GetData() const
{
#undef DataType
	if (bScript)
		return Script_GetData_Impl.Execute(Object);
	return Weapon->GetData();
}

const FECsWeaponState& FCsWeaponPooled::GetCurrentState() const
{
	if (bScript)
		return Script_GetCurrentState_Impl.Execute(Object);
	return Weapon->GetCurrentState();
}

#pragma endregion ICsWeapon

void FCsWeaponPooled::SetPooledObject(const FCsPooledObject& PooledObject)
{
	SetInterface(PooledObject.GetInterface());
	SetObject(PooledObject.GetObject());

	if (PooledObject.IsScript())
		SetScript();

	Script_GetCache_Impl = PooledObject.Script_GetCache_Impl;
	Script_Allocate_Impl = PooledObject.Script_Allocate_Impl;
	Script_Update_Impl = PooledObject.Script_Update_Impl;
	Script_Deallocate_Impl = PooledObject.Script_Deallocate_Impl;

	if (bScript)
	{
		// GetCache
		checkf(Script_GetCache_Impl.IsBound(), TEXT("FCsWeaponPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_GetCache_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Allocate
		checkf(Script_Allocate_Impl.IsBound(), TEXT("FCsWeaponPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Allocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Update
		checkf(Script_Update_Impl.IsBound(), TEXT("FCsWeaponPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Update_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Deallocate
		checkf(Script_Deallocate_Impl.IsBound(), TEXT("FCsWeaponPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Deallocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
	}
}