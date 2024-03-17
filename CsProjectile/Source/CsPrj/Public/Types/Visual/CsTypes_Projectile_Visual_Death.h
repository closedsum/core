// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Macro.h"
#include "Managers/FX/CsTypes_FX.h"
// Log
#include "Utility/CsPrjLog.h"

#include "CsTypes_Projectile_Visual_Death.generated.h"

// FCsProjectile_Visual_Death_FX_ScaleInfo
#pragma region

// NCsProjectile::NVisual::NDeath::NFX::NScale::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsProjectile, NVisual, NDeath, NFX, NScale, FInfo)

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectile_Visual_Death_FX_ScaleInfo
{
	GENERATED_USTRUCT_BODY()

	/** Name of the Float Niagara Parameter associated with Scale. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Visual|Death")
	FName ParameterName;

	/** Whether to scale the FX by the Collision Radius. 
		NOTE: If TRUE, Scale is ignored. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Visual|Death")
	bool bCollisionRadius;

	/** Multiplier to apply to Collision Radius.
		NOTE: Only used if bCollisionRadius is TRUE. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Visual|Deaht", meta = (EditCondition = "bCollisionRadius", UIMin = "0.0", ClampMin = "0.0"))
	float CollisionRadiusMultiplier;

public:

	FCsProjectile_Visual_Death_FX_ScaleInfo() :
		ParameterName(NAME_None),
		bCollisionRadius(true),
		CollisionRadiusMultiplier(1.0f)
	{
	}

#define InfoType NCsProjectile::NVisual::NDeath::NFX::NScale::FInfo
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
		namespace NDeath
		{
			namespace NFX
			{
				namespace NScale
				{
					struct CSPRJ_API FInfo
					{
					private:

						/** Name of the Float Niagara Parameter associated with Scale. */
						CS_DECLARE_MEMBER_WITH_PROXY(ParameterName, FName)
						/** Whether to scale the FX by the Collision Radius. 
							NOTE: If TRUE, Scale is ignored. */
						CS_DECLARE_MEMBER_WITH_PROXY(bCollisionRadius, bool)
						/** Multiplier to apply to Collision Radius.
							NOTE: Only used if bCollisionRadius is TRUE. */
						CS_DECLARE_MEMBER_WITH_PROXY(CollisionRadiusMultiplier, float)

					public:

						FInfo() :
							CS_CTOR_INIT_MEMBER_WITH_PROXY(ParameterName, NAME_None),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(bCollisionRadius, true),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(CollisionRadiusMultiplier, 1.0f)
						{
							CS_CTOR_SET_MEMBER_PROXY(ParameterName);
							CS_CTOR_SET_MEMBER_PROXY(bCollisionRadius);
							CS_CTOR_SET_MEMBER_PROXY(CollisionRadiusMultiplier);
						}

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ParameterName, FName)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bCollisionRadius, bool)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(CollisionRadiusMultiplier, float)

						void Copy(const FInfo& From)
						{
							SetParameterName(From.GetParameterName());
							SetbCollisionRadius(From.GetbCollisionRadius());
							SetCollisionRadiusMultiplier(From.GetCollisionRadiusMultiplier());
						}

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
					};
				}
			}
		}
	}
}

#pragma endregion FCsProjectile_Visual_Death_FX_ScaleInfo

// FCsProjectile_Visual_Death_FX_SpeedInfo
#pragma region

// NCsProjectile::NVisual::NDeath::NFX::NSpeed::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsProjectile, NVisual, NDeath, NFX, NSpeed, FInfo)

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectile_Visual_Death_FX_SpeedInfo
{
	GENERATED_USTRUCT_BODY()

	/** Name of the Float Niagara Parameter associated with Speed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Visual|Death")
	FName ParameterName;

public:

	FCsProjectile_Visual_Death_FX_SpeedInfo() :
		ParameterName(NAME_None)
	{
	}

#define InfoType NCsProjectile::NVisual::NDeath::NFX::NSpeed::FInfo
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
		namespace NDeath
		{
			namespace NFX
			{
				namespace NSpeed
				{
					struct CSPRJ_API FInfo
					{
					private:

						/** Name of the Float Niagara Parameter associated with Speed. */
						CS_DECLARE_MEMBER_WITH_PROXY(ParameterName, FName)

					public:

						FInfo() :
							CS_CTOR_INIT_MEMBER_WITH_PROXY(ParameterName, NAME_None)
						{
							CS_CTOR_SET_MEMBER_PROXY(ParameterName);
						}

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ParameterName, FName)

						void Copy(const FInfo& From)
						{
							SetParameterName(From.GetParameterName());
						}

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
					};
				}
			}
		}
	}
}

#pragma endregion FCsProjectile_Visual_Death_FX_SpeedInfo

// FCsProjectile_Visual_Death_FXInfo
#pragma region

// NCsProjectile::NVisual::NDeath::NFX::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsProjectile, NVisual, NDeath, NFX, FInfo)

