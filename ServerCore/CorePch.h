#pragma once

#include "Types.h"
#include "CoreMacro.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"
#include "Container.h"

#include <windows.h>
#include "Lock.h"
#include "Memory.h"

using namespace std;

void HelloWorld();

class Uncopyable
{
protected:
	Uncopyable() = default;
	virtual ~Uncopyable() = default;

private:
	Uncopyable(const Uncopyable& u) = delete; // 복사 생성자 삭제
	Uncopyable& operator=(const Uncopyable& u) = delete; //복사 대입 연산자 삭제
};