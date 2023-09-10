// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_Common.h"
#include "CsCore.h"
#include "CsCVars.h"

// Types
#include "Types/CsTypes_Curve.h"
#include "Types/CsTypes_Interpolation.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
	// Common
#include "Library/CsLibrary_SceneComponent.h"
#include "Library/CsLibrary_String.h"
#include "Library/CsLibrary_Math.h"
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Player.h"
#include "Library/CsLibrary_Valid.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Game
#include "GameFramework/GameState.h"
#include "GameFramework/GameMode.h"
//#include "Game/CsGameInstance_DEPRECATED.h"
// VR
#include "IHeadMountedDisplay.h"
#include "MotionControllerComponent.h"
//#include "MotionController/CsMotionController_DEPRECATED.h"
// Components
#include "Components/PoseableMeshComponent.h"
//#include "Components/CsStaticMeshComponent.h"
//#include "Components/CsSkeletalMeshComponent.h"
//#include "Components/CsPoseableMeshComponent.h"
//#include "Components/CsBoxComponent.h"
//#include "Components/CsSphereComponent.h"
// Player
//#include "Player/CsPlayerState.h"
//#include "Player/CsPlayerPawn.h"
//#include "VR/Player/CsPlayerPawn_VR.h"
#include "GameFramework/PlayerInput.h"
// Physics
#include "Engine/CollisionProfile.h"
// Data
//#include "Data/CsData.h"
// Managers
//#include "Managers/Inventory/CsManager_Inventory.h"
#include "Managers/Time/CsManager_Time.h"

#if WITH_EDITOR

#include "../Source/Editor/UnrealEd/Public/Editor.h"

#endif // #if WITH_EDITOR

// Cache
#pragma region

namespace NCsCommon
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCommon::FLibrary, ScaleActorOverTime);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCommon::FLibrary, ScaleActorOverTime_Internal);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCommon::FLibrary, ScaleActorOverTime_AsCurve);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCommon::FLibrary, ScaleActorOverTime_AsCurve_Internal);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCommon::FLibrary, MoveActorOverTime);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCommon::FLibrary, MoveActorOverTime_Internal);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCommon::FLibrary, DestroyMaterialInstanceDynamic);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCommon::FLibrary, DestroyMaterialInstanceDynamic_Internal);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCommon::FLibrary, FadeCameraOverTime);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCommon::FLibrary, FadeCameraOverTime_Internal);

				const FString Client = TEXT("Client");
				const FString Server_Dedicated = TEXT("Server-Dedicated");
				const FString Server = TEXT("Server");
				const FString Unknown = TEXT("Unknown");
			}

			namespace Name
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(NCsCommon::FLibrary, ScaleActorOverTime_Internal);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(NCsCommon::FLibrary, ScaleActorOverTime_AsCurve_Internal);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(NCsCommon::FLibrary, MoveActorOverTime_Internal);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(NCsCommon::FLibrary, DestroyMaterialInstanceDynamic_Internal);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(NCsCommon::FLibrary, FadeCameraOverTime_Internal);
			}
		}
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

void UCsLibrary_Common::GetLocalPlayerViewPoint(UWorld* InWorld, FVector3f &OutLocation, FRotator3f&OutRotation)
{
	//GetLocalPlayerViewPoint<APlayerController>(InWorld, OutLocation, OutRotation);
}

float UCsLibrary_Common::GetSquaredDistanceToLocalControllerEye(UWorld *InWorld, const FVector3f& Location)
{
	typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

	APlayerController* LocalController = PlayerControllerLibrary::GetFirstLocal(InWorld);

	if (!LocalController)
		return -1.0f;

	FVector3d ViewLocation;
	FRotator3d ViewRotation;
	LocalController->GetPlayerViewPoint(ViewLocation, ViewRotation);

	typedef NCsMath::FLibrary MathLibrary;

	return FVector3f::DistSquared(MathLibrary::Convert(ViewLocation), Location);
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

void UCsLibrary_Common::GetHMDOrientationAndPosition(FRotator3f& DeviceRotation, FVector3f& DevicePosition)
{
	// TODO: FIX:
	if (GEngine->StereoRenderingDevice.IsValid())// && GEngine->HMDDevice->IsHeadTrackingAllowed())
	{
		FQuat4f OrientationAsQuat;
		FVector3f Position(0.f);

		//GEngine->HMDDevice->GetCurrentOrientationAndPosition(OrientationAsQuat, Position);

		DeviceRotation = OrientationAsQuat.Rotator();
		DevicePosition = Position;
	}
	else
	{
		DeviceRotation = FRotator3f::ZeroRotator;
		DevicePosition = FVector3f::ZeroVector;
	}
}

void UCsLibrary_Common::GetHMDWorldViewPoint(UWorld* InWorld, FVector3f &OutLocation, FRotator3f& OutRotation)
{
	typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;
	typedef NCsMath::FLibrary MathLibrary;

	APlayerController* PlayerController = PlayerControllerLibrary::GetFirstLocal(InWorld);
	
	FVector3d Location;
	FRotator3d Rotation;
	PlayerController->GetPlayerViewPoint(Location, Rotation);

	OutLocation = MathLibrary::Convert(Location);
	OutRotation = MathLibrary::Convert(Rotation);

	// TODO: FIX:
	if (GEngine->StereoRenderingDevice.IsValid())// && GEngine->HMDDevice->IsHeadTrackingAllowed())
	{
		FQuat4f hmdOrientation;
		FVector3f hmdPosition;

		//GEngine->StereoRenderingDevice->GetCurrentOrientationAndPosition(hmdOrientation, hmdPosition);

		//if (GEngine->HMDDevice->GetHMDDeviceType() == EHMDDeviceType::DT_Morpheus)
		//	hmdPosition *= 100.0f;

		// get hmdPosition relative to hmdRotation's forward coordinate system - not the tracker's coordinate system
		// Example. headset is facing -X and moves head position 10 units in -X, the actual world location should be forward by 10 units

		const FVector3f X_Axis = hmdOrientation.GetAxisX();
		const FVector3f Y_Axis = hmdOrientation.GetAxisY();
		const FVector3f Z_Axis = hmdOrientation.GetAxisZ();

		FVector3f positionRelativeToHeadsetOrientation;
		positionRelativeToHeadsetOrientation.X = FVector3f::DotProduct(X_Axis, hmdPosition);
		positionRelativeToHeadsetOrientation.Y = FVector3f::DotProduct(Y_Axis, hmdPosition);
		positionRelativeToHeadsetOrientation.Z = FVector3f::DotProduct(Z_Axis, hmdPosition);

		//OutRotation = PlayerController->GetControlRotation();

		// now rotate the local position into player's world rotation
		FVector3f hmdWorldOffset(OutRotation.RotateVector(positionRelativeToHeadsetOrientation));
		OutLocation += hmdWorldOffset;
	}
}
/*
ACsMotionController_DEPRECATED* UCsLibrary_Common::GetMotionController(UWorld* InWorld, const ECsControllerHand &Hand)
{
	ACsPlayerPawn_VR* Pawn = GetLocalPawn<ACsPlayerPawn_VR>(InWorld);

	if (!Pawn)
		return nullptr;

	return Hand == ECsControllerHand::Right ? Pawn->RightHand : Pawn->LeftHand;
}
*/
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
	/*
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
	*/
	return String;
}
/*
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
*/
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
	return ECsLoadFlags::Game;
}

