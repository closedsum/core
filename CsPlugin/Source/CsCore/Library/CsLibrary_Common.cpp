// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Common.h"
#include "CsCore.h"
#include "CsCVars.h"

// Types
#include "Types/CsTypes_Curve.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Game
#include "GameFramework/GameState.h"
#include "GameFramework/GameMode.h"
#include "Game/CsGameInstance.h"
// VR
#include "IHeadMountedDisplay.h"
#include "MotionControllerComponent.h"
#include "MotionController/CsMotionController.h"
// Components
#include "Components/CsStaticMeshComponent.h"
#include "Components/CsSkeletalMeshComponent.h"
#include "Components/CsPoseableMeshComponent.h"
#include "Components/CsBoxComponent.h"
#include "Components/CsSphereComponent.h"
// Player
#include "Player/CsPlayerState.h"
#include "Player/CsPlayerPawn.h"
#include "VR/Player/CsPlayerPawn_VR.h"
#include "../Engine/Classes/GameFramework/PlayerInput.h"
// Physics
#include "Engine/CollisionProfile.h"
// Data
#include "Data/CsData.h"
// Managers
#include "Managers/Inventory/CsManager_Inventory.h"
#include "Managers/Time/CsManager_Time.h"

#if WITH_EDITOR

// Javascript
#include "JavascriptIsolate.h"
#include "JavascriptContext.h"

// Slate
#include "Runtime/Slate/Public/Framework/Notifications/NotificationManager.h"
#include "Runtime/Slate/Public/Widgets/Notifications/SNotificationList.h"
#include "../Source/Editor/EditorStyle/Public/EditorStyleSet.h"

#include "Runtime/Core/Public/Internationalization/Internationalization.h"

#include "../Source/Editor/UnrealEd/Public/Editor.h"

#endif // #if WITH_EDITOR

// Cache
#pragma region

namespace NCsCommonCached
{
	namespace Name
	{
		// Functions
		const FName ScaleActorOverTime_Internal = FName("UCsLibrary_Common::ScaleActorOverTime_Internal");
		const FName ScaleActorOverTime_AsCurve_Internal = FName("UCsLibrary_Common::ScaleActorOverTime_AsCurve_Internal");
		const FName MoveActorOverTime_Internal = FName("UCsLibrary_Common::MoveActorOverTime_Internal");
		const FName DestroyMaterialInstanceDynamic_Internal = FName("UCsLibrary_Common::DestroyMaterialInstanceDynamic_Internal");
		const FName FadeCameraOverTime_Internal = FName("UCsLibrary_Common::FadeCameraOverTime_Internal");
	}

	namespace Str
	{
		// Functions
		const FString ScaleActorOverTime_Internal = TEXT("UCsLibrary_Common::ScaleActorOverTime_Internal");
		const FString ScaleActorOverTime_AsCurve_Internal = TEXT("UCsLibrary_Common::ScaleActorOverTime_AsCurve_Internal");
		const FString MoveActorOverTime_Internal = TEXT("UCsLibrary_Common::MoveActorOverTime_Internal");
		const FString DestroyMaterialInstanceDynamic_Internal = TEXT("UCsLibrary_Common::DestroyMaterialInstanceDynamic_Internal");
		const FString FadeCameraOverTime_Internal = TEXT("UCsLibrary_Common::FadeCameraOverTime_Internal");

		const FString Client = TEXT("Client");
		const FString Server_Dedicated = TEXT("Server-Dedicated");
		const FString Server = TEXT("Server");
		const FString Unknown = TEXT("Unknown");
	}
}

#pragma endregion Cache

UCsLibrary_Common::UCsLibrary_Common(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

/*
bool UCsLibrary_Common::IsControlledByClient(AShooterCharacter* InPawn)
{
	return GetClientController(InPawn) != nullptr && UShooterStatics::GetMachineClientController(InPawn->GetWorld()) == GetClientController(InPawn);
}

AShooterPlayerController* UCsLibrary_Common::GetClientController(AShooterCharacter* InPawn)
{
	if (!InPawn || !InPawn->IsLocallyControlled())
		return nullptr;
	return InPawn->Controller ? Cast<AShooterPlayerController>(InPawn->Controller) : Cast<AShooterPlayerController>(InPawn->GetLinkedController());
}

AShooterPlayerController* UCsLibrary_Common::GetMachineClientController(UWorld *InWorld)
{
	check(InWorld);
	check(GEngine);

	return Cast<AShooterPlayerController>(GEngine->GetFirstLocalPlayerController(InWorld));
}

bool UCsLibrary_Common::IsLocallyControlled(AShooterCharacter* InPawn, UWorld* InWorld)
{
	check(InWorld);
	check(GEngine);

	if (!InPawn)
		return false;

	if (!InPawn->Controller)
		return false;

	TArray<APlayerController*> Controllers;

	GEngine->GetAllLocalPlayerControllers(Controllers);

	const int32 Count = Controllers.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		if (Controllers[Index] == InPawn->Controller)
			return true;
	}
	return false;
}
*/

// Local Client
#pragma region

AController* UCsLibrary_Common::GetLocalPlayerController(UWorld* InWorld)
{
	return GetLocalPlayerController<AController>(InWorld);
}

UPlayerInput* UCsLibrary_Common::GetLocalPlayerInput(UWorld* InWorld)
{
	APlayerController* Controller = GetLocalPlayerController<APlayerController>(InWorld);
	return Controller->PlayerInput;
}

APlayerState* UCsLibrary_Common::GetLocalPlayerState(UWorld* InWorld)
{
	return GetLocalPlayerState<APlayerState>(InWorld);
}

bool UCsLibrary_Common::IsLocalPlayerState(UWorld* InWorld, APlayerState* InPlayerState)
{
	if (!InPlayerState)
		return false;
	return InPlayerState == GetLocalPlayerState(InWorld);
}

bool UCsLibrary_Common::IsLocalPawn(UWorld* InWorld, APawn* InPawn)
{
	if (!InPawn)
		return false;
	if (!InPawn->GetPlayerState())
		return false;
	return InPawn->GetPlayerState() == GetLocalPlayerState(InWorld);
}

void UCsLibrary_Common::GetLocalPlayerViewPoint(UWorld* InWorld, FVector &OutLocation, FRotator &OutRotation)
{
	GetLocalPlayerViewPoint<APlayerController>(InWorld, OutLocation, OutRotation);
}

float UCsLibrary_Common::GetSquaredDistanceToLocalControllerEye(UWorld *InWorld, const FVector& Location)
{
	APlayerController* LocalController = GetLocalPlayerController<APlayerController>(InWorld);

	if (!LocalController)
		return -1.0f;

	FVector ViewLocation;
	FRotator ViewRotation;

	LocalController->GetPlayerViewPoint(ViewLocation, ViewRotation);

	return FVector::DistSquared(ViewLocation, Location);
}

ACsMotionController* UCsLibrary_Common::GetLocalHand(UWorld *InWorld, const ECsControllerHand &Hand)
{
	ACsPlayerPawn_VR* Pawn = GetLocalPawn<ACsPlayerPawn_VR>(InWorld);

	if (!Pawn)
		return nullptr;

	if (Hand == ECsControllerHand::Left)
		return Pawn->LeftHand;
	if (Hand == ECsControllerHand::Right)
		return Pawn->RightHand;
	return nullptr;
}

ACsManager_Inventory* UCsLibrary_Common::GetLocalManager_Inventory(UWorld *InWorld)
{
	ACsPlayerState* PlayerState = GetLocalPlayerState<ACsPlayerState>(InWorld);

	return PlayerState ? PlayerState->Manager_Inventory : nullptr;
}

#pragma endregion Local Client

// VR
#pragma region

bool UCsLibrary_Common::IsVR()
{
	return GEngine->StereoRenderingDevice.IsValid() && GEngine->IsStereoscopic3D();
}

bool UCsLibrary_Common::IsVive()
{
	// TODO: FIX:
	static const FName SteamVR(TEXT("SteamVR"));
	return GEngine->StereoRenderingDevice.IsValid() && GEngine->StereoRenderingDevice->IsStereoEnabled();// && GEngine->StereoRenderingDevice->GetHMDDeviceType() == SteamVR;
}

bool UCsLibrary_Common::IsRift()
{
	// TODO: FIX:
	static const FName OculusHMD(TEXT("OculusHMD"));
	return GEngine->StereoRenderingDevice.IsValid() && GEngine->StereoRenderingDevice->IsStereoEnabled();// && GEngine->StereoRenderingDevice->GetHMDDeviceType() == OculusHMD;
}

void UCsLibrary_Common::GetHMDOrientationAndPosition(FRotator& DeviceRotation, FVector& DevicePosition)
{
	// TODO: FIX:
	if (GEngine->StereoRenderingDevice.IsValid())// && GEngine->HMDDevice->IsHeadTrackingAllowed())
	{
		FQuat OrientationAsQuat;
		FVector Position(0.f);

		//GEngine->HMDDevice->GetCurrentOrientationAndPosition(OrientationAsQuat, Position);

		DeviceRotation = OrientationAsQuat.Rotator();
		DevicePosition = Position;
	}
	else
	{
		DeviceRotation = FRotator::ZeroRotator;
		DevicePosition = FVector::ZeroVector;
	}
}

void UCsLibrary_Common::GetHMDWorldViewPoint(UWorld* InWorld, FVector &OutLocation, FRotator& OutRotation)
{
	APlayerController* PlayerController = GetLocalPlayerController<APlayerController>(InWorld);
	
	PlayerController->GetPlayerViewPoint(OutLocation, OutRotation);
	// TODO: FIX:
	if (GEngine->StereoRenderingDevice.IsValid())// && GEngine->HMDDevice->IsHeadTrackingAllowed())
	{
		FQuat hmdOrientation;
		FVector hmdPosition;

		//GEngine->StereoRenderingDevice->GetCurrentOrientationAndPosition(hmdOrientation, hmdPosition);

		//if (GEngine->HMDDevice->GetHMDDeviceType() == EHMDDeviceType::DT_Morpheus)
		//	hmdPosition *= 100.0f;

		// get hmdPosition relative to hmdRotation's forward coordinate system - not the tracker's coordinate system
		// Example. headset is facing -X and moves head position 10 units in -X, the actual world location should be forward by 10 units

		const FVector X_Axis = hmdOrientation.GetAxisX();
		const FVector Y_Axis = hmdOrientation.GetAxisY();
		const FVector Z_Axis = hmdOrientation.GetAxisZ();

		FVector positionRelativeToHeadsetOrientation;
		positionRelativeToHeadsetOrientation.X = FVector::DotProduct(X_Axis, hmdPosition);
		positionRelativeToHeadsetOrientation.Y = FVector::DotProduct(Y_Axis, hmdPosition);
		positionRelativeToHeadsetOrientation.Z = FVector::DotProduct(Z_Axis, hmdPosition);

		//OutRotation = PlayerController->GetControlRotation();

		// now rotate the local position into player's world rotation
		FVector hmdWorldOffset(OutRotation.RotateVector(positionRelativeToHeadsetOrientation));
		OutLocation += hmdWorldOffset;
	}
}

ACsMotionController* UCsLibrary_Common::GetMotionController(UWorld* InWorld, const ECsControllerHand &Hand)
{
	ACsPlayerPawn_VR* Pawn = GetLocalPawn<ACsPlayerPawn_VR>(InWorld);

	if (!Pawn)
		return nullptr;

	return Hand == ECsControllerHand::Right ? Pawn->RightHand : Pawn->LeftHand;
}

// version of GEngine->IsStereoscopic3D() that is valid even during toggle frame. 
bool UCsLibrary_Common::IsStereoscopic3D()
{
	return false;
	//return GEngine && GEngine->StereoRenderingDevice.IsValid() && GEngine->StereoRenderingDevice->IsStereoEnabledOnNextFrame();
}

#pragma endregion

// Enum to String Conversion
#pragma region

FString UCsLibrary_Common::LoadFlagsToString(const int32 &LoadFlags)
{
	FString String = TEXT("");
	bool IsFirst = true;

	for (int32 I = 0; I < ECS_LOAD_FLAGS_EDITOR_MAX; ++I)
	{
		if (CS_TEST_BLUEPRINT_BITFLAG(LoadFlags, (ECsLoadFlags)I))
		{
			if (!IsFirst)
			{
				String += TEXT(" | ");
			}
			String += EMCsLoadFlags_Editor::Get().ToString((TCsLoadFlags_Editor)I);
			IsFirst = false;
		}
	}
	return String;
}

FString UCsLibrary_Common::InteractivePhysicsStateToString(const int32 &PhysicsState)
{
	FString String = TEXT("");
	bool IsFirst   = true;

	for (int32 I = 0; I < ECS_INTERACTIVE_PHYSICS_STATE_EDITOR_MAX; ++I)
	{
		if (CS_TEST_BLUEPRINT_BITFLAG(PhysicsState, (ECsInteractivePhysicsState)I))
		{
			if (!IsFirst)
			{
				String += TEXT(" | ");
			}
			String += ECsInteractivePhysicsState_Editor::ToString((TCsInteractivePhysicsState_Editor)I);
			IsFirst = false;
		}
	}
	return String;
}

#pragma endregion Enum to String Conversion

// Enum to Enum Conversion
#pragma region

ECsLoadFlags UCsLibrary_Common::ViewTypeToLoadFlags(const ECsViewType& ViewType, const bool& IsLow /*=false*/)
{
	if (ViewType == ECsViewType::FirstPerson)
		return ECsLoadFlags::Game1P;
	if (ViewType == ECsViewType::ThirdPerson)
		return IsLow ? ECsLoadFlags::Game3PLow : ECsLoadFlags::Game3P;
	if (ViewType == ECsViewType::VR)
		return ECsLoadFlags::GameVR;
	return ECsLoadFlags::All;
}

#pragma endregion Enum to Enum Conversion

// String
#pragma region

FString UCsLibrary_Common::Stream_GetString(const TCHAR*& Str, bool IsLowerCase)
{
	FString Arg;
	FParse::Token(Str, Arg, false);

	return IsLowerCase ? Arg.ToLower() : Arg;
}

FName UCsLibrary_Common::Stream_GetName(const TCHAR*& Str)
{
	return FName(*Stream_GetString(Str, false));
}

bool UCsLibrary_Common::Stream_GetBool(const TCHAR*& Str)
{
	FString Arg;
	FParse::Token(Str, Arg, false);

	const FString Bool = Arg.ToLower();

	if (Bool == TEXT("true") || Bool == TEXT("1"))
		return true;
	if (Bool == TEXT("false") || Bool == TEXT("0"))
		return false;
	return false;
}

int32 UCsLibrary_Common::Stream_GetBoolAsInt(const TCHAR*& Str)
{
	FString Arg = Stream_GetString(Str, true);

	if (Arg == TEXT("true") || Arg == TEXT("1"))
		return 1;
	if (Arg == TEXT("false") || Arg == TEXT("0"))
		return 0;
	return INDEX_NONE;
}

int32 UCsLibrary_Common::Stream_GetInt(const TCHAR*& Str)
{
	FString Arg;
	FParse::Token(Str, Arg, false);

	return FCString::Atoi(*Arg);
}

float UCsLibrary_Common::Stream_GetFloat(const TCHAR*& Str)
{
	FString Arg;
	FParse::Token(Str, Arg, false);

	return FCString::Atof(*Arg);
}

ERichCurveInterpMode UCsLibrary_Common::Stream_GetRichCurveInterpMode(const TCHAR*& Str)
{
	FString Arg = Stream_GetString(Str, true);
	return ECsRichCurveInterpMode::ToBaseType(Arg);
}

ERichCurveTangentMode UCsLibrary_Common::Stream_GetRichCurveTangentMode(const TCHAR*& Str)
{
	FString Arg = Stream_GetString(Str, true);
	return ECsRichCurveTangentMode::ToBaseType(Arg);
}

ECsViewType UCsLibrary_Common::Stream_GetViewType(const TCHAR*& Str)
{
	FString Arg;
	FParse::Token(Str, Arg, false);

	return EMCsViewType::Get().GetEnum(Arg);
}

#pragma endregion

// Data
#pragma region

UCsDataMapping* UCsLibrary_Common::GetDataMapping(UWorld* InWorld)
{
	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(InWorld->GetGameInstance());
	return GameInstance->DataMapping;
}

#pragma endregion Data

// Materials
#pragma region

void UCsLibrary_Common::SetMaterials(UStaticMeshComponent* InMesh, const TArray<UMaterialInstanceConstant*>& Materials)
{
	const int32 Count		  = InMesh->GetStaticMesh()->StaticMaterials.Num();
	const int32 MaterialCount = Materials.Num();

	if (Count > MaterialCount)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Common::SetMaterials: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *InMesh->GetStaticMesh()->GetName(), Count, MaterialCount);
		return;
	}

	ClearOverrideMaterials(InMesh);

	for (int32 Index = 0; Index < Count; Index++)
	{
		InMesh->SetMaterial(Index, Materials[Index]);
	}
}

