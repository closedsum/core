// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Editor/UnrealEdEngine.h"
// Types
#include "Types/Property/Ref/CsProperty_Ref_bool.h"
#include "Types/CsTypes_Load.h"
#include "Types/CsTypes_Async.h"
#include "Types/Enum/CsUserDefinedEnum.h"
#include "CsEdEngine.generated.h"

class UCsDataMapping;
class UCsEnumStructUserDefinedEnumMap;

UCLASS()
class CSEDITOR_API UCsEdEngine : public UUnrealEdEngine
{
public:
	GENERATED_BODY()

// UEngine Interface
#pragma region
public:

	virtual void Init(IEngineLoop* InEngineLoop) override;
	virtual void PreExit() override;
	virtual void Tick(float DeltaSeconds, bool bIdleMode) override;

#pragma endregion UEngine Interface

// FExec Interface
#pragma region
public:

	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar = *GLog) override;

#pragma endregion FExec Interface


// Save
#pragma region
public:

	void OnObjectSaved(UObject* Object);

#pragma endregion Save

public:

	void OnBeginPIE(bool IsSimulating);

// Stream
#pragma region
public:

	bool Stream_GetString(const TCHAR*& Str, const FString& StringType, FString& OutString, const FString& Check, const FString& Format);

#pragma endregion Stream

// Data
#pragma region
public:

	bool Check_MarkDatasDirty(const TCHAR* Stream);
	void MarkDatasDirty(const FECsAssetType& AssetType);

#pragma endregion Data

// DataRootSet
#pragma region
public:

	void OnObjectSaved_Update_DataRootSet_DataTables(UDataTable* DataTable);

	void OnObjectSaved_Update_DataRootSet_Payloads(UDataTable* DataTable);

	void OnObjectSaved_Update_DataRootSet_Payload(FCsPayload& Payload);

#pragma endregion DataRootSet

// References
#pragma region
public:

	bool Check_PrintBlueprintReferencesReport(const TCHAR* Stream);

	void PrintBlueprintReferencesReport(const FName& AssetName);

#pragma endregion References
};
