// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Core/Public/Containers/Map.h"
#include "UObject/WeakFieldPtr.h"

#include "Types/Property/Ref/CsProperty_Ref_bool.h"
#include "Types/Property/Ref/CsProperty_Ref_int32.h"
#include "Types/Property/Ref/CsProperty_Ref_uint8.h"
#include "Types/Property/Ref/CsProperty_Ref_Vector.h"
#include "Types/Property/Ref/Ptr/CsProperty_Ref_Object.h"
#include "Types/Property/Ref/Ptr/CsProperty_Ref_Actor.h"
#include "Types/Property/Ref/Ptr/CsProperty_Ref_Pawn.h"
#include "Types/Property/Ref/Ptr/CsProperty_Ref_ActorComponent.h"
#include "Types/Property/Ref/Ptr/CsProperty_Ref_SceneComponent.h"
#include "Types/Property/Ref/Ptr/CsProperty_Ref_PrimitiveComponent.h"
#include "Types/Property/Ref/Ptr/CsProperty_Ref_StaticMeshComponent.h"
#include "Types/Property/Ref/Ptr/CsProperty_Ref_SkeletalMeshComponent.h"
#include "Types/CsTypes_String.h"
#include "Types/CsTypes_Primitive.h"

class FProperty;
class FByteProperty;
class FEnumProperty;
class FObjectProperty;
class UUserDefinedEnum;
class UClass;
class UObject;
class AActor;
class APawn;
class ACharacter;

struct CSCORE_API FCsClassPropertyMap final
{
protected:
	TMap<FName, TMap<FName, TWeakFieldPtr<FProperty>>> Map;
protected:
	FCsClassPropertyMap() {}
	FCsClassPropertyMap(const FCsClassPropertyMap &) = delete;
	FCsClassPropertyMap(FCsClassPropertyMap &&) = delete;
public:
	~FCsClassPropertyMap() {}

	static FCsClassPropertyMap& Get()
	{
		static FCsClassPropertyMap Instance;
		return Instance;
	}

	bool DoesMapExist(const FName& ClassName);
	bool IsValidMap(const FName& ClassName);

	void CreateMap(UClass* Class, const TArray<FName>& PropertyNames, const ECsStringCompare& CompareType);
	void CreateSafeMap(UClass* Class, const TArray<FName>& PropertyNames, const ECsStringCompare& CompareType);

	const TMap<FName, TWeakFieldPtr<FProperty>>& GetMap(const FName& ClassName);
};

struct CSCORE_API FCsClassInstancePropertyMap
{
public:
	TMap<FName, TCsBool_Ref*> Map_bool;
	TMap<FName, TCsInt32_Ref*> Map_int32;
	TMap<FName, ICsProperty*> Map_EnumClass;
	TMap<FName, TCsUint8_Ref*> Map_EnumNamespaced;
	TMap<FName, TCsFVector_Ref*> Map_Vector;
	TMap<FName, TCsObject_Ref*> Map_Object;
	TMap<FName, TCsActor_Ref*> Map_Actor;
	TMap<FName, TCsPawn_Ref*> Map_Pawn;
	TMap<FName, TCsActorComponent_Ref*> Map_ActorComponent;
	TMap<FName, TCsSceneComponent_Ref*> Map_SceneComponent;
	TMap<FName, TCsPrimitiveComponent_Ref*> Map_PrimitiveComponent;
	TMap<FName, TCsStaticMeshComponent_Ref*> Map_StaticMeshComponent;
	TMap<FName, TCsSkeletalMeshComponent_Ref*> Map_SkeletalMeshComponent;

	TMap<FECsMemberType, TMap<FName, ICsProperty*>> Maps;

	TMap<FName, UUserDefinedEnum*> Map_UserDefinedEnum;

protected:
	bool bMapsCreated;
public:
	FCsClassInstancePropertyMap() :
		bMapsCreated(false)
	{
		for (const FECsMemberType& MemberType : EMCsMemberType::Get())
		{
			Maps.Add(MemberType);
		}
	}

	virtual ~FCsClassInstancePropertyMap()
	{
		for (const FECsMemberType& MemberType : EMCsMemberType::Get())
		{
			for (TPair<FName, ICsProperty*>& Pair : Maps[MemberType])
			{
				ICsProperty* Ref = Pair.Value;
				delete Ref;
				Pair.Value = nullptr;
			}
		}

		Maps.Reset();

		Map_bool.Reset();
		Map_int32.Reset();
		Map_EnumClass.Reset();
		Map_EnumNamespaced.Reset();
		Map_Vector.Reset();
		Map_Object.Reset();
		Map_Actor.Reset();
		Map_Pawn.Reset();
		Map_ActorComponent.Reset();
		Map_SceneComponent.Reset();
		Map_PrimitiveComponent.Reset();
		Map_StaticMeshComponent.Reset();
		Map_SkeletalMeshComponent.Reset();
	}

	bool AreMapsCreated();

