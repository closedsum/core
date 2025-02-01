// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "CsWpEditor.h"

// Customization
#include "DetailCustomizations/CsWeaponRegisterDetailCustomization.h"
#include "GraphEditor/CsWeaponGraphPanelPinFactory.h"

DEFINE_LOG_CATEGORY(LogCsWpEditor);

#define LOCTEXT_NAMESPACE "FCsEditor"

void FCsWpEditor::StartupModule()
{
	FCsWeaponRegisterDetailCustomization::Register();
	FCsWeaponPanelGraphPinFactory::Register();
}

void FCsWpEditor::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_GAME_MODULE(FCsWpEditor, CsWpEditor);