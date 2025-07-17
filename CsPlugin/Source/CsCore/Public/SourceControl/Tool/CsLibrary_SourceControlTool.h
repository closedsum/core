// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

namespace NCsSourceControl
{
	namespace NTool
	{
		struct CSCORE_API FLibrary
		{
		public:

			/**
			* Use currently set source control provider to check out a file.
			* @note	Blocks until action is complete.
			*
			* @param	Context		The Calling context.
			* @param	InFile		The file to check out - can be either fully qualified path, 
			*						relative path, long package name, asset path or export text path (often stored on clipboard)
			* @param	bSilent		(optional)	if false (default) then write out any error info to the Log. 
			*						Any error text can be retrieved by LastErrorMsg() regardless.
			* @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
			*/
			static bool CheckOutFileChecked(const FString& Context, const FString& InFile, bool bSilent=false);
		};
	}
}

using CsSourceControlToolLibrary = NCsSourceControl::NTool::FLibrary;