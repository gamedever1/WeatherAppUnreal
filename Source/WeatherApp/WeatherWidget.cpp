// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherWidget.h"

FString UWeatherWidget::ParseJson()
{
	FString resultStr = FString("");

	TSharedPtr<FJsonObject> JsonObject;

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(cityJson);

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		for (auto currJsonValue = JsonObject->Values.CreateConstIterator(); currJsonValue; ++currJsonValue)
		{
			// Get the key name
			const FString Lvl1_Name = (*currJsonValue).Key;
			// Get the value as a FJsonValue object
			TSharedPtr< FJsonValue > Value = (*currJsonValue).Value;

			if ( Lvl1_Name.Equals(FString("name")) ) {
				cityName = Value->AsString();
			}

			TSharedPtr<FJsonObject> JsonObjectNested = Value->AsObject();
			for (auto currJsonNested = JsonObjectNested->Values.CreateConstIterator(); currJsonNested; ++currJsonNested)
			{
				const FString Lvl2_Name = (*currJsonNested).Key;
				FString Lvl2_value = (*currJsonNested).Value->AsString();
				if (Lvl1_Name.Equals(FString("main")) && Lvl2_Name.Equals(FString("temp"))) {
					cityTemperature = Lvl2_value; //установка температуры из JSON
					resultStr += TEXT("Temperatura: ") + cityTemperature + TEXT(" °C");
					resultStr += "\n";
				}
				else if (Lvl1_Name.Equals(FString("main")) && Lvl2_Name.Equals(FString("pressure"))) {
					resultStr += TEXT("Davlenie: ") + Lvl2_value + TEXT(" hPa");
					resultStr += "\n";
				}
				else if (Lvl1_Name.Equals(FString("main")) && Lvl2_Name.Equals(FString("humidity"))) {
					resultStr += TEXT("Vlazhnost: ") + Lvl2_value + TEXT(" %");
					resultStr += "\n";
				}
				else if (Lvl1_Name.Equals(FString("wind")) && Lvl2_Name.Equals(FString("speed"))) {
					resultStr += TEXT("Skorost vetra: ") + Lvl2_value + TEXT(" m/s");
					resultStr += "\n";
				}
				else if (Lvl1_Name.Equals(FString("clouds")) && Lvl2_Name.Equals(FString("all"))) {
					resultStr += TEXT("Oblachnost: ") + Lvl2_value + TEXT(" %");
					resultStr += "\n";
				}
				else if (Lvl1_Name.Equals(FString("rain")) && Lvl2_Name.Equals(FString("1h"))) {
					resultStr += TEXT("Osadki: ") + Lvl2_value + TEXT(" mm");
					resultStr += "\n";
				}
			}
		}
	}
	return resultStr;
}


