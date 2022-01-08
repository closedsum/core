// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Collision/CsData_Projectile_CollisionImplSlice.h"

// Library
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Projectile
#include "Managers/Projectile/Handler/CsManager_Projectile_DataHandler.h"

#define SliceType NCsProjectile::NData::NCollision::FImplSlice

SliceType* FCsData_Projectile_CollisionImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSlice(Slice);

	return nullptr;
}

SliceType* FCsData_Projectile_CollisionImplSlice::AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSliceAsValue(Slice);

	return nullptr;
}

SliceType* FCsData_Projectile_CollisionImplSlice::AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&FCLog::Warning*/) const
{
	#define DataHandlerType NCsData::NManager::NHandler::TData
	typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;
	typedef NCsProjectile::NData::IData DataType;
	typedef NCsProjectile::NData::FInterfaceMap DataInterfaceMapType;
	
	DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* DataHandler = PrjManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
	
	#undef DataHandlerType

	if (!DataHandler)
		return nullptr;
	
	typedef NCsProjectile::NData::NCollision::ICollision CollisionDataType;
	
	SliceType* Slice = DataHandler->AddSafeDataSlice<SliceType, CollisionDataType>(Context, Name);
	
	return Slice;
}

void FCsData_Projectile_CollisionImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetCollisionPreset(&Preset);
	Slice->SetCollisionRadius(&Radius);
	Slice->SetHitCount(&HitCount);
	Slice->SetIgnoreHitObjectAfterHit(&bIgnoreHitObjectAfterHit);
	Slice->SetIgnoreHitObjectClasses(&IgnoreHitObjectClasses);
}

void FCsData_Projectile_CollisionImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetCollisionPreset(Preset);
	Slice->SetCollisionRadius(Radius);
	Slice->SetHitCount(HitCount);
	Slice->SetIgnoreHitObjectAfterHit(bIgnoreHitObjectAfterHit);
	Slice->SetIgnoreHitObjectClasses(IgnoreHitObjectClasses);
}

#undef SliceType

bool FCsData_Projectile_CollisionImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	if (!Preset.IsValid(Context, Log))
		return false;

	CS_IS_FLOAT_GREATER_THAN(Radius, 0.0f)

	CS_IS_INT_GREATER_THAN_OR_EQUAL(HitCount, 0)

	const int32 Count = IgnoreHitObjectClasses.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		const TSubclassOf<UObject>& O = IgnoreHitObjectClasses[I];

		if (!O.Get())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: IgnoreHitObjectClasses[%d] is NULL."), *Context, I));
		}
	}
	return true;
}

const FName NCsProjectile::NData::NCollision::FImplSlice::Name = FName("NCsProjectile::NData::NCollision::FImplSlice");

namespace NCsProjectile
{
	namespace NData
	{
		namespace NCollision
		{
			namespace NImplSlice
			{
				namespace NCached
				{
					namespace Name
					{
						const FName CollisionSlice = FName("CollisionSlice");

						const FName CollisionPreset = FName("CollisionPreset");
						const FName CollisionRadius = FName("CollisionRadius");
						const FName HitCount = FName("HitCount");
						const FName bIgnoreHitObjectAfterHit = FName("bIgnoreHitObjectAfterHit");
						const FName IgnoreHitObjectClasses = FName("IgnoreHitObjectClasses");
					}
				}
			}

