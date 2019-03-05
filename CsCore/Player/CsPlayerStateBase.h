// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerState.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsPlayerStateBase.generated.h"

// Tick
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPlayerStateBase_OnTick, const uint8&, MappingId, const float&, DeltaSeconds);
// LinkedPawn
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsPlayerStateBase_OnLinkedPawnSet, class ACsPlayerStateBase*, PlayerState);

// Enums
#pragma region

UENUM(BlueprintType)
enum class ECsPlayerStateBaseOnBoardState : uint8
{
	WaitingForGameState						UMETA(DisplayName = "Waiting For GameState"),
	WaitingForFinishLoadingCommonData		UMETA(DisplayName = "Waiting for Finish Loading Common Data"),
	WaitingForLocalPlayerState				UMETA(DisplayName = "Waiting For Local PlayerState"),
	// Client
	RequestLocalUniqueMappingId				UMETA(DisplayName = "Request Local Unique Mapping Id"),
	WaitingForLocalUniqueMappingId			UMETA(DisplayName = "Waiting For Local Unique Mapping Id"),
	RecievedLocalUniqueMappingId			UMETA(DisplayName = "Received Local Unique Mapping Id"),
	// Requesting Player State on Client
	RequestUniqueMappingId					UMETA(DisplayName = "Request Unique Mapping Id"),
	WaitingForUniqueMappingId				UMETA(DisplayName = "Waiting for Unique Mapping Id"),
	RecievedUniqueMappingId					UMETA(DisplayName = "Received Unique Mapping Id"),
	// Player
	RequestPlayerData						UMETA(DisplayName = "Request PlayerData"),
	WaitingForPlayerData					UMETA(DisplayName = "Waiting for PlayerData"),
	ReceivedPlayerData						UMETA(DisplayName = "Received PlayerData"),
	// AI
	RequestAIData							UMETA(DisplayName = "Request AIData"),
	WaitingForAIData						UMETA(DisplayName = "Waiting for AIData"),
	ReceivedAIData							UMETA(DisplayName = "Received AIData"),
	// Loading
	WaitingForGameStateOnBoardCompleted		UMETA(DisplayName = "Waiting for GameState OnBoard Completed"),
	BeginLoadingPlayerData					UMETA(DisplayName = "Begin Loading PlayerData"),
	WaitingForFinishLoadingPlayerData		UMETA(DisplayName = "Waiting for Finish Loading PlayerData"),
	FinishedLoadingPlayerData				UMETA(DisplayName = "Finished Loading PlayerData"),
	SetAssetReferencesPlayerData			UMETA(DisplayName = "Set Asset References PlayerData"),
	WaitingForSetAssetReferencesPlayerData	UMETA(DisplayName = "Waiting for Set Asset References PlayerData"),
	FinishedSetAssetReferencesPlayerData	UMETA(DisplayName = "Finished Set Asset References PlayerData"),
	// Setup
	BeginApplyingPlayerData					UMETA(DisplayName = "Begin Applying PlayerData"),
	WaitingForFinishApplyingPlayerData		UMETA(DisplayName = "Waiting for Finish Applying PlayerData"),
	FinishedApplyingPlayerData				UMETA(DisplayName = "Finished Applying PlayerData"),
	// Handshaking
	SendOnBoardCompleted					UMETA(DisplayName = "Send OnBoard Completed"),
	WaitingForOnBoardCompleted				UMETA(DisplayName = "Waiting for OnBoard Completed"),
	Completed								UMETA(DisplayName = "Completed"),
	ECsPlayerStateBaseOnBoardState_MAX		UMETA(Hidden),
};

#define ECS_PLAYER_STATE_BASE_ONBOARD_STATE_MAX (uint8)ECsPlayerStateBaseOnBoardState::ECsPlayerStateBaseOnBoardState_MAX

struct CSCORE_API EMCsPlayerStateBaseOnBoardState : public TCsEnumMap<ECsPlayerStateBaseOnBoardState>
{
	CS_DECLARE_ENUM_MAP_BODY(EMCsPlayerStateBaseOnBoardState)
};

namespace NCsPlayerStateBaseOnBoardState
{
	namespace Ref
	{
		typedef ECsPlayerStateBaseOnBoardState Type;

