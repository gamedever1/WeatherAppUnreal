// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHttpClass.h"


MyHttpClass::MyHttpClass()
{
}

FString MyHttpClass::GetRequestJson(FString url, int32* actor_http_state_ptr)
{
	fHttpModule = &FHttpModule::Get();
	http_state_ptr = actor_http_state_ptr;


	TSharedRef<IHttpRequest> Request = fHttpModule->CreateRequest();
	Request->OnProcessRequestComplete().BindRaw(this, &MyHttpClass::OnResponseReceived);
	Request->SetURL(url);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->SetContentAsString(OutputString);
	Request->ProcessRequest();

	return FString(TEXT("MyHttpClass: GET ")) + url;
}

void MyHttpClass::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	*http_state_ptr = 1;
	FString response = Response->GetContentAsString();
	responseStr = response;
}

MyHttpClass::~MyHttpClass()
{
}
