// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Sound/CsTypes_Sound.h"
#include "Engine/DataTable.h"
// Types
#include "Utility/CsPrjLog.h"

#include "CsTypes_Projectile_Sound_Impact.generated.h"

// FCsProjectile_Sound_ImpactInfo
#pragma region

// NCsProjectle::NImpact::NSound::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NImpact, NSound, FInfo)

/**
* Container holding Impact Visual FX information for a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectile_Sound_ImpactInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	TEnumAsByte<EPhysicalSurface> Surface;

	/** Whether to spawn Sound or not for the Surface Type associated with Impact Object. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (ScriptName = "m_bSound", InlineEditConditionToggle))
	bool bSound;

	/** Sound to spawn on Impact. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (ScriptName = "m_Sound", EditCondition = "bSound"))
	FCsSound Sound;

public:

	FCsProjectile_Sound_ImpactInfo() :
		Surface(EPhysicalSurface::SurfaceType_Default),
		bSound(false),
		Sound()
	{
	}

#define InfoType NCsProjectile::NImpact::NSound::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

namespace NCsProjectile
{
	namespace NImpact
	{
		namespace NSound
		{
			struct CSPRJ_API FInfo
			{
			private:

				CS_DECLARE_MEMBER_WITH_PROXY(Surface, EPhysicalSurface)
				/** Whether to spawn Sound or not for the Surface Type associated with Impact Object. */
				CS_DECLARE_MEMBER_WITH_PROXY(bSound, bool)
				/** Sound to spawn on Impact. */
				CS_DECLARE_MEMBER_WITH_PROXY(Sound, FCsSound)

			public:

				FInfo() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Surface, EPhysicalSurface::SurfaceType_Default),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bSound, false),
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Sound)
				{
					CS_CTOR_SET_MEMBER_PROXY(Surface);
					CS_CTOR_SET_MEMBER_PROXY(bSound);
					CS_CTOR_SET_MEMBER_PROXY(Sound);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Surface, EPhysicalSurface)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bSound, bool)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Sound, FCsSound)

				void Copy(const FInfo& From)
				{
					SetSurface(From.GetSurface());
					SetbSound(From.GetbSound());
					SetSound(From.GetSound());
				}

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
			};
		}
	}
}

#pragma endregion FCsProjectile_Sound_ImpactInfo