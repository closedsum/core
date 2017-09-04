// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CsTypes.h"
#include "Player/CsPlayerController.h"

#if WITH_EDITOR
#include "AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"

#include "Classes/Factories/BlueprintFactory.h"
#endif WITH_EDITOR

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

	static bool IsLocalPawn(UWorld* InWorld, APawn* InPawn);
	
	template<typename T>
	static void GetLocalPlayerViewPoint(UWorld* InWorld, FVector &OutLocation, FRotator &OutRotation)
	{
		T* PC = GetLocalPlayerController<T>(InWorld);

		if (APlayerController* Controller = Cast<APlayerController>(PC))
			Controller->GetPlayerViewPoint(OutLocation, OutRotation);
	}

	static void GetLocalPlayerViewPoint(UWorld* InWorld, FVector &OutLocation, FRotator &OutRotation);

	static float GetSquaredDistanceToLocalControllerEye(UWorld *InWorld, const FVector& Location);

	static class ACsMotionController* GetLocalHand(UWorld *InWorld, const TCsControllerHand &Hand);

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

	static FString ViewTypeToString(const TCsViewType &ViewType);
	static FString ViewTypeToShooterAnimMemberName(const TCsViewType &ViewType, const bool &IsLow = false);
	static FString ViewTypeToShooterAnimBlueprintMemberName(const TCsViewType &ViewType, const bool &IsLow = false);
	static FString ViewTypeToShooterBlendSpaceMemberName(const TCsViewType &ViewType, const bool &IsLow = false);
	static TCsViewType StringToViewType(const FString &CommonName);

	static FString AdditiveAnimTypeToString(const EAdditiveAnimationType &AddType);
	
	static FString AdditiveBasePoseTypeToString(const EAdditiveBasePoseType &PoseType);

	static FString RichCurveInterpModeToString(const ERichCurveInterpMode &InterpMode);
	static ERichCurveInterpMode StringToRichCurveInterpMode(const FString& CommonName);

	static FString RichCurveTangentModeToString(const ERichCurveTangentMode &TangentMode);
	static ERichCurveTangentMode StringToRichCurveTangentMode(const FString& CommonName);

	static FString InputEventToString(const TCsInputEvent &Event);

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

#pragma endregion 

// Json
#pragma region

// Write
#pragma region

	static void JsonWriter(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, const FName &Member);
	static void JsonWriter(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, TArray<FName> &Member, const FString &ElementName);
	static void JsonWriter_ArrayElement(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, const FName &Member);

	template<typename T>
	static void WriteTAssetPtrToJson(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, TAssetPtr<T> &Member, const bool AsJsonObject=false)
	{
		if (AsJsonObject)
			InJsonWriter->WriteObjectStart();

		if (Member.IsValid() && Member.Get())
		{
			const FString AssetName	= Member.ToString();

			if (AssetName != TEXT(""))
			{
				InJsonWriter->WriteValue(MemberName, AssetName);
			}
			else
			{
				InJsonWriter->WriteValue(MemberName, TEXT(""));
			}
		}
		else
		{
			InJsonWriter->WriteValue(MemberName, TEXT(""));
		}

		if (AsJsonObject)
			InJsonWriter->WriteObjectEnd();
	}

	static void WriteTAssetPtrToJson_AnimBlueprint(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, TAssetPtr<UAnimBlueprint> &Member);
	static void WriteTAssetPtrToJson_Blueprint(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, TAssetPtr<UBlueprint> &Member);

	template<typename T>
	static void WriteTArrayTAssetPtrToJson(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, TArray<TAssetPtr<T>> &Member, const FString &ElementName)
	{
		InJsonWriter->WriteArrayStart(MemberName);
		
		const int32 Count = Member.Num();

		for (int32 I = 0; I < Count; I++)
		{
			WriteTAssetPtrToJson(InJsonWriter, ElementName, Member[I], true);
		}
		InJsonWriter->WriteArrayEnd();
	}

	template<typename T>
	static void WriteTAssetSubclassOfToJson(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, TAssetSubclassOf<T> AssetSubclassOf)
	{
		if (AssetSubclassOf.IsValid() && AssetSubclassOf.Get())
		{
			const FString AssetName = AssetSubclassOf.ToString();

			if (AssetName != TEXT(""))
			{
				InJsonWriter->WriteValue(MemberName, AssetName);
			}
			else
			{
				InJsonWriter->WriteValue(MemberName, TEXT(""));
			}
		}
		else
		{
			InJsonWriter->WriteValue(MemberName, TEXT(""));
		}
	}

	template<typename T>
	static void WriteAssetClassPropertyToJson(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UAssetClassProperty* &AssetClassProperty, void* InObject, const FString &MemberName)
	{
		if (TAssetSubclassOf<T>* Member = AssetClassProperty->ContainerPtrToValuePtr<TAssetSubclassOf<T>>(InObject))
			WriteTAssetSubclassOfToJson<T>(InJsonWriter, MemberName, *Member);
	}

	template<typename T>
	static void WriteAssetObjectPropertyToJson(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName, const bool &AsJsonObject = false)
	{
		if (TAssetPtr<T>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>>(InObject))
			WriteTAssetPtrToJson<T>(InJsonWriter, MemberName, *Member, AsJsonObject);
	}

	static void WriteAssetObjectPropertyToJson_AnimBlueprint(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName);
	static void WriteAssetObjectPropertyToJson_Blueprint(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName);

	template<typename T>
	static void WriteArrayAssetObjectPropertyToJson(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName, const FString &ElementName)
	{
		if (TArray<TAssetPtr<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<T>>>(InObject))
			WriteTArrayTAssetPtrToJson<T>(InJsonWriter, MemberName, *Member, ElementName);
	}

	template<typename T, typename E, int32 SIZE>
	static void WriteFixedArrayAssetObjectPropertyToJson_EnumSize(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName, FString(*ToString)(const E&))
	{
		if (TAssetPtr<T>(*Member)[SIZE] = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>[SIZE]>(InObject))
		{
			InJsonWriter->WriteArrayStart(MemberName);

			for (int32 I = 0; I < SIZE; I++)
			{
				const FString ElementName = (*ToString)((E)I);
				WriteTAssetPtrToJson<T>(InJsonWriter, ElementName, (*Member)[I], true);
			}
			InJsonWriter->WriteArrayEnd();
		}
	}

	template<typename T>
	static void WriteMemberStructPropertyToJson(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString &MemberName, const bool &UseMemberName = true, TCsWriteStructToJson_Internal Internal = nullptr)
	{
		T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject);

		if (UseMemberName)
		{
			InJsonWriter->WriteObjectStart(MemberName);
		}
		else
		{
			InJsonWriter->WriteObjectStart();
			InJsonWriter->WriteValue(TEXT("Index"), MemberName);
		}
		WriteStructToJson(InJsonWriter, (void*)Member, StructProperty->Struct, Internal);
		InJsonWriter->WriteObjectEnd();
	}

	template<typename T>
	static void WriteMemberArrayStructPropertyToJson(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName, TCsWriteStructToJson_Internal Internal = nullptr)
	{
		TArray<T>* Member					 = ArrayProperty->ContainerPtrToValuePtr<TArray<T>>(InObject);
		UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner);
		
		InJsonWriter->WriteArrayStart(MemberName);

		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; I++)
		{
			InJsonWriter->WriteObjectStart();
				InJsonWriter->WriteValue(TEXT("Index"), FString::FromInt(I));
				WriteStructToJson(InJsonWriter, (void*)&((*Member)[I]), InnerStructProperty->Struct, Internal);
			InJsonWriter->WriteObjectEnd();
		}
		InJsonWriter->WriteArrayEnd();
	}

	template<typename T, typename E, uint8 SIZE>
	static void WriteMemberFixedArrayStructPropertyToJson_EnumSize(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString &MemberName, FString(*ToString)(const E&), TCsWriteStructToJson_Internal Internal = nullptr)
	{
		T(*Member)[SIZE] = StructProperty->ContainerPtrToValuePtr<T[SIZE]>(InObject);

		InJsonWriter->WriteObjectStart(MemberName);

		for (int32 I = 0; I < SIZE; I++)
		{
			InJsonWriter->WriteObjectStart((*ToString)((E)I));
			WriteStructToJson(InJsonWriter, (void*)&((*Member)[I]), StructProperty->Struct, Internal);
			InJsonWriter->WriteObjectEnd();
		}
		InJsonWriter->WriteObjectEnd();
	}

	template<typename T>
	static void WriteMemberStructPropertyToJson_Primitive(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString &MemberName, FString(T::*ToString)() const)
	{
		if (T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject))
			InJsonWriter->WriteValue(MemberName, ((*Member).*ToString)());
	}

	template<typename T>
	static void WriteMemberArrayStructPropertyToJson_Primitive(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName, FString(T::*ToString)() const)
	{
		TArray<T>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<T>>(InObject);

		InJsonWriter->WriteArrayStart(MemberName);

		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; I++)
		{
			InJsonWriter->WriteObjectStart();
				InJsonWriter->WriteValue(MemberName, ((*Member)[I].*ToString)());
			InJsonWriter->WriteObjectEnd();
		}
		InJsonWriter->WriteArrayEnd();
	}

	static void WriteMemberStructPropertyToJson_Transform(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString &MemberName);
	static void WriteMemberArrayStructPropertyToJson_Transform(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName);

	template<typename T>
	static void WriteMemberBytePropertyToJson(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UByteProperty* &ByteProperty, void* InObject, const FString &MemberName, FString (*EnumToString)(const T&))
	{
		if (TEnumAsByte<T>* Member = ByteProperty->ContainerPtrToValuePtr<TEnumAsByte<T>>(InObject))
			InJsonWriter->WriteValue(MemberName, (*EnumToString)(*Member));
	}

	template<typename T>
	static void WriteMemberArrayBytePropertyToJson(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName, FString(*EnumToString)(const T&))
	{
		if (TArray<TEnumAsByte<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TEnumAsByte<T>>>(InObject))
		{
			InJsonWriter->WriteObjectStart(MemberName);

			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; I++)
			{
				InJsonWriter->WriteValue(FString::FromInt(I), (*EnumToString)((*Member)[I]));
			}
			InJsonWriter->WriteObjectEnd();
		}
	}

	template<typename T, typename E, int32 SIZE>
	static void WriteMemberFixedArrayBytePropertyToJson_EnumSize(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UByteProperty* &ByteProperty, void* InObject, const FString &MemberName, FString(*EnumToString)(const T&), FString(*EnumSizeToString)(const E&))
	{
		if (TEnumAsByte<T>(*Member)[SIZE] = ByteProperty->ContainerPtrToValuePtr<TEnumAsByte<T>[SIZE]>(InObject))
		{
			InJsonWriter->WriteObjectStart(MemberName);

			for (int32 I = 0; I < SIZE; I++)
			{
				InJsonWriter->WriteValue((*EnumSizeToString)((E)I), (*EnumToString)((T)((*Member)[I])));
			}
			InJsonWriter->WriteObjectEnd();
		}	
	}

	template<typename T, typename E, int32 SIZE>
	static void WriteMemberFixedArrayPropertyToJson_Primitive_EnumSize(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UProperty* &Property, void* InObject, const FString &MemberName, FString(T::*ToString)(void) const, FString(*EnumSizeToString)(const E&))
	{
		if (T(*Member)[SIZE] = Property->ContainerPtrToValuePtr<T[SIZE]>(InObject))
		{
			InJsonWriter->WriteObjectStart(MemberName);

			for (int32 I = 0; I < SIZE; I++)
			{
				InJsonWriter->WriteValue((*EnumSizeToString)((E)I), ((*Member)[I].*ToString)());
			}
			InJsonWriter->WriteObjectEnd();
		}
	}

	static void WriteStructToJson(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, void* InStruct, UScriptStruct* const &InScriptStruct, TCsWriteStructToJson_Internal Internal = nullptr);
	static void WriteObjectToJson(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, void* InObject, UClass* const &InClass, const TArray<FCsCategoryMemberAssociation> &CategoryMemberAssociations, TCsWriteObjectToJson_Internal Internal = nullptr);

#pragma endregion Write