		extern CSCORE_API const Type WaitingForGameState;
		extern CSCORE_API const Type WaitingForFinishLoadingCommonData;
		extern CSCORE_API const Type WaitingForLocalPlayerState;
		// Client
		extern CSCORE_API const Type RequestLocalUniqueMappingId;
		extern CSCORE_API const Type WaitingForLocalUniqueMappingId;
		extern CSCORE_API const Type RecievedLocalUniqueMappingId;
		// Requesting Player State on Client
		extern CSCORE_API const Type RequestUniqueMappingId;
		extern CSCORE_API const Type WaitingForUniqueMappingId;
		extern CSCORE_API const Type RecievedUniqueMappingId;
			// Player
		extern CSCORE_API const Type RequestPlayerData;
		extern CSCORE_API const Type WaitingForPlayerData;
		extern CSCORE_API const Type ReceivedPlayerData;
			// AI
		extern CSCORE_API const Type RequestAIData;
		extern CSCORE_API const Type WaitingForAIData;
		extern CSCORE_API const Type ReceivedAIData;
		// Loading
		extern CSCORE_API const Type BeginLoadingPlayerData;
		extern CSCORE_API const Type WaitingForFinishLoadingPlayerData;
		extern CSCORE_API const Type FinishedLoadingPlayerData;
		extern CSCORE_API const Type SetAssetReferencesPlayerData;
		extern CSCORE_API const Type WaitingForSetAssetReferencesPlayerData;
		extern CSCORE_API const Type FinishedSetAssetReferencesPlayerData;
		// Setup
		extern CSCORE_API const Type BeginApplyingPlayerData;
		extern CSCORE_API const Type WaitingForFinishApplyingPlayerData;
		extern CSCORE_API const Type FinishedApplyingPlayerData;
		// Handshaking
		extern CSCORE_API const Type SendOnBoardCompleted;
		extern CSCORE_API const Type WaitingForOnBoardCompleted;
		extern CSCORE_API const Type Completed;
		extern CSCORE_API const Type ECsPlayerStateBaseOnBoardState_MAX;
	}
}

USTRUCT(BlueprintType)
struct CSCORE_API FECsPlayerStateBaseRoutine : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsPlayerStateBaseRoutine)

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsPlayerStateBaseRoutine& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsPlayerStateBaseRoutine : public TCsEnumStructMap<FECsPlayerStateBaseRoutine, uint8>
{
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsPlayerStateBaseRoutine)
};

namespace ECsPlayerStateBaseRoutine
{
	extern CSCORE_API const FECsPlayerStateBaseRoutine OnBoard_Internal;
	extern CSCORE_API const FECsPlayerStateBaseRoutine RequestUniqueMappingId_AI_Internal;
}

#pragma endregion Enums

UCLASS()
class CSCORE_API ACsPlayerStateBase : public APlayerState
{
	GENERATED_UCLASS_BODY()

public:

	virtual void PostActorCreated() override;

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FBindableDynEvent_CsPlayerStateBase_OnTick OnTick_ScriptEvent;

	TWeakObjectPtr<AController> MyController;

	UFUNCTION(BlueprintCallable, Category = "Controller")
	virtual AController* GetMyController();

	UPROPERTY(BlueprintReadOnly, Category = "Pawn")
	TWeakObjectPtr<class ACsPawn> LinkedPawn;

	UFUNCTION(BlueprintCallable, Category = "Pawn")
	class ACsPawn* GetMyPawn();
	template<typename T>
	T* GetMyPawn()
	{
		return Cast<T>(GetMyPawn());
	}

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnLinkedPawnSet, class ACsPlayerStateBase*);

	FOnLinkedPawnSet OnLinkedPawnSet_Event;

	UPROPERTY(BlueprintAssignable, Category = "Pawn")
	FBindableDynEvent_CsPlayerStateBase_OnLinkedPawnSet OnLinkedPawnSet_ScriptEvent;

// Routines
#pragma region
public:

	static void AddRoutine(UObject* InPlayerState, struct FCsRoutine* Routine, const uint8 &Type);
	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type);

	static void RemoveRoutine(UObject* InPlayerState, struct FCsRoutine* Routine, const uint8 &Type);
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type);

#pragma endregion Routines

// OnBoard
#pragma region
public:

	CS_COROUTINE_DECLARE(OnBoard)

	virtual void OnTick_OnBoard();

	UPROPERTY()
	ECsPlayerStateBaseOnBoardState OnBoardState;

	UPROPERTY()
	uint8 UniqueMappingId;

// Client

	// RequestLocalUniqueMappingId
	UFUNCTION(reliable, server, WithValidation)
	void ServerRequestLocalUniqueMappingId(ACsPlayerStateBase* ClientPlayerState, ACsPlayerStateBase* RequestingPlayerState);
	// RecieveLocalUniqueMappingId
	UFUNCTION(reliable, client)
	void ClientRecieveLocalUniqueMappingId(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState);

	virtual void ClientRecieveLocalUniqueMappingId_Internal(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState);

	// Requesting Player State on Client
