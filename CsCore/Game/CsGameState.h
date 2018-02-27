// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/GameState.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsGameState_OnTick, const float&, DeltaSeconds);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsGameState_OnTick, const float&);

// Enums
#pragma region

namespace ECsGameStateOnBoardState
{
	enum Type
	{
		/** Any Data that is Common to ALL Game Modes. This is usually UI. */
		LoadCommonData,
		SetupHUD,
		/** Any Data that is specific to the Game Mode. */
		LoadData,
		/** Any Items Data loaded from disk or from a Server / Backend. */
		LoadItems,
		/** Any Data that is specific to the Level. */
		LoadSceneData,
		SetupScene,
		SetupLastTickActor,
		SetupJavascriptEntryPoint,
		Completed,
		ECsGameStateOnBoardState_MAX,
	};
}

namespace ECsGameStateOnBoardState
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString LoadCommonData = TCsString(TEXT("LoadCommonData"), TEXT("loadcommondata"), TEXT("load common data"));
		const TCsString SetupHUD = TCsString(TEXT("SetupHUD"), TEXT("setuphud"), TEXT("setup hud"));
		const TCsString LoadData = TCsString(TEXT("LoadData"), TEXT("loaddata"), TEXT("load data"));
		const TCsString LoadItems = TCsString(TEXT("LoadItems"), TEXT("loaditems"), TEXT("load items"));
		const TCsString LoadSceneData = TCsString(TEXT("LoadSceneData"), TEXT("loadscenedata"), TEXT("load scene data"));
		const TCsString SetupScene = TCsString(TEXT("SetupScene"), TEXT("setupscene"), TEXT("setup scene"));
		const TCsString SetupLastTickActor = TCsString(TEXT("SetupLastTickActor"), TEXT("setuplasttickactor"), TEXT("setup last tick actor"));
		const TCsString SetupJavascriptEntryPoint = TCsString(TEXT("SetupJavascriptEntryPoint"), TEXT("setupjavascriptentrypoint"), TEXT("setup javascript entry point"));
		const TCsString Completed = TCsString(TEXT("Completed"), TEXT("completed"), TEXT("completed"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::LoadCommonData) { return Str::LoadCommonData.Value; }
		if (EType == Type::SetupHUD) { return Str::SetupHUD.Value; }
		if (EType == Type::LoadData) { return Str::LoadData.Value; }
		if (EType == Type::LoadItems) { return Str::LoadItems.Value; }
		if (EType == Type::LoadSceneData) { return Str::LoadSceneData.Value; }
		if (EType == Type::SetupScene) { return Str::SetupScene.Value; }
		if (EType == Type::SetupLastTickActor) { return Str::SetupLastTickActor.Value; }
		if (EType == Type::SetupJavascriptEntryPoint) { return Str::SetupJavascriptEntryPoint.Value; }
		if (EType == Type::Completed) { return Str::Completed.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::LoadCommonData) { return Type::LoadCommonData; }
		if (String == Str::SetupHUD) { return Type::SetupHUD; }
		if (String == Str::LoadData) { return Type::LoadData; }
		if (String == Str::LoadItems) { return Type::LoadItems; }
		if (String == Str::LoadSceneData) { return Type::LoadSceneData; }
		if (String == Str::SetupScene) { return Type::SetupScene; }
		if (String == Str::SetupLastTickActor) { return Type::SetupLastTickActor; }
		if (String == Str::SetupJavascriptEntryPoint) { return Type::SetupJavascriptEntryPoint; }
		if (String == Str::Completed) { return Type::Completed; }
		return Type::ECsGameStateOnBoardState_MAX;
	}
}

#define ECS_GAME_STATE_ONBOARD_STATE_MAX (uint8)ECsGameStateOnBoardState::ECsGameStateOnBoardState_MAX
typedef ECsGameStateOnBoardState::Type TCsGameStateOnBoardState;

#pragma endregion Enums

struct FCsPlayerStateMappingRelationship
{
	uint8 A;
	uint8 B;

	bool HasBCompletedInitialReplicationAndLoadingForA;

	FCsPlayerStateMappingRelationship()
	{
		A = CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID;
		B = CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID;

		HasBCompletedInitialReplicationAndLoadingForA = false;
	}
};

struct FCsAIPlayerStateMappingRelationship
{
	// A.I.
	uint8 A;
	// Player
	uint8 B;

	bool HasBCompletedInitialReplicationAndLoadingForA;

	FCsAIPlayerStateMappingRelationship()
	{
		A = CS_INVALID_AI_PLAYER_STATE_UNIQUE_MAPPING_ID;
		B = CS_INVALID_AI_PLAYER_STATE_UNIQUE_MAPPING_ID;

		HasBCompletedInitialReplicationAndLoadingForA = false;
	}
};

UCLASS()
class CSCORE_API ACsGameState : public AGameState
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;

	FBindableEvent_CsGameState_OnTick OnTick_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsGameState_OnTick OnTick_ScriptEvent;

	virtual void PostActorCreated() override;

	/** Called during seamless travel transition twice (once when the transition map is loaded, once when destination map is loaded) */
	virtual void SeamlessTravelTransitionCheckpoint(bool bToTransitionMap) override;

#if WITH_EDITOR
	//virtual void OnLevelTravelTransition();
#endif // #if WITH_EDITOR


