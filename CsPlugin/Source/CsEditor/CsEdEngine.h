// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Editor/UnrealEdEngine.h"
#include "Types/CsTypes_Load.h"
#include "Types/CsTypes_Async.h"
#include "CsEdEngine.generated.h"

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

// Tick
#pragma region
public:

	bool bTicked;
	TCsBool_Ref bTickedHandle;

	virtual void OnFirstTick(const bool& Value);

#pragma endregion Tick

public:

	class ACsDataMapping* DataMapping;

	void OnBlueprintPreCompile(UBlueprint* Blueprint);

	void OnBeginPIE(bool IsSimulating);

// Enums
#pragma region
public:

	TWeakObjectPtr<UCsEnumStructUserDefinedEnumMap> EnumStructUserDefinedEnumMap;

	UCsEnumStructUserDefinedEnumMap* GetEnumStructUserDefinedEnumMap();

	FCsMutex OnBlueprintPreCompile_HandleEnums_Mutex;

	void OnBlueprintPreCompile_HandleEnums();

	void PopulateUserDefinedEnums();
	void PopulateUserDefinedEnum_InputAction();

	void PopulateEnumMapsFromUserDefinedEnums();

	template<typename EnumMap>
	void PopulateEnumMapFromUserDefinedEnum(const FECsUserDefinedEnum& EnumType)
	{
		TArray<FString> Names;
		GetUserDefinedEnumNames(EnumMap::Get().GetEnumName(), EnumType, Names);
		EnumMap::Get().ClearUserDefinedEnums();
		AddEnumsByNameToEnumMap<EnumMap>(Names);
	}

	void GetUserDefinedEnumNames(const FString& EnumName, const FECsUserDefinedEnum& EnumType, TArray<FString>& OutNames);

	template<typename EnumMap>
	void AddEnumsByNameToEnumMap(const TArray<FString>& Names)
	{
		for (const FString& Name : Names)
		{
			EnumMap::Get().CreateSafe(Name, true);
		}
	}

#pragma endregion Enums

// Types
#pragma region
public:

	TCsGetAssetTypeStaticClass GetAssetTypeStaticClass;

#pragma endregion Types

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
};