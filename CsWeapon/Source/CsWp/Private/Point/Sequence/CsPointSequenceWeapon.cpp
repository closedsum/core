// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Sequence/CsPointSequenceWeapon.h"
#include "CsWp.h"

// Weapon
#include "CsWeapon.h"
// Update
#include "Managers/Time/CsUpdate.h"

UCsPointSequenceWeapon::UCsPointSequenceWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// FCsPointSequenceWeapon
#pragma region

const FCsPointSequenceWeapon FCsPointSequenceWeapon::Empty;

// TCsInterfaceObject
#pragma region

void FCsPointSequenceWeapon::SetInterface(ICsPointSequenceWeapon* InInterface)
{
	Super::SetInterface(InInterface);

	if (!Object)
	{
#if UE_BUILD_SHIPPING
		SetUpdate((ICsUpdate*)InInterface);
#else
		SetUpdate(dynamic_cast<ICsUpdate*>(InInterface));
#endif // #if UE_BUILD_SHIPPING
	}
}

void FCsPointSequenceWeapon::SetObject(UObject* InObject)
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
				checkf(false, TEXT("FCsProjectileWeapon:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsWeapon."), *(Object->GetName()), *(Object->GetClass()->GetName()));
			}
		}
		// ICsPointSequenceWeapon
		{
			// Interface
			if (ICsPointSequenceWeapon* O = Cast<ICsPointSequenceWeapon>(Object))
			{
				SetInterface(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsPointSequenceWeapon::StaticClass()))
			{
				SetScript();
			}
			else
			{
				checkf(false, TEXT("FCsPointSequenceWeapon:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsPointSequenceWeapon."), *(Object->GetName()), *(Object->GetClass()->GetName()));
			}
		}
		// ICsUpdate
		{
			// Interface
			if (ICsUpdate* U = Cast<ICsUpdate>(Object))
			{
				SetUpdate(U);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsUpdate::StaticClass()))
			{
				SetScriptUpdate();
			}
		}
	}
}

void FCsPointSequenceWeapon::Reset()
{
	Super::Reset();

	Weapon = nullptr;
	bScriptWeapon = false;

	_Update = nullptr;
	bScriptUpdate = false;

	Script_GetData_Impl.Unbind();
	Script_StartFire_Impl.Unbind();
	Script_StopFire_Impl.Unbind();
	Script_Update_Impl.Unbind();
}

#pragma endregion TCsInterfaceObject

// ICsUpdate
#pragma region

void FCsPointSequenceWeapon::Update(const FCsDeltaTime& DeltaTime)
{
	if (bScriptUpdate)
		Script_Update_Impl.Execute(Object, DeltaTime);
	else
		_Update->Update(DeltaTime);
}

#pragma endregion ICsUpdate

#pragma endregion FCsPointSequenceWeapon