#pragma endregion Enum to Enum Conversion

// String
#pragma region

ERichCurveInterpMode UCsLibrary_Common::Stream_GetRichCurveInterpMode(const TCHAR*& Str)
{
	typedef NCsString::FLibrary StringLibrary;

	FString Arg;
	const bool Success = StringLibrary::Stream_GetValue(Str, Arg, true);
	return NCsRichCurveInterpMode::ToBaseType(Arg);
}

ERichCurveTangentMode UCsLibrary_Common::Stream_GetRichCurveTangentMode(const TCHAR*& Str)
{
	typedef NCsString::FLibrary StringLibrary;

	FString Arg;
	const bool Success = StringLibrary::Stream_GetValue(Str, Arg, true);
	return NCsRichCurveTangentMode::ToBaseType(Arg);
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
/*
UCsDataMapping* UCsLibrary_Common::GetDataMapping(UWorld* InWorld)
{
	//UCsGameInstance_DEPRECATED* GameInstance = Cast<UCsGameInstance_DEPRECATED>(InWorld->GetGameInstance());
	return nullptr;// GameInstance->DataMapping;
}
*/
#pragma endregion Data

FVector3f UCsLibrary_Common::GetBoneLocation(USkeletalMeshComponent* InMesh, const int32 &BoneIndex, const TEnumAsByte<EBoneSpaces::Type> &Space)
{
	if (BoneIndex <= INDEX_NONE)
	{
		UE_LOG(LogAnimation, Log, TEXT("UShooterStatics::GetBoneLocation: BoneIndex <= INDEX_NONE. Not a Valid BoneIndex."));
		return FVector3f::ZeroVector;
	}

	if (BoneIndex >= InMesh->GetNumBones())
	{
		UE_LOG(LogAnimation, Log, TEXT("UShooterStatics::GetBoneLocation: BoneIndex >= Maximum Bone Count. Not a Valid BoneIndex."));
		return FVector3f::ZeroVector;
	}

	typedef NCsMath::FLibrary MathLibrary;

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
			return FVector3f::ZeroVector;
		}
		*/
		return MathLibrary::Convert(InMesh->GetComponentSpaceTransforms()[BoneIndex].GetLocation());
	}
	else if (Space == EBoneSpaces::WorldSpace)
	{
		// To support non-uniform scale (via LocalToWorld), use GetBoneMatrix
		return MathLibrary::Convert(InMesh->GetBoneMatrix(BoneIndex).GetOrigin());
	}
	return FVector3f::ZeroVector;
}

