// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Engine/NavigationObjectBase.h"
#include "CsAIStart.generated.h"

/** 
 *	This class indicates a location where a player can spawn when the game begins
 *	
 *	@see https://docs.unrealengine.com/latest/INT/Engine/Actors/PlayerStart/
 */
UCLASS(Blueprintable, ClassGroup=Common, hidecategories=Collision)
class CSCORE_API ACsAIStart : public ANavigationObjectBase
{
	GENERATED_BODY()
public:

	ACsAIStart(const FObjectInitializer& ObjectInitializer);

	/*~ To take more control over PlayerStart selection, you can override the virtual AGameModeBase::FindPlayerStart and AGameModeBase::ChoosePlayerStart functions. */

	/** Arrow component to indicate forward direction of start */
#if WITH_EDITORONLY_DATA
private:
	UPROPERTY()
	class UArrowComponent* ArrowComponent;
public:
#endif

#if WITH_EDITORONLY_DATA
	/** Returns ArrowComponent subobject **/
	class UArrowComponent* GetArrowComponent() const;
#endif
};
