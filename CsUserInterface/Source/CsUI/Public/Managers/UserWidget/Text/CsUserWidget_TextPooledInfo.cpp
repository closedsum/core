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

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsUserWidget_TextPooledInfo)

namespace NCsUserWidget_TextPooledInfo
{
	using DeallocateMethodType = NCsUserWidget::EDeallocateMethod;

	void FImpl::CopyToInfo(ThisType* This, InfoType* Info)
	{
		Info->SetType(&This->Type);
		Info->SetDeallocateMethod((DeallocateMethodType*)(&This->DeallocateMethod));
		Info->SetRenderScale(&This->RenderScale);
		Info->SetLifeTime(&This->LifeTime);
		Info->SetPositionType((NCsUserWidget::EPosition*)(&This->PositionType));
		Info->SetOffsetType((NCsUserWidget::EPosition*)(&This->OffsetType));
		Info->SetOffset(&This->Offset);
		Info->SetZOrder(&This->ZOrder);
		Info->SetColor(&This->Color);
		This->OutlineSettings.CopyToSettings(Info->GetOutlineSettingsPtr());
		This->ShadowSettings.CopyToSettings(Info->GetShadowSettingsPtr());
		Info->SetbAnimParams(&This->bAnimParams);
		This->AnimParams.CopyToParams(Info->GetAnimParamsPtr());
	}

	void FImpl::CopyToInfoAsValue(const ThisType* This, InfoType* Info)
	{
		Info->SetType(This->Type);
		Info->SetDeallocateMethod((DeallocateMethodType)(This->DeallocateMethod));
		Info->SetRenderScale(This->RenderScale);
		Info->SetLifeTime(This->LifeTime);
		Info->SetPositionType((NCsUserWidget::EPosition)This->PositionType);
		Info->SetOffsetType((NCsUserWidget::EPosition)This->OffsetType);
		Info->SetOffset(This->Offset);
		Info->SetZOrder(This->ZOrder);
		Info->SetColor(This->Color);
		This->OutlineSettings.CopyToSettingsAsValue(Info->GetOutlineSettingsPtr());
		This->ShadowSettings.CopyToSettingsAsValue(Info->GetShadowSettingsPtr());
		Info->SetbAnimParams(This->bAnimParams);
		This->AnimParams.CopyToParamsAsValue(Info->GetAnimParamsPtr());
	}

	using PayloadLibrary = NCsUserWidget::NPayload::NLibrary::FLibrary;
	using SliceType = NCsUserWidget::NPayload::NImpl::NSlice::FSlice;
	using TextSliceType = NCsUserWidget::NPayload::NText::NImpl::NSlice::FSlice;

	void FImpl::SetPayloadChecked(const ThisType* This, const FString& Context, PayloadType* Payload)
	{
		CS_IS_PTR_NULL_CHECKED(Payload)
	
		check(This->IsValidChecked(Context));

		if (PayloadLibrary::HasUniqueBasedSlices(Context, Payload))
		{
			FCsInterfaceMap* InterfaceMap		 = Payload->GetInterfaceMap();
			const TMap<FName, void*>& Interfaces = InterfaceMap->GetInterfaces();

			checkf(Interfaces.Find(SliceType::Name), TEXT("%s: Payload does NOT contain Slice of type: %s."), *Context, *(SliceType::Name.ToString()));
			checkf(Interfaces.Find(TextSliceType::Name), TEXT("%s: Payload does NOT contain Slice of type: %s."), *Context, *(TextSliceType::Name.ToString()));

			for (const TPair<FName, void*>& Pair : Interfaces)
			{
				const FName& Name = Pair.Key;

				// SliceType (NCsPooledObject::NPayload::FImplSlice)
				if (Name == SliceType::Name)
				{
					SliceType* Slice = static_cast<SliceType*>(Pair.Value);

					Slice->RenderScale = This->RenderScale;
					Slice->LifeTime	   = This->LifeTime;
				}
				// TextSliceType (NCsUserWidget::NPayload::NText::NImpl::NSlice::FSlice)
				if (Name == TextSliceType::Name)
				{
					TextSliceType* Slice = static_cast<TextSliceType*>(Pair.Value);

					Slice->Color = This->Color;
					This->OutlineSettings.CopyToSettingsAsValue(Slice->GetOutlineSettingsPtr());
					This->ShadowSettings.CopyToSettingsAsValue(Slice->GetShadowSettingsPtr());
				}
			}
		}
		else
		{
			checkf(0, TEXT("%s: Payload is NOT supported."), *Context);
		}
	}

