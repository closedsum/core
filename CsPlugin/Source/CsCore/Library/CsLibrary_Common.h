// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Anim.h"
#include "Types/CsTypes_Collision.h"
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

	static FORCEINLINE float GetAngleBetweenVectors(const FVector& v1, const FVector& v2)
	{
		float dotValue = FVector::DotProduct(v1, v2);
		float radians = FMath::Acos(dotValue);
		return FMath::RadiansToDegrees(radians);
	}

	static float GetSquaredDistanceToLocalControllerEye(UWorld *InWorld, const FVector& otherLocation);
	*/

// Local Client
#pragma region

	template<typename T>
	static T* GetLocalPlayerController(UWorld* InWorld)
	{
		return Cast<T>(GEngine->GetFirstLocalPlayerController(InWorld));
	}

	static AController* GetLocalPlayerController(UWorld* InWorld);

	template<typename T>
	static T* GetLocalHUD(UWorld* InWorld)
	{
		APlayerController* Controller = GetLocalPlayerController<APlayerController>(InWorld);

		return Cast<T>(Controller->MyHUD);
	}

	static class UPlayerInput* GetLocalPlayerInput(UWorld* InWorld);

	template<typename T>
	static T* GetLocalPlayerState(UWorld* InWorld)
	{
		AController* Controller = GetLocalPlayerController(InWorld);

		return Controller ? Cast<T>(Controller->PlayerState) : nullptr;
	}

	static APlayerState* GetLocalPlayerState(UWorld* InWorld);
	
	static bool IsLocalPlayerState(UWorld* InWorld, APlayerState* InPlayerState);

	template<typename T>
	static T* GetLocalPawn(UWorld* InWorld)
	{
		APlayerController* Controller = GetLocalPlayerController<APlayerController>(InWorld);

		return Controller ? Cast<T>(Controller->GetPawn()) : nullptr;
	}

	UFUNCTION(BlueprintCallable, Category = "Pawn")
	static bool IsLocalPawn(UWorld* InWorld, APawn* InPawn);
	
	template<typename T>
	static void GetLocalPlayerViewPoint(UWorld* InWorld, FVector &OutLocation, FRotator &OutRotation)
	{
		T* PC = GetLocalPlayerController<T>(InWorld);

		if (APlayerController* Controller = Cast<APlayerController>(PC))
			Controller->GetPlayerViewPoint(OutLocation, OutRotation);
	}

	static void GetLocalPlayerViewPoint(UWorld* InWorld, FVector &OutLocation, FRotator &OutRotation);

	UFUNCTION(BlueprintCallable, Category = "Common")
	static float GetSquaredDistanceToLocalControllerEye(UWorld *InWorld, const FVector& Location);

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
	static void GetHMDOrientationAndPosition(FRotator& DeviceRotation, FVector& DevicePosition);

	UFUNCTION(BlueprintCallable, Category = "Common")
	static void GetHMDWorldViewPoint(UWorld* InWorld, FVector &OutLocation, FRotator& OutRotation);

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

	static FString Stream_GetString(const TCHAR*& Str, bool IsLowerCase);
	static FName Stream_GetName(const TCHAR*& Str);
	static bool Stream_GetBool(const TCHAR*& Str);
	static int32 Stream_GetBoolAsInt(const TCHAR*& Str);
	static int32 Stream_GetInt(const TCHAR*& Str);
	static float Stream_GetFloat(const TCHAR*& Str);
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

// Materials
#pragma region

	static void SetMaterials(UStaticMeshComponent* InMesh, const TArray<UMaterialInstanceConstant*>& Materials);
	static void SetMaterials(USkeletalMeshComponent* InMesh, const TArray<UMaterialInstanceConstant*>& Materials);

	static void ClearOverrideMaterials(UStaticMeshComponent* InMesh);
	static void ClearOverrideMaterials(USkeletalMeshComponent* InMesh);

	static void DestroyMIDs(TArray<UMaterialInstanceDynamic*>& MIDs);
	static void SetMIDs(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<FSkeletalMaterial>& Materials);
	static void SetMIDs(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInstanceConstant*>& Materials);
	static void SetMIDs(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials);

	static void MIDs_SetScalarParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float &Value);
	static void MIDs_SetVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector &Value);
	static void MIDs_SetVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor &Value);

