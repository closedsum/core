// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "Json.h"
#include "JsonObjectConverter.h"

#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_Load.h"
#include "Types/CsTypes_View.h"

#include "CsCommon_Load.generated.h"

UCLASS()
class CSCORE_API UCsCommon_Load : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

// Enum to String Conversion
#pragma region

	static FString LoadFlagsToString(const int32 &LoadFlags);

#pragma endregion Enum to String Conversion

// Enum to Enum Conversion
#pragma region

	static int32 StringtoLoadFlags(const FString &LoadFlags);

	static ECsLoadFlags ViewTypeToLoadFlags(const TCsViewType &ViewType, const bool &IsLow = false);

#pragma endregion Enum to Enum Conversion

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
	static void CopyTArrays(TArray<T>& To, TArray<T>& From, T(*CreateAndCopy)(const T&) = nullptr)
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

// Json
#pragma region

// Write
#pragma region

	static void JsonWriter(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, const FName &Member);
	static void JsonWriter(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, TArray<FName> &Member, const FString &ElementName);
	static void JsonWriter_ArrayElement(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, const FName &Member);

	template<typename T>
	static void WriteTAssetPtrToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, TAssetPtr<T> &Member)
	{
		if (Member.IsValid() && Member.Get())
		{
			const FString AssetName	= Member.ToString();

			// (AssetName != TEXT(""))
			if (AssetName != ECsCachedString::Str::Empty)
			{
				InJsonWriter->WriteValue(MemberName, AssetName);
			}
			else
			{
												//   TEXT("")
				InJsonWriter->WriteValue(MemberName, ECsCachedString::Str::Empty);
			}
		}
		else
		{
											//   TEXT("")
			InJsonWriter->WriteValue(MemberName, ECsCachedString::Str::Empty);
		}
	}

	static void WriteTAssetPtrToJson_AnimBlueprint(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, TAssetPtr<class UAnimBlueprint> &Member);
	static void WriteTAssetPtrToJson_Blueprint(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, TAssetPtr<class UBlueprint> &Member);

	template<typename T>
	static void WriteTArrayTAssetPtrToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, TArray<TAssetPtr<T>> &Member)
	{
		InJsonWriter->WriteObjectStart(MemberName);
		
		const int32 Count = Member.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			WriteTAssetPtrToJson(InJsonWriter, FString::FromInt(I), Member[I]);
		}
		InJsonWriter->WriteObjectEnd();
	}

	template<typename T>
	static void WriteTAssetSubclassOfToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, TAssetSubclassOf<T> AssetSubclassOf)
	{
		if (AssetSubclassOf.IsValid() && AssetSubclassOf.Get())
		{
			const FString AssetName = AssetSubclassOf.ToString();

			// (AssetName != TEXT(""))
			if (AssetName != ECsCachedString::Str::Empty)
			{
				InJsonWriter->WriteValue(MemberName, AssetName);
			}
			else
			{
												//   TEXT("")
				InJsonWriter->WriteValue(MemberName, ECsCachedString::Str::Empty);
			}
		}
		else
		{
											//   TEXT("")
			InJsonWriter->WriteValue(MemberName, ECsCachedString::Str::Empty);
		}
	}

	template<typename T>
	static void WriteAssetClassPropertyToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UAssetClassProperty* &AssetClassProperty, void* InObject, const FString &MemberName)
	{
		if (TAssetSubclassOf<T>* Member = AssetClassProperty->ContainerPtrToValuePtr<TAssetSubclassOf<T>>(InObject))
			WriteTAssetSubclassOfToJson<T>(InJsonWriter, MemberName, *Member);
	}

	template<typename T>
	static void WriteAssetObjectPropertyToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName)
	{
		if (TAssetPtr<T>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>>(InObject))
			WriteTAssetPtrToJson<T>(InJsonWriter, MemberName, *Member);
	}

	static void WriteAssetObjectPropertyToJson_AnimBlueprint(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName);
	static void WriteAssetObjectPropertyToJson_Blueprint(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName);

	template<typename T>
	static void WriteArrayAssetObjectPropertyToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName)
	{
		if (TArray<TAssetPtr<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<T>>>(InObject))
			WriteTArrayTAssetPtrToJson<T>(InJsonWriter, MemberName, *Member);
	}

	template<typename T, typename E, int32 SIZE>
	static void WriteFixedArrayAssetObjectPropertyToJson_EnumSize(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName, FString(*ToString)(const E&))
	{
		if (TAssetPtr<T>(*Member)[SIZE] = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>[SIZE]>(InObject))
		{
			InJsonWriter->WriteObjectStart(MemberName);

			for (int32 I = 0; I < SIZE; ++I)
			{
				const FString ElementName = (*ToString)((E)I);
				WriteTAssetPtrToJson<T>(InJsonWriter, ElementName, (*Member)[I]);
			}
			InJsonWriter->WriteObjectEnd();
		}
	}

	template<typename T>
	static void WriteMemberStructPropertyToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString &MemberName, const bool &UseMemberName = true, TCsWriteStructToJson_Internal Internal = nullptr)
	{
		T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject);

		if (UseMemberName)
		{
			InJsonWriter->WriteObjectStart(MemberName);
		}
		else
		{
			InJsonWriter->WriteObjectStart();
								//   TEXT("Index")
			InJsonWriter->WriteValue(ECsCachedString::Str::Index, MemberName);
		}
		WriteStructToJson(InJsonWriter, (void*)Member, StructProperty->Struct, Internal);
		InJsonWriter->WriteObjectEnd();
	}

	template<typename T>
	static void WriteMemberArrayStructPropertyToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName, TCsWriteStructToJson_Internal Internal = nullptr)
	{
		TArray<T>* Member					 = ArrayProperty->ContainerPtrToValuePtr<TArray<T>>(InObject);
		UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner);
		
		InJsonWriter->WriteArrayStart(MemberName);

		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			InJsonWriter->WriteObjectStart();
									//   TEXT("Index")
				InJsonWriter->WriteValue(ECsCachedString::Str::Index, FString::FromInt(I));
				WriteStructToJson(InJsonWriter, (void*)&((*Member)[I]), InnerStructProperty->Struct, Internal);
			InJsonWriter->WriteObjectEnd();
		}
		InJsonWriter->WriteArrayEnd();
	}

	template<typename T, typename E, uint8 SIZE>
	static void WriteMemberFixedArrayStructPropertyToJson_EnumSize(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString &MemberName, FString(*ToString)(const E&), TCsWriteStructToJson_Internal Internal = nullptr)
	{
		T(*Member)[SIZE] = StructProperty->ContainerPtrToValuePtr<T[SIZE]>(InObject);

		InJsonWriter->WriteObjectStart(MemberName);

		for (int32 I = 0; I < SIZE; ++I)
		{
			InJsonWriter->WriteObjectStart((*ToString)((E)I));
			WriteStructToJson(InJsonWriter, (void*)&((*Member)[I]), StructProperty->Struct, Internal);
			InJsonWriter->WriteObjectEnd();
		}
		InJsonWriter->WriteObjectEnd();
	}

	template<typename T>
	static void WriteMemberStructPropertyToJson_Primitive(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString &MemberName, FString(T::*ToString)() const)
	{
		if (T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject))
			InJsonWriter->WriteValue(MemberName, ((*Member).*ToString)());
	}

	template<typename T>
	static void WriteMemberArrayStructPropertyToJson_Primitive(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName, FString(T::*ToString)() const)
	{
		TArray<T>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<T>>(InObject);

		InJsonWriter->WriteObjectStart(MemberName);

		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			InJsonWriter->WriteValue(FString::FromInt(I), ((*Member)[I].*ToString)());
		}
		InJsonWriter->WriteObjectEnd();
	}

	static void WriteMemberIntegralArrayPropertyToJson_uint64(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName);

	static void WriteMemberStructPropertyToJson_Transform(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString &MemberName);
	static void WriteMemberArrayStructPropertyToJson_Transform(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName);

	template<typename T>
	static void WriteMemberBytePropertyToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UByteProperty* &ByteProperty, void* InObject, const FString &MemberName, FString (*EnumToString)(const T&))
	{
		if (TEnumAsByte<T>* Member = ByteProperty->ContainerPtrToValuePtr<TEnumAsByte<T>>(InObject))
			InJsonWriter->WriteValue(MemberName, (*EnumToString)(*Member));
	}

	template<typename T>
	static void WriteMemberArrayBytePropertyToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName, FString(*EnumToString)(const T&))
	{
		if (TArray<TEnumAsByte<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TEnumAsByte<T>>>(InObject))
		{
			InJsonWriter->WriteObjectStart(MemberName);

			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				InJsonWriter->WriteValue(FString::FromInt(I), (*EnumToString)((*Member)[I]));
			}
			InJsonWriter->WriteObjectEnd();
		}
	}

	template<typename T, typename E, int32 SIZE>
	static void WriteMemberFixedArrayBytePropertyToJson_EnumSize(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UByteProperty* &ByteProperty, void* InObject, const FString &MemberName, FString(*EnumToString)(const T&), FString(*EnumSizeToString)(const E&))
	{
		if (TEnumAsByte<T>(*Member)[SIZE] = ByteProperty->ContainerPtrToValuePtr<TEnumAsByte<T>[SIZE]>(InObject))
		{
			InJsonWriter->WriteObjectStart(MemberName);

			for (int32 I = 0; I < SIZE; ++I)
			{
				InJsonWriter->WriteValue((*EnumSizeToString)((E)I), (*EnumToString)((T)((*Member)[I])));
			}
			InJsonWriter->WriteObjectEnd();
		}	
	}

	template<typename T, typename E, int32 SIZE>
	static void WriteMemberFixedArrayPropertyToJson_Primitive_EnumSize(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UProperty* &Property, void* InObject, const FString &MemberName, FString(T::*ToString)(void) const, FString(*EnumSizeToString)(const E&))
	{
		if (T(*Member)[SIZE] = Property->ContainerPtrToValuePtr<T[SIZE]>(InObject))
		{
			InJsonWriter->WriteObjectStart(MemberName);

			for (int32 I = 0; I < SIZE; ++I)
			{
				InJsonWriter->WriteValue((*EnumSizeToString)((E)I), ((*Member)[I].*ToString)());
			}
			InJsonWriter->WriteObjectEnd();
		}
	}

	static bool WriteStructToJson_Internal_Helper(TCsWriteStructToJson_Internal Internal, UProperty* Property, TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, void* InStruct, UScriptStruct* const &InScriptStruct);
	static bool WriteObjectToJson_Internal_Helper(TCsWriteObjectToJson_Internal Internal, UProperty* Property, TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, void* InObject, UClass* const &InClass);

	static void WriteStructToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, void* InStruct, UScriptStruct* const &InScriptStruct, TCsWriteStructToJson_Internal Internal = nullptr);
	static void WriteStructToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, void* InStruct, UScriptStruct* const &InScriptStruct, const TArray<FCsCategoryMemberAssociation> &CategoryMemberAssociations, TCsWriteStructToJson_Internal Internal = nullptr);
	static void WriteObjectToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, void* InObject, UClass* const &InClass, const TArray<FCsCategoryMemberAssociation> &CategoryMemberAssociations, TCsWriteObjectToJson_Internal Internal = nullptr);

