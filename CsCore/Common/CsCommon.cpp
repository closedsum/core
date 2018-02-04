// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Common/CsCommon.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Types/CsTypes_Curve.h"
#include "GameFramework/GameState.h"
#include "GameFramework/GameMode.h"
#include "Game/CsGameInstance.h"
#include "Coroutine/CsCoroutineScheduler.h"

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
#include "Player/CsPlayerPawn.h"
#include "VR/Player/CsPlayerPawn_VR.h"
#include "../Engine/Classes/GameFramework/PlayerInput.h"

#include "Engine/CollisionProfile.h"

#include "Data/CsData.h"

#if WITH_EDITOR

// Javascript
#include "../Plugins/UnrealJS/Source/V8/Public/JavascriptIsolate.h"
#include "../Plugins/UnrealJS/Source/V8/Public/JavascriptContext.h"

// Slate
#include "Runtime/Slate/Public/Framework/Notifications/NotificationManager.h"
#include "Runtime/Slate/Public/Widgets/Notifications/SNotificationList.h"
#include "../Source/Editor/EditorStyle/Public/EditorStyleSet.h"

#include "Runtime/Core/Public/Internationalization/Internationalization.h"

#include "../Source/Editor/UnrealEd/Public/Editor.h"

#endif // #if WITH_EDITOR


namespace ECsCommonCachedName
{
	namespace Name
	{
		// Functions
		const FName ScaleActorOverTime_Internal = FName("UCsCommon::ScaleActorOverTime_Internal");
		const FName ScaleActorOverTime_AsCurve_Internal = FName("UCsCommon::ScaleActorOverTime_AsCurve_Internal");
		const FName MoveActorOverTime_Internal = FName("UCsCommon::MoveActorOverTime_Internal");
		const FName DestroyMaterialInstanceDynamic_Internal = FName("UCsCommon::DestroyMaterialInstanceDynamic_Internal");
		const FName FadeCameraOverTime_Internal = FName("UCsCommon::FadeCameraOverTime_Internal");
	}
}

namespace ECsCommonCachedString
{
	namespace Str
	{
		// Functions
		const FString ScaleActorOverTime_Internal = TEXT("UCsCommon::ScaleActorOverTime_Internal");
		const FString ScaleActorOverTime_AsCurve_Internal = TEXT("UCsCommon::ScaleActorOverTime_AsCurve_Internal");
		const FString MoveActorOverTime_Internal = TEXT("UCsCommon::MoveActorOverTime_Internal");
		const FString DestroyMaterialInstanceDynamic_Internal = TEXT("UCsCommon::DestroyMaterialInstanceDynamic_Internal");
		const FString FadeCameraOverTime_Internal = TEXT("UCsCommon::FadeCameraOverTime_Internal");
	}
}

UCsCommon::UCsCommon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

/*
bool UCsCommon::IsControlledByClient(AShooterCharacter* InPawn)
{
	return GetClientController(InPawn) != nullptr && UShooterStatics::GetMachineClientController(InPawn->GetWorld()) == GetClientController(InPawn);
}

AShooterPlayerController* UCsCommon::GetClientController(AShooterCharacter* InPawn)
{
	if (!InPawn || !InPawn->IsLocallyControlled())
		return nullptr;
	return InPawn->Controller ? Cast<AShooterPlayerController>(InPawn->Controller) : Cast<AShooterPlayerController>(InPawn->GetLinkedController());
}

AShooterPlayerController* UCsCommon::GetMachineClientController(UWorld *InWorld)
{
	check(InWorld);
	check(GEngine);

	return Cast<AShooterPlayerController>(GEngine->GetFirstLocalPlayerController(InWorld));
}

bool UCsCommon::IsLocallyControlled(AShooterCharacter* InPawn, UWorld* InWorld)
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

AController* UCsCommon::GetLocalPlayerController(UWorld* InWorld)
{
	return GetLocalPlayerController<AController>(InWorld);
}

UPlayerInput* UCsCommon::GetLocalPlayerInput(UWorld* InWorld)
{
	APlayerController* Controller = GetLocalPlayerController<APlayerController>(InWorld);
	return Controller->PlayerInput;
}

APlayerState* UCsCommon::GetLocalPlayerState(UWorld* InWorld)
{
	return GetLocalPlayerState<APlayerState>(InWorld);
}

bool UCsCommon::IsLocalPlayerState(UWorld* InWorld, APlayerState* InPlayerState)
{
	if (!InPlayerState)
		return false;
	return InPlayerState == GetLocalPlayerState(InWorld);
}

bool UCsCommon::IsLocalPawn(UWorld* InWorld, APawn* InPawn)
{
	if (!InPawn)
		return false;
	if (!InPawn->PlayerState)
		return false;
	return InPawn->PlayerState == GetLocalPlayerState(InWorld);
}

void UCsCommon::GetLocalPlayerViewPoint(UWorld* InWorld, FVector &OutLocation, FRotator &OutRotation)
{
	GetLocalPlayerViewPoint<APlayerController>(InWorld, OutLocation, OutRotation);
}

float UCsCommon::GetSquaredDistanceToLocalControllerEye(UWorld *InWorld, const FVector& Location)
{
	APlayerController* LocalController = GetLocalPlayerController<APlayerController>(InWorld);

	if (!LocalController)
		return -1.0f;

	FVector ViewLocation;
	FRotator ViewRotation;

	LocalController->GetPlayerViewPoint(ViewLocation, ViewRotation);

	return FVector::DistSquared(ViewLocation, Location);
}

ACsMotionController* UCsCommon::GetLocalHand(UWorld *InWorld, const TCsControllerHand &Hand)
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

#pragma endregion Local Client

// VR
#pragma region

bool UCsCommon::IsVR()
{
	return GEngine->HMDDevice.IsValid() && GEngine->IsStereoscopic3D();
}

bool UCsCommon::IsVive()
{
	return GEngine->HMDDevice.IsValid() && GEngine->HMDDevice->IsHMDEnabled() && GEngine->HMDDevice->GetHMDDeviceType() == EHMDDeviceType::DT_SteamVR;
}

bool UCsCommon::IsRift()
{
	return GEngine->HMDDevice.IsValid() && GEngine->HMDDevice->IsHMDEnabled() && GEngine->HMDDevice->GetHMDDeviceType() == EHMDDeviceType::DT_OculusRift;
}

void UCsCommon::GetHMDOrientationAndPosition(FRotator& DeviceRotation, FVector& DevicePosition)
{
	if (GEngine->HMDDevice.IsValid() && GEngine->HMDDevice->IsHeadTrackingAllowed())
	{
		FQuat OrientationAsQuat;
		FVector Position(0.f);

		GEngine->HMDDevice->GetCurrentOrientationAndPosition(OrientationAsQuat, Position);

		DeviceRotation = OrientationAsQuat.Rotator();
		DevicePosition = Position;
	}
	else
	{
		DeviceRotation = FRotator::ZeroRotator;
		DevicePosition = FVector::ZeroVector;
	}
}

void UCsCommon::GetHMDWorldViewPoint(UWorld* InWorld, FVector &OutLocation, FRotator& OutRotation)
{
	APlayerController* PlayerController = GetLocalPlayerController<APlayerController>(InWorld);
	
	PlayerController->GetPlayerViewPoint(OutLocation, OutRotation);

	if (GEngine->HMDDevice.IsValid() && GEngine->HMDDevice->IsHeadTrackingAllowed())
	{
		FQuat hmdOrientation;
		FVector hmdPosition;

		GEngine->HMDDevice->GetCurrentOrientationAndPosition(hmdOrientation, hmdPosition);

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

ACsMotionController* UCsCommon::GetMotionController(UWorld* InWorld, const TCsControllerHand &Hand)
{
	ACsPlayerPawn_VR* Pawn = GetLocalPawn<ACsPlayerPawn_VR>(InWorld);

	if (!Pawn)
		return nullptr;

	return ECsControllerHand::Right ? Pawn->RightHand : Pawn->LeftHand;
}

#pragma endregion

// Enum to String Conversion
#pragma region

FString UCsCommon::LoadFlagsToString(const int32 &LoadFlags)
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
			String += ECsLoadFlags_Editor::ToString((TCsLoadFlags_Editor)I);
			IsFirst = false;
		}
	}
	return String;
}

FString UCsCommon::InteractivePhysicsStateToString(const int32 &PhysicsState)
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

int32 UCsCommon::StringtoLoadFlags(const FString &LoadFlags)
{
	int32 Flag = 0;

	for (int32 I = 0; I < ECS_LOAD_FLAGS_EDITOR_MAX; ++I)
	{
		const FString EnumAsString = ECsLoadFlags_Editor::ToString((TCsLoadFlags_Editor)I);

		if (LoadFlags.Contains(EnumAsString))
			CS_SET_BLUEPRINT_BITFLAG(Flag, ECsLoadFlags_Editor::ToFlag(EnumAsString));
	}
	return Flag;
}

ECsLoadFlags UCsCommon::ViewTypeToLoadFlags(const TCsViewType &ViewType, const bool &IsLow /*=false*/)
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