#pragma endregion Materials

	static FVector GetBoneLocation(USkeletalMeshComponent* InMesh, const int32 &BoneIndex, const TEnumAsByte<EBoneSpaces::Type> &Space = EBoneSpaces::WorldSpace);
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
	static float GetAngleDelta(const float &Angle1, const float &Angle2);

	static FRotator GetAngleDelta(const FRotator &A, const FRotator &B);
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static FRotator Rotator_GetAngleDelta(const FRotator &A, const FRotator &B);

	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static float GetAbsAngleDelta(const float &Angle1, const float &Angle2);

	static FRotator GetAbsAngleDelta(const FRotator &A, const FRotator &B);
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static FRotator Rotator_GetAbsAngleDelta(const FRotator &A, const FRotator &B);

	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static float AngleClamp180(float Angle);

	static FRotator AngleClamp180(const FRotator &Rotation);
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static float AngleClamp360(float Angle);

	static FRotator AngleClamp360(const FRotator &Rotation);
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static float LerpAngle(const float &FromAngle, const float &ToAngle, const float &LerpRate, const float &DeltaSeconds, float MinAngle, float MaxAngle);
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static int32 Mod(const int32 &A, const int32 &B);

	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static FVector BuildUniformVector(const FVector &V, const int32 &Axes);
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static FRotator BuildUniformRotator(const FRotator &R, const int32 &Axes);

	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static int32 GetNumBitFlags(const int32 &BitMask, const int32 &MaxBits);

	static FString UInt64ToString(const uint64 &Value);

	static FVector ClampVectorComponents(FVector V, const float &Clamp);
	static void ClampMinVectorComponents(FVector &V, const float &Min);
	static void ClampMaxVectorComponents(FVector &V, const float &Max);

#pragma endregion Math

	/*
	static bool IsOnSameTeam(UWorld *InWorld, AShooterCharacter* InPawnA, AShooterCharacter* InPawnB);
	static bool IsOnSameTeam(UWorld *InWorld, AShooterPlayerState* InPlayerStateA, AShooterCharacter* InPawnB);
	static bool IsOnSameTeam(UWorld *InWorld, AShooterPlayerState* InPlayerStateA, AShooterPlayerState* InPlayerStateB);
	*/
	static FVector GetScaledPlayerViewDirection(AController* Controller, const FVector &Scale);

	// Gets world player view point where the HMD is located - not just where PlayerCamera is located
	// The HMD world position and PlayerCamera can be in different positions
	//static void GetHMDWorldViewPoint(APlayerController* PlayerController, FVector& out_Location, FRotator& out_Rotation);

// Easing
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static float Ease(const ECsEasingType &EasingType, const float &Time, const float &Start, const float &Final, const float &Duration);
	
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static float Linear(const float &Time, const float &Start, const float &Final, const float &Duration);
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static float BounceEaseOut(const float &Time, const float &Start, const float &Final, const float &Duration);
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static float BounceEaseIn(const float &Time, const float &Start, const float &Final, const float &Duration);
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static float BounceEaseInOut(const float &Time, const float &Start, const float &Final, const float &Duration);
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static float CubicEaseIn(const float &Time, const float &Start, const float &Final, const float &Duration);
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static float CubicEaseOut(const float &Time, const float &Start, const float &Final, const float &Duration);
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static float CubicEaseInOut(const float &Time, const float &Start, const float &Final, const float &Duration);
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static float ExpoEaseIn(const float &Time, const float &Start, const float &Final, const float &Duration);
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static float ExpoEaseOut(const float &Time, const float &Start, const float &Final, const float &Duration);
	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static float ExpoEaseInOut(const float &Time, const float &Start, const float &Final, const float &Duration);

	static TCsEasingFunction GetEasingFunction(const ECsEasingType &EasingType);

