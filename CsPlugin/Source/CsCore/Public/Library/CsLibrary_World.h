// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UWorld;
class UObject;

class CSCORE_API FCsLibrary_World
{
public:

	static bool IsPlayInGame(UWorld* World);

	static bool IsPlayInEditor(UWorld* World);
	
	static bool IsPlayInPIE(UWorld* World);

	static bool IsPlayInEditorPreview(UWorld* World);

	static bool IsPlayInGameOrPIE(UWorld* World);

	static bool IsAnyWorldContextEditorOrEditorPreview();

	static bool IsEditorPreviewOrphaned(UObject* WorldContext);
};