// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/Engine.h"
#include "HttpModule.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "GenericPlatform/GenericPlatformHttp.h"

/**
 *
 */
class WEATHERAPP_API MyHttpClass
{
public:
	MyHttpClass();

	FHttpModule * fHttpModule;
	FString OutputString;


	void OnResponseReceived(FHttpRequestPtr, FHttpResponsePtr, bool);

	int32 * http_state_ptr;
	FString responseStr;
	FString GetRequestJson(FString, int32 *);

	~MyHttpClass();
};



