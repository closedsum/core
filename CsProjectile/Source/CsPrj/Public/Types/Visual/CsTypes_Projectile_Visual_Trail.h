// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Proxy.h"
#include "Managers/FX/CsTypes_FX.h"
// Log
#include "Utility/CsPrjLog.h"

#include "CsTypes_Projectile_Visual_Trail.generated.h"

// FCsProjectile_Visual_TrailInfo
#pragma region

// NCsProjectile::NVisual::NTrail::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NVisual, NTrail, FInfo)

/**
* Describes any information related to a Trail for a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectile_Visual_TrailInfo
{
	GENERATED_USTRUCT_BODY()

	/** The FX to spawn (and possibly attach). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Visual|Trail")
	FCsFX FX;

	/** Whether to set the Niagara Float Parameter associated with Scale. 
		This parameter will be set with the Collision Radius. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Visual|Trail", meta = (ScriptName = "m_bScaleParameterName", InlineEditConditionToggle))
	bool bScaleParameterName;

	/** The Niagara Float Parameter associated with Scale. 
		This parameter will be set with the Collision Radius. 
		NOTE: bScaleParameterName must be TRUE for this be used. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Visual|Trail", meta = (ScriptName = "m_ScaleParameterName", EditCondition = "bScaleParameterName"))
	FName ScaleParameterName;

	/** Whether to set the Niagara Float Parameter associated with Speed. 
		This parameter will be set with the Projectile's Current Speed (Usually this is Max Speed). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Visual|Trail", meta = (ScriptName = "m_bSpeedParameterName", InlineEditConditionToggle))
	bool bSpeedParameterName;

	/** The Niagara Float Parameter associated with Speed. 
		This parameter will be set with the Projectile's Current Speed (Usually this is Max Speed). 
		NOTE: bScaleParameterName must be TRUE for this be used. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Visual|Trail", meta = (ScriptName = "m_SpeedParameterName", EditCondition = "bSpeedParameterName"))
	FName SpeedParameterName;

public:

	FCsProjectile_Visual_TrailInfo() :
		FX(),
		bScaleParameterName(false),
		ScaleParameterName(NAME_None),
		bSpeedParameterName(false),
		SpeedParameterName(NAME_None)
	{
	}

#define InfoType NCsProjectile::NVisual::NTrail::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

namespace NCsProjectile
{
	namespace NVisual
	{
		namespace NTrail
		{
			struct CSPRJ_API FInfo
			{
			private:

				/** The FX to spawn (and possibly attach). */
				CS_DECLARE_MEMBER_WITH_PROXY(FX, FCsFX)
				/** Whether to set the Niagara Float Parameter associated with Scale. 
					This parameter will be set with the Collision Radius. */
				CS_DECLARE_MEMBER_WITH_PROXY(bScaleParameterName, bool)
				/** The Niagara Float Parameter associated with Scale. 
					This parameter will be set with the Collision Radius. 
					NOTE: GetbScaleParameterName() must be TRUE for this be used. */
				CS_DECLARE_MEMBER_WITH_PROXY(ScaleParameterName, FName)
				/** Whether to set the Niagara Float Parameter associated with Scale. 
					This parameter will be set with the Projectile's Current Speed (Usually this is Max Speed).  */
				CS_DECLARE_MEMBER_WITH_PROXY(bSpeedParameterName, bool)
				/** The Niagara Float Parameter associated with Scale. 
					This parameter will be set with the Projectile's Current Speed (Usually this is Max Speed). 
					NOTE: GetbSpeedParameterName() must be TRUE for this be used. */
				CS_DECLARE_MEMBER_WITH_PROXY(SpeedParameterName, FName)

			public:

				FInfo() :
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(FX),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bScaleParameterName, false),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(ScaleParameterName, NAME_None),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bSpeedParameterName, false),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(SpeedParameterName, NAME_None)
				{
					CS_CTOR_SET_MEMBER_PROXY(FX);
					CS_CTOR_SET_MEMBER_PROXY(bScaleParameterName);
					CS_CTOR_SET_MEMBER_PROXY(ScaleParameterName);
					CS_CTOR_SET_MEMBER_PROXY(bSpeedParameterName);
					CS_CTOR_SET_MEMBER_PROXY(SpeedParameterName);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(FX, FCsFX)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bScaleParameterName, bool)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ScaleParameterName, FName)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bSpeedParameterName, bool)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(SpeedParameterName, FName)

				void Copy(const FInfo& From)
				{
					SetFX(From.GetFX());
					SetbScaleParameterName(From.GetbScaleParameterName());
					SetScaleParameterName(From.GetScaleParameterName());
					SetbSpeedParameterName(From.GetbSpeedParameterName());
					SetSpeedParameterName(From.GetSpeedParameterName());
				}

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
			};
		}
	}
}

#pragma endregion FCsProjectile_Visual_TrailInfo