#pragma endregion Easing

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

	static void ConvertBoneSpaceTransformToComponentSpace(const FTransform& ComponentTransform, USkinnedMeshComponent* Mesh, FTransform& OutTransform, const FName &BoneName, const EBoneControlSpace &Space);
	static void ConvertComponentSpaceTransformToBoneSpace(const FTransform& ComponentTransform, USkinnedMeshComponent* Mesh, FTransform& OutTransform, const FName &BoneName, const EBoneControlSpace &Space);

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
	static const FCsRoutineHandle& ScaleActorOverTime(const FECsUpdateGroup& Group, const ECsEasingType& EasingType, AActor* InActor, const FVector& StartScale, const FVector& EndScale, const float& Time, const bool& IsRelativeScale=false);
	static const FCsRoutineHandle& ScaleActorOverTime(const FECsUpdateGroup& Group, UCurveBase* Curve, AActor* InActor, const float& StartScale, const float& EndScale, const float& Time, const bool& IsRelativeScale=false);
	static const FCsRoutineHandle& ScaleActorOverTime(const FECsUpdateGroup& Group, UCurveBase* Curve, AActor* InActor, const FVector& StartScale, const FVector& EndScale, const float& Time, const bool& IsRelativeScale=false);
	static char ScaleActorOverTime_Internal(FCsRoutine* R);

	static const FCsRoutineHandle& ScaleActorOverTime_AsCurve(const FECsUpdateGroup& Group, UCurveBase* Curve, AActor* InActor, const bool& IsRelativeScale = false);
	static char ScaleActorOverTime_AsCurve_Internal(FCsRoutine* R);

	static const FCsRoutineHandle& MoveActorOverTime(const FECsUpdateGroup& Group, const ECsEasingType& EasingType, AActor* InActor, const FVector& StartLocation, const FVector& EndLocation, const float& Time, const bool& IsRelativeLocation=false);
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
	/*
	static FCsRoutine* AllocateAndActivateEmitter(ECsCoroutineSchedule CoroutineSchedule, FCsFxElement_DEPRECATED* InEffectsElement, FVector Location, float Delay);
	static char AllocateAndActivateEmitter_Internal(struct FCsRoutine* r);
	*/

#pragma endregion Coroutine