// Read
#pragma region

	template<typename T>
	static void WriteToAssetClassPropertyFromJson(TSharedPtr<FJsonObject> &JsonObject, UAssetClassProperty* &AssetClassProperty, void* InObject, const FString &MemberName)
	{
		if (TAssetSubclassOf<T>* Member = AssetClassProperty->ContainerPtrToValuePtr<TAssetSubclassOf<T>>(InObject))
			*Member = TAssetSubclassOf<T>(JsonObject->GetStringField(MemberName));
	}

	template<typename T>
	static void WriteToAssetObjectPropertyFromJson(TSharedPtr<FJsonObject> &JsonObject, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName)
	{
		if (TAssetPtr<T>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>>(InObject))
			*Member = TAssetPtr<T>(JsonObject->GetStringField(MemberName));
	}

	static void WriteToAssetObjectPropertyFromJson_AnimBlueprint(TSharedPtr<FJsonObject> &JsonObject, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName);
	static void WriteToAssetObjectPropertyFromJson_Blueprint(TSharedPtr<FJsonObject> &JsonObject, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName);

	template<typename T>
	static void WriteToArrayAssetObjectPropertyFromJson(TSharedPtr<FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName, const FString &ElementName)
	{
		if (TArray<TAssetPtr<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<T>>>(InObject))
		{
			const TArray<TSharedPtr<FJsonValue>> JsonArray = JsonObject->GetArrayField(MemberName);

			const int32 ArrayCount  = JsonArray.Num();
			const int32 MemberCount	= Member->Num();
			const int32 Count		= FMath::Max(ArrayCount, MemberCount);

			for (int32 I = 0; I < Count; I++)
			{
				if (I >= ArrayCount)
					break;

				if (I >= MemberCount)
					Member->AddDefaulted();

				TSharedPtr<FJsonObject> Object = JsonArray[I]->AsObject();
				
				(*Member)[I] = TAssetPtr<T>(Object->GetStringField(ElementName));
			}
		}
	}

	template<typename T, typename E, int32 SIZE>
	static void WriteToFixedArrayAssetObjectPropertyFromJson_EnumSize(TSharedPtr<FJsonObject> &JsonObject, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName, FString(*ToString)(const E&))
	{
		if (TAssetPtr<T>(*Member)[SIZE] = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>[SIZE]>(InObject))
		{
			const TArray<TSharedPtr<FJsonValue>> JsonArray = JsonObject->GetArrayField(MemberName);

			const int32 ArrayCount = JsonArray.Num();
			const int32 Count	   = FMath::Min(ArrayCount, SIZE);

			for (int32 I = 0; I < Count; I++)
			{
				TSharedPtr<FJsonObject> Object = JsonArray[I]->AsObject();
				const FString ElementName	   = (*ToString)((E)I);
				(*Member)[I]				   = TAssetPtr<T>(Object->GetStringField(ElementName));
			}
		}
	}

	template<typename T>
	static void WriteToMemberStructPropertyFromJson_Primitive(TSharedPtr<FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString &MemberName, bool(T::*InitFromString)(const FString&))
	{
		if (T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject))
			((*Member).*InitFromString)(JsonObject->GetStringField(MemberName));
	}

	template<typename T>
	static void WriteToMemberArrayStructPropertyFromJson_Primitive(TSharedPtr<FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName, bool(T::*InitFromString)(const FString&))
	{
		TArray<T>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<T>>(InObject);

		const TArray<TSharedPtr<FJsonValue>> JsonArray = JsonObject->GetArrayField(MemberName);

		const int32 ArrayCount  = JsonArray.Num();
		const int32 MemberCount = Member->Num();
		const int32 Count		= FMath::Max(ArrayCount, MemberCount);

		for (int32 I = 0; I < Count; I++)
		{
			if (I >= ArrayCount)
				break;

			if (I >= MemberCount)
				Member->AddDefaulted();

			TSharedPtr<FJsonObject> Object = JsonArray[I]->AsObject();

			((*Member)[I].*InitFromString)(Object->GetStringField(MemberName));
		}
	}

	static void WriteToMemberStructPropertyFromJson_Transform(TSharedPtr<FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString &MemberName);
	static void WriteToMemberArrayStructPropertyFromJson_Transform(TSharedPtr<FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName);

	static void WriteToMemberArrayStructPropertyFromJson_Name(TSharedPtr<FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName);

	template<typename T>
	static void WriteToMemberStructPropertyFromJson(TSharedPtr<FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString &MemberName, TCsReadStructFromJson_Internal Internal = nullptr)
	{
		T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject);

		TSharedPtr<FJsonObject> Object = JsonObject->GetObjectField(MemberName);

		ReadStructFromJson(Object, (void*)Member, StructProperty->Struct, Internal);
	}

	template<typename T>
	static void WriteToMemberArrayStructPropertyFromJson(TSharedPtr<FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName, TCsReadStructFromJson_Internal Internal = nullptr)
	{
		TArray<T>* Member					 = ArrayProperty->ContainerPtrToValuePtr<TArray<T>>(InObject);
		UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner);

		const TArray<TSharedPtr<FJsonValue>> JsonArray = JsonObject->GetArrayField(MemberName);

		const int32 ArrayCount	= JsonArray.Num();
		const int32 MemberCount = Member->Num();
		const int32 Count		= FMath::Max(ArrayCount, MemberCount);

		for (int32 I = 0; I < Count; I++)
		{
			if (I >= ArrayCount)
				break;

			if (I >= MemberCount)
				Member->AddDefaulted();

			TSharedPtr<FJsonObject> Object = JsonArray[I]->AsObject();

			ReadStructFromJson(Object, (void*)&((*Member)[I]), InnerStructProperty->Struct, Internal);
		}
	}

	template<typename T, typename E, uint8 SIZE>
	static void WriteToMemberFixedArrayStructPropertyFromJson_EnumSize(TSharedPtr<FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString &MemberName, FString(*ToString)(const E&), TCsReadStructFromJson_Internal Internal = nullptr)
	{
		T(*Member)[SIZE] = StructProperty->ContainerPtrToValuePtr<T[SIZE]>(InObject);

		const TSharedPtr<FJsonObject> JObject = JsonObject->GetObjectField(MemberName);

		for (int32 I = 0; I < SIZE; I++)
		{
			TSharedPtr<FJsonObject> Object = JObject->GetObjectField((*ToString)((E)I));
			
			if (Object->Values.Num() > CS_EMPTY)
				ReadStructFromJson(Object, (void*)&((*Member)[I]), StructProperty->Struct, Internal);
		}
	}

	template<typename T>
	static void WriteToMemberBytePropertyFromJson(TSharedPtr<FJsonObject> &JsonObject, UByteProperty* &ByteProperty, void* InObject, const FString &MemberName, T(*ToType)(const FString&))
	{
		if (TEnumAsByte<T>* Member = ByteProperty->ContainerPtrToValuePtr<TEnumAsByte<T>>(InObject))
			*Member = (*ToType)(*JsonObject->GetStringField(MemberName));
	}

	template<typename T>
	static void WriteToMemberArrayBytePropertyFromJson(TSharedPtr<FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName, T(*ToType)(const FString&))
	{
		if (TArray<TEnumAsByte<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TEnumAsByte<T>>>(InObject))
		{
			const TSharedPtr<FJsonObject> JObject = JsonObject->GetObjectField(MemberName);

			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; I++)
			{
				const FString Value = JObject->GetStringField(FString::FromInt(I));
				(*Member)[I]		= (*ToType)(Value);
			}
		}
	}

	template<typename T, typename E, int32 SIZE>
	static void WriteToMemberFixedArrayBytePropertyFromJson_EnumSize(TSharedPtr<FJsonObject> &JsonObject, UByteProperty* &ByteProperty, void* InObject, const FString &MemberName, T(*ToType)(const FString&), FString(*ToString)(const E&))
	{
		if (TEnumAsByte<T>(*Member)[SIZE] = ByteProperty->ContainerPtrToValuePtr<TEnumAsByte<T>[SIZE]>(InObject))
		{
			const TSharedPtr<FJsonObject> JObject = JsonObject->GetObjectField(MemberName);

			for (int32 I = 0; I < SIZE; I++)
			{
				const FString Value = JObject->GetStringField((*ToString)((E)I));
				(*Member)[I]		= (*ToType)(Value);
			}
		}
	}

	template<typename E, int32 SIZE>
	static void WriteToMemberFixedArrayNamePropertyFromJson_EnumSize(TSharedPtr<FJsonObject> &JsonObject, UNameProperty* &NameProperty, void* InObject, const FString &MemberName, FString(*ToString)(const E&))
	{
		if (FName(*Member)[SIZE] = NameProperty->ContainerPtrToValuePtr<FName[SIZE]>(InObject))
		{
			const TSharedPtr<FJsonObject> JObject = JsonObject->GetObjectField(MemberName);

			for (int32 I = 0; I < SIZE; I++)
			{
				const FString Value = JObject->GetStringField((*ToString)((E)I));
				(*Member)[I]		= FName(*Value);
			}
		}
	}

	static void ReadStructFromJson(TSharedPtr<FJsonObject> &JsonObject, void* InStruct, UScriptStruct* const &InScriptStruct, TCsReadStructFromJson_Internal Internal = nullptr);
	static void ReadObjectFromJson(TSharedPtr<FJsonObject> &JsonParsed, void* InObject, UClass* const &InClass, const TArray<FCsCategoryMemberAssociation> &CategoryMemberAssociations, TCsReadObjectFromJson_Internal Internal = nullptr);

#pragma endregion Read

#pragma endregion Json

