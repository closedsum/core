// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Type
#include "Data/Types/CsData_GetProjectileType.h"
// Log
#include "Utility/CsPrjLog.h"

#include "CsData_GetProjectileTypeImplSlice.generated.h"
#pragma once

// NCsProjectile::NData::NType::FImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NData, NType, FImplSlice)

/**
* Represents a "slice" of data, ICsGetProjectileType.
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsData_GetProjectileTypeImplSlice
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsProjectile Type;

public:

	FCsData_GetProjectileTypeImplSlice() :
		Type()
	{
	}

#define SliceType NCsProjectile::NData::NType::FImplSlice

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

#undef SliceType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

namespace NCsProjectile
{
	namespace NData
	{
		namespace NType
		{
			/**
			* Represents a "slice" of data, ICsGetProjectileType.
			* 
			* If members are set via points to an "owning" data, then
			* "Emulates" ICsData_GetProjectileType by mimicking 
			* the interfaces and having pointers to the appropriate members. 
			* 
			* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
			* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
			*/
			struct CSPRJ_API FImplSlice final : public ICsData_GetProjectileType
			{
			public:

				static const FName Name;

			private:

				// ICsGetInterfaceMap

				/** Pointer to the "root" object for all "Emu Slices". That object acts as the hub for the separate objects (via composition)
				that describe the data. */
				FCsInterfaceMap* InterfaceMap;

				// ICsData_GetProjectileType

				CS_DECLARE_MEMBER_WITH_PROXY(ProjectileType, FECsProjectile)

			public:

				FImplSlice() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// ICsData_GetProjectileType
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(ProjectileType)
				{
					CS_CTOR_SET_MEMBER_PROXY(ProjectileType);
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

			// ICsGetProjectileType
			#pragma region
			public:

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ProjectileType, FECsProjectile)

			#pragma endregion ICsGetProjectileType

			public:

				static void Deconstruct(void* Ptr)
				{
					delete static_cast<NCsProjectile::NData::NType::FImplSlice*>(Ptr);
				}

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

			#undef ParamsType
			};
		}
	}
}