void UCsLibrary_Common::SetMaterials(USkeletalMeshComponent* InMesh, const TArray<UMaterialInstanceConstant*>& Materials)
{
	const int32 Count		  = InMesh->SkeletalMesh->Materials.Num();
	const int32 MaterialCount = Materials.Num();

	if (Count > MaterialCount)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Common::SetMaterials: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *InMesh->SkeletalMesh->GetName(), Count, MaterialCount);
		return;
	}

	ClearOverrideMaterials(InMesh);

	for (int32 Index = 0; Index < Count; Index++)
	{
		InMesh->SetMaterial(Index, Materials[Index]);
	}
}

void UCsLibrary_Common::ClearOverrideMaterials(UStaticMeshComponent* InMesh)
{
	int32 Count = InMesh->OverrideMaterials.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(InMesh->OverrideMaterials[Index]))
		{
			if (!Material->IsPendingKill())
				Material->IsPendingKill();
		}
		InMesh->OverrideMaterials[Index] = nullptr;
	}

	InMesh->OverrideMaterials.SetNum(0, true);
}

void UCsLibrary_Common::ClearOverrideMaterials(USkeletalMeshComponent* InMesh)
{
	int32 Count = InMesh->OverrideMaterials.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(InMesh->OverrideMaterials[Index]))
		{
			if (!Material->IsPendingKill())
				Material->IsPendingKill();
		}
		InMesh->OverrideMaterials[Index] = nullptr;
	}

	InMesh->OverrideMaterials.SetNum(0, true);
}

void UCsLibrary_Common::DestroyMIDs(TArray<UMaterialInstanceDynamic*>& MIDs)
{
	int32 Count = MIDs.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		if (MIDs[Index] &&
			!MIDs[Index]->IsPendingKill())
		{
			MIDs[Index]->MarkPendingKill();
		}
	}
	MIDs.SetNum(0, true);
}

void UCsLibrary_Common::SetMIDs(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<FSkeletalMaterial>& Materials)
{
	ClearOverrideMaterials(InMesh);
	DestroyMIDs(MIDs);

	const int32 Count = Materials.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		MIDs.Add(InMesh->CreateDynamicMaterialInstance(Index, Materials[Index].MaterialInterface));
	}
}

void UCsLibrary_Common::SetMIDs(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInstanceConstant*>& Materials)
{
	ClearOverrideMaterials(InMesh);
	DestroyMIDs(MIDs);

	const int32 Count = Materials.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		MIDs.Add(InMesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
	}
}

void UCsLibrary_Common::SetMIDs(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials)
{
	ClearOverrideMaterials(InMesh);
	DestroyMIDs(MIDs);

	const int32 Count = Materials.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		MIDs.Add(InMesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
	}
}

void UCsLibrary_Common::MIDs_SetScalarParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float &Value)
{
	const int32 Count = MIDs.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		check(MIDs[Index]);

		if (MIDs[Index])
			MIDs[Index]->SetScalarParameterValue(ParamName, Value);
	}
}

void UCsLibrary_Common::MIDs_SetVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector &Value)
{
	const int32 Count = MIDs.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		check(MIDs[Index]);

		if (MIDs[Index])
			MIDs[Index]->SetVectorParameterValue(ParamName, Value);
	}
}

void UCsLibrary_Common::MIDs_SetVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor &Value)
{
	const int32 Count = MIDs.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		check(MIDs[Index]);

		if (MIDs[Index])
			MIDs[Index]->SetVectorParameterValue(ParamName, Value);
	}
}

#pragma endregion Materials

FVector UCsLibrary_Common::GetBoneLocation(USkeletalMeshComponent* InMesh, const int32 &BoneIndex, const TEnumAsByte<EBoneSpaces::Type> &Space)
{
	if (BoneIndex <= INDEX_NONE)
	{
		UE_LOG(LogAnimation, Log, TEXT("UShooterStatics::GetBoneLocation: BoneIndex <= INDEX_NONE. Not a Valid BoneIndex."));
		return FVector::ZeroVector;
	}

	if (BoneIndex >= InMesh->GetNumBones())
	{
		UE_LOG(LogAnimation, Log, TEXT("UShooterStatics::GetBoneLocation: BoneIndex >= Maximum Bone Count. Not a Valid BoneIndex."));
		return FVector::ZeroVector;
	}

	if (Space == EBoneSpaces::ComponentSpace)
	{
		/*
		const USkinnedMeshComponent* const MasterPoseComponentInst = MasterPoseComponent.Get();
		if (MasterPoseComponentInst)
		{
			if (BoneIndex < MasterBoneMap.Num())
			{
				int32 ParentBoneIndex = MasterBoneMap[BoneIndex];
				// If ParentBoneIndex is valid, grab transform from MasterPoseComponent.
				if (ParentBoneIndex != INDEX_NONE &&
					ParentBoneIndex < MasterPoseComponentInst->GetNumSpaceBases())
				{
					return MasterPoseComponentInst->GetSpaceBases()[ParentBoneIndex].GetLocation();
				}
			}

			// return empty vector
			return FVector::ZeroVector;
		}
		*/
		return InMesh->GetComponentSpaceTransforms()[BoneIndex].GetLocation();
	}
	else if (Space == EBoneSpaces::WorldSpace)
	{
		// To support non-uniform scale (via LocalToWorld), use GetBoneMatrix
		return InMesh->GetBoneMatrix(BoneIndex).GetOrigin();
	}
	return FVector::ZeroVector;
}

FName UCsLibrary_Common::GetParentBone(USkeletalMeshComponent* InMesh, const int32 &BoneIndex)
{
	FName Result = NAME_None;

	if ((BoneIndex != INDEX_NONE) && (BoneIndex > 0)) // This checks that this bone is not the root (ie no parent), and that BoneIndex != INDEX_NONE (ie bone name was found)
	{
		Result = InMesh->SkeletalMesh->RefSkeleton.GetBoneName(InMesh->SkeletalMesh->RefSkeleton.GetParentIndex(BoneIndex));
	}
	return Result;
}

void UCsLibrary_Common::CopyHitResult(const FHitResult& From, FHitResult& To)
{
	To.bBlockingHit = From.bBlockingHit;
	To.bStartPenetrating = From.bStartPenetrating;
	To.Time = From.Time;
	To.Distance = From.Distance;
	To.Location = From.Location;
	To.ImpactPoint = From.ImpactPoint;
	To.Normal = From.Normal;
	To.ImpactNormal = From.ImpactNormal;
	To.TraceStart = From.TraceStart;
	To.TraceEnd = From.TraceEnd;
	To.PenetrationDepth = From.PenetrationDepth;
	To.Item = From.Item;
	To.PhysMaterial = From.PhysMaterial;
	To.Actor = From.Actor;
	To.Component = From.Component;
	To.BoneName = From.BoneName;
	To.FaceIndex = From.FaceIndex;
}

