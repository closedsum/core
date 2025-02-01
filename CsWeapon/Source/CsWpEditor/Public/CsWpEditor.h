// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Editor/EditorEngine.h"
#include "Editor/UnrealEdEngine.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCsWpEditor, Log, All);

class CSWPEDITOR_API FCsWpEditor : public IModuleInterface
{
public:

	/* This will get called when the editor loads the module */
	virtual void StartupModule() override;

	/* This will get called when the editor unloads the module */
	virtual void ShutdownModule() override;
};