FName UCsLibrary_Common::GetParentBone(USkeletalMeshComponent* InMesh, const int32 &BoneIndex)
{
	FName Result = NAME_None;

	if ((BoneIndex != INDEX_NONE) && (BoneIndex > 0)) // This checks that this bone is not the root (ie no parent), and that BoneIndex != INDEX_NONE (ie bone name was found)
	{
		USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(InMesh->GetSkinnedAsset());
		Result						= SkeletalMesh->GetRefSkeleton().GetBoneName(SkeletalMesh->GetRefSkeleton().GetParentIndex(BoneIndex));
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
	To.HitObjectHandle = From.HitObjectHandle;
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
	OutHitResult->HitObjectHandle = InHitResult->HitObjectHandle;
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

FRotator3f UCsLibrary_Common::Rotator_GetAngleDelta(const FRotator3f&A, const FRotator3f&B)
{
	return NCsMath::FLibrary::GetAngleDelta(A, B);
}

FRotator3f UCsLibrary_Common::Rotator_GetAbsAngleDelta(const FRotator3f&A, const FRotator3f&B)
{
	return NCsMath::FLibrary::GetAbsAngleDelta(A, B);
}

float UCsLibrary_Common::LerpAngle(const float &FromAngle, const float &ToAngle, const float &LerpRate, const float &DeltaSeconds, float MinAngle, float MaxAngle)
{
	float DeltaAngle	   = NCsMath::FLibrary::GetAngleDelta(FromAngle, ToAngle);
	const float SmallDelta = 0.001f;
	float Percent		   = FMath::Abs(DeltaAngle) > SmallDelta ? FMath::Clamp((LerpRate * DeltaSeconds) / FMath::Abs(DeltaAngle), 0.0f, 1.0f) : 1.0f;

	MinAngle = NCsMath::FLibrary::AngleClamp360(MinAngle);

	if (MinAngle > MaxAngle)
	{
		float Temp = MaxAngle;
		MaxAngle   = MinAngle;
		MinAngle   = Temp;
	}
	return FMath::Clamp(NCsMath::FLibrary::AngleClamp360(FromAngle + Percent * DeltaAngle), MinAngle, MaxAngle);
}

FVector3f UCsLibrary_Common::BuildUniformVector(const FVector3f &V, const int32 &Axes)
{
	/*
	if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_X))
		return FVector3f(V.X);
	if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Y))
		return FVector3f(V.Y);
	if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Z))
		return FVector3f(V.Z);
		*/
	return FVector3f::ZeroVector;
}

FRotator3f UCsLibrary_Common::BuildUniformRotator(const FRotator3f &R, const int32 &Axes)
{
	/*
	if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_ROLL))
		return FRotator3f(R.Roll);
	if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_PITCH))
		return FRotator3f(R.Pitch);
	if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_YAW))
		return FRotator3f(R.Yaw);
		*/
	return FRotator3f::ZeroRotator;
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

FVector3f UCsLibrary_Common::ClampVectorComponents(FVector3f V, const float &Clamp)
{
	V.X = FMath::Abs(V.X) < Clamp ? FMath::Sign(V.X) * Clamp : V.X;
	V.Y = FMath::Abs(V.Y) < Clamp ? FMath::Sign(V.Y) * Clamp : V.Y;
	V.Y = FMath::Abs(V.Z) < Clamp ? FMath::Sign(V.Z) * Clamp : V.Z;

	return V;
}

FVector3d UCsLibrary_Common::ClampVectorComponents(FVector3d V, const float& Clamp)
{
	V.X = FMath::Abs(V.X) < Clamp ? FMath::Sign(V.X) * Clamp : V.X;
	V.Y = FMath::Abs(V.Y) < Clamp ? FMath::Sign(V.Y) * Clamp : V.Y;
	V.Y = FMath::Abs(V.Z) < Clamp ? FMath::Sign(V.Z) * Clamp : V.Z;

	return V;
}

void UCsLibrary_Common::ClampMinVectorComponents(FVector3f&V, const float &Min)
{
	V.X = FMath::Max(V.X, Min);
	V.Y = FMath::Max(V.Y, Min);
	V.Z = FMath::Max(V.Z, Min);
}

void UCsLibrary_Common::ClampMinVectorComponents(FVector3d& V, const float& Min)
{
	V.X = FMath::Max(V.X, Min);
	V.Y = FMath::Max(V.Y, Min);
	V.Z = FMath::Max(V.Z, Min);
}

void UCsLibrary_Common::ClampMaxVectorComponents(FVector3f&V, const float &Max)
{
	V.X = FMath::Min(V.X, Max);
	V.Y = FMath::Min(V.Y, Max);
	V.Z = FMath::Min(V.Z, Max);
}

void UCsLibrary_Common::ClampMaxVectorComponents(FVector3d& V, const float& Max)
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
FVector3f UCsLibrary_Common::GetScaledPlayerViewDirection(AController* Controller, const FVector3f &Scale)
{
	if (!Controller)
		return FVector3f::ZeroVector;

	FVector3d Origin;
	FRotator3d Rotation;

	Controller->GetPlayerViewPoint(Origin, Rotation);

	Rotation.Pitch = 0.0;
	Rotation.Roll  = 0.0;

	FRotationMatrix44d Matrix = FRotationMatrix44d(Rotation);
	const FVector3d Forward   = Scale.X * Matrix.GetScaledAxis(EAxis::X);
	const FVector3d Right	  = Scale.Y * Matrix.GetScaledAxis(EAxis::Y);
	const FVector3d Up	      = Scale.Z * Matrix.GetScaledAxis(EAxis::Z);

	const FVector3d Result = Forward + Right + Up;
	
	typedef NCsMath::FLibrary MathLibrary;

	return MathLibrary::Convert(Result);
}
/*
void UCsLibrary_Common::GetHMDWorldViewPoint(APlayerController* PlayerController, FVector3f& out_Location, FRotator& out_Rotation)
{
	check(PlayerController);

	PlayerController->GetPlayerViewPoint(out_Location, out_Rotation);

	if (UShooterStatics::IsStereoscopic3D() && PlayerController->IsLocalPlayerController())
	{
		FQuat hmdOrientation;
		FVector3f hmdPosition;

		GEngine->HMDDevice->GetCurrentOrientationAndPosition(hmdOrientation, hmdPosition);

		if (GEngine->HMDDevice->GetHMDDeviceType() == EHMDDeviceType::DT_Morpheus)
			hmdPosition *= 100.0f;

		// get hmdPosition relative to hmdRotation's forward coordinate system - not the tracker's coordinate system
		// Example. headset is facing -X and moves head position 10 units in -X, the actual world location should be forward by 10 units

		const FVector3f X_Axis = hmdOrientation.GetAxisX();
		const FVector3f Y_Axis = hmdOrientation.GetAxisY();
		const FVector3f Z_Axis = hmdOrientation.GetAxisZ();

		FVector3f positionRelativeToHeadsetOrientation;
		positionRelativeToHeadsetOrientation.X = FVector3f::DotProduct(X_Axis, hmdPosition);
		positionRelativeToHeadsetOrientation.Y = FVector3f::DotProduct(Y_Axis, hmdPosition);
		positionRelativeToHeadsetOrientation.Z = FVector3f::DotProduct(Z_Axis, hmdPosition);

		out_Rotation = PlayerController->GetControlRotation();

		// now rotate the local position into player's world rotation
		FVector3f hmdWorldOffset(out_Rotation.RotateVector(positionRelativeToHeadsetOrientation));
		out_Location += hmdWorldOffset;
	}
}
*/

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
		Mesh->SetVisibility(false);

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
	typedef NCsMaterial::FLibrary MaterialLibrary;

	// Mesh Component
	if (UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Component))
	{
		// TODO:
		//MaterialLibrary::ClearOverrideChecked(Context, Mesh);
		Mesh->SetStaticMesh(nullptr);
	}
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(Component))
	{
		// TODO:
		//MaterialLibrary::ClearOverrideChecked(Context, Mesh);
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

void UCsLibrary_Common::ConvertBoneSpaceTransformToComponentSpace(const FTransform3d& ComponentTransform, USkinnedMeshComponent* Mesh, FTransform3d& OutTransform, const FName &BoneName, const EBoneControlSpace &Space)
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
					const FTransform3d& ParentTransform = Mesh->GetBoneTransform(ParentBoneIndex);
					OutTransform					 *= ParentTransform;
				}
			}
			break;

		case BCS_BoneSpace:
			if (BoneIndex != INDEX_NONE)
			{
				if (USkeletalMeshComponent* Component = Cast<USkeletalMeshComponent>(Mesh))
				{
					const FTransform3d BoneTransform = Component->GetBoneSpaceTransforms()[BoneIndex];
					OutTransform				   *= BoneTransform;
				}

				if (UPoseableMeshComponent* Component = Cast<UPoseableMeshComponent>(Mesh))
				{
					const FTransform3d& BoneTransform = Component->BoneSpaceTransforms[BoneIndex];
					OutTransform				   *= BoneTransform;
				}
			}
			break;

		default:
			break;
	}
}