// Routines
#pragma region
public:

	static void AddRoutine(UObject* InGameState, struct FCsRoutine* Routine, const uint8 &Type);
	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type);

	static void RemoveRoutine(UObject* InGameState, struct FCsRoutine* Routine, const uint8 &Type);
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type);

#pragma endregion Routines

// OnBoard
#pragma region
public:


	ECsGameStateOnBoardState::Type OnBoardState;

	CS_COROUTINE_DECLARE(OnBoard)

	virtual void GetLoadAssetsShortCodes(const TCsLoadAssetsType &AssetsType, TArray<FName> &OutShortCodes);

	virtual void LoadCommonData();
	virtual void OnFinishedLoadCommonData(const TArray<UObject*> &LoadedAssets, const float& LoadingTime);
	virtual void SetupHUD();
	virtual void LoadData();
	virtual void OnFinishedLoadData(const TArray<UObject*> &LoadedAssets, const float& LoadingTime);
	virtual void LoadItems();
	virtual void LoadSceneData();
	virtual void OnFinishedLoadSceneData(const TArray<UObject*> &LoadedAssets, const float& LoadingTime);
	virtual void SetupScene();
	virtual void OnBoard_Completed();

#pragma endregion OnBoard

	UPROPERTY()
	int32 NumberOfClients;

// LastTickActor
#pragma region
public:

	UPROPERTY()
	class ACsLastTickActor* LastTickActor;

	void SetupLastTickActor();
	virtual void SetupLastTickActor_BindEvents();

#pragma endregion LastTickActor

// Javascript
#pragma region
public:

	TSubclassOf<class ACsJavascriptEntryPoint> JavascriptEntryPointClass;

	UPROPERTY(Transient)
	class ACsJavascriptEntryPoint* JavascriptEntryPoint;

#if WITH_EDITOR

	void SetupJavascriptEntryPoint();

#endif // #if WITH_EDITOR

#pragma endregion Javascript

// Managers
#pragma region
public:

	UPROPERTY()
	class ACsManager_WidgetActor* Manager_WidgetActor;

	UPROPERTY()
	class ACsManager_FX* Manager_FX;

	UPROPERTY()
	class ACsManager_Sound* Manager_Sound;

	UPROPERTY()
	class ACsManager_Projectile* Manager_Projectile;

	UPROPERTY()
	class ACsManager_Damage* Manager_Damage;

	UPROPERTY()
	class ACsManager_InteractiveActor* Manager_InteractiveActor;

	UPROPERTY()
	class ACsManager_Item* Manager_Item;

	UPROPERTY()
	class ACsManager_Inventory* Manager_Inventory;

	UPROPERTY()
	class ACsManager_Crafting* Manager_Crafting;

	UPROPERTY()
	class ACsManager_AI* Manager_AI;

	UPROPERTY()
	class ACsManager_Decal* Manager_Decal;

#pragma endregion Managers

// Match State
#pragma region
public:

	//static char SetMatchInProgressStartTime(struct FCsRoutine* r);

	float MatchInProgressStartTime;
	uint64 MatchInProgressStartTimeMilliseconds;

	float GetElapsedGameTime();
	uint64 GetElapsedGameTimeMilliseconds();

#pragma endregion Match State

// Player State
#pragma region
private:

	uint8 CurrentPlayerStateUniqueMappingId;

public:

	virtual void AddPlayerState(class APlayerState* PlayerState) override;
	void AddPlayerStateMapping(class ACsPlayerState* NewPlayerState);

	virtual void RemovePlayerState(class APlayerState* PlayerState) override;

	TMap<uint8, TWeakObjectPtr<class ACsPlayerState>> PlayerStateMappings;
	TMap<uint8, TArray<FCsPlayerStateMappingRelationship>> PlayerStateMappingRelationships;
	TMap<uint8, bool> HasPlayerStateFullyReplicatedAndLoadedBroadcastFlags;

	class ACsPlayerState* GetPlayerState(const uint8 &MappingId);

	void OnTick_HandleBroadcastingPlayerStateFullyReplicatedAndLoaded();

	void SetPlayerStateMappingRelationshipFlag(const uint8 &ClientMappingId, const uint8 &MappingId);

	bool bServerRequestLocalUniqueMappingId;

	virtual FString GetLocalPlayerProfileName();

#pragma endregion Player State

// A.I. Player State
#pragma region
private:

	uint8 CurrentAIPlayerStateUniqueMappingId;

public:

	void AddAIPlayerStateMapping(class ACsAIPlayerState* NewPlayerState);

	TMap<uint8, TWeakObjectPtr<class ACsAIPlayerState>> AIPlayerStateMappings;
	TMap<uint8, TArray<FCsAIPlayerStateMappingRelationship>> AIPlayerStateMappingRelationships;
	TMap<uint8, bool> HasAIPlayerStateFullyReplicatedAndLoadedBroadcastFlags;

	class ACsAIPlayerState* GetAIPlayerState(const uint8 &MappingId);

	void OnTick_HandleBroadcastingAIPlayerStateFullyReplicatedAndLoaded();

	void SetAIPlayerStateMappingRelationshipFlag(const uint8 &ClientMappingId, const uint8 &MappingId);

#pragma endregion A.I. Player State

#if WITH_EDITOR
	virtual void OnPrePIEEnded(const bool IsSimulating);
#endif // #if WITH_EDITO
};