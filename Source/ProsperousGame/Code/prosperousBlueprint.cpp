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