#include "stdafx.h"
#include "CppUnitTest.h"

#include "../ProtocolPackage/STXProtocol.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProtocolPackageTest
{		
	TEST_CLASS(UnitTest_RetrieveUnexpectedType)
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
		TEST_METHOD(TestSimpleRetrieveUnexpectedPrimitive)
		{
			CSTXProtocol proPrimitives;

			proPrimitives.AppendData((uint16_t)123);
			proPrimitives.AppendData((unsigned char)254);
			proPrimitives.AppendData((uint32_t)175553337);
			proPrimitives.AppendData((int64_t)301194722233);
			proPrimitives.AppendData((float)123.32);
			proPrimitives.AppendData((double)3291.876);

			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextByte(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextDWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextString(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char buf[32];  proPrimitives.GetNextRawData((void*)buf, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; wchar_t buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; wchar_t buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextString(&s); });

			Assert::IsTrue(uint16_t(123) == proPrimitives.GetNextWORD());

			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextDWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextString(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char buf[32];  proPrimitives.GetNextRawData((void*)buf, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; wchar_t buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; wchar_t buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextString(&s); });

			Assert::IsTrue((unsigned char)254 == proPrimitives.GetNextByte());

			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextByte(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextString(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char buf[32];  proPrimitives.GetNextRawData((void*)buf, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; wchar_t buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; wchar_t buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextString(&s); });

			Assert::IsTrue((uint32_t)175553337 == proPrimitives.GetNextDWORD());

			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextByte(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextDWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextString(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char buf[32];  proPrimitives.GetNextRawData((void*)buf, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; wchar_t buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; wchar_t buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextString(&s); });

			Assert::IsTrue((int64_t)301194722233 == proPrimitives.GetNextI64());

			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextByte(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextDWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextString(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char buf[32];  proPrimitives.GetNextRawData((void*)buf, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; wchar_t buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; wchar_t buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextString(&s); });

			float f = proPrimitives.GetNextFloat();
			Assert::IsTrue(abs(f - 123.32) < 0.00001f);

			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextByte(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextDWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextString(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char buf[32];  proPrimitives.GetNextRawData((void*)buf, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; wchar_t buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; wchar_t buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextString(&s); });

			double d = proPrimitives.GetNextDouble();
			Assert::IsTrue(abs(d - 3291.876) < 0.0000001);
		}
		
		TEST_METHOD(TestSimpleRetrieveUnexpectedString)
		{
			CSTXProtocol proStrings;
			proStrings.AppendData("Hello World");
			proStrings.AppendData("Hello Kitty");
			proStrings.AppendUnicodeString(L"World");

			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextByte(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextDWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char buf[32];  proStrings.GetNextRawData((void*)buf, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; wchar_t buf2[32] = { 0 }; proStrings.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proStrings.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; wchar_t buf2[32] = { 0 }; proStrings.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proStrings.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });

			Assert::AreEqual(std::string("Hello World"), proStrings.GetNextString());

			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextDWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char buf[32];  proStrings.GetNextRawData((void*)buf, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; wchar_t buf2[32] = { 0 }; proStrings.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proStrings.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; wchar_t buf2[32] = { 0 }; proStrings.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proStrings.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });


			Assert::AreEqual(std::string("Hello Kitty"), proStrings.GetNextString());

			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextDWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char buf[32];  proStrings.GetNextRawData((void*)buf, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; wchar_t buf2[32] = { 0 }; proStrings.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proStrings.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {wchar_t buf1[32] = { 0 }; wchar_t buf2[32] = { 0 }; proStrings.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proStrings.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });

			Assert::AreEqual(std::string("World"), proStrings.GetNextString());

		}
	};
}