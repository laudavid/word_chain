#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Core\Core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreModuleTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: �ڴ�������Դ���
            Assert::AreEqual("11", "11+22=33");
        }

	};
}