// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Anim.h"
#include "Types/CsTypes_Coroutine.h"
#include "Types/CsTypes_Interpolation.h"
#include "Player/CsPlayerController.h"

#include "CsCommon.generated.h"

UCLASS()
class CSCORE_API UCsCommon : public UBlueprintFunctionLibrary
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

	static class ACsMotionController* GetLocalHand(UWorld *InWorld, const TCsControllerHand &Hand);

	static class ACsManager_Inventory* GetLocalManager_Inventory(UWorld *InWorld);

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

	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static class ACsMotionController* GetMotionController(UWorld* InWorld, const TEnumAsByte<ECsControllerHand::Type> &Hand);

#pragma endregion

// Delegates
#pragma region

	template<typename T>
	static void Bind_OnCalcCamera_Event(UWorld* InWorld, T* Caller, void (T::*Callback)(const uint8&, const float&, const struct FMinimalViewInfo&))
	{
		ACsPlayerController* Controller = GetLocalPlayerController<ACsPlayerController>(InWorld);

		Controller->OnCalcCamera_Event.AddUObject(Caller, Callback);
	}

	template<typename T>
	static void Bind_OnCalcCamera_ScriptEvent(UWorld* InWorld, T* Caller, void (T::*Callback)(const uint8&, const float&, const struct FMinimalViewInfo&))
	{
		ACsPlayerController* Controller = GetLocalPlayerController<ACsPlayerController>(InWorld);

		Controller->OnCalcCamera_ScriptEvent.AddUObject(Caller, Callback);
	}

#pragma endregion Delegates

// Enum to String Conversion
#pragma region

	static FString LoadFlagsToString(const int32 &LoadFlags);

	static FString InteractivePhysicsStateToString(const int32 &PhysicsState);

#pragma endregion Enum to String Conversion

// Enum to Enum Conversion
#pragma region

	static int32 StringtoLoadFlags(const FString &LoadFlags);

	static ECsLoadFlags ViewTypeToLoadFlags(const TCsViewType &ViewType, const bool &IsLow = false);

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
	static TCsViewType Stream_GetViewType(const TCHAR*& Str);

#pragma endregion

// Data
#pragma region

	static class ACsDataMapping* GetDataMapping(UWorld* InWorld);

	template<typename T>
	static T* GetDataMapping(UWorld* InWorld)
	{
		return Cast<T>(GetDataMapping(InWorld));
	}

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

	UFUNCTION(BlueprintCallable, Category = "VR")
	static bool IsStereoscopic3D();

// Easing
#pragma region

	static float Ease(const TEnumAsByte<ECsEasingType::Type> &EasingType, const float &Time, const float &Start, const float &Final, const float &Duration);
	
	static float Linear(const float &Time, const float &Start, const float &Final, const float &Duration);
	static float BounceEaseOut(const float &Time, const float &Start, const float &Final, const float &Duration);
	static float BounceEaseIn(const float &Time, const float &Start, const float &Final, const float &Duration);
	static float BounceEaseInOut(const float &Time, const float &Start, const float &Final, const float &Duration);
	static float CubicEaseIn(const float &Time, const float &Start, const float &Final, const float &Duration);
	static float CubicEaseOut(const float &Time, const float &Start, const float &Final, const float &Duration);
	static float CubicEaseInOut(const float &Time, const float &Start, const float &Final, const float &Duration);
	static float ExpoEaseIn(const float &Time, const float &Start, const float &Final, const float &Duration);
	static float ExpoEaseOut(const float &Time, const float &Start, const float &Final, const float &Duration);
	static float ExpoEaseInOut(const float &Time, const float &Start, const float &Final, const float &Duration);

	static TCsEasingFunction GetEasingFunction(const TCsEasingType &EasingType);
	static TCsEasingFunction GetEasingFunction(const TEnumAsByte<ECsEasingType::Type> &EasingType);

#pragma endregion Easing

	static void GetKeyValue(const FString& Pair, FString& Key, FString& Value, const TCHAR* PairDelimiter = TEXT("="));
	static bool GrabOption(FString& Options, FString& Result);
	static FString ParseOption(const FString& Options, const FString& InKey);

	static void ShuffleTArray_FName(TArray<FName>& InArray);
	static void ShuffleTArray_int32(TArray<int32>& InArray);

	static bool IsValidFpsAnimMontageArray(TArray<FCsFpsAnimMontage> & InArray, const TCsViewType &ViewType, const bool &IsLow=false);

