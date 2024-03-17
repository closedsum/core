// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Macro/CsMacro_Namespace.h"
#include "Managers/UserWidget/CsTypes_UserWidget.h"

// NCsUserWidget::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NPayload, IPayload)

namespace NCsWidgetActor
{
	namespace NPayload
	{ 
		/**
		*/
		struct CSUI_API IUserWidget : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IUserWidget(){}

		#define UserWidgetPayloadType NCsUserWidget::NPayload::IPayload

			/**
			* Get the UserWidgetPooled Type.
			*  "Spawn" (allocate) an object that implements the interface: ICsUserWidgetPooled 
			*   and contains a reference to a UUserObject from the type GetUserWidgetType() from Manager_UserWidget.
			*
			* return UserWidgetPooled type.
			*/
			virtual const FECsUserWidgetPooled& GetUserWidgetPooledType() const = 0;

			/**
			*
			*
			* return
			*/
			virtual UserWidgetPayloadType* GetUserWidgetPayload() const = 0;

		#undef UserWidgetPayloadType
		};
	}
}