// Fill out your copyright notice in the Description page of Project Settings.

#include "LightsMirror.h"
#include "Highscore.h"


UHighScore::UHighScore(const class FObjectInitializer & PCIP)
	: Super(PCIP)
{

}

FString fd = FPaths::GameDir() + "Content/GameLogic/Saved/";
FString fn = "HighScore.txt";
FString fns = "NewScore.txt";
FString fp = fd + fn;
FString fpp = fd + fns;

TArray<FHighScoreNode> UHighScore::setHighScore(FString name, float score)
{
	TArray<FHighScoreNode> curr = getHighScore();
	FHighScoreNode newScore; newScore.p_name = name; newScore.p_score = score;
	bool added = false;
	for (int32 i = 0; i < curr.Num(); ++i) {
		if (score > curr[i].p_score) {
			added = true;
			curr.Insert(newScore, i);
			break;
		}
	}
	if (!added) curr.Add(newScore);
	if (curr.Num() > 5) curr.RemoveAt(curr.Num() - 1);

	//Write to file
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (!PlatformFile.DirectoryExists(*fd)) {
		//create directory if it not exist
		PlatformFile.CreateDirectory(*fd);
	}
	if (PlatformFile.CreateDirectoryTree(*fd)) {
		FString res = "";
		for (int32 i = 0; i < curr.Num(); ++i) {
			res += curr[i].p_name + " " + FString::SanitizeFloat(curr[i].p_score)  + "\n";
		}
		FFileHelper::SaveStringToFile(res, *fp);
	}
	return curr;
}

void  UHighScore::writeNewScore(float score)
{
	//Write to file
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (!PlatformFile.DirectoryExists(*fd)) {
		//create directory if it not exist
		PlatformFile.CreateDirectory(*fd);
	}
	if (PlatformFile.CreateDirectoryTree(*fd)) {
		FString res = "" + FString::SanitizeFloat(score);
		FFileHelper::SaveStringToFile(res, *fpp);
	}
}

TArray<FHighScoreNode> UHighScore::getHighScore()
{
	FString file = "";
	FFileHelper::LoadFileToString(file, *fp);
	TArray<FString> lines;
	file.ParseIntoArray(lines, _T("\n"), true);
	TArray<FHighScoreNode> res;
	for (int32 i = 0; i < lines.Num(); ++i) {
		FString line = lines[i];
		FString name, score;
		line.Split(" ", &name, &score);
		FHighScoreNode hs; hs.p_name = name; hs.p_score = FCString::Atof(*score);
		res.Add(hs);
	}
	return res;
}


float UHighScore::getNewScore()
{
	FString file = "";
	FFileHelper::LoadFileToString(file, *fpp);
	float res = FCString::Atof(*file);
	return res;
}