FString UCsCommon::Stream_GetString(const TCHAR*& Str, bool IsLowerCase)
{
	FString Arg;
	FParse::Token(Str, Arg, false);

	return IsLowerCase ? Arg.ToLower() : Arg;
}

FName UCsCommon::Stream_GetName(const TCHAR*& Str)
{
	return FName(*Stream_GetString(Str, false));
}

bool UCsCommon::Stream_GetBool(const TCHAR*& Str)
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

int32 UCsCommon::Stream_GetBoolAsInt(const TCHAR*& Str)
{
	FString Arg = Stream_GetString(Str, true);

	if (Arg == TEXT("true") || Arg == TEXT("1"))
		return 1;
	if (Arg == TEXT("false") || Arg == TEXT("0"))
		return 0;
	return INDEX_NONE;
}

int32 UCsCommon::Stream_GetInt(const TCHAR*& Str)
{
	FString Arg;
	FParse::Token(Str, Arg, false);

	return FCString::Atoi(*Arg);
}

float UCsCommon::Stream_GetFloat(const TCHAR*& Str)
{
	FString Arg;
	FParse::Token(Str, Arg, false);

	return FCString::Atof(*Arg);
}

ERichCurveInterpMode UCsCommon::Stream_GetRichCurveInterpMode(const TCHAR*& Str)
{
	FString Arg = Stream_GetString(Str, true);
	return ECsRichCurveInterpMode::ToBaseType(Arg);
}

ERichCurveTangentMode UCsCommon::Stream_GetRichCurveTangentMode(const TCHAR*& Str)
{
	FString Arg = Stream_GetString(Str, true);
	return ECsRichCurveTangentMode::ToBaseType(Arg);
}

TCsViewType UCsCommon::Stream_GetViewType(const TCHAR*& Str)
{
	FString Arg;
	FParse::Token(Str, Arg, false);

	return ECsViewType::ToType(Arg);
}

#pragma endregion

// Data
#pragma region

ACsDataMapping* UCsCommon::GetDataMapping(UWorld* InWorld)
{
	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(InWorld->GetGameInstance());
	return GameInstance->DataMapping;
}

#pragma endregion Data

// Materials
#pragma region

void UCsCommon::SetMaterials(UStaticMeshComponent* InMesh, const TArray<UMaterialInstanceConstant*>& Materials)
{
	const int32 Count		  = InMesh->GetStaticMesh()->StaticMaterials.Num();
	const int32 MaterialCount = Materials.Num();

	if (Count > MaterialCount)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsCommon::SetMaterials: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *InMesh->GetStaticMesh()->GetName(), Count, MaterialCount);
		return;
	}

	ClearOverrideMaterials(InMesh);

	for (int32 Index = 0; Index < Count; Index++)
	{
		InMesh->SetMaterial(Index, Materials[Index]);
	}
}

void UCsCommon::SetMaterials(USkeletalMeshComponent* InMesh, const TArray<UMaterialInstanceConstant*>& Materials)
{
	const int32 Count		  = InMesh->SkeletalMesh->Materials.Num();
	const int32 MaterialCount = Materials.Num();

	if (Count > MaterialCount)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsCommon::SetMaterials: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *InMesh->SkeletalMesh->GetName(), Count, MaterialCount);
		return;
	}

	ClearOverrideMaterials(InMesh);

	for (int32 Index = 0; Index < Count; Index++)
	{
		InMesh->SetMaterial(Index, Materials[Index]);
	}
}

void UCsCommon::ClearOverrideMaterials(UStaticMeshComponent* InMesh)
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

void UCsCommon::ClearOverrideMaterials(USkeletalMeshComponent* InMesh)
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

void UCsCommon::DestroyMIDs(TArray<UMaterialInstanceDynamic*>& MIDs)
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

void UCsCommon::SetMIDs(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<FSkeletalMaterial>& Materials)
{
	ClearOverrideMaterials(InMesh);
	DestroyMIDs(MIDs);

	const int32 Count = Materials.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		MIDs.Add(InMesh->CreateDynamicMaterialInstance(Index, Materials[Index].MaterialInterface));
	}
}

void UCsCommon::SetMIDs(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInstanceConstant*>& Materials)
{
	ClearOverrideMaterials(InMesh);
	DestroyMIDs(MIDs);

	const int32 Count = Materials.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		MIDs.Add(InMesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
	}
}

void UCsCommon::SetMIDs(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials)
{
	ClearOverrideMaterials(InMesh);
	DestroyMIDs(MIDs);

	const int32 Count = Materials.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		MIDs.Add(InMesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
	}
}

