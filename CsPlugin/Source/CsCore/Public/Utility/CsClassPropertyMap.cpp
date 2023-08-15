// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsClassPropertyMap.h"
#include "CsCore.h"

#include "Engine/UserDefinedEnum.h"

#include "CoreUObject/Public/UObject/Object.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

// FCsClassPropertyMap
#pragma region

bool FCsClassPropertyMap::DoesMapExist(const FName& ClassName)
{
	return Map.Find(ClassName) != nullptr;
}

bool FCsClassPropertyMap::IsValidMap(const FName& ClassName)
{
	if (!DoesMapExist(ClassName))
		return false;

	const TMap<FName, TWeakFieldPtr<FProperty>>& ClassMap = Map[ClassName];

	for (const TPair<FName, TWeakFieldPtr<FProperty>>& Pair : ClassMap)
	{
		if (Pair.Value.IsValid() && Pair.Value.Get())
			return true;
		break;
	}
	return false;
}

void FCsClassPropertyMap::CreateMap(UClass* Class, const TArray<FName>& PropertyNames, const ECsStringCompare& CompareType)
{
	const FName ClassName = Class->GetFName();

	Map.Add(ClassName);

	TArray<FName> Names;

	for (const FName& Name : PropertyNames)
	{
		Names.Add(Name);
	}

	for (TFieldIterator<FProperty> It(Class); It; ++It)
	{
		FProperty* Property = CastField<FProperty>(*It);

		const FName PropertyName		   = Property->GetFName();
		const FString PropertyNameAsString = PropertyName.ToString();

		const int32 Count = Names.Num();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			const FName& Name		   = Names[I];
			const FString NameAsString = Name.ToString();

			// Equals
			if (CompareType == ECsStringCompare::Equals)
			{
				if (PropertyName == Name)
				{
					Map[ClassName].Add(Name, Property);
					Names.RemoveAt(I);
					break;
				}
			}
			// StartsWith
			else
			if (CompareType == ECsStringCompare::StartsWith)
			{
				if (PropertyNameAsString.StartsWith(NameAsString))
				{
					Map[ClassName].Add(Name, Property);
					Names.RemoveAt(I);
					break;
				}
			}
		}

		if (Names.Num() == CS_EMPTY)
			break;
	}

#if WITH_EDITOR
	for (const FName& Name : Names)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsClassPropertyMap::CreateMap: Failed to find PropertyName: %s for Class: %s."), *(Name.ToString()), *(ClassName.ToString()));
	}
#endif // #if WITH_EDITOR
}

void FCsClassPropertyMap::CreateSafeMap(UClass* Class, const TArray<FName>& PropertyNames, const ECsStringCompare& CompareType)
{
	const FName ClassName = Class->GetFName();

	if (IsValidMap(ClassName))
		return;

	if (Map.Find(ClassName))
		Map.Remove(ClassName);

	CreateMap(Class, PropertyNames, CompareType);
}

const TMap<FName, TWeakFieldPtr<FProperty>>& FCsClassPropertyMap::GetMap(const FName& ClassName)
{ 
	return Map[ClassName];
}

#pragma endregion FCsClassPropertyMap

// FCsClassInstancePropertyMap
#pragma region

bool FCsClassInstancePropertyMap::AreMapsCreated()
{
	return bMapsCreated;
}