// TArray
#pragma region

	template<typename T>
	static bool AreTArraysEqual(TArray<T>& A, TArray<T>& B)
	{
		if (A.Num() != B.Num())
			return false;

		const int32 Count = A.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (A[I] != B[I])
				return false;
		}
		return true;
	}

	template<typename T>
	static bool AreTArraysEqual(TArray<T*>& A, TArray<T*>& B)
	{
		if (A.Num() != B.Num())
			return false;

		const int32 Count = A.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (A[I] != B[I])
				return false;
		}
		return true;
	}

	template<typename T>
	static void CopyTArrays(TArray<T>& To, TArray<T>& From, T(*CreateAndCopy)(const T&)=nullptr)
	{
		To.Reset();
		
		const int32 Count = From.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			To.Add(CreateAndCopy ? (*CreateAndCopy)(From[I]) : From[I]);
		}
	}

	template<typename T>
	static void CopyTArrays(TArray<T*>& To, TArray<T*>& From)
	{
		To.Reset();

		const int32 Count = From.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			To.Add(From[I]);
		}
	}

	template<typename T>
	static void CopyTArrays(TArray<T*>& To, TArray<T*>* From)
	{
		To.Reset();

		const int32 Count = From->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			To.Add((*From)[I]);
		}
	}

	template<typename T>
	static void CopyTArrays(TArray<TSoftObjectPtr<T>>& To, TArray<TSoftObjectPtr<T>>& From)
	{
		To.Reset();

		const int32 Count = From.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			To.Add(From[I]);
		}
	}

	template<typename T>
	static void NullAndEmptyTArray(TArray<T*>& A)
	{
		const int32 Count = A.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			A[I] = nullptr;
		}
		A.Empty();
	}

	template<typename T>
	static void NullAndEmptyTArray(TArray<TWeakObjectPtr<T>>& A)
	{
		const int32 Count = A.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			A[I] = nullptr;
		}
		A.Empty();
	}

	template<typename T>
	static bool IsAnyElementInTArrayNull(TArray<T*>& A)
	{
		const int32 Count = A.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (!A[I])
				return true;
		}
		return false;
	}

	template<typename T>
	static bool IsAnyElementInTArrayNull(TArray<TWeakObjectPtr<T>>& A)
	{
		const int32 Count = A.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (!A[I].IsValid() || !A[I].Get())
				return true;
		}
		return false;
	}

	template<typename T>
	static bool AreAllElementsInTArrayNotNull(TArray<T*>& A)
	{
		return !IsAnyElementInTArrayNull<T>(A);
	}

	template<typename T>
	static bool AreAllElementsInTArrayNotNull(TArray<TWeakObjectPtr<T>>& A)
	{
		return !IsAnyElementInTArrayNull<T>(A);
	}

	template<typename T>
	static bool IsAnyElementInTArrayTSoftObjectPtrNull(TArray<TSoftObjectPtr<T>>& A)
	{
		const int32 Count = A.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (!A[I].IsValid() || !A[I].Get())
				return true;
		}
		return false;
	}

	template<typename T>
	static bool IsAnyElementInTArrayTSoftObjectPtrNull(TArray<TSoftObjectPtr<T>>* &A)
	{
		const int32 Count = A->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (!(*A)[I].IsValid() || !(*A)[I].Get())
				return true;
		}
		return false;
	}

	template<typename T>
	static bool IsAnyElementInTArrayTSoftClassPtrNull(TArray<TSoftClassPtr<T>>& A)
	{
		const int32 Count = A.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (!A[I].IsValid() || !A[I].Get())
				return true;
		}
		return false;
	}

	template<typename T>
	static bool IsAnyElementInTArrayTSoftClassPtrNull(TArray<TSoftClassPtr<T>>* &A)
	{
		const int32 Count = A->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (!(*A)[I].IsValid() || !(*A)[I].Get())
				return true;
		}
		return false;
	}

	template<typename T>
	static bool AreAllElementsInTArrayAssetPtrNotNull(TArray<TSoftObjectPtr<T>>& A)
	{
		return !IsAnyElementInTArrayTSoftObjectPtrNull<T>(A);
	}

	template<typename T>
	static bool AreAllElementsInTArrayAssetPtrNotNull(TArray<TSoftObjectPtr<T>>* &A)
	{
		return !IsAnyElementInTArrayTSoftObjectPtrNull<T>(A);
	}

	template<typename T>
	static bool AreAllElementsInTArrayAssetSubclassOfNotNull(TArray<TSoftClassPtr<T>>& A)
	{
		return !IsAnyElementInTArrayTSoftClassPtrNull<T>(A);
	}

	template<typename T>
	static bool AreAllElementsInTArrayAssetSubclassOfNotNull(TArray<TSoftClassPtr<T>>* &A)
	{
		return !IsAnyElementInTArrayTSoftClassPtrNull<T>(A);
	}

	template<typename T>
	static void ShuffleTArray(TArray<T>& InArray)
	{
		const int32 Len = InArray.Num();

		for (int32 Index = Len; Index > 1; --Index)
		{
			int32 J = FMath::RandRange(0, Index - 1);

			T Temp			   = InArray[J];
			InArray[J]		   = InArray[Index - 1];
			InArray[Index - 1] = Temp;
		}
	}

#pragma endregion TArray

// Fixed Array
#pragma region

	template<typename T>
	void CopyFixedArrays(T* To, T* From, const int32 &Size)
	{
	}

#pragma endregion Fixed Array

	UFUNCTION(BlueprintCallable, Category = "Common")
	static bool IsDedicatedServer(AActor* InActor);

	static FString GetProxyAsString(AActor* InActor);

// World
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Common")
	static bool IsPlayInGame(UWorld* InWorld);
	UFUNCTION(BlueprintCallable, Category = "Common")
	static bool IsPlayInEditor(UWorld* InWorld);
	UFUNCTION(BlueprintCallable, Category = "Common")
	static bool IsPlayInPIE(UWorld* InWorld);
	UFUNCTION(BlueprintCallable, Category = "Common")
	static bool IsPlayInEditorPreview(UWorld* World);
	UFUNCTION(BlueprintCallable, Category = "Common")
	static bool IsAnyWorldContextEditorOrEditorPreview();

#pragma endregion World

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

// Time
#pragma region

	static uint64 GetWorldTimeMilliseconds(UWorld* InWorld);

	static float GetCurrentDateTimeSeconds();

	static uint64 GetCurrentFrame(UWorld* InWorld);

#pragma endregion Time

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