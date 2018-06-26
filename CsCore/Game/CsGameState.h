// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/GameState.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsGameState.generated.h"

// Tick
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsGameState_OnTick, const float&, DeltaSeconds);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsGameState_OnTick, const float&);
// LinkedPawn
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsGameState_OnPlayerStateBaseLinkedToPawn, class ACsPlayerStateBase*, PlayerState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsGameState_OnPlayerStateLinkedToPawn, class ACsPlayerState*, PlayerState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsGameState_OnAIPlayerStateLinkedToPawn, class ACsAIPlayerState*, PlayerState);

// Enums
#pragma region

namespace ECsGameStateOnBoardState
{
	enum Type
	{
		/** Any Data that is Common to ALL Game Modes. This is usually UI. */
		LoadCommonData,
		SetAssetReferencesCommonData,
		SetupHUD,
		/** Any Data that is specific to the Game Mode. */
		LoadGameData,
		SetAssetReferencesGameData,
		/** Any Items Data loaded from disk or from a Server / Backend. */
		LoadItems,
		/** Any Data that is specific to the Level. */
		LoadSceneData,
		SetAssetReferencesSceneData,
		SetupScene,
		SetupLastTickActor,
		SetupJavascriptEntryPoint,
		Completed,
		ECsGameStateOnBoardState_MAX,
	};
}

#define ECS_GAME_STATE_ONBOARD_STATE_MAX (uint8)ECsGameStateOnBoardState::ECsGameStateOnBoardState_MAX
typedef ECsGameStateOnBoardState::Type TCsGameStateOnBoardState;

struct CSCORE_API EMCsGameStateOnBoardState : public TCsEnumMap<ECsGameStateOnBoardState::Type>
{
protected:
	EMCsGameStateOnBoardState() {}
	EMCsGameStateOnBoardState(const EMCsGameStateOnBoardState &) = delete;
	EMCsGameStateOnBoardState(EMCsGameStateOnBoardState &&) = delete;
public:
	~EMCsGameStateOnBoardState() {}
private:
	static EMCsGameStateOnBoardState* Instance;

public:
	static EMCsGameStateOnBoardState& Get();
};

namespace ECsGameStateOnBoardState
{
	namespace Ref
	{
		extern CSCORE_API const Type LoadCommonData;
		extern CSCORE_API const Type SetAssetReferencesCommonData;
		extern CSCORE_API const Type SetupHUD;
		extern CSCORE_API const Type LoadGameData;
		extern CSCORE_API const Type SetAssetReferencesGameData;
		extern CSCORE_API const Type LoadItems;
		extern CSCORE_API const Type LoadSceneData;
		extern CSCORE_API const Type SetAssetReferencesSceneData;
		extern CSCORE_API const Type SetupScene;
		extern CSCORE_API const Type SetupLastTickActor;
		extern CSCORE_API const Type SetupJavascriptEntryPoint;
		extern CSCORE_API const Type Completed;
		extern CSCORE_API const Type ECsGameStateOnBoardState_MAX;
	}
}

namespace ECsGameStateRoutine
{
	enum Type
	{
		OnBoard_Internal,
		ECsGameStateRoutine_MAX,
	};
}

#define ECS_ROUTINE_GAME_STATE_MAX (uint8)ECsGameStateRoutine::ECsGameStateRoutine_MAX
typedef ECsGameStateRoutine::Type TCsGameStateRoutine;

namespace ECsGameStateRoutine
{
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString OnBoard_Internal = TCsString(TEXT("OnBoard_Internal"), TEXT("onboard_internal"), TEXT("onboard internal"));
	}

	namespace Ref
	{
		const TCsGameStateRoutine OnBoard_Internal = Type::OnBoard_Internal;
		const TCsGameStateRoutine ECsGameStateRoutine_MAX = Type::ECsGameStateRoutine_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::OnBoard_Internal) { return Str::OnBoard_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		if (String == Str::OnBoard_Internal) { return Ref::OnBoard_Internal; }
		return Ref::ECsGameStateRoutine_MAX;
	}
}

#pragma endregion Enums

// Structs
#pragma region

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

#pragma endregion Structs

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

	virtual void GetLoadAssetsShortCodes(const FECsLoadAssetsType &AssetsType, TArray<FName> &OutShortCodes);

	virtual void LoadCommonData();
	virtual void OnFinishedLoadCommonData(const TArray<UObject*> &LoadedAssets, const float& LoadingTime);
private:
	void StartSetAssetReferencesCommonData();
	void AsyncSetAssetReferencesCommonData();
public:
	virtual void SetAssetReferencesCommonData();
	virtual void SetupHUD();
	virtual void LoadGameData();
	virtual void OnFinishedLoadGameData(const TArray<UObject*> &LoadedAssets, const float& LoadingTime);
private:
	void StartSetAssetReferencesGameData();
	void AsyncSetAssetReferencesGameData();
public:
	virtual void SetAssetReferencesGameData();
	virtual void LoadItems();
	virtual void LoadSceneData();
	virtual void OnFinishedLoadSceneData(const TArray<UObject*> &LoadedAssets, const float& LoadingTime);
private:
	void StartSetAssetReferencesSceneData();
	void AsyncSetAssetReferencesSceneData();
public:
	virtual void SetAssetReferencesSceneData();
	virtual void SetupScene();
	virtual void OnBoard_Completed();

