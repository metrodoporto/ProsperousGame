#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "prosperousBlueprint.generated.h"

UCLASS()
class UprosperousBlueprint : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Version"), Category = "Game")
    static FString GetAppVersion();

    UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Random Element (Text)", Category = "Get Random Element"))
    static FText GetRandomText(const TArray<FText>& TextArray);

    UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Random Element (String)", Category = "Get Random Element"))
    static FString GetRandomString(const TArray<FString>& StringArray);
};
