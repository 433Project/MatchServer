// MatchServerTester.cpp : �⺻ ������Ʈ �����Դϴ�.

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