			/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
			{
				using namespace NCsProjectile::NData::NCollision::NImplSlice::NCached;

				CS_IS_PTR_NULL_RET_NULL(Object)

				#define DataHandlerType NCsData::NManager::NHandler::TData
				typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;
				typedef NCsProjectile::NData::IData DataType;
				typedef NCsProjectile::NData::FInterfaceMap DataInterfaceMapType;

				DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* DataHandler = PrjManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
				
				#undef DataHandlerType

				if (!DataHandler)
					return nullptr;

				typedef NCsProjectile::NData::NCollision::ICollision CollisionDataType;

				FImplSlice* Slice = DataHandler->AddSafeDataSlice<FImplSlice, CollisionDataType>(Context, DataName);

				if (!Slice)
					return nullptr;

				// Check for properties matching interface: CollisionDataType (NCsProjectile::NData::NCollision::ICollision)
				typedef NCsProperty::FLibrary PropertyLibrary;

				bool Success = false;

				// Try FCsData_Projectile_CollisionImplSlice
				typedef FCsData_Projectile_CollisionImplSlice StructSliceType;

				if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::CollisionSlice, nullptr))
				{
					SliceAsStruct->CopyToSlice(Slice);
					Success = true;
				}
				// Try individual properties
				else
				{
					FCsCollisionPreset* CollisionPresetPtr = PropertyLibrary::GetStructPropertyValuePtr<FCsCollisionPreset>(Context, Object, Object->GetClass(), Name::CollisionPreset, nullptr);
					float* CollisionRadiusPtr			   = PropertyLibrary::GetFloatPropertyValuePtr(Context, Object, Object->GetClass(), Name::CollisionRadius, nullptr);
					int32* HitCountPtr					   = PropertyLibrary::GetIntPropertyValuePtr(Context, Object, Object->GetClass(), Name::HitCount, nullptr);
					bool* bIgnoreHitObjectAfterHitPtr	   = PropertyLibrary::GetBoolPropertyValuePtr(Context, Object, Object->GetClass(), Name::bIgnoreHitObjectAfterHit, nullptr);

					// TODO: Need to implement getting TArray<TSubclassOf<ClassType>>

					if (CollisionPresetPtr &&
						CollisionRadiusPtr &&
						HitCountPtr &&
						bIgnoreHitObjectAfterHitPtr)
					{
						Slice->SetCollisionPreset(CollisionPresetPtr);
						Slice->SetCollisionRadius(CollisionRadiusPtr);
						Slice->SetHitCount(HitCountPtr);
						Slice->SetIgnoreHitObjectAfterHit(bIgnoreHitObjectAfterHitPtr);

						Success = true;
					}
				}

				if (!Success)
				{
					if (Log)
					{
						typedef NCsObject::FLibrary ObjectLibrary;

						Log(FString::Printf(TEXT("%s: Failed to find any properties from %s for interface: CollisionDataType (NCsProjectile::NData::NCollision::ICollision)."), *Context, *(ObjectLibrary::PrintObjectAndClass(Object))));
						Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_Projectile_CollisionImplSlice with name: CollisionSlice."), *Context));
						Log(FString::Printf(TEXT("%s: - OR"), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsCollisionPreset with name: CollisionPreset."), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get float property with name: CollisionRadius."), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get int property with name: HitCount."), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get bool property with name: bIgnoreHitObjectAfterHit."), *Context));
						// Log(FString::Printf(TEXT("%s: - Failed to get array property of type: TSubclassOf<UObject> with name: IgnoreHitObjectClasses."), *Context));
					}
				}
				return Slice;
			}

			bool FImplSlice::IsValidChecked(const FString& Context) const
			{
				check(GetCollisionPreset().IsValidChecked(Context));

				CS_IS_FLOAT_GREATER_THAN_CHECKED(GetCollisionRadius(), 0.0f)

				CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(GetHitCount(), 0)

				const int32 Count = GetIgnoreHitObjectClasses().Num();

				for (int32 I = 0; I < Count; ++I)
				{
					const TSubclassOf<UObject>& O = GetIgnoreHitObjectClasses()[I];

					checkf(O.Get(), TEXT("%s: GetIgnoreHitObjectClasses()[%d] is NULL."), *Context, I);
				}
				return true;
			}

			bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&)/*=&NCsProjectile::FLog::Warning*/) const
			{
				if (!GetCollisionPreset().IsValid(Context, Log))
					return false;

				CS_IS_FLOAT_GREATER_THAN(GetCollisionRadius(), 0.0f)

				CS_IS_INT_GREATER_THAN_OR_EQUAL(GetHitCount(), 0)

				const int32 Count = GetIgnoreHitObjectClasses().Num();

				for (int32 I = 0; I < Count; ++I)
				{
					const TSubclassOf<UObject>& O = GetIgnoreHitObjectClasses()[I];

					if (!O.Get())
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetIgnoreHitObjectClasses()[%d] is NULL."), *Context, I));
					}
				}
				return true;
			}
		}
	}
}