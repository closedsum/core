// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/CsTypes.h"
#include "Animation/CsTypes_Anim.h"
#include "Collision/CsTypes_Collision.h"
#include "Coroutine/CsTypes_Coroutine.h"
#include "Types/CsTypes_Interpolation.h"

#include "CsLibrary_Common.generated.h"

struct FCsRoutine;

UCLASS()
class CSCORE_API UCsLibrary_Common : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/*
	static bool IsControlledByClient(AShooterCharacter* InPawn);

	UFUNCTION(BlueprintCallable, Category = "Pawn")
	static AShooterPlayerController* GetClientController(AShooterCharacter* InPawn);

	UFUNCTION(BlueprintCallable, Category = "Pawn")
	static AShooterPlayerController* GetMachineClientController(UWorld *InWorld);

	UFUNCTION(BlueprintCallable, Category = "Pawn")
	static bool IsLocallyControlled(AShooterCharacter* InPawn, UWorld *InWorld);

	static FORCEINLINE float GetAngleBetweenVectors(const FVector3f& v1, const FVector3f& v2)
	{
		float dotValue = FVector3f::DotProduct(v1, v2);
		float radians = FMath::Acos(dotValue);
		return FMath::RadiansToDegrees(radians);
	}

	static float GetSquaredDistanceToLocalControllerEye(UWorld *InWorld, const FVector3f& otherLocation);
	*/

// Local Client
#pragma region
public:

	static void GetLocalPlayerViewPoint(UWorld* InWorld, FVector3f &OutLocation, FRotator3f&OutRotation);

	UFUNCTION(BlueprintCallable, Category = "Common")
	static float GetSquaredDistanceToLocalControllerEye(UWorld *InWorld, const FVector3f& Location);

	//static class ACsMotionController_DEPRECATED* GetLocalHand(UWorld *InWorld, const ECsControllerHand &Hand);

	//static class ACsManager_Inventory* GetLocalManager_Inventory(UWorld *InWorld);

#pragma endregion Local Client

// VR
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static bool IsVR();
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static bool IsVive();
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static bool IsRift();

	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static void GetHMDOrientationAndPosition(FRotator3f& DeviceRotation, FVector3f& DevicePosition);

	UFUNCTION(BlueprintCallable, Category = "Common")
	static void GetHMDWorldViewPoint(UWorld* InWorld, FVector3f &OutLocation, FRotator3f& OutRotation);

	//UFUNCTION(BlueprintCallable, Category = "Commmon")
	//static class ACsMotionController_DEPRECATED* GetMotionController(UWorld* InWorld, const ECsControllerHand &Hand);

	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static bool IsStereoscopic3D();

#pragma endregion

// Delegates
#pragma region

#pragma endregion Delegates

// Enum to String Conversion
#pragma region

	static FString LoadFlagsToString(const int32 &LoadFlags);

	//static FString InteractivePhysicsStateToString(const int32 &PhysicsState);

#pragma endregion Enum to String Conversion

// Enum to Enum Conversion
#pragma region

	static ECsLoadFlags ViewTypeToLoadFlags(const ECsViewType& ViewType, const bool& IsLow = false);

#pragma endregion Enum to Enum Conversion

// String
#pragma region

	static ERichCurveInterpMode Stream_GetRichCurveInterpMode(const TCHAR*& Str);
	static ERichCurveTangentMode Stream_GetRichCurveTangentMode(const TCHAR*& Str);
	static ECsViewType Stream_GetViewType(const TCHAR*& Str);

#pragma endregion

// Data
#pragma region
	/*
	static class UCsDataMapping* GetDataMapping(UWorld* InWorld);

	template<typename T>
	static T* GetDataMapping(UWorld* InWorld)
	{
		return Cast<T>(GetDataMapping(InWorld));
	}
	*/
