// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Editor/UnrealEdEngine.h"
#include "CsEdEngine.generated.h"

UCLASS()
class CSEDITOR_API UCsEdEngine : public UUnrealEdEngine
{
public:
	GENERATED_BODY()

	virtual void Init(IEngineLoop* InEngineLoop) override;

	// Begin FExec Interface
	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar = *GLog) override;
	// End FExec Interface

// Data
#pragma region
public:

	bool Check_MarkAllDatasDirty(const TCHAR* Stream);
	void MarkAllDatasDirty();

#pragma endregion Data
};