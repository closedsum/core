// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Log
#include "Utility/CsWpLog.h"
// Data
#include "Projectile/Data/CsData_ProjectileWeapon.h"

#include "CsData_ProjectileWeaponImplSlice.generated.h"
#pragma once

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDoFireOnRelease;

	/** Whether the Fire action continues to execute when the Fire action is
	    active. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bFullAuto;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInfiniteAmmo;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0", ClampMin = "0"))
	int32 MaxAmmo;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "1", ClampMin = "1"))
	int32 ProjectilesPerShot;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeBetweenShots;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeBetweenAutoShots;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeBetweenProjectilesPerShot;

	FCsData_ProjectileWeaponImplSlice() :
		bDoFireOnRelease(false),
		bFullAuto(false),
		bInfiniteAmmo(false),
		MaxAmmo(0),
		ProjectilesPerShot(1),
		TimeBetweenShots(0.0f),
		TimeBetweenAutoShots(0.0f),
		TimeBetweenProjectilesPerShot(0.0f)
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

				/** Pointer to the "root" object for all "Emu Slices". That object acts as the hub for the separate objects (via composition)
					that describe the data. */
				FCsInterfaceMap* InterfaceMap;

				// PrjWeaponDataType (NCsWeapon::NProjectile::NData::IData)

				CS_DECLARE_MEMBER_WITH_EMU(bDoFireOnRelease, bool)
				CS_DECLARE_MEMBER_WITH_EMU(bFullAuto, bool)
				CS_DECLARE_MEMBER_WITH_EMU(bInfiniteAmmo, bool)
				CS_DECLARE_MEMBER_WITH_EMU(MaxAmmo, int32)
				CS_DECLARE_MEMBER_WITH_EMU(ProjectilesPerShot, int32)
				CS_DECLARE_MEMBER_WITH_EMU(TimeBetweenShots, float)
				CS_DECLARE_MEMBER_WITH_EMU(TimeBetweenAutoShots, float)
				CS_DECLARE_MEMBER_WITH_EMU(TimeBetweenProjectilesPerShot, float)

				typedef NCsWeapon::NProjectile::NParams::NLaunch::ILaunch LaunchParamsType;

				LaunchParamsType* LaunchParams;
				FName LaunchParamsName;

			public:

				FImplSlice() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// PrjWeaponDataType (NCsWeapon::NProjectile::NData::IData)
					CS_CTOR_INIT_MEMBER_WITH_EMU(bDoFireOnRelease, false),
					CS_CTOR_INIT_MEMBER_WITH_EMU(bFullAuto, false),
					CS_CTOR_INIT_MEMBER_WITH_EMU(bInfiniteAmmo, false),
					CS_CTOR_INIT_MEMBER_WITH_EMU(MaxAmmo, 0),
					CS_CTOR_INIT_MEMBER_WITH_EMU(ProjectilesPerShot, 0),
					CS_CTOR_INIT_MEMBER_WITH_EMU(TimeBetweenShots, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_EMU(TimeBetweenAutoShots, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_EMU(TimeBetweenProjectilesPerShot, 0.0f),
					LaunchParams(nullptr),
					LaunchParamsName(NAME_None)
				{
					CS_CTOR_SET_MEMBER_EMU(bDoFireOnRelease);
					CS_CTOR_SET_MEMBER_EMU(bFullAuto);
					CS_CTOR_SET_MEMBER_EMU(bInfiniteAmmo);
					CS_CTOR_SET_MEMBER_EMU(MaxAmmo);
					CS_CTOR_SET_MEMBER_EMU(ProjectilesPerShot);
					CS_CTOR_SET_MEMBER_EMU(TimeBetweenShots);
					CS_CTOR_SET_MEMBER_EMU(TimeBetweenAutoShots);
					CS_CTOR_SET_MEMBER_EMU(TimeBetweenProjectilesPerShot);
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
					bDoFireOnRelease_Emu = &bDoFireOnRelease;
				}
				FORCEINLINE void SetDoFireOnRelease(bool* Value) { check(Value); bDoFireOnRelease_Emu = Value; }
				FORCEINLINE const bool& DoFireOnRelease() const { return *bDoFireOnRelease_Emu; }

				FORCEINLINE void SetFullAuto(const bool& Value) \
				{
					bFullAuto = Value;
					bFullAuto_Emu = &bFullAuto;
				}
				FORCEINLINE void SetFullAuto(bool* Value) { check(Value); bFullAuto_Emu = Value; }
				FORCEINLINE const bool& IsFullAuto() const { return *bFullAuto_Emu; }

				FORCEINLINE void SetInfiniteAmmo(const bool& Value) \
				{
					bInfiniteAmmo = Value;
					bInfiniteAmmo_Emu = &bInfiniteAmmo;
				}
				FORCEINLINE void SetInfiniteAmmo(bool* Value) { check(Value); bInfiniteAmmo_Emu = Value; }
				FORCEINLINE const bool& HasInfiniteAmmo() const { return *bInfiniteAmmo_Emu; }

				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(MaxAmmo, int32)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(ProjectilesPerShot, int32)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(TimeBetweenShots, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(TimeBetweenAutoShots, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(TimeBetweenProjectilesPerShot, float)

				FORCEINLINE const LaunchParamsType* GetLaunchParams() const { return LaunchParams; }

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