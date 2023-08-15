// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/FX/CsTypes_FX.h"
// Types
#include "Utility/CsWpLog.h"

#include "CsTypes_PointSequenceWeapon_VisualConnect.generated.h"

// FCsPointSequenceWeapon_Visaul_Connect_FX_EndInfo
#pragma region

// NCsWeapon::NPoint::NSequence::NVisual::NConnect::NFX::NEnd::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_7(NCsWeapon, NPoint, NSequence, NVisual, NConnect, NFX, NEnd, FInfo)

/**
* Describes any Visual End Point information related to Connect (connecting points in a sequence) FX
* for a Point Sequence Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsPointSequenceWeapon_Visaul_Connect_FX_EndInfo
{
	GENERATED_USTRUCT_BODY()

	/** Name of the Vector User Parameter associated with End Point of the FX. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Point|Sequence|Visual|Connect")
	FName ParameterName;

	/** Offset to apply to the End Point associated with Parameter Name. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Point|Sequence|Visual|Connect")
	FVector3f Offset;

public:

	FCsPointSequenceWeapon_Visaul_Connect_FX_EndInfo() :
		ParameterName(NAME_None),
		Offset(0.0f)
	{
	}

#define InfoType NCsWeapon::NPoint::NSequence::NVisual::NConnect::NFX::NEnd::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NVisual
			{
				namespace NConnect
				{
					namespace NFX
					{
						namespace NEnd
						{
							/**
							* Describes any Visual End Point information related to Connect (connecting points in a sequence) FX
							* for a Point Sequence Weapon.
							*  Weapon is an object that implements the interface: ICsWeapon.
							*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
							*/
							struct CSWP_API FInfo
							{
							private:

								/** Name of the Vector User Parameter associated with End Point of the FX. */
								CS_DECLARE_MEMBER_WITH_PROXY(ParameterName, FName)
								CS_DECLARE_MEMBER_WITH_PROXY(Offset, FVector3f)

							public:

								FInfo() :
									CS_CTOR_INIT_MEMBER_WITH_PROXY(ParameterName, NAME_None),
									CS_CTOR_INIT_MEMBER_WITH_PROXY(Offset, 0.0f)
								{
									CS_CTOR_SET_MEMBER_PROXY(ParameterName);
									CS_CTOR_SET_MEMBER_PROXY(Offset);
								}

								CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ParameterName, FName)
								CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Offset, FVector3f)

								void Copy(const FInfo& From)
								{
									SetParameterName(From.GetParameterName());
									SetOffset(From.GetOffset());
								}

								bool IsValidChecked(const FString& Context) const;
								bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
							};
						}
					}
				}
			}
		}
	}
}

#pragma endregion FCsPointSequenceWeapon_Visaul_Connect_FX_EndInfo

// FCsPointSequenceWeapon_Visaul_Connect_FXInfo
#pragma region

// NCsWeapon::NPoint::NSequence::NVisual::NConnect::NFX::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsWeapon, NPoint, NSequence, NVisual, NConnect, NFX, FInfo)