void UCsLibrary_Common::ConvertComponentSpaceTransformToBoneSpace(const FTransform3d& ComponentTransform, USkinnedMeshComponent* Mesh, FTransform3d& OutTransform, const FName &BoneName, const EBoneControlSpace &Space)
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
				const FTransform3d& ParentTransform = Mesh->GetBoneTransform(ParentBoneIndex);
				OutTransform.SetToRelativeTransform(ParentTransform);
			}
		}
		break;

		case BCS_BoneSpace:
		{
			if (USkeletalMeshComponent* Component = Cast<USkeletalMeshComponent>(Mesh))
			{
				const FTransform3d BoneTransform = Component->GetBoneSpaceTransforms()[BoneIndex];
				OutTransform.SetToRelativeTransform(BoneTransform);
			}

			if (UPoseableMeshComponent* Component = Cast<UPoseableMeshComponent>(Mesh))
			{
				const FTransform3d& BoneTransform = Component->GetBoneSpaceTransforms()[BoneIndex];
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
	return ScaleActorOverTime(Group, EasingType, InActor, FVector3f(StartScale), FVector3f(EndScale), Time, IsRelativeScale);
}

const FCsRoutineHandle& UCsLibrary_Common::ScaleActorOverTime(const FECsUpdateGroup& Group, const ECsEasingType& EasingType, AActor* InActor, const FVector3f& StartScale, const FVector3f& EndScale, const float& Time, const bool& IsRelativeScale)
{
	using namespace NCsCommon::NLibrary::NCached;

	const FString& Context = Str::ScaleActorOverTime;

	CS_IS_INT_GREATER_THAN_CHECKED(Time, 0.0f)

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = CoroutineSchedulerLibrary::AllocatePayloadChecked(Context, InActor, Group);

	typedef UCsLibrary_Common ClassType;
	#define COROUTINE ScaleActorOverTime_Internal

	Payload->Init(Context, &ClassType::COROUTINE, InActor, InActor, Group, Str::COROUTINE, Name::COROUTINE);

	#undef COROUTINE

	CS_COROUTINE_PAYLOAD_PASS_FLAG_START
	CS_COROUTINE_PAYLOAD_PASS_INT_START
	CS_COROUTINE_PAYLOAD_PASS_FLOAT_START
	CS_COROUTINE_PAYLOAD_PASS_VECTOR_START

	// Start Scale
	CS_COROUTINE_PAYLOAD_PASS_VECTOR(Payload, StartScale);
	// End Scale
	CS_COROUTINE_PAYLOAD_PASS_VECTOR(Payload, EndScale);

	// Time
	CS_COROUTINE_PAYLOAD_PASS_FLOAT(Payload, Time);

	// Is Relative Scale
	CS_COROUTINE_PAYLOAD_PASS_FLAG(Payload, IsRelativeScale);
	// Easing Type
	CS_COROUTINE_PAYLOAD_PASS_INT(Payload, (int32)EasingType);

	return CoroutineSchedulerLibrary::StartChecked(Context, InActor, Payload);
}

const FCsRoutineHandle& UCsLibrary_Common::ScaleActorOverTime(const FECsUpdateGroup& Group, UCurveBase* Curve, AActor* InActor, const float& StartScale, const float& EndScale, const float& Time, const bool& IsRelativeScale)
{
	return ScaleActorOverTime(Group, Curve, InActor, FVector3f(StartScale), FVector3f(EndScale), Time, IsRelativeScale);
}

const FCsRoutineHandle& UCsLibrary_Common::ScaleActorOverTime(const FECsUpdateGroup& Group, UCurveBase* Curve, AActor* InActor, const FVector3f& StartScale, const FVector3f& EndScale, const float& Time, const bool& IsRelativeScale)
{
	using namespace NCsCommon::NLibrary::NCached;

	const FString& Context = Str::ScaleActorOverTime;

	//CS_IS_INT_GREATER_THAN_OR_EQUAL_RET_VALUE(Time, 0.0f, FCsRoutineHandle::Invalid)

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = CoroutineSchedulerLibrary::AllocatePayloadChecked(Context, InActor, Group);

	typedef UCsLibrary_Common ClassType;
	#define COROUTINE ScaleActorOverTime_Internal

	Payload->Init(Context, &ClassType::COROUTINE, InActor, InActor, Group, Str::COROUTINE, Name::COROUTINE);

	#undef COROUTINE

	CS_COROUTINE_PAYLOAD_PASS_FLAG_START
	CS_COROUTINE_PAYLOAD_PASS_FLOAT_START
	CS_COROUTINE_PAYLOAD_PASS_VECTOR_START
	CS_COROUTINE_PAYLOAD_PASS_OBJECT_START

	// Start Scale
	CS_COROUTINE_PAYLOAD_PASS_VECTOR(Payload, StartScale);
	// End Scale
	CS_COROUTINE_PAYLOAD_PASS_VECTOR(Payload, EndScale);

	// Time
	CS_COROUTINE_PAYLOAD_PASS_FLOAT(Payload, Time);

	// Is Relative Scale
	CS_COROUTINE_PAYLOAD_PASS_FLAG(Payload, IsRelativeScale);
	// Curve
	CS_COROUTINE_PAYLOAD_PASS_OBJECT(Payload, Curve);

	return CoroutineSchedulerLibrary::StartChecked(Context, InActor, Payload);
}

char UCsLibrary_Common::ScaleActorOverTime_Internal(FCsRoutine* R)
{
	using namespace NCsCommon::NLibrary::NCached;

	const FString& Context = Str::ScaleActorOverTime_Internal;

	CS_COROUTINE_READ_FLAG_START
	CS_COROUTINE_READ_DELTA_TIME_START
	CS_COROUTINE_READ_INT_START
	CS_COROUTINE_READ_FLOAT_START
	CS_COROUTINE_READ_VECTOR_START
	CS_COROUTINE_READ_OBJECT_START

	AActor* A = R->GetOwnerAsActor();

	// Max Time
	CS_COROUTINE_READ_FLOAT_CONST_REF(R, MaxTime);

	// Start Scale
	CS_COROUTINE_READ_VECTOR(R, StartScale);
	StartScale = ClampVectorComponents(StartScale, CS_ACTOR_SMALLEST_SCALE);
	// End Scale
	CS_COROUTINE_READ_VECTOR(R, EndScale);
	EndScale = ClampVectorComponents(EndScale, CS_ACTOR_SMALLEST_SCALE);

	// Is Relative Scale
	CS_COROUTINE_READ_FLAG_CONST_REF(R, IsRelativeScale);
	// Easing Type
	CS_COROUTINE_READ_INT_AS_ENUM_CONST(R, EasingType, ECsEasingType);
	// Curve Float
	CS_COROUTINE_READ_OBJECT_AS(R, CurveFloat, UCurveFloat);
	CS_COROUTINE_READ_OBJECT_AS(R, CurveVector, UCurveVector);

	// Elapsed Time
	CS_COROUTINE_READ_DELTA_TIME_REF(R, ElapsedTime);
	ElapsedTime += R->DeltaTime;

	typedef NCsMath::FLibrary MathLibrary;

	CS_COROUTINE_BEGIN(R);

	ElapsedTime.Reset();

	if (R->Delay > 0.0f)
		CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time > R->Delay);

	ElapsedTime.Reset();

	do
	{
		{
			const float Percent = FMath::Clamp(ElapsedTime.Time / MaxTime, 0.0f, 1.0f);
			FVector3f Scale		= EndScale;

			if (CurveFloat)
			{
				float Time = CurveFloat->GetFloatValue(Percent);
				Scale	   = ClampVectorComponents(FMath::Lerp(StartScale, EndScale, Time), CS_ACTOR_SMALLEST_SCALE);
			}
			else
			if (CurveVector)
			{
				FVector3f Times = MathLibrary::Convert(CurveVector->GetVectorValue(Percent));

				Scale.X	= FMath::Lerp(StartScale.X, EndScale.X, Times.X);
				Scale.X	= FMath::Abs(Scale.X) < CS_ACTOR_SMALLEST_SCALE ? FMath::Sign(Scale.X) * CS_ACTOR_SMALLEST_SCALE : Scale.X;
				Scale.Y = FMath::Lerp(StartScale.Y, EndScale.Y, Times.Y);
				Scale.Y = FMath::Abs(Scale.Y) < CS_ACTOR_SMALLEST_SCALE ? FMath::Sign(Scale.Y) * CS_ACTOR_SMALLEST_SCALE : Scale.Y;
				Scale.Z = FMath::Lerp(StartScale.Z, EndScale.Z, Times.Z);
				Scale.Z = FMath::Abs(Scale.Z) < CS_ACTOR_SMALLEST_SCALE ? FMath::Sign(Scale.Z) * CS_ACTOR_SMALLEST_SCALE : Scale.Z;
			}
			else
			{
				float Time = MathLibrary::Ease(EasingType, Percent, 0.0f, 1.0f, 1.0f);
				Scale	   = ClampVectorComponents(FMath::Lerp(StartScale, EndScale, Time), CS_ACTOR_SMALLEST_SCALE);
			}

			if (IsRelativeScale)
				A->SetActorRelativeScale3D(MathLibrary::Convert(Scale));
			else
				A->SetActorScale3D(MathLibrary::Convert(Scale));
		}
		CS_COROUTINE_YIELD(R);
	} while (ElapsedTime.Time <= MaxTime);

	if (IsRelativeScale)
		A->SetActorRelativeScale3D(MathLibrary::Convert(EndScale));
	else
		A->SetActorScale3D(MathLibrary::Convert(EndScale));

	CS_COROUTINE_END(R);
}

