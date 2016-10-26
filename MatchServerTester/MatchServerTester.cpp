// MatchServerTester.cpp : 기본 프로젝트 파일입니다.

#include "stdafx.h"
#include "src\MatchServer.h"
#include "src\util\Matcher.h"
#include "src\type\Client.h"




using namespace System;

int main()
{


	Matcher* matcher = Matcher::GetInstance();

	Client client();
	

	matcher->Matching();



}