void UCsCommon::MIDs_SetScalarParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float &Value)
{
	const int32 Count = MIDs.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		check(MIDs[Index]);

		if (MIDs[Index])
			MIDs[Index]->SetScalarParameterValue(ParamName, Value);
	}
}

void UCsCommon::MIDs_SetVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector &Value)
{
	const int32 Count = MIDs.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		check(MIDs[Index]);

		if (MIDs[Index])
			MIDs[Index]->SetVectorParameterValue(ParamName, Value);
	}
}

void UCsCommon::MIDs_SetVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor &Value)
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

FVector UCsCommon::GetBoneLocation(USkeletalMeshComponent* InMesh, const int32 &BoneIndex, const TEnumAsByte<EBoneSpaces::Type> &Space)
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

FName UCsCommon::GetParentBone(USkeletalMeshComponent* InMesh, const int32 &BoneIndex)
{
	FName Result = NAME_None;

	if ((BoneIndex != INDEX_NONE) && (BoneIndex > 0)) // This checks that this bone is not the root (ie no parent), and that BoneIndex != INDEX_NONE (ie bone name was found)
	{
		Result = InMesh->SkeletalMesh->RefSkeleton.GetBoneName(InMesh->SkeletalMesh->RefSkeleton.GetParentIndex(BoneIndex));
	}
	return Result;
}

void UCsCommon::CopyHitResult(const FHitResult& From, FHitResult& To)
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

void UCsCommon::SetHitResult(FHitResult* InHitResult, FHitResult* OutHitResult)
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

bool UCsCommon::IsMatchInProgress(UWorld *InWorld)
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

float UCsCommon::GetAngleDelta(const float &Angle1, const float &Angle2)
{
	int32 Mag		 = Angle2 - Angle1 > 0 ? 1 : -1;
	float DeltaAngle = Angle2 - Angle1;

	return FMath::Abs(DeltaAngle) > 180.0f ? -1 * Mag * (360.0f - FMath::Abs(DeltaAngle)) : Mag * FMath::Abs(DeltaAngle);
}

FRotator UCsCommon::GetAngleDelta(const FRotator &A, const FRotator &B)
{
	FRotator Rotation;

	Rotation.Pitch = GetAngleDelta(A.Pitch, B.Pitch);
	Rotation.Yaw = GetAngleDelta(A.Yaw, B.Yaw);
	Rotation.Roll = GetAngleDelta(A.Roll, B.Roll);

	return Rotation;
}

FRotator UCsCommon::Rotator_GetAngleDelta(const FRotator &A, const FRotator &B)
{
	return GetAngleDelta(A, B);
}

float UCsCommon::AngleClamp180(float Angle)
{
	while (Angle < -180.0f){ Angle += 360.0f; }
	while (Angle > 180.0f){ Angle -= 360.0f; }
	return Angle;
}

FRotator UCsCommon::AngleClamp180(const FRotator &Rotation)
{
	return FRotator(AngleClamp180(Rotation.Pitch), AngleClamp180(Rotation.Yaw), AngleClamp180(Rotation.Roll));
}

float UCsCommon::AngleClamp360(float Angle)
{
	while (Angle < 0.0f){ Angle += 360.0f; }
	while (Angle > 360.0f){ Angle -= 360.0f; }
	return Angle;
}

FRotator UCsCommon::AngleClamp360(const FRotator &Rotation)
{
	return FRotator(AngleClamp360(Rotation.Pitch), AngleClamp360(Rotation.Yaw), AngleClamp360(Rotation.Roll));
}

float UCsCommon::LerpAngle(const float &FromAngle, const float &ToAngle, const float &LerpRate, const float &DeltaSeconds, float MinAngle, float MaxAngle)
{
	float DeltaAngle	   = UCsCommon::GetAngleDelta(FromAngle, ToAngle);
	const float SmallDelta = 0.001f;
	float Percent		   = FMath::Abs(DeltaAngle) > SmallDelta ? FMath::Clamp((LerpRate * DeltaSeconds) / FMath::Abs(DeltaAngle), 0.0f, 1.0f) : 1.0f;

	MinAngle = UCsCommon::AngleClamp360(MinAngle);

	if (MinAngle > MaxAngle)
	{
		float Temp = MaxAngle;
		MaxAngle   = MinAngle;
		MinAngle   = Temp;
	}
	return FMath::Clamp(UCsCommon::AngleClamp360(FromAngle + Percent * DeltaAngle), MinAngle, MaxAngle);
}

int32 UCsCommon::Mod(const int32 &A, const int32 &B)
{
	const int32 C = A % B;
	return C < 0 ? C + B : C;
}

FVector UCsCommon::BuildUniformVector(const FVector &V, const int32 &Axes)
{
	if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_X))
		return FVector(V.X);
	if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Y))
		return FVector(V.Y);
	if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Z))
		return FVector(V.Z);
	return FVector::ZeroVector;
}

FRotator UCsCommon::BuildUniformRotator(const FRotator &R, const int32 &Axes)
{
	if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_ROLL))
		return FRotator(R.Roll);
	if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_PITCH))
		return FRotator(R.Pitch);
	if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_YAW))
		return FRotator(R.Yaw);
	return FRotator::ZeroRotator;
}

int32 UCsCommon::GetNumBitFlags(const int32 &BitMask, const int32 &MaxBits)
{
	int32 Bits = 0;

	for (int32 I = 0; I < MaxBits; ++I)
	{
		if (CS_TEST_BLUEPRINT_BITFLAG(BitMask, I))
			Bits++;
	}
	return Bits;
}

FString UCsCommon::UInt64ToString(const uint64 &Value)
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

#pragma endregion Math

