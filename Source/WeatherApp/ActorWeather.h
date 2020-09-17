// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyHttpClass.h"


#include "ActorWeather.generated.h"


USTRUCT(BlueprintType)
struct FSqliteData
{
	GENERATED_USTRUCT_BODY()

		// Item class to spawn
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeatherApp")
		int32 struct_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeatherApp")
		FString struct_json;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeatherApp")
		FString struct_temp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeatherApp")
		FString struct_cityname;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeatherApp")
		FString struct_timewas;

	// Default constructor
	FSqliteData() { }
};

UCLASS()
class WEATHERAPP_API AActorWeather : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActorWeather();


		MyHttpClass * httpClass;

		FString databasePath = FString("DataBase/database.sqlite3");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeatherApp")
		int32 id = -2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeatherApp")
		int32 http_state = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeatherApp")
		FString httpResponseStr;
	
	UFUNCTION(BlueprintCallable, Category = "WeatherApp")
		void PrintMsg();

	UFUNCTION(BlueprintCallable, Category = "WeatherApp")
		void SendHttpRequest(FString requestText);

	UFUNCTION(BlueprintCallable, Category = "WeatherApp")
		TArray<FSqliteData>  ParseSqlite();

	UFUNCTION(BlueprintCallable, Category = "WeatherApp")
		int InsertNewRow(FString new_json, FString new_citytemp, FString new_cityname, FString new_timewas);

	UFUNCTION(BlueprintCallable, Category = "WeatherApp")
		bool UpdateRowById(int32 row_id, FString new_json, FString new_timewas);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};


