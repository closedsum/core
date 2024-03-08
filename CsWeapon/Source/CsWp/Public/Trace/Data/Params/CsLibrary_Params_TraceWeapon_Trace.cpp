// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/Data/Params/CsLibrary_Params_TraceWeapon_Trace.h"

#include "Types/CsTypes_Macro.h"

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NParams
		{
			namespace NTrace
			{
				#define ParamsType NCsWeapon::NTrace::NParams::NTrace::ITrace
				const bool FLibrary::IsValidChecked(const FString& Context, const ParamsType* Params)
				{
					checkf(Params, TEXT("%s: Params is NULL."), *Context);

					// Check Bone is Valid for appropriate Location Type
					const FLocationInfo& LocationInfo = Params->GetLocationInfo();

					if (LocationInfo.GetType() == ELocation::Bone ||
						LocationInfo.GetType() == ELocation::Socket)
					{
						checkf(LocationInfo.GetBoneOrSocket() != NAME_None, TEXT("%s: BoneOrSocket: None is NOT Valid when LocationInfo.GetType() == (ELocation::Bone | ELocation::Socket)."), *Context);
					}
					// Check Bone is Valid for appropriate Direction Type
					const FDirectionInfo& DirectionInfo = Params->GetDirectionInfo();

					if (DirectionInfo.GetType() == EDirection::Bone ||
						DirectionInfo.GetType() == EDirection::Socket)
					{
						checkf(DirectionInfo.GetBoneOrSocket() != NAME_None, TEXT("%s: BoneOrSocket: None is NOT Valid when DirectionInfo.GetType() == (EDirection::Bone | EDirection::Socket)."), *Context);
					}
					// Check ObjectTypes was set
					const TArray<ECollisionChannel>& ObjectTypes = Params->GetObjectTypes();

					const int32 Count = ObjectTypes.Num();
					// Check ObjectTyps are Valid
					checkf(Count > CS_EMPTY, TEXT("%s: No ObjectTypes set."), *Context);

					for (int32 I = 0; I < Count; ++I)
					{
						const ECollisionChannel& ObjectType = ObjectTypes[I];

						checkf(ObjectType != ECollisionChannel::ECC_OverlapAll_Deprecated && ObjectType != ECollisionChannel::ECC_MAX, TEXT("%s: ObjectTypes[%d] is NOT Valid (ECC_OverlapAll_Deprecated or ECC_MAX)."), *Context, I);
					}
					// Check Distance > 0.0f
					checkf(Params->GetDistance() > 0.0f, TEXT("%s: Distance must be > 0.0f."), *Context);
					return true;
				}
				#undef ParamsType
			}
		}
	}
}