// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "Engine/LevelScriptActor.h"
// Interfaces
#include "ICsStartPlay.h"
#include "Level/CsGetLevelPayload.h"
// Types
#include "Data/CsTypes_Payload.h"
// Object
#include "UObject/ObjectSaveContext.h"

#include "CsLevelScriptActor.generated.h"

class ITargetPlatform;

UCLASS()
class CSCORE_API ACsLevelScriptActor : public ALevelScriptActor,
									   public ICsStartPlay,
									   public ICsGetLevelPayload
{
	GENERATED_UCLASS_BODY()

// UObject Interface
#pragma region
public:

	//virtual void PreSave(const ITargetPlatform* TargetPlatform) override;

	virtual void PostLoad() override;

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// AActor Interface
#pragma region
public:

	virtual void PostInitializeComponents() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma endregion AActor Interface

// ICsStartPlay
#pragma region
public:

	void StartPlay();

protected:

	bool bHasStartedPlay;

public:

	FORCEINLINE bool HasStartedPlay() const
	{
		return bHasStartedPlay;
	}

#pragma endregion ICsStartPlay

protected:

	/** Script Event when StartPlay is called. */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "StartPlay"))
	void ReceiveStartPlay();

// ICsGetLevelPayload
#pragma region
public:

	FORCEINLINE const FCsPayload& GetLevelPayload() const
	{
		return Payload;
	}

#pragma endregion ICsGetLevelPayload

// Level
#pragma region
public:

	const FString GetLevelName();
	const FName GetLevelFName();

#pragma endregion Level

// SubLevel
#pragma region
#if WITH_EDITOR
public:

	TArray<FName> SubLevelNames;

	void SetupOnSubLevelSavedDelegate();

	FDelegateHandle OnSubLevelSavedHandle;

	void OnSubLevelSaved(UObject* Object, FObjectPreSaveContext SaveContext);

#endif // #if WITH_EDITOR
#pragma endregion SubLevel

// Payload
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Payload")
	bool bTest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Payload")
	FCsPayload Payload;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Payload")
	TMap<FName, FCsPayload> Payload_Levels;

	/** Payload + Payload_Levels */
	UPROPERTY(BlueprintReadOnly, Category = "Payload")
	FCsPayload Payload_Combined;

#if WITH_EDITOR

	/**
	* Get ObjectPath information for specified for Level. This will update
	*  Payload_Levels[LevelName] where LevelName is the name of the Level.
	*
	* @param Level	Level to update ObjectPaths for.
	*/
	void PopulatePayload(ULevel* Level);

	/**
	*
	*/
	void PopulatePayloadLevels();

	/**
	*
	*/
	void PopulatePayloadCombined();

#endif // #if WITH_EDITOR

#pragma endregion Payload

// Editor
#pragma region
#if WITH_EDITOR
public:

	virtual void PostEditChangeProperty(FPropertyChangedEvent& e) override;
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& e) override;

#endif // #if WITH_EDITOR
#pragma endregion Editor
};