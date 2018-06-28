// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
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
namespace ECsPlayerStateBaseOnBoardState
{
	enum Type
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
}

namespace ECsPlayerStateBaseOnBoardState
{
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString WaitingForGameState = TCsString(TEXT("WaitingForGameState"), TEXT("waitingforgamestate"), TEXT("waiting for game state"));
		const TCsString WaitingForFinishLoadingCommonData = TCsString(TEXT("WaitingForFinishLoadingCommonData"), TEXT("waitingforfinishloadingcommondata"), TEXT("waiting for finish loading common data"));
		const TCsString WaitingForLocalPlayerState = TCsString(TEXT("WaitingForLocalPlayerState"), TEXT("waitingforlocalplayerstate"), TEXT("waiting for local player state"));
		// Client
		const TCsString RequestLocalUniqueMappingId = TCsString(TEXT("RequestLocalUniqueMappingId"), TEXT("requestlocaluniquemappingid"), TEXT("request local unique mapping id"));
		const TCsString WaitingForLocalUniqueMappingId = TCsString(TEXT("WaitingForLocalUniqueMappingId"), TEXT("waitingforlocaluniquemappingid"), TEXT("waiting for local unique mapping id"));
		const TCsString RecievedLocalUniqueMappingId = TCsString(TEXT("RecievedLocalUniqueMappingId"), TEXT("recievedlocaluniquemappingid"), TEXT("recieved local unique mapping id"));
		// Requesting Player State on Client
		const TCsString RequestUniqueMappingId = TCsString(TEXT("RequestUniqueMappingId"), TEXT("requestuniquemappingid"), TEXT("request unique mapping id"));
		const TCsString WaitingForUniqueMappingId = TCsString(TEXT("WaitingForUniqueMappingId"), TEXT("waitingforuniquemappingid"), TEXT("waiting for unique mapping id"));
		const TCsString RecievedUniqueMappingId = TCsString(TEXT("RecievedUniqueMappingId"), TEXT("recievedunqiuemappingid"), TEXT("recieved unique mapping id"));
			// Player
		const TCsString RequestPlayerData = TCsString(TEXT("RequestPlayerData"), TEXT("requestplayerdata"), TEXT("request player data"));
		const TCsString WaitingForPlayerData = TCsString(TEXT("WaitingForPlayerData"), TEXT("waitingforplayerdata"), TEXT("waiting for player data"));
		const TCsString ReceivedPlayerData = TCsString(TEXT("ReceivedPlayerData"), TEXT("receivedplayerdata"), TEXT("received player data"));
			// AI
		const TCsString RequestAIData = TCsString(TEXT("RequestAIData"), TEXT("requestaidata"), TEXT("request ai data"));
		const TCsString WaitingForAIData = TCsString(TEXT("WaitingForAIData"), TEXT("waitingforaidata"), TEXT("waiting for ai data"));
		const TCsString ReceivedAIData = TCsString(TEXT("ReceivedAIData"), TEXT("receivedaidata"), TEXT("received ai data"));
		// Loading
		const TCsString BeginLoadingPlayerData = TCsString(TEXT("BeginLoadingPlayerData"), TEXT("beginloadingplayerdata"), TEXT("begin loading player data"));
		const TCsString WaitingForFinishLoadingPlayerData = TCsString(TEXT("WaitingForFinishLoadingPlayerData"), TEXT("waitingforfinishloadingplayerdata"), TEXT("waiting for finish loading player data"));
		const TCsString FinishedLoadingPlayerData = TCsString(TEXT("FinishedLoadingPlayerData"), TEXT("finishedloadingplayerdata"), TEXT("finished loading player data"));
		const TCsString SetAssetReferencesPlayerData = TCsString(TEXT("SetAssetReferencesPlayerData"), TEXT("setassetreferencesplayerdata"), TEXT("set asset references player data"));
		const TCsString WaitingForSetAssetReferencesPlayerData = TCsString(TEXT("WaitingForSetAssetReferencesPlayerData"), TEXT("waitingforsetassetreferencesplayerdata"), TEXT("waiting for set asset references player data"));
		const TCsString FinishedSetAssetReferencesPlayerData = TCsString(TEXT("FinishedSetAssetReferencesPlayerData"), TEXT("finishedsetassetreferencesplayerdata"), TEXT("finished set asset references player data"));
		// Setup
		const TCsString BeginApplyingPlayerData = TCsString(TEXT("BeginApplyingPlayerData"), TEXT("beginapplyingplayerdata"), TEXT("begin applying player data"));
		const TCsString WaitingForFinishApplyingPlayerData = TCsString(TEXT("WaitingForFinishApplyingPlayerData"), TEXT("waitingforfinishapplyingplayerdata"), TEXT("waiting for finish applying player data"));
		const TCsString FinishedApplyingPlayerData = TCsString(TEXT("FinishedApplyingPlayerData"), TEXT("finishedapplyingplayerdata"), TEXT("finished applying player data"));
		// Handshaking
		const TCsString SendOnBoardCompleted = TCsString(TEXT("SendOnBoardCompleted"), TEXT("sendonboardcompleted"), TEXT("send onboard completed"));
		const TCsString WaitingForOnBoardCompleted = TCsString(TEXT("WaitingForOnBoardCompleted"), TEXT("waitingforonboardcompleted"), TEXT("waiting for onboard completed"));
		const TCsString Completed = TCsString(TEXT("Completed"), TEXT("completed"), TEXT("completed"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::WaitingForGameState) { return Str::WaitingForGameState.Value; }
		if (EType == Type::WaitingForFinishLoadingCommonData) { return Str::WaitingForFinishLoadingCommonData.Value; }
		if (EType == Type::WaitingForLocalPlayerState) { return Str::WaitingForLocalPlayerState.Value; }
		// Client
		if (EType == Type::RequestLocalUniqueMappingId) { return Str::RequestLocalUniqueMappingId.Value; }
		if (EType == Type::WaitingForLocalUniqueMappingId) { return Str::WaitingForLocalUniqueMappingId.Value; }
		if (EType == Type::RecievedLocalUniqueMappingId) { return Str::RecievedLocalUniqueMappingId.Value; }
		// Requesting Player State on Client
		if (EType == Type::RequestUniqueMappingId) { return Str::RequestUniqueMappingId.Value; }
		if (EType == Type::WaitingForUniqueMappingId) { return Str::WaitingForUniqueMappingId.Value; }
		if (EType == Type::RecievedUniqueMappingId) { return Str::RecievedUniqueMappingId.Value; }
			// Player
		if (EType == Type::RequestPlayerData) { return Str::RequestPlayerData.Value; }
		if (EType == Type::WaitingForPlayerData) { return Str::WaitingForPlayerData.Value; }
		if (EType == Type::ReceivedPlayerData) { return Str::ReceivedPlayerData.Value; }
			// AI
		if (EType == Type::RequestAIData) { return Str::RequestAIData.Value; }
		if (EType == Type::WaitingForAIData) { return Str::WaitingForAIData.Value; }
		if (EType == Type::ReceivedAIData) { return Str::ReceivedAIData.Value; }
		// Loading
		if (EType == Type::BeginLoadingPlayerData) { return Str::BeginLoadingPlayerData.Value; }
		if (EType == Type::WaitingForFinishLoadingPlayerData) { return Str::WaitingForFinishLoadingPlayerData.Value; }
		if (EType == Type::FinishedLoadingPlayerData) { return Str::FinishedLoadingPlayerData.Value; }
		if (EType == Type::SetAssetReferencesPlayerData) { return Str::SetAssetReferencesPlayerData.Value; }
		if (EType == Type::WaitingForSetAssetReferencesPlayerData) { return Str::WaitingForSetAssetReferencesPlayerData.Value; }
		if (EType == Type::FinishedSetAssetReferencesPlayerData) { return Str::FinishedSetAssetReferencesPlayerData.Value; }
		// Setup
		if (EType == Type::BeginApplyingPlayerData) { return Str::BeginApplyingPlayerData.Value; }
		if (EType == Type::WaitingForFinishApplyingPlayerData) { return Str::WaitingForFinishApplyingPlayerData.Value; }
		if (EType == Type::FinishedApplyingPlayerData) { return Str::FinishedApplyingPlayerData.Value; }
		// Handshaking
		if (EType == Type::SendOnBoardCompleted) { return Str::SendOnBoardCompleted.Value; }
		if (EType == Type::WaitingForOnBoardCompleted) { return Str::WaitingForOnBoardCompleted.Value; }
		if (EType == Type::Completed) { return Str::Completed.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::WaitingForGameState) { return Type::WaitingForGameState; }
		if (String == Str::WaitingForFinishLoadingCommonData) { return Type::WaitingForFinishLoadingCommonData; }
		if (String == Str::WaitingForLocalPlayerState) { return Type::WaitingForLocalPlayerState; }
		// Client
		if (String == Str::RequestLocalUniqueMappingId) { return Type::RequestLocalUniqueMappingId; }
		if (String == Str::WaitingForLocalUniqueMappingId) { return Type::WaitingForLocalUniqueMappingId; }
		if (String == Str::RecievedLocalUniqueMappingId) { return Type::RecievedLocalUniqueMappingId; }
		// Requesting Player State on Client
		if (String == Str::RequestUniqueMappingId) { return Type::RequestUniqueMappingId; }
		if (String == Str::WaitingForUniqueMappingId) { return Type::WaitingForUniqueMappingId; }
		if (String == Str::RecievedUniqueMappingId) { return Type::RecievedUniqueMappingId; }
			// Player
		if (String == Str::RequestPlayerData) { return Type::RequestPlayerData; }
		if (String == Str::WaitingForPlayerData) { return Type::WaitingForPlayerData; }
		if (String == Str::ReceivedPlayerData) { return Type::ReceivedPlayerData; }
			// AI
		if (String == Str::RequestAIData) { return Type::RequestAIData; }
		if (String == Str::WaitingForAIData) { return Type::WaitingForAIData; }
		if (String == Str::ReceivedAIData) { return Type::ReceivedAIData; }
		// Loading
		if (String == Str::BeginLoadingPlayerData) { return Type::BeginLoadingPlayerData; }
		if (String == Str::WaitingForFinishLoadingPlayerData) { return Type::WaitingForFinishLoadingPlayerData; }
		if (String == Str::FinishedLoadingPlayerData) { return Type::FinishedLoadingPlayerData; }
		if (String == Str::SetAssetReferencesPlayerData) { return Type::SetAssetReferencesPlayerData; }
		if (String == Str::WaitingForSetAssetReferencesPlayerData) { return Type::WaitingForSetAssetReferencesPlayerData; }
		if (String == Str::FinishedSetAssetReferencesPlayerData) { return Type::FinishedSetAssetReferencesPlayerData; }
		// Setup
		if (String == Str::BeginApplyingPlayerData) { return Type::BeginApplyingPlayerData; }
		if (String == Str::WaitingForFinishApplyingPlayerData) { return Type::WaitingForFinishApplyingPlayerData; }
		if (String == Str::FinishedApplyingPlayerData) { return Type::FinishedApplyingPlayerData; }
		// Handshaking
		if (String == Str::SendOnBoardCompleted) { return Type::SendOnBoardCompleted; }
		if (String == Str::WaitingForOnBoardCompleted) { return Type::WaitingForOnBoardCompleted; }
		if (String == Str::Completed) { return Type::Completed; }
		return Type::ECsPlayerStateBaseOnBoardState_MAX;
	}
}

