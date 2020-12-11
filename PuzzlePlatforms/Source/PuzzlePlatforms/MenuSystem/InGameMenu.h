// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "InGameMenu.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()
	
/*
* Members *
*/
private:
	UPROPERTY(meta = (BindWidget))
	UButton* PauseCancelButton;

	UPROPERTY(meta = (BindWidget))
	UButton* PauseMainMenuButton;


/*
* Methods *
*/
protected:
	virtual bool Initialize() override;

private:

	UFUNCTION()
	void CloseInGameMenu();

	UFUNCTION()
	void QuitToMainMenu();

};