	bool FImpl::SetSafePayload(const ThisType* This, const FString& Context, PayloadType* Payload, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
	{
		CS_IS_PTR_NULL(Payload)

		if (!This->IsValid(Context, Log))
			return false;

		if (PayloadLibrary::HasUniqueBasedSlices(Context, Payload))
		{
			FCsInterfaceMap* InterfaceMap		 = Payload->GetInterfaceMap();
			const TMap<FName, void*>& Interfaces = InterfaceMap->GetInterfaces();

			if (!Interfaces.Find(SliceType::Name))
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Payload does NOT contain Slice of type: %s."), *Context, *(SliceType::Name.ToString())));
				return false;
			}

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

					Slice->RenderScale = This->RenderScale;
					Slice->LifeTime    = This->LifeTime;
				}
				// TextSliceType (NCsUserWidget::NPayload::NText::NImipl::NSlice::FSlice)
				if (Name == TextSliceType::Name)
				{
					TextSliceType* Slice = static_cast<TextSliceType*>(Pair.Value);

					Slice->Color = This->Color;
					This->OutlineSettings.CopyToSettingsAsValue(Slice->GetOutlineSettingsPtr());
					This->ShadowSettings.CopyToSettingsAsValue(Slice->GetShadowSettingsPtr());
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
}

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
			using DeallocateMethodMapType = NCsUserWidget::EMDeallocateMethod ;

			using PoolePayloadType = NCsPooledObject::NPayload::IPayload;
			using PooledSliceType = NCsPooledObject::NPayload::FImplSlice;
			using PayloadLibrary = NCsUserWidget::NPayload::NLibrary::FLibrary;
			using PayloadType = NCsUserWidget::NPayload::IPayload;
			using SliceType = NCsUserWidget::NPayload::NImpl::NSlice::FSlice;
			using TextPayloadType = NCsUserWidget::NPayload::NText::IText;
			using TextSliceType = NCsUserWidget::NPayload::NText::NImpl::NSlice::FSlice;

			bool FInfo::IsValidChecked(const FString& Context) const
			{
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUserWidgetPooled, GetType());
				CS_IS_ENUM_VALID_CHECKED(DeallocateMethodMapType, GetDeallocateMethod());
				CS_IS_FLOAT_GREATER_THAN_CHECKED(GetRenderScale(), 0.0f)

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

				PayloadType* Payload = CsWidgetManagerLibrary::AllocatePayloadChecked(Context, WorldContext, GetType());

				// Pooled
				PooledSliceType* PooledSlice = PayloadLibrary::StaticCastChecked<PooledSliceType, PoolePayloadType>(Context, Payload);

				PooledSlice->Instigator = Instigator;
				PooledSlice->Owner		= Owner;
				PooledSlice->PreserveChangesFromDefaultMask |= (uint32)NCsUserWidget::NPayload::EChange::AddedToViewport;

				// UserWidget
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
				TextSliceType* TextSlice = PayloadLibrary::StaticCastChecked<TextSliceType, TextPayloadType>(Context, Payload);

				TextSlice->Text = Value;
				TextSlice->Color = GetColor();
				TextSlice->OutlineSettings.Copy(GetOutlineSettings());
				TextSlice->ShadowSettings.Copy(GetShadowSettings());

				return CsWidgetManagerLibrary::SpawnChecked(Context, WorldContext, GetType(), Payload);
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
