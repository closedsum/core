// Copyright 2019, RCT Studios and The Rogue Initiative. All Rights Reserved.

#include "Managers/InteractiveObject/CsLibrary_InteractiveObject.h"
#include "CsCore.h"

#include "Managers/InteractiveObject/CsInteractiveObject.h"

UCsLibrary_InteractiveObject::UCsLibrary_InteractiveObject(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UCsLibrary_InteractiveObject::Freeze(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Freeze();
	}
}

void UCsLibrary_InteractiveObject::UnFreeze(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->UnFreeze();
	}
}

void UCsLibrary_InteractiveObject::Hold(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Hold();
	}
}

void UCsLibrary_InteractiveObject::Release(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Release();
	}
}

void UCsLibrary_InteractiveObject::Touch(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Touch();
	}
}

void UCsLibrary_InteractiveObject::Hover(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Hover();
	}
}

void UCsLibrary_InteractiveObject::UnHover(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->UnHover();
	}
}

void UCsLibrary_InteractiveObject::Collide(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Collide();
	}
}

void UCsLibrary_InteractiveObject::UnCollide(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->UnCollide();
	}
}

void UCsLibrary_InteractiveObject::Remove(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Remove();
	}
}