/**
* Describes any FX information related to Death FX for a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectile_Visual_Death_FXInfo
{
	GENERATED_USTRUCT_BODY()

	/** FX to spawn on Death. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Visual|Death")
	FCsFX FX;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Visual|Death", meta = (ScriptName = "m_bScaleInfo", InlineEditConditionToggle))
	bool bScaleInfo;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Visual|Deaht", meta = (ScriptName = "m_ScaleInfo", EditCondition = "bScaleInfo"))
	FCsProjectile_Visual_Death_FX_ScaleInfo ScaleInfo;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Visual|Death", meta = (ScriptName = "m_bSpeedInfo", InlineEditConditionToggle))
	bool bSpeedInfo;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Visual|Deaht", meta = (ScriptName = "m_SpeedInfo", EditCondition = "bSpeedInfo"))
	FCsProjectile_Visual_Death_FX_SpeedInfo SpeedInfo;

public:

	FCsProjectile_Visual_Death_FXInfo() :
		FX(),
		bScaleInfo(false),
		ScaleInfo(),
		bSpeedInfo(false),
		SpeedInfo()
	{
	}

#define InfoType NCsProjectile::NVisual::NDeath::NFX::FInfo
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
		namespace NDeath
		{
			namespace NFX
			{
				/**
				* Describes any Visual information related to Death FX for a Projectile.
				*  Projectile is an object that implements the interface: ICsProjectile.
				*/
				struct CSPRJ_API FInfo
				{
				#define ScaleInfoType NCsProjectile::NVisual::NDeath::NFX::NScale::FInfo
				#define SpeedInfoType NCsProjectile::NVisual::NDeath::NFX::NSpeed::FInfo

				private:

					/** FX to spawn on Death. */
					CS_DECLARE_MEMBER_WITH_PROXY(FX, FCsFX)
					CS_DECLARE_MEMBER_WITH_PROXY(bScaleInfo, bool)
					ScaleInfoType ScaleInfo;
					CS_DECLARE_MEMBER_WITH_PROXY(bSpeedInfo, bool)
					SpeedInfoType SpeedInfo;

				public:

					FInfo() :
						CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(FX),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bScaleInfo, false),
						ScaleInfo(),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bSpeedInfo, false),
						SpeedInfo()
					{
						CS_CTOR_SET_MEMBER_PROXY(FX);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(FX, FCsFX)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bScaleInfo, bool)
					FORCEINLINE const ScaleInfoType& GetScaleInfo() const { return ScaleInfo; }
					FORCEINLINE ScaleInfoType* GetScaleInfoPtr() { return &ScaleInfo; }
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bSpeedInfo, bool)
					FORCEINLINE const SpeedInfoType& GetSpeedInfo() const { return SpeedInfo; }
					FORCEINLINE SpeedInfoType* GetSpeedInfoPtr() { return &SpeedInfo; }

					void Copy(const FInfo& From)
					{
						SetFX(From.GetFX());
						SetbScaleInfo(From.GetbScaleInfo());
						ScaleInfo.Copy(From.GetScaleInfo());
						SetbSpeedInfo(From.GetbSpeedInfo());
						SpeedInfo.Copy(From.GetSpeedInfo());
					}

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

				#undef ScaleInfoType
				#undef SpeedInfoType
				};
			}
		}
	}
}

#pragma endregion FCsProjectile_Visual_Death_FXInfo

// FCsProjectile_Visual_DeathInfo
#pragma region

// NCsProjectile::NVisual::NDeath::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NVisual, NDeath, FInfo)

/**
* Describes any Visual information related to Death for a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectile_Visual_DeathInfo
{
	GENERATED_USTRUCT_BODY()

	/** Whether to use the List of FX information related to Death. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Visual|Death", meta = (ScriptName = "m_bFXInfos", InlineEditConditionToggle))
	bool bFXInfos;

	/** List of FX information related to Death. 
		NOTE: bFXInfos must be TRUE for this information to be considered. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Visual|Death", meta = (DisplayName = "FX Infos", ScriptName = "m_FXInfos", EditCondition = "bFXInfos"))
	TArray<FCsProjectile_Visual_Death_FXInfo> FXInfos;

public:

	FCsProjectile_Visual_DeathInfo() :
		bFXInfos(false),
		FXInfos()
	{
	}

#define InfoType NCsProjectile::NVisual::NDeath::FInfo
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
		namespace NDeath
		{
			/**
			* Describes any Visual information related to Death for a Projectile.
			*  Projectile is an object that implements the interface: ICsProjectile.
			*/
			struct CSPRJ_API FInfo
			{
			#define FXInfoType NCsProjectile::NVisual::NDeath::NFX::FInfo

			private:

				/** Whether to use the List of FX information related to Death. */
				CS_DECLARE_MEMBER_WITH_PROXY(bFXInfos, bool)
				/** List of FX information related to Death. 
					NOTE: bFXInfos must be TRUE for this information to be considered. */
				TArray<FXInfoType> FXInfos;

			public:

				FInfo() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bFXInfos, false),
					FXInfos()
				{
					CS_CTOR_SET_MEMBER_PROXY(bFXInfos);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bFXInfos, bool)
				FORCEINLINE const TArray<FXInfoType>& GetFXInfos() const { return FXInfos; }
				FORCEINLINE TArray<FXInfoType>* GetFXInfosPtr() { return &FXInfos; }

				void Copy(const FInfo& From)
				{
					SetbFXInfos(From.GetbFXInfos());
					
					const int32 Count = From.GetFXInfos().Num();

					FXInfos.Reset(Count);

					for (int32 I = 0; I < Count; ++I)
					{
						FXInfoType& Info = FXInfos.AddDefaulted_GetRef();

						Info.Copy(From.GetFXInfos()[I]);
					}
				}

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

			#undef FXInfoType
			};
		}
	}
}

#pragma endregion FCsProjectile_Visual_DeathInfo