#pragma endregion Write

// Read
#pragma region

	template<typename T>
	static void WriteToAssetClassPropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, UAssetClassProperty* &AssetClassProperty, void* InObject, const FString &MemberName)
	{
		if (TAssetSubclassOf<T>* Member = AssetClassProperty->ContainerPtrToValuePtr<TAssetSubclassOf<T>>(InObject))
			*Member = TAssetSubclassOf<T>(JsonObject->GetStringField(MemberName));
	}

	template<typename T>
	static void WriteToAssetObjectPropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName)
	{
		if (TAssetPtr<T>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>>(InObject))
			*Member = TAssetPtr<T>(JsonObject->GetStringField(MemberName));
	}

	static void WriteToAssetObjectPropertyFromJson_AnimBlueprint(TSharedPtr<class FJsonObject> &JsonObject, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName);
	static void WriteToAssetObjectPropertyFromJson_Blueprint(TSharedPtr<class FJsonObject> &JsonObject, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName);

	template<typename T>
	static void WriteToArrayAssetObjectPropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName)
	{
		if (TArray<TAssetPtr<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<T>>>(InObject))
		{
			const TSharedPtr<FJsonObject>& Object = JsonObject->GetObjectField(MemberName);

			TArray<FString> Keys;

			Object->Values.GetKeys(Keys);

			const int32 ArrayCount  = Keys.Num();
			const int32 MemberCount	= Member->Num();
			const int32 Count		= FMath::Max(ArrayCount, MemberCount);


			for (int32 I = 0; I < Count; ++I)
			{
				if (I >= ArrayCount)
					break;

				if (I >= MemberCount)
					Member->AddDefaulted();

				const FString& Key			     = Keys[I];
				TSharedPtr<FJsonValue> JsonValue = *(Object->Values.Find(Key));
				FString Value					 = JsonValue->AsString();

				(*Member)[I] = TAssetPtr<T>(Value);
			}
		}
	}

	template<typename T, typename E, int32 SIZE>
	static void WriteToFixedArrayAssetObjectPropertyFromJson_EnumSize(TSharedPtr<class FJsonObject> &JsonObject, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName, FString(*ToString)(const E&))
	{
		if (TAssetPtr<T>(*Member)[SIZE] = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>[SIZE]>(InObject))
		{
			const TSharedPtr<FJsonObject>& Object = JsonObject->GetObjectField(MemberName);

			TArray<FString> Keys;

			Object->Values.GetKeys(Keys);

			const int32 ArrayCount = Keys.Num();
			const int32 Count	   = FMath::Min(ArrayCount, SIZE);

			for (int32 I = 0; I < Count; ++I)
			{
				const FString& Key		  = Keys[I];
				const FString ElementName = (*ToString)((E)I);

				check(Key == ElementName);

				TSharedPtr<FJsonValue> JsonValue = *(Object->Values.Find(Key));
				FString Value					 = JsonValue->AsString();
				
				(*Member)[I] = TAssetPtr<T>(Value);
			}
		}
	}

	template<typename T>
	static void WriteToMemberStructPropertyFromJson_Primitive(TSharedPtr<class FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString &MemberName, bool(T::*InitFromString)(const FString&))
	{
		if (T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject))
			((*Member).*InitFromString)(JsonObject->GetStringField(MemberName));
	}

	template<typename T>
	static void WriteToMemberArrayStructPropertyFromJson_Primitive(TSharedPtr<class FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName, bool(T::*InitFromString)(const FString&))
	{
		TArray<T>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<T>>(InObject);

		const TSharedPtr<FJsonObject>& Object = JsonObject->GetObjectField(MemberName);

		TArray<FString> Keys;

		Object->Values.GetKeys(Keys);

		const int32 ArrayCount  = Keys.Num();
		const int32 MemberCount = Member->Num();
		const int32 Count		= FMath::Max(ArrayCount, MemberCount);

		for (int32 I = 0; I < Count; ++I)
		{
			if (I >= ArrayCount)
				break;

			if (I >= MemberCount)
				Member->AddDefaulted();

			const FString& Key				 = Keys[I];
			TSharedPtr<FJsonValue> JsonValue = *(Object->Values.Find(Key));
			FString Value					 = JsonValue->AsString();

			((*Member)[I].*InitFromString)(Value);
		}
	}

	static void WriteToMemberStructPropertyFromJson_Transform(TSharedPtr<class FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString &MemberName);
	static void WriteToMemberArrayStructPropertyFromJson_Transform(TSharedPtr<class FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName);

	static void WriteToMemberArrayStructPropertyFromJson_Name(TSharedPtr<class FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName);

	static void WriteToMemberArrayStructPropertyFromJson_uint64(TSharedPtr<class FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName);

	template<typename T>
	static void WriteToMemberStructPropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString &MemberName, TCsReadStructFromJson_Internal Internal = nullptr)
	{
		T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject);

		TSharedPtr<FJsonObject> Object = JsonObject->GetObjectField(MemberName);

		ReadStructFromJson(Object, (void*)Member, StructProperty->Struct, Internal);
	}

	template<typename T>
	static void WriteToMemberArrayStructPropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName, TCsReadStructFromJson_Internal Internal = nullptr)
	{
		TArray<T>* Member					 = ArrayProperty->ContainerPtrToValuePtr<TArray<T>>(InObject);
		UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner);

		const TArray<TSharedPtr<FJsonValue>> JsonArray = JsonObject->GetArrayField(MemberName);

		const int32 ArrayCount	= JsonArray.Num();
		const int32 MemberCount = Member->Num();
		const int32 Count		= FMath::Max(ArrayCount, MemberCount);

		for (int32 I = 0; I < Count; ++I)
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
	static void WriteToMemberFixedArrayStructPropertyFromJson_EnumSize(TSharedPtr<class FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString &MemberName, FString(*ToString)(const E&), TCsReadStructFromJson_Internal Internal = nullptr)
	{
		T(*Member)[SIZE] = StructProperty->ContainerPtrToValuePtr<T[SIZE]>(InObject);

		const TSharedPtr<class FJsonObject> JObject = JsonObject->GetObjectField(MemberName);

		for (int32 I = 0; I < SIZE; ++I)
		{
			TSharedPtr<class FJsonObject> Object = JObject->GetObjectField((*ToString)((E)I));
			
			if (Object->Values.Num() > CS_EMPTY)
				ReadStructFromJson(Object, (void*)&((*Member)[I]), StructProperty->Struct, Internal);
		}
	}

	template<typename T>
	static void WriteToMemberBytePropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, UByteProperty* &ByteProperty, void* InObject, const FString &MemberName, T(*ToType)(const FString&))
	{
		if (TEnumAsByte<T>* Member = ByteProperty->ContainerPtrToValuePtr<TEnumAsByte<T>>(InObject))
			*Member = (*ToType)(*JsonObject->GetStringField(MemberName));
	}

	template<typename T>
	static void WriteToMemberArrayBytePropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName, T(*ToType)(const FString&))
	{
		if (TArray<TEnumAsByte<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TEnumAsByte<T>>>(InObject))
		{
			const TSharedPtr<FJsonObject> JObject = JsonObject->GetObjectField(MemberName);

			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const FString Value = JObject->GetStringField(FString::FromInt(I));
				(*Member)[I]		= (*ToType)(Value);
			}
		}
	}

	template<typename T, typename E, int32 SIZE>
	static void WriteToMemberFixedArrayBytePropertyFromJson_EnumSize(TSharedPtr<class FJsonObject> &JsonObject, UByteProperty* &ByteProperty, void* InObject, const FString &MemberName, T(*ToType)(const FString&), FString(*ToString)(const E&))
	{
		if (TEnumAsByte<T>(*Member)[SIZE] = ByteProperty->ContainerPtrToValuePtr<TEnumAsByte<T>[SIZE]>(InObject))
		{
			const TSharedPtr<FJsonObject> JObject = JsonObject->GetObjectField(MemberName);

			for (int32 I = 0; I < SIZE; ++I)
			{
				const FString Value = JObject->GetStringField((*ToString)((E)I));
				(*Member)[I]		= (*ToType)(Value);
			}
		}
	}

	template<typename E, int32 SIZE>
	static void WriteToMemberFixedArrayNamePropertyFromJson_EnumSize(TSharedPtr<class FJsonObject> &JsonObject, UNameProperty* &NameProperty, void* InObject, const FString &MemberName, FString(*ToString)(const E&))
	{
		if (FName(*Member)[SIZE] = NameProperty->ContainerPtrToValuePtr<FName[SIZE]>(InObject))
		{
			const TSharedPtr<FJsonObject> JObject = JsonObject->GetObjectField(MemberName);

			for (int32 I = 0; I < SIZE; ++I)
			{
				const FString Value = JObject->GetStringField((*ToString)((E)I));
				(*Member)[I]		= FName(*Value);
			}
		}
	}

	static bool ReadStructFromJson_Internal_Helper(TCsReadStructFromJson_Internal Internal, UProperty* Property, TSharedPtr<class FJsonObject> &JsonObject, void* InStruct, UScriptStruct* const &InScriptStruct);
	static bool ReadObjectFromJson_Internal_Helper(TCsReadObjectFromJson_Internal Internal, UProperty* Property, TSharedPtr<class FJsonObject> &JsonObject, void* InObject, UClass* const &InClass);

	static void ReadStructFromJson(TSharedPtr<class FJsonObject> &JsonObject, void* InStruct, UScriptStruct* const &InScriptStruct, TCsReadStructFromJson_Internal Internal = nullptr);
	static void ReadStructFromJson(TSharedPtr<class FJsonObject> &JsonParsed, void* InStruct, UScriptStruct* const &InScriptStruct, const TArray<FCsCategoryMemberAssociation> &CategoryMemberAssociations, TCsReadStructFromJson_Internal Internal = nullptr);
	static void ReadObjectFromJson(TSharedPtr<class FJsonObject> &JsonParsed, void* InObject, UClass* const &InClass, const TArray<FCsCategoryMemberAssociation> &CategoryMemberAssociations, TCsReadObjectFromJson_Internal Internal = nullptr);

