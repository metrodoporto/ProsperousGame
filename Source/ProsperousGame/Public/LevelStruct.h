#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Materials/MaterialInterface.h"
#include "Engine/Level.h"
#include "LevelStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FLevelStruct
{
    GENERATED_BODY()

    // Name of the item
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
    FName Name;

    // Level reference
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
    TSoftObjectPtr<UWorld> LevelReference;

    // Texture
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
    UTexture2D* Texture;

    // Material
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
    UMaterialInterface* Material;

    // Default Constructor
    FLevelStruct()
        : Name("Default"), LevelReference(nullptr), Texture(nullptr), Material(nullptr)
    {
    }
};