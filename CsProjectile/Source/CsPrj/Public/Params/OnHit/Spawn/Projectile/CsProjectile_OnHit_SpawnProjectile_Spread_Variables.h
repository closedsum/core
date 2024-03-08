// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"

namespace NCsProjectile
{
	namespace NOnHit
	{
		namespace NSpawn
		{
			namespace NProjectile
			{
				namespace NSpread
				{
					namespace NVariables
					{
						struct CSPRJ_API FVariables
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
								Offsets.AddDefaulted(Size);

								Yaws.Reset(FMath::Max(Yaws.Max(), Size));
								Yaws.AddDefaulted(Size);

								Pitches.Reset(FMath::Max(Pitches.Max(), Size));
								Pitches.AddDefaulted(Size);
							}
						};

						struct CSPRJ_API FResource final : public TCsResourceContainer<FVariables>
						{
						};

						struct CSPRJ_API FManager final : public NCsResource::NManager::NValue::TFixed<FVariables, FResource, 0>
						{
						};
					}
				}
			}
		}
	}
}