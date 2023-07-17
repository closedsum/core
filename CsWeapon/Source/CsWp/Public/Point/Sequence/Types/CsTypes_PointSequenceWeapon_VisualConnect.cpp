// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Sequence/Types/CsTypes_PointSequenceWeapon_VisualConnect.h"

// Library
#include "Library/CsLibrary_Valid.h"

// FCsPointSequenceWeapon_Visaul_Connect_FX_EndInfo
#pragma region

#define InfoType NCsWeapon::NPoint::NSequence::NVisual::NConnect::NFX::NEnd::FInfo

void FCsPointSequenceWeapon_Visaul_Connect_FX_EndInfo::CopyToInfo(InfoType* Info)
{
	Info->SetParameterName(&ParameterName);
	Info->SetOffset(&Offset);
}

void FCsPointSequenceWeapon_Visaul_Connect_FX_EndInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetParameterName(ParameterName);
	Info->SetOffset(Offset);
}

#undef InfoType

bool FCsPointSequenceWeapon_Visaul_Connect_FX_EndInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_NAME_NONE_CHECKED(ParameterName)
	return true;
}

bool FCsPointSequenceWeapon_Visaul_Connect_FX_EndInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_NAME_NONE(ParameterName)
	return true;
}

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
							bool FInfo::IsValidChecked(const FString& Context) const
							{
								CS_IS_NAME_NONE_CHECKED(GetParameterName())
								return true;
							}

							bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
							{
								CS_IS_NAME_NONE(GetParameterName())
								return true;
							}
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

#define InfoType NCsWeapon::NPoint::NSequence::NVisual::NConnect::NFX::FInfo

void FCsPointSequenceWeapon_Visaul_Connect_FXInfo::CopyToInfo(InfoType* Info)
{
	Info->SetFX(&FX);
	Info->SetbEndInfo(&bEndInfo);
	EndInfo.CopyToInfo(Info->GetEndInfoPtr());
}

void FCsPointSequenceWeapon_Visaul_Connect_FXInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetFX(FX);
	Info->SetbEndInfo(bEndInfo);
	EndInfo.CopyToInfoAsValue(Info->GetEndInfoPtr());
}

#undef InfoType

bool FCsPointSequenceWeapon_Visaul_Connect_FXInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(FX);

	if (bEndInfo)
	{
		CS_IS_VALID_CHECKED(EndInfo);
	}
	return true;
}

bool FCsPointSequenceWeapon_Visaul_Connect_FXInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_VALID(FX)

	if (bEndInfo)
	{
		CS_IS_VALID(EndInfo)
	}
	return true;
}

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
						bool FInfo::IsValidChecked(const FString& Context) const
						{
							CS_IS_VALID_CHECKED(GetFX());

							if (GetbEndInfo())
							{
								CS_IS_VALID_CHECKED(GetEndInfo());
							}
							return true;
						}

						bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
						{
							CS_IS_VALID(GetFX())

							if (GetbEndInfo())
							{
								CS_IS_VALID(GetEndInfo())
							}
							return true;
						}
					}
				}
			}
		}
	}
}

#pragma endregion FCsPointSequenceWeapon_Visaul_Connect_FXInfo

// FCsPointSequenceWeapon_Visual_ConnectInfo
#pragma region

#define InfoType NCsWeapon::NPoint::NSequence::NVisual::NConnect::FInfo

void FCsPointSequenceWeapon_Visual_ConnectInfo::CopyToInfo(InfoType* Info)
{
	Info->SetbFXInfo(&bFXInfo);
	FXInfo.CopyToInfo(Info->GetFXInfoPtr());
}

void FCsPointSequenceWeapon_Visual_ConnectInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetbFXInfo(bFXInfo);
	FXInfo.CopyToInfoAsValue(Info->GetFXInfoPtr());
}

#undef InfoType

bool FCsPointSequenceWeapon_Visual_ConnectInfo::IsValidChecked(const FString& Context) const
{
	if (bFXInfo)
	{
		CS_IS_VALID_CHECKED(FXInfo);
	}
	return true;
}

bool FCsPointSequenceWeapon_Visual_ConnectInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	if (bFXInfo)
	{
		CS_IS_VALID(FXInfo)
	}
	return true;
}

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
					bool FInfo::IsValidChecked(const FString& Context) const
					{
						if (GetbFXInfo())
						{
							CS_IS_VALID_CHECKED(GetFXInfo());
						}
						return true;
					}

					bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
					{
						if (GetbFXInfo())
						{
							CS_IS_VALID(GetFXInfo())
						}
						return true;
					}
				}
			}
		}
	}
}

#pragma endregion FCsPointSequenceWeapon_Visual_ConnectInfo