void FCsClassInstancePropertyMap::CreateMaps(const FName& ClassName, void* Object)
{
	const TMap<FName, TWeakFieldPtr<FProperty>>& Map = FCsClassPropertyMap::Get().GetMap(ClassName);

	for (const TPair<FName, TWeakFieldPtr<FProperty>>& Pair : Map)
	{
		const FName& PropertyName   = Pair.Key;
		FProperty* Property			= Pair.Value.Get();

		// bool
		if (FBoolProperty* BoolProperty = CastField<FBoolProperty>(Property))
		{
			TCsBool_Ref* Bool_Ref = new TCsBool_Ref();

			Map_bool.Add(PropertyName, Bool_Ref);
			Map_bool[PropertyName]->Set(BoolProperty->ContainerPtrToValuePtr<bool>(Object));
			Map_bool[PropertyName]->Resolve();
			
			Maps[NCsMemberType::Bool].Add(PropertyName, Bool_Ref);
		}
		// int32
		if (FIntProperty* Int32Property = CastField<FIntProperty>(Property))
		{
			TCsInt32_Ref* Int32_Ref = new TCsInt32_Ref();

			Map_int32.Add(PropertyName, Int32_Ref);
			Map_int32[PropertyName]->Set(Int32Property->ContainerPtrToValuePtr<int32>(Object));
			Map_int32[PropertyName]->Resolve();
			
			Maps[NCsMemberType::Int32].Add(PropertyName, Int32_Ref);
		}
		// Byte / Enum (Regular or Namespaced/UserDefinedEnum)
		if (FByteProperty* ByteProperty = CastField<FByteProperty>(Property))
		{
			// UserDefinedEnum
			if (UUserDefinedEnum* Enum = Cast<UUserDefinedEnum>(ByteProperty->GetIntPropertyEnum()))
			{
				TCsUint8_Ref* Uint8_Ref = new TCsUint8_Ref();

				Map_EnumNamespaced.Add(PropertyName, Uint8_Ref);
				Map_EnumNamespaced[PropertyName]->Set(ByteProperty->ContainerPtrToValuePtr<uint8>(Object));
				Map_EnumNamespaced[PropertyName]->Resolve();

				Maps[NCsMemberType::EnumNamespaced].Add(PropertyName, Uint8_Ref);

				Map_UserDefinedEnum.Add(PropertyName, Enum);
			}
			CreateMaps_Byte(Object, ByteProperty, PropertyName);
		}
		// EnumClass
		else
		if (FEnumProperty* EnumProperty = CastField<FEnumProperty>(Property))
		{
			CreateMaps_Enum(Object, EnumProperty, PropertyName);
		}
		// Struct
		else
		if (FStructProperty* StructProperty = CastField<FStructProperty>(Property))
		{
			// FVector | FVector3d
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
			{
				TCsFVector_Ref* Vector_Ref = new TCsFVector_Ref();

				Map_Vector.Add(PropertyName, Vector_Ref);
				Map_Vector[PropertyName]->Set(StructProperty->ContainerPtrToValuePtr<FVector>(Object));
				Map_Vector[PropertyName]->Resolve();

				Maps[NCsMemberType::Vector].Add(PropertyName, Vector_Ref);
			}
		}
		// Object
		else
		if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
		{
			TCsObject_Ref* Object_Ref = new TCsObject_Ref();

			Map_Object.Add(PropertyName, Object_Ref);
			Map_Object[PropertyName]->Set(ObjectProperty->ContainerPtrToValuePtr<UObject*>(Object));
			Map_Object[PropertyName]->Resolve();
			
			Maps[NCsMemberType::Object].Add(PropertyName, Object_Ref);

			CreateMaps_Object(Object, ObjectProperty, PropertyName);

			// Actor
			if (ObjectProperty->PropertyClass->IsChildOf(AActor::StaticClass()))
			{
				TCsActor_Ref* Actor_Ref = new TCsActor_Ref();

				Map_Actor.Add(PropertyName, Actor_Ref);
				Map_Actor[PropertyName]->Set(ObjectProperty->ContainerPtrToValuePtr<AActor*>(Object));
				Map_Actor[PropertyName]->Resolve();

				Maps[NCsMemberType::Actor].Add(PropertyName, Actor_Ref);

				// Pawn
				if (ObjectProperty->PropertyClass->IsChildOf(APawn::StaticClass()))
				{
					TCsPawn_Ref* Pawn_Ref = new TCsPawn_Ref();

					Map_Pawn.Add(PropertyName, Pawn_Ref);
					Map_Pawn[PropertyName]->Set(ObjectProperty->ContainerPtrToValuePtr<APawn*>(Object));
					Map_Pawn[PropertyName]->Resolve();

					Maps[NCsMemberType::Pawn].Add(PropertyName, Pawn_Ref);
				}
			}
			// ActorComponent
			else
			if (ObjectProperty->PropertyClass->IsChildOf(UActorComponent::StaticClass()))
			{
				TCsActorComponent_Ref* ActorComponent_Ref = new TCsActorComponent_Ref();

				Map_ActorComponent.Add(PropertyName, ActorComponent_Ref);
				Map_ActorComponent[PropertyName]->Set(ObjectProperty->ContainerPtrToValuePtr<UActorComponent*>(Object));
				Map_ActorComponent[PropertyName]->Resolve();

				Maps[NCsMemberType::ActorComponent].Add(PropertyName, ActorComponent_Ref);

				// SceneComponent
				if (ObjectProperty->PropertyClass->IsChildOf(USceneComponent::StaticClass()))
				{
					TCsSceneComponent_Ref* SceneComponent_Ref = new TCsSceneComponent_Ref();

					Map_SceneComponent.Add(PropertyName, SceneComponent_Ref);
					Map_SceneComponent[PropertyName]->Set(ObjectProperty->ContainerPtrToValuePtr<USceneComponent*>(Object));
					Map_SceneComponent[PropertyName]->Resolve();

					Maps[NCsMemberType::SceneComponent].Add(PropertyName, SceneComponent_Ref);

					// PrimitiveComponent
					if (ObjectProperty->PropertyClass->IsChildOf(UPrimitiveComponent::StaticClass()))
					{
						TCsPrimitiveComponent_Ref* PrimitiveComponent_Ref = new TCsPrimitiveComponent_Ref();

						Map_PrimitiveComponent.Add(PropertyName, PrimitiveComponent_Ref);
						Map_PrimitiveComponent[PropertyName]->Set(ObjectProperty->ContainerPtrToValuePtr<UPrimitiveComponent*>(Object));
						Map_PrimitiveComponent[PropertyName]->Resolve();

						Maps[NCsMemberType::PrimitiveComponent].Add(PropertyName, PrimitiveComponent_Ref);

						// StaticMeshComponent
						if (ObjectProperty->PropertyClass->IsChildOf(UStaticMeshComponent::StaticClass()))
						{
							TCsStaticMeshComponent_Ref* StaticMeshComponent_Ref = new TCsStaticMeshComponent_Ref();

							Map_StaticMeshComponent.Add(PropertyName, StaticMeshComponent_Ref);
							Map_StaticMeshComponent[PropertyName]->Set(ObjectProperty->ContainerPtrToValuePtr<UStaticMeshComponent*>(Object));
							Map_StaticMeshComponent[PropertyName]->Resolve();

							Maps[NCsMemberType::StaticMeshComponent].Add(PropertyName, StaticMeshComponent_Ref);
						}
						else
						// SkeletalMeshComponent
						if (ObjectProperty->PropertyClass->IsChildOf(USkeletalMeshComponent::StaticClass()))
						{
							TCsSkeletalMeshComponent_Ref* SkeletalMeshComponent_Ref = new TCsSkeletalMeshComponent_Ref();

							Map_SkeletalMeshComponent.Add(PropertyName, SkeletalMeshComponent_Ref);
							Map_SkeletalMeshComponent[PropertyName]->Set(ObjectProperty->ContainerPtrToValuePtr<USkeletalMeshComponent*>(Object));
							Map_SkeletalMeshComponent[PropertyName]->Resolve();

							Maps[NCsMemberType::SkeletalMeshComponent].Add(PropertyName, SkeletalMeshComponent_Ref);
						}
					}
				}
			}
		}
	}
}

