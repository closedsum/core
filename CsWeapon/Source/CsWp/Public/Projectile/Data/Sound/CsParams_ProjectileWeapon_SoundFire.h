// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Sound/CsTypes_Sound.h"
// Containers
#include "Containers/CsGetInterfaceMap.h"
// Log
#include "Utility/CsWpLog.h"

struct FCsInterfaceMap;

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{
			namespace NSound
			{
				namespace NFire
				{
					namespace NParams
					{
						// Attach
						#pragma region

						/**
						*/
						enum class EAttach
						{
							None,
							Owner,
							Component,
							Custom
						};

						#pragma endregion Attach

						/**
						*/
						struct CSWP_API IParams : virtual public ICsGetInterfaceMap
						{
						public:

							static const FName Name;

						public:

							virtual ~IParams(){}

							/**
							*/
							virtual const FCsSound& GetSound() const = 0;

							/**
							*/
							virtual const EAttach& GetAttachType() const = 0;
						};

						/**
						*/
						struct CSWP_API FImpl : public IParams
						{
						public:

							static const FName Name;

						private:

							// ICsGetInterfaceMap
						
							FCsInterfaceMap* InterfaceMap;

							// IParams

							FCsSound Sound;
							FCsSound* Sound_Emu;

							EAttach AttachType;
							EAttach* AttachType_Emu;

						public:

							FImpl();
							~FImpl();

						FORCEINLINE UObject* _getUObject() const { return nullptr; }

						// ICsGetInterfaceMap
						#pragma region
						public:

							FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

						#pragma endregion ICsGetInterfaceMap

						// IParams
						#pragma region
						public:

							CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Sound, FCsSound)
							CS_DEFINE_SET_GET_MEMBER_WITH_EMU(AttachType, EAttach)

						#pragma endregion IParams

						public:

							bool IsValidChecked(const FString& Context) const;
							bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
						};
					}
				}
			}
		}
	}
}