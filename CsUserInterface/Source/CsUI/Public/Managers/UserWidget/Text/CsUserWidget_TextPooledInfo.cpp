// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Text/CsUserWidget_TextPooledInfo.h"

// Library
#include "Managers/UserWidget/Payload/CsLibrary_Payload_UserWidget.h"
#include "Library/CsLibrary_Valid.h"
// UserWidget
#include "Managers/UserWidget/Payload/CsPayload_UserWidgetImplSlice.h"
#include "Managers/UserWidget/Payload/Text/CsPayload_UserWidget_TextImplSlice.h"

#define InfoType NCsUserWidget::NText::FInfo

void FCsUserWidget_TextPooledInfo::CopyToInfo(InfoType* Info)
{
	Info->SetType(&Type);

	typedef NCsUserWidget::EDeallocateMethod DeallocateMethodType;

	Info->SetDeallocateMethod((DeallocateMethodType*)(&DeallocateMethod));
	Info->SetRenderScale(&RenderScale);
	Info->SetLifeTime(&LifeTime);
	Info->SetColor(&Color);
	OutlineSettings.CopyToSettings(Info->GetOutlineSettingsPtr());
	ShadowSettings.CopyToSettings(Info->GetShadowSettingsPtr());
}

void FCsUserWidget_TextPooledInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetType(Type);

	typedef NCsUserWidget::EDeallocateMethod DeallocateMethodType;

	Info->SetDeallocateMethod((DeallocateMethodType)(DeallocateMethod));
	Info->SetRenderScale(RenderScale);
	Info->SetLifeTime(LifeTime);
	Info->SetColor(Color);
	OutlineSettings.CopyToSettingsAsValue(Info->GetOutlineSettingsPtr());
	ShadowSettings.CopyToSettingsAsValue(Info->GetShadowSettingsPtr());
}

#undef InfoType

#define PayloadType NCsUserWidget::NPayload::IPayload

void FCsUserWidget_TextPooledInfo::SetPayloadChecked(const FString& Context, PayloadType* Payload) const
{
	CS_IS_PTR_NULL_CHECKED(Payload)
	
	check(IsValidChecked(Context));

	typedef NCsUserWidget::NPayload::FLibrary PayloadLibrary;

	if (PayloadLibrary::HasUniqueBasedSlices(Context, Payload))
	{
		FCsInterfaceMap* InterfaceMap		 = Payload->GetInterfaceMap();
		const TMap<FName, void*>& Interfaces = InterfaceMap->GetInterfaces();

		typedef NCsUserWidget::NPayload::FImplSlice SliceType;
		typedef NCsUserWidget::NPayload::NText::FImplSlice TextSliceType;

		checkf(Interfaces.Find(SliceType::Name), TEXT("%s: Payload does NOT contain Slice of type: %s."), *Context, *(SliceType::Name.ToString()));
		checkf(Interfaces.Find(TextSliceType::Name), TEXT("%s: Payload does NOT contain Slice of type: %s."), *Context, *(TextSliceType::Name.ToString()));

		for (const TPair<FName, void*>& Pair : Interfaces)
		{
			const FName& Name = Pair.Key;

			// SliceType (NCsPooledObject::NPayload::FImplSlice)
			if (Name == SliceType::Name)
			{
				SliceType* Slice = static_cast<SliceType*>(Pair.Value);

				Slice->RenderScale = RenderScale;
				Slice->LifeTime	   = LifeTime;
			}
			// TextSliceType (NCsUserWidget::NPayload::NText::FImplSlice)
			if (Name == TextSliceType::Name)
			{
				TextSliceType* Slice = static_cast<TextSliceType*>(Pair.Value);

				Slice->Color = Color;
				OutlineSettings.CopyToSettingsAsValue(Slice->GetOutlineSettingsPtr());
				ShadowSettings.CopyToSettingsAsValue(Slice->GetShadowSettingsPtr());
			}
		}
	}
	else
	{
		checkf(0, TEXT("%s: Payload is NOT supported."), *Context);
	}
}

