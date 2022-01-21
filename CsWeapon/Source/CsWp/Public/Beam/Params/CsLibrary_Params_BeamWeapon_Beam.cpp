// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Beam/Params/CsLibrary_Params_BeamWeapon_Beam.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NParams
		{
			namespace NBeam
			{
				#define ParamsType NCsWeapon::NBeam::NParams::NBeam::IBeam

				const bool FLibrary::IsValidChecked(const FString& Context, const ParamsType* Params)
				{
					CS_IS_PTR_NULL_CHECKED(Params)

					// Check LifeCycle is Valid
					typedef NCsWeapon::NBeam::NParams::NBeam::EMLifeCycle LifeCycleMapType;

					check(LifeCycleMapType::Get().IsValidEnumChecked(Context, Params->GetLifeCycle()));

					// Check Bone is Valid for appropriate Location Type
					typedef NCsWeapon::NBeam::NParams::NBeam::FLocationInfo LocationInfoType;
					typedef NCsWeapon::NBeam::NParams::NBeam::ELocation LocationType;

					const LocationInfoType& LocationInfo = Params->GetLocationInfo();

					if (LocationInfo.GetType() == LocationType::Bone ||
						LocationInfo.GetType() == LocationType::Socket)
					{
						checkf(LocationInfo.GetBoneOrSocket() != NAME_None, TEXT("%s: BoneOrSocket: None is NOT Valid when LocationInfo.GetType() == (ELocation::Bone | ELocation::Socket)."), *Context);
					}
					// Check Bone is Valid for appropriate Direction Type
					typedef NCsWeapon::NBeam::NParams::NBeam::FDirectionInfo DirectionInfoType;
					typedef NCsWeapon::NBeam::NParams::NBeam::EMDirection DirectionMapType;
					typedef NCsWeapon::NBeam::NParams::NBeam::EDirection DirectionType;

					const DirectionInfoType& DirectionInfo = Params->GetDirectionInfo();

					if (DirectionInfo.GetType() == DirectionType::Bone ||
						DirectionInfo.GetType() == DirectionType::Socket)
					{
						checkf(DirectionInfo.GetBoneOrSocket() != NAME_None, TEXT("%s: DirectionInfo.GetBoneOrSocket(): None is NOT Valid when DirectionInfo.GetType() == (EDirection::Bone | EDirection::Socket)."), *Context);

						checkf(DirectionInfo.GetRules() != 0, TEXT("%s: DirectionInfo>GetRules() should != 0 for GetType(): %s."), *Context, DirectionMapType::Get().ToChar(DirectionInfo.GetType()));
					}
					return true;
				}

				#undef ParamsType
			}
		}
	}
}