

#include "prosperousAsyncBlueprint.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Engine/Engine.h"


UprosperousAsyncBlueprint* UprosperousAsyncBlueprint::RevealText(UObject* WorldContextObject, FText InputText, float Delay, ETextRevealMode RevealMode)
{
    UprosperousAsyncBlueprint* Node = NewObject<UprosperousAsyncBlueprint>();
    Node->WorldContextObject = WorldContextObject;
    Node->OriginalString = InputText.ToString();
    Node->Delay = Delay;
    Node->RevealMode = RevealMode;
    return Node;
}

void UprosperousAsyncBlueprint::Activate()
{
    if (!WorldContextObject || OriginalString.IsEmpty())
    {
        OnFinished.Broadcast();
        return;
    }

    // Don't restart if text hasn't changed
    if (OriginalString == LastOutput)
    {
        OnFinished.Broadcast(); // Still trigger the end for consistency
        return;
    }

    CurrentIndex = 0;
    RevealStep();
}

void UprosperousAsyncBlueprint::RevealStep()
{
    FString CurrentText = GetCurrentReveal();

    // Only broadcast if it has changed
    if (CurrentText != LastOutput)
    {
        OnUpdate.Broadcast(FText::FromString(CurrentText));
        LastOutput = CurrentText;
    }

    CurrentIndex++;

    int32 MaxSteps = OriginalString.Len();
    if (RevealMode == ETextRevealMode::Middle)
    {
        MaxSteps = (OriginalString.Len() + 1) / 2;
    }

    if (CurrentIndex >= MaxSteps)
    {
        LastOutput = OriginalString; // Store for the next comparison
        OnFinished.Broadcast();
        return;
    }

    if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
    {
        World->GetTimerManager().SetTimer(TimerHandle, this, &UprosperousAsyncBlueprint::RevealStep, Delay, false);
    }
}


FString UprosperousAsyncBlueprint::GetCurrentReveal() const
{
    int32 Len = OriginalString.Len();

    switch (RevealMode)
    {
    case ETextRevealMode::Beginning:
        return OriginalString.Left(CurrentIndex + 1);

    case ETextRevealMode::End:
        return OriginalString.Right(CurrentIndex + 1);

    case ETextRevealMode::Middle:
    {
        int32 Mid = Len / 2;

        int32 Start;
        int32 Count;

        if (Len % 2 == 0)
        {
            // Even-length: center is between two letters (Mid - 1 and Mid)
            Start = Mid - CurrentIndex - 1;
            Count = (CurrentIndex + 1) * 2;

            if (Start < 0)
            {
                Count += Start; // Shrink count
                Start = 0;
            }
        }
        else
        {
            // Odd-length: center is one character (Mid)
            Start = Mid - CurrentIndex;
            Count = CurrentIndex * 2 + 1;

            if (Start < 0)
            {
                Count += Start; // Shrink count
                Start = 0;
            }
        }

        Count = FMath::Min(Count, Len - Start);
        return OriginalString.Mid(Start, Count);
    }

    default:
        return OriginalString;
    }
}