#pragma region

		// Player
#pragma region
public:

	// RequestUniqueMappingId
	UFUNCTION(reliable, server, WithValidation)
	void ServerRequestUniqueMappingId(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState);

	virtual void ServerRequestUniqueMappingId_Internal(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState);

	// RecieveUniqueMappingId
	UFUNCTION(reliable, client)
	void ClientRecieveUniqueMappingId(ACsPlayerStateBase* RequestingPlayerState, const uint8 &MappingId);

	/** Called by RequestingPlayerState */
	virtual void ClientRecieveUniqueMappingId_Internal(const uint8 &MappingId);

	// RequestPlayerData
	UFUNCTION(reliable, server, WithValidation)
	void ServerRequestPlayerData(const uint8 &ClientMappingId, const uint8 &MappingId);

	virtual void ServerRequestPlayerData_Internal(const uint8 &ClientMappingId, const uint8 &MappingId);

#pragma endregion Player

		// AI
#pragma region
public:

	// RequestUniqueMappingId AI
	UFUNCTION(reliable, server, WithValidation)
	void ServerRequestUniqueMappingId_AI(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState);

	virtual void ServerRequestUniqueMappingId_AI_Internal(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState);

	void RequestUniqueMappingId_AI(ACsPlayerStateBase* RequestingPlayerState);
	static char RequestUniqueMappingId_AI_Internal(struct FCsRoutine* r);
	struct FCsRoutine* RequestUniqueMappingId_AI_Internal_Routine;

	// RecieveUniqueMappingId AI
	UFUNCTION(reliable, client)
	void ClientRecieveUniqueMappingId_AI(ACsPlayerStateBase* RequestingPlayerState, const uint8 &MappingId);

	/** Called by RequestingPlayerState */
	virtual void ClientRecieveUniqueMappingId_AI_Internal(const uint8 &MappingId);

	// RequestAIData
	UFUNCTION(reliable, server, WithValidation)
	void ServerRequestAIData(const uint8 &ClientMappingId, const uint8 &MappingId);

	virtual void ServerRequestAIData_Internal(const uint8 &ClientMappingId, const uint8 &MappingId);

#pragma endregion AI

#pragma endregion Requesting Player State on Client
public:

// Loading

	virtual void GetLoadAssetsShortCodes(const FECsLoadAssetsType &AssetsType, TArray<FName> &OutShortCodes);
	virtual void LoadPlayerData();
	virtual void OnFinishedLoadingPlayerData(const TArray<UObject*> &LoadedAssets, const float &LoadingTime);
private:
	void StartSetAssetReferencesPlayerData();
	void AsyncSetAssetReferencesPlayerData();
public:
	virtual void SetAssetReferencesPlayerData();

// Setup

	virtual void SetupPlayerData();

// Handshaking

	// SendOnBoardCompleted
	UFUNCTION(reliable, server, WithValidation)
	void ServerSendOnBoardCompleted(const uint8 &ClientMappingId, const uint8 &MappingId);

	virtual void ServerSendOnBoardCompleted_Internal(const uint8 &ClientMappingId, const uint8 &MappingId);

	// SendOnBoardCompleted AI
	UFUNCTION(reliable, server, WithValidation)
	void ServerSendOnBoardCompleted_AI(const uint8 &ClientMappingId, const uint8 &MappingId);

	virtual void ServerSendOnBoardCompleted_AI_Internal(const uint8 &ClientMappingId, const uint8 &MappingId);

	virtual void ClearFullscreenWidget();

	bool IsOnBoardCompleted;

	UFUNCTION(reliable, netmulticast)
	void MulticastSetIsOnBoardCompleted();

	UFUNCTION(reliable, netmulticast)
	void MulticastUnSetIsOnBoardCompleted();

	virtual void OnBoard_Completed();

	virtual bool IsOnBoardCompleted_Game();

protected:

	UPROPERTY()
	TArray<UObject*> TransientLoadedAssets;

	void SetTransientLoadedAssets(const TArray<UObject*> &LoadedAssets);
	void ClearTransientLoadedAssets();

#pragma endregion OnBoard

public:

	UPROPERTY()
	class ACsManager_Inventory* Manager_Inventory;

// Items
#pragma region
public:

	UPROPERTY()
	FGuid ItemOwnerId;

#pragma endregion Items

#if WITH_EDITOR
	FDelegateHandle OnPrePIEEndedDelegateHandle;

	virtual void OnPrePIEEnded(const bool bIsSimulating);
#endif // #if WITH_EDITOR
};