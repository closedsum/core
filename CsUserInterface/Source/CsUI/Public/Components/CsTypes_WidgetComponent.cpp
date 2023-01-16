// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Components/CsTypes_WidgetComponent.h"
#include "CsUI.h"

// Library
#include "Library/CsLibrary_Valid.h"

// FCsWidgetComponent_CameraInfo
#pragma region

#define InfoType NCsWidgetComponent::NCamera::FInfo

void FCsWidgetComponent_CameraInfo::CopyToInfo(InfoType* Info)
{
	Info->SetLerpRate(&LerpRate);
	Info->SetLockAxes(&LockAxes);
	Info->SetRotation(&Rotation);
}

void FCsWidgetComponent_CameraInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetLerpRate(LerpRate);
	Info->SetLockAxes(LockAxes);
	Info->SetRotation(Rotation);
}

#undef InfoType

bool FCsWidgetComponent_CameraInfo::IsValidChecked(const FString& Context) const
{
	checkf(LockAxes == 7, TEXT("%s: LockAxes == 7 (Pitch | Yaw | Row). All Axes can NOT be locked when orienting to the Player Camera."), *Context);
	return true;
}

bool FCsWidgetComponent_CameraInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	if (LockAxes == 7)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: LockAxes == 7 (Pitch | Yaw | Row). All Axes can NOT be locked when orienting to the Player Camera."), *Context));
		return false;
	}
	return true;
}

namespace NCsWidgetComponent
{
	namespace NCamera
	{
		bool FInfo::IsValidChecked(const FString& Context) const
		{
			checkf(GetLockAxes() == 7, TEXT("%s: GetLockAxes() == 7 (Pitch | Yaw | Row). All Axes can NOT be locked when orienting to the Player Camera."), *Context);
			return true;
		}

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
		{
			if (GetLockAxes() == 7)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetLockAxes() == 7 (Pitch | Yaw | Row). All Axes can NOT be locked when orienting to the Player Camera"), *Context));
				return false;
			}
			return true;
		}
	}
}

#pragma endregion FCsWidgetComponent_CameraInfo

// FCsWidgetComponentInfo
#pragma region


#define InfoType NCsWidgetComponent::FInfo

void FCsWidgetComponentInfo::CopyToInfo(InfoType* Info)
{
	Info->SetWidget(Widget.GetClassPtr());
	Info->SetbDrawSize(&bDrawSize);
	Info->SetDrawSize(&DrawSize);
	Info->SetBone(&Bone);
	Info->SetTransformRules(&TransformRules);
	Info->SetTransformSpaces(&TransformSpaces);
	Info->SetTransform(&Transform);
	Info->SetbCameraInfo(&bCameraInfo);
	CameraInfo.CopyToInfo(Info->GetCameraInfoPtr());
}

void FCsWidgetComponentInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetWidget(Widget.GetClass());
	Info->SetbDrawSize(bDrawSize);
	Info->SetDrawSize(DrawSize);
	Info->SetBone(Bone);
	Info->SetTransformRules(TransformRules);
	Info->SetTransformSpaces(TransformSpaces);
	Info->SetTransform(Transform);
	Info->SetbCameraInfo(bCameraInfo);
	CameraInfo.CopyToInfoAsValue(Info->GetCameraInfoPtr());
}

#undef InfoType

bool FCsWidgetComponentInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Widget);

	if (bDrawSize)
	{
		checkf(DrawSize.X, TEXT("%s: If bDrawSize == True, DrawSize.X: %f MUST be > 0.0f."), *Context, DrawSize.X);
		checkf(DrawSize.Y, TEXT("%s: If bDrawSize == True, DrawSize.Y: %f MUST be > 0.0f."), *Context, DrawSize.Y);
	}

	if (bCameraInfo)
	{
		CS_IS_VALID_CHECKED(CameraInfo);
	}
	return true;
}

bool FCsWidgetComponentInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	CS_IS_VALID(Widget)

	if (bDrawSize)
	{
		if (DrawSize.X < 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: If bDrawSize == True, DrawSize.X: %f MUST be > 0.0f."), *Context, DrawSize.X));
			return false;
		}
		
		if (DrawSize.Y < 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: If bDrawSize == True, DrawSize.Y: %f MUST be > 0.0f."), *Context, DrawSize.Y));
			return false;
		}
	}

	if (bCameraInfo)
	{
		CS_IS_VALID(CameraInfo)
	}
	return true;
}

namespace NCsWidgetComponent
{
	bool FInfo::IsValidChecked(const FString& Context) const
	{
		CS_IS_PTR_NULL_CHECKED(GetWidget())

		if (GetbDrawSize())
		{
			checkf(GetDrawSize().X, TEXT("%s: If GetbDrawSize() == True, GetDrawSize().X: %f MUST be > 0.0f."), *Context, GetDrawSize().X);
			checkf(GetDrawSize().Y, TEXT("%s: If GetbDrawSize() == True, GetDrawSize().Y: %f MUST be > 0.0f."), *Context, GetDrawSize().Y);
		}

		if (GetbCameraInfo())
		{
			CS_IS_VALID_CHECKED(GetCameraInfo());
		}
		return true;
	}

	bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
	{
		CS_IS_PTR_NULL(GetWidget())

		if (GetbDrawSize())
		{
			if (GetDrawSize().X < 0.0f)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: If GetbDrawSize() == True, GetDrawSize().X: %f MUST be > 0.0f."), *Context, GetDrawSize().X));
				return false;
			}
		
			if (GetDrawSize().Y < 0.0f)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: If GetbDrawSize() == True, GetDrawSize().Y: %f MUST be > 0.0f."), *Context, GetDrawSize().Y));
				return false;
			}
		}

		if (GetbCameraInfo())
		{
			CS_IS_VALID(GetCameraInfo())
		}
		return true;
	}
}

#pragma endregion FCsWidgetComponentInfo