// Materials
#pragma region

	static void SetMaterials(UStaticMeshComponent* InMesh, TArray<UMaterialInstanceConstant*>& Materials);
	static void SetMaterials(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceConstant*>& Materials);

	static void SetSkeletalMeshAndMaterials(USkeletalMeshComponent* InMesh, USkeletalMesh* MeshTemplate);
	static void SetSkeletalMeshAndMaterials(USkeletalMeshComponent* InMesh, USkeletalMesh* MeshTemplate, TArray<UMaterialInstanceConstant*> & Materials);

	static void ClearOverrideMaterials(UStaticMeshComponent* InMesh);
	static void ClearOverrideMaterials(USkeletalMeshComponent* InMesh);

	static void DestroyMIDs(TArray<UMaterialInstanceDynamic*>& MIDs);
	static void SetMIDs(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceDynamic*>& MIDs, TArray<FSkeletalMaterial>& Materials);
	static void SetMIDs(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceDynamic*>& MIDs, TArray<UMaterialInstanceConstant*>& Materials);
	static void SetMIDs(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceDynamic*>& MIDs, TArray<UMaterialInterface*>& Materials);

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
	static float BounceEaseOut(float Time, const float &Start, const float &Final, const float &Duration);
	static float BounceEaseIn(const float &Time, const float &Start, const float &Final, const float &Duration);
	static float BounceEaseInOut(const float &Time, const float &Start, const float &Final, const float &Duration);
	static float CubicEaseIn(float Time, const float &Start, const float &Final, const float &Duration);
	static float CubicEaseOut(float Time, const float &Start, const float &Final, const float &Duration);
	static float CubicEaseInOut(float Time, const float &Start, const float &Final, const float &Duration);
	static float ExpoEaseIn(const float &Time, const float &Start, const float &Final, const float &Duration);
	static float ExpoEaseOut(const float &Time, const float &Start, const float &Final, const float &Duration);
	static float ExpoEaseInOut(float Time, const float &Start, const float &Final, const float &Duration);

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

	static FCsRoutine* ScaleActorOverTime(const TCsCoroutineSchedule &CoroutineSchedule, const TEnumAsByte<ECsEasingType::Type> &EasingType, AActor* InActor, const float &StartScale, const float &EndScale, const float &Time, const bool &IsRelativeScale=false);
	static FCsRoutine* ScaleActorOverTime(const TCsCoroutineSchedule &CoroutineSchedule, const TEnumAsByte<ECsEasingType::Type> &EasingType, AActor* InActor, const FVector &StartScale, const FVector &EndScale, const float &Time, const bool &IsRelativeScale=false);
	static FCsRoutine* ScaleActorOverTime(const TCsCoroutineSchedule &CoroutineSchedule, UCurveBase* Curve, AActor* InActor, const float &StartScale, const float &EndScale, const float &Time, const bool &IsRelativeScale=false);
	static FCsRoutine* ScaleActorOverTime(const TCsCoroutineSchedule &CoroutineSchedule, UCurveBase* Curve, AActor* InActor, const FVector &StartScale, const FVector &EndScale, const float &Time, const bool &IsRelativeScale=false);
	static char ScaleActorOverTime_Internal(struct FCsRoutine* r);

	static FCsRoutine* ScaleActorOverTime_AsCurve(const TCsCoroutineSchedule &CoroutineSchedule, UCurveBase* Curve, AActor* InActor, const bool &IsRelativeScale = false);
	static char ScaleActorOverTime_AsCurve_Internal(struct FCsRoutine* r);

	static FCsRoutine* MoveActorOverTime(const TCsCoroutineSchedule &CoroutineSchedule, const TEnumAsByte<ECsEasingType::Type> &EasingType, AActor* InActor, const FVector &StartLocation, const FVector &EndLocation, const float &Time, const bool &IsRelativeLocation=false);
	static char MoveActorOverTime_Internal(struct FCsRoutine* r);
	/*
	static FCsRoutine* DeAllocateActor(const TCsCoroutineSchedule &CoroutineSchedule, AActor* InActor, const int32 &Index, const float &Delay);
	static char DeAllocateActor_Internal(struct FCsRoutine* r);
	*/
	static FCsRoutine* DestroyMaterialInstanceDynamic(const TCsCoroutineSchedule &CoroutineSchedule, UMaterialInstanceDynamic* InMID, const float &Delay);
	static char DestroyMaterialInstanceDynamic_Internal(struct FCsRoutine* r);

	static FCsRoutine* DestroyMaterialInstanceDynamics(const TCsCoroutineSchedule &CoroutineSchedule, TArray<UMaterialInstanceDynamic*>& InMIDs, const float &Delay);

	static FCsRoutine* FadeCameraOverTime(const TCsCoroutineSchedule &CoroutineSchedule, const TEnumAsByte<ECsEasingType::Type> &EasingType, APlayerController* Controller, const float &Start, const float &End, const float &Time, const FLinearColor &Color);
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

		for (int32 I = 0; I < Count; I++)
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

		for (int32 I = 0; I < Count; I++)
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

		for (int32 I = 0; I < Count; I++)
		{
			To.Add(CreateAndCopy ? (*CreateAndCopy)(From[I]) : From[I]);
		}
	}

	template<typename T>
	static void CopyTArrays(TArray<T*>& To, TArray<T*>& From)
	{
		To.Reset();

		const int32 Count = From.Num();

		for (int32 I = 0; I < Count; I++)
		{
			To.Add(From[I]);
		}
	}

	template<typename T>
	static void CopyTArrays(TArray<T*>& To, TArray<T*>* From)
	{
		To.Reset();

		const int32 Count = From->Num();

		for (int32 I = 0; I < Count; I++)
		{
			To.Add((*From)[I]);
		}
	}

	template<typename T>
	static void CopyTArrays(TArray<TAssetPtr<T>>& To, TArray<TAssetPtr<T>>& From)
	{
		To.Reset();

		const int32 Count = From.Num();

		for (int32 I = 0; I < Count; I++)
		{
			To.Add(From[I]);
		}
	}

	template<typename T>
	static void NullAndEmptyTArray(TArray<T*>& A)
	{
		const int32 Count = A.Num();

		for (int32 I = 0; I < Count; I++)
		{
			A[I] = nullptr;
		}
		A.Empty();
	}

	template<typename T>
	static void NullAndEmptyTArray(TArray<TWeakObjectPtr<T>>& A)
	{
		const int32 Count = A.Num();

		for (int32 I = 0; I < Count; I++)
		{
			A[I] = nullptr;
		}
		A.Empty();
	}

	template<typename T>
	static bool IsAnyElementInTArrayNull(TArray<T*>& A)
	{
		const int32 Count = A.Num();

		for (int32 I = 0; I < Count; I++)
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

		for (int32 I = 0; I < Count; I++)
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

		for (int32 I = 0; I < Count; I++)
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

		for (int32 I = 0; I < Count; I++)
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

		for (int32 I = 0; I < Count; I++)
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

		for (int32 I = 0; I < Count; I++)
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

// Loading
#pragma region

	// Asset References
#pragma region

	template<typename T>
	static FString GetAssetDescription(TAssetSubclassOf<T> &AssetSubclassOf)
	{
		const FStringAssetReference& AssetRef = AssetSubclassOf.ToStringReference();
		const FString AssetName				  = AssetRef.ToString();
		FString AssetDescription			  = TEXT("");

		if (AssetName != TEXT(""))
		{
			AssetDescription = TEXT("Blueprint'") + AssetName + TEXT("'");
		}
		return AssetDescription;
	}

		// CsStringAssetReference
#pragma region

	template<typename T>
	static void GetAssetReferenceFromAssetObjectProperty(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences)
	{
		if (TAssetPtr<T>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>>(InObject))
		{
			const FStringAssetReference AssetRef = Member->ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			if (AssetName == TEXT(""))
				return;

			const FString MemberName	 = AssetObjectProperty->GetName();
			const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

			if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
			{
				if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
				{
					if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
					{
						OutAssetReferences.AddDefaulted();

						const int32 Size = OutAssetReferences.Num();

						FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
						Reference.Reference				   = AssetName;
						Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
						if (CalculateResourceSizes)
						{
							UObject* Asset = Cast<UObject>(Member->LoadSynchronous());

							Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(ResourceSizeMode);
							Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
							Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
						}
#endif // #if WITH_EDITOR
					}
				}
			}
		}
	}

	template<typename T>
	static void GetAssetReferenceFromAssetObjectProperty(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences)
	{
		if (TAssetPtr<T>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>>(InObject))
		{
			const FStringAssetReference AssetRef = Member->ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			if (AssetName == TEXT(""))
				return;

			const FString MemberName = AssetObjectProperty->GetName();
			const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

			if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
			{
				if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
				{
					if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
					{
						OutAssetReferences.AddDefaulted();

						const int32 Size = OutAssetReferences.Num();

						FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
						Reference.Reference				   = AssetName;
						Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
						if (CalculateResourceSizes)
						{
							UObject* Asset = Cast<UObject>(Member->LoadSynchronous());

							Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(ResourceSizeMode);
							Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
							Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
						}
#endif // #if WITH_EDITOR
					}
				}
			}
		}
	}

	static void GetAssetReferenceFromAssetObjectProperty_AnimMontage(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences);
	static void GetAssetReferenceFromAssetObjectProperty_AnimMontage(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences);

	static void GetAssetReferenceFromAssetObjectProperty_AnimSequence(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences);
	static void GetAssetReferenceFromAssetObjectProperty_AnimSequence(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences);

	static void GetAssetReferenceFromAssetObjectProperty_AnimBlueprint(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences);
	static void GetAssetReferenceFromAssetObjectProperty_AnimBlueprint(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences);

	static void GetAssetReferenceFromAssetObjectProperty_MaterialInstanceConstant(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences);
	static void GetAssetReferenceFromAssetObjectProperty_MaterialInstanceConstant(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences);

	static void GetAssetReferenceFromAssetObjectProperty_Blueprint(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences);
	static void GetAssetReferenceFromAssetObjectProperty_Blueprint(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences);

	template<typename T>
	static void GetAssetReferenceFromArrayAssetObjectProperty(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences)
	{
		if (TArray<TAssetPtr<T>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<T>>>(InObject))
		{
			const FString MemberName	 = ArrayAssetObjectProperty->GetName();
			const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

			// Array
			if (UArrayProperty* ArrayProperty = FindField<UArrayProperty>(InClass, *FlagMemberName))
			{
				if (UIntProperty* IntProperty = Cast<UIntProperty>(ArrayProperty->Inner))
				{
					if (TArray<int32>* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<TArray<int32>>(InObject))
					{
						const int32 Count	  = Member->Num();
						const int32 FlagCount = MemberLoadFlags->Num();

						if (Count != FlagCount)
							return;

						for (int32 I = 0; I < Count; I++)
						{
							const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
							const FString AssetName				 = AssetRef.ToString();

							if (AssetName == TEXT(""))
								continue;

							if (CS_TEST_BLUEPRINT_BITFLAG((*MemberLoadFlags)[I], LoadFlags))
							{
								OutAssetReferences.AddDefaulted();

								const int32 Size = OutAssetReferences.Num();

								FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
								Reference.Reference				   = AssetName;
								Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
								if (CalculateResourceSizes)
								{
									UObject* Asset = Cast<UObject>((*Member)[I].LoadSynchronous());

									Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(ResourceSizeMode);
									Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
									Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
								}
#endif // #if WITH_EDITOR
							}
						}
					}
				}
				return;
			}
			// Singleton
			if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
			{
				if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
				{
					if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
					{
						const int32 Count = Member->Num();

						for (int32 I = 0; I < Count; I++)
						{
							const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
							const FString AssetName				 = AssetRef.ToString();

							if (AssetName == TEXT(""))
								continue;

							OutAssetReferences.AddDefaulted();

							const int32 Size = OutAssetReferences.Num();

							FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
							Reference.Reference				   = AssetName;
							Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
							UObject* Asset = Cast<UObject>((*Member)[I].LoadSynchronous());

							Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(ResourceSizeMode);
							Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
							Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
#endif // #if WITH_EDITOR
						}
					}
				}
			}
		}
	}

	template<typename T>
	static void GetAssetReferenceFromArrayAssetObjectProperty(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences)
	{
		if (TArray<TAssetPtr<T>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<T>>>(InObject))
		{
			const FString MemberName	 = ArrayAssetObjectProperty->GetName();
			const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

			// Array
			if (UArrayProperty* ArrayProperty = FindField<UArrayProperty>(InClass, *FlagMemberName))
			{
				if (UIntProperty* IntProperty = Cast<UIntProperty>(ArrayProperty->Inner))
				{
					if (TArray<int32>* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<TArray<int32>>(InObject))
					{
						const int32 Count	  = Member->Num();
						const int32 FlagCount = MemberLoadFlags->Num();

						if (Count != FlagCount)
							return;

						for (int32 I = 0; I < Count; I++)
						{
							const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
							const FString AssetName				 = AssetRef.ToString();

							if (AssetName == TEXT(""))
								continue;

							if (CS_TEST_BLUEPRINT_BITFLAG((*MemberLoadFlags)[I], LoadFlags))
							{
								OutAssetReferences.AddDefaulted();

								const int32 Size = OutAssetReferences.Num();

								FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
								Reference.Reference				   = AssetName;
								Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
								if (CalculateResourceSizes)
								{
									UObject* Asset = Cast<UObject>((*Member)[I].LoadSynchronous());

									Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(ResourceSizeMode);
									Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
									Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
								}
#endif // #if WITH_EDITOR
							}
						}
					}
				}
				return;
			}
			// Singleton
			if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
			{
				if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
				{
					if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
					{
						const int32 Count = Member->Num();

						for (int32 I = 0; I < Count; I++)
						{
							const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
							const FString AssetName				 = AssetRef.ToString();

							if (AssetName == TEXT(""))
								continue;

							OutAssetReferences.AddDefaulted();

							const int32 Size = OutAssetReferences.Num();

							FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
							Reference.Reference				   = AssetName;
							Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
							UObject* Asset = Cast<UObject>((*Member)[I].LoadSynchronous());

							Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(ResourceSizeMode);
							Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
							Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
#endif // #if WITH_EDITOR
						}
					}
				}
			}
		}
	}

	template<typename T, int32 SIZE>
	static void GetAssetReferenceFromFixedArrayAssetObjectProperty_EnumSize(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences)
	{
		if (TAssetPtr<T>(*Member)[SIZE] = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>[SIZE]>(InObject))
		{
			const FString MemberName	 = ArrayAssetObjectProperty->GetName();
			const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

			// Singleton
			if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
			{
				if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
				{
					if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
					{
						for (int32 I = 0; I < SIZE; I++)
						{
							const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
							const FString AssetName				 = AssetRef.ToString();

							if (AssetName == TEXT(""))
								continue;

							OutAssetReferences.AddDefaulted();

							const int32 Size = OutAssetReferences.Num();

							FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
							Reference.Reference				   = AssetName;
							Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
							if (CalculateResourceSizes)
							{
								UObject* Asset = Cast<UObject>((*Member)[I].LoadSynchronous());

								Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(ResourceSizeMode);
								Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
								Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
							}
#endif // #if WITH_EDITOR
						}
					}
				}
			}
		}
	}

	static void GetAssetReferenceFromArrayAssetObjectProperty_AnimMontage(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences);
	static void GetAssetReferenceFromArrayAssetObjectProperty_AnimMontage(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences);

	static void GetAssetReferenceFromArrayAssetObjectProperty_AnimSequence(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences);
	static void GetAssetReferenceFromArrayAssetObjectProperty_AnimSequence(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences);

	static void GetAssetReferenceFromArrayAssetObjectProperty_MaterialInstanceConstant(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences);
	static void GetAssetReferenceFromArrayAssetObjectProperty_MaterialInstanceConstant(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences);

	template<int32 SIZE>
	static void GetAssetReferenceFromFixedArrayAssetObjectProperty_EnumSize_MaterialInstanceConstant(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
	{
		if (TAssetPtr<UMaterialInstanceConstant>(*Member)[SIZE] = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UMaterialInstanceConstant>[SIZE]>(InObject))
		{
			const FString MemberName	 = AssetObjectProperty->GetName();
			const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

			int32* MemberLoadFlags = nullptr;

			if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
				MemberLoadFlags	= IntProperty->ContainerPtrToValuePtr<int32>(InObject);

			if (!MemberLoadFlags)
				return;

			if (!CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
				return;

			for (int32 I = 0; I < SIZE; I++)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
				const FString AssetName				 = AssetRef.ToString();

				if (AssetName == TEXT(""))
					continue;

				OutAssetReferences.AddDefaulted();

				const int32 Size = OutAssetReferences.Num();

				FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
				Reference.Reference				   = AssetName;
				Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
				if (CalculateResourceSizes)
				{
					UMaterialInstanceConstant* Asset = Cast<UMaterialInstanceConstant>((*Member)[I].LoadSynchronous());

					const int32 TextureCount = Asset->TextureParameterValues.Num();

					for (int32 J = 0; J < TextureCount; J++)
					{
						UTexture* Texture = Asset->TextureParameterValues[J].ParameterValue;

						if (!Texture)
							continue;

						Reference.Size.Bytes += Texture->GetResourceSizeBytes(EResourceSizeMode::Inclusive);
					}

					Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
					Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
				}
#endif // #if WITH_EDITOR
			}
		}
	}

	static void GetAssetReferenceFromArrayAssetObjectProperty_Blueprint(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences);
	static void GetAssetReferenceFromArrayAssetObjectProperty_Blueprint(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences);

	template<int32 SIZE>
	static void GetAssetReferenceFromFixedArrayAssetObjectProperty_Blueprint_EnumSize(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
	{
		if (TAssetPtr<UBlueprint>(*Member)[SIZE] = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UBlueprint>[SIZE]>(InObject))
		{
			const FString MemberName = AssetObjectProperty->GetName();

			if (!CanLoad(InObject, InClass, MemberName, LoadFlags))
				return;

			for (int32 I = 0; I < SIZE; I++)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
				const FString AssetName				 = AssetRef.ToString();

				if (AssetName == TEXT(""))
					continue;

				OutAssetReferences.AddDefaulted();

				const int32 Size = OutAssetReferences.Num();
				// TODO: Fix / Investigate. 4.16.1. Built Game (Okay in Editor). TAssetPtr for UAnimBlueprint / UWidgetBlueprint does NOT have _C
				FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
				Reference.Reference				   = AssetName.EndsWith(TEXT("_C")) ? AssetName : AssetName + TEXT("_C");
				Reference.Reference_Internal	   = FStringAssetReference(Reference.Reference);
#if WITH_EDITOR
				if (CalculateResourceSizes)
				{
					UObject* Asset = Cast<UObject>((*Member)[I].LoadSynchronous());

					Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(EResourceSizeMode::Inclusive);
					Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
					Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
				}
#endif // #if WITH_EDITOR
			}
		}
	}

	template<int32 SIZE>
	static void GetAssetReferenceFromFixedArrayAssetObjectProperty_Blueprint_EnumSize(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
	{
		if (TAssetPtr<UBlueprint>(*Member)[SIZE] = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UBlueprint>[SIZE]>(InObject))
		{
			const FString MemberName = AssetObjectProperty->GetName();

			if (!CanLoad(InObject, InClass, MemberName, LoadFlags))
				return;

			for (int32 I = 0; I < SIZE; I++)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
				const FString AssetName				 = AssetRef.ToString();

				if (AssetName == TEXT(""))
					continue;

				OutAssetReferences.AddDefaulted();

				const int32 Size = OutAssetReferences.Num();
				// TODO: Fix / Investigate. 4.16.1. Built Game (Okay in Editor). TAssetPtr for UWidgetBlueprint does NOT have _C
				FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
				Reference.Reference				   = AssetName.EndsWith(TEXT("_C")) ? AssetName : AssetName + TEXT("_C");
				Reference.Reference_Internal	   = FStringAssetReference(Reference.Reference);
#if WITH_EDITOR
				if (CalculateResourceSizes)
				{
					UObject* Asset = Cast<UObject>((*Member)[I].LoadSynchronous());

					Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(EResourceSizeMode::Inclusive);
					Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
					Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
				}
#endif // #if WITH_EDITOR
			}
		}
	}

	template<typename T, int32 SIZE>
	static void GetAssetReferencesFromFixedArrayStructProperty_EnumSize(UStructProperty* &StructProperty, void* InObject, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromStruct_Internal Internal = NULL)
	{
		if (T(*Member)[SIZE] = StructProperty->ContainerPtrToValuePtr<T[SIZE]>(InObject))
		{
			for (int32 I = 0; I < SIZE; I++)
			{
				UCsCommon::GetAssetReferencesFromStruct((void*)&((*Member)[I]), StructProperty->Struct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal);
			}
		}
	}

	template<typename T>
	static void GetAssetReferenceFromAssetClassProperty(UAssetClassProperty* &AssetClassProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences)
	{
		if (TAssetSubclassOf<T>* Member = AssetClassProperty->ContainerPtrToValuePtr<TAssetSubclassOf<T>>(InObject))
		{
			const FStringAssetReference AssetRef = Member->ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			if (AssetName == TEXT(""))
				return;

			const FString MemberName	 = AssetClassProperty->GetName();
			const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

			if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
			{
				if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
				{
					if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
					{
						OutAssetReferences.AddDefaulted();

						const int32 Size = OutAssetReferences.Num();

						FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
						Reference.Reference				   = AssetName;
						Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
						if (CalculateResourceSizes)
						{
							UObject* Asset = Cast<UObject>(Member->LoadSynchronous());

							Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(ResourceSizeMode);
							Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
							Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
						}
#endif // #if WITH_EDITOR
					}
				}
			}
		}
	}

	template<typename T>
	static void GetAssetReferenceFromAssetClassProperty(UAssetClassProperty* &AssetClassProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences)
	{
		if (TAssetSubclassOf<T>* Member = AssetClassProperty->ContainerPtrToValuePtr<TAssetSubclassOf<T>>(InObject))
		{
			const FStringAssetReference AssetRef = Member->ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			if (AssetName == TEXT(""))
				return;

			const FString MemberName = AssetClassProperty->GetName();
			const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

			if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
			{
				if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
				{
					if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
					{
						OutAssetReferences.AddDefaulted();

						const int32 Size = OutAssetReferences.Num();

						FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
						Reference.Reference				   = AssetName;
						Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
						if (CalculateResourceSizes)
						{
							UObject* Asset = Cast<UObject>(Member->LoadSynchronous());

							Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(ResourceSizeMode);
							Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
							Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
						}
#endif // #if WITH_EDITOR
					}
				}
			}
		}
	}

	template<typename T>
	static void GetAssetReferenceFromArrayAssetClassProperty(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences)
	{
		if (TArray<TAssetSubclassOf<T>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetSubclassOf<T>>>(InObject))
		{
			const FString MemberName	 = ArrayAssetObjectProperty->GetName();
			const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

			int32* MemberLoadFlags = NULL;

			if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
				MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject);

			if (!MemberLoadFlags)
				return;

			if (!CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
				return;

			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; I++)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
				const FString AssetName				 = AssetRef.ToString();

				if (AssetName == TEXT(""))
					continue;

				OutAssetReferences.AddDefaulted();

				const int32 Size = OutAssetReferences.Num();

				FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
				Reference.Reference				   = AssetName;
				Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
				if (CalculateResourceSizes)
				{
					UObject* Asset = Cast<UObject>((*Member)[I].LoadSynchronous());

					Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(ResourceSizeMode);
					Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
					Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
				}
#endif // #if WITH_EDITOR
			}
		}
	}

	template<typename T>
	static void GetAssetReferenceFromArrayAssetClassProperty(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences)
	{
		if (TArray<TAssetSubclassOf<T>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetSubclassOf<T>>>(InObject))
		{
			const FString MemberName	 = ArrayAssetObjectProperty->GetName();
			const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

			int32* MemberLoadFlags = NULL;

			if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
				MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject);

			if (!MemberLoadFlags)
				return;

			if (!CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
				return;

			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; I++)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
				const FString AssetName				 = AssetRef.ToString();

				if (AssetName == TEXT(""))
					continue;

				OutAssetReferences.AddDefaulted();

				const int32 Size = OutAssetReferences.Num();

				FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
				Reference.Reference				   = AssetName;
				Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
				if (CalculateResourceSizes)
				{
					UObject* Asset = Cast<UObject>((*Member)[I].LoadSynchronous());

					Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(ResourceSizeMode);
					Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
					Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
				}
#endif // #if WITH_EDITOR
			}
		}
	}

	template<typename T>
	static void GetAssetReferencesFromStructProperty(UStructProperty* &StructProperty, void* InObject, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromStruct_Internal Internal = NULL)
	{
		if (T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject))
			GetAssetReferencesFromStruct((void*)Member, StructProperty->Struct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal);
	}

	template<typename T>
	static void GetAssetReferencesFromArrayStructProperty(UArrayProperty* ArrayProperty, void* InObject, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromStruct_Internal Internal = NULL)
	{
		if (TArray<T>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<T>>(InObject))
		{
			UStructProperty* StructProperty = Cast<UStructProperty>(ArrayProperty->Inner);

			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; I++)
			{
				GetAssetReferencesFromStruct((void*)&((*Member)[I]), StructProperty->Struct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal);
			}
		}
	}