void FCsClassInstancePropertyMap::CreateMaps_Byte(void* Object, FByteProperty* ByteProperty, const FName& PropertyName)
{
}

void FCsClassInstancePropertyMap::CreateMaps_Enum(void* Object, FEnumProperty* EnumProperty, const FName& PropertyName)
{
}

void FCsClassInstancePropertyMap::CreateMaps_Object(void* Object, FObjectProperty* ObjectProperty, const FName& PropertyName)
{
}

void FCsClassInstancePropertyMap::CreateSafeMaps(const FName& ClassName, void* Object)
{
	if (bMapsCreated)
		return;

	CreateMaps(ClassName, Object);

	bMapsCreated = true;
}

bool FCsClassInstancePropertyMap::DoesPropertyExist(const FECsMemberType& MemberType, const FName& PropertyName)
{
	return Maps[MemberType].Find(PropertyName) != nullptr;
}

void FCsClassInstancePropertyMap::Resolve()
{
	for (const FECsMemberType& MemberType : EMCsMemberType::Get())
	{
		for (TPair<FName, ICsProperty*>& Pair : Maps[MemberType])
		{
			Pair.Value->Resolve();
		}
	}
}

	// Get
#pragma region

bool FCsClassInstancePropertyMap::GetValue_bool(const FName& PropertyName)
{
	return Map_bool[PropertyName]->Get();
}