// Component
#pragma region

	static void InitComponent(USceneComponent* Component, USceneComponent* RootComponent, const ECollisionChannel &Channel, const TCsViewType &ViewType=ECsViewType::ECsViewType_MAX);
	static void EnableComponent(USceneComponent* Component, const bool &SetUpdateFlag=false);
	static void DisableComponent(USceneComponent* Component, const bool &Detach=false, const bool &DisableCollision=false, const bool &SetUpdateFlag=false);
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

	static void EndRoutine(struct FCsRoutine* r);
	static void EndAndClearRoutine(struct FCsRoutine* &r);

	static FCsRoutine* ScaleActorOverTime(const TCsCoroutineSchedule &ScheduleType, const TEnumAsByte<ECsEasingType::Type> &EasingType, AActor* InActor, const float &StartScale, const float &EndScale, const float &Time, const bool &IsRelativeScale=false);
	static FCsRoutine* ScaleActorOverTime(const TCsCoroutineSchedule &ScheduleType, const TEnumAsByte<ECsEasingType::Type> &EasingType, AActor* InActor, const FVector &StartScale, const FVector &EndScale, const float &Time, const bool &IsRelativeScale=false);
	static FCsRoutine* ScaleActorOverTime(const TCsCoroutineSchedule &ScheduleType, UCurveBase* Curve, AActor* InActor, const float &StartScale, const float &EndScale, const float &Time, const bool &IsRelativeScale=false);
	static FCsRoutine* ScaleActorOverTime(const TCsCoroutineSchedule &ScheduleType, UCurveBase* Curve, AActor* InActor, const FVector &StartScale, const FVector &EndScale, const float &Time, const bool &IsRelativeScale=false);
	static char ScaleActorOverTime_Internal(struct FCsRoutine* r);

	static FCsRoutine* ScaleActorOverTime_AsCurve(const TCsCoroutineSchedule &ScheduleType, UCurveBase* Curve, AActor* InActor, const bool &IsRelativeScale = false);
	static char ScaleActorOverTime_AsCurve_Internal(struct FCsRoutine* r);

	static FCsRoutine* MoveActorOverTime(const TCsCoroutineSchedule &ScheduleType, const TEnumAsByte<ECsEasingType::Type> &EasingType, AActor* InActor, const FVector &StartLocation, const FVector &EndLocation, const float &Time, const bool &IsRelativeLocation=false);
	static char MoveActorOverTime_Internal(struct FCsRoutine* r);
	/*
	static FCsRoutine* DeAllocateActor(const TCsCoroutineSchedule &CoroutineSchedule, AActor* InActor, const int32 &Index, const float &Delay);
	static char DeAllocateActor_Internal(struct FCsRoutine* r);
	*/
	static FCsRoutine* DestroyMaterialInstanceDynamic(const TCsCoroutineSchedule &ScheduleType, UMaterialInstanceDynamic* InMID, const float &Delay);
	static char DestroyMaterialInstanceDynamic_Internal(struct FCsRoutine* r);

	static FCsRoutine* DestroyMaterialInstanceDynamics(const TCsCoroutineSchedule &ScheduleType, TArray<UMaterialInstanceDynamic*>& InMIDs, const float &Delay);

	static FCsRoutine* FadeCameraOverTime(const TCsCoroutineSchedule &ScheduleType, const TEnumAsByte<ECsEasingType::Type> &EasingType, APlayerController* Controller, const float &Start, const float &End, const float &Time, const FLinearColor &Color);
	static char FadeCameraOverTime_Internal(struct FCsRoutine* r);
	/*
	static FCsRoutine* AllocateAndActivateEmitter(TCsCoroutineSchedule CoroutineSchedule, FCsFxElement* InEffectsElement, FVector Location, float Delay);
	static char AllocateAndActivateEmitter_Internal(struct FCsRoutine* r);
	*/
	static void CoroutineStopCondition_CheckActor(struct FCsRoutine* r);
	static void CoroutineStopCondition_CheckObject(struct FCsRoutine* r);
	//static void CoroutineStopCondition_CheckCharacter(struct FCsRoutine* r);

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
	static void CopyTArrays(TArray<TAssetPtr<T>>& To, TArray<TAssetPtr<T>>& From)
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
	static bool IsAnyElementInTArrayTAssetPtrNull(TArray<TAssetPtr<T>>& A)
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
	static bool IsAnyElementInTArrayTAssetPtrNull(TArray<TAssetPtr<T>>* &A)
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
	static bool IsAnyElementInTArrayTAssetSubclassOfNull(TArray<TAssetSubclassOf<T>>& A)
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
	static bool IsAnyElementInTArrayTAssetSubclassOfNull(TArray<TAssetSubclassOf<T>>* &A)
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
	static bool AreAllElementsInTArrayAssetPtrNotNull(TArray<TAssetPtr<T>>& A)
	{
		return !IsAnyElementInTArrayTAssetPtrNull<T>(A);
	}

	template<typename T>
	static bool AreAllElementsInTArrayAssetPtrNotNull(TArray<TAssetPtr<T>>* &A)
	{
		return !IsAnyElementInTArrayTAssetPtrNull<T>(A);
	}

	template<typename T>
	static bool AreAllElementsInTArrayAssetSubclassOfNotNull(TArray<TAssetSubclassOf<T>>& A)
	{
		return !IsAnyElementInTArrayTAssetSubclassOfNull<T>(A);
	}

	template<typename T>
	static bool AreAllElementsInTArrayAssetSubclassOfNotNull(TArray<TAssetSubclassOf<T>>* &A)
	{
		return !IsAnyElementInTArrayTAssetSubclassOfNull<T>(A);
	}