void UCsLibrary_Common::SetHitResult(FHitResult* InHitResult, FHitResult* OutHitResult)
{
	OutHitResult->bBlockingHit = InHitResult->bBlockingHit;
	OutHitResult->bStartPenetrating = InHitResult->bStartPenetrating;
	OutHitResult->Time = InHitResult->Time;
	OutHitResult->Location = InHitResult->Location;
	OutHitResult->Normal = InHitResult->Normal;
	OutHitResult->ImpactPoint = InHitResult->ImpactPoint;
	OutHitResult->ImpactNormal = InHitResult->ImpactNormal;
	OutHitResult->TraceStart = InHitResult->TraceStart;
	OutHitResult->TraceEnd = InHitResult->TraceEnd;
	OutHitResult->PenetrationDepth = InHitResult->PenetrationDepth;
	OutHitResult->Item = InHitResult->Item;
	OutHitResult->PhysMaterial = InHitResult->PhysMaterial;
	OutHitResult->Actor = InHitResult->Actor;
	OutHitResult->Component = InHitResult->Component;
	OutHitResult->BoneName = InHitResult->BoneName;
	OutHitResult->FaceIndex = InHitResult->FaceIndex;
}

void UCsLibrary_Common::CopyCollisionObjectQueryParams(const FCollisionObjectQueryParams& From, FCollisionObjectQueryParams& To)
{
	To.ObjectTypesToQuery = From.ObjectTypesToQuery;
	To.IgnoreMask = From.IgnoreMask;
}

bool UCsLibrary_Common::IsMatchInProgress(UWorld *InWorld)
{
	AGameState* GameState = Cast<AGameState>(InWorld->GetGameState());

	if (!GameState)
		return false;

	if (GameState->GetMatchState() != MatchState::InProgress)
		return false;
	return true;
}

// Math
#pragma region

float UCsLibrary_Common::GetAngleDelta(const float &Angle1, const float &Angle2)
{
	const int32 Mag			= Angle2 - Angle1 > 0 ? 1 : -1;
	const float DeltaAngle	= Angle2 - Angle1;

	return FMath::Abs(DeltaAngle) > 180.0f ? -1 * Mag * (360.0f - FMath::Abs(DeltaAngle)) : Mag * FMath::Abs(DeltaAngle);
}

FRotator UCsLibrary_Common::GetAngleDelta(const FRotator &A, const FRotator &B)
{
	FRotator Rotation;

	Rotation.Pitch = GetAngleDelta(A.Pitch, B.Pitch);
	Rotation.Yaw = GetAngleDelta(A.Yaw, B.Yaw);
	Rotation.Roll = GetAngleDelta(A.Roll, B.Roll);

	return Rotation;
}

FRotator UCsLibrary_Common::Rotator_GetAngleDelta(const FRotator &A, const FRotator &B)
{
	return GetAngleDelta(A, B);
}

float UCsLibrary_Common::GetAbsAngleDelta(const float &Angle1, const float &Angle2)
{
	const float DeltaAngle = Angle2 - Angle1;
	const int32 Mag		   = DeltaAngle > 0 ? 1 : -1;

	return FMath::Abs(FMath::Abs(DeltaAngle) > 180.0f ? -1 * Mag * (360.0f - FMath::Abs(DeltaAngle)) : Mag * FMath::Abs(DeltaAngle));
}

FRotator UCsLibrary_Common::GetAbsAngleDelta(const FRotator &A, const FRotator &B)
{
	FRotator Rotation;

	Rotation.Pitch = GetAbsAngleDelta(A.Pitch, B.Pitch);
	Rotation.Yaw = GetAbsAngleDelta(A.Yaw, B.Yaw);
	Rotation.Roll = GetAbsAngleDelta(A.Roll, B.Roll);

	return Rotation;
}

FRotator UCsLibrary_Common::Rotator_GetAbsAngleDelta(const FRotator &A, const FRotator &B)
{
	return GetAbsAngleDelta(A, B);
}

float UCsLibrary_Common::AngleClamp180(float Angle)
{
	while (Angle < -180.0f){ Angle += 360.0f; }
	while (Angle > 180.0f){ Angle -= 360.0f; }
	return Angle;
}

FRotator UCsLibrary_Common::AngleClamp180(const FRotator &Rotation)
{
	return FRotator(AngleClamp180(Rotation.Pitch), AngleClamp180(Rotation.Yaw), AngleClamp180(Rotation.Roll));
}

float UCsLibrary_Common::AngleClamp360(float Angle)
{
	while (Angle < 0.0f){ Angle += 360.0f; }
	while (Angle > 360.0f){ Angle -= 360.0f; }
	return Angle;
}

FRotator UCsLibrary_Common::AngleClamp360(const FRotator &Rotation)
{
	return FRotator(AngleClamp360(Rotation.Pitch), AngleClamp360(Rotation.Yaw), AngleClamp360(Rotation.Roll));
}

float UCsLibrary_Common::LerpAngle(const float &FromAngle, const float &ToAngle, const float &LerpRate, const float &DeltaSeconds, float MinAngle, float MaxAngle)
{
	float DeltaAngle	   = UCsLibrary_Common::GetAngleDelta(FromAngle, ToAngle);
	const float SmallDelta = 0.001f;
	float Percent		   = FMath::Abs(DeltaAngle) > SmallDelta ? FMath::Clamp((LerpRate * DeltaSeconds) / FMath::Abs(DeltaAngle), 0.0f, 1.0f) : 1.0f;

	MinAngle = UCsLibrary_Common::AngleClamp360(MinAngle);

	if (MinAngle > MaxAngle)
	{
		float Temp = MaxAngle;
		MaxAngle   = MinAngle;
		MinAngle   = Temp;
	}
	return FMath::Clamp(UCsLibrary_Common::AngleClamp360(FromAngle + Percent * DeltaAngle), MinAngle, MaxAngle);
}

int32 UCsLibrary_Common::Mod(const int32 &A, const int32 &B)
{
	const int32 C = A % B;
	return C < 0 ? C + B : C;
}

FVector UCsLibrary_Common::BuildUniformVector(const FVector &V, const int32 &Axes)
{
	if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_X))
		return FVector(V.X);
	if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Y))
		return FVector(V.Y);
	if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Z))
		return FVector(V.Z);
	return FVector::ZeroVector;
}

FRotator UCsLibrary_Common::BuildUniformRotator(const FRotator &R, const int32 &Axes)
{
	if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_ROLL))
		return FRotator(R.Roll);
	if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_PITCH))
		return FRotator(R.Pitch);
	if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_YAW))
		return FRotator(R.Yaw);
	return FRotator::ZeroRotator;
}

int32 UCsLibrary_Common::GetNumBitFlags(const int32 &BitMask, const int32 &MaxBits)
{
	int32 Bits = 0;

	for (int32 I = 0; I < MaxBits; ++I)
	{
		if (CS_TEST_BLUEPRINT_BITFLAG(BitMask, I))
			Bits++;
	}
	return Bits;
}

FString UCsLibrary_Common::UInt64ToString(const uint64 &Value)
{
	// 18,446,744,073,709,551,615
	const uint8 MAX_UINT64_DIGITS = 20;

	uint8 Digits = 0;
	float ValueDivided = (float)Value;

	while (ValueDivided >= 1.0f)
	{
		ValueDivided /= 10.0f;
		Digits++;
	}

	FString Zeroes	  = TEXT("");
	const uint8 Count = MAX_UINT64_DIGITS - Digits;

	for (uint8 I = 0; I < Count; ++I)
	{
		Zeroes += TEXT("0");
	}

	return Zeroes + FString::Printf(TEXT("%llu"), Value);
}

FVector UCsLibrary_Common::ClampVectorComponents(FVector V, const float &Clamp)
{
	V.X = FMath::Abs(V.X) < Clamp ? FMath::Sign(V.X) * Clamp : V.X;
	V.Y = FMath::Abs(V.Y) < Clamp ? FMath::Sign(V.Y) * Clamp : V.Y;
	V.Y = FMath::Abs(V.Z) < Clamp ? FMath::Sign(V.Z) * Clamp : V.Z;

	return V;
}

void UCsLibrary_Common::ClampMinVectorComponents(FVector &V, const float &Min)
{
	V.X = FMath::Max(V.X, Min);
	V.Y = FMath::Max(V.Y, Min);
	V.Z = FMath::Max(V.Z, Min);
}

void UCsLibrary_Common::ClampMaxVectorComponents(FVector &V, const float &Max)
{
	V.X = FMath::Min(V.X, Max);
	V.Y = FMath::Min(V.Y, Max);
	V.Z = FMath::Min(V.Z, Max);
}

#pragma endregion Math

/*
bool UCsLibrary_Common::IsOnSameTeam(UWorld *InWorld, AShooterCharacter* InPawnA, AShooterCharacter* InPawnB)
{
	check(InWorld);

	AShooterGameState* GameState = Cast<AShooterGameState>(InWorld->GetGameState());

	if (!GameState)
		return false;

	if (InPawnA && InPawnA == InPawnB)
		return true;

	if (Cast<AShooterGameState_FFA>(GameState))
		return false;

	if (!InPawnA || !InPawnB)
		return false;

	AShooterPlayerState* PlayerStateA = InPawnA->GetLinkedPlayerState();
	AShooterPlayerState* PlayerStateB = InPawnB->GetLinkedPlayerState();

	if (!PlayerStateA || !PlayerStateB)
		return false;
	return PlayerStateA->GetTeamNum() == PlayerStateB->GetTeamNum();
}

bool UCsLibrary_Common::IsOnSameTeam(UWorld *InWorld, AShooterPlayerState* InPlayerStateA, AShooterCharacter* InPawnB)
{
	check(InWorld);

	AShooterGameState* GameState = Cast<AShooterGameState>(InWorld->GetGameState());

	if (!GameState)
		return false;

	if (!InPlayerStateA || !InPawnB)
		return false;

	AShooterPlayerState* PlayerStateB = InPawnB->GetLinkedPlayerState();

	if (!InPlayerStateA || !PlayerStateB)
		return false;

	if (InPlayerStateA && InPlayerStateA == PlayerStateB)
		return true;

	if (Cast<AShooterGameState_FFA>(GameState))
		return false;

	if (InPlayerStateA->GetTeamNum() == PlayerStateB->GetTeamNum())
		return true;
	return false;
}

bool UCsLibrary_Common::IsOnSameTeam(UWorld *InWorld, AShooterPlayerState* InPlayerStateA, AShooterPlayerState* InPlayerStateB)
{
	check(InWorld);

	AShooterGameState* GameState = Cast<AShooterGameState>(InWorld->GetGameState());

	if (!GameState)
		return false;

	if (!InPlayerStateA || !InPlayerStateB)
		return false;

	if (InPlayerStateA == InPlayerStateB)
		return true;

	if (Cast<AShooterGameState_FFA>(GameState))
		return false;

	return InPlayerStateA->GetTeamNum() == InPlayerStateB->GetTeamNum();
}
*/
FVector UCsLibrary_Common::GetScaledPlayerViewDirection(AController* Controller, const FVector &Scale)
{
	if (!Controller)
		return FVector::ZeroVector;

	FVector Origin;
	FRotator Rotation;

	Controller->GetPlayerViewPoint(Origin, Rotation);

	Rotation.Pitch = 0.0f;
	Rotation.Roll  = 0.0f;

	FRotationMatrix Matrix = FRotationMatrix(Rotation);
	const FVector Forward  = Scale.X * Matrix.GetScaledAxis(EAxis::X);
	const FVector Right	   = Scale.Y * Matrix.GetScaledAxis(EAxis::Y);
	const FVector Up	   = Scale.Z * Matrix.GetScaledAxis(EAxis::Z);

	return Forward + Right + Up;
}
/*
void UCsLibrary_Common::GetHMDWorldViewPoint(APlayerController* PlayerController, FVector& out_Location, FRotator& out_Rotation)
{
	check(PlayerController);

	PlayerController->GetPlayerViewPoint(out_Location, out_Rotation);

	if (UShooterStatics::IsStereoscopic3D() && PlayerController->IsLocalPlayerController())
	{
		FQuat hmdOrientation;
		FVector hmdPosition;

		GEngine->HMDDevice->GetCurrentOrientationAndPosition(hmdOrientation, hmdPosition);

		if (GEngine->HMDDevice->GetHMDDeviceType() == EHMDDeviceType::DT_Morpheus)
			hmdPosition *= 100.0f;

		// get hmdPosition relative to hmdRotation's forward coordinate system - not the tracker's coordinate system
		// Example. headset is facing -X and moves head position 10 units in -X, the actual world location should be forward by 10 units

		const FVector X_Axis = hmdOrientation.GetAxisX();
		const FVector Y_Axis = hmdOrientation.GetAxisY();
		const FVector Z_Axis = hmdOrientation.GetAxisZ();

		FVector positionRelativeToHeadsetOrientation;
		positionRelativeToHeadsetOrientation.X = FVector::DotProduct(X_Axis, hmdPosition);
		positionRelativeToHeadsetOrientation.Y = FVector::DotProduct(Y_Axis, hmdPosition);
		positionRelativeToHeadsetOrientation.Z = FVector::DotProduct(Z_Axis, hmdPosition);

		out_Rotation = PlayerController->GetControlRotation();

		// now rotate the local position into player's world rotation
		FVector hmdWorldOffset(out_Rotation.RotateVector(positionRelativeToHeadsetOrientation));
		out_Location += hmdWorldOffset;
	}
}
*/

