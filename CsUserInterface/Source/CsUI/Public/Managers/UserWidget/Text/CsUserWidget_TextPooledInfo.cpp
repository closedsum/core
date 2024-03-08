// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/Text/CsUserWidget_TextPooledInfo.h"

// Library
#include "Managers/UserWidget/CsLibrary_Manager_UserWidget.h"
#include "Managers/UserWidget/Payload/CsLibrary_Payload_UserWidget.h"
#include "Library/CsLibrary_Viewport.h"
#include "Library/CsLibrary_Valid.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// UserWidget
#include "Managers/UserWidget/Payload/CsPayload_UserWidgetImplSlice.h"
#include "Managers/UserWidget/Payload/Text/CsPayload_UserWidget_TextImplSlice.h"

#define InfoType NCsUserWidget::NPooled::NText::FInfo

void FCsUserWidget_TextPooledInfo::CopyToInfo(InfoType* Info)
{
	Info->SetType(&Type);

	typedef NCsUserWidget::EDeallocateMethod DeallocateMethodType;

	Info->SetDeallocateMethod((DeallocateMethodType*)(&DeallocateMethod));
	Info->SetRenderScale(&RenderScale);
	Info->SetLifeTime(&LifeTime);
	Info->SetPositionType((NCsUserWidget::EPosition*)(&PositionType));
	Info->SetOffsetType((NCsUserWidget::EPosition*)(&OffsetType));
	Info->SetOffset(&Offset);
	Info->SetZOrder(&ZOrder);
	Info->SetColor(&Color);
	OutlineSettings.CopyToSettings(Info->GetOutlineSettingsPtr());
	ShadowSettings.CopyToSettings(Info->GetShadowSettingsPtr());
	Info->SetbAnimParams(&bAnimParams);
	AnimParams.CopyToParams(Info->GetAnimParamsPtr());
}

void FCsUserWidget_TextPooledInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetType(Type);

	typedef NCsUserWidget::EDeallocateMethod DeallocateMethodType;

	Info->SetDeallocateMethod((DeallocateMethodType)(DeallocateMethod));
	Info->SetRenderScale(RenderScale);
	Info->SetLifeTime(LifeTime);
	Info->SetPositionType((NCsUserWidget::EPosition)PositionType);
	Info->SetOffsetType((NCsUserWidget::EPosition)OffsetType);
	Info->SetOffset(Offset);
	Info->SetZOrder(ZOrder);
	Info->SetColor(Color);
	OutlineSettings.CopyToSettingsAsValue(Info->GetOutlineSettingsPtr());
	ShadowSettings.CopyToSettingsAsValue(Info->GetShadowSettingsPtr());
	Info->SetbAnimParams(bAnimParams);
	AnimParams.CopyToParamsAsValue(Info->GetAnimParamsPtr());
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
	CS_IS_ENUM_VALID_CHECKED(EMCsUserWidgetPosition, PositionType)
	CS_IS_ENUM_VALID_CHECKED(EMCsUserWidgetPosition, OffsetType)
	CS_IS_VALID_CHECKED(OutlineSettings);
	CS_IS_VALID_CHECKED(ShadowSettings);
	
	if (bAnimParams)
	{
		CS_IS_VALID_CHECKED(AnimParams);
	}
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

	CS_IS_ENUM_VALID(EMCsUserWidgetPosition, ECsUserWidgetPosition, PositionType)
	CS_IS_ENUM_VALID(EMCsUserWidgetPosition, ECsUserWidgetPosition, OffsetType)
	CS_IS_VALID(OutlineSettings)
	CS_IS_VALID(ShadowSettings)

	if (bAnimParams)
	{
		CS_IS_VALID(AnimParams)
	}
	return true;
}

namespace NCsUserWidget
{
	namespace NPooled
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

				CS_IS_ENUM_VALID_CHECKED(NCsUserWidget::EMPosition, GetPositionType())
				CS_IS_ENUM_VALID_CHECKED(NCsUserWidget::EMPosition, GetOffsetType())
				CS_IS_VALID_CHECKED(GetOutlineSettings());
				CS_IS_VALID_CHECKED(GetShadowSettings());

				if (GetbAnimParams())
				{
					CS_IS_VALID_CHECKED(GetAnimParams());
				}
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

				CS_IS_ENUM_VALID(NCsUserWidget::EMPosition, NCsUserWidget::EPosition, GetPositionType())
				CS_IS_ENUM_VALID(NCsUserWidget::EMPosition, NCsUserWidget::EPosition, GetOffsetType())
				CS_IS_VALID(GetOutlineSettings())
				CS_IS_VALID(GetShadowSettings())

