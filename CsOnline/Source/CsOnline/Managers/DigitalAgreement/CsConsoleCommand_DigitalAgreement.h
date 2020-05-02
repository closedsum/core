// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Misc/OutputDevice.h"
#pragma once

class UObject;
class UWorld;

class CSONLINE_API FCsConsoleCommand_DigitalAgreement
{
public:

	FCsConsoleCommand_DigitalAgreement(UObject* InRoot);

private:

	UObject* MyRoot;

public:

	bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Out = *GLog);

private:

	/**
	* Broadcasts the Reset action for all or specific Digital Agreement
	* Checks for the following console commands:
	* - DigitalAgreeementReset
	* - DigitalAgreement Reset
	* - DigitalAgreeementResetAll
	* - DigitalAgreeement ResetAll
	* - DigitalAgreement UA Reset
	* - DigitalAgreement PCP Reset
	*
	* @param Cmd	Console Command
	* return		Whether the console command was found / executed
	*/
	bool Exec_DigitalAgreementReset(const TCHAR* Cmd);

	/**
	* Broadcasts the Accept action for all or specific Digital Agreement
	* Checks for the following console commands:
	* - DigitalAgreeementAccept
	* - DigitalAgreement Accept
	* - DigitalAgreement UA Accept
	* - DigitalAgreement PCP Accept
	*
	* @param Cmd	Console Command
	* return		Whether the console command was found / executed
	*/
	bool Exec_DigitalAgreementAccept(const TCHAR* Cmd);

	/**
	* Broadcasts the Do Not Accept action for all or specific Digital Agreement
	* Checks for the following console commands:
	* - DigitalAgreeementDoNotAccept
	* - DigitalAgreement DoNotAccept
	* - DigitalAgreement UA DoNotAccept
	* - DigitalAgreement PCP DoNotAccept
	*
	* @param Cmd	Console Command
	* return		Whether the console command was found / executed
	*/
	bool Exec_DigitalAgreementDoNotAccept(const TCHAR* Cmd);

	/**
	* Broadcast the User Agreement - Reset action
	* Checks for the following console commands:
	* - UserAgreementReset
	* - UserAgreement Reset
	*
	* @param Cmd	Console Command
	* return		Whether the console command was found / executed
	*/
	bool Exec_UserAgreementReset(const TCHAR* Cmd);

	/**
	* Broadcast the User Agreement - Accept action
	* Checks for the following console commands:
	* - UserAgreementAccept
	* - UserAgreement Accept
	*
	* @param Cmd	Console Command
	* return		Whether the console command was found / executed
	*/
	bool Exec_UserAgreementAccept(const TCHAR* Cmd);

	/**
	* Broadcast the User Agreement - Do Not Accept action
	* Checks for the following console commands:
	* - UserAgreementDoNotAccept
	* - UserAgreement DoNotAccept
	*
	* @param Cmd	Console Command
	* return		Whether the console command was found / executed
	*/
	bool Exec_UserAgreementDoNotAccept(const TCHAR* Cmd);

	/**
	* Broadcast the Privacy and Cookie Policy - Reset action
	* Checks for the following console commands:
	* - PrivacyAndCookiePolicyReset
	* - PrivacyAndCookiePolicy Reset
	*
	* @param Cmd	Console Command
	* return		Whether the console command was found / executed
	*/
	bool Exec_PrivacyAndCookiePolicyReset(const TCHAR* Cmd);

	/**
	* Broadcast the Privacy and Cookie Policy - Accept action
	* Checks for the following console commands:
	* - PrivacyAndCookiePolicyAccept
	* - PrivacyAndCookiePolicy Accept
	*
	* @param Cmd	Console Command
	* return		Whether the console command was found / executed
	*/
	bool Exec_PrivacyAndCookiePolicyAccept(const TCHAR* Cmd);

	/**
	* Broadcast the Privacy and Cookie Policy - Do Not Accept action
	* Checks for the following console commands:
	* - PrivacyAndCookiePolicyDoNotAccept
	* - PrivacyAndCookiePolicy DoNotAccept
	*
	* @param Cmd	Console Command
	* return		Whether the console command was found / executed
	*/
	bool Exec_PrivacyAndCookiePolicyDoNotAccept(const TCHAR* Cmd);
};