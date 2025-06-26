#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "prosperousAsyncBlueprint.generated.h"

UENUM(BlueprintType)
enum class ETextRevealMode : uint8
{
    Beginning,
    Middle,
    End
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTextUpdate, FText, CurrentText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTextFinished);

UCLASS()
class PROSPEROUSGAME_API UprosperousAsyncBlueprint : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnTextUpdate OnUpdate;

    UPROPERTY(BlueprintAssignable)
    FOnTextFinished OnFinished;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Reveal Text", Keywords = "text reveal typewriter async"), Category = "Text")
    static UprosperousAsyncBlueprint* RevealText(UObject* WorldContextObject, FText InputText, float Delay, ETextRevealMode RevealMode);


    virtual void Activate() override;

private:
    void RevealStep();

    UObject* WorldContextObject;
    FString OriginalString;
    float Delay;
    ETextRevealMode RevealMode;

    int32 CurrentIndex = 0;
    FTimerHandle TimerHandle;
    FString LastOutput; // The final revealed text from the last run

    FString GetCurrentReveal() const;
};