const FCsRoutineHandle& UCsLibrary_Common::ScaleActorOverTime_AsCurve(const FECsUpdateGroup& Group, UCurveBase* Curve, AActor* InActor, const bool& IsRelativeScale)
{
	using namespace NCsCommon::NLibrary::NCached;

	const FString& Context = Str::ScaleActorOverTime_AsCurve;

	if (!Cast<UCurveFloat>(Curve) && !Cast<UCurveVector>(Curve))
	{
		// Log Warning
		return FCsRoutineHandle::Invalid;
	}

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = CoroutineSchedulerLibrary::AllocatePayloadChecked(Context, InActor, Group);

	typedef UCsLibrary_Common ClassType;
	#define COROUTINE ScaleActorOverTime_AsCurve_Internal

	Payload->Init(Context, &ClassType::COROUTINE, InActor, InActor, Group, Str::COROUTINE, Name::COROUTINE);

	#undef COROUTINE

	CS_COROUTINE_PAYLOAD_PASS_FLAG_START
	CS_COROUTINE_PAYLOAD_PASS_FLOAT_START
	CS_COROUTINE_PAYLOAD_PASS_OBJECT_START

	// TODO: Add Delay to Payload
	float MinTime = 0.0f;
	float MaxTime = 0.0f;
	/*
	Curve->GetTimeRange(MinTime, MaxTime);
	R->delay	  = MinTime > 0.0f ? MinTime : 0.0f;
	*/

	// Max Time
	CS_COROUTINE_PAYLOAD_PASS_FLOAT(Payload, MaxTime);
	// Is Relative Scale
	CS_COROUTINE_PAYLOAD_PASS_FLAG(Payload, IsRelativeScale);
	// Use Curve Float
	const bool UseCurveFloat = Cast<UCurveFloat>(Curve) != nullptr;
	CS_COROUTINE_PAYLOAD_PASS_FLAG(Payload, UseCurveFloat);
	// Use Curve Vector
	const bool UseCurveVector = Cast<UCurveVector>(Curve) != nullptr;
	CS_COROUTINE_PAYLOAD_PASS_FLAG(Payload, UseCurveVector);
	
	// Curve
	CS_COROUTINE_PAYLOAD_PASS_OBJECT(Payload, Curve);

	return CoroutineSchedulerLibrary::StartChecked(Context, InActor, Payload);
}

