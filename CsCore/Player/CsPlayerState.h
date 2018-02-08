// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerState.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPlayerState_OnTick, const uint8&, MappingId, const float&, DeltaSeconds);

// Enums
#pragma region

UENUM(BlueprintType)
namespace ECsPlayerStateOnBoardState
{
	enum Type
	{
		WaitingForGameState						UMETA(DisplayName = "Waiting For GameState"),
		WaitingForFinishLoadingCommonData		UMETA(DisplayName = "Waiting for Finish Loading Commong Data"),
		WaitingForLocalPlayerState				UMETA(DisplayName = "Waiting For Local PlayerState"),
		// Client
		RequestLocalUniqueMappingId				UMETA(DisplayName = "Request Local Unique Mapping Id"),
		WaitingForLocalUniqueMappingId			UMETA(DisplayName = "Waiting For Local Unique Mapping Id"),
		RecievedLocalUniqueMappingId			UMETA(DisplayName = "Recieved Local Unique Mapping Id"),
		// Requesting Player State on Client
		RequestUniqueMappingId					UMETA(DisplayName = "Request Unique Mapping Id"),
		WaitingForUniqueMappingId				UMETA(DisplayName = "Waiting for Unique Mapping Id"),
		RecievedUniqueMappingId					UMETA(DisplayName = "Recieved Unique Mapping Id"),
		RequestPlayerData						UMETA(DisplayName = "Request PlayerData"),
		WaitingForPlayerData					UMETA(DisplayName = "Waiting for PlayerData"),
		RecievedPlayerData						UMETA(DisplayName = "Recieved PlayerData"),
		// Loading
		WaitingForGameStateOnBoardCompleted		UMETA(DisplayName = "Waiting for GameState OnBoard Completed"),
		BeginLoadingPlayerData					UMETA(DisplayName = "Begin Loading PlayerData"),
		WaitingForFinishLoadingPlayerData		UMETA(DisplayName = "Waiting for Finish Loading PlayerData"),
		FinishedLoadingPlayerData				UMETA(DisplayName = "Finished Loading PlayerData"),
		// Setup
		BeginApplyingPlayerData					UMETA(DisplayName = "Begin Applying PlayerData"),
		WaitingForFinishApplyingPlayerData		UMETA(DisplayName = "Waiting for Finish Applying PlayerData"),
		FinishedApplyingPlayerData				UMETA(DisplayName = "Finished Applying PlayerData"),
		// Handshaking
		SendOnBoardCompleted					UMETA(DisplayName = "Send OnBoard Completed"),
		WaitingForOnBoardCompleted				UMETA(DisplayName = "Waiting for OnBoard Completed"),
		Completed								UMETA(DisplayName = "Completed"),
		ECsPlayerStateOnBoardState_MAX			UMETA(Hidden),
	};
}