protected:

	UPROPERTY()
	TArray<UObject*> TransientLoadedAssets;

	void SetTransientLoadedAssets(const TArray<UObject*> &LoadedAssets);
	void ClearTransientLoadedAssets();

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
	class AICsManager_WidgetActor* Manager_WidgetActor;

	UPROPERTY()
	class AICsManager_FX* Manager_FX;

	UPROPERTY()
	class AICsManager_Sound* Manager_Sound;

	UPROPERTY()
	class AICsManager_Projectile* Manager_Projectile;

	UPROPERTY()
	class ACsManager_Damage* Manager_Damage;

	UPROPERTY()
	class AICsManager_InteractiveActor* Manager_InteractiveActor;

	UPROPERTY()
	class ACsManager_Item* Manager_Item;

	UPROPERTY()
	class ACsManager_Inventory* Manager_Inventory;

	UPROPERTY()
	class ACsManager_Crafting* Manager_Crafting;

	UPROPERTY()
	class AICsManager_AI* Manager_AI;

	UPROPERTY()
	class ACsManager_Decal* Manager_Decal;

	UPROPERTY()
	class ACsManager_Trace* Manager_Trace;

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

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStateBaseLinkedToPawn, class ACsPlayerStateBase*);

	FOnPlayerStateBaseLinkedToPawn OnPlayerStateBaseLinkedToPawn_Event;

	UPROPERTY(BlueprintAssignable, Category = "Player State")
	FBindableDynEvent_CsGameState_OnPlayerStateBaseLinkedToPawn OnPlayerStateBaseLinkedToPawn_ScriptEvent;

	void OnPlayerStateBaseLinkedToPawn(class ACsPlayerStateBase* PlayerState);

// Player State
#pragma region
private:

	uint8 CurrentPlayerStateUniqueMappingId;

public:

	virtual void AddPlayerState(class APlayerState* PlayerState) override;
	void AddPlayerStateMapping(class ACsPlayerState* NewPlayerState);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddPlayerStateMapping, class ACsPlayerState*);

	FOnAddPlayerStateMapping OnAddPlayerStateMapping_Event;

	virtual void RemovePlayerState(class APlayerState* PlayerState) override;

	TMap<uint8, TWeakObjectPtr<class ACsPlayerState>> PlayerStateMappings;
	TMap<uint8, TArray<FCsPlayerStateMappingRelationship>> PlayerStateMappingRelationships;
	TMap<uint8, bool> HasPlayerStateFullyReplicatedAndLoadedBroadcastFlags;

	class ACsPlayerState* GetPlayerState(const uint8 &MappingId);
	template<typename T>
	T* GetPlayerState(const uint8 &MappingId)
	{
		return Cast<T>(GetPlayerState(MappingId));
	}

	class ACsPlayerPawn* GetPlayerPawn(const uint8 &MappingId);
	template<typename T>
	T* GetPlayerPawn(const uint8& MappingId)
	{
		return Cast<T>(GetPlayerPawn(MappingId));
	}

	void GetSpawnedAndActivePlayerPawns(TArray<class ACsPlayerPawn*>& OutPawns);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStateLinkedToPawn, class ACsPlayerState*);

	FOnPlayerStateLinkedToPawn OnPlayerStateLinkedToPawn_Event;

	UPROPERTY(BlueprintAssignable, Category = "Player State")
	FBindableDynEvent_CsGameState_OnPlayerStateLinkedToPawn OnPlayerStateLinkedToPawn_ScriptEvent;

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
	template<typename T>
	T* GetAIPlayerState(const uint8 &MappingId)
	{
		return Cast<T>(GetAIPlayerState(MappingId));
	}

	class ACsAIPlayerState* GetSafeAIPlayerState(const uint8 &MappingId);
	template<typename T>
	T* GetSafeAIPlayerState(const uint8 &MappingId)
	{
		return Cast<T>(GetSafeAIPlayerState(MappingId));
	}

	class ACsAIPawn* GetAIPawn(const uint8 &MappingId);
	template<typename T>
	T* GetAIPawn(const uint8& MappingId)
	{
		return Cast<T>(GetAIPawn(MappingId));
	}

	class ACsAIPawn* GetSafeAIPawn(const uint8 &MappingId);
	template<typename T>
	T* GetSafeAIPawn(const uint8& MappingId)
	{
		return Cast<T>(GetSafeAIPawn(MappingId));
	}

	void GetAIPlayerStates(TArray<ACsAIPlayerState*>& OutPlayerStates);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnAIPlayerStateLinkedToPawn, class ACsAIPlayerState*);

	FOnAIPlayerStateLinkedToPawn OnAIPlayerStateLinkedToPawn_Event;

	UPROPERTY(BlueprintAssignable, Category = "Player State")
	FBindableDynEvent_CsGameState_OnAIPlayerStateLinkedToPawn OnAIPlayerStateLinkedToPawn_ScriptEvent;

	void OnTick_HandleBroadcastingAIPlayerStateFullyReplicatedAndLoaded();

	void SetAIPlayerStateMappingRelationshipFlag(const uint8 &ClientMappingId, const uint8 &MappingId);

#pragma endregion A.I. Player State

public:

	virtual void StartLevelTransition();
	virtual void ExitGame();

#if WITH_EDITOR
	FDelegateHandle OnPrePIEEndedDelegateHandle;

	virtual void OnPrePIEEnded(const bool IsSimulating);
#endif // #if WITH_EDITO
};