// Easing
#pragma region

float UCsLibrary_Common::Ease(const ECsEasingType &EasingType, const float &Time, const float &Start, const float &Final, const float &Duration)
{
	if (EasingType == ECsEasingType::Linear)
		return Linear(Time, Start, Final, Duration);
	if (EasingType == ECsEasingType::BounceIn)
		return BounceEaseIn(Time, Start, Final, Duration);
	if (EasingType == ECsEasingType::BounceOut)
		return BounceEaseOut(Time, Start, Final, Duration);
	if (EasingType == ECsEasingType::BounceInOut)
		return BounceEaseInOut(Time, Start, Final, Duration);
	if (EasingType == ECsEasingType::CubicIn)
		return CubicEaseIn(Time, Start, Final, Duration);
	if (EasingType == ECsEasingType::CubicOut)
		return CubicEaseOut(Time, Start, Final, Duration);
	if (EasingType == ECsEasingType::CubicInOut)
		return CubicEaseInOut(Time, Start, Final, Duration);
	if (EasingType == ECsEasingType::ExpoIn)
		return ExpoEaseIn(Time, Start, Final, Duration);
	if (EasingType == ECsEasingType::ExpoOut)
		return ExpoEaseOut(Time, Start, Final, Duration);
	if (EasingType == ECsEasingType::ExpoInOut)
		return ExpoEaseInOut(Time, Start, Final, Duration);
	return Linear(Time, Start, Final, Duration);
}

float UCsLibrary_Common::Linear(const float &Time, const float &Start, const float &Final, const float &Duration)
{
	return ((Final * Time) / Duration) + Start;
}

float UCsLibrary_Common::BounceEaseOut(const float &Time, const float &Start, const float &Final, const float &Duration)
{
	float T = Time;

	T /= Duration;

	if (T < (1 / 2.75f))
	{
		return Final * (7.5625f * T * T) + Start;
	}
	else if (Time < (2.0f / 2.75f))
	{
		T -= (1.5f / 2.75f);
		return Final * (7.5625f * T * T + 0.75f) + Start;
	}
	else if (Time < (2.5f / 2.75f))
	{
		T -= (2.25f / 2.75f);
		return Final * (7.5625f * T * T + 0.9375f) + Start;
	}
	else
	{
		T -= (2.625f / 2.75f);
		return Final * (7.5625f * T * T + 0.984375f) + Start;
	}
}

float UCsLibrary_Common::BounceEaseIn(const float &Time, const float &Start, const float &Final, const float &Duration)
{
	return Final - BounceEaseOut(Duration - Time, 0, Final, Duration) + Start;
}

float UCsLibrary_Common::BounceEaseInOut(const float &Time, const float &Start, const float &Final, const float &Duration)
{
	if (Time < (Duration / 2.0f))
		return (BounceEaseIn(Time * 2, 0, Final, Duration) * 0.5f) + Start;
	else
		return (BounceEaseOut(Time * 2 - Duration, 0, Final, Duration) * 0.5f) + Final * 0.5f + Start;
}

float UCsLibrary_Common::CubicEaseIn(const float &Time, const float &Start, const float &Final, const float &Duration)
{
	float T = Time;
	T /= Duration;
	return Final * T * T * T + Start;
}

float UCsLibrary_Common::CubicEaseOut(const float &Time, const float &Start, const float &Final, const float &Duration)
{
	float T = Time;
	T = (T / Duration) - 1.0f;
	return Final * ((T *  T * T) + 1) + Start;
}

float UCsLibrary_Common::CubicEaseInOut(const float &Time, const float &Start, const float &Final, const float &Duration)
{
	float T = Time;

	if ((T / (Duration / 2.0f)) < 1)
	{
		T /= Duration / 2.0f;
		return (Final / (2.0f * T * T * T)) + Start;
	}
	T -= 2.0f;
	return (Final / (2 * T * T * T + 2)) + Start;
}

float UCsLibrary_Common::ExpoEaseIn(const float &Time, const float &Start, const float &Final, const float &Duration)
{
	return (Time == 0.0f) ? Start : Final * FMath::Pow(2.0f, 10.0f * (Time / Duration - 1.0f)) + Start;
}

float UCsLibrary_Common::ExpoEaseOut(const float &Time, const float &Start, const float &Final, const float &Duration)
{
	return (Time == Duration) ? Start + Final : Final * (-1.0f * FMath::Pow(2.0f, -10.0f * Time / Duration) + 1.0f) + Start;
}

float UCsLibrary_Common::ExpoEaseInOut(const float &Time, const float &Start, const float &Final, const float &Duration)
{
	float T = Time;

	if (T == 0)
		return Start;
	if (T == Duration)
		return Start + Final;
	if (Duration / 2.0f < 1.0f)
	{
		T /= Duration / 2.0f;
		return (Final / 2.0f) * FMath::Pow(2.0f, 10 * (T - 1.0f)) + Start;
	}
	T--;
	return (Final / 2.0f) * (-FMath::Pow(2.0f, -10.0f * T) + 2.0f) + Start;
}

TCsEasingFunction UCsLibrary_Common::GetEasingFunction(const ECsEasingType &EasingType)
{
	if (EasingType == ECsEasingType::Linear)
		return &UCsLibrary_Common::Linear;
	if (EasingType == ECsEasingType::BounceIn)
		return &UCsLibrary_Common::BounceEaseIn;
	if (EasingType == ECsEasingType::BounceOut)
		return &UCsLibrary_Common::BounceEaseOut;
	if (EasingType == ECsEasingType::BounceInOut)
		return &UCsLibrary_Common::BounceEaseInOut;
	if (EasingType == ECsEasingType::CubicIn)
		return &UCsLibrary_Common::CubicEaseIn;
	if (EasingType == ECsEasingType::CubicOut)
		return &UCsLibrary_Common::CubicEaseOut;
	if (EasingType == ECsEasingType::CubicInOut)
		return &UCsLibrary_Common::CubicEaseInOut;
	if (EasingType == ECsEasingType::ExpoIn)
		return &UCsLibrary_Common::ExpoEaseIn;
	if (EasingType == ECsEasingType::ExpoOut)
		return &UCsLibrary_Common::ExpoEaseOut;
	if (EasingType == ECsEasingType::ExpoInOut)
		return &UCsLibrary_Common::ExpoEaseInOut;
	return &UCsLibrary_Common::Linear;
}

#pragma endregion Easing

void UCsLibrary_Common::GetKeyValue(const FString& Pair, FString& Key, FString& Value, const TCHAR* PairDelimiter)
{
	const int32 pairSignIndex = Pair.Find(PairDelimiter, ESearchCase::CaseSensitive);
	if (pairSignIndex != INDEX_NONE)
	{
		Key = Pair.Left(pairSignIndex);
		Value = Pair.Mid(pairSignIndex + FCString::Strlen(PairDelimiter), MAX_int32);
	}
	else
	{
		Key = Pair;
		Value = TEXT("");
	}
}

bool UCsLibrary_Common::GrabOption(FString& Options, FString& Result)
{
	if (Options.Left(1) == TEXT("?"))
	{
		// Get result.
		Result = Options.Mid(1, MAX_int32);
		if (Result.Contains(TEXT("?"), ESearchCase::CaseSensitive))
		{
			Result = Result.Left(Result.Find(TEXT("?"), ESearchCase::CaseSensitive));
		}

		// Update options.
		Options = Options.Mid(1, MAX_int32);
		if (Options.Contains(TEXT("?"), ESearchCase::CaseSensitive))
		{
			Options = Options.Mid(Options.Find(TEXT("?"), ESearchCase::CaseSensitive), MAX_int32);
		}
		else
		{
			Options = TEXT("");
		}

		return true;
	}
	else
	{
		return false;
	}
}

FString UCsLibrary_Common::ParseOption(const FString& Options, const FString& InKey)
{
	FString Pair, Key, Value;

	int32 optionsStartIndex = Options.Find(TEXT("?"));

	if (optionsStartIndex == INDEX_NONE)
		return TEXT("");

	FString OptionsMod = Options.RightChop(optionsStartIndex);

	while (GrabOption(OptionsMod, Pair))
	{
		GetKeyValue(Pair, Key, Value);
		if (FCString::Stricmp(*Key, *InKey) == 0)
			return Value;
	}
	return TEXT("");
}

bool UCsLibrary_Common::IsValidFpsAnimMontageArray(TArray<FCsFpvAnimMontage>& InArray, const ECsViewType& ViewType, const bool& IsLow)
{
	const int32 Count = InArray.Num();

	if (Count == 0)
		return false;

	for (int32 Index = 0; Index < Count; Index++)
	{
		if (!InArray[Index].Get(ViewType, IsLow))
			return false;
	}
	return true;
}

// Component
#pragma region

void UCsLibrary_Common::InitComponent(USceneComponent* Component, USceneComponent* RootComponent, const ECollisionChannel& Channel, const ECsViewType& ViewType /*=ECsViewType::ECsViewType_MAXv*/)
{
	// Mesh Component
	if (UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Component))
	{
		Mesh->SetHiddenInGame(true);
		Mesh->SetVisibility(true);

		if (ViewType == ECsViewType::FirstPerson)
		{
			Mesh->SetOnlyOwnerSee(true);
			Mesh->SetOwnerNoSee(false);
		}
		if (ViewType == ECsViewType::ThirdPerson)
		{
			Mesh->SetOnlyOwnerSee(false);
			Mesh->SetOwnerNoSee(true);
		}
		Mesh->SetCollisionObjectType(Channel);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		Mesh->SetMobility(EComponentMobility::Movable);
		Mesh->SetCastShadow(false);
		Mesh->bCastDynamicShadow = false;

		if (RootComponent)
			Mesh->SetupAttachment(RootComponent);
	}
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(Component))
	{
		Mesh->SetHiddenInGame(true);
		Mesh->bVisible		= false;

		if (ViewType == ECsViewType::FirstPerson)
		{
			Mesh->SetOnlyOwnerSee(true);
			Mesh->SetOwnerNoSee(false);
		}
		if (ViewType == ECsViewType::ThirdPerson)
		{
			Mesh->SetOnlyOwnerSee(false);
			Mesh->SetOwnerNoSee(true);
		}
		Mesh->bReceivesDecals = false;
		Mesh->SetEnableGravity(false);
		Mesh->SetCollisionObjectType(Channel);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		Mesh->SetCastShadow(false);
		Mesh->bCastDynamicShadow = false;
		Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;

		if (RootComponent)
			Mesh->SetupAttachment(RootComponent);

		Mesh->SetGenerateOverlapEvents(false);
	}
	// Text Render Component
	if (UTextRenderComponent* Text = Cast<UTextRenderComponent>(Component))
	{
		Text->SetHiddenInGame(true);
		Text->SetVisibility(false);

		if (ViewType == ECsViewType::FirstPerson)
		{
			Text->SetOnlyOwnerSee(true);
			Text->SetOwnerNoSee(false);
		}
		if (ViewType == ECsViewType::ThirdPerson)
		{
			Text->SetOnlyOwnerSee(false);
			Text->SetOwnerNoSee(true);
		}
		Text->SetCollisionObjectType(ECC_Visibility);
		Text->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Text->SetCollisionResponseToAllChannels(ECR_Ignore);
		Text->SetMobility(EComponentMobility::Movable);
		Text->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);

		if (RootComponent)
			Text->SetupAttachment(RootComponent);
	}
	// Box Component
	if (UBoxComponent* Box = Cast<UBoxComponent>(Component))
	{
		Box->SetGenerateOverlapEvents(false);
		Box->SetNotifyRigidBodyCollision(false);
		Box->SetCollisionObjectType(Channel);
		Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Box->SetCollisionResponseToAllChannels(ECR_Ignore);

		if (RootComponent)
			Box->SetupAttachment(RootComponent);
	}
	// Sphere Component
	if (USphereComponent* Sphere = Cast<USphereComponent>(Component))
	{
		Sphere->SetGenerateOverlapEvents(false);
		Sphere->SetNotifyRigidBodyCollision(false);
		Sphere->SetCollisionObjectType(Channel);
		Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);

		if (RootComponent)
			Sphere->SetupAttachment(RootComponent);
	}
	Component->Deactivate();
}

