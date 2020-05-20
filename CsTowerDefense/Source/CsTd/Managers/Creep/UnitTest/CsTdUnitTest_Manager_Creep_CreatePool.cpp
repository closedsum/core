// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
#include "Managers/Creep/UnitTest/CsTdUnitTest_Manager_Creep_CreatePool.h"
#include "CsTd.h"

// CVar
#include "Managers/Creep/CsTdCVars_Manager_Creep.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
#include "Managers/Creep/CsTdManager_Creep.h"
// Settings
#include "Settings/CsTdSettings.h"
// Game
#include "GameFramework/GameStateBase.h"

namespace NCsTdUnitTestManagerCreepCreatePoolCached
{
	namespace Str
	{
		//const FString StartReadWrite_Internal = TEXT("FRsUnitTest_Manager_Save_ReadWrite::StartReadWrite_Internal");
	}

	namespace Name
	{
		//const FName StartReadWrite_Internal = FName("FRsUnitTest_Manager_Save_ReadWrite::StartReadWrite_Internal");
	}
}

FCsTdUnitTest_Manager_Creep_CreatePool::FCsTdUnitTest_Manager_Creep_CreatePool() 
	: Super()
{
	Name		  = TEXT("FCsTdUnitTest_Manager_Creep_CreatePool");
	Name_Internal = FName(*Name);

	DisplayName  = TEXT("Create Pool");
	DisplayFName = FName(*DisplayName);

	Start_Internal_Name  = Name + TEXT("::Start_Internal");
	Start_Internal_FName = FName(*Start_Internal_Name);

	bComplete = false;

	GameState = nullptr;
}

FCsTdUnitTest_Manager_Creep_CreatePool::~FCsTdUnitTest_Manager_Creep_CreatePool()
{
}

// ICsUnitTest
#pragma region

void FCsTdUnitTest_Manager_Creep_CreatePool::Start()
{
	GameState = MyRoot->GetWorld()->GetGameState();



	Super::Start();
}

#pragma endregion ICsUnitTest

// ICsUnitTest_Impl
#pragma region

