// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Highscore.generated.h"

USTRUCT(BlueprintType)
struct FHighScoreNode {
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
		float p_score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
		FString p_name;
};

UCLASS()
class LIGHTSMIRROR_API UHighScore : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "HighScore")
		static TArray<FHighScoreNode> setHighScore(FString name, float score);

	UFUNCTION(BlueprintCallable, Category = "HighScore")
		static void writeNewScore(float score);

	UFUNCTION(BlueprintCallable, Category = "HighScore")
		static TArray<FHighScoreNode> getHighScore();

	UFUNCTION(BlueprintCallable, Category = "HighScore")
		static float getNewScore();

};