char UCsLibrary_Common::ScaleActorOverTime_AsCurve_Internal(FCsRoutine* R)
{
	using namespace NCsCommon::NLibrary::NCached;

	const FString& Context = Str::ScaleActorOverTime_AsCurve_Internal;

	CS_COROUTINE_READ_FLAG_START
	CS_COROUTINE_READ_DELTA_TIME_START
	CS_COROUTINE_READ_FLOAT_START
	CS_COROUTINE_READ_OBJECT_START

	AActor* A= R->GetOwnerAsActor();

	// Max Time
	CS_COROUTINE_READ_FLOAT_CONST_REF(R, MaxTime);
	// Is Relative Scale
	CS_COROUTINE_READ_FLAG_CONST_REF(R, IsRelativeScale);
	// Use Curve Float
	CS_COROUTINE_READ_FLAG_CONST_REF(R, UseCurveFloat);
	// Use Curve Vector
	CS_COROUTINE_READ_FLAG_CONST_REF(R, UseCurveVector);

	FVector3d EndScale = FVector3d(1.0f);
	
	// Curve Float
	CS_COROUTINE_READ_OBJECT_AS(R, CurveFloat, UCurveFloat);

	if (UseCurveFloat && CurveFloat)
	{
		EndScale = FVector3d(CurveFloat->GetFloatValue(MaxTime));
	}

	// Curve Vector
	CS_COROUTINE_READ_OBJECT_AS(R, CurveVector, UCurveVector);

	if (UseCurveVector && CurveVector)
	{
		EndScale = CurveVector->GetVectorValue(MaxTime);
	}

	// Elapsed Time
	CS_COROUTINE_READ_DELTA_TIME_REF(R, ElapsedTime);
	ElapsedTime += R->DeltaTime;

	typedef NCsMath::FLibrary MathLibrary;

	CS_COROUTINE_BEGIN(R);

	ElapsedTime.Reset();

	if (R->Delay > 0)
		CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time > R->Delay);

	ElapsedTime.Reset();

	do
	{
		{
			if (!UseCurveFloat && !UseCurveVector)
				break;

			const float Percent = FMath::Clamp(ElapsedTime.Time / MaxTime, 0.0f, 1.0f);
			FVector3d Scale		= FVector3d(1.0f);

			if (CurveFloat)
			{
				float Value = CurveFloat->GetFloatValue(Percent);
				Value		= FMath::Abs(Value) < CS_ACTOR_SMALLEST_SCALE ? FMath::Sign(Value) * CS_ACTOR_SMALLEST_SCALE : Value;
				Scale		= FVector3d(Value);
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
	} while (ElapsedTime.Time <= MaxTime);

	if (IsRelativeScale)
		A->SetActorRelativeScale3D(EndScale);
	else
		A->SetActorScale3D(EndScale);

	CS_COROUTINE_END(R);
}

const FCsRoutineHandle& UCsLibrary_Common::MoveActorOverTime(const FECsUpdateGroup& Group, const ECsEasingType& EasingType, AActor* InActor, const FVector3f& StartLocation, const FVector3f& EndLocation, const float& Time, const bool& IsRelativeLocation)
{
	using namespace NCsCommon::NLibrary::NCached;

	const FString& Context = Str::MoveActorOverTime;

	CS_IS_FLOAT_GREATER_THAN_CHECKED(Time, 0.0f)

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = CoroutineSchedulerLibrary::AllocatePayloadChecked(Context, InActor, Group);

	typedef UCsLibrary_Common ClassType;
	#define COROUTINE MoveActorOverTime_Internal

	Payload->Init(Context, &ClassType::COROUTINE, InActor, InActor, Group, Str::COROUTINE, Name::COROUTINE);

	#undef COROUTINE

	CS_COROUTINE_PAYLOAD_PASS_FLAG_START
	CS_COROUTINE_PAYLOAD_PASS_INT_START
	CS_COROUTINE_PAYLOAD_PASS_FLOAT_START
	CS_COROUTINE_PAYLOAD_PASS_VECTOR_START

	// Start Location
	CS_COROUTINE_PAYLOAD_PASS_VECTOR(Payload, StartLocation);
	// End Location
	CS_COROUTINE_PAYLOAD_PASS_VECTOR(Payload, EndLocation);
	// Time
	CS_COROUTINE_PAYLOAD_PASS_FLOAT(Payload, Time);
	// Is Relative Location
	CS_COROUTINE_PAYLOAD_PASS_FLAG(Payload, IsRelativeLocation);
	// Easing Type
	CS_COROUTINE_PAYLOAD_PASS_INT(Payload, (int32)EasingType);

	return CoroutineSchedulerLibrary::StartChecked(Context, InActor, Payload);
}

char UCsLibrary_Common::MoveActorOverTime_Internal(FCsRoutine* R)
{
	using namespace NCsCommon::NLibrary::NCached;

	const FString& Context = Str::MoveActorOverTime_Internal;

	CS_COROUTINE_READ_FLAG_START
	CS_COROUTINE_READ_DELTA_TIME_START
	CS_COROUTINE_READ_INT_START
	CS_COROUTINE_READ_FLOAT_START
	CS_COROUTINE_READ_VECTOR_START

	AActor* A = R->GetOwnerAsActor();

	// Max Time
	CS_COROUTINE_READ_FLOAT_CONST_REF(R, MaxTime);
	// Start Location
	CS_COROUTINE_READ_VECTOR_CONST_REF(R, StartLocation);
	// End Location
	CS_COROUTINE_READ_VECTOR_CONST_REF(R, EndLocation);
	// Is Relative Location
	CS_COROUTINE_READ_FLAG_CONST_REF(R, IsRelativeLocation);
	// Easing Type
	CS_COROUTINE_READ_INT_AS_ENUM_CONST(R, EasingType, ECsEasingType);

	// Elapsed Time
	CS_COROUTINE_READ_DELTA_TIME_REF(R, ElapsedTime);
	ElapsedTime += R->DeltaTime;

	typedef NCsMath::FLibrary MathLibrary;

	CS_COROUTINE_BEGIN(R);

	ElapsedTime.Reset();

	if (R->Delay > 0)
		CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time > R->Delay);

	ElapsedTime.Reset();

	do
	{
		{
			const float Percent    = FMath::Clamp(ElapsedTime.Time / MaxTime, 0.0f, 1.0f);
			float Time			   = MathLibrary::Ease(EasingType, Percent, 0.0f, 1.0f, 1.0f);
			const FVector3d Location = MathLibrary::Convert(FMath::Lerp(StartLocation, EndLocation, Time));

			if (IsRelativeLocation)
				A->SetActorRelativeLocation(Location);
			else
				A->SetActorLocation(Location);
		}
		CS_COROUTINE_YIELD(R);
	} while (ElapsedTime.Time <= MaxTime);

	if (IsRelativeLocation)
		A->SetActorRelativeLocation(MathLibrary::Convert(EndLocation));
	else
		A->SetActorLocation(MathLibrary::Convert(EndLocation));

	CS_COROUTINE_END(R);
}