/**
* Describes any Visual information related to Connect (connecting points in a sequence) FX
* for a Point Sequence Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsPointSequenceWeapon_Visaul_Connect_FXInfo
{
	GENERATED_USTRUCT_BODY()

	/** FX for connecting to points in a Sequence. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Point|Sequence|Visual|Connect")
	FCsFX FX;

	/** Whether to use the information related to the End Point of the FX. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Point|Sequence|Visual|Connect", meta = (ScriptName = "m_bEndInfo", InlineEditConditionToggle))
	bool bEndInfo;

	/** Describes any information related to the End Point of the FX. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Point|Sequence|Visual|Connect", meta = (ScriptName = "m_EndInfo", EditCondition = "bEndInfo"))
	FCsPointSequenceWeapon_Visaul_Connect_FX_EndInfo EndInfo;

public:

	FCsPointSequenceWeapon_Visaul_Connect_FXInfo() :
		FX(),
		bEndInfo(true),
		EndInfo()
	{
	}

#define InfoType NCsWeapon::NPoint::NSequence::NVisual::NConnect::NFX::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NVisual
			{
				namespace NConnect
				{
					namespace NFX
					{
						struct CSWP_API FInfo
						{
						#define EndInfoType NCsWeapon::NPoint::NSequence::NVisual::NConnect::NFX::NEnd::FInfo

						private:

							/** FX for connecting to points in a Sequence. */
							CS_DECLARE_MEMBER_WITH_PROXY(FX, FCsFX)
							/** Whether to use the information related to the End Point of the FX. */
							CS_DECLARE_MEMBER_WITH_PROXY(bEndInfo, bool)
							/** Describes any information related to the End Point of the FX. */
							EndInfoType EndInfo;

						public:

							FInfo() :
								CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(FX),
								CS_CTOR_INIT_MEMBER_WITH_PROXY(bEndInfo, true),
								EndInfo()
							{
								CS_CTOR_SET_MEMBER_PROXY(FX);
								CS_CTOR_SET_MEMBER_PROXY(bEndInfo);
							}

							CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(FX, FCsFX)
							CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bEndInfo, bool)
							FORCEINLINE const EndInfoType& GetEndInfo() const { return EndInfo; }
							FORCEINLINE EndInfoType* GetEndInfoPtr() { return &EndInfo; }

							void Copy(const FInfo& From)
							{
								SetFX(From.GetFX());
								SetbEndInfo(From.GetbEndInfo());
								EndInfo.Copy(From.GetEndInfo());
							}

							bool IsValidChecked(const FString& Context) const;
							bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

						#undef EndInfoType
						};
					}
				}
			}
		}
	}
}

#pragma endregion FCsPointSequenceWeapon_Visaul_Connect_FXInfo

// FCsPointSequenceWeapon_Visual_ConnectInfo
#pragma region

// NCsWeapon::NPoint::NSequence::NVisual::NConnect::NFInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NPoint, NSequence, NVisual, NConnect, FInfo)

/**
* Describes any Visual information for Connecting points in a Sequence for a Point Sequence Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsPointSequenceWeapon_Visual_ConnectInfo
{
	GENERATED_USTRUCT_BODY()
	
	/** Whether to use FX Info or not when connecting points in a sequence. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (ScriptName = "m_bFXInfo", InlineEditConditionToggle))
	bool bFXInfo;

	/** Describes any Visual information related to Connect (connecting points in a sequence). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (ScriptName = "m_FXInfo", DisplayName = "FX Info", EditCondition = "bFXInfo"))
	FCsPointSequenceWeapon_Visaul_Connect_FXInfo FXInfo;

public:

	FCsPointSequenceWeapon_Visual_ConnectInfo() :
		bFXInfo(true),
		FXInfo()
	{
	}

#define InfoType NCsWeapon::NPoint::NSequence::NVisual::NConnect::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NVisual
			{
				namespace NConnect
				{
					struct CSWP_API FInfo
					{
					#define FXInfoType NCsWeapon::NPoint::NSequence::NVisual::NConnect::NFX::FInfo

					private:

						/** Whether to use FX Info or not when connecting points in a sequence. */
						CS_DECLARE_MEMBER_WITH_PROXY(bFXInfo, bool)
						/** Describes any Visual information related to Connect (connecting points in a sequence). */
						FXInfoType FXInfo;

					public:

						FInfo() :
							CS_CTOR_INIT_MEMBER_WITH_PROXY(bFXInfo, true),
							FXInfo()
						{
							CS_CTOR_SET_MEMBER_PROXY(bFXInfo);
						}

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bFXInfo, bool)
						FORCEINLINE const FXInfoType& GetFXInfo() const { return FXInfo; }
						FORCEINLINE FXInfoType* GetFXInfoPtr() { return &FXInfo; }

						void Copy(const FInfo& From)
						{
							SetbFXInfo(From.GetbFXInfo());
							FXInfo.Copy(From.GetFXInfo());
						}

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

					#undef FXInfoType
					};
				}
			}
		}
	}
}

#pragma endregion FCsPointSequenceWeapon_Visual_ConnectInfo