#pragma endregion 

	static FVector3f GetBoneLocation(USkeletalMeshComponent* InMesh, const int32 &BoneIndex, const TEnumAsByte<EBoneSpaces::Type> &Space = EBoneSpaces::WorldSpace);
	static FName GetParentBone(USkeletalMeshComponent* InMesh, const int32 &BoneIndex);

	static void CopyHitResult(const FHitResult& From, FHitResult& To);
	static void SetHitResult(FHitResult* InHitResult, FHitResult* OutHitResult);
	static void CopyCollisionObjectQueryParams(const FCollisionObjectQueryParams& From, FCollisionObjectQueryParams& To);

	static FORCEINLINE FString GetFloatAsStringWithPrecision(float TheFloat, const uint8 Precision)
	{
		const TCHAR* TheDot = TEXT(".");

		FString FloatString = FString::SanitizeFloat(TheFloat);

		//No . ?
		if (!FloatString.Contains(TheDot))
		{
			return FloatString;
		}

		//Split
		FString LeftS;
		FString RightS;

		FloatString.Split(TheDot, &LeftS, &RightS);

		if (Precision == 0)
			return LeftS;

		//Add dot back to LeftS
		LeftS += TheDot;

		//Get the Single Number after the precision amount
		// so in .1273, get the 7
		FString RightSFirstTruncated = "";
		if (RightS.Len() - 1 >= Precision)
		{
			RightSFirstTruncated = RightS.Mid(Precision, 1);
		}

		//Truncate the RightS
		// 	.1273 becomes .12 with precision 2
		RightS = RightS.Left(Precision);

		//Round Up if There was any truncated portion
		if (RightSFirstTruncated != "")
		{
			if (FCString::Atod(*RightSFirstTruncated) >= 5)
			{
				//.1273 becomes .13
				RightS = FString::FromInt(FCString::Atod(*RightS) + 1);
			}
		}

		return LeftS + RightS;
	}

	static bool IsMatchInProgress(UWorld *InWorld);

// Math
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static FRotator3f Rotator_GetAngleDelta(const FRotator3f&A, const FRotator3f&B);

	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static FRotator3f Rotator_GetAbsAngleDelta(const FRotator3f&A, const FRotator3f&B);

	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static float LerpAngle(const float &FromAngle, const float &ToAngle, const float &LerpRate, const float &DeltaSeconds, float MinAngle, float MaxAngle);

	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static FVector3f BuildUniformVector(const FVector3f&V, const int32 &Axes);
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static FRotator3f BuildUniformRotator(const FRotator3f&R, const int32 &Axes);

	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static int32 GetNumBitFlags(const int32 &BitMask, const int32 &MaxBits);

	static FString UInt64ToString(const uint64 &Value);

	static FVector3f ClampVectorComponents(FVector3f V, const float &Clamp);
	static FVector3d ClampVectorComponents(FVector3d V, const float& Clamp);

	static void ClampMinVectorComponents(FVector3f&V, const float &Min);
	static void ClampMinVectorComponents(FVector3d& V, const float& Min);

	static void ClampMaxVectorComponents(FVector3f&V, const float &Max);
	static void ClampMaxVectorComponents(FVector3d& V, const float& Max);

#pragma endregion Math

	/*
	static bool IsOnSameTeam(UWorld *InWorld, AShooterCharacter* InPawnA, AShooterCharacter* InPawnB);
	static bool IsOnSameTeam(UWorld *InWorld, AShooterPlayerState* InPlayerStateA, AShooterCharacter* InPawnB);
	static bool IsOnSameTeam(UWorld *InWorld, AShooterPlayerState* InPlayerStateA, AShooterPlayerState* InPlayerStateB);
	*/
	static FVector3f GetScaledPlayerViewDirection(AController* Controller, const FVector3f &Scale);

	// Gets world player view point where the HMD is located - not just where PlayerCamera is located
	// The HMD world position and PlayerCamera can be in different positions
	//static void GetHMDWorldViewPoint(APlayerController* PlayerController, FVector3f& out_Location, FRotator3f& out_Rotation);

	static void GetKeyValue(const FString& Pair, FString& Key, FString& Value, const TCHAR* PairDelimiter = TEXT("="));
	static bool GrabOption(FString& Options, FString& Result);
	static FString ParseOption(const FString& Options, const FString& InKey);

	static bool IsValidFpsAnimMontageArray(TArray<FCsFpvAnimMontage>& InArray, const ECsViewType& ViewType, const bool& IsLow=false);