bool FCsUserWidget_TextPooledInfo::SetSafePayload(const FString& Context, PayloadType* Payload, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	CS_IS_PTR_NULL(Payload)

	if (!IsValid(Context, Log))
		return false;

	typedef NCsUserWidget::NPayload::FLibrary PayloadLibrary;

	if (PayloadLibrary::HasUniqueBasedSlices(Context, Payload))
	{
		FCsInterfaceMap* InterfaceMap		 = Payload->GetInterfaceMap();
		const TMap<FName, void*>& Interfaces = InterfaceMap->GetInterfaces();

		typedef NCsUserWidget::NPayload::FImplSlice SliceType;

		if (!Interfaces.Find(SliceType::Name))
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Payload does NOT contain Slice of type: %s."), *Context, *(SliceType::Name.ToString())));
			return false;
		}

		typedef NCsUserWidget::NPayload::NText::FImplSlice TextSliceType;

		if (!Interfaces.Find(TextSliceType::Name))
		{	
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Payload does NOT contain Slice of type: %s."), *Context, *(TextSliceType::Name.ToString())));
			return false;
		}

		for (const TPair<FName, void*>& Pair : Interfaces)
		{
			const FName& Name = Pair.Key;

			// SliceType (NCsPooledObject::NPayload::FImplSlice)
			if (Name == SliceType::Name)
			{
				SliceType* Slice = static_cast<SliceType*>(Pair.Value);

				Slice->RenderScale = RenderScale;
				Slice->LifeTime = LifeTime;
			}
			// TextSliceType (NCsUserWidget::NPayload::NText::FImplSlice)
			if (Name == TextSliceType::Name)
			{
				TextSliceType* Slice = static_cast<TextSliceType*>(Pair.Value);

				Slice->Color = Color;
				OutlineSettings.CopyToSettingsAsValue(Slice->GetOutlineSettingsPtr());
				ShadowSettings.CopyToSettingsAsValue(Slice->GetShadowSettingsPtr());
			}
		}
	}
	else
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Payload is NOT supported."), *Context));
		return false;
	}
	return true;
}	

#undef PayloadType

bool FCsUserWidget_TextPooledInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUserWidgetPooled, Type);
	CS_IS_ENUM_VALID_CHECKED(EMCsUserWidgetDeallocateMethod, DeallocateMethod);
	CS_IS_FLOAT_GREATER_THAN_CHECKED(RenderScale, 0.0f)

	if (DeallocateMethod == ECsUserWidgetDeallocateMethod::LifeTime)
	{
		CS_IS_FLOAT_GREATER_THAN_CHECKED(LifeTime, 0.0f)
	}

	CS_IS_VALID_CHECKED(OutlineSettings);
	CS_IS_VALID_CHECKED(ShadowSettings);
	return true;
}

bool FCsUserWidget_TextPooledInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsUserWidgetPooled, FECsUserWidgetPooled, Type)
	CS_IS_ENUM_VALID(EMCsUserWidgetDeallocateMethod, ECsUserWidgetDeallocateMethod, DeallocateMethod)
	CS_IS_FLOAT_GREATER_THAN(RenderScale, 0.0f)

	if (DeallocateMethod == ECsUserWidgetDeallocateMethod::LifeTime)
	{
		CS_IS_FLOAT_GREATER_THAN(LifeTime, 0.0f)
	}

	CS_IS_VALID(OutlineSettings)
	CS_IS_VALID(ShadowSettings)
	return true;
}

namespace NCsUserWidget
{
	namespace NText
	{
		bool FInfo::IsValidChecked(const FString& Context) const
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUserWidgetPooled, GetType());

			typedef NCsUserWidget::EMDeallocateMethod DeallocateMethodMapType;

			CS_IS_ENUM_VALID_CHECKED(DeallocateMethodMapType, GetDeallocateMethod());
			CS_IS_FLOAT_GREATER_THAN_CHECKED(GetRenderScale(), 0.0f)

			typedef NCsUserWidget::EDeallocateMethod DeallocateMethodType;

			if (GetDeallocateMethod() == DeallocateMethodType::LifeTime)
			{
				CS_IS_FLOAT_GREATER_THAN_CHECKED(GetLifeTime(), 0.0f)
			}

			CS_IS_VALID_CHECKED(GetOutlineSettings());
			CS_IS_VALID_CHECKED(GetShadowSettings());
			return true;
		}

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsUserWidgetPooled, FECsUserWidgetPooled, GetType())

			typedef NCsUserWidget::EMDeallocateMethod DeallocateMethodMapType;
			typedef NCsUserWidget::EDeallocateMethod DeallocateMethodType;

			CS_IS_ENUM_VALID(DeallocateMethodMapType, DeallocateMethodType, GetDeallocateMethod())
			CS_IS_FLOAT_GREATER_THAN(GetRenderScale(), 0.0f)

			if (GetDeallocateMethod() == DeallocateMethodType::LifeTime)
			{
				CS_IS_FLOAT_GREATER_THAN(GetLifeTime(), 0.0f)
			}

			CS_IS_VALID(GetOutlineSettings())
			CS_IS_VALID(GetShadowSettings())
			return true;
		}
	}
}
