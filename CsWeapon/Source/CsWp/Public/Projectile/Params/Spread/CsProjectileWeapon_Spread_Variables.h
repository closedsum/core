// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
		{
			namespace NVariables
			{
				struct CSWP_API FVariables
				{
				public:

					TArray<FVector3f> Offsets;

					TArray<float> Yaws;
					TArray<float> Pitches;

					FVariables() :
						Offsets(),
						Yaws(),
						Pitches()
					{
					}

					void SetSizeAndAddDefaulted(const int32& Size)
					{
						Offsets.Reset(FMath::Max(Offsets.Max(), Size));
						Yaws.Reset(FMath::Max(Yaws.Max(), Size));
						Pitches.Reset(FMath::Max(Pitches.Max(), Size));

						for (int32 I = 0; I < Size; ++I)
						{
							Offsets.Add(FVector3f::ZeroVector);
							Yaws.Add(0.0f);
							Pitches.Add(0.0f);
						}
					}
				};

				struct CSWP_API FResource final : public TCsResourceContainer<FVariables>
				{
				};

				struct CSWP_API FManager final : public NCsResource::NManager::NValue::TFixed<FVariables, FResource, 0>
				{
				};
			}
		}
	}
}