// Component
#pragma region

	static void InitComponent(USceneComponent* Component, USceneComponent* RootComponent, const ECollisionChannel& Channel, const ECsViewType& ViewType=ECsViewType::ECsViewType_MAX);
	static void EnableComponent(USceneComponent* Component, const bool& SetUpdateFlag=false);
	static void DisableComponent(USceneComponent* Component, const bool& Detach=false, const bool& DisableCollision=false, const bool& SetUpdateFlag=false);
	static void ClearComponent(USceneComponent* Component);

	static bool CanDetachFromComponent(USceneComponent* Component);
	static bool CanDetachFromComponent(USceneComponent* Component, USceneComponent* Parent);
	static void SafeDetachFromComponent(USceneComponent* Component);
	static void SafeDetachFromComponent(USceneComponent* Component, USceneComponent* Parent);
	static bool CanAttachToComponent(USceneComponent* Component);

	static void ToggleEditorIcons(AActor* InActor, const bool &IsVisible);

#pragma endregion Component

// Animation
#pragma region

	static void ConvertBoneSpaceTransformToComponentSpace(const FTransform3d& ComponentTransform, USkinnedMeshComponent* Mesh, FTransform3d& OutTransform, const FName &BoneName, const EBoneControlSpace &Space);
	static void ConvertComponentSpaceTransformToBoneSpace(const FTransform3d& ComponentTransform, USkinnedMeshComponent* Mesh, FTransform3d& OutTransform, const FName &BoneName, const EBoneControlSpace &Space);

#pragma endregion Animation

// Emitter
#pragma region

	static void ActivateEmitter(AEmitter* InEmitter);
	static void DeActivateEmitter(AEmitter* InEmitter);
	/*
	static void StopAndClearEmitter(UWorld* InWorld, TWeakObjectPtr<AShooterEmitter> &InEmitter);
	static void SetAndAttachEmitter(AEmitter* InEmitter, USceneComponent* Parent, FEffectsElement* Effect);
	*/
#pragma endregion Emitter

// Coroutine
#pragma region

	static void EndRoutine(FCsRoutine* R);
	static void EndAndClearRoutine(FCsRoutine*& R);

	static const FCsRoutineHandle& ScaleActorOverTime(const FECsUpdateGroup& Group, const ECsEasingType& EasingType, AActor* InActor, const float& StartScale, const float& EndScale, const float& Time, const bool& IsRelativeScale=false);
	static const FCsRoutineHandle& ScaleActorOverTime(const FECsUpdateGroup& Group, const ECsEasingType& EasingType, AActor* InActor, const FVector3f& StartScale, const FVector3f& EndScale, const float& Time, const bool& IsRelativeScale=false);
	static const FCsRoutineHandle& ScaleActorOverTime(const FECsUpdateGroup& Group, UCurveBase* Curve, AActor* InActor, const float& StartScale, const float& EndScale, const float& Time, const bool& IsRelativeScale=false);
	static const FCsRoutineHandle& ScaleActorOverTime(const FECsUpdateGroup& Group, UCurveBase* Curve, AActor* InActor, const FVector3f& StartScale, const FVector3f& EndScale, const float& Time, const bool& IsRelativeScale=false);
	static char ScaleActorOverTime_Internal(FCsRoutine* R);

	static const FCsRoutineHandle& ScaleActorOverTime_AsCurve(const FECsUpdateGroup& Group, UCurveBase* Curve, AActor* InActor, const bool& IsRelativeScale = false);
	static char ScaleActorOverTime_AsCurve_Internal(FCsRoutine* R);

	static const FCsRoutineHandle& MoveActorOverTime(const FECsUpdateGroup& Group, const ECsEasingType& EasingType, AActor* InActor, const FVector3f& StartLocation, const FVector3f& EndLocation, const float& Time, const bool& IsRelativeLocation=false);
	static char MoveActorOverTime_Internal(FCsRoutine* R);
	/*
	static FCsRoutine* DeAllocateActor(const ECsCoroutineSchedule &CoroutineSchedule, AActor* InActor, const int32 &Index, const float &Delay);
	static char DeAllocateActor_Internal(struct FCsRoutine* r);
	*/
	static const FCsRoutineHandle& DestroyMaterialInstanceDynamic(const FECsUpdateGroup& Group, UMaterialInstanceDynamic* InMID, const float& Delay);
	static char DestroyMaterialInstanceDynamic_Internal(FCsRoutine* R);

	//static const FCsRoutineHandle& DestroyMaterialInstanceDynamics(const FECsUpdateGroup& Group, TArray<UMaterialInstanceDynamic*>& InMIDs, const float& Delay);

	static const FCsRoutineHandle& FadeCameraOverTime(const FECsUpdateGroup& Group, const ECsEasingType& EasingType, APlayerController* Controller, const float& Start, const float& End, const float& Time, const FLinearColor& Color);
	static char FadeCameraOverTime_Internal(FCsRoutine* R);

