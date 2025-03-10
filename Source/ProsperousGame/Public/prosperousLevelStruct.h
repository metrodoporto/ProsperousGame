#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Materials/MaterialInterface.h"
#include "prosperousLevelStruct.generated.h"



USTRUCT(BlueprintType)
struct PROSPEROUSGAME_API FProsperousLevelStruct: public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString LevelName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UWorld> Level;

    // Material
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterialInterface* LevelMaterial;
};