#define ECS_PLAYER_STATE_BASE_ONBOARD_STATE_MAX (uint8)ECsPlayerStateBaseOnBoardState::ECsPlayerStateBaseOnBoardState_MAX
typedef ECsPlayerStateBaseOnBoardState::Type TCsPlayerStateBaseOnBoardState;

namespace ECsPlayerStateBaseRoutine
{
	enum Type
	{
		OnBoard_Internal,
		RequestUniqueMappingId_AI_Internal,
		ECsPlayerStateBaseRoutine_MAX,
	};
}

namespace ECsPlayerStateBaseRoutine
{
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString OnBoard_Internal = TCsString(TEXT("OnBoard_Internal"), TEXT("onboard_internal"), TEXT("onboard internal"));
		const TCsString RequestUniqueMappingId_AI_Internal = TCsString(TEXT("RequestUniqueMappingId_AI_Internal"), TEXT("requestuniquemappingid_ai_internal"), TEXT("request unique mappind id ai internal"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::OnBoard_Internal) { return Str::OnBoard_Internal.Value; }
		if (EType == Type::RequestUniqueMappingId_AI_Internal) { return Str::RequestUniqueMappingId_AI_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::OnBoard_Internal) { return Type::OnBoard_Internal; }
		if (String == Str::RequestUniqueMappingId_AI_Internal) { return Type::RequestUniqueMappingId_AI_Internal; }
		return Type::ECsPlayerStateBaseRoutine_MAX;
	}
}

#define ECS_PLAYER_STATE_BASE_ROUTINE_MAX (uint8)ECsPlayerStateBaseRoutine::ECsPlayerStateBaseRoutine_MAX
typedef ECsPlayerStateBaseRoutine::Type TCsPlayerStateBaseRoutine;

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
	TEnumAsByte<ECsPlayerStateBaseOnBoardState::Type> OnBoardState;

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