/*
bool UCsCommon::IsOnSameTeam(UWorld *InWorld, AShooterCharacter* InPawnA, AShooterCharacter* InPawnB)
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

bool UCsCommon::IsOnSameTeam(UWorld *InWorld, AShooterPlayerState* InPlayerStateA, AShooterCharacter* InPawnB)
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

bool UCsCommon::IsOnSameTeam(UWorld *InWorld, AShooterPlayerState* InPlayerStateA, AShooterPlayerState* InPlayerStateB)
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
FVector UCsCommon::GetScaledPlayerViewDirection(AController* Controller, const FVector &Scale)
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
void UCsCommon::GetHMDWorldViewPoint(APlayerController* PlayerController, FVector& out_Location, FRotator& out_Rotation)
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

// version of GEngine->IsStereoscopic3D() that is valid even during toggle frame. 
bool UCsCommon::IsStereoscopic3D()
{
	return false;
	//return GEngine && GEngine->StereoRenderingDevice.IsValid() && GEngine->StereoRenderingDevice->IsStereoEnabledOnNextFrame();
}

// Easing
#pragma region

float UCsCommon::Ease(const TEnumAsByte<ECsEasingType::Type> &EasingType, const float &Time, const float &Start, const float &Final, const float &Duration)
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

float UCsCommon::Linear(const float &Time, const float &Start, const float &Final, const float &Duration)
{
	return ((Final * Time) / Duration) + Start;
}

float UCsCommon::BounceEaseOut(float Time, const float &Start, const float &Final, const float &Duration)
{
	Time /= Duration;

	if (Time < (1 / 2.75f))
	{
		return Final * (7.5625f * Time * Time) + Start;
	}
	else if (Time < (2.0f / 2.75f))
	{
		Time -= (1.5f / 2.75f);
		return Final * (7.5625f * Time * Time + 0.75f) + Start;
	}
	else if (Time < (2.5f / 2.75f))
	{
		Time -= (2.25f / 2.75f);
		return Final * (7.5625f * Time * Time + 0.9375f) + Start;
	}
	else
	{
		Time -= (2.625f / 2.75f);
		return Final * (7.5625f * Time * Time + 0.984375f) + Start;
	}
}

float UCsCommon::BounceEaseIn(const float &Time, const float &Start, const float &Final, const float &Duration)
{
	return Final - BounceEaseOut(Duration - Time, 0, Final, Duration) + Start;
}

float UCsCommon::BounceEaseInOut(const float &Time, const float &Start, const float &Final, const float &Duration)
{
	if (Time < (Duration / 2.0f))
		return (BounceEaseIn(Time * 2, 0, Final, Duration) * 0.5f) + Start;
	else
		return (BounceEaseOut(Time * 2 - Duration, 0, Final, Duration) * 0.5f) + Final * 0.5f + Start;
}

float UCsCommon::CubicEaseIn(float Time, const float &Start, const float &Final, const float &Duration)
{
	Time /= Duration;
	return Final * Time * Time *Time + Start;
}

float UCsCommon::CubicEaseOut(float Time, const float &Start, const float &Final, const float &Duration)
{
	Time = (Time / Duration) - 1.0f;
	return Final * ((Time *  Time * Time) + 1) + Start;
}

float UCsCommon::CubicEaseInOut(float Time, const float &Start, const float &Final, const float &Duration)
{
	if ((Time / (Duration / 2.0f)) < 1)
	{
		Time /= Duration / 2.0f;
		return (Final / (2.0f * Time * Time * Time)) + Start;
	}
	Time -= 2.0f;
	return (Final / (2 * Time * Time * Time + 2)) + Start;
}

float UCsCommon::ExpoEaseIn(const float &Time, const float &Start, const float &Final, const float &Duration)
{
	return (Time == 0.0f) ? Start : Final * FMath::Pow(2.0f, 10.0f * (Time / Duration - 1.0f)) + Start;
}

float UCsCommon::ExpoEaseOut(const float &Time, const float &Start, const float &Final, const float &Duration)
{
	return (Time == Duration) ? Start + Final : Final * (-1.0f * FMath::Pow(2.0f, -10.0f * Time / Duration) + 1.0f) + Start;
}

float UCsCommon::ExpoEaseInOut(float Time, const float &Start, const float &Final, const float &Duration)
{
	if (Time == 0)
		return Start;
	if (Time == Duration)
		return Start + Final;
	if (Duration / 2.0f < 1.0f)
	{
		Time /= Duration / 2.0f;
		return (Final / 2.0f) * FMath::Pow(2.0f, 10 * (Time - 1.0f)) + Start;
	}
	Time--;
	return (Final / 2.0f) * (-FMath::Pow(2.0f, -10.0f * Time) + 2.0f) + Start;
}

#pragma endregion Easing

void UCsCommon::GetKeyValue(const FString& Pair, FString& Key, FString& Value, const TCHAR* PairDelimiter)
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

bool UCsCommon::GrabOption(FString& Options, FString& Result)
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

FString UCsCommon::ParseOption(const FString& Options, const FString& InKey)
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

void UCsCommon::ShuffleTArray_FName(TArray<FName>& InArray)
{
	const int32 Len = InArray.Num();

	for (int32 Index = Len; Index > 1; Index--)
	{
		int32 J = FMath::RandRange(0, Index - 1);

		FName Temp		   = InArray[J];
		InArray[J]		   = InArray[Index - 1];
		InArray[Index - 1] = Temp;
	}
}

void UCsCommon::ShuffleTArray_int32(TArray<int32>& InArray)
{
	const int32 Len = InArray.Num();

	for (int32 Index = Len; Index > 1; Index--)
	{
		int32 J = FMath::RandRange(0, Index - 1);

		int32 Temp		   = InArray[J];
		InArray[J]		   = InArray[Index - 1];
		InArray[Index - 1] = Temp;
	}
}

bool UCsCommon::IsValidFpsAnimMontageArray(TArray<FCsFpsAnimMontage> & InArray, const TCsViewType &ViewType, const bool &IsLow)
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

void UCsCommon::InitComponent(USceneComponent* Component, USceneComponent* RootComponent, const ECollisionChannel &Channel, const TCsViewType &ViewType /*=ECsViewType::ECsViewType_MAXv*/)
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
		Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;

		if (RootComponent)
			Mesh->SetupAttachment(RootComponent);

		Mesh->bGenerateOverlapEvents  = false;
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
		Box->bGenerateOverlapEvents = false;
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
		Sphere->bGenerateOverlapEvents = false;
		Sphere->SetNotifyRigidBodyCollision(false);
		Sphere->SetCollisionObjectType(Channel);
		Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);

		if (RootComponent)
			Sphere->SetupAttachment(RootComponent);
	}
	Component->Deactivate();
}

void UCsCommon::EnableComponent(USceneComponent* Component, const bool &SetUpdateFlag /*=false*/)
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
			Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPoseAndRefreshBones;
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

void UCsCommon::DisableComponent(USceneComponent* Component, const bool &Detach /*=false*/, const bool &DisableCollision /*=false*/, const bool &SetUpdateFlag /*=false*/)
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
			Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
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

void UCsCommon::ClearComponent(USceneComponent* Component)
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

bool UCsCommon::CanDetachFromComponent(USceneComponent* Component)
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

bool UCsCommon::CanDetachFromComponent(USceneComponent* Component, USceneComponent* Parent)
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