const FCsRoutineHandle& UCsLibrary_Common::DestroyMaterialInstanceDynamic(const FECsUpdateGroup& Group, UMaterialInstanceDynamic* InMID, const float& Delay)
{
	using namespace NCsCommon::NLibrary::NCached;

	const FString& Context = Str::DestroyMaterialInstanceDynamic;

	/*
	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = CoroutineSchedulerLibrary::AllocatePayloadChecked(Context, ContextObject, Group);

	typedef UCsLibrary_Common ClassType;
	#define COROUTINE DestroyMaterialInstanceDynamic_Internal

	Payload->Init(Context, &ClassType::COROUTINE, InActor, ContextObject, Group, Str::COROUTINE, Name::COROUTINE);

	#undef COROUTINE
	*/

	//return CoroutineSchedulerLibrary::StartChecked(Context, ContextObject, Payload);
	return FCsRoutineHandle::Invalid;
}

char UCsLibrary_Common::DestroyMaterialInstanceDynamic_Internal(FCsRoutine* R)
{
	UMaterialInstanceDynamic* M = R->GetOwnerAsObject<UMaterialInstanceDynamic>();

	const FCsTime& CurrentTime = UCsManager_Time::Get()->GetTime(R->GetGroup());
	const FCsTime& StartTime   = R->StartTime;

	CS_COROUTINE_BEGIN(R);

	if (R->Delay > 0)
		CS_COROUTINE_WAIT_UNTIL(R, CurrentTime.Time - StartTime.Time > R->Delay);

	M->MarkAsGarbage();

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
		NCsCoroutine::NPayload::FImpl* Payload = Scheduler->AllocatePayload(Group);

		Payload->CoroutineImpl.BindStatic(&UCsLibrary_Common::DestroyMaterialInstanceDynamic_Internal);
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
	using namespace NCsCommon::NLibrary::NCached;

	const FString& Context = Str::FadeCameraOverTime;

	if (Time <= 0.0f)
	{
		// Log Warning
		return FCsRoutineHandle::Invalid;
	}

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = CoroutineSchedulerLibrary::AllocatePayloadChecked(Context, Controller, Group);

	typedef UCsLibrary_Common ClassType;
	#define COROUTINE FadeCameraOverTime_Internal

	Payload->Init(Context, &ClassType::COROUTINE, Controller, Controller, Group, Str::COROUTINE, Name::COROUTINE);

	#undef COROUTINE

	CS_COROUTINE_PAYLOAD_PASS_INT_START
	CS_COROUTINE_PAYLOAD_PASS_FLOAT_START
	CS_COROUTINE_PAYLOAD_PASS_COLOR_START

	// Easing Type
	CS_COROUTINE_PAYLOAD_PASS_INT(Payload, (int32)EasingType);
	// Start
	CS_COROUTINE_PAYLOAD_PASS_FLOAT(Payload, Start);
	// End
	CS_COROUTINE_PAYLOAD_PASS_FLOAT(Payload, End);
	// Time
	CS_COROUTINE_PAYLOAD_PASS_FLOAT(Payload, Time);
	// Color
	CS_COROUTINE_PAYLOAD_PASS_COLOR(Payload, Color);

	return CoroutineSchedulerLibrary::StartChecked(Context, Controller, Payload);
}

