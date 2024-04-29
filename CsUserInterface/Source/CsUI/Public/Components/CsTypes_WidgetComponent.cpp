// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Components/CsTypes_WidgetComponent.h"
#include "CsUI.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Component
#include "Components/SceneComponent.h"
// Engine
#include "GameFramework/Actor.h"

// FCsWidgetComponent_CameraInfo
#pragma region

#define InfoType NCsWidgetComponent::NCamera::FInfo

void FCsWidgetComponent_CameraInfo::CopyToInfo(InfoType* Info)
{
	CS_COPY_TO_PROXY(Info, LerpRate);
	CS_COPY_TO_PROXY(Info, LockAxes);
	CS_COPY_TO_PROXY(Info, Rotation);
}

void FCsWidgetComponent_CameraInfo::CopyToInfoAsValue(InfoType* Info) const
{
	CS_COPY_TO_PROXY_AS_VALUE(Info, LerpRate);
	CS_COPY_TO_PROXY_AS_VALUE(Info, LockAxes);
	CS_COPY_TO_PROXY_AS_VALUE(Info, Rotation);
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
	CS_COPY_CLASS_PTR_TO_PROXY(Info, Widget);
	CS_COPY_TO_PROXY(Info, bDrawSize);
	CS_COPY_TO_PROXY(Info, DrawSize);
	Info->SetAttachmentTransformRules(AttachmentTransformRules.ToRule());
	CS_COPY_TO_PROXY(Info, Bone);
	CS_COPY_TO_PROXY(Info, TransformRules);
	CS_COPY_TO_PROXY(Info, TransformSpaces);
	CS_COPY_TO_PROXY(Info, Transform);
	CS_COPY_TO_PROXY(Info, bCameraInfo);
	CS_COPY_INFO_TO_PROXY_PTR(Info, CameraInfo);
}

void FCsWidgetComponentInfo::CopyToInfoAsValue(InfoType* Info) const
{
	CS_COPY_CLASS_PTR_TO_PROXY_AS_VALUE(Info, Widget);
	CS_COPY_TO_PROXY_AS_VALUE(Info, bDrawSize);
	CS_COPY_TO_PROXY_AS_VALUE(Info, DrawSize);
	Info->SetAttachmentTransformRules(AttachmentTransformRules.ToRule());
	CS_COPY_TO_PROXY_AS_VALUE(Info, Bone);
	CS_COPY_TO_PROXY_AS_VALUE(Info, TransformRules);
	CS_COPY_TO_PROXY_AS_VALUE(Info, TransformSpaces);
	CS_COPY_TO_PROXY_AS_VALUE(Info, Transform);
	CS_COPY_TO_PROXY_AS_VALUE(Info, bCameraInfo);
	CS_COPY_INFO_TO_PROXY_PTR_AS_VALUE(Info, CameraInfo);
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

	void FInfo::AttachChecked(const FString& Context, USceneComponent* Parent, USceneComponent* Child, const FName& BoneOrSocket /*=NAME_None*/) const
	{
		CS_IS_PTR_NULL_CHECKED(Parent);

		Child->AttachToComponent(Parent, GetAttachmentTransformRules(), BoneOrSocket);
		SetTransform(Child);
	}

	void FInfo::AttachChecked(const FString& Context, AActor* Parent, USceneComponent* Child, const FName& BoneOrSocket /*=NAME_None*/) const
	{
		CS_IS_PTR_NULL_CHECKED(Parent)

		AttachChecked(Context, Parent->GetRootComponent(), Child, BoneOrSocket);
	}
}

#pragma endregion FCsWidgetComponentInfo