#include "stdafx.h"
#include "CppUnitTest.h"

#include "../ProtocolPackage/STXProtocol.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProtocolPackageTest
{		
	TEST_CLASS(UnitTest_Embedded)
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
		TEST_METHOD(TestSimpleEmbeddedObjects)
		{
			CSTXProtocol p;
			p.AppendData((uint16_t)500);

			CSTXProtocol e1;
			e1.AppendData((unsigned char)56);
			e1.AppendData("E1 String1");
			e1.AppendDataPair("E1 Key1", "Value1");


			CSTXProtocol e2;
			e2.AppendData(u"E2 String1");
			e2.AppendDataPair(u"E2 Key1", u"Value2");
			e2.AppendUnicodeString("E2 Unicode1");

			p.AppendData(&e1);
			p.AppendData((uint32_t)100000);
			p.AppendData(&e2);

			//Now retrieving...

			Assert::IsTrue((uint16_t)500 == p.GetNextWORD());

			CSTXProtocol *pe1 = p.GetNextObject();
			Assert::IsNotNull(pe1);
			Assert::AreEqual((unsigned char)56, pe1->GetNextByte());
			Assert::AreEqual(std::string("E1 String1"), pe1->GetNextString());
			char buf1[64] = { 0 };
			char buf2[64] = { 0 };
			pe1->GetNextStringPair(buf1, 64, buf2, 64);
			Assert::AreEqual(std::string("E1 Key1"), std::string(buf1));
			Assert::AreEqual(std::string("Value1"), std::string(buf2));
			Assert::IsFalse(pe1->IsDataAvailable());
			Assert::ExpectException<std::runtime_error>([&] {pe1->GetNextByte(); });

			delete pe1;

			Assert::IsTrue((uint32_t)100000 == p.GetNextDWORD());
			CSTXProtocol *pe2 = p.GetNextObject();
			Assert::IsNotNull(pe2);
			Assert::IsTrue(std::u16string(u"E2 String1") == pe2->GetNextUnicodeString());
			char16_t bufu1[64] = { 0 };
			char16_t bufu2[64] = { 0 };
			pe2->GetNextStringPair(bufu1, 64, bufu2, 64);
			Assert::IsTrue(std::u16string(u"E2 Key1") == std::u16string(bufu1));
			Assert::IsTrue(std::u16string(u"Value2") == std::u16string(bufu2));
			Assert::IsTrue(std::u16string(u"E2 Unicode1") == pe2->GetNextUnicodeString());
			Assert::IsFalse(pe2->IsDataAvailable());
			Assert::ExpectException<std::runtime_error>([&] {pe2->GetNextByte(); });


			Assert::IsFalse(p.IsDataAvailable());

			delete pe2;
		}
		
		TEST_METHOD(TestRecursiveEmbeddedObjects)
		{

			CSTXProtocol p;
			p.AppendData("Main");

			CSTXProtocol e1;
			e1.AppendData("Child Level 1");

			CSTXProtocol e2;
			e2.AppendData(u"Second Level Child");

			e1.AppendData(&e2);
			p.AppendData(&e1);

			//Now retrieving

			Assert::IsTrue(std::u16string(u"Main") == p.GetNextUnicodeString());

			CSTXProtocol *pc1 = p.GetNextObject();
			Assert::IsNotNull(pc1);
			Assert::IsTrue(std::u16string(u"Child Level 1") == pc1->GetNextUnicodeString());

			CSTXProtocol *pc2 = pc1->GetNextObject();
			Assert::IsNotNull(pc2);
			Assert::IsFalse(pc1->IsDataAvailable());

			Assert::IsTrue(std::u16string(u"Second Level Child") ==  pc2->GetNextUnicodeString());
			Assert::IsFalse(pc2->IsDataAvailable());

			delete pc2;
			delete pc1;

		}


	};
}