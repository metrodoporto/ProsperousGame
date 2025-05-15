#include "prosperousBlueprint.h"
#include "Misc/App.h"
#include "Misc/ConfigCacheIni.h" // Include this to use GConfig and GGameIni
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Level.h"

FString UprosperousBlueprint::GetAppVersion()
{
    FString AppVersion;
    GConfig->GetString(
        TEXT("/Script/EngineSettings.GeneralProjectSettings"),
        TEXT("ProjectVersion"),
        AppVersion,
        GGameIni
    );

    return AppVersion;
}

FText UprosperousBlueprint::GetRandomText(const TArray<FText>& TextArray)
{

    if (TextArray.Num() > 0) {
        int32 RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, TextArray.Num() - 1);

        return TextArray[RandomIndex];
    }

    return FText::GetEmpty();
}

FString UprosperousBlueprint::GetRandomString(const TArray<FString>& StringArray) {
    if (StringArray.Num() > 0) {
        int32 RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, StringArray.Num() - 1);

        return StringArray[RandomIndex];
    }

    return "none";
}

bool UprosperousBlueprint::IsCurrentLevel(const UObject* WorldContextObject, TSoftObjectPtr<UWorld> LevelToCheck)
{
    UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
    if (World && LevelToCheck.IsValid())
    {
        return World->GetCurrentLevel()->GetOuter() == LevelToCheck.Get();
    }
    return false;
}

FString UprosperousBlueprint::IntToRoman(int Number)
{
    if (Number <= 0 || Number > 3999)
    {
        return TEXT("Invalid Number");
    }

    TArray<TPair<int, FString>> RomanNumerals = {
        {1000, TEXT("M")}, {900, TEXT("CM")}, {500, TEXT("D")}, {400, TEXT("CD")},
        {100, TEXT("C")}, {90, TEXT("XC")}, {50, TEXT("L")}, {40, TEXT("XL")},
        {10, TEXT("X")}, {9, TEXT("IX")}, {5, TEXT("V")}, {4, TEXT("IV")}, {1, TEXT("I")}
    };

    FString Result = TEXT("");

    for (const TPair<int, FString>& Pair : RomanNumerals)
    {
        while (Number >= Pair.Key)
        {
            Result += Pair.Value;
            Number -= Pair.Key;
        }
    }

    return Result;
}