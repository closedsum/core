// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Editor/UnrealEdEngine.h"
#include "Types/CsTypes_Load.h"
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

// Types
#pragma region

	CS_DECLARE_ASSET_TYPE

	TCsGetAssetTypeStaticClass GetAssetTypeStaticClass;

#pragma endregion Types

// Stream
#pragma region
public:

	bool Stream_GetString(const TCHAR*& Str, const FString &StringType, FString &OutString, const FString &Check, const FString &Format);

#pragma endregion Stream

// Data
#pragma region
public:

	bool Check_MarkDatasDirty(const TCHAR* Stream);
	void MarkDatasDirty(const TCsAssetType &AssetType);

#pragma endregion Data
};