// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Beam/CsBeamPooled.h"

#include "Managers/Beam/ICsBeam.h"

const FCsBeamPooled FCsBeamPooled::Empty;

FCsBeamPooled::FCsBeamPooled() :
	Super(),
	Beam(nullptr),
	bScriptBeam(false),
	Script_GetOwner_Impl(),
	Script_GetInstigator_Impl()
{
}

// TCsInterfaceObject
#pragma region

void FCsBeamPooled::SetInterface(ICsPooledObject* InInterface)
{
	Super::SetInterface(InInterface);

	if (!Object)
	{
#if UE_BUILD_SHIPPING
		SetBeam((ICsBeam*)InInterface);
#else
		SetBeam(dynamic_cast<ICsBeam*>(InInterface));
#endif // #if UE_BUILD_SHIPPING
	}
}

void FCsBeamPooled::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsBeam
		{
			// Interface
			if (ICsBeam* O = Cast<ICsBeam>(Object))
			{
				SetBeam(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsBeam::StaticClass()))
			{
				SetScriptBeam();
			}
			else
			{
				checkf(false, TEXT("FCsBeamPooled:SetObject: Object: %s with Class; %s does NOT implement the interface: ICsBeam."), *(Object->GetName()));
			}
		}
	}
}

void FCsBeamPooled::Reset()
{
	Super::Reset();

	Beam = nullptr;
}

#pragma endregion TCsInterfaceObject

// ICsBeam
#pragma region

UObject* FCsBeamPooled::GetOwner() const
{
	if (bScript)
		return Script_GetOwner_Impl.Execute(Object);
	return Beam->GetOwner();
}

UObject* FCsBeamPooled::GetInstigator() const
{
	if (bScript)
		return Script_GetInstigator_Impl.Execute(Object);
	return Beam->GetInstigator();
}

#pragma endregion ICsBeam

void FCsBeamPooled::SetPooledObject(const FCsPooledObject& PooledObject)
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
		checkf(Script_GetCache_Impl.IsBound(), TEXT("FCsBeam::SetPooledObject: Object: %s with Class: %s does NOT have Script_GetCache_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Allocate
		checkf(Script_Allocate_Impl.IsBound(), TEXT("FCsBeam::SetPooledObject: Object: %s with Class: %s does NOT have Script_Allocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Update
		checkf(Script_Update_Impl.IsBound(), TEXT("FCsBeam::SetPooledObject: Object: %s with Class: %s does NOT have Script_Update_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Deallocate
		checkf(Script_Deallocate_Impl.IsBound(), TEXT("FCsBeam::SetPooledObject: Object: %s with Class: %s does NOT have Script_Deallocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
	}
}