void UCsCommon::SafeDetachFromComponent(USceneComponent* Component)
{
	if (CanDetachFromComponent(Component))
	{
		Component->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}

void UCsCommon::SafeDetachFromComponent(USceneComponent* Component, USceneComponent* Parent)
{
	if (CanDetachFromComponent(Component, Parent))
	{
		Component->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}

bool UCsCommon::CanAttachToComponent(USceneComponent* Component)
{
	return !Component->GetAttachParent() && Component->IsRegistered();
}

void UCsCommon::ToggleEditorIcons(AActor* InActor, const bool &IsVisible)
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

void UCsCommon::ConvertBoneSpaceTransformToComponentSpace(const FTransform& ComponentTransform, USkinnedMeshComponent* Mesh, FTransform& OutTransform, const FName &BoneName, const EBoneControlSpace &Space)
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

void UCsCommon::ConvertComponentSpaceTransformToBoneSpace(const FTransform& ComponentTransform, USkinnedMeshComponent* Mesh, FTransform& OutTransform, const FName &BoneName, const EBoneControlSpace &Space)
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

void UCsCommon::ActivateEmitter(AEmitter* InEmitter)
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

void UCsCommon::DeActivateEmitter(AEmitter* InEmitter)
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
void UCsCommon::StopAndClearEmitter(UWorld* InWorld, TWeakObjectPtr<AShooterEmitter> &InEmitter)
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

void UCsCommon::SetAndAttachEmitter(AEmitter* InEmitter, USceneComponent* Parent, FEffectsElement* Effect)
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

void UCsCommon::EndRoutine(struct FCsRoutine* r)
{
	if (r && r->IsValid())
		r->End(ECsCoroutineEndReason::Manual);
}

void UCsCommon::EndAndClearRoutine(struct FCsRoutine* &r)
{
	if (r && r->IsValid())
		r->End(ECsCoroutineEndReason::Manual);
	r = nullptr;
}

FCsRoutine* UCsCommon::ScaleActorOverTime(const TCsCoroutineSchedule &ScheduleType, const TEnumAsByte<ECsEasingType::Type> &EasingType, AActor* InActor, const float &StartScale, const float &EndScale, const float &Time, const bool &IsRelativeScale)
{
	return ScaleActorOverTime(ScheduleType, EasingType, InActor, FVector(StartScale), FVector(EndScale), Time, IsRelativeScale);
}

FCsRoutine* UCsCommon::ScaleActorOverTime(const TCsCoroutineSchedule &ScheduleType, const TEnumAsByte<ECsEasingType::Type> &EasingType, AActor* InActor, const FVector &StartScale, const FVector &EndScale, const float &Time, const bool &IsRelativeScale)
{
	if (Time <= 0.0f)
		return nullptr;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	Payload->Schedule		= ScheduleType;
	Payload->Function		= &UCsCommon::ScaleActorOverTime_Internal;
	Payload->Actor			= InActor;
	Payload->Stop			= &UCsCommon::CoroutineStopCondition_CheckActor;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsCommonCachedName::Name::ScaleActorOverTime_Internal;
	Payload->NameAsString	= ECsCommonCachedString::Str::ScaleActorOverTime_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	UWorld* World			= InActor ? InActor->GetWorld() : nullptr;
	const float CurrentTime = World ? World->GetTimeSeconds() : GetCurrentDateTimeSeconds();
	
	R->timers[0] = CurrentTime;
	R->vectors[0] = StartScale;
	R->vectors[1] = EndScale;
	R->floats[2] = Time;
	R->flags[0] = IsRelativeScale;
	R->ints[0] = (int32)EasingType;

	Scheduler->StartRoutine(ScheduleType, R);
	return R;
}

FCsRoutine* UCsCommon::ScaleActorOverTime(const TCsCoroutineSchedule &ScheduleType, UCurveBase* Curve, AActor* InActor, const float &StartScale, const float &EndScale, const float &Time, const bool &IsRelativeScale)
{
	return ScaleActorOverTime(ScheduleType, Curve, InActor, FVector(StartScale), FVector(EndScale), Time, IsRelativeScale);
}

FCsRoutine* UCsCommon::ScaleActorOverTime(const TCsCoroutineSchedule &ScheduleType, UCurveBase* Curve, AActor* InActor, const FVector &StartScale, const FVector &EndScale, const float &Time, const bool &IsRelativeScale)
{
	if (Time <= 0.0f)
		return nullptr;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();

	if (!Scheduler)
		return nullptr;

	FCsRoutine* R = nullptr;

	CsCoroutine Function		  = &UCsCommon::ScaleActorOverTime_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckActor;

	R = Scheduler->Allocate(ScheduleType, Function, Stop, InActor, true, false);

	UWorld* World			= InActor ? InActor->GetWorld() : nullptr;
	const float CurrentTime = World ? World->GetTimeSeconds() : GetCurrentDateTimeSeconds();

	R->name = ECsCommonCachedName::Name::ScaleActorOverTime_Internal;
	R->nameAsString = ECsCommonCachedString::Str::ScaleActorOverTime_Internal;

	R->timers[0] = CurrentTime;
	R->vectors[0] = StartScale;
	R->vectors[1] = EndScale;
	R->floats[2] = Time;
	R->flags[0] = IsRelativeScale;
	R->objects[0] = Curve;

	Scheduler->StartRoutine(ScheduleType, R);
	return R;
}

PT_THREAD(UCsCommon::ScaleActorOverTime_Internal(struct FCsRoutine* r))
{
	AActor* a			     = r->GetActor();
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w			     = a->GetWorld();

	const float CurrentTime = w->TimeSeconds;
	const float StartTime	= r->timers[0];
	const float MaxTime		= r->floats[2];

	const FVector StartScale = ClampVectorComponents(r->vectors[0], CS_ACTOR_SMALLEST_SCALE);
	const FVector EndScale   = ClampVectorComponents(r->vectors[1], CS_ACTOR_SMALLEST_SCALE);

	const bool IsRelativeScale						  = r->flags[0];
	const TEnumAsByte<ECsEasingType::Type> EasingType = (TEnumAsByte<ECsEasingType::Type>)r->ints[0];
	UCurveFloat* CurveFloat							  = r->objects[0].IsValid() && r->objects[0].Get() ? Cast<UCurveFloat>(r->objects[0].Get()) : nullptr;
	UCurveVector* CurveVector					      = r->objects[0].IsValid() && r->objects[0].Get() ? Cast<UCurveVector>(r->objects[0].Get()) : nullptr;

	CS_COROUTINE_BEGIN(r);

	if (r->delay > 0)
		CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime > r->delay);

	do
	{
		{
			const float Percent = FMath::Clamp((CurrentTime - StartTime) / MaxTime, 0.0f, 1.0f);
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
				a->SetActorRelativeScale3D(Scale);
			else
				a->SetActorScale3D(Scale);
		}
		CS_COROUTINE_YIELD(r);
	} while (CurrentTime - StartTime <= MaxTime);

	if (IsRelativeScale)
		a->SetActorRelativeScale3D(EndScale);
	else
		a->SetActorScale3D(EndScale);

	CS_COROUTINE_END(r);
}

FCsRoutine* UCsCommon::ScaleActorOverTime_AsCurve(const TCsCoroutineSchedule &ScheduleType, UCurveBase* Curve, AActor* InActor, const bool &IsRelativeScale)
{
	if (!Cast<UCurveFloat>(Curve) && !Cast<UCurveVector>(Curve))
		return nullptr;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	Payload->Schedule		= ScheduleType;
	Payload->Function		= &UCsCommon::ScaleActorOverTime_AsCurve_Internal;
	Payload->Actor			= InActor;
	Payload->Stop			= &UCsCommon::CoroutineStopCondition_CheckActor;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsCommonCachedName::Name::ScaleActorOverTime_AsCurve_Internal;
	Payload->NameAsString	= ECsCommonCachedString::Str::ScaleActorOverTime_AsCurve_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	UWorld* World			= InActor ? InActor->GetWorld() : nullptr;
	const float CurrentTime = World ? World->GetTimeSeconds() : GetCurrentDateTimeSeconds();

	R->timers[0] = CurrentTime;
	float MinTime = 0.0f;
	float MaxTime = 0.0f;
	Curve->GetTimeRange(MinTime, MaxTime);
	R->delay	  = MinTime > 0.0f ? MinTime : 0.0f;
	R->floats[2]  = MaxTime;
	R->flags[0]   = IsRelativeScale;
	R->flags[1] = Cast<UCurveFloat>(Curve) != nullptr; // Use CurveFloat
	R->flags[2] = Cast<UCurveVector>(Curve) != nullptr; // Use CurveVector;
	R->objects[0] = Curve;

	Scheduler->StartRoutine(ScheduleType, R);
	return R;
}

PT_THREAD(UCsCommon::ScaleActorOverTime_AsCurve_Internal(struct FCsRoutine* r))
{
	AActor* a				 = r->GetActor();
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w				 = a->GetWorld();

	const float CurrentTime = w->TimeSeconds;
	const float StartTime   = r->timers[0];
	const float MaxTime     = r->floats[2];

	const bool IsRelativeScale = r->flags[0];
	const bool UseCurveFloat = r->flags[1];
	const bool UseCurveVector = r->flags[2];
	FVector EndScale		   = FVector(1.0f);

	UCurveFloat* CurveFloat	= UseCurveFloat && r->objects[0].IsValid() && r->objects[0].Get() ? Cast<UCurveFloat>(r->objects[0].Get()) : nullptr;

	if (CurveFloat)
	{
		EndScale = FVector(CurveFloat->GetFloatValue(MaxTime));
	}

	UCurveVector* CurveVector = UseCurveVector && r->objects[0].IsValid() && r->objects[0].Get() ? Cast<UCurveVector>(r->objects[0].Get()) : nullptr;

	if (CurveVector)
	{
		EndScale = CurveVector->GetVectorValue(MaxTime);
	}

	CS_COROUTINE_BEGIN(r);

	if (r->delay > 0)
		CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime > r->delay);

	do
	{
		{
			if (!UseCurveFloat && !UseCurveVector)
				break;

			const float Percent = FMath::Clamp((CurrentTime - StartTime) / MaxTime, 0.0f, 1.0f);
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
				a->SetActorRelativeScale3D(Scale);
			else
				a->SetActorScale3D(Scale);
		}
		CS_COROUTINE_YIELD(r);
	} while (CurrentTime - StartTime <= MaxTime);

	if (IsRelativeScale)
		a->SetActorRelativeScale3D(EndScale);
	else
		a->SetActorScale3D(EndScale);

	CS_COROUTINE_END(r);
}

