#include "stdafx.h"
#include "CppUnitTest.h"

#include "../ProtocolPackage/STXProtocol.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProtocolPackageTest
{		
	TEST_CLASS(UnitTest_Offset)
	{

	public:
		GUID GenerateGUID()
		{
			GUID guid;
			guid.Data1 = 0xAE3C55DA;
			guid.Data2 = 12765;
			guid.Data3 = 7883;
			for (int i = 0; i < 8; i++)
				guid.Data4[i] = rand() % 256;
			return guid;
		}
	public:
		TEST_METHOD(TestOffset)
		{
			CSTXProtocol p;

			size_t offset1 = 0;
			p.AppendData((uint32_t)0, &offset1);
			size_t offset2 = 0;
			p.AppendData((uint32_t)100, &offset2);

			p.IncreaseDWORDAtOffset(offset1, 1);
			Assert::AreEqual((uint32_t)1, p.GetDWORDAtOffset(offset1));
			p.IncreaseDWORDAtOffset(offset1, 3);
			Assert::AreEqual((uint32_t)4, p.GetDWORDAtOffset(offset1));
			p.IncreaseDWORDAtOffset(offset1, 8);
			Assert::AreEqual((uint32_t)12, p.GetDWORDAtOffset(offset1));
			p.DecreaseDWORDAtOffset(offset1, 7);
			Assert::AreEqual((uint32_t)5, p.GetDWORDAtOffset(offset1));
			p.DecreaseDWORDAtOffset(offset1, 5);
			Assert::AreEqual((uint32_t)0, p.GetDWORDAtOffset(offset1));
			Assert::ExpectException<std::runtime_error>([&] {p.DecreaseDWORDAtOffset(offset1, 1); });		//0 can not be decreased
			Assert::AreEqual((uint32_t)0, p.GetDWORDAtOffset(offset1));

			p.IncreaseDWORDAtOffset(offset2, 10);
			Assert::AreEqual((uint32_t)110, p.GetDWORDAtOffset(offset2));
			p.IncreaseDWORDAtOffset(offset2, 5);
			Assert::AreEqual((uint32_t)115, p.GetDWORDAtOffset(offset2));
			p.IncreaseDWORDAtOffset(offset2, 200);
			Assert::AreEqual((uint32_t)315, p.GetDWORDAtOffset(offset2));
			Assert::AreEqual((uint32_t)0, p.GetDWORDAtOffset(offset1));

			Assert::ExpectException<std::runtime_error>([&] {p.GetDWORDAtOffset(offset2 + sizeof(uint32_t)); });
			Assert::ExpectException<std::runtime_error>([&] {p.DecreaseDWORDAtOffset(offset1, 1); });	//0 can not be decreased
			p.IncreaseDWORDAtOffset(offset1, UINT32_MAX - 4);											//**This value will be checked later
			Assert::AreEqual((uint32_t)UINT32_MAX - 4, p.GetDWORDAtOffset(offset1));
			Assert::ExpectException<std::runtime_error>([&] {p.IncreaseDWORDAtOffset(offset1, 5); });	//can not be increased to greater than UINT32_MAX

			int val1 = 17;
			p.AppendData<int>(val1);			//take a left value as parameter

			size_t offset3 = 0;
			p.AppendData<int>(50, &offset3);	//take a right value as parameter

			int &intRef = p.GetReferenceAtOffset<int>(offset3);
			Assert::AreEqual(50, intRef);
			intRef += 20;
			Assert::AreEqual(70, intRef);
			int &intRef2 = p.GetReferenceAtOffset<int>(offset3);
			Assert::AreEqual(70, intRef2);
			intRef2 -= 100;
			Assert::AreEqual(-30, intRef);
			Assert::AreEqual(-30, intRef2);
			Assert::AreEqual(&intRef, &intRef2);

			Assert::ExpectException<std::runtime_error>([&] {p.GetReferenceAtOffset<int>(offset3 + sizeof(int)); });


			Assert::AreEqual((uint32_t)UINT32_MAX - 4, p.GetNextDWORD());
			Assert::AreEqual((uint32_t)315, p.GetNextDWORD());
			Assert::AreEqual((int)17, p.GetNextData<int>());
			Assert::AreEqual((int)-30, p.GetNextData<int>());
			Assert::ExpectException<std::runtime_error>([&] {p.GetNextData<int>(); });		//No more data

		}

	};
}