// Change to RichTextBlock!!!


#include "sealTextWidget.h"
#include "Components/RichTextBlock.h"
#include "TimerManager.h"

UsealTextWidget::UsealTextWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    TextToDisplay = FText::FromString("Hello, World!");
    TypingSpeed = 0.09f;
    ShowWriterCharacterAfterFinish = false;
    WriterCharacter = FText::FromString("_");
    ClearInstantly = false;
    ShowCharacterInClear = true;
    ClearSpeed = 0.02f;
    bIsCursorVisible = true;
    bCycleLoopCharacter = false;
    CycleCharacters = { "/", "-", "\\", "|" };
    CurrentCycleIndex = 0;
}

void UsealTextWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Ensure TypingTextBlock is valid
    if (!TypingTextBlock)
    {
        UE_LOG(LogTemp, Warning, TEXT("TypingTextBlock is not bound!"));
    }

    RichTextBlock = TypingTextBlock;

    if (!RichTextBlock)
    {
        UE_LOG(LogTemp, Warning, TEXT("TypingTextBlock is not a URichTextBlock!"));
    }
}

void UsealTextWidget::StartTyping()
{

    switch (LoopCharacterType) {
    default:
    case 0:
        CycleCharacters = { "/", "-", "\\", "|" };
        break;
    case 1:
        CycleCharacters = { ".", "..", "..." };
        break;
    }

    if (TypingSpeed > 0)
    {
        CurrentText = "";
        CurrentIndex = 0;
        GetWorld()->GetTimerManager().SetTimer(TypingTimerHandle, this, &UsealTextWidget::TypingUpdate, TypingSpeed, true);
    } else {
        CurrentText = TextToDisplay.ToString();
        CurrentIndex = TextToDisplay.ToString().Len();

        OnTypingFinished.Broadcast();

        if (bCycleLoopCharacter)
        {
            GetWorld()->GetTimerManager().SetTimer(CharacterCycleTimerHandle, this, &UsealTextWidget::CycleLoopCharacter, 0.3f, true);
        }
        else
        {
            GetWorld()->GetTimerManager().SetTimer(CursorBlinkingTimerHandle, this, &UsealTextWidget::ToggleCursorVisibility, 0.5f, true);
        }
    }
}

void UsealTextWidget::TypingUpdate()
{
    if (CurrentIndex >= TextToDisplay.ToString().Len())
    {
        GetWorld()->GetTimerManager().ClearTimer(TypingTimerHandle);
        OnTypingFinished.Broadcast();

        if (bCycleLoopCharacter)
        {
            GetWorld()->GetTimerManager().SetTimer(CharacterCycleTimerHandle, this, &UsealTextWidget::CycleLoopCharacter, 0.3f, true);
        }
        else
        {
            GetWorld()->GetTimerManager().SetTimer(CursorBlinkingTimerHandle, this, &UsealTextWidget::ToggleCursorVisibility, 0.5f, true);
        }
    }
    else
    {
        CurrentText += TextToDisplay.ToString()[CurrentIndex];
        CurrentIndex++;

        if (RichTextBlock)
        {
            if (CurrentIndex == TextToDisplay.ToString().Len() && !ShowWriterCharacterAfterFinish && !bCycleLoopCharacter)
            {
                RichTextBlock->SetText(FText::FromString(CurrentText));
            }
            else
            {
                RichTextBlock->SetText(FText::FromString(CurrentText + WriterCharacter.ToString()));
            }
        }
    }
}

void UsealTextWidget::ClearText()
{
    // Stop cursor blinking when text is being cleared
    GetWorld()->GetTimerManager().ClearTimer(CursorBlinkingTimerHandle);

    if (ClearInstantly)
    {
        if (RichTextBlock)
        {
            if (bCycleLoopCharacter) {
                GetWorld()->GetTimerManager().ClearTimer(CharacterCycleTimerHandle);
            }
            RichTextBlock->SetText(FText::GetEmpty());
        }
    }
    else
    {
        GetWorld()->GetTimerManager().SetTimer(ClearingTimerHandle, this, &UsealTextWidget::ClearUpdate, ClearSpeed, true);
    }
}

void UsealTextWidget::ClearUpdate()
{
    if (bCycleLoopCharacter) {
        GetWorld()->GetTimerManager().ClearTimer(CharacterCycleTimerHandle);
    }

    if (CurrentText.Len() == 0)
    {
        GetWorld()->GetTimerManager().ClearTimer(ClearingTimerHandle);

        RichTextBlock->SetText(FText::GetEmpty());

        GetWorld()->GetTimerManager().SetTimer(CursorBlinkingTimerHandle, this, &UsealTextWidget::ToggleCursorVisibility, 0.5f, true);
    }
    else
    {
        CurrentText = CurrentText.LeftChop(1);

        if (RichTextBlock)
        {
            if (ShowCharacterInClear)
            {
                RichTextBlock->SetText(FText::FromString(CurrentText + WriterCharacter.ToString()));
            }
            else
            {
                RichTextBlock->SetText(FText::FromString(CurrentText));
            }
        }
    }
}

void UsealTextWidget::ToggleCursorVisibility()
{
    if (bCycleLoopCharacter)
    {
        GetWorld()->GetTimerManager().ClearTimer(CharacterCycleTimerHandle);
    }

    bIsCursorVisible = !bIsCursorVisible;

    if (RichTextBlock)
    {
        FString DisplayText = CurrentText + (bIsCursorVisible ? WriterCharacter.ToString() : "");
        RichTextBlock->SetText(FText::FromString(DisplayText));
    }
}

void UsealTextWidget::CycleLoopCharacter()
{

    if (CurrentText.IsEmpty())
    {
        GetWorld()->GetTimerManager().ClearTimer(CharacterCycleTimerHandle);
        return;
    }

    CurrentCycleIndex = (CurrentCycleIndex + 1) % CycleCharacters.Num();
    LoopCharacter = FText::FromString(CycleCharacters[CurrentCycleIndex]);

    if (RichTextBlock)
    {
        RichTextBlock->SetText(FText::FromString(CurrentText + LoopCharacter.ToString()));
    }
}