#pragma endregion Coroutine

	UFUNCTION(BlueprintCallable, Category = "Common")
	static bool IsDedicatedServer(AActor* InActor);

	static FString GetProxyAsString(AActor* InActor);

// Object / Actor
#pragma region

	template<typename T>
	static T* GetUObject(UWorld* InWorld)
	{
		for (TObjectIterator<T> Itr; Itr; ++Itr)
		{
			if (Itr &&
				!(*Itr)->IsPendingKill())
			{
				return (T*)*Itr;
			}
		}
		return nullptr;
	}

	template<typename T>
	static T* GetActor(UWorld* InWorld)
	{
		for (TActorIterator<T> Itr(InWorld); Itr; ++Itr)
		{
			if (Itr &&
				!(*Itr)->IsPendingKill())
			{
				return (T*)*Itr;
			}
		}
		return nullptr;
	}

	template<typename T>
	static T* GetActor(UWorld* InWorld, const FName &Tag)
	{
		for (TActorIterator<T> Itr(InWorld); Itr; ++Itr)
		{
			if (Itr &&
				Itr->Tags.Find(Tag) != INDEX_NONE)
			{
				return (T*)*Itr;
			}
		}
		return nullptr;
	}
	
	template<typename T>
	static void GetActors(UWorld* InWorld, TArray<T*> &OutActors)
	{
		for (TActorIterator<T> Itr(InWorld); Itr; ++Itr)
		{
			if (Itr &&
				!(*Itr)->IsPendingKill())
			{
				OutActors.Add((T*)*Itr);
			}
		}
	}

	template<typename T>
	static T* SpawnActor(UWorld* InWorld, USkeletalMeshComponent* Mesh, const FName& Tag)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.ObjectFlags				    |= RF_Transient;

		T* Actor = InWorld->SpawnActor<T>(Mesh->GetComponentLocation(), Mesh->GetComponentRotation(), SpawnInfo);
		((AActor*)Actor)->Tags.Add(Tag);
		return Actor;
	}

	static bool IsDefaultObject(UObject* InObject);

	//static const uint64& GetUniqueObjectId(AActor* Actor);

#pragma endregion Object / Actor

	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static bool IsDeveloperBuild();

// Physics
#pragma region

	static bool SetPhysicsPreset(FCsPhysicsPreset &Preset, UPrimitiveComponent* Component);
	static void SetPhysicsFromPreset(const FCsPhysicsPreset &Preset, UPrimitiveComponent* Component);

#pragma endregion Physics

// Collision
#pragma  region

	static bool SetCollisionPreset(FCsCollisionPreset &Preset, UPrimitiveComponent* Component);
	static void SetCollisionFromPreset(const FCsCollisionPreset &Preset, UPrimitiveComponent* Component, const bool &SetCollisionEnabled = true);
	static void SetCollisionFromTemplate(const FName &TemplateName, UPrimitiveComponent* Component, const bool &SetCollisionEnabled = true);

#pragma endregion Collision

// Level
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Common")
	static void TransitionToLevel(UWorld* InWorld, const FString &Level, const FString &GameMode);
	
	UFUNCTION(BlueprintCallable, Category = "Common")
	static void RequestEndPlayMap();

#pragma endregion Level

	static bool CanAsyncTask();
};