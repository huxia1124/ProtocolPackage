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
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPrimitives.GetNextStringToDWORDPair(buf1, 32); });

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
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPrimitives.GetNextStringToDWORDPair(buf1, 32); });

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
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPrimitives.GetNextStringToDWORDPair(buf1, 32); });

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
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPrimitives.GetNextStringToDWORDPair(buf1, 32); });

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
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPrimitives.GetNextStringToDWORDPair(buf1, 32); });

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
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPrimitives.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; proPrimitives.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proPrimitives.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPrimitives.GetNextString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPrimitives.GetNextStringToDWORDPair(buf1, 32); });

			double d = proPrimitives.GetNextDouble();
			Assert::IsTrue(abs(d - 3291.876) < 0.0000001);
		}
		
		TEST_METHOD(TestSimpleRetrieveUnexpectedString)
		{
			CSTXProtocol proStrings;
			proStrings.AppendData("Hello World");
			proStrings.AppendData("Hello Kitty");
			proStrings.AppendUnicodeString(u"World");

			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextByte(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextDWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char buf[32];  proStrings.GetNextRawData((void*)buf, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proStrings.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proStrings.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proStrings.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proStrings.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proStrings.GetNextStringToDWORDPair(buf1, 32); });

			Assert::AreEqual(std::string("Hello World"), proStrings.GetNextString());

			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextDWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char buf[32];  proStrings.GetNextRawData((void*)buf, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proStrings.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proStrings.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proStrings.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proStrings.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proStrings.GetNextStringToDWORDPair(buf1, 32); });

			Assert::AreEqual(std::string("Hello Kitty"), proStrings.GetNextString());

			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextDWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proStrings.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char buf[32];  proStrings.GetNextRawData((void*)buf, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proStrings.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proStrings.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proStrings.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proStrings.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proStrings.GetNextStringToDWORDPair(buf1, 32); });

			Assert::AreEqual(std::string("World"), proStrings.GetNextString());
		}
		TEST_METHOD(TestSimpleRetrieveUnexpectedPairs)
		{
			CSTXProtocol proPairs;
			proPairs.AppendDataPair("Hello", "World");
			proPairs.AppendDataPair(u"Hello", u"Kitty");
			proPairs.AppendDataPair("Hello", 1024);
			proPairs.AppendDataPair(u"Hi there", 1921);
			proPairs.AppendUnicodeStringPair("Go", "Home");

			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextByte(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextString(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char buf[32];  proPairs.GetNextRawData((void*)buf, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPairs.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; proPairs.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPairs.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPairs.GetNextString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPairs.GetNextStringToDWORDPair(buf1, 32); });

			proPairs.SkipNextField();

			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextByte(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextString(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char buf[32];  proPairs.GetNextRawData((void*)buf, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPairs.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; proPairs.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPairs.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPairs.GetNextString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPairs.GetNextStringToDWORDPair(buf1, 32); });

			proPairs.SkipNextField();

			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextByte(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextString(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char buf[32];  proPairs.GetNextRawData((void*)buf, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPairs.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; proPairs.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPairs.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPairs.GetNextString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proPairs.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPairs.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proPairs.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPairs.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });

			proPairs.SkipNextField();

			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextByte(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextString(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char buf[32];  proPairs.GetNextRawData((void*)buf, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPairs.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; proPairs.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPairs.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPairs.GetNextString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proPairs.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPairs.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proPairs.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proPairs.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });

			proPairs.SkipNextField();

			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextByte(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextString(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char buf[32];  proPairs.GetNextRawData((void*)buf, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPairs.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; proPairs.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proPairs.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPairs.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proPairs.GetNextString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proPairs.GetNextStringToDWORDPair(buf1, 32); });

		}
		TEST_METHOD(TestSimpleRetrieveUnexpectedRawData)
		{
			CSTXProtocol proRaws;
			char rawData1[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
			proRaws.AppendRawData(rawData1, 12);
			char rawData2[7] = { 11,12,13,14,15,16,17 };
			proRaws.AppendRawData(rawData2, 7);
			proRaws.AppendRawData(nullptr, 0);

			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextByte(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextDWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextString(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proRaws.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proRaws.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proRaws.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proRaws.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proRaws.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; proRaws.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proRaws.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proRaws.GetNextString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proRaws.GetNextStringToDWORDPair(buf1, 32); });

			proRaws.SkipNextField();

			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextByte(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextDWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextString(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proRaws.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proRaws.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proRaws.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proRaws.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proRaws.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; proRaws.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proRaws.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proRaws.GetNextString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proRaws.GetNextStringToDWORDPair(buf1, 32); });

			proRaws.SkipNextField();

			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextByte(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextDWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextString(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextGUID(); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proRaws.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proRaws.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proRaws.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proRaws.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proRaws.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; proRaws.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proRaws.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proRaws.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proRaws.GetNextString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proRaws.GetNextStringToDWORDPair(buf1, 32); });

		}
		TEST_METHOD(TestSimpleRetrieveUnexpectedGUID)
		{
			CSTXProtocol proGUID;
			GUID g1 = GenerateGUID();
			proGUID.AppendData(g1);

			Assert::ExpectException<std::runtime_error>([&] {proGUID.GetNextByte(); });
			Assert::ExpectException<std::runtime_error>([&] {proGUID.GetNextWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proGUID.GetNextDWORD(); });
			Assert::ExpectException<std::runtime_error>([&] {proGUID.GetNextI64(); });
			Assert::ExpectException<std::runtime_error>([&] {proGUID.GetNextFloat(); });
			Assert::ExpectException<std::runtime_error>([&] {proGUID.GetNextDouble(); });
			Assert::ExpectException<std::runtime_error>([&] {proGUID.GetNextString(); });
			Assert::ExpectException<std::runtime_error>([&] {proGUID.GetNextObject(); });
			Assert::ExpectException<std::runtime_error>([&] {char buf[32];  proGUID.GetNextRawData((void*)buf, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proGUID.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proGUID.GetNextStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; char16_t buf2[32] = { 0 }; proGUID.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; char buf2[32] = { 0 }; proGUID.GetNextUnicodeStringPair(buf1, 32, buf2, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proGUID.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {char16_t buf1[32] = { 0 }; proGUID.GetNextUnicodeString(buf1, 32); });
			Assert::ExpectException<std::runtime_error>([&] {proGUID.GetNextUnicodeString(); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proGUID.GetNextUnicodeString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {CSTXProtocolString s; proGUID.GetNextString(&s); });
			Assert::ExpectException<std::runtime_error>([&] {char buf1[32] = { 0 }; proGUID.GetNextStringToDWORDPair(buf1, 32); });
		}
	};
}