bool FCsClassInstancePropertyMap::GetSafeValue_bool(const FName& PropertyName, bool& Success)
{
	Success = true;

	if (TCsBool_Ref** Value = Map_bool.Find(PropertyName))
		return (*Value)->Get();

	Success = false;
	return false;
}

int32 FCsClassInstancePropertyMap::GetValue_int32(const FName& PropertyName)
{
	return Map_int32[PropertyName]->Get();
}

int32 FCsClassInstancePropertyMap::GetSafeValue_int32(const FName& PropertyName, bool& Success)
{
	Success = true;

	if (TCsInt32_Ref** Value = Map_int32.Find(PropertyName))
		return (*Value)->Get();

	Success = false;
	return 0;
}

uint8 FCsClassInstancePropertyMap::GetValue_EnumNamespaced(const FName& PropertyName)
{
	return Map_EnumNamespaced[PropertyName]->Get();
}

uint8 FCsClassInstancePropertyMap::GetSafeValue_EnumNamespaced(const FName& PropertyName, bool& Success)
{
	Success = true;

	if (TCsUint8_Ref** Value = Map_EnumNamespaced.Find(PropertyName))
		return (*Value)->Get();

	Success = false;
	return 0L;
}

FVector FCsClassInstancePropertyMap::GetValue_Vector(const FName& PropertyName)
{
	return Map_Vector[PropertyName]->Get();
}

FVector FCsClassInstancePropertyMap::GetSafeValue_Vector(const FName& PropertyName, bool& Success)
{
	Success = true;

	if (TCsFVector_Ref** Value = Map_Vector.Find(PropertyName))
		return (*Value)->Get();

	Success = false;
	return FVector::ZeroVector;
}

UObject* FCsClassInstancePropertyMap::GetValue_Object(const FName& PropertyName)
{
	return Map_Object[PropertyName]->Get();
}

UObject* FCsClassInstancePropertyMap::GetSafeValue_Object(const FName& PropertyName, bool& Success)
{
	Success = true;

	if (TCsObject_Ref** Value = Map_Object.Find(PropertyName))
		return (*Value)->Get();

	Success = false;
	return nullptr;
}

AActor* FCsClassInstancePropertyMap::GetValue_Actor(const FName& PropertyName)
{
	return Map_Actor[PropertyName]->Get();
}

AActor* FCsClassInstancePropertyMap::GetSafeValue_Actor(const FName& PropertyName, bool& Success)
{
	Success = true;

	if (TCsActor_Ref** Value = Map_Actor.Find(PropertyName))
		return (*Value)->Get();

	Success = false;
	return nullptr;
}

APawn* FCsClassInstancePropertyMap::GetValue_Pawn(const FName& PropertyName)
{
	return Map_Pawn[PropertyName]->Get();
}

APawn* FCsClassInstancePropertyMap::GetSafeValue_Pawn(const FName& PropertyName, bool& Success)
{
	Success = true;

	if (TCsPawn_Ref** Value = Map_Pawn.Find(PropertyName))
		return (*Value)->Get();

	Success = false;
	return nullptr;
}

UActorComponent* FCsClassInstancePropertyMap::GetValue_ActorComponent(const FName& PropertyName)
{
	return Map_ActorComponent[PropertyName]->Get();
}

UActorComponent* FCsClassInstancePropertyMap::GetSafeValue_ActorComponent(const FName& PropertyName, bool& Success)
{
	Success = true;

	if (TCsActorComponent_Ref** Value = Map_ActorComponent.Find(PropertyName))
		return (*Value)->Get();

	Success = false;
	return nullptr;
}

USceneComponent* FCsClassInstancePropertyMap::GetValue_SceneComponent(const FName& PropertyName)
{
	return Map_SceneComponent[PropertyName]->Get();
}

USceneComponent* FCsClassInstancePropertyMap::GetSafeValue_SceneComponent(const FName& PropertyName, bool& Success)
{
	Success = true;

	if (TCsSceneComponent_Ref** Value = Map_SceneComponent.Find(PropertyName))
		return (*Value)->Get();

	Success = false;
	return nullptr;
}

UPrimitiveComponent* FCsClassInstancePropertyMap::GetValue_PrimitiveComponent(const FName& PropertyName)
{
	return Map_PrimitiveComponent[PropertyName]->Get();
}

