#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Materials/MaterialInterface.h"
#include "prosperousLevelStruct.generated.h"



USTRUCT(BlueprintType)
struct PROSPEROUSGAME_API FProsperousLevelStruct: public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
    FName Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
    TSoftObjectPtr<UWorld> LevelReference;

    // Use UMaterialInterface* for both materials and material instances
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
    UMaterialInterface* LevelMaterial;

    // Use FText for localizable title
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
    FText LevelTitle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
    FText LevelDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
    int32 LevelDifficulty;


    FProsperousLevelStruct()
        : Name("Default")
        , LevelReference(nullptr)
        , LevelMaterial(nullptr)
        , LevelTitle(FText::FromString("O. Level Name"))
        , LevelDescription(FText::FromString("Descrição do Nível"))
        , LevelDifficulty(1)
    {
    }
};