#pragma endregion TArray

// Fixed Array
#pragma region

	template<typename T>
	void CopyFixedArrays(T* To, T* From, const int32 &Size)
	{
	}

#pragma endregion Fixed Array

// Javascript
#pragma region

#if WITH_EDITOR

	static void SetupJavascript(UObject* InOwner, UWorld* InWorld, UObject* &JavascriptIsolate, UObject* &JavascriptContext, const FString &EditorJavascriptFile);
	static void SetupJavascript(UObject* InOwner, UWorld* InWorld, UObject* &JavascriptIsolate, UObject* &JavascriptContext);

	static void Javascript_ExposeObject(UObject* &JavascriptContext, const FString &Name, UObject* InObject);
	static void Javascript_RunFile(UObject* &JavascriptContext, const FString &EditorJavascriptFile);

#endif // #if WITH_EDITOR

#pragma endregion Javascript

	static FVector ClampVectorComponents(FVector V, float Clamp);
	static void ClampMinVectorComponents(FVector &V, const float &Min);
	static void ClampMaxVectorComponents(FVector &V, const float &Max);

	UFUNCTION(BlueprintCallable, Category = "Common")
	static bool IsDedicatedServer(AActor* InActor);

	static FString GetProxyAsString(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Common")
	static bool IsPlayInGame(UWorld* InWorld);
	UFUNCTION(BlueprintCallable, Category = "Common")
	static bool IsPlayInEditor(UWorld* InWorld);
	UFUNCTION(BlueprintCallable, Category = "Common")
	static bool IsPlayInPIE(UWorld* InWorld);
	UFUNCTION(BlueprintCallable, Category = "Common")
	static bool IsPlayInEditorPreview(UWorld* World);

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

// Time
#pragma region

	static uint64 GetWorldTimeMilliseconds(UWorld* InWorld);

	static float GetCurrentDateTimeSeconds();

	static uint64 GetCurrentFrame(UWorld* InWorld);

#pragma endregion Time

	static float BytesToKilobytes(const int32 &Bytes);
	static float BytesToMegabytes(const int32 &Bytes);
	static int32 KilobytesToBytes(const float &Kilobytes);

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

// Editor Message
#pragma region

#if WITH_EDITOR

	static void DisplayNotificationInfo(const FString &InTextLiteral, const FString &InNamespace, const FString &InKey, const float &Duration);

#endif // #if WITH_EDITOR
	
#pragma endregion Editor Message

	static bool CanAsyncTask();
};