FCsRoutine* UCsCommon::MoveActorOverTime(const TCsCoroutineSchedule &ScheduleType, const TEnumAsByte<ECsEasingType::Type> &EasingType, AActor* InActor, const FVector &StartLocation, const FVector &EndLocation, const float &Time, const bool &IsRelativeLocation)
{
	if (Time <= 0.0f)
		return nullptr;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	Payload->Schedule		= ScheduleType;
	Payload->Function		= &UCsCommon::MoveActorOverTime_Internal;
	Payload->Actor			= InActor;
	Payload->Stop			= &UCsCommon::CoroutineStopCondition_CheckActor;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsCommonCachedName::Name::MoveActorOverTime_Internal;
	Payload->NameAsString	= ECsCommonCachedString::Str::MoveActorOverTime_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	UWorld* World			= InActor ? InActor->GetWorld() : nullptr;
	const float CurrentTime = World ? World->GetTimeSeconds() : GetCurrentDateTimeSeconds();

	R->timers[0] = CurrentTime;
	R->vectors[0] = StartLocation;
	R->vectors[1] = EndLocation;
	R->floats[0] = Time;
	R->flags[0] = IsRelativeLocation;
	R->ints[0] = (int32)EasingType;

	Scheduler->StartRoutine(ScheduleType, R);
	return R;
}

PT_THREAD(UCsCommon::MoveActorOverTime_Internal(struct FCsRoutine* r))
{
	AActor* a			     = r->GetActor();
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w			     = a->GetWorld();

	const float CurrentTime = w->TimeSeconds;
	const float StartTime   = r->timers[0];
	const float MaxTime     = r->floats[0];

	const FVector StartLocation = r->vectors[0];
	const FVector EndLocation   = r->vectors[1];

	const bool IsRelativeLocation					  = r->flags[0];
	const TEnumAsByte<ECsEasingType::Type> EasingType = (TEnumAsByte<ECsEasingType::Type>)r->ints[0];

	CS_COROUTINE_BEGIN(r);

	if (r->delay > 0)
		CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime > r->delay);

	do
	{
		{
			const float Percent    = FMath::Clamp((CurrentTime - StartTime) / MaxTime, 0.0f, 1.0f);
			float Time			   = Ease(EasingType, Percent, 0.0f, 1.0f, 1.0f);
			const FVector Location = FMath::Lerp(StartLocation, EndLocation, Time);

			if (IsRelativeLocation)
				a->SetActorRelativeLocation(Location);
			else
				a->SetActorLocation(Location);
		}
		CS_COROUTINE_YIELD(r);
	} while (CurrentTime - StartTime <= MaxTime);

	if (IsRelativeLocation)
		a->SetActorRelativeLocation(EndLocation);
	else
		a->SetActorLocation(EndLocation);

	CS_COROUTINE_END(r);
}

FCsRoutine* UCsCommon::DestroyMaterialInstanceDynamic(const TCsCoroutineSchedule &ScheduleType, UMaterialInstanceDynamic* InMID, const float &Delay)
{
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	Payload->Schedule		= ScheduleType;
	Payload->Function		= &UCsCommon::DestroyMaterialInstanceDynamic_Internal;
	Payload->Object			= InMID;
	Payload->Stop			= &UCsCommon::CoroutineStopCondition_CheckObject;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsCommonCachedName::Name::DestroyMaterialInstanceDynamic_Internal;
	Payload->NameAsString	= ECsCommonCachedString::Str::DestroyMaterialInstanceDynamic_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	UWorld* World			= InMID ? InMID->GetWorld() : nullptr;
	const float CurrentTime = World ? World->GetTimeSeconds() : GetCurrentDateTimeSeconds();

	R->timers[0] = CurrentTime;
	R->delay	 = Delay;

	Scheduler->StartRoutine(ScheduleType, R);
	return R;
}