#pragma endregion CsStringAssetReference

	static void GetAssetReferencesFromStruct(void* InStruct, UScriptStruct* const &InScriptStruct, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromStruct_Internal Internal = NULL);
	static void GetAssetReferencesFromObject(void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromObject_Internal Internal = NULL);

#pragma endregion Asset References

	// Load
#pragma region

	template<typename T>
	static void LoadTAssetPtr(const FString &MemberName, TAssetPtr<T> AssetPtr, T* &Internal, const FString &AssetType, const FString &AssetErrorMessageType)
	{
		const FString AssetName = AssetPtr.ToString();

		if (AssetName == TEXT(""))
		{
			Internal = nullptr;
			return;
		}

		if (Internal &&
			AssetPtr.IsValid() &&
			Internal == AssetPtr.Get())
		{
			UE_LOG(LogLoad, Warning, TEXT("Load (%s): Possibly trying to load %s and it is already loaded"), *MemberName, *AssetErrorMessageType);
			return;
		}
	
		if (AssetPtr.IsValid() && AssetPtr.Get())
		{
			Internal = AssetPtr.Get();
		}
		else
		{
			if (T* Data = AssetPtr.LoadSynchronous())
			{
				Internal = Data;
			}
			else
			{
				const FString AssetDescription = AssetType + TEXT("'") + AssetName + TEXT("'");

				UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetPtr (%s): Failed to load %s at %s"), *MemberName, *AssetErrorMessageType, *AssetDescription);

				Internal = nullptr;
			}
		}
	}

	template<typename T>
	static void LoadTAssetPtr(const FString &MemberName, TAssetPtr<T>* AssetPtr, T* &Internal, const FString &AssetType, const FString &AssetErrorMessageType)
	{
		const FString AssetName = AssetPtr->ToString();

		if (AssetName == TEXT(""))
		{
			Internal = nullptr;
			return;
		}

		if (Internal &&
			AssetPtr->IsValid() &&
			Internal == AssetPtr->Get())
		{
			//UE_LOG(LogLoad, Warning, TEXT("Load (%s): Possibly trying to load %s and it is already loaded"), *MemberName, *AssetErrorMessageType);
			return;
		}

		if (AssetPtr->IsValid() && AssetPtr->Get())
		{
			Internal = AssetPtr->Get();
		}
		else
		{
			if (T* Data = AssetPtr->LoadSynchronous())
			{
				Internal = Data;
			}
			else
			{
				const FString AssetDescription = AssetType + TEXT("'") + AssetName + TEXT("'");

				UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetPtr (%s): Failed to load %s at %s"), *MemberName, *AssetErrorMessageType, *AssetDescription);

				Internal = nullptr;
			}
		}
	}

	template<typename T>
	static void LoadTAssetPtr(const FString &MemberName, TAssetPtr<T> AssetPtr, TWeakObjectPtr<T> &Internal, const FString &AssetType, const FString &AssetErrorMessageType)
	{
		const FString AssetName = AssetPtr.ToString();

		if (AssetName == TEXT(""))
		{
			Internal = nullptr;
			return;
		}

		if (Internal.IsValid() && Internal.Get() &&
			AssetPtr.IsValid() &&
			Internal.Get() == AssetPtr.Get())
		{
			//UE_LOG(LogLoad, Warning, TEXT("Load (%s): Possibly trying to load %s and it is already loaded"), *MemberName, *AssetErrorMessageType);
			return;
		}

		if (AssetPtr.IsValid() && AssetPtr.Get())
		{
			Internal = AssetPtr.Get();
		}
		else
		{
			if (T* Data = AssetPtr.LoadSynchronous())
			{
				Internal = Data;
			}
			else
			{
				const FString AssetDescription = AssetType + TEXT("'") + AssetName + TEXT("'");

				UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetPtr (%s): Failed to load %s at %s"), *MemberName, *AssetErrorMessageType, *AssetDescription);

				Internal = nullptr;
			}
		}
	}

	static void LoadTAssetPtr_Blueprint(const FString &MemberName, TAssetPtr<UBlueprint> AssetPtr, UBlueprintGeneratedClass* &Internal);
	static void LoadTAssetPtr_Blueprint(const FString &MemberName, TAssetPtr<UBlueprint>* AssetPtr, UBlueprintGeneratedClass* &Internal);

	static void LoadTAssetPtr_AnimBlueprint(const FString &MemberName, TAssetPtr<UAnimBlueprint> AssetPtr, UAnimBlueprintGeneratedClass* &Internal);
	static void LoadTAssetPtr_AnimBlueprint(const FString &MemberName, TAssetPtr<UAnimBlueprint>* AssetPtr, UAnimBlueprintGeneratedClass* &Internal);

	template<typename T>
	static void LoadTAssetSubclassOf(const FString &MemberName, TAssetSubclassOf<T> &AssetSubclassOf, T* &Internal, const FString &AssetErrorMessageType)
	{
		const FString AssetName = AssetSubclassOf.ToString();

		if (AssetName == TEXT(""))
		{
			Internal = nullptr;
			return;
		}

		if (Internal &&
			AssetSubclassOf.IsValid() && AssetSubclassOf.Get() &&
			Internal == AssetSubclassOf.Get()->template GetDefaultObject<T>())
		{
			UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetSubclassOf (%s): Possibly trying to load %s and it is already loaded"), *MemberName, *AssetErrorMessageType);
			return;
		}

		if (AssetSubclassOf.IsValid() && AssetSubclassOf.Get())
		{
			Internal = AssetSubclassOf.Get()->template GetDefaultObject<T>();
		}
		else
		{
			if (UClass* DataClass = AssetSubclassOf.LoadSynchronous())
			{
				Internal = DataClass->GetDefaultObject<T>();
			}
			else
			{
				const FString AssetDescription = TEXT("Blueprint'") + AssetName + TEXT("'");

				UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetSubclassOf (%s): Failed to load %s at %s"), *MemberName, *AssetErrorMessageType, *AssetDescription);

				Internal = nullptr;
			}
		}
	}

	template<typename T>
	static void LoadTAssetSubclassOf(const FString &MemberName, TAssetSubclassOf<T>* &AssetSubclassOf, T* &Internal, const FString &AssetErrorMessageType)
	{
		const FString AssetName = AssetSubclassOf->ToString();

		if (AssetName == TEXT(""))
		{
			Internal = nullptr;
			return;
		}

		if (Internal &&
			AssetSubclassOf->IsValid() && AssetSubclassOf->Get() &&
			Internal == AssetSubclassOf->Get()->template GetDefaultObject<T>())
		{
			UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetSubclassOf (%s): Possibly trying to load %s and it is already loaded"), *MemberName, *AssetErrorMessageType);
			return;
		}

		if (AssetSubclassOf->IsValid() && AssetSubclassOf->Get())
		{
			Internal = AssetSubclassOf->Get()->template GetDefaultObject<T>();
		}
		else
		{
			if (UClass* DataClass = AssetSubclassOf->LoadSynchronous())
			{
				Internal = DataClass->GetDefaultObject<T>();
			}
			else
			{
				const FString AssetDescription = TEXT("Blueprint'") + AssetName + TEXT("'");

				UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetSubclassOf (%s): Failed to load %s at %s"), *MemberName, *AssetErrorMessageType, *AssetDescription);

				Internal = nullptr;
			}
		}
	}

	template<typename T>
	static void LoadTAssetSubclassOf(const FString &MemberName, TAssetSubclassOf<T> &AssetSubclassOf, TWeakObjectPtr<T> &Internal, const FString &AssetErrorMessageType)
	{
		const FString AssetName = AssetSubclassOf.ToString();

		if (AssetName == TEXT(""))
		{
			Internal = nullptr;
			return;
		}

		if (Internal.IsValid() && Internal.Get() &&
			AssetSubclassOf.IsValid() && AssetSubclassOf.Get() &&
			Internal == AssetSubclassOf.Get()->template GetDefaultObject<T>())
		{
			UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetSubclassOf (%s): Possibly trying to load %s and it is already loaded"), *MemberName, *AssetErrorMessageType);
			return;
		}

		if (AssetSubclassOf.IsValid() && AssetSubclassOf.Get())
		{
			Internal = AssetSubclassOf.Get()->template GetDefaultObject<T>();
		}
		else
		{
			if (UClass* DataClass = AssetSubclassOf.LoadSynchronous())
			{
				Internal = DataClass->GetDefaultObject<T>();
			}
			else
			{
				const FString AssetDescription = TEXT("Blueprint'") + AssetName + TEXT("'");

				UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetSubclassOf (%s): Failed to load %s at %s"), *MemberName, *AssetErrorMessageType, *AssetDescription);

				Internal = nullptr;
			}
		}
	}

	template<typename T>
	static void LoadTAssetSubclassOf(TAssetSubclassOf<T> &AssetSubclassOf, T* &OutAsset, const FString &AssetErrorMessageType)
	{
		OutAsset = nullptr;

		const FString AssetName = AssetSubclassOf.ToString();

		if (AssetName == TEXT(""))
			return;

		if (AssetSubclassOf.IsValid() && AssetSubclassOf.Get())
		{
			OutAsset = AssetSubclassOf.Get()->template GetDefaultObject<T>();
		}
		else
		{
			if (UClass* DataClass = AssetSubclassOf.LoadSynchronous())
			{
				OutAsset = DataClass->GetDefaultObject<T>();
			}
			else
			{
				const FString AssetDescription = TEXT("Blueprint'") + AssetName + TEXT("'");

				UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetSubclassOf (%s): Failed to load %s at %s"), *AssetErrorMessageType, *AssetDescription);
			}
		}
	}

	template<typename T>
	static void SetTArrayFromTArrayTAssetPtr(TArray<T*> &Array, TArray<TAssetPtr<T>> &ArrayAssetPtr)
	{
		Array.Reset();

		const int32 Count = ArrayAssetPtr.Num();

		for (int32 I = 0; I < Count; I++)
		{
			Array.Add(ArrayAssetPtr[I].Get());
		}
	}

	template<typename T>
	static void SetTArrayFromTArrayTAssetPtr(TArray<T*> &Array, TArray<TAssetPtr<T>>* &ArrayAssetPtr)
	{
		Array.Reset();

		const int32 Count = ArrayAssetPtr->Num();

		for (int32 I = 0; I < Count; I++)
		{
			Array.Add((*ArrayAssetPtr)[I].Get());
		}
	}

	template<typename T>
	static void SetTArrayFromTArrayTAssetPtr(TArray<TWeakObjectPtr<T>> &Array, TArray<TAssetPtr<T>> &ArrayAssetPtr)
	{
		Array.Reset();

		const int32 Count = ArrayAssetPtr.Num();

		for (int32 I = 0; I < Count; I++)
		{
			Array.Add(ArrayAssetPtr[I].Get());
		}
	}

	template<typename T>
	static void SetTArrayFromTArrayTAssetPtr(TArray<TWeakObjectPtr<T>> &Array, TArray<TAssetPtr<T>>* &ArrayAssetPtr)
	{
		Array.Reset();

		const int32 Count = ArrayAssetPtr->Num();

		for (int32 I = 0; I < Count; I++)
		{
			Array.Add((*ArrayAssetPtr)[I].Get());
		}
	}

	template<typename T>
	static void LoadTArrayTAssetPtr(const FString &MemberName, TArray<TAssetPtr<T>> &ArrayAssetPtr, TArray<T*> &ArrayInternal, const FString &AssetType, const FString &AssetErrorMessageType)
	{
		if (ArrayInternal.Num() > 0 &&
			AreAllElementsInTArrayNotNull(ArrayInternal))
		{
			//UE_LOG(LogLoad, Warning, TEXT("Load (%s): Possibly trying to load %s and it is already loaded"), *MemberName, *AssetErrorMessageType);
		}

		if (ArrayAssetPtr.Num() > 0 &&
			AreAllElementsInTArrayAssetPtrNotNull(ArrayAssetPtr))
		{
			SetTArrayFromTArrayTAssetPtr<T>(ArrayInternal, ArrayAssetPtr);
		}
		else
		{
			UCsCommon::NullAndEmptyTArray<T>(ArrayInternal);

			const int32 Count = ArrayAssetPtr.Num();

			for (int32 I = 0; I < Count; I++)
			{
				TAssetPtr<T>& AssetPtr				  = ArrayAssetPtr[I];
				const FStringAssetReference& AssetRef = AssetPtr.ToStringReference();
				const FString AssetName				  = AssetRef.ToString();

				if (AssetName != TEXT(""))
				{
					const FString AssetDescription = AssetType + TEXT("'") + AssetName + TEXT("'");
					T* Data						   = Cast<T>(StaticLoadObject(T::StaticClass(), NULL, *AssetDescription, NULL, LOAD_None, NULL));

					if (!Data)
					{
						UE_LOG(LogLoad, Warning, TEXT("Load (%s[%d]): Failed to load %s at %s"), *MemberName, I, *AssetErrorMessageType, *AssetDescription);
					}
					ArrayInternal.Add(Data);
				}
				else
				{
					ArrayInternal.Add(nullptr);
				}
			}
		}
	}

	template<typename T>
	static void LoadTArrayTAssetPtr(const FString &MemberName, TArray<TAssetPtr<T>>* &ArrayAssetPtr, TArray<T*> &ArrayInternal, const FString &AssetType, const FString &AssetErrorMessageType)
	{
		if (ArrayInternal.Num() > 0 &&
			AreAllElementsInTArrayNotNull(ArrayInternal))
		{
			//UE_LOG(LogLoad, Warning, TEXT("Load (%s): Possibly trying to load %s and it is already loaded"), *MemberName, *AssetErrorMessageType);
		}

		if (ArrayAssetPtr->Num() > 0 &&
			AreAllElementsInTArrayAssetPtrNotNull(ArrayAssetPtr))
		{
			SetTArrayFromTArrayTAssetPtr<T>(ArrayInternal, ArrayAssetPtr);
		}
		else
		{
			UCsCommon::NullAndEmptyTArray<T>(ArrayInternal);

			const int32 Count = ArrayAssetPtr->Num();

			for (int32 I = 0; I < Count; I++)
			{
				TAssetPtr<T>& AssetPtr				  = (*ArrayAssetPtr)[I];
				const FStringAssetReference& AssetRef = AssetPtr.ToStringReference();
				const FString AssetName				  = AssetRef.ToString();

				if (AssetName != TEXT(""))
				{
					const FString AssetDescription = AssetType + TEXT("'") + AssetName + TEXT("'");
					T* Data						   = Cast<T>(StaticLoadObject(T::StaticClass(), NULL, *AssetDescription, NULL, LOAD_None, NULL));

					if (!Data)
					{
						UE_LOG(LogLoad, Warning, TEXT("Load (%s[%d]): Failed to load %s at %s"), *MemberName, I, *AssetErrorMessageType, *AssetDescription);
					}
					ArrayInternal.Add(Data);
				}
				else
				{
					ArrayInternal.Add(nullptr);
				}
			}
		}
	}

	template<typename T>
	static void LoadTArrayTAssetPtr(const FString &MemberName, TArray<TAssetPtr<T>> &ArrayAssetPtr, TArray<TWeakObjectPtr<T>> &ArrayInternal, const FString &AssetType, const FString &AssetErrorMessageType)
	{
		if (ArrayInternal.Num() > 0 &&
			AreAllElementsInTArrayNotNull(ArrayInternal))
		{
			//UE_LOG(LogLoad, Warning, TEXT("Load (%s): Possibly trying to load %s and it is already loaded"), *MemberName, *AssetErrorMessageType);
		}

		if (ArrayAssetPtr.Num() > 0 &&
			AreAllElementsInTArrayAssetPtrNotNull(ArrayAssetPtr))
		{
			SetTArrayFromTArrayTAssetPtr<T>(ArrayInternal, ArrayAssetPtr);
		}
		else
		{
			UCsCommon::NullAndEmptyTArray<T>(ArrayInternal);

			const int32 Count = ArrayAssetPtr.Num();

			for (int32 I = 0; I < Count; I++)
			{
				TAssetPtr<T>& AssetPtr				  = ArrayAssetPtr[I];
				const FStringAssetReference& AssetRef = AssetPtr.ToStringReference();
				const FString AssetName				  = AssetRef.ToString();

				if (AssetName != TEXT(""))
				{
					const FString AssetDescription = AssetType + TEXT("'") + AssetName + TEXT("'");
					T* Data						   = Cast<T>(StaticLoadObject(T::StaticClass(), NULL, *AssetDescription, NULL, LOAD_None, NULL));

					if (!Data)
					{
						UE_LOG(LogLoad, Warning, TEXT("Load (%s[%d]): Failed to load %s at %s"), *MemberName, I, *AssetErrorMessageType, *AssetDescription);
					}
					ArrayInternal.Add(Data);
				}
				else
				{
					ArrayInternal.Add(nullptr);
				}
			}
		}
	}

	static void LoadTArrayTAssetPtr_Blueprint(const FString &MemberName, TArray<TAssetPtr<UBlueprint>> &ArrayAssetPtr, TArray<UBlueprintGeneratedClass*> &ArrayInternal);
	static void LoadTArrayTAssetPtr_Blueprint(const FString &MemberName, TArray<TAssetPtr<UBlueprint>>* &ArrayAssetPtr, TArray<UBlueprintGeneratedClass*> &ArrayInternal);

	template<typename T>
	static void SetTArrayFromTArrayTAssetSubclassOf(TArray<T*> &Array, TArray<TAssetSubclassOf<T>> &ArrayAssetSubclassOf)
	{
		Array.Reset();

		const int32 Count = ArrayAssetSubclassOf.Num();

		for (int32 I = 0; I < Count; I++)
		{
			Array.Add(ArrayAssetSubclassOf[I].Get()->template GetDefaultObject<T>());
		}
	}

	template<typename T>
	static void SetTArrayFromTArrayTAssetSubclassOf(TArray<T*> &Array, TArray<TAssetSubclassOf<T>>* &ArrayAssetSubclassOf)
	{
		Array.Reset();

		const int32 Count = ArrayAssetSubclassOf->Num();

		for (int32 I = 0; I < Count; I++)
		{
			Array.Add((*ArrayAssetSubclassOf)[I].Get()->template GetDefaultObject<T>());
		}
	}

	template<typename T>
	static void LoadTArrayTAssetSubclassOf(const FString &MemberName, TArray<TAssetSubclassOf<T>>* &ArrayAssetSubclassOf, TArray<T*> &ArrayInternal, const FString &AssetErrorMessageType)
	{
		if (ArrayInternal.Num() > 0 &&
			AreAllElementsInTArrayNotNull(ArrayInternal))
		{
			//UE_LOG(LogLoad, Warning, TEXT("Load (%s): Possibly trying to load %s and it is already loaded"), *MemberName, *AssetErrorMessageType);
		}

		if (ArrayAssetSubclassOf->Num() > 0 &&
			AreAllElementsInTArrayAssetSubclassOfNotNull(ArrayAssetSubclassOf))
		{
			SetTArrayFromTArrayTAssetSubclassOf<T>(ArrayInternal, ArrayAssetSubclassOf);
		}
		else
		{
			UCsCommon::NullAndEmptyTArray<T>(ArrayInternal);

			const int32 Count = ArrayAssetSubclassOf->Num();

			for (int32 I = 0; I < Count; I++)
			{
				TAssetSubclassOf<T>& AssetSubclassOf  = (*ArrayAssetSubclassOf)[I];
				const FStringAssetReference& AssetRef = AssetSubclassOf.ToStringReference();
				const FString AssetName				  = AssetRef.ToString();

				if (AssetName != TEXT(""))
				{
					const FString AssetDescription = TEXT("Blueprint'") + AssetName + TEXT("'");
					UClass* DataClass			   = (UClass*)(StaticLoadObject(UClass::StaticClass(), NULL, *AssetDescription, NULL, LOAD_None, NULL));

					if (DataClass)
					{
						ArrayInternal.Add(DataClass->GetDefaultObject<T>());
						check(DataClass->GetDefaultObject<T>());
					}
				    else
					{
						UE_LOG(LogLoad, Warning, TEXT("Load (%s[%d]): Failed to load %s at %s"), *MemberName, I, *AssetErrorMessageType, *AssetDescription);
					}
					
				}
				else
				{
					ArrayInternal.Add(nullptr);
				}
			}
		}
	}

	template<typename T>
	static void LoadFCsStruct(const FString &MemberName, T* InStruct, const ECsLoadFlags &LoadFlags)
	{
		LoadStructWithTAssetPtrs(MemberName, InStruct, T::StaticStruct(), LoadFlags);
	}

	template<typename T>
	static void LoadFCsStruct(const FString &MemberName, T* InStruct)
	{
		LoadFCsStruct<T>(MemberName, InStruct, ECsLoadFlags::All);
	}

	static void LoadFCsAnimSequence(const FString &MemberName, FCsAnimSequence* Anim, const ECsLoadFlags &LoadFlags);
	static void LoadFCsAnimSequence(const FString &MemberName, FCsAnimSequence* Anim);
	static void LoadFCsFpsAnimSequence(const FString &MemberName, FCsFpsAnimSequence* Anim, const ECsLoadFlags &LoadFlags);
	static void LoadFCsFpsAnimSequence(const FString &MemberName, FCsFpsAnimSequence* Anim, const TCsViewType &ViewType);

	static void LoadFCsAnimMontage(const FString &MemberName, FCsAnimMontage* Anim, const ECsLoadFlags &LoadFlags);
	static void LoadFCsAnimMontage(const FString &MemberName, FCsAnimMontage* Anim);
	static void LoadFCsFpsAnimMontage(const FString &MemberName, FCsFpsAnimMontage* Anim, const ECsLoadFlags &LoadFlags);
	static void LoadFCsFpsAnimMontage(const FString &MemberName, FCsFpsAnimMontage* Anim, const TCsViewType &ViewType);

	static bool CanLoad(void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags);
	static bool CanLoad(void* InObject, UClass* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags);

	template<typename T>
	static void LoadAssetClassProperty(UAssetClassProperty* &AssetClassProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString &MemberName, const FString &AssetType, const ECsLoadFlags &LoadFlags)
	{
		if (TAssetSubclassOf<T>* Member = AssetClassProperty->ContainerPtrToValuePtr<TAssetSubclassOf<T>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags))
				return;

			const FString InternalMemberName = MemberName + TEXT("_Internal");

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (T** Internal = InternalProperty->ContainerPtrToValuePtr<T*>(InObject))
					LoadTAssetSubclassOf<T>(ObjectName + TEXT(".") + MemberName, Member, *Internal, AssetType);
			}
		}
	}

	template<typename T>
	static void LoadAssetClassProperty(UAssetClassProperty* &AssetClassProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const FString &AssetType, const ECsLoadFlags &LoadFlags)
	{
		if (TAssetSubclassOf<T>* Member = AssetClassProperty->ContainerPtrToValuePtr<TAssetSubclassOf<T>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags))
				return;

			const FString InternalMemberName = MemberName + TEXT("_Internal");

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (T** Internal = InternalProperty->ContainerPtrToValuePtr<T*>(InObject))
					LoadTAssetSubclassOf<T>(ObjectName + TEXT(".") + MemberName, Member, *Internal, AssetType);
			}
		}
	}

	template<typename T>
	static void LoadArrayAssetClassProperty(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString &MemberName, const FString &AssetErrorMessageType, const ECsLoadFlags &LoadFlags)
	{
		if (TArray<TAssetSubclassOf<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TAssetSubclassOf<T>>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags))
				return;

			const FString InternalMemberName = MemberName + TEXT("_Internal");

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (TArray<T*>* Internal = InternalProperty->ContainerPtrToValuePtr<TArray<T*>>(InObject))
					LoadTArrayTAssetSubclassOf<T>(ObjectName + TEXT(".") + MemberName, Member, *Internal, AssetErrorMessageType);
			}
		}
	}

	template<typename T>
	static void LoadArrayAssetClassProperty(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const FString &AssetErrorMessageType, const ECsLoadFlags &LoadFlags)
	{
		if (TArray<TAssetSubclassOf<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TAssetSubclassOf<T>>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags))
				return;

			const FString InternalMemberName = MemberName + TEXT("_Internal");

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (TArray<T*>* Internal = InternalProperty->ContainerPtrToValuePtr<TArray<T*>>(InObject))
					LoadTArrayTAssetSubclassOf<T>(ObjectName + TEXT(".") + MemberName, Member, *Internal, AssetErrorMessageType);
			}
		}
	}

	template<typename T>
	static void LoadAssetObjectProperty(UAssetObjectProperty* &AssetObjectProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString &MemberName, const FString &AssetType, const FString &AssetErrorMessageType, const ECsLoadFlags &LoadFlags)
	{
		if (TAssetPtr<T>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags))
				return;

			const FString InternalMemberName = MemberName + TEXT("_Internal");

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (T** Internal = InternalProperty->ContainerPtrToValuePtr<T*>(InObject))
					LoadTAssetPtr<T>(ObjectName + TEXT(".") + MemberName, Member, *Internal, AssetType, AssetErrorMessageType);
			}
		}
	}

	template<typename T>
	static void LoadAssetObjectProperty(UAssetObjectProperty* &AssetObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const FString &AssetType, const FString &AssetErrorMessageType, const ECsLoadFlags &LoadFlags)
	{
		if (TAssetPtr<T>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags))
				return;

			const FString InternalMemberName = MemberName + TEXT("_Internal");

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (T** Internal = InternalProperty->ContainerPtrToValuePtr<T*>(InObject))
					LoadTAssetPtr<T>(ObjectName + TEXT(".") + MemberName, Member, *Internal, AssetType, AssetErrorMessageType);
			}
		}
	}

	static void LoadAssetObjectProperty_AnimBlueprint(UAssetObjectProperty* &AssetObjectProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags);
	static void LoadAssetObjectProperty_AnimBlueprint(UAssetObjectProperty* &AssetObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags);

	static void LoadAssetObjectProperty_Blueprint(UAssetObjectProperty* &AssetObjectProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags);
	static void LoadAssetObjectProperty_Blueprint(UAssetObjectProperty* &AssetObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags);

	template<typename T>
	static void LoadArrayAssetObjectProperty(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString &MemberName, const FString &AssetType, const FString &AssetErrorMessageType, const ECsLoadFlags &LoadFlags)
	{
		if (TArray<TAssetPtr<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<T>>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags))
				return;

			const FString InternalMemberName = MemberName + TEXT("_Internal");

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (TArray<T*>* Internal = InternalProperty->ContainerPtrToValuePtr<TArray<T*>>(InObject))
					LoadTArrayTAssetPtr<T>(ObjectName + TEXT(".") + MemberName, Member, *Internal, AssetType, AssetErrorMessageType);
			}
		}
	}

	template<typename T>
	static void LoadArrayAssetObjectProperty(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const FString &AssetType, const FString &AssetErrorMessageType, const ECsLoadFlags &LoadFlags)
	{
		if (TArray<TAssetPtr<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<T>>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags))
				return;

			const FString InternalMemberName = MemberName + TEXT("_Internal");

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (TArray<T*>* Internal = InternalProperty->ContainerPtrToValuePtr<TArray<T*>>(InObject))
					LoadTArrayTAssetPtr<T>(ObjectName + TEXT(".") + MemberName, Member, *Internal, AssetType, AssetErrorMessageType);
			}
		}
	}

	template<typename T, typename E, int32 SIZE>
	static void LoadFixedArrayAssetObjectProperty_EnumSize(UAssetObjectProperty* &AssetObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const FString &AssetType, const FString &AssetErrorMessageType, const ECsLoadFlags &LoadFlags, FString(*ToString)(const E&))
	{
		if (TAssetPtr<T>(*Member)[SIZE] = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>[SIZE]>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags))
				return;

			const FString InternalMemberName = MemberName + TEXT("_Internal");

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (T*(*Internal)[SIZE] = InternalProperty->ContainerPtrToValuePtr<T*[SIZE]>(InObject))
				{
					for (int32 I = 0; I < SIZE; I++)
					{
						const FString Index		  = (*ToString)((E)I);
						const FString ElementName = MemberName + TEXT("[") + Index + TEXT("]");

						LoadTAssetPtr<T>(ElementName, (*Member)[I], (*Internal)[I], AssetType, AssetErrorMessageType);
					}
				}
			}
		}
	}

	static void LoadArrayAssetObjectProperty_Blueprint(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags);
	static void LoadArrayAssetObjectProperty_Blueprint(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags);

	template<typename E, int32 SIZE>
	static void LoadFixedArrayAssetObjectProperty_Blueprint_EnumSize(UAssetObjectProperty* &AssetObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags, FString(*ToString)(const E&))
	{
		if (TAssetPtr<UBlueprint>(*Member)[SIZE] = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UBlueprint>[SIZE]>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags))
				return;

			const FString InternalMemberName = MemberName + TEXT("_Internal");

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (UBlueprintGeneratedClass*(*Internal)[SIZE] = InternalProperty->ContainerPtrToValuePtr<UBlueprintGeneratedClass*[SIZE]>(InObject))
				{
					for (int32 I = 0; I < SIZE; I++)
					{
						const FString Index		  = (*ToString)((E)I);
						const FString ElementName = MemberName + TEXT("[") + Index + TEXT("]");
						UCsCommon::LoadTAssetPtr_Blueprint(ElementName, (*Member)[I], (*Internal)[I]);
					}
				}
			}
		}
	}

	template<typename E, int32 SIZE>
	static void LoadFixedArrayAssetObjectProperty_Blueprint_EnumSize(UAssetObjectProperty* &AssetObjectProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags, FString(*ToString)(const E&))
	{
		if (TAssetPtr<UBlueprint>(*Member)[SIZE] = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UBlueprint>[SIZE]>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags))
				return;

			const FString InternalMemberName = MemberName + TEXT("_Internal");

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (UBlueprintGeneratedClass*(*Internal)[SIZE] = InternalProperty->ContainerPtrToValuePtr<UBlueprintGeneratedClass*[SIZE]>(InObject))
				{
					for (int32 I = 0; I < SIZE; I++)
					{
						const FString Index		  = (*ToString)((E)I);
						const FString ElementName = MemberName + TEXT("[") + Index + TEXT("]");
						UCsCommon::LoadTAssetPtr_Blueprint(ElementName, (*Member)[I], (*Internal)[I]);
					}
				}
			}
		}
	}

	template<typename T>
	static void LoadMemberStructProperty(UStructProperty* &StructProperty, void* InObject, const FString &MemberName, const ECsLoadFlags &LoadFlags, TCsLoadStructWithTAssetPtrs_Internal Internal = NULL)
	{
		if (T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject))
			LoadStructWithTAssetPtrs(MemberName, (void*)Member, StructProperty->Struct, LoadFlags, Internal);
	}

	template<typename T>
	static void LoadMemberArrayStructProperty(UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName, const ECsLoadFlags &LoadFlags)
	{
		if (TArray<T>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<T>>(InObject))
		{
			UStructProperty* StructProperty = Cast<UStructProperty>(ArrayProperty->Inner);

			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; I++)
			{
				const FString ElementName = MemberName + TEXT("[") + FString::FromInt(I) + TEXT("]");
				LoadStructWithTAssetPtrs(ElementName, (void*)&((*Member)[I]), StructProperty->Struct, LoadFlags);
			}
		}
	}

	template<typename T, typename E, int32 SIZE>
	static void LoadMemberFixedArrayStructProperty_EnumSize(UStructProperty* &StructProperty, void* InObject, const FString &MemberName, const ECsLoadFlags &LoadFlags, FString(*ToString)(const E&), TCsLoadStructWithTAssetPtrs_Internal Internal = nullptr)
	{
		if (T(*Member)[SIZE] = StructProperty->ContainerPtrToValuePtr<T[SIZE]>(InObject))
		{
			for (int32 I = 0; I < SIZE; I++)
			{
				const FString Index		  = (*ToString)((E)I);
				const FString ElementName = MemberName + TEXT("[") + Index + TEXT("]");
				UCsCommon::LoadStructWithTAssetPtrs(ElementName, (void*)&((*Member)[I]), StructProperty->Struct, LoadFlags, Internal);
			}
		}
	}

	static void LoadStructWithTAssetPtrs(const FString &ObjectName, void* InStruct, UScriptStruct* const &InScriptStruct, const ECsLoadFlags &LoadFlags, TCsLoadStructWithTAssetPtrs_Internal Internal = NULL);
	static void LoadObjectWithTAssetPtrs(const FString &ObjectName, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TCsLoadObjectWithTAssetPtrs_Internal Internal = NULL);

	template<typename T, typename U, typename S>
	static void SetTArrayInternalMemberFromLoadedAssets(void* InObject, UClass* const &InClass, const FString &StructMemberName, UScriptStruct* const &InScriptStruct, const FString &MemberName, const TArray<UObject*> &LoadedAssets)
	{
		if (UStructProperty* StructProperty = FindField<UStructProperty>(InClass, *StructMemberName))
		{
			// Struct
			if (T* Struct = StructProperty->ContainerPtrToValuePtr<T>(InObject))
			{
				const FString InternalName = MemberName + TEXT("_Internal");

				TArray<TAssetPtr<U>>* AssetPtrs = nullptr;
				TArray<S*>* Internals			= nullptr;
				// Member
				if (UArrayProperty* ArrayProperty = FindField<UArrayProperty>(InScriptStruct, *MemberName))
					AssetPtrs = ArrayProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<U>>>(Struct);
				// Internal
				if (UArrayProperty* ArrayProperty = FindField<UArrayProperty>(InScriptStruct, *InternalName))
					Internals = ArrayProperty->ContainerPtrToValuePtr<TArray<S*>>(Struct);

				// Set Internal from LoadedAsset
				if (AssetPtrs && Internals)
				{
					const int32 AssetPtrCount = AssetPtrs->Num();
					const int32 AssetCount	  = LoadedAssets.Num();

					for (int32 I = 0; I < AssetPtrCount; I++)
					{
						const FString AssetName = (*AssetPtrs)[I].GetAssetName();

						for (int32 J = 0; J < AssetCount; J++)
						{
							if (LoadedAssets[J]->GetName().Contains(AssetName))
							{
								if (Internals->Num() <= I)
									Internals->AddDefaulted(I + 1 - Internals->Num());

								(*Internals)[I] = Cast<S>(LoadedAssets[J]);
							}
						}
					}
				}
			}
		}
	}