char UCsLibrary_Common::FadeCameraOverTime_Internal(FCsRoutine* R)
{
	using namespace NCsCommon::NLibrary::NCached;

	const FString& Context = Str::FadeCameraOverTime_Internal;

	CS_COROUTINE_READ_INT_START
	CS_COROUTINE_READ_FLOAT_START
	CS_COROUTINE_READ_COLOR_START
	CS_COROUTINE_READ_DELTA_TIME_START

	APlayerController* PC = R->GetOwnerAsObject<APlayerController>();

	// Start
	CS_COROUTINE_READ_FLOAT_CONST_REF(R, Start);
	// End
	CS_COROUTINE_READ_FLOAT_CONST_REF(R, End);
	// Max Time
	CS_COROUTINE_READ_FLOAT_CONST_REF(R, MaxTime);
	// Easing Type
	CS_COROUTINE_READ_INT_AS_ENUM_CONST(R, EasingType, ECsEasingType);

	const bool IsFadeOut = Start > End;
	const float Max		 = FMath::Max(Start, End);
	const float Min		 = FMath::Min(Start, End);
	const float Delta	 = Max - Min;

	// Color
	CS_COROUTINE_READ_COLOR_CONST_REF(R, Color);

	// Elapsed Time
	CS_COROUTINE_READ_DELTA_TIME_REF(R, ElapsedTime);
	ElapsedTime += R->DeltaTime;

	CS_COROUTINE_BEGIN(R);

	ElapsedTime.Reset();

	if (R->Delay > 0)
		CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time > R->Delay);

	ElapsedTime.Reset();

	do
	{
		{
			typedef NCsMath::FLibrary MathLibrary;

			const float Percent = FMath::Clamp((ElapsedTime.Time) / MaxTime, 0.0f, 1.0f);
			const float Time    = MathLibrary::Ease(EasingType, Percent, 0.0f, 1.0f, 1.0f);
			const float Alpha	= IsFadeOut ? 1.0f - (Min + Percent * Delta) : Min + Percent * Delta;

			PC->PlayerCameraManager->SetManualCameraFade(Alpha, Color, false);
		}
		CS_COROUTINE_YIELD(R);
	} while (ElapsedTime.Time <= MaxTime);

	PC->PlayerCameraManager->SetManualCameraFade(End, Color, false);

	CS_COROUTINE_END(R);
}

#pragma endregion Coroutine

bool UCsLibrary_Common::IsDedicatedServer(AActor* InActor)
{
	return IsRunningDedicatedServer() || InActor->GetNetMode() == NM_DedicatedServer;
}

FString UCsLibrary_Common::GetProxyAsString(AActor* InActor)
{
	using namespace NCsCommon::NLibrary::NCached;

	if (InActor->GetLocalRole() < ROLE_Authority)
		return Str::Client;
	if (InActor->GetLocalRole() == ROLE_Authority)
	{
		if (IsDedicatedServer(InActor))
			return Str::Server_Dedicated;
		return Str::Server;
	}
	return Str::Unknown;
}

bool UCsLibrary_Common::IsDefaultObject(UObject* InObject)
{
	return InObject->GetName().StartsWith(TEXT("Default__"));
}

/*
const uint64& UCsLibrary_Common::GetUniqueObjectId(AActor* Actor)
{
	if (ACsPawn* Pawn = Cast<ACsPawn>(Actor))
		return Pawn->UniqueObjectId;
	return CS_INVALID_UNIQUE_OBJECT_ID;
}
*/

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
	//UCsGameInstance_DEPRECATED* GameInstance = Cast<UCsGameInstance_DEPRECATED>(InWorld->GetGameInstance());
	//GameInstance->PerformLevelTransition(Level, GameMode);
}

void UCsLibrary_Common::RequestEndPlayMap() 
{
#if WITH_EDITOR
	GEditor->RequestEndPlayMap();
#endif // #if WITH_EDITOR
}

#pragma endregion Level

bool UCsLibrary_Common::CanAsyncTask()
{
	return FPlatformProcess::SupportsMultithreading() && FPlatformMisc::NumberOfCoresIncludingHyperthreads() > 1;
}