// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/GameState.h"
#include "CsTypes.h"
#include "CsGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsGameState_OnTick, const float&, DeltaSeconds);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsGameState_OnTick, const float&);

// Enums
#pragma region

namespace ECsGameStateRoutine
{
	enum Type
	{
		OnBoard_Internal		UMETA(DisplayName = "OnBoard_Internal"),
		ECsGameStateRoutine_MAX	UMETA(Hidden),
	};
}

namespace ECsGameStateRoutine
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString OnBoard_Internal = TCsString(TEXT("OnBoard_Internal"), TEXT("onboard_internal"), TEXT("onboard internal"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::OnBoard_Internal) { return Str::OnBoard_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::OnBoard_Internal) { return Type::OnBoard_Internal; }
		return Type::ECsGameStateRoutine_MAX;
	}
}

#define ECS_GAME_STATE_ROUTINE_MAX (uint8)ECsGameStateRoutine::ECsGameStateRoutine_MAX
typedef ECsGameStateRoutine::Type TCsGameStateRoutine;

namespace ECsGameStateOnBoardState
{
	enum Type
	{
		LoadCommonData,
		SetupHUD,
		LoadData,
		SetupScene,
		SetupLastTickActor,
		SetupJavascriptEntryPoint,
		Completed,
		ECsGameStateOnBoardState_MAX,
	};
}

namespace ECsGameStateOnBoardState
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString LoadCommonData = TCsString(TEXT("LoadCommonData"), TEXT("loadcommondata"), TEXT("load common data"));
		const TCsString SetupHUD = TCsString(TEXT("SetupHUD"), TEXT("setuphud"), TEXT("setup hud"));
		const TCsString LoadData = TCsString(TEXT("LoadData"), TEXT("loaddata"), TEXT("load data"));
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

	void OnBoard();
	CS_COROUTINE_DECLARE(OnBoard_Internal);

	struct FCsRoutine* OnBoard_Internal_Routine;

	virtual void LoadCommonData();
	virtual void OnFinishedLoadCommonData(const TArray<UObject*> &LoadedAssets, const float& LoadingTime);
	virtual void SetupHUD();
	virtual void LoadData();
	virtual void OnFinishedLoadData(const TArray<UObject*> &LoadedAssets, const float& LoadingTime);
	virtual void SetupScene();

#pragma endregion OnBoard

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
	class ACsManager_InteractiveActor* Manager_InteractiveActor;

	UPROPERTY()
	class ACsManager_AI* Manager_AI;

	UPROPERTY()
	class ACsManager_Decal* Manager_Decal;

#pragma endregion Managers
};