void UCsLibrary_Common::EnableComponent(USceneComponent* Component, const bool &SetUpdateFlag /*=false*/)
{
	Component->Activate();
	Component->SetComponentTickEnabled(true);

	// Motion Controller Component
	if (UMotionControllerComponent* Motion = Cast<UMotionControllerComponent>(Component))
	{
	}
	// Mesh Component
	if (UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Component))
	{
		Mesh->SetHiddenInGame(false);
		Mesh->SetVisibility(true);
	}
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(Component))
	{
		Mesh->SetHiddenInGame(false);
		Mesh->SetVisibility(true);

		if (SetUpdateFlag)
		{
			Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
		}
	}
	// Sphere Component
	if (USphereComponent* Sphere = Cast<USphereComponent>(Component))
	{
		Sphere->SetHiddenInGame(false);
		Sphere->SetVisibility(true);
		Sphere->SetOnlyOwnerSee(true);
		Sphere->SetOwnerNoSee(true);
	}
	// Text Render Component
	if (UTextRenderComponent* Text = Cast<UTextRenderComponent>(Component))
	{
		Text->SetHiddenInGame(false);
		Text->SetVisibility(true);
	}
}

void UCsLibrary_Common::DisableComponent(USceneComponent* Component, const bool &Detach /*=false*/, const bool &DisableCollision /*=false*/, const bool &SetUpdateFlag /*=false*/)
{
	if (Detach)
	{
		Component->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}

	// Motion Controller Component
	if (UMotionControllerComponent* Motion = Cast<UMotionControllerComponent>(Component))
	{
		Motion->SetComponentTickEnabled(false);
	}
	// Mesh Component
	if (UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Component))
	{
		Mesh->SetHiddenInGame(true);
		Mesh->SetVisibility(false);
		Mesh->SetComponentTickEnabled(false);
		Mesh->PrimaryComponentTick.bStartWithTickEnabled = false;
	}
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(Component))
	{
		Mesh->SetHiddenInGame(true);
		Mesh->SetVisibility(false);

		if (SetUpdateFlag)
		{
			Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
		}
		Mesh->SetComponentTickEnabled(false);
		Mesh->PrimaryComponentTick.bStartWithTickEnabled = false;

		if (DisableCollision)
		{
			Mesh->KinematicBonesUpdateType = EKinematicBonesUpdateToPhysics::SkipAllBones;

			Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		}

		if (UAnimInstance* AnimInstance = Mesh->GetAnimInstance())
		{
			AnimInstance->Montage_Stop(0.0f);
		}
		else
		{
			Mesh->Stop();
		}
		Mesh->HandleExistingParallelEvaluationTask(true, false);
		Mesh->SetAnimInstanceClass(nullptr);
	}
	// Text Render Component
	if (UTextRenderComponent* Text = Cast<UTextRenderComponent>(Component))
	{
		Text->SetHiddenInGame(true);
		Text->SetVisibility(false);
		Text->SetComponentTickEnabled(false);
	}
	// Box Component
	if (UBoxComponent* Box = Cast<UBoxComponent>(Component))
	{
		Box->SetHiddenInGame(true);
		Box->SetVisibility(false);
		Box->SetComponentTickEnabled(false);

		if (DisableCollision)
		{
			Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Box->SetCollisionResponseToAllChannels(ECR_Ignore);
		}
	}
	// Sphere Component
	if (USphereComponent* Sphere = Cast<USphereComponent>(Component))
	{
		Sphere->SetHiddenInGame(true);
		Sphere->SetVisibility(false);
		Sphere->SetComponentTickEnabled(false);

		if (DisableCollision)
		{
			Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
		}
	}
	Component->Deactivate();
}

void UCsLibrary_Common::ClearComponent(USceneComponent* Component)
{
	// Mesh Component
	if (UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Component))
	{
		ClearOverrideMaterials(Mesh);
		Mesh->SetStaticMesh(nullptr);
	}
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(Component))
	{
		ClearOverrideMaterials(Mesh);
		Mesh->SetSkeletalMesh(nullptr);
	}
}

bool UCsLibrary_Common::CanDetachFromComponent(USceneComponent* Component)
{
	if (Component->GetAttachParent() &&
		Component->IsRegistered() &&
		Component->GetAttachParent()->GetAttachChildren().Num() > 0 &&
		Component->GetAttachParent()->GetAttachChildren().Contains(Component))
	{
		return true;
	}
	return false;
}

bool UCsLibrary_Common::CanDetachFromComponent(USceneComponent* Component, USceneComponent* Parent)
{
	if (Component->GetAttachParent() == Parent &&
		Component->IsRegistered() &&
		Component->GetAttachParent()->GetAttachChildren().Num() > 0 &&
		Component->GetAttachParent()->GetAttachChildren().Contains(Component))
	{
		return true;
	}
	return false;
}

void UCsLibrary_Common::SafeDetachFromComponent(USceneComponent* Component)
{
	if (CanDetachFromComponent(Component))
	{
		Component->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}

void UCsLibrary_Common::SafeDetachFromComponent(USceneComponent* Component, USceneComponent* Parent)
{
	if (CanDetachFromComponent(Component, Parent))
	{
		Component->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}

bool UCsLibrary_Common::CanAttachToComponent(USceneComponent* Component)
{
	return !Component->GetAttachParent() && Component->IsRegistered();
}

void UCsLibrary_Common::ToggleEditorIcons(AActor* InActor, const bool &IsVisible)
{
#if WITH_EDITOR
	// Emitter
	if (AEmitter* Emitter = Cast<AEmitter>(InActor))
	{
		Emitter->GetSpriteComponent()->SetVisibility(IsVisible);
		Emitter->GetSpriteComponent()->SetHiddenInGame(!IsVisible);
		Emitter->GetArrowComponent()->SetVisibility(IsVisible);
		Emitter->GetArrowComponent()->SetHiddenInGame(!IsVisible);
	}
	// Sound
	/*
	if (AShooterSound* Sound = Cast<AShooterSound>(InActor))
	{
		Sound->AudioComponent->SetVisibility(IsVisible);
		Sound->AudioComponent->SetHiddenInGame(!IsVisible);
	}
	*/
#endif // #if WITH_EDITOR
}

#pragma endregion Component

// Animation
#pragma region

void UCsLibrary_Common::ConvertBoneSpaceTransformToComponentSpace(const FTransform& ComponentTransform, USkinnedMeshComponent* Mesh, FTransform& OutTransform, const FName &BoneName, const EBoneControlSpace &Space)
{
	const int32 BoneIndex = Mesh->GetBoneIndex(BoneName);

	switch (Space)
	{
		case BCS_WorldSpace:
			OutTransform.SetToRelativeTransform(ComponentTransform);
			break;

		case BCS_ComponentSpace:
			// Component Space, no change.
			break;

		case BCS_ParentBoneSpace:
			if (BoneIndex != INDEX_NONE)
			{
				const FName ParentBoneName = Mesh->GetParentBone(BoneName);
				const int32 ParentBoneIndex = Mesh->GetBoneIndex(ParentBoneName);

				if (ParentBoneIndex != INDEX_NONE)
				{
					const FTransform& ParentTransform = Mesh->GetBoneTransform(ParentBoneIndex);
					OutTransform					 *= ParentTransform;
				}
			}
			break;

		case BCS_BoneSpace:
			if (BoneIndex != INDEX_NONE)
			{
				if (USkeletalMeshComponent* Component = Cast<USkeletalMeshComponent>(Mesh))
				{
					const FTransform& BoneTransform = Component->BoneSpaceTransforms[BoneIndex];
					OutTransform				   *= BoneTransform;
				}

				if (UPoseableMeshComponent* Component = Cast<UPoseableMeshComponent>(Mesh))
				{
					const FTransform& BoneTransform = Component->BoneSpaceTransforms[BoneIndex];
					OutTransform				   *= BoneTransform;
				}
			}
			break;

		default:
			break;
	}
}

void UCsLibrary_Common::ConvertComponentSpaceTransformToBoneSpace(const FTransform& ComponentTransform, USkinnedMeshComponent* Mesh, FTransform& OutTransform, const FName &BoneName, const EBoneControlSpace &Space)
{
	const int32 BoneIndex = Mesh->GetBoneIndex(BoneName);

	switch (Space)
	{
		case BCS_WorldSpace:
			// world space, so component space * component to world
			OutTransform *= ComponentTransform;
			break;

		case BCS_ComponentSpace:
			// Component Space, no change.
			break;

		case BCS_ParentBoneSpace:
		{
			const FName ParentBoneName  = Mesh->GetParentBone(BoneName);
			const int32 ParentBoneIndex = Mesh->GetBoneIndex(ParentBoneName);

			if (ParentBoneIndex != INDEX_NONE)
			{
				const FTransform& ParentTransform = Mesh->GetBoneTransform(ParentBoneIndex);
				OutTransform.SetToRelativeTransform(ParentTransform);
			}
		}
		break;

		case BCS_BoneSpace:
		{
			if (USkeletalMeshComponent* Component = Cast<USkeletalMeshComponent>(Mesh))
			{
				const FTransform& BoneTransform = Component->BoneSpaceTransforms[BoneIndex];
				OutTransform.SetToRelativeTransform(BoneTransform);
			}

			if (UPoseableMeshComponent* Component = Cast<UPoseableMeshComponent>(Mesh))
			{
				const FTransform& BoneTransform = Component->BoneSpaceTransforms[BoneIndex];
				OutTransform.SetToRelativeTransform(BoneTransform);
			}
		}
		break;

		default:
			break;
	}
}

#pragma endregion Animation

// Emitter
#pragma region

void UCsLibrary_Common::ActivateEmitter(AEmitter* InEmitter)
{
	if (UParticleSystemComponent* Component = InEmitter->GetParticleSystemComponent())
	{
		Component->SetHiddenInGame(false);
		Component->SetVisibility(true);
		Component->Activate(true);
		Component->ActivateSystem();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("DeActivateEmitter: Attempting to DeActivate Emitter but the ParticleSystemComponent is nullptr"));
	}
}

void UCsLibrary_Common::DeActivateEmitter(AEmitter* InEmitter)
{
	if (UParticleSystemComponent* Component = InEmitter->GetParticleSystemComponent())
	{
		Component->SetHiddenInGame(true);
		Component->SetVisibility(false);
		Component->KillParticlesForced();
		Component->DeactivateSystem();
		Component->Deactivate();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("DeActivateEmitter: Attempting to DeActivate Emitter but the ParticleSystemComponent is nullptr"));
	}
}
/*
void UCsLibrary_Common::StopAndClearEmitter(UWorld* InWorld, TWeakObjectPtr<AShooterEmitter> &InEmitter)
{
	if (InEmitter.IsValid() && InEmitter.Get())
	{
		InEmitter->DeathStartTime = InWorld->TimeSeconds;

		if (InEmitter->GetParticleSystemComponent())
		{
			InEmitter->GetParticleSystemComponent()->DeactivateSystem();
		}
	}
	InEmitter.Reset();
	InEmitter = nullptr;
}

void UCsLibrary_Common::SetAndAttachEmitter(AEmitter* InEmitter, USceneComponent* Parent, FEffectsElement* Effect)
{
	InEmitter->SetTemplate(Effect->Get());
	InEmitter->SetActorRelativeLocation(Effect->LocationOffset);
	InEmitter->SetActorRelativeRotation(Effect->RotationOffset);
	InEmitter->AttachToComponent(Parent, FAttachmentTransformRules::KeepRelativeTransform, Effect->Bone == TEXT("") ? NAME_None : Effect->Bone);
}
*/
#pragma endregion Emitter

