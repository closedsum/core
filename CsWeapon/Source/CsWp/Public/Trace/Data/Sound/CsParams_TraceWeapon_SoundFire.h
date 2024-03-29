// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

#include "Managers/Sound/CsTypes_SoundPooled.h"

struct FCsInterfaceMap;
class UObject;

namespace NCsWeapon
{
	namespace NTrace
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
						struct CSWP_API FProxy : public IParams
						{
						public:

							static const FName Name;

						private:

							// ICsGetInterfaceMap
						
							FCsInterfaceMap* InterfaceMap;

							// IParams

							FCsSound* Sound;

							EAttach* Attach;

						public:

							FProxy();
							~FProxy();

						FORCEINLINE UObject* _getUObject() const { return nullptr; }

						// ICsGetInterfaceMap
						#pragma region
						public:

							FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

						#pragma endregion ICsGetInterfaceMap

						public:

							FORCEINLINE void SetSound(FCsSound* Value){ Sound = Value; }
							FORCEINLINE void SetAttachType(EAttach* Value){ Attach = Value; }

						// IParams
						#pragma region
						public:

							FORCEINLINE const FCsSound& GetSound() const { return *Sound; }
							FORCEINLINE const EAttach& GetAttachType() const { return *Attach; }

						#pragma endregion IParams
						};
					}
				}
			}
		}
	}
}