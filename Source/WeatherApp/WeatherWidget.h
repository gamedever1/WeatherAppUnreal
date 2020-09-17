// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "Dom/JsonObject.h"

#include "WeatherWidget.generated.h"

/**
 * 
 */
UCLASS()
class WEATHERAPP_API UWeatherWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeatherApp")
		int32 cityId = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeatherApp")
		FString cityJson;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeatherApp")
		FString cityTemperature;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeatherApp")
		FString cityName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeatherApp")
		FString timeWas;

	UFUNCTION(BlueprintCallable, Category = "WeatherApp")
		FString ParseJson();
};