#pragma endregion Load

	// UnLoad
#pragma region
	
	template<typename T>
	static void UnLoadClassProperty(UClassProperty* &ClassProperty, void* InObject)
	{
		if (T** Internal = ClassProperty->ContainerPtrToValuePtr<T*>(InObject))
			*Internal = nullptr;
	}

	template<typename T>
	static void UnLoadObjectProperty(UObjectProperty* &ObjectProperty, void* InObject)
	{
		if (T** Internal = ObjectProperty->ContainerPtrToValuePtr<T*>(InObject))
			*Internal = nullptr;
	}

	template<typename T>
	static void UnLoadMemberStructProperty(UStructProperty* &StructProperty, void* InObject)
	{
		if (T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject))
			UnLoadStructWithTAssetPtrs((void*)Member, StructProperty->Struct);
	}
	/*
	template<typename T>
	static void UnLoadMemberFixedArrayStructProperty_Melee(UStructProperty* &StructProperty, void* InObject)
	{
		if (T(*Member)[EMeleeType::EMeleeType_MAX] = StructProperty->ContainerPtrToValuePtr<T[EMeleeType::EMeleeType_MAX]>(InObject))
		{
			const int32 Count = (int32)EMeleeType::EMeleeType_MAX;

			for (int32 I = 0; I < Count; I++)
			{
				UnLoadStructWithTAssetPtrs((void*)&((*Member)[I]), StructProperty->Struct);
			}
		}
	}
	*/
	/*
	template<typename T>
	static void UnLoadMemberFixedArrayStructProperty_Pickup(UStructProperty* &StructProperty, void* InObject)
	{
		if (T(*Member)[EPickupItem::EPickupItem_MAX] = StructProperty->ContainerPtrToValuePtr<T[EPickupItem::EPickupItem_MAX]>(InObject))
		{
			const int32 Count = (int32)EPickupItem::EPickupItem_MAX;

			for (int32 I = 0; I < Count; I++)
			{
				UnLoadStructWithTAssetPtrs((void*)&((*Member)[I]), StructProperty->Struct);
			}
		}
	}
	*/
	/*
	template<typename T>
	static void UnLoadMemberFixedArrayStructProperty_Surface(UStructProperty* &StructProperty, void* InObject)
	{
		if (T(*Member)[ESurfaceType::ESurfaceType_MAX] = StructProperty->ContainerPtrToValuePtr<T[ESurfaceType::ESurfaceType_MAX]>(InObject))
		{
			const int32 Count = (int32)ESurfaceType::ESurfaceType_MAX;

			for (int32 I = 0; I < Count; I++)
			{
				UnLoadStructWithTAssetPtrs((void*)&((*Member)[I]), StructProperty->Struct);
			}
		}
	}
	*/
	template<typename T>
	static void UnLoadMemberArrayStructProperty(UArrayProperty* &ArrayProperty, void* InObject)
	{
		if (TArray<T>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<T>>(InObject))
		{
			UStructProperty* StructProperty = Cast<UStructProperty>(ArrayProperty->Inner);

			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; I++)
			{
				UnLoadStructWithTAssetPtrs((void*)&((*Member)[I]), StructProperty->Struct);
			}
		}
	}

	template<typename T>
	static void UnLoadArrayObjectProperty(UArrayProperty* &ArrayProperty, void* InObject)
	{
		if (TArray<T*>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<T*>>(InObject))
			Member->Reset();
	}

	static void UnLoadStructWithTAssetPtrs(void* InStruct, UScriptStruct* const &InScriptStruct);
	static void UnLoadObjectWithTAssetPtrs(void* InObject, UClass* const &InClass);