// Coroutine
#pragma region

const FCsRoutineHandle& UCsLibrary_Common::ScaleActorOverTime(const FECsUpdateGroup& Group, const ECsEasingType& EasingType, AActor* InActor, const float& StartScale, const float& EndScale, const float& Time, const bool& IsRelativeScale)
{
	return ScaleActorOverTime(Group, EasingType, InActor, FVector(StartScale), FVector(EndScale), Time, IsRelativeScale);
}

const FCsRoutineHandle& UCsLibrary_Common::ScaleActorOverTime(const FECsUpdateGroup& Group, const ECsEasingType& EasingType, AActor* InActor, const FVector& StartScale, const FVector& EndScale, const float& Time, const bool& IsRelativeScale)
{
	if (Time <= 0.0f)
	{
		// LOG Warning
		return FCsRoutineHandle::Invalid;
	}

	UCsCoroutineScheduler* Scheduler						= UCsCoroutineScheduler::Get(InActor->GetGameInstance());
	FCsResourceContainer_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload							= PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsLibrary_Common::ScaleActorOverTime_Internal);
	Payload->StartTime = UCsManager_Time::Get(InActor->GetGameInstance())->GetTime(Group);
	Payload->Owner.SetObject(InActor);

	Payload->SetName(NCsCommonCached::Name::ScaleActorOverTime_Internal);
	Payload->SetNameAsString(NCsCommonCached::Str::ScaleActorOverTime_Internal);

	static const int32 START_SCALE_INDEX = 0;
	Payload->SetValue_Vector(START_SCALE_INDEX, StartScale);

	static const int32 END_SCALE_INDEX = 1;
	Payload->SetValue_Vector(END_SCALE_INDEX, EndScale);

	static const int32 TIME_INDEX = 2;
	Payload->SetValue_Float(TIME_INDEX, Time);

	Payload->SetValue_Flag(CS_FIRST, IsRelativeScale);
	Payload->SetValue_Int(CS_FIRST, (int32)EasingType);

	return Scheduler->Start(Payload);
}

const FCsRoutineHandle& UCsLibrary_Common::ScaleActorOverTime(const FECsUpdateGroup& Group, UCurveBase* Curve, AActor* InActor, const float& StartScale, const float& EndScale, const float& Time, const bool& IsRelativeScale)
{
	return ScaleActorOverTime(Group, Curve, InActor, FVector(StartScale), FVector(EndScale), Time, IsRelativeScale);
}

const FCsRoutineHandle& UCsLibrary_Common::ScaleActorOverTime(const FECsUpdateGroup& Group, UCurveBase* Curve, AActor* InActor, const FVector& StartScale, const FVector& EndScale, const float& Time, const bool& IsRelativeScale)
{
	if (Time <= 0.0f)
	{
		// LOG Warning
		return FCsRoutineHandle::Invalid;
	}

	UCsCoroutineScheduler* Scheduler						= UCsCoroutineScheduler::Get(InActor->GetGameInstance());
	FCsResourceContainer_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload							= PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsLibrary_Common::ScaleActorOverTime_Internal);
	Payload->StartTime = UCsManager_Time::Get(InActor->GetGameInstance())->GetTime(Group);
	Payload->Owner.SetObject(InActor);

	Payload->SetName(NCsCommonCached::Name::ScaleActorOverTime_Internal);
	Payload->SetNameAsString(NCsCommonCached::Str::ScaleActorOverTime_Internal);

	static const int32 START_SCALE_INDEX = 0;
	Payload->SetValue_Vector(START_SCALE_INDEX, StartScale);

	static const int32 END_SCALE_INDEX = 1;
	Payload->SetValue_Vector(END_SCALE_INDEX, EndScale);

	static const int32 TIME_INDEX = 2;
	Payload->SetValue_Float(TIME_INDEX, Time);

	Payload->SetValue_Flag(CS_FIRST, IsRelativeScale);
	Payload->SetValue_Object(CS_FIRST, Curve);

	return Scheduler->Start(Payload);
}

char UCsLibrary_Common::ScaleActorOverTime_Internal(FCsRoutine* R)
{
	AActor* A = R->GetOwnerAsActor();

	const FCsTime& CurrentTime = UCsManager_Time::Get(A->GetGameInstance())->GetTime(R->Group);

	const FCsTime& StartTime = R->GetValue_Timer(CS_FIRST);

	static const int32 TIME_INDEX = 2;
	const float& MaxTime = R->GetValue_Float(TIME_INDEX);

	static const int32 START_SCALE_INDEX = 0;
	const FVector StartScale = ClampVectorComponents(R->GetValue_Vector(START_SCALE_INDEX), CS_ACTOR_SMALLEST_SCALE);

	static const int32 END_SCALE_INDEX = 1;
	const FVector EndScale   = ClampVectorComponents(R->GetValue_Vector(END_SCALE_INDEX), CS_ACTOR_SMALLEST_SCALE);

	const bool& IsRelativeScale		= R->GetValue_Flag(CS_FIRST);
	const ECsEasingType& EasingType = EMCsEasingType::Get().GetEnumAt(R->GetValue_Int(CS_FIRST));
	UCurveFloat* CurveFloat			= Cast<UCurveFloat>(R->GetValue_Object(CS_FIRST).Get());
	UCurveVector* CurveVector		= Cast<UCurveVector>(R->GetValue_Object(CS_FIRST).Get());

	CS_COROUTINE_BEGIN(R);

	if (R->Delay > 0.0f)
		CS_COROUTINE_WAIT_UNTIL(R, CurrentTime.Time - StartTime.Time > R->Delay);

	do
	{
		{
			const float Percent = FMath::Clamp((CurrentTime.Time - StartTime.Time) / MaxTime, 0.0f, 1.0f);
			FVector Scale		= EndScale;

			if (CurveFloat)
			{
				float Time = CurveFloat->GetFloatValue(Percent);
				Scale	   = ClampVectorComponents(FMath::Lerp(StartScale, EndScale, Time), CS_ACTOR_SMALLEST_SCALE);
			}
			else
			if (CurveVector)
			{
				FVector Times = CurveVector->GetVectorValue(Percent);

				Scale.X	= FMath::Lerp(StartScale.X, EndScale.X, Times.X);
				Scale.X	= FMath::Abs(Scale.X) < CS_ACTOR_SMALLEST_SCALE ? FMath::Sign(Scale.X) * CS_ACTOR_SMALLEST_SCALE : Scale.X;
				Scale.Y = FMath::Lerp(StartScale.Y, EndScale.Y, Times.Y);
				Scale.Y = FMath::Abs(Scale.Y) < CS_ACTOR_SMALLEST_SCALE ? FMath::Sign(Scale.Y) * CS_ACTOR_SMALLEST_SCALE : Scale.Y;
				Scale.Z = FMath::Lerp(StartScale.Z, EndScale.Z, Times.Z);
				Scale.Z = FMath::Abs(Scale.Z) < CS_ACTOR_SMALLEST_SCALE ? FMath::Sign(Scale.Z) * CS_ACTOR_SMALLEST_SCALE : Scale.Z;
			}
			else
			{
				float Time = Ease(EasingType, Percent, 0.0f, 1.0f, 1.0f);
				Scale	   = ClampVectorComponents(FMath::Lerp(StartScale, EndScale, Time), CS_ACTOR_SMALLEST_SCALE);
			}

			if (IsRelativeScale)
				A->SetActorRelativeScale3D(Scale);
			else
				A->SetActorScale3D(Scale);
		}
		CS_COROUTINE_YIELD(R);
	} while (CurrentTime.Time - StartTime.Time <= MaxTime);

	if (IsRelativeScale)
		A->SetActorRelativeScale3D(EndScale);
	else
		A->SetActorScale3D(EndScale);

	CS_COROUTINE_END(R);
}

const FCsRoutineHandle& UCsLibrary_Common::ScaleActorOverTime_AsCurve(const FECsUpdateGroup& Group, UCurveBase* Curve, AActor* InActor, const bool& IsRelativeScale)
{
	if (!Cast<UCurveFloat>(Curve) && !Cast<UCurveVector>(Curve))
	{
		// Log Warning
		return FCsRoutineHandle::Invalid;
	}

	UCsCoroutineScheduler* Scheduler						= UCsCoroutineScheduler::Get(InActor->GetGameInstance());
	FCsResourceContainer_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload							= PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsLibrary_Common::ScaleActorOverTime_AsCurve_Internal);
	Payload->StartTime = UCsManager_Time::Get(InActor->GetGameInstance())->GetTime(Group);
	Payload->Owner.SetObject(InActor);

	Payload->SetName(NCsCommonCached::Name::ScaleActorOverTime_AsCurve_Internal);
	Payload->SetNameAsString(NCsCommonCached::Str::ScaleActorOverTime_AsCurve_Internal);

	// TODO: Add Delay to Payload
	float MinTime = 0.0f;
	float MaxTime = 0.0f;
	/*
	Curve->GetTimeRange(MinTime, MaxTime);
	R->delay	  = MinTime > 0.0f ? MinTime : 0.0f;
	*/
	static const int32 MAX_TIME_INDEX = 2;
	Payload->SetValue_Float(MAX_TIME_INDEX, MaxTime);

	static const int32 RELATIVE_SCALE_INDEX = 0;
	Payload->SetValue_Flag(RELATIVE_SCALE_INDEX, IsRelativeScale);

	static const int32 USE_CURVE_FLOAT_INDEX = 1;
	Payload->SetValue_Flag(USE_CURVE_FLOAT_INDEX, Cast<UCurveFloat>(Curve) != nullptr); // Use CurveFloat

	static const int32 USE_CURVE_VECTOR_INDEX = 2;
	Payload->SetValue_Flag(USE_CURVE_VECTOR_INDEX, Cast<UCurveVector>(Curve) != nullptr); // Use CurveVector;
	
	Payload->SetValue_Object(CS_FIRST, Curve);

	return Scheduler->Start(Payload);
}

char UCsLibrary_Common::ScaleActorOverTime_AsCurve_Internal(FCsRoutine* R)
{
	AActor* A= R->GetOwnerAsActor();

	const FCsTime& CurrentTime = UCsManager_Time::Get(A->GetGameInstance())->GetTime(R->Group);
	const FCsTime& StartTime   = R->StartTime;

	static const int32 MAX_TIME_INDEX = 2;
	const float& MaxTime = R->GetValue_Float(MAX_TIME_INDEX);
	 
	static const int32 RELATIVE_SCALE_INDEX = 0;
	const bool& IsRelativeScale = R->GetValue_Flag(RELATIVE_SCALE_INDEX);

	static const int32 USE_CURVE_FLOAT_INDEX = 1;
	const bool& UseCurveFloat = R->GetValue_Flag(USE_CURVE_FLOAT_INDEX);

	static const int32 USE_CURVE_VECTOR_INDEX = 2;
	const bool& UseCurveVector = R->GetValue_Flag(USE_CURVE_VECTOR_INDEX);

	FVector EndScale = FVector(1.0f);

	UCurveFloat* CurveFloat	= UseCurveFloat ? Cast<UCurveFloat>(R->GetValue_Object(CS_FIRST).Get()) : nullptr;

	if (CurveFloat)
	{
		EndScale = FVector(CurveFloat->GetFloatValue(MaxTime));
	}

	UCurveVector* CurveVector = UseCurveVector ? Cast<UCurveVector>(R->GetValue_Object(CS_FIRST).Get()) : nullptr;

	if (CurveVector)
	{
		EndScale = CurveVector->GetVectorValue(MaxTime);
	}

	CS_COROUTINE_BEGIN(R);

	if (R->Delay > 0)
		CS_COROUTINE_WAIT_UNTIL(R, CurrentTime.Time - StartTime.Time > R->Delay);

	do
	{
		{
			if (!UseCurveFloat && !UseCurveVector)
				break;

			const float Percent = FMath::Clamp((CurrentTime.Time - StartTime.Time) / MaxTime, 0.0f, 1.0f);
			FVector Scale		= FVector(1.0f);

			if (CurveFloat)
			{
				float Value = CurveFloat->GetFloatValue(Percent);
				Value		= FMath::Abs(Value) < CS_ACTOR_SMALLEST_SCALE ? FMath::Sign(Value) * CS_ACTOR_SMALLEST_SCALE : Value;
				Scale		= FVector(Value);
			}
			else
			if (CurveVector)
			{
				Scale = ClampVectorComponents(CurveVector->GetVectorValue(Percent), CS_ACTOR_SMALLEST_SCALE);
			}

			if (IsRelativeScale)
				A->SetActorRelativeScale3D(Scale);
			else
				A->SetActorScale3D(Scale);
		}
		CS_COROUTINE_YIELD(R);
	} while (CurrentTime.Time - StartTime.Time <= MaxTime);

	if (IsRelativeScale)
		A->SetActorRelativeScale3D(EndScale);
	else
		A->SetActorScale3D(EndScale);

	CS_COROUTINE_END(R);
}

