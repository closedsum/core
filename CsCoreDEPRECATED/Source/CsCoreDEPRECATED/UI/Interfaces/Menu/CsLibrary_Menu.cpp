// Copyright 2019, RCT Studios and The Rogue Initiative. All Rights Reserved.

#include "UI/Interfaces/Menu/CsLibrary_Menu.h"
#include "CsCoreDEPRECATED.h"

#include "UI/Interfaces/Menu/CsMenu.h"

UCsLibrary_Menu::UCsLibrary_Menu(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UCsLibrary_Menu::Open(TScriptInterface<ICsMenu>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Open();
	}
}

bool UCsLibrary_Menu::IsOpened(TScriptInterface<ICsMenu>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		return Target->IsOpened();
	}
	return false;
}

void UCsLibrary_Menu::Close(TScriptInterface<ICsMenu>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Close();
	}
}

bool UCsLibrary_Menu::IsClosed(TScriptInterface<ICsMenu>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		return Target->IsClosed();
	}
	return false;
}