#pragma endregion UnLoad

	// IsLoaded
#pragma region

	static void IsLoaded_LogMessages(const FString &DataName, TArray<FString>& OutMessages);

	template<typename T>
	static bool IsLoadedMember(const FString &MemberName, T* &Internal)
	{
		if (Internal)
		{
			UE_LOG(LogLoad, Warning, TEXT("IsLoaded (%s)"), *MemberName);
			return true;
		}
		return false;
	}

	template<typename T>
	static bool IsLoadedMember(const FString &MemberName, TArray<T*> &Internal)
	{
		bool Pass		  = true;
		const int32 Count = Internal.Num();

		for (int32 I = 0; I < Count; I++)
		{
			const FString Name = MemberName + TEXT("[") + FString::FromInt(I) + TEXT("]");
			Pass			  &= IsLoadedMember<T>(Name, Internal[I]);
		}
		return Pass;
	}

	template<typename T>
	static bool IsLoadedClassProperty(UClassProperty* &ClassProperty, void* InObject, const FString &MemberName)
	{
		if (T** Internal = ClassProperty->ContainerPtrToValuePtr<T*>(InObject))
			return IsLoadedMember<T>(MemberName, *Internal);
		return true;
	}

	template<typename T>
	static bool IsLoadedObjectProperty(UObjectProperty* &ObjectProperty, void* InObject, const FString &MemberName)
	{
		if (T** Internal = ObjectProperty->ContainerPtrToValuePtr<T*>(InObject))
			return IsLoadedMember<T>(MemberName, *Internal);
		return true;
	}

	template<typename T>
	static bool IsLoadedMemberStructProperty(UStructProperty* &StructProperty, void* InObject, const FString &MemberName)
	{
		T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject);
		return IsLoadedStructWithTAssetPtrs(MemberName, (void*)Member, StructProperty->Struct);
	}
	/*
	template<typename T>
	static bool IsLoadedMemberFixedArrayStructProperty_Melee(UStructProperty* &StructProperty, void* InObject, const FString &MemberName)
	{
		if (T(*Member)[EMeleeType::EMeleeType_MAX] = StructProperty->ContainerPtrToValuePtr<T[EMeleeType::EMeleeType_MAX]>(InObject))
		{
			bool Pass		  = true;
			const int32 Count = (int32)EMeleeType::EMeleeType_MAX;

			for (int32 I = 0; I < Count; I++)
			{
				const FString Index		  = MeleeTypeToString((TEnumAsByte<EMeleeType::Type>)I);
				const FString ElementName = MemberName + TEXT("[") + Index + TEXT("].");
				Pass &= IsLoadedStructWithTAssetPtrs(ElementName, (void*)&((*Member)[I]), StructProperty->Struct);
			}
			return Pass;
		}
		return true;
	}
	*/
	/*
	template<typename T>
	static bool IsLoadedMemberFixedArrayStructProperty_Pickup(UStructProperty* &StructProperty, void* InObject, const FString &MemberName)
	{
		if (T(*Member)[EPickupItem::EPickupItem_MAX] = StructProperty->ContainerPtrToValuePtr<T[EPickupItem::EPickupItem_MAX]>(InObject))
		{
			bool Pass = true;
			const int32 Count = (int32)EPickupItem::EPickupItem_MAX;

			for (int32 I = 0; I < Count; I++)
			{
				const FString Index		  = PickupItemToString((TEnumAsByte<EPickupItem::Type>)I);
				const FString ElementName = MemberName + TEXT("[") + Index + TEXT("].");
				Pass &= IsLoadedStructWithTAssetPtrs(ElementName, (void*)&((*Member)[I]), StructProperty->Struct);
			}
			return Pass;
		}
		return true;
	}
	*/
	/*
	template<typename T>
	static bool IsLoadedMemberFixedArrayStructProperty_Surface(UStructProperty* &StructProperty, void* InObject, const FString &MemberName)
	{
		if (T(*Member)[ESurfaceType::ESurfaceType_MAX] = StructProperty->ContainerPtrToValuePtr<T[ESurfaceType::ESurfaceType_MAX]>(InObject))
		{
			bool Pass		  = true;
			const int32 Count = (int32)ESurfaceType::ESurfaceType_MAX;

			for (int32 I = 0; I < Count; I++)
			{
				const FString Index		  = SurfaceTypeToString((TEnumAsByte<ESurfaceType::Type>)I);
				const FString ElementName = MemberName + TEXT("[") + Index + TEXT("].");
				Pass &= IsLoadedStructWithTAssetPtrs(ElementName, (void*)&((*Member)[I]), StructProperty->Struct);
			}
			return Pass;
		}
		return true;
	}
	*/
	template<typename T>
	static bool IsLoadedMemberArrayStructProperty(UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName)
	{
		if (TArray<T>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<T>>(InObject))
		{
			bool Pass						= true;
			UStructProperty* StructProperty = Cast<UStructProperty>(ArrayProperty->Inner);
			const int32 Count				= Member->Num();

			for (int32 I = 0; I < Count; I++)
			{
				const FString ElementName = MemberName + TEXT("[") + FString::FromInt(I) + TEXT("].");
				Pass &= IsLoadedStructWithTAssetPtrs(ElementName, (void*)&((*Member)[I]), StructProperty->Struct);
			}
			return Pass;
		}
		return true;
	}

	template<typename T>
	static bool IsLoadedArrayObjectProperty(UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName)
	{
		if (TArray<T*>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<T*>>(InObject))
			return IsLoadedMember<T>(MemberName, *Member);
		return true;
	}

	static bool IsLoadedStructWithTAssetPtrs(const FString &ObjectName, void* InStruct, UScriptStruct* const &InScriptStruct);
	static bool IsLoadedObjectWithTAssetPtrs(const FString &ObjectName, void* InObject, UClass* const &InClass);

