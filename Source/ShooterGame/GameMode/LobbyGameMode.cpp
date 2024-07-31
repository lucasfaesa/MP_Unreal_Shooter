// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("On Post Login"));
	
	if(NumberOfPlayers == 2)
	{
		UWorld* World = GetWorld();

		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("On Two Players"));
		
		if(World)
		{
			if(GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Travelling to blaster map"));
			
			bUseSeamlessTravel = false;
			World->ServerTravel(FString("/Game/Maps/BlasterMap?listen"));
		}
	}
	
}
