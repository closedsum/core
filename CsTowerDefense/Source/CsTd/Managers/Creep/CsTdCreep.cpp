// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Creep/CsTdCreep.h"
#include "CsTd.h"

UCsTdCreep::UCsTdCreep(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FCsTdCreep FCsTdCreep::Empty;

// FCsTdCreepPooled
#pragma region

const FCsTdCreepPooled FCsTdCreepPooled::Empty;

// TCsInterfaceObject
#pragma region

void FCsTdCreepPooled::SetInterface(ICsPooledObject* InInterface)
{
	Super::SetInterface(InInterface);

	/*
	if (!Object)
	{
#if UE_BUILD_SHIPPING
		SetUpdate((ICsUpdate*)InInterface);
#else
		SetUpdate(dynamic_cast<ICsUpdate*>(InInterface));
#endif // #if UE_BUILD_SHIPPING
	}
	*/
}

void FCsTdCreepPooled::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	/*
	if (Object)
	{
		UClass* Class = Object->GetClass();

		// ICsPooledObject
		{
			// Interface
			if (ICsPooledObject* O = Cast<ICsPooledObject>(Object))
			{
				SetInterface(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
			{
				SetScript();
			}
			else
			{
				checkf(false, TEXT("FCsPooledObject:SetObject: Object: %s with Class; %s does NOT implement the interface: ICsPooledObject."), *(Object->GetName()));
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
	*/
}
	
#pragma endregion TCsInterfaceObject

#pragma endregion FCsTdCreepPooled