PT_THREAD(UCsCommon::DestroyMaterialInstanceDynamic_Internal(struct FCsRoutine* r))
{
	UMaterialInstanceDynamic* m = Cast<UMaterialInstanceDynamic>(r->GetRObject());
	UCsCoroutineScheduler* s	= r->scheduler;
	UWorld* w					= m->GetWorld();

	const float CurrentTime = w->TimeSeconds;
	const float StartTime   = r->startTime;

	CS_COROUTINE_BEGIN(r);

	if (r->delay > 0)
		CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime > r->delay);

	if (m && !m->IsPendingKill())
	{
		m->MarkPendingKill();
	}

	CS_COROUTINE_END(r);
}

FCsRoutine* UCsCommon::DestroyMaterialInstanceDynamics(const TCsCoroutineSchedule &ScheduleType, TArray<UMaterialInstanceDynamic*>& InMIDs, const float &Delay)
{
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();

	if (!Scheduler)
		return nullptr;

	FCsRoutine* R = nullptr;

	CsCoroutine Function		  = &UCsCommon::DestroyMaterialInstanceDynamic_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckObject;

	int32 Count = InMIDs.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		R = Scheduler->Allocate(ScheduleType, Function, Stop, InMIDs[I], true, false);

		R->name			= ECsCommonCachedName::Name::DestroyMaterialInstanceDynamic_Internal;
		R->nameAsString = ECsCommonCachedString::Str::DestroyMaterialInstanceDynamic_Internal;

		UWorld* World			= InMIDs[I] ? InMIDs[I]->GetWorld() : nullptr;
		const float CurrentTime = World ? World->GetTimeSeconds() : GetCurrentDateTimeSeconds();

		R->timers[0] = CurrentTime;
		R->delay	 = Delay;

		Scheduler->StartRoutine(ScheduleType, R);
	}
	return R;
}

FCsRoutine* UCsCommon::FadeCameraOverTime(const TCsCoroutineSchedule &ScheduleType, const TEnumAsByte<ECsEasingType::Type> &EasingType, APlayerController* Controller, const float &Start, const float &End, const float &Time, const FLinearColor &Color)
{
	if (Time <= 0.0f)
		return nullptr;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	Payload->Schedule		= ScheduleType;
	Payload->Function		= &UCsCommon::FadeCameraOverTime_Internal;
	Payload->Actor			= Controller;
	Payload->Stop			= &UCsCommon::CoroutineStopCondition_CheckObject;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsCommonCachedName::Name::FadeCameraOverTime_Internal;
	Payload->NameAsString	= ECsCommonCachedString::Str::FadeCameraOverTime_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	UWorld* World		    = Controller ? Controller->GetWorld() : nullptr;
	const float CurrentTime = World ? World->GetTimeSeconds() : GetCurrentDateTimeSeconds();

	R->timers[0] = CurrentTime;
	R->ints[0] = (int32)EasingType;
	R->floats[0] = Start;
	R->floats[1] = End;
	R->floats[2] = Time;
	R->colors[0] = Color;

	Scheduler->StartRoutine(ScheduleType, R);
	return R;
}

PT_THREAD(UCsCommon::FadeCameraOverTime_Internal(struct FCsRoutine* r))
{
	APlayerController* pc    = Cast<APlayerController>(r->GetRObject());
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w			     = pc->GetWorld();

	const float CurrentTime = w->TimeSeconds;
	const float StartTime   = r->timers[0];
	const float MaxTime		= r->floats[2];

	const TEnumAsByte<ECsEasingType::Type> EasingType = (TEnumAsByte<ECsEasingType::Type>)r->ints[0];

	const float Start	 = r->floats[0];
	const float End		 = r->floats[1];
	const bool IsFadeOut = Start > End;
	const float Max		 = FMath::Max(Start, End);
	const float Min		 = FMath::Min(Start, End);
	const float Delta	 = Max - Min;

	const FLinearColor Color = r->colors[0];

	CS_COROUTINE_BEGIN(r);

	if (r->delay > 0)
		CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime > r->delay);

	do
	{
		{
			const float Percent = FMath::Clamp((CurrentTime - StartTime) / MaxTime, 0.0f, 1.0f);
			const float Time    = Ease(EasingType, Percent, 0.0f, 1.0f, 1.0f);
			const float Alpha	= IsFadeOut ? 1.0f - (Min + Percent * Delta) : Min + Percent * Delta;

			pc->PlayerCameraManager->SetManualCameraFade(Alpha, Color, false);
		}
		CS_COROUTINE_YIELD(r);
	} while (CurrentTime - StartTime <= MaxTime);

	pc->PlayerCameraManager->SetManualCameraFade(End, Color, false);

	CS_COROUTINE_END(r);
}
/*
FCsRoutine* UCsCommon::AllocateAndActivateEmitter(ACsCoroutineScheduler* ScheduleType, const TCsCoroutineSchedule &CoroutineSchedule, FEffectsElement* InEffectsElement, FVector Location, float Delay)
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
PT_THREAD(UCsCommon::AllocateAndActivateEmitter_Internal(struct FCsRoutine* r))
{
	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_END(r);
}
*/
void UCsCommon::CoroutineStopCondition_CheckActor(struct FCsRoutine* r)
{
	if (!r->GetActor())
		r->End(ECsCoroutineEndReason::StopCondition);
}

void UCsCommon::CoroutineStopCondition_CheckObject(struct FCsRoutine* r)
{
	if (!r->GetRObject())
		r->End(ECsCoroutineEndReason::StopCondition);
}
/*
void UCsCommon::CoroutineStopCondition_CheckCharacter(struct FRoutine* r)
{
	AShooterCharacter* c = Cast<AShooterCharacter>(r->GetActor());

	if (!c || !c->IsAlive() || !c->IsActiveAndFullyReplicated)
		r->End(ECsCoroutineEndReason::StopCondition);
}
*/
#pragma endregion Coroutine

// Javascript
#pragma region

#if WITH_EDITOR

void UCsCommon::SetupJavascript(UObject* InOwner, UWorld* InWorld, UObject* &JavascriptIsolate, UObject* &JavascriptContext, const FString &EditorJavascriptFile)
{
	auto Isolate = NewObject<UJavascriptIsolate>();
	auto Context = Isolate->CreateContext();

	JavascriptIsolate = Isolate;
	JavascriptContext = Context;

	Context->Expose("Root", InOwner);
	Context->Expose("GWorld", InWorld);
	Context->Expose("GEngine", GEngine);

	if (EditorJavascriptFile != TEXT(""))
		Context->RunFile(*EditorJavascriptFile);
}