const FCsRoutineHandle& UCsLibrary_Common::MoveActorOverTime(const FECsUpdateGroup& Group, const ECsEasingType& EasingType, AActor* InActor, const FVector& StartLocation, const FVector& EndLocation, const float& Time, const bool& IsRelativeLocation)
{
	if (Time <= 0.0f)
	{
		// Log Warning
		return FCsRoutineHandle::Invalid;
	}

	UCsCoroutineScheduler* Scheduler						= UCsCoroutineScheduler::Get(InActor->GetGameInstance());
	FCsResourceContainer_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload							= PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsLibrary_Common::MoveActorOverTime_Internal);
	Payload->StartTime = UCsManager_Time::Get(InActor->GetGameInstance())->GetTime(Group);
	Payload->Owner.SetObject(InActor);

	Payload->SetName(NCsCommonCached::Name::MoveActorOverTime_Internal);
	Payload->SetNameAsString(NCsCommonCached::Str::MoveActorOverTime_Internal);

	static const int32 START_LOCATION_INDEX = 0;
	Payload->SetValue_Vector(START_LOCATION_INDEX, StartLocation);

	static const int32 END_LOCATION_INDEX = 1;
	Payload->SetValue_Vector(END_LOCATION_INDEX, EndLocation);

	Payload->SetValue_Float(CS_FIRST, Time);
	Payload->SetValue_Flag(CS_FIRST, IsRelativeLocation);
	Payload->SetValue_Int(CS_FIRST, (int32)EasingType);

	return Scheduler->Start(Payload);
}

char UCsLibrary_Common::MoveActorOverTime_Internal(FCsRoutine* R)
{
	AActor* A = R->GetOwnerAsActor();

	const FCsTime& CurrentTime = UCsManager_Time::Get(A->GetGameInstance())->GetTime(R->Group);
	const FCsTime& StartTime   = R->StartTime;

	const float& MaxTime = R->GetValue_Float(CS_FIRST);

	static const int32 START_LOCATION_INDEX = 0;
	const FVector& StartLocation = R->GetValue_Vector(START_LOCATION_INDEX);

	static const int32 END_LOCATION_INDEX = 1;
	const FVector& EndLocation = R->GetValue_Vector(END_LOCATION_INDEX);

	const bool& IsRelativeLocation	= R->GetValue_Flag(CS_FIRST);
	const ECsEasingType& EasingType = EMCsEasingType::Get().GetEnumAt(R->GetValue_Int(CS_FIRST));

	CS_COROUTINE_BEGIN(R);

	if (R->Delay > 0)
		CS_COROUTINE_WAIT_UNTIL(R, CurrentTime.Time - StartTime.Time > R->Delay);

	do
	{
		{
			const float Percent    = FMath::Clamp((CurrentTime.Time - StartTime.Time) / MaxTime, 0.0f, 1.0f);
			float Time			   = Ease(EasingType, Percent, 0.0f, 1.0f, 1.0f);
			const FVector Location = FMath::Lerp(StartLocation, EndLocation, Time);

			if (IsRelativeLocation)
				A->SetActorRelativeLocation(Location);
			else
				A->SetActorLocation(Location);
		}
		CS_COROUTINE_YIELD(R);
	} while (CurrentTime.Time - StartTime.Time <= MaxTime);

	if (IsRelativeLocation)
		A->SetActorRelativeLocation(EndLocation);
	else
		A->SetActorLocation(EndLocation);

	CS_COROUTINE_END(R);
}

const FCsRoutineHandle& UCsLibrary_Common::DestroyMaterialInstanceDynamic(const FECsUpdateGroup& Group, UMaterialInstanceDynamic* InMID, const float& Delay)
{
	UCsCoroutineScheduler* Scheduler						= UCsCoroutineScheduler::Get();
	FCsResourceContainer_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload							= PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsLibrary_Common::DestroyMaterialInstanceDynamic_Internal);
	Payload->StartTime = UCsManager_Time::Get()->GetTime(Group);
	Payload->Owner.SetObject(InMID);

	Payload->SetName(NCsCommonCached::Name::DestroyMaterialInstanceDynamic_Internal);
	Payload->SetNameAsString(NCsCommonCached::Str::DestroyMaterialInstanceDynamic_Internal);

	//R->delay	 = Delay;

	return Scheduler->Start(Payload);
}

char UCsLibrary_Common::DestroyMaterialInstanceDynamic_Internal(FCsRoutine* R)
{
	UMaterialInstanceDynamic* M = R->GetOwnerAsObject<UMaterialInstanceDynamic>();

	const FCsTime& CurrentTime = UCsManager_Time::Get()->GetTime(R->Group);
	const FCsTime& StartTime   = R->StartTime;

	CS_COROUTINE_BEGIN(R);

	if (R->Delay > 0)
		CS_COROUTINE_WAIT_UNTIL(R, CurrentTime.Time - StartTime.Time > R->Delay);

	M->MarkPendingKill();

	CS_COROUTINE_END(R);
}

/*
const FCsRoutineHandle& UCsLibrary_Common::DestroyMaterialInstanceDynamics(const FECsUpdateGroup& Group, TArray<UMaterialInstanceDynamic*>& InMIDs, const float& Delay)
{
	FCsRoutine* R = nullptr;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();

	int32 Count = InMIDs.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FCsResourceContainer_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
		FCsCoroutinePayload* Payload							= PayloadContainer->Get();

		Payload->Coroutine.BindStatic(&UCsLibrary_Common::DestroyMaterialInstanceDynamic_Internal);
		Payload->StartTime = UCsManager_Time::Get()->GetTime(Group);
		Payload->Owner.SetObject(InMIDs[I]);

		Payload->Name		  = NCsCommonCached::Name::DestroyMaterialInstanceDynamic_Internal;
		Payload->NameAsString = NCsCommonCached::Str::DestroyMaterialInstanceDynamic_Internal;

		//Payload->Delay = Delay;

		Scheduler->StartRoutine(ScheduleType, R);
	}
	return R;
}
*/

const FCsRoutineHandle& UCsLibrary_Common::FadeCameraOverTime(const FECsUpdateGroup &Group, const ECsEasingType& EasingType, APlayerController* Controller, const float& Start, const float& End, const float& Time, const FLinearColor& Color)
{
	if (Time <= 0.0f)
	{
		// Log Warning
		return FCsRoutineHandle::Invalid;
	}

	UCsCoroutineScheduler* Scheduler						= UCsCoroutineScheduler::Get(Controller->GetGameInstance());
	FCsResourceContainer_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload							= PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsLibrary_Common::FadeCameraOverTime_Internal);
	Payload->StartTime = UCsManager_Time::Get(Controller->GetGameInstance())->GetTime(Group);
	Payload->Owner.SetObject(Controller);

	Payload->SetName(NCsCommonCached::Name::FadeCameraOverTime_Internal);
	Payload->SetNameAsString(NCsCommonCached::Str::FadeCameraOverTime_Internal);

	Payload->SetValue_Int(CS_FIRST, (int32)EasingType);

	static const int32 START_INDEX = 0;
	Payload->SetValue_Float(START_INDEX, Start);

	static const int32 END_INDEX = 1;
	Payload->SetValue_Float(END_INDEX, End);

	static const int32 TIME_INDEX = 2;
	Payload->SetValue_Float(TIME_INDEX, Time);

	Payload->SetValue_Color(CS_FIRST, Color);

	return Scheduler->Start(Payload);
}

char UCsLibrary_Common::FadeCameraOverTime_Internal(FCsRoutine* R)
{
	APlayerController* PC = R->GetOwnerAsObject<APlayerController>();

	const FCsTime& CurrentTime = UCsManager_Time::Get(PC->GetGameInstance())->GetTime(R->Group);
	const FCsTime& StartTime   = R->StartTime;

	static const int32 MAX_TIME_INDEX = 2;
	const float& MaxTime = R->GetValue_Float(MAX_TIME_INDEX);

	const ECsEasingType& EasingType = EMCsEasingType::Get().GetEnumAt(R->GetValue_Int(CS_FIRST));

	static const int32 START_INDEX = 0;
	const float& Start = R->GetValue_Float(START_INDEX);

	static const int32 END_INDEX = 1;
	const float& End = R->GetValue_Float(END_INDEX);

	const bool IsFadeOut = Start > End;
	const float Max		 = FMath::Max(Start, End);
	const float Min		 = FMath::Min(Start, End);
	const float Delta	 = Max - Min;

	const FLinearColor& Color = R->GetValue_Color(CS_FIRST);

	CS_COROUTINE_BEGIN(R);

	if (R->Delay > 0)
		CS_COROUTINE_WAIT_UNTIL(R, CurrentTime.Time - StartTime.Time > R->Delay);

	do
	{
		{
			const float Percent = FMath::Clamp((CurrentTime.Time - StartTime.Time) / MaxTime, 0.0f, 1.0f);
			const float Time    = Ease(EasingType, Percent, 0.0f, 1.0f, 1.0f);
			const float Alpha	= IsFadeOut ? 1.0f - (Min + Percent * Delta) : Min + Percent * Delta;

			PC->PlayerCameraManager->SetManualCameraFade(Alpha, Color, false);
		}
		CS_COROUTINE_YIELD(R);
	} while (CurrentTime.Time - StartTime.Time <= MaxTime);

	PC->PlayerCameraManager->SetManualCameraFade(End, Color, false);

	CS_COROUTINE_END(R);
}
/*
FCsRoutine* UCsLibrary_Common::AllocateAndActivateEmitter(ACsCoroutineScheduler* ScheduleType, const ECsCoroutineSchedule &CoroutineSchedule, FEffectsElement* InEffectsElement, FVector Location, float Delay)
{
	if (!CoroutineScheduler)
		return nullptr;

	FRoutine* R = nullptr;

	Coroutine Function = &UShooterStatics::AllocateAndActivateEmitter_Internal;

	R = CoroutineScheduler->Allocate(ScheduleType, Function, true, false);

	R->timers[0] = CoroutineScheduler->GetWorld()->TimeSeconds;
	R->delay = Delay;

	CoroutineScheduler->StartRoutine(ScheduleType, R);
	return R;
}
*/
/*
PT_THREAD(UCsLibrary_Common::AllocateAndActivateEmitter_Internal(struct FCsRoutine* r))
{
	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_END(r);
}
*/

#pragma endregion Coroutine

// Javascript
#pragma region

#if WITH_EDITOR

void UCsLibrary_Common::SetupJavascript(UObject* InOwner, UWorld* InWorld, UObject* &JavascriptIsolate, UObject* &JavascriptContext, const FString &EditorJavascriptFile)
{
	auto Isolate = NewObject<UJavascriptIsolate>();
	// TODO: bIsEditor. Probably need to set to true if we want to interact with AnimInstance in Editor.
	Isolate->Init(false);
	auto Context = Isolate->CreateContext();

	JavascriptIsolate = Isolate;
	JavascriptContext = Context;

	Context->Expose("Root", InOwner);
	Context->Expose("GWorld", InWorld);
	Context->Expose("GEngine", GEngine);

	if (EditorJavascriptFile != TEXT(""))
		Context->RunFile(*EditorJavascriptFile);
}

