// Copyright 2019, RCT Studios and The Rogue Initiative. All Rights Reserved.

#include "UI/Interfaces/Object/CsLibrary_UIObject.h"
#include "CsCore.h"

#include "UI/Interfaces/Object/CsUIObject.h"

UCsLibrary_UIObject::UCsLibrary_UIObject(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UCsLibrary_UIObject::Show(TScriptInterface<ICsUIObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Show();
	}
}

void UCsLibrary_UIObject::Hide(TScriptInterface<ICsUIObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Hide();
	}
}

void UCsLibrary_UIObject::Enable(TScriptInterface<ICsUIObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Enable();
	}
}

void UCsLibrary_UIObject::Disable(TScriptInterface<ICsUIObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Disable();
	}
}