void UCsCommon::SetupJavascript(UObject* InOwner, UWorld* InWorld, UObject* &JavascriptIsolate, UObject* &JavascriptContext)
{
	SetupJavascript(InOwner, InWorld, JavascriptIsolate, JavascriptContext, TEXT(""));
}

void UCsCommon::Javascript_ExposeObject(UObject* &JavascriptContext, const FString &Name, UObject* InObject)
{
	Cast<UJavascriptContext>(JavascriptContext)->Expose(Name, InObject);
}

void UCsCommon::Javascript_RunFile(UObject* &JavascriptContext, const FString &EditorJavascriptFile)
{
	Cast<UJavascriptContext>(JavascriptContext)->RunFile(*EditorJavascriptFile);
}

#endif // #if WITH_EDITOR

#pragma endregion Javascript

FVector UCsCommon::ClampVectorComponents(FVector V, float Clamp)
{
	V.X = FMath::Abs(V.X) < Clamp ? FMath::Sign(V.X) * Clamp : V.X;
	V.Y = FMath::Abs(V.Y) < Clamp ? FMath::Sign(V.Y) * Clamp : V.Y;
	V.Y = FMath::Abs(V.Z) < Clamp ? FMath::Sign(V.Z) * Clamp : V.Z;

	return V;
}

void UCsCommon::ClampMinVectorComponents(FVector &V, const float &Min)
{
	V.X = FMath::Max(V.X, Min);
	V.Y = FMath::Max(V.Y, Min);
	V.Z = FMath::Max(V.Z, Min);
}

void UCsCommon::ClampMaxVectorComponents(FVector &V, const float &Max)
{
	V.X = FMath::Min(V.X, Max);
	V.Y = FMath::Min(V.Y, Max);
	V.Z = FMath::Min(V.Z, Max);
}

FString UCsCommon::GetProxyAsString(AActor* InActor)
{
	if (InActor->Role < ROLE_Authority)
		return TEXT("Client");
	if (InActor->Role == ROLE_Authority)
	{
		if (IsRunningDedicatedServer() || InActor->GetNetMode() == NM_DedicatedServer)
			return TEXT("Server-Dedicated");
		return TEXT("Server");
	}
	return TEXT("Unknown");
}

bool UCsCommon::IsPlayInGame(UWorld* InWorld)
{
	return InWorld && InWorld->WorldType == EWorldType::Game;
}

bool UCsCommon::IsPlayInEditor(UWorld* InWorld)
{
	return InWorld && InWorld->WorldType == EWorldType::Editor;
}

bool UCsCommon::IsPlayInPIE(UWorld* InWorld)
{
	return InWorld && InWorld->WorldType == EWorldType::PIE;
}

bool UCsCommon::IsPlayInEditorPreview(UWorld* InWorld)
{
	return InWorld && InWorld->WorldType == EWorldType::EditorPreview;
}

bool UCsCommon::IsDefaultObject(UObject* InObject)
{
	return InObject->GetName().StartsWith(TEXT("Default__"));
}

// Time
#pragma region

uint64 UCsCommon::GetWorldTimeMilliseconds(UWorld* InWorld)
{
	return (uint64)FMath::FloorToInt(InWorld->TimeSeconds * 1000.0f);
}

float UCsCommon::GetCurrentDateTimeSeconds()
{
	FDateTime DateTime = FDateTime::Now();
	
	float Seconds = (float)DateTime.GetMinute() * 60.0f;
	Seconds		 += (float)DateTime.GetSecond();
	Seconds		 += (float)DateTime.GetMillisecond() / 1000.0f;
	
	return Seconds;
}

// TODO: Get InputManager and then get CurrentFrame. Possibly move CurrentFrame to GameInstnace since
//		 there is an InputManager for each Player
uint64 UCsCommon::GetCurrentFrame(UWorld* InWorld) { return 0; }

#pragma endregion Time

float UCsCommon::BytesToKilobytes(const int32 &Bytes)
{
	return Bytes * FMath::Pow(10, -3);
}

float UCsCommon::BytesToMegabytes(const int32 &Bytes)
{
	return Bytes * FMath::Pow(10, -6);
}

int32 UCsCommon::KilobytesToBytes(const float &Kilobytes)
{
	return Kilobytes * FMath::Pow(10, 3);
}

bool UCsCommon::IsDeveloperBuild()
{
#if UE_BUILD_SHIPPING
	return false;
#else
	return true;
#endif
}

// Physics
#pragma  region

bool UCsCommon::SetPhysicsPreset(FCsPhysicsPreset &Preset, UPrimitiveComponent* Component)
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

void UCsCommon::SetPhysicsFromPreset(FCsPhysicsPreset &Preset, UPrimitiveComponent* Component)
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

bool UCsCommon::SetColliionPreset(FCsCollisionPreset &Preset, UPrimitiveComponent* Component)
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
	IsDirty |= Component->bGenerateOverlapEvents != Preset.bGenerateOverlapEvents;
	Preset.bGenerateOverlapEvents = Component->bGenerateOverlapEvents;
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

void UCsCommon::SetCollisionFromPreset(FCsCollisionPreset &Preset, UPrimitiveComponent* Component, bool SetCollisionEnabled)
{
	FBodyInstance& BodyInstance = Component->BodyInstance;

	// bSimulationGeneratesHitEvents
	BodyInstance.bNotifyRigidBodyCollision = Preset.bSimulationGeneratesHitEvents;
	// PhysMaterialOverride
	BodyInstance.SetPhysMaterialOverride(Preset.PhysMaterialOverride.Get());
	// bGenerateOverlapEvents
	Component->bGenerateOverlapEvents = Preset.bGenerateOverlapEvents;
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

void UCsCommon::SetCollisionFromTemplate(const FName &TemplateName, UPrimitiveComponent* Component, bool SetCollisionEnabled)
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

void UCsCommon::TransitionToLevel(UWorld* InWorld, const FString &Level, const FString &GameMode)
{
	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(InWorld->GetGameInstance());
	GameInstance->PerformLevelTransition(Level, GameMode);
}

void UCsCommon::RequestEndPlayMap() 
{
#if WITH_EDITOR
	GEditor->RequestEndPlayMap();
#endif // #if WITH_EDITOR
}

#pragma endregion Level

// Editor Message
#pragma region

#if WITH_EDITOR

void UCsCommon::DisplayNotificationInfo(const FString &InTextLiteral, const FString &InNamespace, const FString &InKey, const float &Duration)
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

bool UCsCommon::CanAsyncTask()
{
	return FPlatformMisc::NumberOfCoresIncludingHyperthreads() > 1;
}