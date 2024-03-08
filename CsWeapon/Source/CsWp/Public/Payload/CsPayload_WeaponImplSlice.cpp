// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_WeaponImplSlice.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsWeapon::NPayload::FImplSlice::Name = FName("NCsWeapon::NPayload::FImplSlice");;

namespace NCsWeapon
{
	namespace NPayload
	{
		FImplSlice::FImplSlice() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// PayloadType (NCsWeapon::NPayload::IPayload)
			Type(),
			UpdateGroup(),
			Transform(FTransform3f::Identity)
		{
		}

		void FImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
		{
			checkf(InInterfaceMap, TEXT("NCsWeapon::NPayload::IPayload::SetInterfaceMap: InInterfaceMap is NULL."));

			checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("NCsWeapon::NPayload::IPayload::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

			InterfaceMap = InInterfaceMap;

			InterfaceMap->Add<IPayload>(FImplSlice::Name, static_cast<IPayload*>(this));
		}


		// ICsReset
		#pragma region

		void FImplSlice::Reset()
		{
			// IPayload
			Type		= EMCsWeapon::Get().GetMAX();
			UpdateGroup = EMCsUpdateGroup::Get().GetMAX();
			Transform	= FTransform3f::Identity;
		}

		#pragma endregion ICsReset

		bool FImplSlice::CopyFrom(const FImplSlice* From)
		{
			Type		= From->Type;
			UpdateGroup = From->UpdateGroup;
			Transform   = From->Transform;
			return true;
		}
	}
}