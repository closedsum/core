// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Editor/UnrealEdEngine.h"
#include "Types/CsTypes_Load.h"
#include "CsEdEngine.generated.h"

UCLASS()
class CSEDITOR_API UCsEdEngine : public UUnrealEdEngine
{
public:
	GENERATED_BODY()

	//~ Begin UEngine Interface.
	virtual void Init(IEngineLoop* InEngineLoop) override;
	virtual void PreExit() override;
	virtual void Tick(float DeltaSeconds, bool bIdleMode) override;
	//~ End UEngine Interface.

	// Begin FExec Interface
	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar = *GLog) override;
	// End FExec Interface

	class ACsDataMapping* DataMapping;

	void OnBlueprintPreCompile(UBlueprint* Blueprint);

	void OnBeginPIE(bool IsSimulating);

// Enums
#pragma region
public:

	void PopulateUserDefinedEnums();
	void PopulateUserDefinedEnum_InputAction();

	void PopulateEnumMapsFromUserDefinedEnums();

	template<typename EnumMap>
	void PopulateEnumMapFromUserDefinedEnum(const FString& EnumName, const FName& UserDefinedEnumObjectPath)
	{
		TArray<FString> Names;
		GetUserDefinedEnumNames(EnumName, UserDefinedEnumObjectPath, Names);
		EnumMap::Get().ClearUserDefinedEnums();
		AddEnumsByNameToEnumMap<EnumMap>(Names);
	}

	void GetUserDefinedEnumNames(const FString& EnumName, const FName& UserDefinedEnumObjectPath, TArray<FString>& OutNames);

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
