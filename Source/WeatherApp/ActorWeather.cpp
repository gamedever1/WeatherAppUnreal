// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorWeather.h"
#include "SQLiteDatabase.h"///

#include "Engine/Classes/Engine/Engine.h"



// Sets default values
AActorWeather::AActorWeather()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActorWeather::BeginPlay()
{
	httpClass = new MyHttpClass();

	Super::BeginPlay();
}

// Called every frame
void AActorWeather::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (http_state == 1) //сигнал записать в ActorWeather строку http ответа
	{
		httpResponseStr = httpClass->responseStr;
		http_state = 2; //сигнал для Blueprint, что http ответ записан
	}
}



void AActorWeather::PrintMsg()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString(TEXT("TEST PRINT MSG")));
}

void AActorWeather::SendHttpRequest(FString requestText) //берет уже полученный из blueprint текст запроса, делает из него http-запрос 
{
	FString httpReqStr = FString("http://api.openweathermap.org/data/2.5/weather?q=") + FPlatformHttp::UrlEncode(requestText) + FString(",RU&appid=8ca5e2415b2e6cfa62325ab018126c72&lang=ru&units=metric");
	FString json_str = httpClass->GetRequestJson(httpReqStr, &http_state);

	return;
}

TArray<FSqliteData> AActorWeather::ParseSqlite()
{

	TArray<FSqliteData> resultArr = TArray<FSqliteData>();

	FString dbName = TEXT("weather_db");

	if (USQLiteDatabase::IsDatabaseRegistered(dbName))
	{
		USQLiteDatabase::UnregisterDatabase(dbName);
	}
	bool success = USQLiteDatabase::RegisterDatabase(dbName, databasePath, true, true);
	if (success) {
		FString out = "-1";
		TUniquePtr<SQLiteQueryResult> result = USQLiteDatabase::RunQueryAndGetResults(dbName,
			FString::Printf(TEXT("SELECT * FROM weather")));
		if (result->Success && result->Results.Num() > 0 && result->Results[0].Fields.Num() > 0) {
			for (int32 i = 0; i < result->Results.Num(); i += 1)
			{
				out = result->Results[i].Fields[3].ToString();
				FSqliteData new_struct;
				new_struct.struct_id = result->Results[i].Fields[0].IntValue;
				new_struct.struct_json = result->Results[i].Fields[1].ToString();
				new_struct.struct_temp = result->Results[i].Fields[2].ToString();
				new_struct.struct_cityname = result->Results[i].Fields[3].ToString();
				new_struct.struct_timewas = result->Results[i].Fields[4].ToString();
				resultArr.Add(new_struct);
			}

		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("ERROR QUERY DB"));

		}

		USQLiteDatabase::UnregisterDatabase(dbName);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("NO_CONNECT(DATABASE FILE DOESNT EXITS)"));
	}
	return resultArr;

}

int AActorWeather::InsertNewRow(FString new_json, FString new_citytemp, FString new_cityname, FString new_timewas)
{
	FString dbName = TEXT("weather_db");

	if (USQLiteDatabase::IsDatabaseRegistered(dbName))
	{
		USQLiteDatabase::UnregisterDatabase(dbName);
	}
	bool success = USQLiteDatabase::RegisterDatabase(dbName, databasePath, true, true);
	if (success) {

		FString SQLstr = FString::Printf(TEXT("INSERT INTO weather (json, citytemp, cityname, timewas) VALUES ('%s', '%s', '%s', '%s');"), *new_json, *new_citytemp, *new_cityname, *new_timewas);
		bool result = USQLiteDatabase::ExecSql(dbName, SQLstr);
		if (result) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("INSERT ROWS SUCESS"));
			TUniquePtr<SQLiteQueryResult> sql_result = USQLiteDatabase::RunQueryAndGetResults(dbName, FString::Printf(TEXT("SELECT last_insert_rowid();")));
			if (sql_result->Success && sql_result->Results.Num() > 0 && sql_result->Results[0].Fields.Num() > 0) {
				return sql_result->Results[0].Fields[0].IntValue;
			}
			else { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("ERROR: CANT GET LAST INSERTED ID")); }
		}
		else GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("ERROR: INSERT QUERY DB"));

		USQLiteDatabase::UnregisterDatabase(dbName);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ERROR: CANT CONNECT TO SQLITE DATABASE"));
	}

	return -1;
}

bool AActorWeather::UpdateRowById(int32 row_id, FString new_json, FString new_timewas)
{
	FString dbName = TEXT("weather_db");

	if (USQLiteDatabase::IsDatabaseRegistered(dbName))
	{
		USQLiteDatabase::UnregisterDatabase(dbName);
	}
	bool success = USQLiteDatabase::RegisterDatabase(dbName, databasePath, true, true);
	if (success) {
		FString SQLstr = FString::Printf(TEXT("UPDATE weather SET json = '%s', timewas = '%s'  WHERE id = %d;"), *new_json, *new_timewas, row_id);/// "INSERT INTO weather (json, citytemp, cityname, timewas) VALUES ('%s', '%s', '%s', '%s');"), *new_json, *new_citytemp, *new_cityname, *new_timewas);
		bool result = USQLiteDatabase::ExecSql(dbName, SQLstr);
		if (result) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("UPDATE ROW SUCESS"));
			return true;
		}
		else GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("ERROR: UPDATE QUERY DB"));

		USQLiteDatabase::UnregisterDatabase(dbName);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ERROR: CANT CONNECT TO SQLITE DATABASE"));
	}

	return false;
}


