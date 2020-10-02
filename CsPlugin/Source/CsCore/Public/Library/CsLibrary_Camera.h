// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;

namespace NCsLibraryCameraCached
{
	namespace Str
	{
		//extern CSCORE_API const FString GetFirstLocalPlayerControllerChecked;
		//extern CSCORE_API const FString GetFirstLocalPlayerStateChecked;
		//extern CSCORE_API const FString GetFirstLocalPawnChecked;
	}
}

class CSCORE_API FCsLibrary_Camera
{
	/**
	*/
	static FVector GetLocation(UObject* Object);

	/**
	*/
	static FVector GetLocation(UObject* Object, const int32& Rules);

	/**
	*/
	static FVector GetLocationChecked(const FString& Context, UObject* Object);

	/**
	*/
	static FVector GetLocationChecked(UObject* Object);
};