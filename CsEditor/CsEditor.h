// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine.h"
#include "Editor/EditorEngine.h"
#include "Editor/UnrealEdEngine.h"
#include "ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCsEditor, Log, All);

class FCsEditor : public IModuleInterface
{
public:

	/* This will get called when the editor loads the module */
	virtual void StartupModule() override;

	/* This will get called when the editor unloads the module */
	virtual void ShutdownModule() override;
};