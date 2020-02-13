// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsPooledObject.h"
#include "CsCore.h"

UCsPooledObject::UCsPooledObject(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// FCsPooledObject
#pragma region

const FCsPooledObject FCsPooledObject::Empty;

// TCsInterfaceObject
#pragma region

void FCsPooledObject::SetInterface(ICsPooledObject* InInterface)
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

void FCsPooledObject::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

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
}
	
#pragma endregion TCsInterfaceObject

#pragma endregion FCsPooledObject