				if (GetbAnimParams())
				{
					CS_IS_VALID(GetAnimParams())
				}
				return true;
			}

			const FCsUserWidgetPooled* FInfo::SpawnChecked(const FString& Context, const UObject* WorldContext, UObject* Instigator, UObject* Owner, const FText& Value, const FVector3f& Location) const
			{
				check(IsValidChecked(Context));

				typedef NCsUserWidget::NManager::FLibrary UserWidgetManagerLibrary;
				typedef NCsUserWidget::NPayload::FLibrary PayloadLibrary;
				typedef NCsUserWidget::NPayload::IPayload PayloadType;

				PayloadType* Payload = UserWidgetManagerLibrary::AllocatePayloadChecked(Context, WorldContext, GetType());

				// Pooled
				typedef NCsPooledObject::NPayload::IPayload PoolePayloadType;
				typedef NCsPooledObject::NPayload::FImplSlice PooledSliceType;

				PooledSliceType* PooledSlice = PayloadLibrary::StaticCastChecked<PooledSliceType, PoolePayloadType>(Context, Payload);

				PooledSlice->Instigator = Instigator;
				PooledSlice->Owner		= Owner;
				PooledSlice->PreserveChangesFromDefaultMask |= (uint32)NCsUserWidget::NPayload::EChange::AddedToViewport;

				// UserWidget
				typedef NCsUserWidget::NPayload::FImplSlice SliceType;

				SliceType* Slice = PayloadLibrary::StaticCastChecked<SliceType>(Context, Payload);

				Slice->bAddToViewport = true;
				Slice->Visibility	  = ESlateVisibility::HitTestInvisible;
				Slice->RenderScale	  = GetRenderScale();
				Slice->LifeTime		  = GetLifeTime();

				typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

				Slice->PositionType = GetPositionType();
				Slice->Position		= Location;
				Slice->OffsetType   = GetOffsetType();
				Slice->Offset		= GetOffset();

				if (GetPositionType() == NCsUserWidget::EPosition::Screen)
				{
					FVector3f WorldLocation = Location;

					if (GetOffsetType() == NCsUserWidget::EPosition::World)
					{
						WorldLocation += GetOffset();
					}

					FVector2f Pos;
					const bool Result = ViewportLibrary::ProjectWorldToScreenChecked(Context, WorldContext, Location, Pos);

					Slice->Position.X = Pos.X;
					Slice->Position.Y = Pos.Y;

					if (GetOffsetType() == NCsUserWidget::EPosition::Screen)
					{
						Slice->Position += GetOffset();
					}
				}
				Slice->ZOrder = GetZOrder();

				Slice->bAnimParams = GetbAnimParams();
				Slice->AnimParams.Copy(GetAnimParams());

				// NOTE: Not sure if the spawning should be skipped if the Position is off screen.
				// FUTURE: Add an option on whether the spawning should be "forced"
			
				//check(Result);

				// UserWidget Text
				typedef NCsUserWidget::NPayload::NText::IText TextPayloadType;
				typedef NCsUserWidget::NPayload::NText::FImplSlice TextSliceType;

				TextSliceType* TextSlice = PayloadLibrary::StaticCastChecked<TextSliceType, TextPayloadType>(Context, Payload);

				TextSlice->Text = Value;
				TextSlice->Color = GetColor();
				TextSlice->OutlineSettings.Copy(GetOutlineSettings());
				TextSlice->ShadowSettings.Copy(GetShadowSettings());

				return UserWidgetManagerLibrary::SpawnChecked(Context, WorldContext, GetType(), Payload);
			}

			const FCsUserWidgetPooled* FInfo::SpawnChecked(const FString& Context, const UObject* WorldContext, UObject* Instigator, UObject* Owner, const FString& Value, const FVector3f& Location) const
			{
				return SpawnChecked(Context, WorldContext, Instigator, Owner, FText::FromString(Value), Location);
			}

			const FCsUserWidgetPooled* FInfo::SpawnChecked(const FString& Context, const UObject* WorldContext, UObject* Instigator, UObject* Owner, const float& Value, const FVector3f& Location) const
			{
				return SpawnChecked(Context, WorldContext, Instigator, Owner, FString::Printf(TEXT("%f"), Value), Location);
			}

			const FCsUserWidgetPooled* FInfo::SpawnChecked(const FString& Context, const UObject* WorldContext, UObject* Instigator, UObject* Owner, const int32& Value, const FVector3f& Location) const
			{
				return SpawnChecked(Context, WorldContext, Instigator, Owner, FString::Printf(TEXT("%d"), Value), Location);
			}
		}
	}
}