void UCsLibrary_Common::SetupJavascript(UObject* InOwner, UWorld* InWorld, UObject* &JavascriptIsolate, UObject* &JavascriptContext)
{
	SetupJavascript(InOwner, InWorld, JavascriptIsolate, JavascriptContext, TEXT(""));
}

void UCsLibrary_Common::Javascript_ExposeObject(UObject* &JavascriptContext, const FString &Name, UObject* InObject)
{
	Cast<UJavascriptContext>(JavascriptContext)->Expose(Name, InObject);
}

void UCsLibrary_Common::Javascript_RunFile(UObject* &JavascriptContext, const FString &EditorJavascriptFile)
{
	Cast<UJavascriptContext>(JavascriptContext)->RunFile(*EditorJavascriptFile);
}

#endif // #if WITH_EDITOR

#pragma endregion Javascript

bool UCsLibrary_Common::IsDedicatedServer(AActor* InActor)
{
	return IsRunningDedicatedServer() || InActor->GetNetMode() == NM_DedicatedServer;
}

FString UCsLibrary_Common::GetProxyAsString(AActor* InActor)
{
	if (InActor->Role < ROLE_Authority)
		return NCsCommonCached::Str::Client;
	if (InActor->Role == ROLE_Authority)
	{
		if (IsDedicatedServer(InActor))
			return NCsCommonCached::Str::Server_Dedicated;
		return NCsCommonCached::Str::Server;
	}
	return NCsCommonCached::Str::Unknown;
}

// World
#pragma region

bool UCsLibrary_Common::IsPlayInGame(UWorld* InWorld)
{
	return InWorld && InWorld->WorldType == EWorldType::Game;
}

bool UCsLibrary_Common::IsPlayInEditor(UWorld* InWorld)
{
	return InWorld && InWorld->WorldType == EWorldType::Editor;
}

bool UCsLibrary_Common::IsPlayInPIE(UWorld* InWorld)
{
	return InWorld && InWorld->WorldType == EWorldType::PIE;
}

bool UCsLibrary_Common::IsPlayInEditorPreview(UWorld* InWorld)
{
	return InWorld && InWorld->WorldType == EWorldType::EditorPreview;
}

bool UCsLibrary_Common::IsAnyWorldContextEditorOrEditorPreview()
{
	const TIndirectArray<FWorldContext>& WorldContexts = GEngine->GetWorldContexts();

	for (const FWorldContext& Context : WorldContexts)
	{
		if (Context.WorldType == EWorldType::Editor ||
			Context.WorldType == EWorldType::EditorPreview)
		{
			return true;
		}
	}
	return false;
}

#pragma endregion World

bool UCsLibrary_Common::IsDefaultObject(UObject* InObject)
{
	return InObject->GetName().StartsWith(TEXT("Default__"));
}

const uint64& UCsLibrary_Common::GetUniqueObjectId(AActor* Actor)
{
	if (ACsPawn* Pawn = Cast<ACsPawn>(Actor))
		return Pawn->UniqueObjectId;
	return CS_INVALID_UNIQUE_OBJECT_ID;
}

// Time
#pragma region

uint64 UCsLibrary_Common::GetWorldTimeMilliseconds(UWorld* InWorld)
{
	return (uint64)FMath::FloorToInt(InWorld->TimeSeconds * 1000.0f);
}

float UCsLibrary_Common::GetCurrentDateTimeSeconds()
{
	FDateTime DateTime = FDateTime::Now();
	
	float Seconds = (float)DateTime.GetMinute() * 60.0f;
	Seconds		 += (float)DateTime.GetSecond();
	Seconds		 += (float)DateTime.GetMillisecond() / 1000.0f;
	
	return Seconds;
}

uint64 UCsLibrary_Common::GetCurrentFrame(UWorld* InWorld) 
{
#if WITH_EDITOR
	if (IsPlayInEditorPreview(InWorld))
		return 0;
#endif // #if WITH_EDITOR
	return InWorld->GetGameInstance<UCsGameInstance>()->CurrentGameFrame; 
}

#pragma endregion Time

bool UCsLibrary_Common::IsDeveloperBuild()
{
#if UE_BUILD_SHIPPING
	return false;
#else
	return true;
#endif
}

// Physics
#pragma  region

bool UCsLibrary_Common::SetPhysicsPreset(FCsPhysicsPreset &Preset, UPrimitiveComponent* Component)
{
	bool IsDirty = false;

	FBodyInstance& BodyInstance = Component->BodyInstance;

	// bSimulatePhysics
	IsDirty |= BodyInstance.bSimulatePhysics != Preset.bSimulatePhysics;
	Preset.bSimulatePhysics = BodyInstance.bSimulatePhysics;
	// OverrideMassInKg
	IsDirty |= BodyInstance.bOverrideMass != Preset.OverrideMassInKg;
	Preset.OverrideMassInKg = BodyInstance.bOverrideMass;
	// MassInKg
	if (Preset.OverrideMassInKg)
	{
		IsDirty |= BodyInstance.GetMassOverride() != Preset.MassInKg;
		Preset.MassInKg = BodyInstance.GetMassOverride();
	}
	else
	{
		IsDirty |= BodyInstance.GetBodyMass() != Preset.MassInKg;
		Preset.MassInKg = BodyInstance.GetBodyMass();
	}
	// LinearDamping
	IsDirty |= BodyInstance.LinearDamping != Preset.LinearDamping;
	Preset.LinearDamping = BodyInstance.LinearDamping;
	// AngularDamping
	IsDirty |= BodyInstance.AngularDamping != Preset.AngularDamping;
	Preset.AngularDamping = BodyInstance.AngularDamping;
	// bEnableGravity
	IsDirty |= BodyInstance.bEnableGravity != Preset.bEnableGravity;
	Preset.bEnableGravity = BodyInstance.bEnableGravity;

	return IsDirty;
}

void UCsLibrary_Common::SetPhysicsFromPreset(const FCsPhysicsPreset &Preset, UPrimitiveComponent* Component)
{
	// bSimulatePhysics
	Component->SetSimulatePhysics(Preset.bSimulatePhysics);
	// MassInKg and OverrideMassInKg
	Component->GetBodyInstance()->SetMassOverride(Preset.MassInKg, Preset.OverrideMassInKg);
	// LinearDamping
	Component->SetLinearDamping(Preset.LinearDamping);
	// AngularDamping
	Component->SetAngularDamping(Preset.AngularDamping);
	// bEnableGravity
	Component->SetEnableGravity(Preset.bEnableGravity);
}

#pragma endregion Physics

// Collision
#pragma  region

bool UCsLibrary_Common::SetCollisionPreset(FCsCollisionPreset &Preset, UPrimitiveComponent* Component)
{
	bool IsDirty = false;
	
	FBodyInstance& BodyInstance = Component->BodyInstance;
	
	// bSimulationGeneratesHitEvents
	IsDirty |= BodyInstance.bNotifyRigidBodyCollision != Preset.bSimulationGeneratesHitEvents;
	Preset.bSimulationGeneratesHitEvents = BodyInstance.bNotifyRigidBodyCollision;
	// PhysMaterialOverride
	IsDirty |= BodyInstance.GetSimplePhysicalMaterial() != Preset.PhysMaterialOverride.Material;
	Preset.PhysMaterialOverride.Material = BodyInstance.GetSimplePhysicalMaterial();
	// bGenerateOverlapEvents
	IsDirty |= Component->GetGenerateOverlapEvents() != Preset.bGenerateOverlapEvents;
	Preset.bGenerateOverlapEvents = Component->GetGenerateOverlapEvents();
	// CollisionEnabled
	IsDirty |= Component->GetCollisionEnabled() != Preset.CollisionEnabled;
	Preset.CollisionEnabled = Component->GetCollisionEnabled();
	// ObjectType
	IsDirty |= Component->GetCollisionObjectType() != Preset.ObjectType;
	Preset.ObjectType = Component->GetCollisionObjectType();
	// CollisionResponses
	const int32 Max = ECollisionChannel::ECC_MAX - 1;

	for (int32 I = 0; I < Max; ++I)
	{
		const ECollisionChannel Channel = (ECollisionChannel)I;

		const ECollisionResponse Reponse = Component->GetCollisionResponseToChannel(Channel);
		IsDirty |= Preset.CollisionResponses.GetResponse(Channel) != Reponse;
		Preset.CollisionResponses.SetResponse(Channel, Reponse);
	}
	return IsDirty;
}

void UCsLibrary_Common::SetCollisionFromPreset(const FCsCollisionPreset &Preset, UPrimitiveComponent* Component, const bool &SetCollisionEnabled /*=true*/)
{
	FBodyInstance& BodyInstance = Component->BodyInstance;

	// bSimulationGeneratesHitEvents
	//BodyInstance.bNotifyRigidBodyCollision = Preset.bSimulationGeneratesHitEvents;
	Component->SetNotifyRigidBodyCollision(Preset.bSimulationGeneratesHitEvents);
	// PhysMaterialOverride
	BodyInstance.SetPhysMaterialOverride(Preset.PhysMaterialOverride.Get());
	// bGenerateOverlapEvents
	Component->SetGenerateOverlapEvents(Preset.bGenerateOverlapEvents);
	// ObjectType
	Component->SetCollisionObjectType(Preset.ObjectType);
	// CollisionResponses
	const int32 Max = ECollisionChannel::ECC_MAX - 1;

	for (int32 I = 0; I < Max; ++I)
	{
		const ECollisionChannel Channel = (ECollisionChannel)I;

		Component->SetCollisionResponseToChannel(Channel, Preset.CollisionResponses.GetResponse(Channel));
	}
	// CollisionEnabled
	if (SetCollisionEnabled)
		Component->SetCollisionEnabled(Preset.CollisionEnabled);
}

void UCsLibrary_Common::SetCollisionFromTemplate(const FName &TemplateName, UPrimitiveComponent* Component, const bool &SetCollisionEnabled /*=true*/)
{
	FCollisionResponseTemplate Template;

	if (UCollisionProfile::Get()->GetProfileTemplate(TemplateName, Template))
	{
		Component->SetCollisionObjectType(Template.ObjectType);
		Component->SetCollisionResponseToChannels(Template.ResponseToChannels);

		if (SetCollisionEnabled)
			Component->SetCollisionEnabled(Template.CollisionEnabled);
	}
}

#pragma endregion Collision

// Level
#pragma region

void UCsLibrary_Common::TransitionToLevel(UWorld* InWorld, const FString &Level, const FString &GameMode)
{
	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(InWorld->GetGameInstance());
	GameInstance->PerformLevelTransition(Level, GameMode);
}

void UCsLibrary_Common::RequestEndPlayMap() 
{
#if WITH_EDITOR
	GEditor->RequestEndPlayMap();
#endif // #if WITH_EDITOR
}

#pragma endregion Level

// Editor Message
#pragma region

#if WITH_EDITOR

void UCsLibrary_Common::DisplayNotificationInfo(const FString &InTextLiteral, const FString &InNamespace, const FString &InKey, const float &Duration)
{
	FText Text = FInternationalization::Get().ForUseOnlyByLocMacroAndGraphNodeTextLiterals_CreateText(*InTextLiteral, *InNamespace, *InKey);
	//FText Text = FTextCache::Get().FindOrCache(*InTextLiteral, *InNamespace, *InKey);

	FNotificationInfo Info(Text);

	Info.Image = FEditorStyle::GetBrush(TEXT("LevelEditor.RecompileGameCode"));
	Info.FadeInDuration = 0.1f;
	Info.FadeOutDuration = 0.5f;
	Info.ExpireDuration = Duration;
	Info.bUseThrobber = false;
	Info.bUseSuccessFailIcons = true;
	Info.bUseLargeFont = true;
	Info.bFireAndForget = false;
	Info.bAllowThrottleWhenFrameRateIsLow = false;

	auto NotificationItem = FSlateNotificationManager::Get().AddNotification(Info);

	NotificationItem->SetCompletionState(SNotificationItem::CS_Success);
	NotificationItem->ExpireAndFadeout();
}

#endif // #if WITH_EDITOR

#pragma endregion Editor Message

bool UCsLibrary_Common::CanAsyncTask()
{
	return FPlatformProcess::SupportsMultithreading() && FPlatformMisc::NumberOfCoresIncludingHyperthreads() > 1;
}