// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"

#include "Json.h"
#include "JsonObjectConverter.h"
// Types
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_Load.h"
#include "Types/CsTypes_View.h"
#include "Library/Load/CsTypes_Library_Load.h"
// Library
#include "Library/CsLibrary_Math.h"

#include "CsLibrary_Load.generated.h"

UCLASS()
class CSCORE_API UCsLibrary_Load : public UObject
{
	GENERATED_UCLASS_BODY()

// Enum to String Conversion
#pragma region

#pragma endregion Enum to String Conversion

// Enum to Enum Conversion
#pragma region

	static ECsLoadFlags ViewTypeToLoadFlags(const ECsViewType& ViewType, const bool& IsLow = false);

#pragma endregion Enum to Enum Conversion

// Base Structure
#pragma region

	static FString ToString_FInt32Interval(const FInt32Interval &Interval);
	static bool InitFromString_FInt32Interval(const FString& InSourceString, FInt32Interval &OutInterval);

	static FString ToString_FFloatInterval(const FFloatInterval &Interval);
	static bool InitFromString_FFloatInterval(const FString& InSourceString, FFloatInterval &OutInterval);

#pragma endregion Base Structure

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

	static void JsonWriter(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, const FString& MemberName, const FName &Member);
	static void JsonWriter(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, const FString& MemberName, TArray<FName> &Member, const FString &ElementName);
	static void JsonWriter_ArrayElement(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, const FString& MemberName, const FName &Member);