#pragma endregion IsLoaded

	static TCsLoadAsyncOrder GetLoadAsyncOrder();

#pragma endregion Loading
	
// Members
#pragma region

#if WITH_EDITOR
	static void GetCategoryMemberAssociations(void* InObject, UClass* const &InClass, TArray<FCsCategoryMemberAssociation> &OutCategoryMemberAssociations);
#endif // #if WITH_EDITOR

	// Set
#pragma region

	template<typename T>
	static bool SetMemberProperty(void* InObject, UProperty* Property, void* MemberValue)
	{
		bool Changed = false;

		if (T* Member = Property->ContainerPtrToValuePtr<T>(InObject))
		{
			Changed = *Member != *((T*)MemberValue);
			*Member = *((T*)MemberValue);
		}
		return Changed;
	}

	static bool SetObjectMember(void* InObject, UClass* const &InClass, const FString &MemberName, void* MemberValue);
	static bool SetStructMember(void* InStruct, UScriptStruct* const &InScriptStruct, const FString &MemberName, void* MemberValue);

	static bool SetObjectMember(void* InObject, UClass* const &InClass, const uint16 &MemberIndex, void* MemberValue);
	static bool SetStructMember(void* InStruct, UScriptStruct* const &InScriptStruct, const uint16 &MemberIndex, void* MemberValue);

	static void SetObjectMembers(void* FromObject, void* ToObject, UClass* const &InClass, const TArray<FString>* MemberNames);

