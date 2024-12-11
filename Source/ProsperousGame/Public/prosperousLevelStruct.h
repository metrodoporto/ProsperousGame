#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "prosperousLevelStruct.generated.h"



USTRUCT(BlueprintType)
struct PROSPEROUSGAME_API FProsperousLevelStruct: public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString LevelName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UWorld> Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* LevelTexture;
};
