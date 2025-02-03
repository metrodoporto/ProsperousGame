// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "sealTextWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTypingFinished);

UCLASS()
class PROSPEROUSGAME_API UsealTextWidget : public UUserWidget
{

    GENERATED_BODY()

public:
    UsealTextWidget(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Typing")
    FText TextToDisplay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Typing", meta = (ClampMin = "-1.0", ClampMax = "10.0"))
    float TypingSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Typing")
    bool ShowWriterCharacterAfterFinish;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Typing")
    FText WriterCharacter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Typing")
    bool ClearInstantly;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Typing")
    bool ShowCharacterInClear;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Typing")
    bool bCycleLoopCharacter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Typing", meta = (ClampMin = "0", ClampMax = "1"))
    int32 LoopCharacterType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Typing")
    float ClearSpeed;

    UFUNCTION(BlueprintCallable, Category = "Typing")
    void StartTyping();

    UFUNCTION(BlueprintCallable, Category = "Typing")
    void ClearText();

    UPROPERTY(BlueprintAssignable, Category = "Typing")
    FOnTypingFinished OnTypingFinished;

protected:
    virtual void NativeConstruct() override;

private:
    FTimerHandle TypingTimerHandle;
    FTimerHandle ClearingTimerHandle;
    FTimerHandle CursorBlinkingTimerHandle;
    FTimerHandle CharacterCycleTimerHandle;
    FString CurrentText;
    int32 CurrentIndex;
    int32 CurrentCycleIndex;
    bool bIsCursorVisible;

    FText LoopCharacter;

    TArray<FString> CycleCharacters;

    void TypingUpdate();
    void ClearUpdate();
    void ToggleCursorVisibility();
    void CycleLoopCharacter();

    UPROPERTY(meta = (BindWidget))
    class URichTextBlock* TypingTextBlock;

    URichTextBlock* RichTextBlock;
};