#pragma endregion Set

	// Get
#pragma region

	//static TEnumAsByte<EMemberType::Type> GetObjectMemberType(UClass* const &InClass, const FString &MemberName);
	//static TEnumAsByte<EMemberType::Type> GetStructMemberType(UScriptStruct* const &InScriptStruct, const FString &MemberName);

	template<typename T>
	static T* GetStructMember(void* InStruct, UScriptStruct* const &InScriptStruct, const FString &MemberName, TCsGetStructMember_Internal Internal = NULL)
	{
		for (TFieldIterator<UProperty> It(InScriptStruct); It; ++It)
		{
			UProperty* Property = Cast<UProperty>(*It);

			const FString PropertyName = Property->GetName();

			if (PropertyName != MemberName)
				continue;

			// Struct
			if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
			{
				if (Internal)
				{
					if (void* Ptr = (*Internal)(Property, InStruct, InScriptStruct, MemberName))
						return (T*)Ptr;
				}
				return NULL;
			}
			// bool
			if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
				return (T*)Property->ContainerPtrToValuePtr<bool>(InStruct);
			// Byte / Enum
			if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
			{
				// enum
				if (ByteProperty->IsEnum())
				{
					// ECharacterClass
					//if (ByteProperty->Enum->CppType.Contains(TEXT("ECharacterClass")))
					//	OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TEnumAsByte<ECharacterClass::Type>>(InObject));
				}
				// uint8
				return (T*)Property->ContainerPtrToValuePtr<uint8>(InStruct);
			}
			// int32
			if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
				return (T*)Property->ContainerPtrToValuePtr<int32>(InStruct);
			// float
			if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
				return (T*)Property->ContainerPtrToValuePtr<float>(InStruct);
		}
		return NULL;
	}

	static UScriptStruct* GetScriptStructMember(void* InStruct, UScriptStruct* const &InScriptStruct, const FString &MemberName, TCsGetScriptStructMember_Internal Internal = NULL);

	template<typename T>
	static T* GetObjectMember(void* InObject, UClass* const &InClass, const FString &MemberName, TCsGetObjectMember_Internal Internal = NULL)
	{
		for (TFieldIterator<UProperty> It(InClass); It; ++It)
		{
			UProperty* Property = Cast<UProperty>(*It);

			const FString PropertyName = Property->GetName();

			if (PropertyName != MemberName)
				continue;

			// Struct
			if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
			{
				if (Internal)
				{
					if (void* Ptr = (*Internal)(Property, InObject, InClass, MemberName))
						return (T*)Ptr;
				}
				return NULL;
			}
			// bool
			if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
				return (T*)Property->ContainerPtrToValuePtr<bool>(InObject);
			// Byte / Enum
			if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
			{
				// enum
				if (ByteProperty->IsEnum())
				{
					// ECharacterClass
					//if (ByteProperty->Enum->CppType.Contains(TEXT("ECharacterClass")))
					//	OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TEnumAsByte<ECharacterClass::Type>>(InObject));
				}
				// uint8
				return (T*)Property->ContainerPtrToValuePtr<uint8>(InObject);
			}
			// int32
			if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
				return (T*)Property->ContainerPtrToValuePtr<int32>(InObject);
			// float
			if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
				return (T*)Property->ContainerPtrToValuePtr<float>(InObject);
		}
		return NULL;
	}

	static uint16 GetObjectMemberIndex(UClass* const &InClass, const FString &MemberName);

	static void GetObjectMembers(void* InObject, UClass* const &InClass, const TArray<FString>* MemberNames, TArray<void*> &OutMemberValues);

#pragma endregion Get

#pragma endregion Members

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

	static FString GetProxyAsString(AActor* InActor);

	static bool IsPlayInGame(UWorld* InWorld);
	static bool IsPlayInEditor(UWorld* InWorld);
	static bool IsPlayInPIE(UWorld* InWorld);
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

// Time
#pragma region

	static uint64 GetWorldTimeMilliseconds(UWorld* InWorld);

	static float GetCurrentDateTimeSeconds();

#pragma endregion Time

	static float BytesToKilobytes(const int32 &Bytes);
	static float BytesToMegabytes(const int32 &Bytes);
	static int32 KilobytesToBytes(const float &Kilobytes);

	UFUNCTION(BlueprintCallable, Category = "Commmon")
	static bool IsDeveloperBuild();

// Physics
#pragma region

	static bool SetPhysicsPreset(FCsPhysicsPreset &Preset, UPrimitiveComponent* Component);
	static void SetPhysicsFromPreset(FCsPhysicsPreset &Preset, UPrimitiveComponent* Component);

#pragma endregion Physics

// Collision
#pragma  region

	static bool SetColliionPreset(FCsCollisionPreset &Preset, UPrimitiveComponent* Component);
	static void SetCollisionFromPreset(FCsCollisionPreset &Preset, UPrimitiveComponent* Component, bool SetCollisionEnabled = true);
	static void SetCollisionFromTemplate(const FName &TemplateName, UPrimitiveComponent* Component, bool SetCollisionEnabled = true);

#pragma endregion Collision

// Asset Registry
#pragma region

#if WITH_EDITOR

	template<typename T>
	static void SetObjectFromAssetData(FAssetData& InAssetData, const FName& AssetName, T*& OutObject, FString& OutPackagePath)
	{
		if (InAssetData.AssetName == AssetName)
		{
			OutObject = Cast<T>(InAssetData.GetAsset());
			OutPackagePath = InAssetData.PackagePath.ToString();
		}
	}

	template<typename T>
	static void SetObjectFromAssetData(FAssetData& InAssetData, const FName& AssetName, T*& OutObject)
	{
		if (InAssetData.AssetName == AssetName)
			OutObject = Cast<T>(InAssetData.GetAsset());
	}

	template<typename T>
	static UBlueprint* CreateBlueprintAsset(const FString &Name, const FString &PackagePath)
	{
		UBlueprintFactory* Factory			= NewObject<UBlueprintFactory>();
		Factory->ParentClass				= T::StaticClass();
		FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
		UBlueprint* Bp						= Cast<UBlueprint>(AssetToolsModule.Get().CreateAsset(Name, PackagePath, UBlueprint::StaticClass(), Factory));

		TArray<UObject*> ObjectsToSync;
		ObjectsToSync.Add(Bp);

		FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
		ContentBrowserModule.Get().SyncBrowserToAssets(ObjectsToSync);

		return Bp;
	}

	template<typename T>
	static T* GetAsset(const FString &Name)
	{
		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
		IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

		TArray<FAssetData> OutAssetData;

		AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

		const int32 AssetCount = OutAssetData.Num();

		for (int32 I = 0; I < AssetCount; I++)
		{
			const FString AssetStringName = OutAssetData[I].AssetName.ToString().ToLower();

			if (AssetStringName == Name)
			{
				return Cast<T>(OutAssetData[I].GetAsset());
			}
		}
		return NULL;
	}

	template<typename T>
	static T* GetAsset(const TArray<FString> &KeywordsOR)
	{
		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
		IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

		TArray<FAssetData> OutAssetData;

		AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

		const int32 AssetCount = OutAssetData.Num();
		const int32 Count = KeywordsOR.Num();

		for (int32 I = 0; I < AssetCount; I++)
		{
			const FString AssetStringName = OutAssetData[I].AssetName.ToString().ToLower();

			for (int32 J = 0; J < Count; J++)
			{
				if (AssetStringName == KeywordsOR[J])
				{
					return Cast<T>(OutAssetData[I].GetAsset());
				}
			}
		}
		return NULL;
	}

	template<typename T>
	static void GetAssets(TArray<T*> &OutAssets, const FName &Name)
	{
		OutAssets.Reset();

		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
		IAssetRegistry& AssetRegistry			  = AssetRegistryModule.Get();

		TArray<FAssetData> OutAssetData;

		AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

		const int32 AssetCount = OutAssetData.Num();

		for (int32 I = 0; I < AssetCount; I++)
		{
			if (Name == OutAssetData[I].AssetName)
				OutAssets.Add(Cast<T>(OutAssetData[I].GetAsset()));
		}
	}

	template<typename T>
	static void GetAssets(TArray<T*> &OutAssets, const FString &Name)
	{
		OutAssets.Reset();

		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
		IAssetRegistry& AssetRegistry			  = AssetRegistryModule.Get();

		TArray<FAssetData> OutAssetData;

		AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

		const FString NameLower = Name.ToLower();

		const int32 AssetCount = OutAssetData.Num();

		for (int32 I = 0; I < AssetCount; I++)
		{
			const FString AssetStringName = OutAssetData[I].AssetName.ToString().ToLower();

			if (AssetStringName == NameLower)
				OutAssets.Add(Cast<T>(OutAssetData[I].GetAsset()));
		}
	}

	template<typename T>
	static void GetAssets(TArray<T*> &OutAssets, const TArray<FString> &KeywordsAND)
	{
		OutAssets.Reset();

		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
		IAssetRegistry& AssetRegistry			  = AssetRegistryModule.Get();

		TArray<FAssetData> OutAssetData;

		AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

		const int32 AssetCount = OutAssetData.Num();
		const int32 KeywordCount = KeywordsAND.Num();

		for (int32 I = 0; I < AssetCount; I++)
		{
			const FString AssetStringName = OutAssetData[I].AssetName.ToString().ToLower();

			bool Pass = true;

			for (int32 I = 0; I < KeywordCount; I++)
			{
				Pass &= AssetStringName.Contains(KeywordsAND[I]);
			}

			if (Pass)
			{
				OutAssets.Add(Cast<T>(OutAssetData[I].GetAsset()));
			}
		}
	}

	template<typename T>
	static T* GetBlueprintDefaultObject(const FString &Name)
	{
		UBlueprint* Bp = GetAsset<UBlueprint>(Name);

		return Bp ? Cast<UBlueprintCore>(Bp)->GeneratedClass->GetDefaultObject<T>() : NULL;
	}

	template<typename T>
	static T* GetBlueprintDefaultObject(const FName &Name)
	{
		return GetBlueprintDefaultObject<T>(Name.ToString());
	}

	template<typename T>
	static void GetBlueprintDefaultObjects(TArray<T*> &OutDefaultObjects, const TArray<FString>& KeywordsAND)
	{
		TArray<UBlueprint*> OutAssets;
		GetAssets<UBlueprint>(OutAssets, KeywordsAND);

		OutDefaultObjects.Reset();

		const uint32 Count = OutAssets.Num();

		for (uint32 I = 0; I < Count; I++)
		{
			if (T* DOb = Cast<UBlueprintCore>(OutAssets[I])->GeneratedClass->GetDefaultObject<T>())
				OutDefaultObjects.Add(DOb);
		}
	}

#endif // #if WITH_EDITOR

#pragma endregion Asset Registry
};