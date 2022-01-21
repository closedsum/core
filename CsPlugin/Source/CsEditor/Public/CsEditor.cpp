// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "CsEditor.h"

#include "GraphEditor/CsGraphPanelPinFactory.h"

DEFINE_LOG_CATEGORY(LogCsEditor);

#define LOCTEXT_NAMESPACE "FCsEditor"

void FCsEditor::StartupModule()
{
	TSharedPtr<FCsPanelGraphPinFactory> CsPanelGraphPinFactory = MakeShareable(new FCsPanelGraphPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(CsPanelGraphPinFactory);
}

void FCsEditor::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_GAME_MODULE(FCsEditor, CsEditor);