// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Sound/CsTypes_Sound.h"
// Data
#include "Projectile/Data/Sound/Fire/CsData_ProjectileWeapon_SoundFire.h"
// Params
#include "Projectile/Data/Sound/Fire/CsTypes_ProjectileWeapon_SoundFire.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsData_ProjectileWeapon_SoundFireImplSlice.generated.h"

// NCsWeapon::NProjectile::NFire::NSound::FImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NFire, NSound, FImplSlice)

/**
* Represents a "slice" of data, SoundFireDataType (NCsWeapon::NProjectile::NData::NSound::NFire::IFire).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsData_ProjectileWeapon_SoundFireImplSlice
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsProjectileWeapon_Fire_SoundParams Params;

public:

	FCsData_ProjectileWeapon_SoundFireImplSlice() :
		Params()
	{
	}

#define SliceType NCsWeapon::NProjectile::NFire::NSound::FImplSlice

	SliceType* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);
	SliceType* AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

private:

	SliceType* AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

public:

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

#undef SliceType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

struct FCsInterfaceMap;

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NFire
		{
			namespace NSound
			{
			#define SoundFireDataType NCsWeapon::NProjectile::NData::NSound::NFire::IFire

				struct CSWP_API FImplSlice : public SoundFireDataType
				{
				public:

					static const FName Name;
						
				#define ParamsType NCsWeapon::NProjectile::NFire::NSound::FParams

				private:

					// ICsGetInterfaceMap

					/** Pointer to the "root" object for all "Impl Slices". That object acts as the hub for the separate objects (via composition)
						that describe the data. */
					FCsInterfaceMap* InterfaceMap;

				public:

					// SoundFireDataType (NCsWeapon::NProjectile::NData::NSound::NFire::IFire)

					ParamsType Params;

				public:

					FImplSlice() :
						InterfaceMap(nullptr),
						Params()
					{
					}
					~FImplSlice(){}

					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				public:

					FORCEINLINE void SetInterfaceMap(FCsInterfaceMap* Map) { InterfaceMap = Map; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				public:

					FORCEINLINE ParamsType* GetFireSoundParamsPtr() { return &Params; }

				// SoundFireDataType (NCsWeapon::NProjectile::NData::NSound::NFire::IFire)
				#pragma region
				public:

					FORCEINLINE const ParamsType& GetFireSoundParams() const { return Params; }

				#pragma endregion SoundFireDataType (NCsWeapon::NProjectile::NData::NSound::NFire::IFire)
					
				public:

					static void Deconstruct(void* Ptr)
					{
						delete static_cast<NCsWeapon::NProjectile::NFire::NSound::FImplSlice*>(Ptr);
					}

					static FImplSlice* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

				#undef ParamsType
				};

			#undef SoundFireDataType
			}
		}
	}
}