namespace ECsPlayerStateOnBoardState
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

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
		const TCsString RequestPlayerData = TCsString(TEXT("RequestPlayerData"), TEXT("requestplayerdata"), TEXT("request player data"));
		const TCsString WaitingForPlayerData = TCsString(TEXT("WaitingForPlayerData"), TEXT("waitingforplayerdata"), TEXT("waiting for player data"));
		const TCsString RecievedPlayerData = TCsString(TEXT("RecievedPlayerData"), TEXT("recievedplayerdata"), TEXT("recieved player data"));
		// Loading
		const TCsString BeginLoadingPlayerData = TCsString(TEXT("BeginLoadingPlayerData"), TEXT("beginloadingplayerdata"), TEXT("begin loading player data"));
		const TCsString WaitingForFinishLoadingPlayerData = TCsString(TEXT("WaitingForFinishLoadingPlayerData"), TEXT("waitingforfinishloadingplayerdata"), TEXT("waiting for finish loading player data"));
		const TCsString FinishedLoadingPlayerData = TCsString(TEXT("FinishedLoadingPlayerData"), TEXT("finishedloadingplayerdata"), TEXT("finished loading player data"));
		// Setup
		const TCsString BeginApplyingPlayerData = TCsString(TEXT("BeginApplyingPlayerData"), TEXT("beginapplyingplayerdata"), TEXT("begin applying player data"));
		const TCsString WaitingForFinishApplyingPlayerData = TCsString(TEXT("WaitingForFinishApplyingPlayerData"), TEXT("waitingforfinishapplyingplayerdata"), TEXT("waiting for finish applying player data"));
		const TCsString FinishedApplyingPlayerData = TCsString(TEXT("FinishedApplyingPlayerData"), TEXT("finishedapplyingplayerdata"), TEXT("finished applying player data"));
		// Handshaking
		const TCsString SendOnBoardCompleted = TCsString(TEXT("SendOnBoardCompleted"), TEXT("sendonboardcompleted"), TEXT("send onboard completed"));
		const TCsString WaitingForOnBoardCompleted = TCsString(TEXT("WaitingForOnBoardCompleted"), TEXT("waitingforonboardcompleted"), TEXT("waiting for onboard completed"));
		const TCsString Completed = TCsString(TEXT("Completed"), TEXT("completed"), TEXT("completed"));
	}

	FORCEINLINE FString ToString(const Type &EType)
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
		if (EType == Type::RequestPlayerData) { return Str::RequestPlayerData.Value; }
		if (EType == Type::WaitingForPlayerData) { return Str::WaitingForPlayerData.Value; }
		if (EType == Type::RecievedPlayerData) { return Str::RecievedPlayerData.Value; }
		// Loading
		if (EType == Type::BeginLoadingPlayerData) { return Str::BeginLoadingPlayerData.Value; }
		if (EType == Type::WaitingForFinishLoadingPlayerData) { return Str::WaitingForFinishLoadingPlayerData.Value; }
		if (EType == Type::FinishedLoadingPlayerData) { return Str::FinishedLoadingPlayerData.Value; }
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
		if (String == Str::RequestPlayerData) { return Type::RequestPlayerData; }
		if (String == Str::WaitingForPlayerData) { return Type::WaitingForPlayerData; }
		if (String == Str::RecievedPlayerData) { return Type::RecievedPlayerData; }
		// Loading
		if (String == Str::BeginLoadingPlayerData) { return Type::BeginLoadingPlayerData; }
		if (String == Str::WaitingForFinishLoadingPlayerData) { return Type::WaitingForFinishLoadingPlayerData; }
		if (String == Str::FinishedLoadingPlayerData) { return Type::FinishedLoadingPlayerData; }
		// Setup
		if (String == Str::BeginApplyingPlayerData) { return Type::BeginApplyingPlayerData; }
		if (String == Str::WaitingForFinishApplyingPlayerData) { return Type::WaitingForFinishApplyingPlayerData; }
		if (String == Str::FinishedApplyingPlayerData) { return Type::FinishedApplyingPlayerData; }
		// Handshaking
		if (String == Str::SendOnBoardCompleted) { return Type::SendOnBoardCompleted; }
		if (String == Str::WaitingForOnBoardCompleted) { return Type::WaitingForOnBoardCompleted; }
		if (String == Str::Completed) { return Type::Completed; }
		return Type::ECsPlayerStateOnBoardState_MAX;
	}
}

#define ECS_PLAYER_STATE_ONBOARD_STATE_MAX (uint8)ECsPlayerStateOnBoardState::ECsPlayerStateOnBoardState_MAX
typedef TEnumAsByte<ECsPlayerStateOnBoardState::Type> TCsPlayerStateOnBoardState;

namespace ECsPlayerStateRoutine
{
	enum Type
	{
		OnBoard_Internal,
		SetupPawn_Internal,
		ECsPlayerStateRoutine_MAX,
	};
}