	void CreateMaps(const FName& ClassName, void* Object);
	virtual void CreateMaps_Byte(void* Object, FByteProperty* ByteProperty, const FName& PropertyName);
	virtual void CreateMaps_Enum(void* Object, FEnumProperty* EnumProperty, const FName& PropertyName);
	virtual void CreateMaps_Object(void* Object, FObjectProperty* ObjectProperty, const FName& PropertyName);

	void CreateSafeMaps(const FName& ClassName, void* Object);

	bool DoesPropertyExist(const FECsMemberType& MemberType, const FName& PropertyName);

	void Resolve();

	// Get
#pragma region
public:

	bool GetValue_bool(const FName& PropertyName);
	bool GetSafeValue_bool(const FName& PropertyName, bool& Success);
	int32 GetValue_int32(const FName& PropertyName);
	int32 GetSafeValue_int32(const FName& PropertyName, bool& Success);

	template<typename EnumType>
	EnumType GetValue_EnumClass(const FName& PropertyName)
	{
		ICsProperty* Ref = Map_EnumClass.Find(PropertyName);
		TCsProperty_Ref<EnumType>* Enum_Ref = (TCsProperty_Ref<EnumType>*)(Ref);
		return Enum_Ref->Get();
	}

	template<typename EnumType>
	EnumType GetSafeValue_EnumClass(const FName& PropertyName, bool& Success)
	{
		Success = true;

		if (ICsProperty** Ref = Map_EnumClass.Find(PropertyName))
		{
			TCsProperty_Ref<EnumType>* Enum_Ref = (TCsProperty_Ref<EnumType>*)(*Ref);
			return Enum_Ref->Get();
		}
		return EnumType(0);
	}


	uint8 GetValue_EnumNamespaced(const FName& PropertyName);
	uint8 GetSafeValue_EnumNamespaced(const FName& PropertyName, bool& Success);

	FVector GetValue_Vector(const FName& PropertyName);
	FVector GetSafeValue_Vector(const FName& PropertyName, bool& Success);

	UObject* GetValue_Object(const FName& PropertyName);
	UObject* GetSafeValue_Object(const FName& PropertyName, bool& Success);
	AActor* GetValue_Actor(const FName& PropertyName);
	AActor* GetSafeValue_Actor(const FName& PropertyName, bool& Success);
	APawn* GetValue_Pawn(const FName& PropertyName);
	APawn* GetSafeValue_Pawn(const FName& PropertyName, bool& Success);
	UActorComponent* GetValue_ActorComponent(const FName& PropertyName);
	UActorComponent* GetSafeValue_ActorComponent(const FName& PropertyName, bool& Success);
	USceneComponent* GetValue_SceneComponent(const FName& PropertyName);
	USceneComponent* GetSafeValue_SceneComponent(const FName& PropertyName, bool& Success);
	UPrimitiveComponent* GetValue_PrimitiveComponent(const FName& PropertyName);
	UPrimitiveComponent* GetSafeValue_PrimitiveComponent(const FName& PropertyName, bool& Success);
	UStaticMeshComponent* GetValue_StaticMeshComponent(const FName& PropertyName);
	UStaticMeshComponent* GetSafeValue_StaticMeshComponent(const FName& PropertyName, bool& Success);
	USkeletalMeshComponent* GetValue_SkeletalMeshComponent(const FName& PropertyName);
	USkeletalMeshComponent* GetSafeValue_SkeletalMeshComponent(const FName& PropertyName, bool& Success);

#pragma endregion Get

	// Set
#pragma region
public:

	void SetValue_bool(const FName& PropertyName, const bool& Value);
	bool SetSafeValue_bool(const FName& PropertyName, const bool& Value);
	void SetValue_int32(const FName& PropertyName, const int32& Value);
	bool SetSafeValue_int32(const FName& PropertyName, const int32& Value);

	template<typename EnumType>
	void SetValue_EnumClass(const FName& PropertyName, const EnumType& Value)
	{
		ICsProperty* Ref = Map_EnumClass.Find(PropertyName);
		TCsProperty_Ref<EnumType>* Enum_Ref = (TCsProperty_Ref<EnumType>*)(Ref);

		*(Enum_Ref) = Value;
	}

	template<typename EnumType>
	bool SetSafeValue_EnumClass(const FName& PropertyName, const EnumType& Value)
	{
		if (ICsProperty** Ref = Map_EnumClass.Find(PropertyName))
		{
			TCsProperty_Ref<EnumType>* Enum_Ref = (TCsProperty_Ref<EnumType>*)(*Ref);

			*(Enum_Ref) = Value;
			return true;
		}
		return false;
	}

	void SetValue_EnumNamespaced(const FName& PropertyName, const uint8& Value);
	bool SetSafeValue_EnumNamespaced(const FName& PropertyName, const uint8& Value);
	void SetValue_EnumNamespaced(const FName& PropertyName, const FName& EnumName);
	bool SetSafeValue_EnumNamespaced(const FName& PropertyName, const FName& EnumName);

	void SetValue_Vector(const FName& PropertyName, const FVector& Value);
	bool SetSafeValue_Vector(const FName& PropertyName, const FVector& Value);

#pragma endregion Set
};