// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Projectile/Params/Shot/Projectile/CsParams_ProjectileWeapon_Shot_Projectile.h"
#include "Projectile/Params/Spread/CsParams_ProjectileWeapon_Spread.h"
// Log
#include "Utility/CsWpLog.h"
// Data
#include "Projectile/Data/CsData_ProjectileWeapon.h"

#include "CsData_ProjectileWeaponImplSlice.generated.h"

// NCsWeapon::NProjectile::NData::FImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWeapon, NProjectile, NData, FImplSlice)

/**
* Represents a "slice" of data, PrjWeaponDataType (NCsWeapon::NProjectile::NData::ICollision).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsData_ProjectileWeaponImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// CollisionDataType (NCsProjectile::NData::NCollision::IData)

	/** Whether to perform a Fire action on input pressed or released. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp|Projectile|Data")
	bool bDoFireOnRelease;

	/** Whether the Fire action continues to execute when the Fire action is
	    active. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp|Projectile|Data")
	bool bFullAuto;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp|Projectile|Data")
	bool bInfiniteAmmo;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp|Projectile|Data", meta = (UIMin = "0", ClampMin = "0"))
	int32 MaxAmmo;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp|Projectile|Data")
	float TimeBetweenShots;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp|Projectile|Data")
	float TimeBetweenAutoShots;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp|Projectile|Data")
	FCsProjectileWeapon_Shot_ProjectileParams ProjectilesPerShotParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp|Projectile|Data", meta = (ScriptName = "m_bSpreadParams"))
	bool bSpreadParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp|Projectile|Data", meta = (ScriptName = "m_SpreadParams"))
	FCsProjectileWeapon_SpreadParams SpreadParams;

	FCsData_ProjectileWeaponImplSlice() :
		bDoFireOnRelease(false),
		bFullAuto(false),
		bInfiniteAmmo(false),
		MaxAmmo(0),
		TimeBetweenShots(0.0f),
		TimeBetweenAutoShots(0.0f),
		ProjectilesPerShotParams(),
		bSpreadParams(false),
		SpreadParams()
	{
	}

#define SliceType NCsWeapon::NProjectile::NData::FImplSlice

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

// NCsWeapon::NProjectile::NParams::NLaunch::ILaunch
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NParams, NLaunch, ILaunch)

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{
			/**
			* Represents a "slice" of data, PrjWeaponDataType (NCsWeapon::NProjectile::NData::IData).
			*
			* If members are set via points to an "owning" data, then
			* "Emulates" PrjWeaponDataType (NCsWeapon::NProjectile::NData::IData) by mimicking
			* the interfaces and having pointers to the appropriate members.
			*
			* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
			* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
			*/
			struct CSWP_API FImplSlice : public IData
			{
			public:

				static const FName Name;

			private:

				// ICsGetInterfaceMap

				/** Pointer to the "root" object for all "Impl Slices". That object acts as the hub for the separate objects (via composition)
					that describe the data. */
				FCsInterfaceMap* InterfaceMap;

				// PrjWeaponDataType (NCsWeapon::NProjectile::NData::IData)

				CS_DECLARE_MEMBER_WITH_PROXY(bDoFireOnRelease, bool)
				CS_DECLARE_MEMBER_WITH_PROXY(bFullAuto, bool)
				CS_DECLARE_MEMBER_WITH_PROXY(bInfiniteAmmo, bool)
				CS_DECLARE_MEMBER_WITH_PROXY(MaxAmmo, int32)
				CS_DECLARE_MEMBER_WITH_PROXY(TimeBetweenShots, float)
				CS_DECLARE_MEMBER_WITH_PROXY(TimeBetweenAutoShots, float)

				typedef NCsWeapon::NProjectile::NShot::NProjectile::FParams ProjectilesPerShotParamsType;

				ProjectilesPerShotParamsType ProjectilesPerShotParams;

				typedef NCsWeapon::NProjectile::NParams::NLaunch::ILaunch LaunchParamsType;

				LaunchParamsType* LaunchParams;
				FName LaunchParamsName;

				CS_DECLARE_MEMBER_WITH_PROXY(bSpreadParams, bool)

				typedef NCsWeapon::NProjectile::NSpread::FParams SpreadParamsType;

				SpreadParamsType SpreadParams;

			public:

				FImplSlice() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// PrjWeaponDataType (NCsWeapon::NProjectile::NData::IData)
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bDoFireOnRelease, false),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bFullAuto, false),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bInfiniteAmmo, false),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(MaxAmmo, 0),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(TimeBetweenShots, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(TimeBetweenAutoShots, 0.0f),
					ProjectilesPerShotParams(),
					LaunchParams(nullptr),
					LaunchParamsName(NAME_None),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bSpreadParams, false),
					SpreadParams()
				{
					CS_CTOR_SET_MEMBER_PROXY(bDoFireOnRelease);
					CS_CTOR_SET_MEMBER_PROXY(bFullAuto);
					CS_CTOR_SET_MEMBER_PROXY(bInfiniteAmmo);
					CS_CTOR_SET_MEMBER_PROXY(MaxAmmo);
					CS_CTOR_SET_MEMBER_PROXY(TimeBetweenShots);
					CS_CTOR_SET_MEMBER_PROXY(TimeBetweenAutoShots);
					CS_CTOR_SET_MEMBER_PROXY(bSpreadParams);
				}

				~FImplSlice();

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			public:

				FORCEINLINE void SetInterfaceMap(FCsInterfaceMap* Map) { InterfaceMap = Map; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			public:

				template<typename T>
				FORCEINLINE T* ConstructLaunchParams()
				{
					T* ImplType		 = new T();
					LaunchParams	 = ImplType;
					LaunchParamsName = T::Name;
					return ImplType;
				}

			// PrjWeaponDataType (NCsWeapon::NProjectile::NData::IData)
			#pragma region
			public:

				FORCEINLINE void SetDoFireOnRelease(const bool& Value) \
				{
					bDoFireOnRelease = Value;
					bDoFireOnRelease_Proxy = &bDoFireOnRelease;
				}
				FORCEINLINE void SetDoFireOnRelease(bool* Value) { check(Value); bDoFireOnRelease_Proxy = Value; }
				FORCEINLINE const bool& DoFireOnRelease() const { return *bDoFireOnRelease_Proxy; }

				FORCEINLINE void SetFullAuto(const bool& Value) \
				{
					bFullAuto = Value;
					bFullAuto_Proxy = &bFullAuto;
				}
				FORCEINLINE void SetFullAuto(bool* Value) { check(Value); bFullAuto_Proxy = Value; }
				FORCEINLINE const bool& IsFullAuto() const { return *bFullAuto_Proxy; }

				FORCEINLINE void SetInfiniteAmmo(const bool& Value) \
				{
					bInfiniteAmmo = Value;
					bInfiniteAmmo_Proxy = &bInfiniteAmmo;
				}
				FORCEINLINE void SetInfiniteAmmo(bool* Value) { check(Value); bInfiniteAmmo_Proxy = Value; }
				FORCEINLINE const bool& HasInfiniteAmmo() const { return *bInfiniteAmmo_Proxy; }

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MaxAmmo, int32)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TimeBetweenShots, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TimeBetweenAutoShots, float)

				FORCEINLINE const ProjectilesPerShotParamsType& GetProjectilesPerShotParams() const { return ProjectilesPerShotParams; }
				FORCEINLINE ProjectilesPerShotParamsType* GetProjectilesPerShotParamsPtr() { return &ProjectilesPerShotParams; }

				FORCEINLINE const LaunchParamsType* GetLaunchParams() const { return LaunchParams; }

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bSpreadParams, bool)

				FORCEINLINE const bool& UseSpreadParams() const { return GetbSpreadParams(); }
				FORCEINLINE const SpreadParamsType& GetSpreadParams() const { return SpreadParams; }
				FORCEINLINE SpreadParamsType* GetSpreadParamsPtr() { return &SpreadParams; }

			#pragma endregion PrjWeaponDataType (NCsWeapon::NProjectile::NData::IData)

			public:

				static void Deconstruct(void* Ptr)
				{
					delete static_cast<NCsWeapon::NProjectile::NData::FImplSlice*>(Ptr);
				}

				static FImplSlice* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
			};
		}
	}
}