namespace ECsPlayerStateRoutine
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString OnBoard_Internal = TCsString(TEXT("OnBoard_Internal"), TEXT("onboard_internal"), TEXT("onboard internal"));
		const TCsString SetupPawn_Internal = TCsString(TEXT("SetupPawn_Internal"), TEXT("setuppawn_internal"), TEXT("setup pawn internal"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::OnBoard_Internal) { return Str::OnBoard_Internal.Value; }
		if (EType == Type::SetupPawn_Internal) { return Str::SetupPawn_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::OnBoard_Internal) { return Type::OnBoard_Internal; }
		if (String == Str::SetupPawn_Internal) { return Type::SetupPawn_Internal; }
		return Type::ECsPlayerStateRoutine_MAX;
	}
}

#define ECS_PLAYER_STATE_ROUTINE_MAX (uint8)ECsPlayerStateRoutine::ECsPlayerStateRoutine_MAX
typedef ECsPlayerStateRoutine::Type TCsPlayerStateRoutine;

#pragma endregion Enums

UCLASS()
class CSCORE_API ACsPlayerState : public APlayerState
{
	GENERATED_UCLASS_BODY()

	virtual void PostActorCreated() override;

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FBindableDynEvent_CsPlayerState_OnTick OnTick_ScriptEvent;

	TWeakObjectPtr<AController> MyController;

	AController* GetMyController();

	TWeakObjectPtr<class ACsPlayerPawn> LinkedPawn;

	ACsPlayerPawn* GetMyPawn();

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
	TEnumAsByte<ECsPlayerStateOnBoardState::Type> OnBoardState;

	UPROPERTY()
	uint8 UniqueMappingId;

// Client

	// RequestLocalUniqueMappingId
	UFUNCTION(reliable, server, WithValidation)
	void ServerRequestLocalUniqueMappingId(ACsPlayerState* ClientPlayerState);
	// RecieveLocalUniqueMappingId
	UFUNCTION(reliable, client)
	void ClientRecieveLocalUniqueMappingId(const uint8 &MappingId);

// Requesting Player State on Client

	// RequestUniqueMappingId
	UFUNCTION(reliable, server, WithValidation)
	void ServerRequestUniqueMappingId(const uint8 &ClientMappingId, ACsPlayerState* RequestingPlayerState);
	// RecieveUniqueMappingId
	UFUNCTION(reliable, client)
	void ClientRecieveUniqueMappingId(ACsPlayerState* RequestingPlayerState, const uint8 &MappingId);
	// RequestPlayerData
	UFUNCTION(reliable, server, WithValidation)
	void ServerRequestPlayerData(const uint8 &ClientMappingId, const uint8 &MappingId);

	virtual void ServerRequestPlayerData_Internal(const uint8 &ClientMappingId, const uint8 &MappingId);

// Loading

	virtual void GetLoadAssetsShortCodes(const TCsLoadAssetsType &AssetsType, TArray<FName> &OutShortCodes);
	virtual void LoadPlayerData();
	virtual void OnFinishedLoadingPlayerData(const TArray<UObject*> &LoadedAssets, const float &LoadingTime);

// Setup

	virtual void SetupPlayerData();

// Handshaking

	// SendOnBoardCompleted
	UFUNCTION(reliable, server, WithValidation)
	void ServerSendOnBoardCompleted(const uint8 &ClientMappingId, const uint8 &MappingId);

	bool IsOnBoardCompleted;

	UFUNCTION(reliable, netmulticast)
	void MulticastSetIsOnBoardCompleted();

	UFUNCTION(reliable, netmulticast)
	void MulticastUnSetIsOnBoardCompleted();

	virtual void OnBoard_Completed();

	bool IsOnBoardCompleted_Game();

#pragma endregion OnBoard

	UPROPERTY()
	class ACsManager_Inventory* Manager_Inventory;

// Items
#pragma region
public:

	UPROPERTY()
	uint64 ItemOwnerId;

#pragma endregion Items

#if WITH_EDITOR
	virtual void OnPrePIEEnded(const bool bIsSimulating);
#endif // #if WITH_EDITOR
};