UPrimitiveComponent* FCsClassInstancePropertyMap::GetSafeValue_PrimitiveComponent(const FName& PropertyName, bool& Success)
{
	Success = true;

	if (TCsPrimitiveComponent_Ref** Value = Map_PrimitiveComponent.Find(PropertyName))
		return (*Value)->Get();

	Success = false;
	return nullptr;
}

UStaticMeshComponent* FCsClassInstancePropertyMap::GetValue_StaticMeshComponent(const FName& PropertyName)
{
	return Map_StaticMeshComponent[PropertyName]->Get();
}

UStaticMeshComponent* FCsClassInstancePropertyMap::GetSafeValue_StaticMeshComponent(const FName& PropertyName, bool& Success)
{
	Success = true;

	if (TCsStaticMeshComponent_Ref** Value = Map_StaticMeshComponent.Find(PropertyName))
		return (*Value)->Get();

	Success = false;
	return nullptr;
}

USkeletalMeshComponent* FCsClassInstancePropertyMap::GetValue_SkeletalMeshComponent(const FName& PropertyName)
{
	return Map_SkeletalMeshComponent[PropertyName]->Get();
}

USkeletalMeshComponent* FCsClassInstancePropertyMap::GetSafeValue_SkeletalMeshComponent(const FName& PropertyName, bool& Success)
{
	Success = true;

	if (TCsSkeletalMeshComponent_Ref** Value = Map_SkeletalMeshComponent.Find(PropertyName))
		return (*Value)->Get();

	Success = false;
	return nullptr;
}

#pragma endregion Get

	// Set
#pragma region

void FCsClassInstancePropertyMap::SetValue_bool(const FName& PropertyName, const bool& Value)
{
	*(Map_bool[PropertyName]) = Value;
}

bool FCsClassInstancePropertyMap::SetSafeValue_bool(const FName& PropertyName, const bool& Value)
{
	if (TCsBool_Ref** Property = Map_bool.Find(PropertyName))
	{
		(**Property) = Value;
		return true;
	}
	return false;
}

void FCsClassInstancePropertyMap::SetValue_int32(const FName& PropertyName, const int32& Value)
{
	*(Map_int32[PropertyName]) = Value;
}

bool FCsClassInstancePropertyMap::SetSafeValue_int32(const FName& PropertyName, const int32& Value)
{
	if (TCsInt32_Ref** Property = Map_int32.Find(PropertyName))
	{
		(**Property) = Value;
		return true;
	}
	return false;
}

void FCsClassInstancePropertyMap::SetValue_EnumNamespaced(const FName& PropertyName, const uint8& Value)
{
	*(Map_EnumNamespaced[PropertyName]) = Value;
}

bool FCsClassInstancePropertyMap::SetSafeValue_EnumNamespaced(const FName& PropertyName, const uint8& Value)
{
	if (TCsUint8_Ref** Property = Map_EnumNamespaced.Find(PropertyName))
	{
		(**Property) = Value;
		return true;
	}
	return false;
}

void FCsClassInstancePropertyMap::SetValue_EnumNamespaced(const FName& PropertyName, const FName& EnumName)
{
	UUserDefinedEnum* Enum = Map_UserDefinedEnum[PropertyName];
	uint8 Value			   = (uint8)Enum->GetValueByName(EnumName);
	SetValue_EnumNamespaced(PropertyName, Value);
}

bool FCsClassInstancePropertyMap::SetSafeValue_EnumNamespaced(const FName& PropertyName, const FName& EnumName)
{
	UUserDefinedEnum* Enum = Map_UserDefinedEnum[PropertyName];
	uint8 Value			   = (uint8)Enum->GetValueByName(EnumName);
	return SetSafeValue_EnumNamespaced(PropertyName, Value);
}

void FCsClassInstancePropertyMap::SetValue_Vector(const FName& PropertyName, const FVector& Value)
{
	*(Map_Vector[PropertyName]) = Value;
}

bool FCsClassInstancePropertyMap::SetSafeValue_Vector(const FName& PropertyName, const FVector& Value)
{
	if (TCsFVector_Ref** Property = Map_Vector.Find(PropertyName))
	{
		(**Property) = Value;
		return true;
	}
	return false;
}

#pragma endregion Set

#pragma endregion FCsClassInstancePropertyMap