char FCsTdUnitTest_Manager_Creep_CreatePool::Start_Internal(FCsRoutine* R)
{
	const FCsTime& CurrentTime = UCsManager_Time::Get(MyRoot)->GetTime(R->Group);
	FCsTime& StartTime		   = R->GetValue_Timer(CS_FIRST);

	FCsDeltaTime ElapsedTime = FCsDeltaTime::GetDeltaTime(CurrentTime, StartTime);

	CS_COROUTINE_BEGIN(R);

	StartTime = CurrentTime;

	// Prepping for Test
	UE_LOG(LogTemp, Log, TEXT("- Prepping for Tests."));

	FCsCVarToggleMap::Get().Enable(NCsCVarToggle::EnableManagerCreepUnitTest);

	// Adding temp Types
	UE_LOG(LogTemp, Log, TEXT("-- Adding temp types, FECsTdCreep, to EMCsTdCreep."));
	UE_LOG(LogTemp, Log, TEXT("--- __Unit_Test_Type_A__ ('Type A')."));
	UE_LOG(LogTemp, Log, TEXT("--- __Unit_Test_Type_B__ ('Type B')."));
	UE_LOG(LogTemp, Log, TEXT("--- __Unit_Test_Type_C__ ('Type C')."));

	TypeA = EMCsTdCreep::Get().Create(TEXT("__Unit_Test_Type_A__"), TEXT("Type A"), false);
	TypeB = EMCsTdCreep::Get().Create(TEXT("__Unit_Test_Type_B__"), TEXT("Type B"), false);
	TypeC = EMCsTdCreep::Get().Create(TEXT("__Unit_Test_Type_C__"), TEXT("Type C"), false);

	UE_LOG(LogTemp, Log, TEXT(" "));

	UE_LOG(LogTemp, Log, TEXT("- Test 1"));
	UE_LOG(LogTemp, Log, TEXT("-- Power of 2: 8. Pool Size: 64. Payload Size: 4"));

	// Init UCsTdManager_Creep
	if (UCsTdManager_Creep::IsValid(GameState))
	{
		UE_LOG(LogTemp, Log, TEXT("--- Shutting down UCsTdManager_Creep."));

		UCsTdManager_Creep::Shutdown(GameState);
	}

	UE_LOG(LogTemp, Log, TEXT("--- Initializing UCsTdManager_Creep."));

	UCsTdManager_Creep::Init(GameState, UCsTdManager_Creep::StaticClass(), GameState->GetGameInstance());

	// Updating Settings
	{
		UE_LOG(LogTemp, Log, TEXT("--- Updating Settings."));

		UCsTdSettings* Settings = GetMutableDefault<UCsTdSettings>();

		FCsTdSettings_UnitTestPlan_Manager_Creep& Settings_Plan = Settings->UnitTestPlan_ManagerCreep;

		FCsTdManager_Creep_Internal::FCsManagerPooledObjectMapParams Params;

		Params.Name = TEXT("UCsTdManager_Creep::FCsTdManager_Creep_Internal");
		Params.World = MyRoot->GetWorld();

		// Type A
		{
			TSoftClassPtr<AActor>& SoftClass = Settings_Plan.ClassA;

			if (!SoftClass.ToSoftObjectPath().IsValid())
			{
				SET_WARN_COLOR(COLOR_RED)
				UE_LOG(LogTemp, Log, TEXT("--- Class Path for Type: %s is NOT Valid. FAILURE."), *(TypeA.Name));
				CLEAR_WARN_COLOR()

				bComplete = true;

				CS_COROUTINE_EXIT(R);
			}

			UClass* Class = SoftClass.LoadSynchronous();

			if (!Class)
			{
				SET_WARN_COLOR(COLOR_RED)
				UE_LOG(LogTemp, Log, TEXT("--- Failed to load Class @ %s for Type: %s. FAILURE."), *(SoftClass.ToSoftObjectPath().ToString()), *(TypeA.Name));
				CLEAR_WARN_COLOR()

				bComplete = true;

				CS_COROUTINE_EXIT(R);
			}

			FCsManagerPooledObjectParams& ObjectParams = Params.ObjectParams.Add(TypeA);
			
			ObjectParams.Name  = Params.Name + TEXT("_") + TypeA.GetName();
			ObjectParams.World = Params.World;
			//ObjectParams.LogType
			ObjectParams.ConstructParams.Class			  = Class;
			ObjectParams.ConstructParams.ConstructionType = ECsPooledObjectConstruction::Actor;
			
			ObjectParams.bConstructPayloads				  = true;
			ObjectParams.PayloadSize					  = 4;
			ObjectParams.bCreatePool					  = true;
			ObjectParams.PoolSize						  = 64;
		}

		// Type B
		{
			//FCsTdSettings_Manager_Creep_PoolParams& P = Settings.PoolParams.Add(TypeB);
		}

		// Init Internal
		{
			UE_LOG(LogTemp, Log, TEXT("--- Start InitInternal."));

			const double BeginTime = FPlatformTime::Seconds();

			UCsTdManager_Creep::Get(GameState)->InitInternal(Params);

			UE_LOG(LogTemp, Log, TEXT("--- Finshed InitInternal in %f seconds."), (float)(FPlatformTime::Seconds() - BeginTime));
		}
		/*
		UE_LOG(LogTemp, Log, TEXT("--- InitInternal."));

		UCsTdManager_Creep::Get(GameState)->InitInternal(Params);

		// Construct Payloads
		{
			UE_LOG(LogTemp, Log, TEXT("--- Start ConstructPayloads()."));

			FDateTime BeginTime = FDateTime::Now();

			UCsTdManager_Creep::Get(GameState)->ConstructPayloads(TypeA, 4);

			FDateTime EndTime   = FDateTime::Now();
			FTimespan DeltaTime = EndTime - BeginTime;

			UE_LOG(LogTemp, Log, TEXT("--- Finshed ConstructPayloads() in %f seconds."), (float)DeltaTime.GetTotalSeconds());
		}
		// Create Pool
		{
			UE_LOG(LogTemp, Log, TEXT("--- Start CreatePool()."));

			FDateTime BeginTime = FDateTime::Now();

			UCsTdManager_Creep::Get(GameState)->CreatePool(TypeA, 64);

			FDateTime EndTime   = FDateTime::Now();
			FTimespan DeltaTime = EndTime - BeginTime;

			UE_LOG(LogTemp, Log, TEXT("--- Finshed CreatePool() in %f seconds."), (float)DeltaTime.GetTotalSeconds());
		}
		*/
	}

	// Clean up after Tests
	UE_LOG(LogTemp, Log, TEXT("- Clean up after Tests."));

	// Shutdown UCsTdManager_Creep
	UE_LOG(LogTemp, Log, TEXT("-- Shutting down UCsTdManager_Creep."));

	UCsTdManager_Creep::Shutdown(GameState);

	// Remove temp Types
	UE_LOG(LogTemp, Log, TEXT("-- Removing temp types, FECsTdCreep, to EMCsTdCreep."));
	UE_LOG(LogTemp, Log, TEXT("--- __Unit_Test_Type_A__ ('Type A')."));
	UE_LOG(LogTemp, Log, TEXT("--- __Unit_Test_Type_B__ ('Type B')."));
	UE_LOG(LogTemp, Log, TEXT("--- __Unit_Test_Type_C__ ('Type C')."));

	EMCsTdCreep::Get().Remove(TypeA);
	EMCsTdCreep::Get().Remove(TypeB);
	EMCsTdCreep::Get().Remove(TypeC);

	FCsCVarToggleMap::Get().Disable(NCsCVarToggle::EnableManagerCreepUnitTest);

	bComplete = true;

	CS_COROUTINE_END(R);
}

#pragma endregion ICsUnitTest_Impl

void FCsTdUnitTest_Manager_Creep_CreatePool::OnConstructObject_TypeA(const FCsTdCreepPooled* Creep)
{

}