#pragma endregion Read

#pragma endregion Json

// Loading
#pragma region

	// Asset References
#pragma region

	template<typename T>
	static FString GetAssetDescription(TAssetSubclassOf<T> &AssetSubclassOf)
	{
		const FStringAssetReference& AssetRef = AssetSubclassOf.ToStringReference();
		const FString AssetName				  = AssetRef.ToString();
		FString AssetDescription			  = ECsCachedString::Str::Empty;

		// (AssetName != TEXT(""))
		if (AssetName != ECsCachedString::Str::Empty)
		{
			AssetDescription = TEXT("Blueprint'") + AssetName + TEXT("'");
		}
		return AssetDescription;
	}

		// CsStringAssetReference
#pragma region

	template<typename T>
	static void GetAssetReferenceFromAssetObjectProperty(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = AssetObjectProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TAssetPtr<T>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>>(InObject))
		{
			const FStringAssetReference AssetRef = Member->ToStringReference();
			const FString AssetName				 = AssetRef.ToString();
			
			// (AssetName == TEXT(""))
			if (AssetName == ECsCachedString::Str::Empty)
				return;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();

			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
			Reference.Reference				   = AssetName;
			Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
			if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
			{
				UObject* Asset = Cast<UObject>(Member->LoadSynchronous());

				Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(ResourceSizeMode);
				Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}

	template<typename T>
	static void GetAssetReferenceFromAssetObjectProperty(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = AssetObjectProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TAssetPtr<T>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>>(InObject))
		{
			const FStringAssetReference AssetRef = Member->ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == ECsCachedString::Str::Empty)
				return;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();

			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
			Reference.Reference				   = AssetName;
			Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
			if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
			{
				UObject* Asset = Cast<UObject>(Member->LoadSynchronous());

				Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(ResourceSizeMode);
				Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}

	static void GetAssetReferenceFromAssetObjectProperty_AnimMontage(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferenceFromAssetObjectProperty_AnimMontage(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	static void GetAssetReferenceFromAssetObjectProperty_AnimSequence(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferenceFromAssetObjectProperty_AnimSequence(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	static void GetAssetReferenceFromAssetObjectProperty_AnimBlueprint(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferenceFromAssetObjectProperty_AnimBlueprint(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	static void GetAssetReferenceFromAssetObjectProperty_MaterialInstanceConstant(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferenceFromAssetObjectProperty_MaterialInstanceConstant(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	static void GetAssetReferenceFromAssetObjectProperty_Blueprint(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferenceFromAssetObjectProperty_Blueprint(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	template<typename T>
	static void GetAssetReferenceFromArrayAssetObjectProperty(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		if (TArray<TAssetPtr<T>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<T>>>(InObject))
		{
			const FString MemberName	 = ArrayAssetObjectProperty->GetName();
										// MemberName + TEXT("_LaodFlags")
			const FString FlagMemberName = MemberName + ECsLoadCachedString::Str::_LoadFlags;

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

						for (int32 I = 0; I < Count; ++I)
						{
							const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
							const FString AssetName				 = AssetRef.ToString();
							
							// (AssetName == TEXT(""))
							if (AssetName == ECsCachedString::Str::Empty)
								continue;

							if (CS_TEST_BLUEPRINT_BITFLAG((*MemberLoadFlags)[I], LoadFlags))
							{
								OutAssetReferences.AddDefaulted();

								const int32 Size = OutAssetReferences.Num();

								FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
								Reference.Reference				   = AssetName;
								Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
								if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
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
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
				return;

			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
				const FString AssetName				 = AssetRef.ToString();

				// (AssetName == TEXT(""))
				if (AssetName == ECsCachedString::Str::Empty)
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

	template<typename T>
	static void GetAssetReferenceFromArrayAssetObjectProperty(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		if (TArray<TAssetPtr<T>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<T>>>(InObject))
		{
			const FString MemberName	 = ArrayAssetObjectProperty->GetName();
										// MemberName + TEXT("_LoadFlags")
			const FString FlagMemberName = MemberName + ECsLoadCachedString::Str::_LoadFlags;

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

						for (int32 I = 0; I < Count; ++I)
						{
							const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
							const FString AssetName				 = AssetRef.ToString();

							// (AssetName == TEXT(""))
							if (AssetName == ECsCachedString::Str::Empty)
								continue;

							if (CS_TEST_BLUEPRINT_BITFLAG((*MemberLoadFlags)[I], LoadFlags))
							{
								OutAssetReferences.AddDefaulted();

								const int32 Size = OutAssetReferences.Num();

								FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
								Reference.Reference				   = AssetName;
								Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
								if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
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
			const FString MemberName = AssetObjectProperty->GetName();

			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
				return;

			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
				const FString AssetName				 = AssetRef.ToString();

				// (AssetName == TEXT(""))
				if (AssetName == ECsCachedString::Str::Empty)
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

	template<typename T, int32 SIZE>
	static void GetAssetReferenceFromFixedArrayAssetObjectProperty_EnumSize(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = AssetObjectProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TAssetPtr<T>(*Member)[SIZE] = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>[SIZE]>(InObject))
		{
			for (int32 I = 0; I < SIZE; ++I)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
				const FString AssetName				 = AssetRef.ToString();

				// (AssetName == TEXT(""))
				if (AssetName == ECsCachedString::Str::Empty)
					continue;

				OutAssetReferences.AddDefaulted();

				const int32 Size = OutAssetReferences.Num();

				FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
				Reference.Reference				   = AssetName;
				Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
				if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
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

	static void GetAssetReferenceFromArrayAssetObjectProperty_AnimMontage(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferenceFromArrayAssetObjectProperty_AnimMontage(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	static void GetAssetReferenceFromArrayAssetObjectProperty_AnimSequence(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferenceFromArrayAssetObjectProperty_AnimSequence(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	static void GetAssetReferenceFromArrayAssetObjectProperty_MaterialInstanceConstant(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferenceFromArrayAssetObjectProperty_MaterialInstanceConstant(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	template<int32 SIZE>
	static void GetAssetReferenceFromFixedArrayAssetObjectProperty_EnumSize_MaterialInstanceConstant(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = AssetObjectProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TAssetPtr<UMaterialInstanceConstant>(*Member)[SIZE] = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UMaterialInstanceConstant>[SIZE]>(InObject))
		{
			for (int32 I = 0; I < SIZE; ++I)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
				const FString AssetName				 = AssetRef.ToString();

				// (AssetName == TEXT(""))
				if (AssetName == ECsCachedString::Str::Empty)
					continue;

				OutAssetReferences.AddDefaulted();

				const int32 Size = OutAssetReferences.Num();

				FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
				Reference.Reference				   = AssetName;
				Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
				if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
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

	static void GetAssetReferenceFromArrayAssetObjectProperty_Blueprint(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferenceFromArrayAssetObjectProperty_Blueprint(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	template<int32 SIZE>
	static void GetAssetReferenceFromFixedArrayAssetObjectProperty_Blueprint_EnumSize(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = AssetObjectProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TAssetPtr<UBlueprint>(*Member)[SIZE] = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UBlueprint>[SIZE]>(InObject))
		{
			for (int32 I = 0; I < SIZE; ++I)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
				const FString AssetName				 = AssetRef.ToString();

				// (AssetName == TEXT(""))
				if (AssetName == ECsCachedString::Str::Empty)
					continue;

				OutAssetReferences.AddDefaulted();

				const int32 Size = OutAssetReferences.Num();
				// TODO: Fix / Investigate. 4.16.1. Built Game (Okay in Editor). TAssetPtr for UAnimBlueprint / UWidgetBlueprint does NOT have _C
				FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
				Reference.Reference				   = AssetName.EndsWith(ECsLoadCachedString::Str::_C) ? AssetName : AssetName + ECsLoadCachedString::Str::_C;
				Reference.Reference_Internal	   = FStringAssetReference(Reference.Reference);
#if WITH_EDITOR
				if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
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
	static void GetAssetReferenceFromFixedArrayAssetObjectProperty_Blueprint_EnumSize(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = AssetObjectProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TAssetPtr<UBlueprint>(*Member)[SIZE] = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UBlueprint>[SIZE]>(InObject))
		{
			for (int32 I = 0; I < SIZE; ++I)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
				const FString AssetName				 = AssetRef.ToString();

				// (AssetName == TEXT(""))
				if (AssetName == ECsCachedString::Str::Empty)
					continue;

				OutAssetReferences.AddDefaulted();

				const int32 Size = OutAssetReferences.Num();
				// TODO: Fix / Investigate. 4.16.1. Built Game (Okay in Editor). TAssetPtr for UWidgetBlueprint does NOT have _C
				FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
				Reference.Reference				   = AssetName.EndsWith(ECsLoadCachedString::Str::_C) ? AssetName : AssetName + ECsLoadCachedString::Str::_C;
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
	static void GetAssetReferencesFromFixedArrayStructProperty_EnumSize(UStructProperty* &StructProperty, void* InObject, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromStruct_Internal Internal = nullptr, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		if (T(*Member)[SIZE] = StructProperty->ContainerPtrToValuePtr<T[SIZE]>(InObject))
		{
			for (int32 I = 0; I < SIZE; ++I)
			{
				GetAssetReferencesFromStruct((void*)&((*Member)[I]), StructProperty->Struct, LoadFlags, OutAssetReferences, Internal, LoadCodes);
			}
		}
	}

	template<typename T>
	static void GetAssetReferenceFromAssetClassProperty(UAssetClassProperty* &AssetClassProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = AssetClassProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TAssetSubclassOf<T>* Member = AssetClassProperty->ContainerPtrToValuePtr<TAssetSubclassOf<T>>(InObject))
		{
			const FStringAssetReference AssetRef = Member->ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == ECsCachedString::Str::Empty)
				return;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();

			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
			Reference.Reference				   = AssetName;
			Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
			if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
			{
				UObject* Asset = Cast<UObject>(Member->LoadSynchronous());

				Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(ResourceSizeMode);
				Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}

	template<typename T>
	static void GetAssetReferenceFromAssetClassProperty(UAssetClassProperty* &AssetClassProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = AssetClassProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TAssetSubclassOf<T>* Member = AssetClassProperty->ContainerPtrToValuePtr<TAssetSubclassOf<T>>(InObject))
		{
			const FStringAssetReference AssetRef = Member->ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == ECsCachedString::Str::Empty)
				return;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();

			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
			Reference.Reference				   = AssetName;
			Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
			if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
			{
				UObject* Asset = Cast<UObject>(Member->LoadSynchronous());

				Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(ResourceSizeMode);
				Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}

	template<typename T>
	static void GetAssetReferenceFromArrayAssetClassProperty(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = ArrayAssetObjectProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TArray<TAssetSubclassOf<T>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetSubclassOf<T>>>(InObject))
		{
			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
				const FString AssetName				 = AssetRef.ToString();

				// (AssetName == TEXT(""))
				if (AssetName == ECsCachedString::Str::Empty)
					continue;

				OutAssetReferences.AddDefaulted();

				const int32 Size = OutAssetReferences.Num();

				FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
				Reference.Reference				   = AssetName;
				Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
				if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
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
	static void GetAssetReferenceFromArrayAssetClassProperty(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = ArrayAssetObjectProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TArray<TAssetSubclassOf<T>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetSubclassOf<T>>>(InObject))
		{
			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
				const FString AssetName				 = AssetRef.ToString();

				// (AssetName == TEXT(""))
				if (AssetName == ECsCachedString::Str::Empty)
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
	static void GetAssetReferencesFromStructProperty(UStructProperty* &StructProperty, void* InObject, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromStruct_Internal Internal = nullptr, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		if (T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject))
			GetAssetReferencesFromStruct((void*)Member, StructProperty->Struct, LoadFlags, OutAssetReferences, Internal, LoadCodes);
	}

	template<typename T>
	static void GetAssetReferencesFromArrayStructProperty(UArrayProperty* ArrayProperty, void* InObject, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromStruct_Internal Internal = nullptr, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		if (TArray<T>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<T>>(InObject))
		{
			UStructProperty* StructProperty = Cast<UStructProperty>(ArrayProperty->Inner);

			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				GetAssetReferencesFromStruct((void*)&((*Member)[I]), StructProperty->Struct, LoadFlags, OutAssetReferences, Internal, LoadCodes);
			}
		}
	}

#pragma endregion CsStringAssetReference

	static void GetAssetReferencesFromStruct(void* InStruct, UScriptStruct* const &InScriptStruct, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromStruct_Internal Internal = nullptr, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferencesFromObject(void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromObject_Internal Internal = nullptr, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

#pragma endregion Asset References

	// Load
#pragma region

	template<typename T>
	static void LoadTAssetPtr(const FString &MemberName, TAssetPtr<T> AssetPtr, T* &Internal, const FString &AssetType, const FString &AssetErrorMessageType)
	{
		const FString& AssetName = AssetPtr.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == ECsCachedString::Str::Empty)
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
		const FString& AssetName = AssetPtr->ToString();

		// (AssetName == TEXT(""))
		if (AssetName == ECsCachedString::Str::Empty)
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
		const FString& AssetName = AssetPtr.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == ECsCachedString::Str::Empty)
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

	static void LoadTAssetPtr_Blueprint(const FString &MemberName, TAssetPtr<class UBlueprint> AssetPtr, class UBlueprintGeneratedClass* &Internal);
	static void LoadTAssetPtr_Blueprint(const FString &MemberName, TAssetPtr<class UBlueprint>* AssetPtr, class UBlueprintGeneratedClass* &Internal);

	static void LoadTAssetPtr_AnimBlueprint(const FString &MemberName, TAssetPtr<class UAnimBlueprint> AssetPtr, class UAnimBlueprintGeneratedClass* &Internal);
	static void LoadTAssetPtr_AnimBlueprint(const FString &MemberName, TAssetPtr<class UAnimBlueprint>* AssetPtr, class UAnimBlueprintGeneratedClass* &Internal);

	template<typename T>
	static void LoadTAssetSubclassOf(const FString &MemberName, TAssetSubclassOf<T> &AssetSubclassOf, T* &Internal, const FString &AssetErrorMessageType)
	{
		const FString& AssetName = AssetSubclassOf.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == ECsCachedString::Str::Empty)
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
		const FString& AssetName = AssetSubclassOf->ToString();

		// (AssetName == TEXT(""))
		if (AssetName == ECsCachedString::Str::Empty)
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
		const FString& AssetName = AssetSubclassOf.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == ECsCachedString::Str::Empty)
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

		const FString& AssetName = AssetSubclassOf.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == ECsCachedString::Str::Empty)
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

		for (int32 I = 0; I < Count; ++I)
		{
			Array.Add(ArrayAssetPtr[I].Get());
		}
	}

	template<typename T>
	static void SetTArrayFromTArrayTAssetPtr(TArray<T*> &Array, TArray<TAssetPtr<T>>* &ArrayAssetPtr)
	{
		Array.Reset();

		const int32 Count = ArrayAssetPtr->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Array.Add((*ArrayAssetPtr)[I].Get());
		}
	}

	template<typename T>
	static void SetTArrayFromTArrayTAssetPtr(TArray<TWeakObjectPtr<T>> &Array, TArray<TAssetPtr<T>> &ArrayAssetPtr)
	{
		Array.Reset();

		const int32 Count = ArrayAssetPtr.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Array.Add(ArrayAssetPtr[I].Get());
		}
	}

	template<typename T>
	static void SetTArrayFromTArrayTAssetPtr(TArray<TWeakObjectPtr<T>> &Array, TArray<TAssetPtr<T>>* &ArrayAssetPtr)
	{
		Array.Reset();

		const int32 Count = ArrayAssetPtr->Num();

		for (int32 I = 0; I < Count; ++I)
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

			for (int32 I = 0; I < Count; ++I)
			{
				TAssetPtr<T>& AssetPtr				  = ArrayAssetPtr[I];
				const FStringAssetReference& AssetRef = AssetPtr.ToStringReference();
				const FString& AssetName			  = AssetRef.ToString();

				// (AssetName != TEXT(""))
				if (AssetName != ECsCachedString::Str::Empty)
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
			NullAndEmptyTArray<T>(ArrayInternal);

			const int32 Count = ArrayAssetPtr->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				TAssetPtr<T>& AssetPtr				  = (*ArrayAssetPtr)[I];
				const FStringAssetReference& AssetRef = AssetPtr.ToStringReference();
				const FString& AssetName			  = AssetRef.ToString();

				// (AssetName != TEXT(""))
				if (AssetName != ECsCachedString::Str::Empty)
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

			for (int32 I = 0; I < Count; ++I)
			{
				TAssetPtr<T>& AssetPtr				  = ArrayAssetPtr[I];
				const FStringAssetReference& AssetRef = AssetPtr.ToStringReference();
				const FString& AssetName			  = AssetRef.ToString();

				// (AssetName != TEXT(""))
				if (AssetName != ECsCachedString::Str::Empty)
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

	static void LoadTArrayTAssetPtr_Blueprint(const FString &MemberName, TArray<TAssetPtr<class UBlueprint>> &ArrayAssetPtr, TArray<class UBlueprintGeneratedClass*> &ArrayInternal);
	static void LoadTArrayTAssetPtr_Blueprint(const FString &MemberName, TArray<TAssetPtr<class UBlueprint>>* &ArrayAssetPtr, TArray<class UBlueprintGeneratedClass*> &ArrayInternal);

	template<typename T>
	static void SetTArrayFromTArrayTAssetSubclassOf(TArray<T*> &Array, TArray<TAssetSubclassOf<T>> &ArrayAssetSubclassOf)
	{
		Array.Reset();

		const int32 Count = ArrayAssetSubclassOf.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Array.Add(ArrayAssetSubclassOf[I].Get()->template GetDefaultObject<T>());
		}
	}

	template<typename T>
	static void SetTArrayFromTArrayTAssetSubclassOf(TArray<T*> &Array, TArray<TAssetSubclassOf<T>>* &ArrayAssetSubclassOf)
	{
		Array.Reset();

		const int32 Count = ArrayAssetSubclassOf->Num();

		for (int32 I = 0; I < Count; ++I)
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

			for (int32 I = 0; I < Count; ++I)
			{
				TAssetSubclassOf<T>& AssetSubclassOf  = (*ArrayAssetSubclassOf)[I];
				const FStringAssetReference& AssetRef = AssetSubclassOf.ToStringReference();
				const FString& AssetName			  = AssetRef.ToString();

				// (AssetName != TEXT(""))
				if (AssetName != ECsCachedString::Str::Empty)
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

	static void LoadFCsAnimSequence(const FString &MemberName, struct FCsAnimSequence* Anim, const ECsLoadFlags &LoadFlags);
	static void LoadFCsAnimSequence(const FString &MemberName, struct FCsAnimSequence* Anim);
	static void LoadFCsFpsAnimSequence(const FString &MemberName, struct FCsFpsAnimSequence* Anim, const ECsLoadFlags &LoadFlags);
	static void LoadFCsFpsAnimSequence(const FString &MemberName, struct FCsFpsAnimSequence* Anim, const TCsViewType &ViewType);

	static void LoadFCsAnimMontage(const FString &MemberName, struct FCsAnimMontage* Anim, const ECsLoadFlags &LoadFlags);
	static void LoadFCsAnimMontage(const FString &MemberName, struct FCsAnimMontage* Anim);
	static void LoadFCsFpsAnimMontage(const FString &MemberName, struct FCsFpsAnimMontage* Anim, const ECsLoadFlags &LoadFlags);
	static void LoadFCsFpsAnimMontage(const FString &MemberName, struct FCsFpsAnimMontage* Anim, const TCsViewType &ViewType);

	static void LoadFCsBlendSpace1D(const FString &MemberName, struct FCsBlendSpace1D *Blend, const ECsLoadFlags &LoadFlags);
	static void LoadFCsBlendSpace1D(const FString &MemberName, struct FCsBlendSpace1D* Blend);
	static void LoadFCsFpsBlendSpace1D(const FString &MemberName, struct FCsFpsBlendSpace1D* Blend, const ECsLoadFlags &LoadFlags);
	static void LoadFCsFpsBlendSpace1D(const FString &MemberName, struct FCsFpsBlendSpace1D* Blend, const TCsViewType &ViewType);

	static void LoadFCsBlendSpace(const FString &MemberName, struct FCsBlendSpace* Blend, const ECsLoadFlags &LoadFlags);
	static void LoadFCsBlendSpace(const FString &MemberName, struct FCsBlendSpace* Blend);
	static void LoadFCsFpsBlendSpace(const FString &MemberName, struct FCsFpsBlendSpace* Blend, const ECsLoadFlags &LoadFlags);
	static void LoadFCsFpsBlendSpace(const FString &MemberName, struct FCsFpsBlendSpace* Blend, const TCsViewType &ViewType);

	static bool CanLoad(void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags, const int32 &LoadCodes);
	static bool CanLoad(void* InObject, UClass* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags, const int32 &LoadCodes);

	template<typename T>
	static void LoadAssetClassProperty(UAssetClassProperty* &AssetClassProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString &MemberName, const FString &AssetType, const ECsLoadFlags &LoadFlags)
	{
		if (TAssetSubclassOf<T>* Member = AssetClassProperty->ContainerPtrToValuePtr<TAssetSubclassOf<T>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCachedString::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (T** Internal = InternalProperty->ContainerPtrToValuePtr<T*>(InObject))
					LoadTAssetSubclassOf<T>(ObjectName + ECsCachedString::Str::Dot + MemberName, Member, *Internal, AssetType);
										//  ObjectName + TEXT(".") + MemberName
			}
		}
	}

	template<typename T>
	static void LoadAssetClassProperty(UAssetClassProperty* &AssetClassProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const FString &AssetType, const ECsLoadFlags &LoadFlags)
	{
		if (TAssetSubclassOf<T>* Member = AssetClassProperty->ContainerPtrToValuePtr<TAssetSubclassOf<T>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCachedString::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (T** Internal = InternalProperty->ContainerPtrToValuePtr<T*>(InObject))
					LoadTAssetSubclassOf<T>(ObjectName + ECsCachedString::Str::Dot + MemberName, Member, *Internal, AssetType);
										//  ObjectName + TEXT(".") + MemberName
			}
		}
	}

	template<typename T>
	static void LoadArrayAssetClassProperty(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString &MemberName, const FString &AssetErrorMessageType, const ECsLoadFlags &LoadFlags)
	{
		if (TArray<TAssetSubclassOf<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TAssetSubclassOf<T>>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCachedString::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (TArray<T*>* Internal = InternalProperty->ContainerPtrToValuePtr<TArray<T*>>(InObject))
					LoadTArrayTAssetSubclassOf<T>(ObjectName + ECsCachedString::Str::Dot + MemberName, Member, *Internal, AssetErrorMessageType);
												//ObjectName + TEXT(".") + MemberName
			}
		}
	}

	template<typename T>
	static void LoadArrayAssetClassProperty(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const FString &AssetErrorMessageType, const ECsLoadFlags &LoadFlags)
	{
		if (TArray<TAssetSubclassOf<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TAssetSubclassOf<T>>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCachedString::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (TArray<T*>* Internal = InternalProperty->ContainerPtrToValuePtr<TArray<T*>>(InObject))
					LoadTArrayTAssetSubclassOf<T>(ObjectName + ECsCachedString::Str::Dot + MemberName, Member, *Internal, AssetErrorMessageType);
												//ObjectName + TEXT(".") + MemberName
			}
		}
	}

	template<typename T>
	static void LoadAssetObjectProperty(UAssetObjectProperty* &AssetObjectProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString &MemberName, const FString &AssetType, const FString &AssetErrorMessageType, const ECsLoadFlags &LoadFlags)
	{
		if (TAssetPtr<T>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCachedString::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (T** Internal = InternalProperty->ContainerPtrToValuePtr<T*>(InObject))
					LoadTAssetPtr<T>(ObjectName + ECsCachedString::Str::Dot + MemberName, Member, *Internal, AssetType, AssetErrorMessageType);
								//   ObjectName + TEXT(".") + MemberName
			}
		}
	}

	template<typename T>
	static void LoadAssetObjectProperty(UAssetObjectProperty* &AssetObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const FString &AssetType, const FString &AssetErrorMessageType, const ECsLoadFlags &LoadFlags)
	{
		if (TAssetPtr<T>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCachedString::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (T** Internal = InternalProperty->ContainerPtrToValuePtr<T*>(InObject))
					LoadTAssetPtr<T>(ObjectName + ECsCachedString::Str::Dot + MemberName, Member, *Internal, AssetType, AssetErrorMessageType);
								//   ObjectName + TEXT(".") + MemberName
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
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCachedString::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (TArray<T*>* Internal = InternalProperty->ContainerPtrToValuePtr<TArray<T*>>(InObject))
					LoadTArrayTAssetPtr<T>(ObjectName + ECsCachedString::Str::Dot + MemberName, Member, *Internal, AssetType, AssetErrorMessageType);
										// ObjectName + TEXT(".") + MemberName
			}
		}
	}

	template<typename T>
	static void LoadArrayAssetObjectProperty(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const FString &AssetType, const FString &AssetErrorMessageType, const ECsLoadFlags &LoadFlags)
	{
		if (TArray<TAssetPtr<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<T>>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCachedString::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (TArray<T*>* Internal = InternalProperty->ContainerPtrToValuePtr<TArray<T*>>(InObject))
					LoadTArrayTAssetPtr<T>(ObjectName + ECsCachedString::Str::Dot + MemberName, Member, *Internal, AssetType, AssetErrorMessageType);
										// ObjectName + TEXT(".") + MemberName
			}
		}
	}

	template<typename T, typename E, int32 SIZE>
	static void LoadFixedArrayAssetObjectProperty_EnumSize(UAssetObjectProperty* &AssetObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const FString &AssetType, const FString &AssetErrorMessageType, const ECsLoadFlags &LoadFlags, FString(*ToString)(const E&))
	{
		if (TAssetPtr<T>(*Member)[SIZE] = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<T>[SIZE]>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCachedString::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (T*(*Internal)[SIZE] = InternalProperty->ContainerPtrToValuePtr<T*[SIZE]>(InObject))
				{
					for (int32 I = 0; I < SIZE; ++I)
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
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCachedString::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (UBlueprintGeneratedClass*(*Internal)[SIZE] = InternalProperty->ContainerPtrToValuePtr<UBlueprintGeneratedClass*[SIZE]>(InObject))
				{
					for (int32 I = 0; I < SIZE; ++I)
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
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCachedString::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (UBlueprintGeneratedClass*(*Internal)[SIZE] = InternalProperty->ContainerPtrToValuePtr<UBlueprintGeneratedClass*[SIZE]>(InObject))
				{
					for (int32 I = 0; I < SIZE; ++I)
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
	static void LoadMemberStructProperty(UStructProperty* &StructProperty, void* InObject, const FString &MemberName, const ECsLoadFlags &LoadFlags, TCsLoadStructWithTAssetPtrs_Internal Internal = nullptr)
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

			for (int32 I = 0; I < Count; ++I)
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
			for (int32 I = 0; I < SIZE; ++I)
			{
				const FString Index		  = (*ToString)((E)I);
				const FString ElementName = MemberName + TEXT("[") + Index + TEXT("]");
				LoadStructWithTAssetPtrs(ElementName, (void*)&((*Member)[I]), StructProperty->Struct, LoadFlags, Internal);
			}
		}
	}

	static void LoadStructWithTAssetPtrs(const FString &ObjectName, void* InStruct, UScriptStruct* const &InScriptStruct, const ECsLoadFlags &LoadFlags, TCsLoadStructWithTAssetPtrs_Internal Internal = nullptr);
	static void LoadObjectWithTAssetPtrs(const FString &ObjectName, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TCsLoadObjectWithTAssetPtrs_Internal Internal = nullptr);

	template<typename T, typename U, typename S>
	static void SetTArrayInternalMemberFromLoadedAssets(void* InObject, UClass* const &InClass, const FString &StructMemberName, UScriptStruct* const &InScriptStruct, const FString &MemberName, const TArray<UObject*> &LoadedAssets)
	{
		if (UStructProperty* StructProperty = FindField<UStructProperty>(InClass, *StructMemberName))
		{
			// Struct
			if (T* Struct = StructProperty->ContainerPtrToValuePtr<T>(InObject))
			{
										//   MemberName = TEXT("_Internal")
				const FString InternalName = MemberName + ECsLoadCachedString::Str::_Internal;

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

					for (int32 I = 0; I < AssetPtrCount; ++I)
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

			for (int32 I = 0; I < Count; ++I)
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

			for (int32 I = 0; I < Count; ++I)
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

			for (int32 I = 0; I < Count; ++I)
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

			for (int32 I = 0; I < Count; ++I)
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

		for (int32 I = 0; I < Count; ++I)
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

			for (int32 I = 0; I < Count; ++I)
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

			for (int32 I = 0; I < Count; ++I)
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

			for (int32 I = 0; I < Count; ++I)
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

			for (int32 I = 0; I < Count; ++I)
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
	static void GetCategoryMemberAssociations(void* InStruct, UScriptStruct* const &InScriptStruct, TArray<FCsCategoryMemberAssociation> &OutCategoryMemberAssociations);
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

	static void* GetStructMemberEX(UProperty* Property, void* InStruct, UScriptStruct* const &InScriptStruct, const FString &MemberName);

	template<typename T>
	static T* GetStructMember(void* InStruct, UScriptStruct* const &InScriptStruct, const FString &MemberName, TCsGetStructMember_Internal Internal = nullptr)
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
				if (void* Ptr = GetStructMemberEX(Property, InStruct, InScriptStruct, MemberName))
					return (T*)Ptr;

				if (Internal)
				{
					if (void* Ptr = (*Internal)(Property, InStruct, InScriptStruct, MemberName))
						return (T*)Ptr;
				}
				return nullptr;
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
		return nullptr;
	}

	static UScriptStruct* GetScriptStructMember(void* InStruct, UScriptStruct* const &InScriptStruct, const FString &MemberName, TCsGetScriptStructMember_Internal Internal = nullptr);

	template<typename T>
	static T* GetObjectMember(void* InObject, UClass* const &InClass, const FString &MemberName, TCsGetObjectMember_Internal Internal = nullptr)
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
				return nullptr;
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
		return nullptr;
	}

	static uint16 GetObjectMemberIndex(UClass* const &InClass, const FString &MemberName);

	static void GetObjectMembers(void* InObject, UClass* const &InClass, const TArray<FString>* MemberNames, TArray<void*> &OutMemberValues);

#pragma endregion Get

#pragma endregion Members

};