	template<typename T>
	static void WriteTSoftObjectPtrToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, const FString& MemberName, TSoftObjectPtr<T> &Member)
	{
		if (Member.IsValid() && Member.Get())
		{
			const FString AssetName	= Member.ToString();

			// (AssetName != TEXT(""))
			if (AssetName != NCsCached::Str::Empty)
			{
				InJsonWriter->WriteValue(MemberName, AssetName);
			}
			else
			{
												//   TEXT("")
				InJsonWriter->WriteValue(MemberName, NCsCached::Str::Empty);
			}
		}
		else
		{
											//   TEXT("")
			InJsonWriter->WriteValue(MemberName, NCsCached::Str::Empty);
		}
	}

	static void WriteTSoftObjectPtrToJson_AnimBlueprint(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, const FString& MemberName, TSoftObjectPtr<class UAnimBlueprint> &Member);
	static void WriteTSoftObjectPtrToJson_Blueprint(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, const FString& MemberName, TSoftObjectPtr<class UBlueprint> &Member);

	template<typename T>
	static void WriteTArrayTSoftObjectPtrToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, const FString& MemberName, TArray<TSoftObjectPtr<T>> &Member)
	{
		InJsonWriter->WriteObjectStart(MemberName);
		
		const int32 Count = Member.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			WriteTSoftObjectPtrToJson(InJsonWriter, FString::FromInt(I), Member[I]);
		}
		InJsonWriter->WriteObjectEnd();
	}

	template<typename T>
	static void WriteTSoftClassPtrToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, const FString& MemberName, TSoftClassPtr<T> AssetSubclassOf)
	{
		if (AssetSubclassOf.IsValid() && AssetSubclassOf.Get())
		{
			const FString AssetName = AssetSubclassOf.ToString();

			// (AssetName != TEXT(""))
			if (AssetName != NCsCached::Str::Empty)
			{
				InJsonWriter->WriteValue(MemberName, AssetName);
			}
			else
			{
												//   TEXT("")
				InJsonWriter->WriteValue(MemberName, NCsCached::Str::Empty);
			}
		}
		else
		{
											//   TEXT("")
			InJsonWriter->WriteValue(MemberName, NCsCached::Str::Empty);
		}
	}

	template<typename T>
	static void WriteSoftClassPropertyToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, USoftClassProperty* &SoftClassProperty, void* InObject, const FString& MemberName)
	{
		if (TSoftClassPtr<T>* Member = SoftClassProperty->ContainerPtrToValuePtr<TSoftClassPtr<T>>(InObject))
			WriteTSoftClassPtrToJson<T>(InJsonWriter, MemberName, *Member);
	}

	template<typename T>
	static void WriteSoftObjectPropertyToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, USoftObjectProperty* &SoftObjectProperty, void* InObject, const FString& MemberName)
	{
		if (TSoftObjectPtr<T>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<T>>(InObject))
			WriteTSoftObjectPtrToJson<T>(InJsonWriter, MemberName, *Member);
	}

	static void WriteSoftObjectPropertyToJson_AnimBlueprint(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, USoftObjectProperty* &SoftObjectProperty, void* InObject, const FString& MemberName);
	static void WriteSoftObjectPropertyToJson_Blueprint(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, USoftObjectProperty* &SoftObjectProperty, void* InObject, const FString& MemberName);

	template<typename T>
	static void WriteArraySoftObjectPropertyToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString& MemberName)
	{
		if (TArray<TSoftObjectPtr<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<T>>>(InObject))
			WriteTArrayTSoftObjectPtrToJson<T>(InJsonWriter, MemberName, *Member);
	}

	template<typename T, typename E, int32 SIZE>
	static void WriteFixedArraySoftObjectPropertyToJson_EnumSize(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, USoftObjectProperty* &SoftObjectProperty, void* InObject, const FString& MemberName, const FString&(*ToString)(const E&))
	{
		if (TSoftObjectPtr<T>(*Member)[SIZE] = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<T>[SIZE]>(InObject))
		{
			InJsonWriter->WriteObjectStart(MemberName);

			for (int32 I = 0; I < SIZE; ++I)
			{
				const FString ElementName = (*ToString)((E)I);
				WriteTSoftObjectPtrToJson<T>(InJsonWriter, ElementName, (*Member)[I]);
			}
			InJsonWriter->WriteObjectEnd();
		}
	}

	template<typename T>
	static void WriteMemberStructPropertyToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString& MemberName, const bool &UseMemberName = true, TCsWriteStructToJson_Internal Internal = nullptr)
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
			InJsonWriter->WriteValue(NCsCached::Str::Index, MemberName);
		}
		WriteStructToJson(InJsonWriter, (void*)Member, StructProperty->Struct, Internal);
		InJsonWriter->WriteObjectEnd();
	}

	static void WriteMemberStructPropertyToJson_FCsData_ShortCode(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString& MemberName);

	template<typename T>
	static void WriteMemberEnumStructPropertyToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString& MemberName)
	{
		T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject);
		InJsonWriter->WriteValue(MemberName, Member->Name);
	}

	template<typename T>
	static void WriteMemberArrayStructPropertyToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString& MemberName, TCsWriteStructToJson_Internal Internal = nullptr)
	{
		TArray<T>* Member					 = ArrayProperty->ContainerPtrToValuePtr<TArray<T>>(InObject);
		UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner);
		
		InJsonWriter->WriteArrayStart(MemberName);

		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			InJsonWriter->WriteObjectStart();
									//   TEXT("Index")
				InJsonWriter->WriteValue(NCsCached::Str::Index, FString::FromInt(I));
				WriteStructToJson(InJsonWriter, (void*)&((*Member)[I]), InnerStructProperty->Struct, Internal);
			InJsonWriter->WriteObjectEnd();
		}
		InJsonWriter->WriteArrayEnd();
	}

	template<typename T, typename E, uint8 SIZE>
	static void WriteMemberFixedArrayStructPropertyToJson_EnumSize(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString& MemberName, const FString&(*ToString)(const E&), TCsWriteStructToJson_Internal Internal = nullptr)
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

	template<typename T, typename EnumType, typename EnumMap, uint8 SIZE>
	static void WriteMemberFixedArrayStructPropertyToJson_EnumSize(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString& MemberName, TCsWriteStructToJson_Internal Internal = nullptr)
	{
		T(*Member)[SIZE] = StructProperty->ContainerPtrToValuePtr<T[SIZE]>(InObject);

		InJsonWriter->WriteObjectStart(MemberName);

		for (int32 I = 0; I < SIZE; ++I)
		{
			InJsonWriter->WriteObjectStart(EnumMap::Get().ToString(I));
			WriteStructToJson(InJsonWriter, (void*)&((*Member)[I]), StructProperty->Struct, Internal);
			InJsonWriter->WriteObjectEnd();
		}
		InJsonWriter->WriteObjectEnd();
	}

	template<typename T>
	static void WriteMemberStructPropertyToJson_Primitive(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString& MemberName, FString(T::*ToString)() const)
	{
		if (T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject))
			InJsonWriter->WriteValue(MemberName, ((*Member).*ToString)());
	}

	template<typename T>
	static void WriteMemberArrayStructPropertyToJson_Primitive(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString& MemberName, FString(T::*ToString)() const)
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

	template<typename T>
	static void WriteMemberStructPropertyToJson_BaseStructure(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString& MemberName, FString(*ToString)(const T&))
	{
		if (T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject))
			InJsonWriter->WriteValue(MemberName, (*ToString)(*Member));
	}

	static void WriteMemberIntegralArrayPropertyToJson_uint64(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString& MemberName);

	static void WriteMemberStructPropertyToJson_Transform(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString& MemberName);
	static void WriteMemberArrayStructPropertyToJson_Transform(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString& MemberName);

	template<typename EnumType, typename EnumMap>
	static void WriteMemberEnumPropertyToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UEnumProperty* &EnumProperty, void* InObject, const FString& MemberName)
	{
		if (EnumType* Member = EnumProperty->ContainerPtrToValuePtr<EnumType>(InObject))
			InJsonWriter->WriteValue(MemberName, EnumMap::Get().ToString(*Member));
	}

	template<typename EnumType, typename EnumMap>
	static void WriteMemberEnumAsBytePropertyToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UByteProperty* &ByteProperty, void* InObject, const FString& MemberName)
	{
		if (TEnumAsByte<EnumType>* Member = ByteProperty->ContainerPtrToValuePtr<TEnumAsByte<EnumType>>(InObject))
			InJsonWriter->WriteValue(MemberName, EnumMap::Get().ToString(*Member));
	}

	template<typename EnumType>
	static void WriteMemberBytePropertyToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UByteProperty* &ByteProperty, void* InObject, const FString& MemberName, const FString& (*EnumToString)(const EnumType&))
	{
		if (EnumType* Member = ByteProperty->ContainerPtrToValuePtr<T>(InObject))
			InJsonWriter->WriteValue(MemberName, (*EnumToString)(*Member));
	}

	template<typename EnumType, typename EnumMap>
	static void WriteMemberBytePropertyToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UByteProperty* &ByteProperty, void* InObject, const FString& MemberName)
	{
		if (EnumType* Member = ByteProperty->ContainerPtrToValuePtr<T>(InObject))
			InJsonWriter->WriteValue(MemberName, EnumMap::Get().ToString(*Member));
	}

	template<typename T>
	static void WriteMemberArrayBytePropertyToJson(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString& MemberName, FString(*EnumToString)(const T&))
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
	static void WriteMemberFixedArrayBytePropertyToJson_EnumSize(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UByteProperty* &ByteProperty, void* InObject, const FString& MemberName, FString(*EnumToString)(const T&), FString(*EnumSizeToString)(const E&))
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
	static void WriteMemberFixedArrayPropertyToJson_Primitive_EnumSize(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UProperty* &Property, void* InObject, const FString& MemberName, FString(T::*ToString)(void) const, FString(*EnumSizeToString)(const E&))
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

	template<typename KeyType, typename ValueType>
	static void WriteMemberMapStructPropertyToJson_EnumStructKey_StructValue(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UMapProperty* &MapProperty, void* InObject, const FString& MemberName, TCsWriteStructToJson_Internal Internal = nullptr)
	{
		TMap<KeyType, ValueType>* Member = MapProperty->ContainerPtrToValuePtr<TMap<KeyType, ValueType>>(InObject);

		UStructProperty* StructProperty = Cast<UStructProperty>(MapProperty->ValueProp);

		InJsonWriter->WriteObjectStart(MemberName);

		TArray<KeyType> Keys;
		Member->GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			InJsonWriter->WriteObjectStart(Key.Name);
				WriteStructToJson(InJsonWriter, (void*)&((*Member)[Key]), StructProperty->Struct, Internal);
			InJsonWriter->WriteObjectEnd();
		}
		InJsonWriter->WriteObjectEnd();
	}

	template<typename KeyType, typename ValueType>
	static void WriteMemberMapStructPropertyToJson_EnumStructKey_NumericValue(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UMapProperty* &MapProperty, void* InObject, const FString& MemberName, TCsWriteStructToJson_Internal Internal = nullptr)
	{
		TMap<KeyType, ValueType>* Member = MapProperty->ContainerPtrToValuePtr<TMap<KeyType, ValueType>>(InObject);

		InJsonWriter->WriteObjectStart(MemberName);

		TArray<KeyType> Keys;
		Member->GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			InJsonWriter->WriteValue(Key.Name, (*Member)[Key]);
		}
		InJsonWriter->WriteObjectEnd();
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
	static void WriteToSoftClassPropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, USoftClassProperty* &SoftClassProperty, void* InObject, const FString& MemberName)
	{
		if (TSoftClassPtr<T>* Member = SoftClassProperty->ContainerPtrToValuePtr<TSoftClassPtr<T>>(InObject))
			*Member = TSoftClassPtr<T>(JsonObject->GetStringField(MemberName));
	}

	template<typename T>
	static void WriteToSoftObjectPropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, USoftObjectProperty* &SoftObjectProperty, void* InObject, const FString& MemberName)
	{
		if (TSoftObjectPtr<T>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<T>>(InObject))
			*Member = TSoftObjectPtr<T>(JsonObject->GetStringField(MemberName));
	}

	static void WriteToSoftObjectPropertyFromJson_AnimBlueprint(TSharedPtr<class FJsonObject> &JsonObject, USoftObjectProperty* &SoftObjectProperty, void* InObject, const FString& MemberName);
	static void WriteToSoftObjectPropertyFromJson_Blueprint(TSharedPtr<class FJsonObject> &JsonObject, USoftObjectProperty* &SoftObjectProperty, void* InObject, const FString& MemberName);

	template<typename T>
	static void WriteToArraySoftObjectPropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString& MemberName)
	{
		if (TArray<TSoftObjectPtr<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<T>>>(InObject))
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

				(*Member)[I] = TSoftObjectPtr<T>(Value);
			}
		}
	}

	template<typename T, typename E, int32 SIZE>
	static void WriteToFixedArraySoftObjectPropertyFromJson_EnumSize(TSharedPtr<class FJsonObject> &JsonObject, USoftObjectProperty* &SoftObjectProperty, void* InObject, const FString& MemberName, const FString&(*ToString)(const E&))
	{
		if (TSoftObjectPtr<T>(*Member)[SIZE] = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<T>[SIZE]>(InObject))
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
				
				(*Member)[I] = TSoftObjectPtr<T>(Value);
			}
		}
	}

	template<typename T>
	static void WriteToMemberStructPropertyFromJson_Primitive(TSharedPtr<class FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString& MemberName, bool(T::*InitFromString)(const FString&))
	{
		if (T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject))
			((*Member).*InitFromString)(JsonObject->GetStringField(MemberName));
	}

	template<typename T>
	static void WriteToMemberArrayStructPropertyFromJson_Primitive(TSharedPtr<class FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString& MemberName, bool(T::*InitFromString)(const FString&))
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

	template<typename T>
	static void WriteToMemberStructPropertyFromJson_BaseStructure(TSharedPtr<class FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString& MemberName, bool(*InitFromString)(const FString&, T&))
	{
		if (T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject))
			(*InitFromString)(JsonObject->GetStringField(MemberName), *Member);
	}

	template<typename T>
	static void WriteToMemberArrayStructPropertyFromJson_BaseStructure(TSharedPtr<class FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString& MemberName, bool(*InitFromString)(const FString&, T&))
	{
		TArray<T>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<T>>(InObject);

		const TSharedPtr<FJsonObject>& Object = JsonObject->GetObjectField(MemberName);

		TArray<FString> Keys;

		Object->Values.GetKeys(Keys);

		const int32 ArrayCount	= Keys.Num();
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

			(*InitFromString)(Value, (*Member)[I]);
		}
	}

	static void WriteToMemberStructPropertyFromJson_Transform(TSharedPtr<class FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString& MemberName);
	static void WriteToMemberArrayStructPropertyFromJson_Transform(TSharedPtr<class FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString& MemberName);

	static void WriteToMemberArrayStructPropertyFromJson_Name(TSharedPtr<class FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString& MemberName);

	static void WriteToMemberArrayStructPropertyFromJson_uint64(TSharedPtr<class FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString& MemberName);

	template<typename T>
	static void WriteToMemberStructPropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString& MemberName, TCsReadStructFromJson_Internal Internal = nullptr)
	{
		T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject);

		TSharedPtr<FJsonObject> Object = JsonObject->GetObjectField(MemberName);

		ReadStructFromJson(Object, (void*)Member, StructProperty->Struct, Internal);
	}

	static void WriteToMemberStructPropertyFromJson_FCsData_ShortCode(TSharedPtr<class FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString& MemberName);

	template<typename EnumStruct, typename EnumMap>
	static void WriteToMemberEnumStructPropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString& MemberName)
	{
		EnumStruct* Member  = StructProperty->ContainerPtrToValuePtr<EnumStruct>(InObject);
		const FString Value = JsonObject->GetStringField(MemberName);
		*Member				= EnumMap::Get().GetSafeEnum(Value);
	}

	template<typename T>
	static void WriteToMemberArrayStructPropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString& MemberName, TCsReadStructFromJson_Internal Internal = nullptr)
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
	static void WriteToMemberFixedArrayStructPropertyFromJson_EnumSize(TSharedPtr<class FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString& MemberName, const FString&(*ToString)(const E&), TCsReadStructFromJson_Internal Internal = nullptr)
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

	template<typename T, typename EnumType, typename EnumMap, uint8 SIZE>
	static void WriteToMemberFixedArrayStructPropertyFromJson_EnumSize(TSharedPtr<class FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString& MemberName, TCsReadStructFromJson_Internal Internal = nullptr)
	{
		T(*Member)[SIZE] = StructProperty->ContainerPtrToValuePtr<T[SIZE]>(InObject);

		const TSharedPtr<class FJsonObject> JObject = JsonObject->GetObjectField(MemberName);

		for (int32 I = 0; I < SIZE; ++I)
		{
			TSharedPtr<class FJsonObject> Object = JObject->GetObjectField(EnumMap::Get().ToString(I));

			if (Object->Values.Num() > CS_EMPTY)
				ReadStructFromJson(Object, (void*)&((*Member)[I]), StructProperty->Struct, Internal);
		}
	}

	template<typename EnumType, typename EnumMap>
	static void WriteToMemberEnumPropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, UEnumProperty* &EnumProperty, void* InObject, const FString& MemberName)
	{
		if (EnumType* Member = EnumProperty->ContainerPtrToValuePtr<EnumType>(InObject))
			*Member = EnumMap::Get()[JsonObject->GetStringField(MemberName)];
	}

	template<typename EnumType>
	static void WriteToMemberEnumAsBytePropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, UByteProperty* &ByteProperty, void* InObject, const FString& MemberName, const EnumType&(*ToType)(const FString&))
	{
		if (TEnumAsByte<EnumType>* Member = ByteProperty->ContainerPtrToValuePtr<TEnumAsByte<EnumType>>(InObject))
			*Member = (*ToType)(JsonObject->GetStringField(MemberName));
	}

	template<typename EnumType, typename EnumMap>
	static void WriteToMemberEnumAsBytePropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, UByteProperty* &ByteProperty, void* InObject, const FString& MemberName)
	{
		if (TEnumAsByte<EnumType>* Member = ByteProperty->ContainerPtrToValuePtr<TEnumAsByte<EnumType>>(InObject))
			*Member = EnumMap::Get()[JsonObject->GetStringField(MemberName)];
	}

	template<typename EnumType>
	static void WriteToMemberBytePropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, UByteProperty* &ByteProperty, void* InObject, const FString& MemberName, const EnumType&(*ToType)(const FString&))
	{
		if (EnumType* Member = ByteProperty->ContainerPtrToValuePtr<EnumType>(InObject))
			*Member = (*ToType)(JsonObject->GetStringField(MemberName));
	}

	template<typename EnumType, typename EnumMap>
	static void WriteToMemberBytePropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, UByteProperty* &ByteProperty, void* InObject, const FString& MemberName)
	{
		if (EnumType* Member = ByteProperty->ContainerPtrToValuePtr<EnumType>(InObject))
			*Member = EnumMap::Get()[JsonObject->GetStringField(MemberName)];
	}

	template<typename T>
	static void WriteToMemberArrayBytePropertyFromJson(TSharedPtr<class FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString& MemberName, T(*ToType)(const FString&))
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
	static void WriteToMemberFixedArrayBytePropertyFromJson_EnumSize(TSharedPtr<class FJsonObject> &JsonObject, UByteProperty* &ByteProperty, void* InObject, const FString& MemberName, T(*ToType)(const FString&), FString(*ToString)(const E&))
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
	static void WriteToMemberFixedArrayNamePropertyFromJson_EnumSize(TSharedPtr<class FJsonObject> &JsonObject, UNameProperty* &NameProperty, void* InObject, const FString& MemberName, FString(*ToString)(const E&))
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

	template<typename KeyType, typename ValueType>
	static void WriteToMemberMapStructPropertyFromJson_EnumStructKey_StructValue(TSharedPtr<class FJsonObject> &JsonObject, UMapProperty* &MapProperty, void* InObject, const FString& MemberName, TCsReadStructFromJson_Internal Internal = nullptr)
	{
		TMap<KeyType, ValueType>* Member = MapProperty->ContainerPtrToValuePtr<TMap<KeyType, ValueType>>(InObject);

		UStructProperty* StructProperty = Cast<UStructProperty>(MapProperty->ValueProp);

		const TSharedPtr<FJsonObject> JsonObjects = JsonObject->GetObjectField(MemberName);

		TArray<KeyType> Keys;
		Member->GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			TSharedPtr<FJsonObject> Object = JsonObjects->GetObjectField(Key.Name);

			ReadStructFromJson(Object, (void*)&((*Member)[Key]), StructProperty->Struct, Internal);
		}
	}

	template<typename KeyType, typename ValueType>
	static void WriteToMemberMapStructPropertyFromJson_EnumStructKey_NumericValue(TSharedPtr<class FJsonObject> &JsonObject, UMapProperty* &MapProperty, void* InObject, const FString& MemberName, TCsReadStructFromJson_Internal Internal = nullptr)
	{
		TMap<KeyType, ValueType>* Member = MapProperty->ContainerPtrToValuePtr<TMap<KeyType, ValueType>>(InObject);

		const TSharedPtr<FJsonObject> JsonObjects = JsonObject->GetObjectField(MemberName);

		TArray<KeyType> Keys;
		Member->GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			(*Member)[Key] = (ValueType)JsonObjects->GetNumberField(Key.Name);
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
	static FString GetAssetDescription(TSoftClassPtr<T>& AssetSubclassOf)
	{
		const FStringAssetReference& AssetRef = AssetSubclassOf.ToSoftObjectPath();
		const FString AssetName				  = AssetRef.ToString();
		FString AssetDescription			  = NCsCached::Str::Empty;

		// (AssetName != TEXT(""))
		if (AssetName != NCsCached::Str::Empty)
		{
			AssetDescription = TEXT("Blueprint'") + AssetName + TEXT("'");
		}
		return AssetDescription;
	}

		// CsStringAssetReference
#pragma region

	template<typename T>
	static void GetAssetReferenceFromSoftObjectProperty(USoftObjectProperty* &SoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags& LoadFlags, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = SoftObjectProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TSoftObjectPtr<T>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<T>>(InObject))
		{
			const FStringAssetReference AssetRef = Member->ToSoftObjectPath();
			const FString AssetName				 = AssetRef.ToString();
			
			// (AssetName == TEXT(""))
			if (AssetName == NCsCached::Str::Empty)
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
				Reference.Size.Kilobytes = UCsLibrary_Math::BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = UCsLibrary_Math::BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}

	template<typename T>
	static void GetAssetReferenceFromSoftObjectProperty(USoftObjectProperty* &SoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags& LoadFlags, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = SoftObjectProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TSoftObjectPtr<T>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<T>>(InObject))
		{
			const FStringAssetReference AssetRef = Member->ToSoftObjectPath();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == NCsCached::Str::Empty)
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
				Reference.Size.Kilobytes = UCsLibrary_Math::BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = UCsLibrary_Math::BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}

	static void GetAssetReferenceFromSoftObjectProperty_AnimMontage(USoftObjectProperty* &SoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferenceFromSoftObjectProperty_AnimMontage(USoftObjectProperty* &SoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	static void GetAssetReferenceFromSoftObjectProperty_AnimSequence(USoftObjectProperty* &SoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferenceFromSoftObjectProperty_AnimSequence(USoftObjectProperty* &SoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	static void GetAssetReferenceFromSoftObjectProperty_AnimBlueprint(USoftObjectProperty* &SoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferenceFromSoftObjectProperty_AnimBlueprint(USoftObjectProperty* &SoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	static void GetAssetReferenceFromSoftObjectProperty_MaterialInstanceConstant(USoftObjectProperty* &SoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferenceFromSoftObjectProperty_MaterialInstanceConstant(USoftObjectProperty* &SoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	static void GetAssetReferenceFromSoftObjectProperty_Blueprint(USoftObjectProperty* &SoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferenceFromSoftObjectProperty_Blueprint(USoftObjectProperty* &SoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	template<typename T>
	static void GetAssetReferenceFromArraySoftObjectProperty(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags& LoadFlags, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		if (TArray<TSoftObjectPtr<T>>* Member = ArraySoftObjectProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<T>>>(InObject))
		{
			const FString MemberName	 = ArraySoftObjectProperty->GetName();
										// MemberName + TEXT("_LaodFlags")
			const FString FlagMemberName = MemberName + ECsLoadCached::Str::_LoadFlags;

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
							const FStringAssetReference AssetRef = (*Member)[I].ToSoftObjectPath();
							const FString AssetName				 = AssetRef.ToString();
							
							// (AssetName == TEXT(""))
							if (AssetName == NCsCached::Str::Empty)
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
									Reference.Size.Kilobytes = UCsLibrary_Math::BytesToKilobytes(Reference.Size.Bytes);
									Reference.Size.Megabytes = UCsLibrary_Math::BytesToMegabytes(Reference.Size.Bytes);
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
				const FStringAssetReference AssetRef = (*Member)[I].ToSoftObjectPath();
				const FString AssetName				 = AssetRef.ToString();

				// (AssetName == TEXT(""))
				if (AssetName == NCsCached::Str::Empty)
					continue;

				OutAssetReferences.AddDefaulted();

				const int32 Size = OutAssetReferences.Num();

				FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
				Reference.Reference				   = AssetName;
				Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
				UObject* Asset = Cast<UObject>((*Member)[I].LoadSynchronous());

				Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(ResourceSizeMode);
				Reference.Size.Kilobytes = UCsLibrary_Math::BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = UCsLibrary_Math::BytesToMegabytes(Reference.Size.Bytes);
#endif // #if WITH_EDITOR
			}
		}
	}

	template<typename T>
	static void GetAssetReferenceFromArraySoftObjectProperty(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags& LoadFlags, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		if (TArray<TSoftObjectPtr<T>>* Member = ArraySoftObjectProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<T>>>(InObject))
		{
			const FString MemberName	 = ArraySoftObjectProperty->GetName();
										// MemberName + TEXT("_LoadFlags")
			const FString FlagMemberName = MemberName + ECsLoadCached::Str::_LoadFlags;

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
							const FStringAssetReference AssetRef = (*Member)[I].ToSoftObjectPath();
							const FString AssetName				 = AssetRef.ToString();

							// (AssetName == TEXT(""))
							if (AssetName == NCsCached::Str::Empty)
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
									Reference.Size.Kilobytes = BytesToKilobytes(Reference.Size.Bytes);
									Reference.Size.Megabytes = BytesToMegabytes(Reference.Size.Bytes);
								}
#endif // #if WITH_EDITOR
							}
						}
					}
				}
				return;
			}
			// Singleton
			const FString MemberName = SoftObjectProperty->GetName();

			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
				return;

			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToSoftObjectPath();
				const FString AssetName				 = AssetRef.ToString();

				// (AssetName == TEXT(""))
				if (AssetName == NCsCached::Str::Empty)
					continue;

				OutAssetReferences.AddDefaulted();

				const int32 Size = OutAssetReferences.Num();

				FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
				Reference.Reference				   = AssetName;
				Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
				UObject* Asset = Cast<UObject>((*Member)[I].LoadSynchronous());

				Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(ResourceSizeMode);
				Reference.Size.Kilobytes = UCsLibrary_Math::BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = UCsLibrary_Math::BytesToMegabytes(Reference.Size.Bytes);
#endif // #if WITH_EDITOR
			}
		}
	}

	template<typename T, int32 SIZE>
	static void GetAssetReferenceFromFixedArraySoftObjectProperty_EnumSize(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags& LoadFlags, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = SoftObjectProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TSoftObjectPtr<T>(*Member)[SIZE] = ArraySoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<T>[SIZE]>(InObject))
		{
			for (int32 I = 0; I < SIZE; ++I)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToSoftObjectPath();
				const FString AssetName				 = AssetRef.ToString();

				// (AssetName == TEXT(""))
				if (AssetName == NCsCached::Str::Empty)
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
					Reference.Size.Kilobytes = UCsLibrary_Math::BytesToKilobytes(Reference.Size.Bytes);
					Reference.Size.Megabytes = UCsLibrary_Math::BytesToMegabytes(Reference.Size.Bytes);
				}
#endif // #if WITH_EDITOR
			}
		}
	}

	static void GetAssetReferenceFromArraySoftObjectProperty_AnimMontage(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferenceFromArraySoftObjectProperty_AnimMontage(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	static void GetAssetReferenceFromArraySoftObjectProperty_AnimSequence(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferenceFromArraySoftObjectProperty_AnimSequence(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	static void GetAssetReferenceFromArraySoftObjectProperty_MaterialInstanceConstant(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferenceFromArraySoftObjectProperty_MaterialInstanceConstant(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	template<int32 SIZE>
	static void GetAssetReferenceFromFixedArraySoftObjectProperty_EnumSize_MaterialInstanceConstant(USoftObjectProperty* &SoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = SoftObjectProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TSoftObjectPtr<UMaterialInstanceConstant>(*Member)[SIZE] = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UMaterialInstanceConstant>[SIZE]>(InObject))
		{
			for (int32 I = 0; I < SIZE; ++I)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToSoftObjectPath();
				const FString AssetName				 = AssetRef.ToString();

				// (AssetName == TEXT(""))
				if (AssetName == NCsCached::Str::Empty)
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

						Reference.Size.Bytes += Texture->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
					}

					Reference.Size.Kilobytes = UCsLibrary_Math::BytesToKilobytes(Reference.Size.Bytes);
					Reference.Size.Megabytes = UCsLibrary_Math::BytesToMegabytes(Reference.Size.Bytes);
				}
#endif // #if WITH_EDITOR
			}
		}
	}

	static void GetAssetReferenceFromArraySoftObjectProperty_Blueprint(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferenceFromArraySoftObjectProperty_Blueprint(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	template<int32 SIZE>
	static void GetAssetReferenceFromFixedArraySoftObjectProperty_Blueprint_EnumSize(USoftObjectProperty* &SoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = SoftObjectProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TSoftObjectPtr<UBlueprint>(*Member)[SIZE] = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UBlueprint>[SIZE]>(InObject))
		{
			for (int32 I = 0; I < SIZE; ++I)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToSoftObjectPath();
				const FString AssetName				 = AssetRef.ToString();

				// (AssetName == TEXT(""))
				if (AssetName == NCsCached::Str::Empty)
					continue;

				OutAssetReferences.AddDefaulted();

				const int32 Size = OutAssetReferences.Num();
				// TODO: Fix / Investigate. 4.16.1. Built Game (Okay in Editor). TSoftObjectPtr for UAnimBlueprint / UWidgetBlueprint does NOT have _C
				FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
				Reference.Reference				   = AssetName.EndsWith(ECsLoadCached::Str::_C) ? AssetName : AssetName + ECsLoadCached::Str::_C;
				Reference.Reference_Internal	   = FStringAssetReference(Reference.Reference);
#if WITH_EDITOR
				if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
				{
					UObject* Asset = Cast<UObject>((*Member)[I].LoadSynchronous());

					Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(EResourceSizeMode::Inclusive);
					Reference.Size.Kilobytes = UCsLibrary_Math::BytesToKilobytes(Reference.Size.Bytes);
					Reference.Size.Megabytes = UCsLibrary_Math::BytesToMegabytes(Reference.Size.Bytes);
				}
#endif // #if WITH_EDITOR
			}
		}
	}

	template<int32 SIZE>
	static void GetAssetReferenceFromFixedArraySoftObjectProperty_Blueprint_EnumSize(USoftObjectProperty* &SoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = SoftObjectProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TSoftObjectPtr<UBlueprint>(*Member)[SIZE] = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UBlueprint>[SIZE]>(InObject))
		{
			for (int32 I = 0; I < SIZE; ++I)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToSoftObjectPath();
				const FString AssetName				 = AssetRef.ToString();

				// (AssetName == TEXT(""))
				if (AssetName == NCsCached::Str::Empty)
					continue;

				OutAssetReferences.AddDefaulted();

				const int32 Size = OutAssetReferences.Num();
				// TODO: Fix / Investigate. 4.16.1. Built Game (Okay in Editor). TSoftObjectPtr for UWidgetBlueprint does NOT have _C
				FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
				Reference.Reference				   = AssetName.EndsWith(ECsLoadCached::Str::_C) ? AssetName : AssetName + ECsLoadCached::Str::_C;
				Reference.Reference_Internal	   = FStringAssetReference(Reference.Reference);
#if WITH_EDITOR
				if (CalculateResourceSizes)
				{
					UObject* Asset = Cast<UObject>((*Member)[I].LoadSynchronous());

					Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(EResourceSizeMode::Inclusive);
					Reference.Size.Kilobytes = UCsLibrary_Math::BytesToKilobytes(Reference.Size.Bytes);
					Reference.Size.Megabytes = UCsLibrary_Math::BytesToMegabytes(Reference.Size.Bytes);
				}
#endif // #if WITH_EDITOR
			}
		}
	}

	template<typename T, int32 SIZE>
	static void GetAssetReferencesFromFixedArrayStructProperty_EnumSize(UStructProperty* &StructProperty, void* InObject, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromStruct_Internal Internal = nullptr, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
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
	static void GetAssetReferenceFromSoftClassProperty(USoftClassProperty* &SoftClassProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags& LoadFlags, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = SoftClassProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TSoftClassPtr<T>* Member = SoftClassProperty->ContainerPtrToValuePtr<TSoftClassPtr<T>>(InObject))
		{
			const FStringAssetReference AssetRef = Member->ToSoftObjectPath();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == NCsCached::Str::Empty)
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
				Reference.Size.Kilobytes = BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}

	template<typename T>
	static void GetAssetReferenceFromSoftClassProperty(USoftClassProperty* &SoftClassProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags& LoadFlags, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = SoftClassProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TSoftClassPtr<T>* Member = SoftClassProperty->ContainerPtrToValuePtr<TSoftClassPtr<T>>(InObject))
		{
			const FStringAssetReference AssetRef = Member->ToSoftObjectPath();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == NCsCached::Str::Empty)
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
				Reference.Size.Kilobytes = UCsLibrary_Math::BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = UCsLibrary_Math::BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}

	template<typename T>
	static void GetAssetReferenceFromArraySoftClassProperty(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags& LoadFlags, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = ArraySoftObjectProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TArray<TSoftClassPtr<T>>* Member = ArraySoftObjectProperty->ContainerPtrToValuePtr<TArray<TSoftClassPtr<T>>>(InObject))
		{
			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToSoftObjectPath();
				const FString AssetName				 = AssetRef.ToString();

				// (AssetName == TEXT(""))
				if (AssetName == NCsCached::Str::Empty)
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
					Reference.Size.Kilobytes = UCsLibrary_Math::BytesToKilobytes(Reference.Size.Bytes);
					Reference.Size.Megabytes = UCsLibrary_Math::BytesToMegabytes(Reference.Size.Bytes);
				}
#endif // #if WITH_EDITOR
			}
		}
	}

	template<typename T>
	static void GetAssetReferenceFromArraySoftClassProperty(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags& LoadFlags, const EResourceSizeMode::Type &ResourceSizeMode, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		const FString MemberName = ArraySoftObjectProperty->GetName();

		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
			return;

		if (TArray<TSoftClassPtr<T>>* Member = ArraySoftObjectProperty->ContainerPtrToValuePtr<TArray<TSoftClassPtr<T>>>(InObject))
		{
			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const FStringAssetReference AssetRef = (*Member)[I].ToSoftObjectPath();
				const FString AssetName				 = AssetRef.ToString();

				// (AssetName == TEXT(""))
				if (AssetName == NCsCached::Str::Empty)
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
					Reference.Size.Kilobytes = UCsLibrary_Math::BytesToKilobytes(Reference.Size.Bytes);
					Reference.Size.Megabytes = UCsLibrary_Math::BytesToMegabytes(Reference.Size.Bytes);
				}
#endif // #if WITH_EDITOR
			}
		}
	}

	template<typename T>
	static void GetAssetReferencesFromStructProperty(UStructProperty* &StructProperty, void* InObject, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromStruct_Internal Internal = nullptr, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		if (T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject))
			GetAssetReferencesFromStruct((void*)Member, StructProperty->Struct, LoadFlags, OutAssetReferences, Internal, LoadCodes);
	}

	template<typename T>
	static void GetAssetReferencesFromArrayStructProperty(UArrayProperty* ArrayProperty, void* InObject, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromStruct_Internal Internal = nullptr, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
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

	template<typename KeyType, typename ValueType>
	static void GetAssetReferencesFromMapStructProperty(UMapProperty* MapProperty, void* InObject, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromStruct_Internal Internal = nullptr, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES)
	{
		if (TMap<KeyType, ValueType>* Member = MapProperty->ContainerPtrToValuePtr<TMap<KeyType, ValueType>>(InObject))
		{
			UStructProperty* StructProperty = Cast<UStructProperty>(MapProperty->ValueProp);

			TArray<KeyType> Keys;
			Member->GetKeys(Keys);

			for (const KeyType& Key : Keys)
			{
				GetAssetReferencesFromStruct((void*)&((*Member)[Key]), StructProperty->Struct, LoadFlags, OutAssetReferences, Internal, LoadCodes);
			}
		}
	}

#pragma endregion CsStringAssetReference

	static void GetAssetReferencesFromStruct(void* InStruct, UScriptStruct* const &InScriptStruct, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromStruct_Internal Internal = nullptr, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);
	static void GetAssetReferencesFromObject(void* InObject, UClass* const &InClass, const ECsLoadFlags& LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromObject_Internal Internal = nullptr, const int32 &LoadCodes = ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES);

	static void GetObjectPaths(const void* StructValue, UStruct* const& Struct, TArray<FSoftObjectPath>& OutObjectPaths);
	static void GetObjectPaths(const void* StructValue, UStruct* const& Struct, TMap<FName, FSoftObjectPath>& OutObjectPathMap);
	static void GetObjectPaths(ULevel* Level, TMap<FName, FSoftObjectPath>& OutObjectPathMap);
	static void GetUniqueObjectPaths(const void* StructValue, UStruct* const& Struct, TArray<FSoftObjectPath>& OutObjectPaths);

#pragma endregion Asset References

	// DataTable
#pragma region
public:

	static void GetDataTables(const void* StructValue, UStruct* const& Struct, TMap<FName, UDataTable*>& OutDataTableMap);
	static void GetDataTables(ULevel* Level, TMap<FName, UDataTable*>& OutDataTableMap);

#pragma endregion DataTable

	// Load
#pragma region

	template<typename T>
	static void LoadTSoftObjectPtr(const FString& MemberName, TSoftObjectPtr<T> AssetPtr, T*& Internal, const FString& AssetType, const FString& AssetErrorMessageType)
	{
		const FString& AssetName = AssetPtr.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
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

				UE_LOG(LogLoad, Warning, TEXT("UCsLibrary_Load::LoadTSoftObjectPtr (%s): Failed to load %s at %s"), *MemberName, *AssetErrorMessageType, *AssetDescription);

				Internal = nullptr;
			}
		}
	}

	template<typename T>
	static void LoadTSoftObjectPtr(const FString& MemberName, TSoftObjectPtr<T>* AssetPtr, T*& Internal, const FString& AssetType, const FString& AssetErrorMessageType)
	{
		const FString& AssetName = AssetPtr->ToString();

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
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

				UE_LOG(LogLoad, Warning, TEXT("UCsLibrary_Load::LoadTSoftObjectPtr (%s): Failed to load %s at %s"), *MemberName, *AssetErrorMessageType, *AssetDescription);

				Internal = nullptr;
			}
		}
	}

	template<typename T>
	static void LoadTSoftObjectPtr(const FString& MemberName, TSoftObjectPtr<T> AssetPtr, TWeakObjectPtr<T>& Internal, const FString &AssetType, const FString& AssetErrorMessageType)
	{
		const FString& AssetName = AssetPtr.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
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

				UE_LOG(LogLoad, Warning, TEXT("UCsLibrary_Load::LoadTSoftObjectPtr (%s): Failed to load %s at %s"), *MemberName, *AssetErrorMessageType, *AssetDescription);

				Internal = nullptr;
			}
		}
	}

	static void LoadTSoftObjectPtr_Blueprint(const FString& MemberName, TSoftObjectPtr<class UBlueprint> AssetPtr, class UBlueprintGeneratedClass* &Internal);
	static void LoadTSoftObjectPtr_Blueprint(const FString& MemberName, TSoftObjectPtr<class UBlueprint>* AssetPtr, class UBlueprintGeneratedClass* &Internal);

	static void LoadTSoftObjectPtr_AnimBlueprint(const FString& MemberName, TSoftObjectPtr<class UAnimBlueprint> AssetPtr, class UAnimBlueprintGeneratedClass* &Internal);
	static void LoadTSoftObjectPtr_AnimBlueprint(const FString& MemberName, TSoftObjectPtr<class UAnimBlueprint>* AssetPtr, class UAnimBlueprintGeneratedClass* &Internal);

	template<typename T>
	static void LoadTSoftClassPtr(const FString& MemberName, TSoftClassPtr<T>& AssetSubclassOf, T* &Internal, const FString& AssetErrorMessageType)
	{
		const FString& AssetName = AssetSubclassOf.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
		{
			Internal = nullptr;
			return;
		}

		if (Internal &&
			AssetSubclassOf.IsValid() && AssetSubclassOf.Get() &&
			Internal == AssetSubclassOf.Get()->template GetDefaultObject<T>())
		{
			UE_LOG(LogLoad, Warning, TEXT("UCsLibrary_Load::LoadTSoftClassPtr (%s): Possibly trying to load %s and it is already loaded"), *MemberName, *AssetErrorMessageType);
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

				UE_LOG(LogLoad, Warning, TEXT("UCsLibrary_Load::LoadTSoftClassPtr (%s): Failed to load %s at %s"), *MemberName, *AssetErrorMessageType, *AssetDescription);

				Internal = nullptr;
			}
		}
	}

	template<typename T>
	static void LoadTSoftClassPtr(const FString& MemberName, TSoftClassPtr<T>*& AssetSubclassOf, T*& Internal, const FString& AssetErrorMessageType)
	{
		const FString& AssetName = AssetSubclassOf->ToString();

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
		{
			Internal = nullptr;
			return;
		}

		if (Internal &&
			AssetSubclassOf->IsValid() && AssetSubclassOf->Get() &&
			Internal == AssetSubclassOf->Get()->template GetDefaultObject<T>())
		{
			UE_LOG(LogLoad, Warning, TEXT("UCsLibrary_Load::LoadTSoftClassPtr (%s): Possibly trying to load %s and it is already loaded"), *MemberName, *AssetErrorMessageType);
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

				UE_LOG(LogLoad, Warning, TEXT("UCsLibrary_Load::LoadTSoftClassPtr (%s): Failed to load %s at %s"), *MemberName, *AssetErrorMessageType, *AssetDescription);

				Internal = nullptr;
			}
		}
	}

	template<typename T>
	static void LoadTSoftClassPtr(const FString& MemberName, TSoftClassPtr<T>& AssetSubclassOf, TWeakObjectPtr<T>& Internal, const FString& AssetErrorMessageType)
	{
		const FString& AssetName = AssetSubclassOf.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
		{
			Internal = nullptr;
			return;
		}

		if (Internal.IsValid() && Internal.Get() &&
			AssetSubclassOf.IsValid() && AssetSubclassOf.Get() &&
			Internal == AssetSubclassOf.Get()->template GetDefaultObject<T>())
		{
			UE_LOG(LogLoad, Warning, TEXT("UCsLibrary_Load::LoadTSoftClassPtr (%s): Possibly trying to load %s and it is already loaded"), *MemberName, *AssetErrorMessageType);
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

				UE_LOG(LogLoad, Warning, TEXT("UCsLibrary_Load::LoadTSoftClassPtr (%s): Failed to load %s at %s"), *MemberName, *AssetErrorMessageType, *AssetDescription);

				Internal = nullptr;
			}
		}
	}

	template<typename T>
	static void LoadTSoftClassPtr(TSoftClassPtr<T>& AssetSubclassOf, T*& OutAsset, const FString& AssetErrorMessageType)
	{
		OutAsset = nullptr;

		const FString& AssetName = AssetSubclassOf.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
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

				UE_LOG(LogLoad, Warning, TEXT("UCsLibrary_Load::LoadTSoftClassPtr (%s): Failed to load %s at %s"), *AssetErrorMessageType, *AssetDescription);
			}
		}
	}

	template<typename T>
	static void LoadTSoftClassPtr(TSoftClassPtr<T>& AssetSubclassOf, T*& OutAsset)
	{
		OutAsset = nullptr;

		const FString& AssetName = AssetSubclassOf.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
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

				UE_LOG(LogLoad, Warning, TEXT("UCsLibrary_Load::LoadTSoftClassPtr: Failed to load %s at %s"), *AssetDescription);
			}
		}
	}

	template<typename T>
	static void SetTArrayFromTArrayTSoftObjectPtr(TArray<T*>& Array, TArray<TSoftObjectPtr<T>>& ArrayAssetPtr)
	{
		Array.Reset();

		const int32 Count = ArrayAssetPtr.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Array.Add(ArrayAssetPtr[I].Get());
		}
	}

	template<typename T>
	static void SetTArrayFromTArrayTSoftObjectPtr(TArray<T*>& Array, TArray<TSoftObjectPtr<T>>*& ArrayAssetPtr)
	{
		Array.Reset();

		const int32 Count = ArrayAssetPtr->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Array.Add((*ArrayAssetPtr)[I].Get());
		}
	}

	template<typename T>
	static void SetTArrayFromTArrayTSoftObjectPtr(TArray<TWeakObjectPtr<T>> &Array, TArray<TSoftObjectPtr<T>> &ArrayAssetPtr)
	{
		Array.Reset();

		const int32 Count = ArrayAssetPtr.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Array.Add(ArrayAssetPtr[I].Get());
		}
	}

	template<typename T>
	static void SetTArrayFromTArrayTSoftObjectPtr(TArray<TWeakObjectPtr<T>> &Array, TArray<TSoftObjectPtr<T>>* &ArrayAssetPtr)
	{
		Array.Reset();

		const int32 Count = ArrayAssetPtr->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Array.Add((*ArrayAssetPtr)[I].Get());
		}
	}

	template<typename T>
	static void LoadTArrayTSoftObjectPtr(const FString& MemberName, TArray<TSoftObjectPtr<T>> &ArrayAssetPtr, TArray<T*> &ArrayInternal, const FString &AssetType, const FString& AssetErrorMessageType)
	{
		if (ArrayInternal.Num() > 0 &&
			AreAllElementsInTArrayNotNull(ArrayInternal))
		{
			//UE_LOG(LogLoad, Warning, TEXT("Load (%s): Possibly trying to load %s and it is already loaded"), *MemberName, *AssetErrorMessageType);
		}

		if (ArrayAssetPtr.Num() > 0 &&
			AreAllElementsInTArrayAssetPtrNotNull(ArrayAssetPtr))
		{
			SetTArrayFromTArrayTSoftObjectPtr<T>(ArrayInternal, ArrayAssetPtr);
		}
		else
		{
			NullAndEmptyTArray<T>(ArrayInternal);

			const int32 Count = ArrayAssetPtr.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				TSoftObjectPtr<T>& AssetPtr				  = ArrayAssetPtr[I];
				const FStringAssetReference& AssetRef = AssetPtr.ToSoftObjectPath();
				const FString& AssetName			  = AssetRef.ToString();

				// (AssetName != TEXT(""))
				if (AssetName != NCsCached::Str::Empty)
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
	static void LoadTArrayTSoftObjectPtr(const FString& MemberName, TArray<TSoftObjectPtr<T>>* &ArrayAssetPtr, TArray<T*> &ArrayInternal, const FString &AssetType, const FString& AssetErrorMessageType)
	{
		if (ArrayInternal.Num() > 0 &&
			AreAllElementsInTArrayNotNull(ArrayInternal))
		{
			//UE_LOG(LogLoad, Warning, TEXT("Load (%s): Possibly trying to load %s and it is already loaded"), *MemberName, *AssetErrorMessageType);
		}

		if (ArrayAssetPtr->Num() > 0 &&
			AreAllElementsInTArrayAssetPtrNotNull(ArrayAssetPtr))
		{
			SetTArrayFromTArrayTSoftObjectPtr<T>(ArrayInternal, ArrayAssetPtr);
		}
		else
		{
			NullAndEmptyTArray<T>(ArrayInternal);

			const int32 Count = ArrayAssetPtr->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				TSoftObjectPtr<T>& AssetPtr				  = (*ArrayAssetPtr)[I];
				const FStringAssetReference& AssetRef = AssetPtr.ToSoftObjectPath();
				const FString& AssetName			  = AssetRef.ToString();

				// (AssetName != TEXT(""))
				if (AssetName != NCsCached::Str::Empty)
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
	static void LoadTArrayTSoftObjectPtr(const FString& MemberName, TArray<TSoftObjectPtr<T>> &ArrayAssetPtr, TArray<TWeakObjectPtr<T>> &ArrayInternal, const FString &AssetType, const FString& AssetErrorMessageType)
	{
		if (ArrayInternal.Num() > 0 &&
			AreAllElementsInTArrayNotNull(ArrayInternal))
		{
			//UE_LOG(LogLoad, Warning, TEXT("Load (%s): Possibly trying to load %s and it is already loaded"), *MemberName, *AssetErrorMessageType);
		}

		if (ArrayAssetPtr.Num() > 0 &&
			AreAllElementsInTArrayAssetPtrNotNull(ArrayAssetPtr))
		{
			SetTArrayFromTArrayTSoftObjectPtr<T>(ArrayInternal, ArrayAssetPtr);
		}
		else
		{
			NullAndEmptyTArray<T>(ArrayInternal);

			const int32 Count = ArrayAssetPtr.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				TSoftObjectPtr<T>& AssetPtr				  = ArrayAssetPtr[I];
				const FStringAssetReference& AssetRef = AssetPtr.ToSoftObjectPath();
				const FString& AssetName			  = AssetRef.ToString();

				// (AssetName != TEXT(""))
				if (AssetName != NCsCached::Str::Empty)
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

	static void LoadTArrayTSoftObjectPtr_Blueprint(const FString& MemberName, TArray<TSoftObjectPtr<class UBlueprint>> &ArrayAssetPtr, TArray<class UBlueprintGeneratedClass*> &ArrayInternal);
	static void LoadTArrayTSoftObjectPtr_Blueprint(const FString& MemberName, TArray<TSoftObjectPtr<class UBlueprint>>* &ArrayAssetPtr, TArray<class UBlueprintGeneratedClass*> &ArrayInternal);

	template<typename T>
	static void SetTArrayFromTArrayTSoftClassPtr(TArray<T*> &Array, TArray<TSoftClassPtr<T>> &ArrayAssetSubclassOf)
	{
		Array.Reset();

		const int32 Count = ArrayAssetSubclassOf.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Array.Add(ArrayAssetSubclassOf[I].Get()->template GetDefaultObject<T>());
		}
	}

	template<typename T>
	static void SetTArrayFromTArrayTSoftClassPtr(TArray<T*> &Array, TArray<TSoftClassPtr<T>>* &ArrayAssetSubclassOf)
	{
		Array.Reset();

		const int32 Count = ArrayAssetSubclassOf->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Array.Add((*ArrayAssetSubclassOf)[I].Get()->template GetDefaultObject<T>());
		}
	}

	template<typename T>
	static void LoadTArrayTSoftClassPtr(const FString& MemberName, TArray<TSoftClassPtr<T>>* &ArrayAssetSubclassOf, TArray<T*> &ArrayInternal, const FString& AssetErrorMessageType)
	{
		if (ArrayInternal.Num() > 0 &&
			AreAllElementsInTArrayNotNull(ArrayInternal))
		{
			//UE_LOG(LogLoad, Warning, TEXT("Load (%s): Possibly trying to load %s and it is already loaded"), *MemberName, *AssetErrorMessageType);
		}

		if (ArrayAssetSubclassOf->Num() > 0 &&
			AreAllElementsInTArrayAssetSubclassOfNotNull(ArrayAssetSubclassOf))
		{
			SetTArrayFromTArrayTSoftClassPtr<T>(ArrayInternal, ArrayAssetSubclassOf);
		}
		else
		{
			NullAndEmptyTArray<T>(ArrayInternal);

			const int32 Count = ArrayAssetSubclassOf->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				TSoftClassPtr<T>& AssetSubclassOf  = (*ArrayAssetSubclassOf)[I];
				const FStringAssetReference& AssetRef = AssetSubclassOf.ToSoftObjectPath();
				const FString& AssetName			  = AssetRef.ToString();

				// (AssetName != TEXT(""))
				if (AssetName != NCsCached::Str::Empty)
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
	static void LoadFCsStruct(const FString& MemberName, T* InStruct, const ECsLoadFlags& LoadFlags)
	{
		LoadStructWithTSoftObjectPtrs(MemberName, InStruct, T::StaticStruct(), LoadFlags);
	}

	template<typename T>
	static void LoadFCsStruct(const FString& MemberName, T* InStruct)
	{
		LoadFCsStruct<T>(MemberName, InStruct, ECsLoadFlags::Game);
	}

	static void LoadFCsAnimSequence(const FString& MemberName, struct FCsAnimSequence* Anim, const ECsLoadFlags& LoadFlags);
	static void LoadFCsAnimSequence(const FString& MemberName, struct FCsAnimSequence* Anim);
	static void LoadFCsFpvAnimSequence(const FString& MemberName, struct FCsFpvAnimSequence* Anim, const ECsLoadFlags& LoadFlags);
	static void LoadFCsFpvAnimSequence(const FString& MemberName, struct FCsFpvAnimSequence* Anim, const ECsViewType& ViewType);

	static void LoadFCsAnimMontage(const FString& MemberName, struct FCsAnimMontage* Anim, const ECsLoadFlags& LoadFlags);
	static void LoadFCsAnimMontage(const FString& MemberName, struct FCsAnimMontage* Anim);
	static void LoadFCsFpvAnimMontage(const FString& MemberName, struct FCsFpvAnimMontage* Anim, const ECsLoadFlags& LoadFlags);
	static void LoadFCsFpvAnimMontage(const FString& MemberName, struct FCsFpvAnimMontage* Anim, const ECsViewType& ViewType);

	static void LoadFCsBlendSpace1D(const FString& MemberName, struct FCsBlendSpace1D *Blend, const ECsLoadFlags& LoadFlags);
	static void LoadFCsBlendSpace1D(const FString& MemberName, struct FCsBlendSpace1D* Blend);
	static void LoadFCsFpvBlendSpace1D(const FString& MemberName, struct FCsFpvBlendSpace1D* Blend, const ECsLoadFlags& LoadFlags);
	static void LoadFCsFpvBlendSpace1D(const FString& MemberName, struct FCsFpvBlendSpace1D* Blend, const ECsViewType& ViewType);

	static void LoadFCsBlendSpace(const FString& MemberName, struct FCsBlendSpace* Blend, const ECsLoadFlags& LoadFlags);
	static void LoadFCsBlendSpace(const FString& MemberName, struct FCsBlendSpace* Blend);
	static void LoadFCsFpvBlendSpace(const FString& MemberName, struct FCsFpvBlendSpace* Blend, const ECsLoadFlags& LoadFlags);
	static void LoadFCsFpvBlendSpace(const FString& MemberName, struct FCsFpvBlendSpace* Blend, const ECsViewType& ViewType);

	static void LoadFCsAimOffset(const FString& MemberName, struct FCsAimOffset* Blend, const ECsLoadFlags& LoadFlags);
	static void LoadFCsAimOffset(const FString& MemberName, struct FCsAimOffset* Blend);
	static void LoadFCsFpvAimOffset(const FString& MemberName, struct FCsFpvAimOffset* Blend, const ECsLoadFlags& LoadFlags);
	static void LoadFCsFpvAimOffset(const FString& MemberName, struct FCsFpvAimOffset* Blend, const ECsViewType& ViewType);

	static bool CanLoad(void* InObject, UScriptStruct* const &InClass, const FString& MemberName, const ECsLoadFlags& LoadFlags, const int32 &LoadCodes);
	static bool CanLoad(void* InObject, UClass* const &InClass, const FString& MemberName, const ECsLoadFlags& LoadFlags, const int32 &LoadCodes);
	static bool CanLoad(void* StructValue, UStruct* const& Struct, const FString& MemberName, const ECsLoadFlags& LoadFlags, const int32& LoadCodes);

	template<typename T>
	static void LoadSoftClassProperty(USoftClassProperty* &SoftClassProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString& MemberName, const FString &AssetType, const ECsLoadFlags& LoadFlags)
	{
		if (TSoftClassPtr<T>* Member = SoftClassProperty->ContainerPtrToValuePtr<TSoftClassPtr<T>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (T** Internal = InternalProperty->ContainerPtrToValuePtr<T*>(InObject))
					LoadTSoftClassPtr<T>(ObjectName + NCsCached::Str::Dot + MemberName, Member, *Internal, AssetType);
										//  ObjectName + TEXT(".") + MemberName
			}
		}
	}

	template<typename T>
	static void LoadSoftClassProperty(USoftClassProperty* &SoftClassProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString& MemberName, const FString &AssetType, const ECsLoadFlags& LoadFlags)
	{
		if (TSoftClassPtr<T>* Member = SoftClassProperty->ContainerPtrToValuePtr<TSoftClassPtr<T>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (T** Internal = InternalProperty->ContainerPtrToValuePtr<T*>(InObject))
					LoadTSoftClassPtr<T>(ObjectName + NCsCached::Str::Dot + MemberName, Member, *Internal, AssetType);
										//  ObjectName + TEXT(".") + MemberName
			}
		}
	}

	template<typename T>
	static void LoadArraySoftClassProperty(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString& MemberName, const FString& AssetErrorMessageType, const ECsLoadFlags& LoadFlags)
	{
		if (TArray<TSoftClassPtr<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TSoftClassPtr<T>>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (TArray<T*>* Internal = InternalProperty->ContainerPtrToValuePtr<TArray<T*>>(InObject))
					LoadTArrayTSoftClassPtr<T>(ObjectName + NCsCached::Str::Dot + MemberName, Member, *Internal, AssetErrorMessageType);
												//ObjectName + TEXT(".") + MemberName
			}
		}
	}

	template<typename T>
	static void LoadArraySoftClassProperty(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString& MemberName, const FString& AssetErrorMessageType, const ECsLoadFlags& LoadFlags)
	{
		if (TArray<TSoftClassPtr<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TSoftClassPtr<T>>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (TArray<T*>* Internal = InternalProperty->ContainerPtrToValuePtr<TArray<T*>>(InObject))
					LoadTArrayTSoftClassPtr<T>(ObjectName + NCsCached::Str::Dot + MemberName, Member, *Internal, AssetErrorMessageType);
												//ObjectName + TEXT(".") + MemberName
			}
		}
	}

	template<typename T>
	static void LoadSoftObjectProperty(USoftObjectProperty* &SoftObjectProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString& MemberName, const FString &AssetType, const FString& AssetErrorMessageType, const ECsLoadFlags& LoadFlags)
	{
		if (TSoftObjectPtr<T>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<T>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (T** Internal = InternalProperty->ContainerPtrToValuePtr<T*>(InObject))
					LoadTSoftObjectPtr<T>(ObjectName + NCsCached::Str::Dot + MemberName, Member, *Internal, AssetType, AssetErrorMessageType);
								//   ObjectName + TEXT(".") + MemberName
			}
		}
	}

	template<typename T>
	static void LoadSoftObjectProperty(USoftObjectProperty* &SoftObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString& MemberName, const FString &AssetType, const FString& AssetErrorMessageType, const ECsLoadFlags& LoadFlags)
	{
		if (TSoftObjectPtr<T>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<T>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (T** Internal = InternalProperty->ContainerPtrToValuePtr<T*>(InObject))
					LoadTSoftObjectPtr<T>(ObjectName + NCsCached::Str::Dot + MemberName, Member, *Internal, AssetType, AssetErrorMessageType);
								//   ObjectName + TEXT(".") + MemberName
			}
		}
	}

	static void LoadSoftObjectProperty_AnimBlueprint(USoftObjectProperty* &SoftObjectProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString& MemberName, const ECsLoadFlags& LoadFlags);
	static void LoadSoftObjectProperty_AnimBlueprint(USoftObjectProperty* &SoftObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString& MemberName, const ECsLoadFlags& LoadFlags);

	static void LoadSoftObjectProperty_Blueprint(USoftObjectProperty* &SoftObjectProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString& MemberName, const ECsLoadFlags& LoadFlags);
	static void LoadSoftObjectProperty_Blueprint(USoftObjectProperty* &SoftObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString& MemberName, const ECsLoadFlags& LoadFlags);

	template<typename T>
	static void LoadArraySoftObjectProperty(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString& MemberName, const FString &AssetType, const FString& AssetErrorMessageType, const ECsLoadFlags& LoadFlags)
	{
		if (TArray<TSoftObjectPtr<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<T>>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (TArray<T*>* Internal = InternalProperty->ContainerPtrToValuePtr<TArray<T*>>(InObject))
					LoadTArrayTSoftObjectPtr<T>(ObjectName + NCsCached::Str::Dot + MemberName, Member, *Internal, AssetType, AssetErrorMessageType);
										// ObjectName + TEXT(".") + MemberName
			}
		}
	}

	template<typename T>
	static void LoadArraySoftObjectProperty(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString& MemberName, const FString &AssetType, const FString& AssetErrorMessageType, const ECsLoadFlags& LoadFlags)
	{
		if (TArray<TSoftObjectPtr<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<T>>>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (TArray<T*>* Internal = InternalProperty->ContainerPtrToValuePtr<TArray<T*>>(InObject))
					LoadTArrayTSoftObjectPtr<T>(ObjectName + NCsCached::Str::Dot + MemberName, Member, *Internal, AssetType, AssetErrorMessageType);
										// ObjectName + TEXT(".") + MemberName
			}
		}
	}

	template<typename T, typename E, int32 SIZE>
	static void LoadFixedArraySoftObjectProperty_EnumSize(USoftObjectProperty* &SoftObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString& MemberName, const FString &AssetType, const FString& AssetErrorMessageType, const ECsLoadFlags& LoadFlags, const FString&(*ToString)(const E&))
	{
		if (TSoftObjectPtr<T>(*Member)[SIZE] = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<T>[SIZE]>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (T*(*Internal)[SIZE] = InternalProperty->ContainerPtrToValuePtr<T*[SIZE]>(InObject))
				{
					for (int32 I = 0; I < SIZE; ++I)
					{
						const FString Index		  = (*ToString)((E)I);
						const FString ElementName = MemberName + TEXT("[") + Index + TEXT("]");

						LoadTSoftObjectPtr<T>(ElementName, (*Member)[I], (*Internal)[I], AssetType, AssetErrorMessageType);
					}
				}
			}
		}
	}

	static void LoadArraySoftObjectProperty_Blueprint(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString& MemberName, const ECsLoadFlags& LoadFlags);
	static void LoadArraySoftObjectProperty_Blueprint(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString& MemberName, const ECsLoadFlags& LoadFlags);

	template<typename E, int32 SIZE>
	static void LoadFixedArraySoftObjectProperty_Blueprint_EnumSize(USoftObjectProperty* &SoftObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString& MemberName, const ECsLoadFlags& LoadFlags, FString(*ToString)(const E&))
	{
		if (TSoftObjectPtr<UBlueprint>(*Member)[SIZE] = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UBlueprint>[SIZE]>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (UBlueprintGeneratedClass*(*Internal)[SIZE] = InternalProperty->ContainerPtrToValuePtr<UBlueprintGeneratedClass*[SIZE]>(InObject))
				{
					for (int32 I = 0; I < SIZE; ++I)
					{
						const FString Index		  = (*ToString)((E)I);
						const FString ElementName = MemberName + TEXT("[") + Index + TEXT("]");
						LoadTSoftObjectPtr_Blueprint(ElementName, (*Member)[I], (*Internal)[I]);
					}
				}
			}
		}
	}

	template<typename E, int32 SIZE>
	static void LoadFixedArraySoftObjectProperty_Blueprint_EnumSize(USoftObjectProperty* &SoftObjectProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString& MemberName, const ECsLoadFlags& LoadFlags, FString(*ToString)(const E&))
	{
		if (TSoftObjectPtr<UBlueprint>(*Member)[SIZE] = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UBlueprint>[SIZE]>(InObject))
		{
			if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
				return;

											// MemberName + TEXT("_Internal")
			const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

			if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
			{
				if (UBlueprintGeneratedClass*(*Internal)[SIZE] = InternalProperty->ContainerPtrToValuePtr<UBlueprintGeneratedClass*[SIZE]>(InObject))
				{
					for (int32 I = 0; I < SIZE; ++I)
					{
						const FString Index		  = (*ToString)((E)I);
						const FString ElementName = MemberName + TEXT("[") + Index + TEXT("]");
						LoadTSoftObjectPtr_Blueprint(ElementName, (*Member)[I], (*Internal)[I]);
					}
				}
			}
		}
	}

	template<typename T>
	static void LoadMemberStructProperty(UStructProperty* &StructProperty, void* InObject, const FString& MemberName, const ECsLoadFlags& LoadFlags, TCsLoadStructWithTSoftObjectPtrs_Internal Internal = nullptr)
	{
		if (T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject))
			LoadStructWithTSoftObjectPtrs(MemberName, (void*)Member, StructProperty->Struct, LoadFlags, Internal);
	}

	template<typename T>
	static void LoadMemberArrayStructProperty(UArrayProperty* &ArrayProperty, void* InObject, const FString& MemberName, const ECsLoadFlags& LoadFlags)
	{
		if (TArray<T>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<T>>(InObject))
		{
			UStructProperty* StructProperty = Cast<UStructProperty>(ArrayProperty->Inner);

			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const FString ElementName = MemberName + TEXT("[") + FString::FromInt(I) + TEXT("]");
				LoadStructWithTSoftObjectPtrs(ElementName, (void*)&((*Member)[I]), StructProperty->Struct, LoadFlags);
			}
		}
	}

	template<typename T, typename E, int32 SIZE>
	static void LoadMemberFixedArrayStructProperty_EnumSize(UStructProperty* &StructProperty, void* InObject, const FString& MemberName, const ECsLoadFlags& LoadFlags, const FString&(*ToString)(const E&), TCsLoadStructWithTSoftObjectPtrs_Internal Internal = nullptr)
	{
		if (T(*Member)[SIZE] = StructProperty->ContainerPtrToValuePtr<T[SIZE]>(InObject))
		{
			for (int32 I = 0; I < SIZE; ++I)
			{
				const FString Index		  = (*ToString)((E)I);
				const FString ElementName = MemberName + TEXT("[") + Index + TEXT("]");
				LoadStructWithTSoftObjectPtrs(ElementName, (void*)&((*Member)[I]), StructProperty->Struct, LoadFlags, Internal);
			}
		}
	}

	template<typename KeyType, typename ValueType>
	static void LoadMemberMapStructProperty_EnumStructKey(UMapProperty* &MapProperty, void* InObject, const FString& MemberName, const ECsLoadFlags& LoadFlags, TCsLoadStructWithTSoftObjectPtrs_Internal Internal = nullptr)
	{
		if (TMap<KeyType, ValueType>* Member = MapProperty->ContainerPtrToValuePtr<TMap<KeyType, ValueType>>(InObject))
		{
			UStructProperty* StructProperty = Cast<UStructProperty>(MapProperty->ValueProp);

			TArray<KeyType> Keys;
			Member->GetKeys(Keys);

			for (const KeyType& Key : Keys)
			{
				const FString ElementName = MemberName + TEXT("[") + Key.Name + TEXT("]");
				LoadStructWithTSoftObjectPtrs(ElementName, (void*)&((*Member)[Key]), StructProperty->Struct, LoadFlags, Internal);
			}
		}
	}

	static void LoadStructWithTSoftObjectPtrs(const FString &ObjectName, void* InStruct, UScriptStruct* const &InScriptStruct, const ECsLoadFlags& LoadFlags, TCsLoadStructWithTSoftObjectPtrs_Internal Internal = nullptr);
	static void LoadObjectWithTSoftObjectPtrs(const FString &ObjectName, void* InObject, UClass* const &InClass, const ECsLoadFlags& LoadFlags, TCsLoadObjectWithTSoftObjectPtrs_Internal Internal = nullptr);

	template<typename T, typename U, typename S>
	static void SetTArrayInternalMemberFromLoadedAssets(void* InObject, UClass* const &InClass, const FString &StructMemberName, UScriptStruct* const &InScriptStruct, const FString& MemberName, const TArray<UObject*> &LoadedAssets)
	{
		if (UStructProperty* StructProperty = FindField<UStructProperty>(InClass, *StructMemberName))
		{
			// Struct
			if (T* Struct = StructProperty->ContainerPtrToValuePtr<T>(InObject))
			{
										//   MemberName = TEXT("_Internal")
				const FString InternalName = MemberName + ECsLoadCached::Str::_Internal;

				TArray<TSoftObjectPtr<U>>* AssetPtrs = nullptr;
				TArray<S*>* Internals			= nullptr;
				// Member
				if (UArrayProperty* ArrayProperty = FindField<UArrayProperty>(InScriptStruct, *MemberName))
					AssetPtrs = ArrayProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<U>>>(Struct);
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

	static void LoadSoftClassProperty(USoftClassProperty*& SoftClassProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const ECsLoadFlags& LoadFlags);

	static void LoadArraySoftClassProperty(UArrayProperty*& ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const ECsLoadFlags& LoadFlags);

	static void LoadSoftObjectProperty(USoftObjectProperty*& SoftObjectProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const ECsLoadFlags& LoadFlags);

	static void LoadArraySoftObjectProperty(UArrayProperty*& ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const ECsLoadFlags& LoadFlags);

	static void LoadArrayStructProperty(UArrayProperty*& ArrayProperty, void* StructValue);




	static bool CanLoad(void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadSoftClassProperty(USoftClassProperty*& SoftClassProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadArraySoftClassProperty(UArrayProperty*& ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadSoftObjectProperty(USoftObjectProperty*& SoftObjectProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadArraySoftObjectProperty(UArrayProperty*& ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadArrayObjectProperty(UArrayProperty*& ArrayProperty, void* StructValue, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadArrayStructProperty(UArrayProperty*& ArrayProperty, void* StructValue, const int32& LoadFlags, const int32& LoadCodes);

	/**
	*
	*
	* @param StructValue
	* @param Struct
	* @param LoadFlags
	* @param LoadCodes
	*/
	static void LoadStruct(void* StructValue, UStruct* const& Struct, const int32& LoadFlags, const int32& LoadCodes);

	/**
	*
	*
	* @param DataTable
	* @param LoadFlags
	* @param LoadCodes
	*/
	static void LoadDataTable(UDataTable* DataTable, const int32& LoadFlags, const int32& LoadCodes);

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
			UnLoadStructWithTSoftObjectPtrs((void*)Member, StructProperty->Struct);
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
				UnLoadStructWithTSoftObjectPtrs((void*)&((*Member)[I]), StructProperty->Struct);
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
				UnLoadStructWithTSoftObjectPtrs((void*)&((*Member)[I]), StructProperty->Struct);
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
				UnLoadStructWithTSoftObjectPtrs((void*)&((*Member)[I]), StructProperty->Struct);
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
				UnLoadStructWithTSoftObjectPtrs((void*)&((*Member)[I]), StructProperty->Struct);
			}
		}
	}

	template<typename T>
	static void UnLoadArrayObjectProperty(UArrayProperty* &ArrayProperty, void* InObject)
	{
		if (TArray<T*>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<T*>>(InObject))
			Member->Reset();
	}

	static void UnLoadStructWithTSoftObjectPtrs(void* InStruct, UScriptStruct* const &InScriptStruct);
	static void UnLoadObjectWithTSoftObjectPtrs(void* InObject, UClass* const &InClass);

	static void UnloadSoftClassProperty(USoftClassProperty*& SoftClassProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const ECsLoadFlags& LoadFlags);

	static void UnloadStruct(void* StructValue, UStruct* const& Struct);

#pragma endregion UnLoad

	// References
#pragma region
public:

		// Hard
#pragma region
public:

	static void GetReferencesReport_ClassProperty(UClassProperty* ClassProperty, const void* StructValue, UStruct* const& Struct, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport);
	static void GetReferencesReport_ObjectProperty(UObjectProperty* ObjectProperty, const void* StructValue, UStruct* const& Struct, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport);
	static void GetReferencesReport_SoftClassProperty(USoftClassProperty* SoftClassProperty, const void* StructValue, UStruct* const& Struct, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport);
	static void GetReferencesReport_SoftObjectProperty(USoftObjectProperty* SoftObjectProperty, const void* StructValue, UStruct* const& Struct, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport);

	static void GetReferencesReport(const void* StructValue, UStruct* const& Struct, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport);

#pragma endregion Hard

#pragma endregion References

	// IsLoaded
#pragma region

	static void IsLoaded_LogMessages(const FString &DataName, TArray<FString>& OutMessages);

	template<typename T>
	static bool IsLoadedMember(const FString& MemberName, T* &Internal)
	{
		if (Internal)
		{
			UE_LOG(LogLoad, Warning, TEXT("IsLoaded (%s)"), *MemberName);
			return true;
		}
		return false;
	}

	template<typename T>
	static bool IsLoadedMember(const FString& MemberName, TArray<T*> &Internal)
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
	static bool IsLoadedClassProperty(UClassProperty* &ClassProperty, void* InObject, const FString& MemberName)
	{
		if (T** Internal = ClassProperty->ContainerPtrToValuePtr<T*>(InObject))
			return IsLoadedMember<T>(MemberName, *Internal);
		return true;
	}

	template<typename T>
	static bool IsLoadedObjectProperty(UObjectProperty* &ObjectProperty, void* InObject, const FString& MemberName)
	{
		if (T** Internal = ObjectProperty->ContainerPtrToValuePtr<T*>(InObject))
			return IsLoadedMember<T>(MemberName, *Internal);
		return true;
	}

	template<typename T>
	static bool IsLoadedMemberStructProperty(UStructProperty* &StructProperty, void* InObject, const FString& MemberName)
	{
		T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject);
		return IsLoadedStructWithTSoftObjectPtrs(MemberName, (void*)Member, StructProperty->Struct);
	}
	/*
	template<typename T>
	static bool IsLoadedMemberFixedArrayStructProperty_Melee(UStructProperty* &StructProperty, void* InObject, const FString& MemberName)
	{
		if (T(*Member)[EMeleeType::EMeleeType_MAX] = StructProperty->ContainerPtrToValuePtr<T[EMeleeType::EMeleeType_MAX]>(InObject))
		{
			bool Pass		  = true;
			const int32 Count = (int32)EMeleeType::EMeleeType_MAX;

			for (int32 I = 0; I < Count; ++I)
			{
				const FString Index		  = MeleeTypeToString((TEnumAsByte<EMeleeType::Type>)I);
				const FString ElementName = MemberName + TEXT("[") + Index + TEXT("].");
				Pass &= IsLoadedStructWithTSoftObjectPtrs(ElementName, (void*)&((*Member)[I]), StructProperty->Struct);
			}
			return Pass;
		}
		return true;
	}
	*/
	/*
	template<typename T>
	static bool IsLoadedMemberFixedArrayStructProperty_Pickup(UStructProperty* &StructProperty, void* InObject, const FString& MemberName)
	{
		if (T(*Member)[EPickupItem::EPickupItem_MAX] = StructProperty->ContainerPtrToValuePtr<T[EPickupItem::EPickupItem_MAX]>(InObject))
		{
			bool Pass = true;
			const int32 Count = (int32)EPickupItem::EPickupItem_MAX;

			for (int32 I = 0; I < Count; ++I)
			{
				const FString Index		  = PickupItemToString((TEnumAsByte<EPickupItem::Type>)I);
				const FString ElementName = MemberName + TEXT("[") + Index + TEXT("].");
				Pass &= IsLoadedStructWithTSoftObjectPtrs(ElementName, (void*)&((*Member)[I]), StructProperty->Struct);
			}
			return Pass;
		}
		return true;
	}
	*/
	/*
	template<typename T>
	static bool IsLoadedMemberFixedArrayStructProperty_Surface(UStructProperty* &StructProperty, void* InObject, const FString& MemberName)
	{
		if (T(*Member)[ESurfaceType::ESurfaceType_MAX] = StructProperty->ContainerPtrToValuePtr<T[ESurfaceType::ESurfaceType_MAX]>(InObject))
		{
			bool Pass		  = true;
			const int32 Count = (int32)ESurfaceType::ESurfaceType_MAX;

			for (int32 I = 0; I < Count; ++I)
			{
				const FString Index		  = SurfaceTypeToString((TEnumAsByte<ESurfaceType::Type>)I);
				const FString ElementName = MemberName + TEXT("[") + Index + TEXT("].");
				Pass &= IsLoadedStructWithTSoftObjectPtrs(ElementName, (void*)&((*Member)[I]), StructProperty->Struct);
			}
			return Pass;
		}
		return true;
	}
	*/
	template<typename T>
	static bool IsLoadedMemberArrayStructProperty(UArrayProperty* &ArrayProperty, void* InObject, const FString& MemberName)
	{
		if (TArray<T>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<T>>(InObject))
		{
			bool Pass						= true;
			UStructProperty* StructProperty = Cast<UStructProperty>(ArrayProperty->Inner);
			const int32 Count				= Member->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const FString ElementName = MemberName + TEXT("[") + FString::FromInt(I) + TEXT("].");
				Pass &= IsLoadedStructWithTSoftObjectPtrs(ElementName, (void*)&((*Member)[I]), StructProperty->Struct);
			}
			return Pass;
		}
		return true;
	}

	template<typename T>
	static bool IsLoadedArrayObjectProperty(UArrayProperty* &ArrayProperty, void* InObject, const FString& MemberName)
	{
		if (TArray<T*>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<T*>>(InObject))
			return IsLoadedMember<T>(MemberName, *Member);
		return true;
	}

	static bool IsLoadedStructWithTSoftObjectPtrs(const FString &ObjectName, void* InStruct, UScriptStruct* const &InScriptStruct);
	static bool IsLoadedObjectWithTSoftObjectPtrs(const FString &ObjectName, void* InObject, UClass* const &InClass);

#pragma endregion IsLoaded

	static ECsLoadAsyncOrder GetLoadAsyncOrder();

	// Enum
#pragma region

#if WITH_EDITOR

	static void CheckEnumLoadFlags(int32* LoadFlags, const FString &ObjectName, const FString& MemberName);

	template<typename T>
	static void CheckEnumSoftObjectProperty(USoftObjectProperty* &SoftObjectProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString& MemberName)
	{
		if (TSoftObjectPtr<T>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<T>>(InObject))
		{
			// MemberName + TEXT("_LoadFlags")
			const FString LoadFlagsMemberName = MemberName + ECsLoadCached::Str::_LoadFlags;

			if (UProperty* LoadFlagsProperty = FindField<UProperty>(InClass, *LoadFlagsMemberName))
			{
				if (int32* LoadFlags = LoadFlagsProperty->ContainerPtrToValuePtr<int32>(InObject))
				{
					const FString FullLoadFlagsMemberName = ObjectName + ECsLoadCached::Str::_LoadFlags;

					CheckEnumLoadFlags(LoadFlags, FullLoadFlagsMemberName, LoadFlagsMemberName);
				}
			}
		}
	}

	template<typename T>
	static void CheckEnumSoftObjectProperty(USoftObjectProperty* &SoftObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString& MemberName)
	{
		if (TSoftObjectPtr<T>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<T>>(InObject))
		{
			// MemberName + TEXT("_LoadFlags")
			const FString LoadFlagsMemberName = MemberName + ECsLoadCached::Str::_LoadFlags;

			if (UProperty* LoadFlagsProperty = FindField<UProperty>(InClass, *LoadFlagsMemberName))
			{
				if (int32* LoadFlags = InternalProperty->ContainerPtrToValuePtr<int32>(InObject))
				{
					const FString FullLoadFlagsMemberName = ObjectName + ECsLoadCached::Str::_LoadFlags;

					CheckEnumLoadFlags(LoadFlags, FullLoadFlagsMemberName, LoadFlagsMemberName);
				}
			}
		}
	}

	template<typename T>
	static void CheckEnumArraySoftObjectProperty(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString& MemberName)
	{
		if (TArray<TSoftObjectPtr<T>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<T>>>(InObject))
		{
			// MemberName + TEXT("_LoadFlags")
			const FString LoadFlagsMemberName = MemberName + ECsLoadCached::Str::_LoadFlags;

			if (UProperty* LoadFlagsProperty = FindField<UProperty>(InClass, *LoadFlagsMemberName))
			{
				if (int32* LoadFlags = LoadFlagsProperty->ContainerPtrToValuePtr<int32>(InObject))
				{
					const FString FullLoadFlagsMemberName = ObjectName + ECsLoadCached::Str::_LoadFlags;

					CheckEnumLoadFlags(LoadFlags, FullLoadFlagsMemberName, LoadFlagsMemberName);
				}
			}
		}
	}

	template<typename T>
	static void CheckEnumStructProperty(UStructProperty* &StructProperty, void* InObject, const FString& MemberName, TCsCheckStructWithEnum_Internal Internal = nullptr)
	{
		if (T* Member = StructProperty->ContainerPtrToValuePtr<T>(InObject))
			CheckStructWithEnum(MemberName, (void*)Member, StructProperty->Struct, Internal);
	}

	template<typename T>
	static void CheckEnumArrayStructProperty(UArrayProperty* &ArrayProperty, void* InObject, const FString& MemberName)
	{
		if (TArray<T>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<T>>(InObject))
		{
			UStructProperty* StructProperty = Cast<UStructProperty>(ArrayProperty->Inner);

			const int32 Count = Member->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const FString ElementName = MemberName + TEXT("[") + FString::FromInt(I) + TEXT("]");
				CheckStructWithEnum(ElementName, (void*)&((*Member)[I]), StructProperty->Struct);
			}
		}
	}

	template<typename T>
	static void CheckEnumByteProperty(UByteProperty* &ByteProperty, void* InObject, const FString& MemberName, const T &Enum_MAX)
	{
		if (TEnumAsByte<T>* Member = ByteProperty->ContainerPtrToValuePtr<TEnumAsByte<T>>(InObject))
		{
			if (*Member == Enum_MAX)
				*Member = (T)0;
		}
	}

	static void CheckStructWithEnum(const FString &ObjectName, void* InStruct, UScriptStruct* const &InScriptStruct, TCsCheckStructWithEnum_Internal Internal = nullptr);
	static void CheckObjectWithEnum(const FString &ObjectName, void* InObject, UClass* const &InClass, TCsCheckObjectWithEnum_Internal Internal = nullptr);

#endif // #if WITH_EDITOR

#pragma endregion Enum

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

	static bool SetObjectMember(void* InObject, UClass* const &InClass, const FString& MemberName, void* MemberValue);
	static bool SetStructMember(void* InStruct, UScriptStruct* const &InScriptStruct, const FString& MemberName, void* MemberValue);

	static bool SetObjectMember(void* InObject, UClass* const &InClass, const uint16 &MemberIndex, void* MemberValue);
	static bool SetStructMember(void* InStruct, UScriptStruct* const &InScriptStruct, const uint16 &MemberIndex, void* MemberValue);

	static void SetObjectMembers(void* FromObject, void* ToObject, UClass* const &InClass, const TArray<FString>* MemberNames);

#pragma endregion Set

	// Get
#pragma region

	//static TEnumAsByte<EMemberType::Type> GetObjectMemberType(UClass* const &InClass, const FString& MemberName);
	//static TEnumAsByte<EMemberType::Type> GetStructMemberType(UScriptStruct* const &InScriptStruct, const FString& MemberName);

	static void* GetStructMemberEX(UProperty* Property, void* InStruct, UScriptStruct* const &InScriptStruct, const FString& MemberName);

	template<typename T>
	static T* GetStructMember(void* InStruct, UScriptStruct* const &InScriptStruct, const FString& MemberName, TCsGetStructMember_Internal Internal = nullptr)
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

	static UScriptStruct* GetScriptStructMember(void* InStruct, UScriptStruct* const &InScriptStruct, const FString& MemberName, TCsGetScriptStructMember_Internal Internal = nullptr);

	template<typename T>
	static T* GetObjectMember(void* InObject, UClass* const &InClass, const FString& MemberName, TCsGetObjectMember_Internal Internal = nullptr)
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

	static uint16 GetObjectMemberIndex(UClass* const &InClass, const FString& MemberName);

	static void GetObjectMembers(void* InObject, UClass* const &InClass, const TArray<FString>* MemberNames, TArray<void*> &OutMemberValues);

#pragma endregion Get

#pragma endregion Members

};