#include "stdafx.h"
#include "CppUnitTest.h"

#include "../ProtocolPackage/STXProtocol.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProtocolPackageTest
{		
	TEST_CLASS(UnitTest_Retrieve)
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
		TEST_METHOD(TestSimpleRetrievePrimitive)
		{
			CSTXProtocol proPrimitives;
			proPrimitives.AppendData((uint16_t)123);
			proPrimitives.AppendData((unsigned char)254);
			proPrimitives.AppendData((uint32_t)175553337);
			proPrimitives.AppendData((int64_t)301194722233);
			proPrimitives.AppendData((int64_t)-92865553832);
			proPrimitives.AppendData((float)123.32);
			proPrimitives.AppendData((double)3291.876);

			Assert::IsTrue(proPrimitives.GetNextFieldType() == STXPROTOCOL_DATA_TYPE_WORD);
			Assert::IsTrue(uint16_t(123) == proPrimitives.GetNextWORD());
			Assert::IsTrue((unsigned char)254 == proPrimitives.GetNextByte());
			Assert::IsTrue((uint32_t)175553337 == proPrimitives.GetNextDWORD());
			Assert::IsTrue((int64_t)301194722233 == proPrimitives.GetNextI64());
			Assert::IsTrue((int64_t)-92865553832 == proPrimitives.GetNextI64());
			float f = proPrimitives.GetNextFloat();
			Assert::IsTrue(abs(f - 123.32) < 0.00001f);
			double d = proPrimitives.GetNextDouble();
			Assert::IsTrue(abs(d - 3291.876) < 0.0000001);
		}
		
		TEST_METHOD(TestSimpleRetrieveString)
		{
			CSTXProtocol proStrings;
			proStrings.AppendData("Hello World");		//Store as UTF8
			proStrings.AppendData("Hello Kitty");		//Store as UTF8
			proStrings.AppendData("Test");				//Store as UTF8
			proStrings.AppendData("More Test");			//Store as UTF8
			proStrings.AppendData(u"More Unicode Test");		//Store as UTF8
			proStrings.AppendRawData("Hello", 5);
			proStrings.AppendUnicodeString(u"World");			//Store as Unicode(char16_t)
			proStrings.AppendUnicodeString(u"Try Another One 123");		//Store as Unicode(char16_t)
			proStrings.AppendUnicodeString(u"!!@@##$$%%");		//Store as Unicode(char16_t)
			proStrings.AppendData("Another String UTF8");		//Store as UTF8
			proStrings.AppendUnicodeString("Unicode Again");		//Store as Unicode(char16_t)
			proStrings.AppendData("Test1");		//Store as UTF8
			proStrings.AppendData("Test2");		//Store as UTF8

			Assert::AreEqual(std::string("Hello World"), proStrings.GetNextString());
			Assert::AreEqual(std::string("Hello Kitty"), proStrings.GetNextString());
			char16_t buf[64] = {0};
			proStrings.GetNextString(buf, 64);
			Assert::IsTrue(std::u16string(u"Test") == std::u16string(buf));

			char buf2[64] = { 0 };
			proStrings.GetNextString(buf2, 64);
			Assert::AreEqual(std::string("More Test"), std::string(buf2));

			proStrings.GetNextString(buf2, 64);
			Assert::AreEqual(std::string("More Unicode Test"), std::string(buf2));

			char bufRaw[32] = { 0 };
			proStrings.GetNextRawData((void*)bufRaw, 32);
			Assert::AreEqual(0, memcmp(bufRaw, "Hello", 5));

			char16_t bufUnicode[64] = { 0 };
			proStrings.GetNextUnicodeString(bufUnicode, 32);
			Assert::IsTrue(std::u16string(u"World") == std::u16string(bufUnicode));

			proStrings.GetNextString(buf2, 64);
			Assert::AreEqual(std::string("Try Another One 123"), std::string(buf2));

			Assert::AreEqual(std::string("!!@@##$$%%"), proStrings.GetNextString());

			Assert::IsTrue(std::u16string(u"Another String UTF8") == proStrings.GetNextUnicodeString());
			Assert::IsTrue(std::u16string(u"Unicode Again") == proStrings.GetNextUnicodeString());

			CSTXProtocolString s1;
			proStrings.GetNextString(&s1);
			Assert::AreEqual(std::string("Test1"), std::string((const char*)s1));

			CSTXProtocolString s2;
			proStrings.GetNextString(&s2);
			Assert::IsTrue(std::u16string(u"Test2") == std::u16string((const char16_t*)s2));

		}

		TEST_METHOD(TestRetrieveLongString)
		{
			CSTXProtocol proStrings;

			//Add string 'Hello World', Type + lenthPrefix + content[?]
			const char str1[] = "Maybe you glance through a ground-floor window and your gaze lingers a little longer than it should because the twinkle of a chandelier catches your eye. Or maybe the crisp lines of a doorman¡¯s uniform make you pause or maybe it¡¯s the gentle hand he proffers to help an elderly resident cross the threshold.";
			proStrings.AppendData(str1);
			std::string result = proStrings.GetNextString();

			Assert::AreEqual(std::string(str1), result);
		}

		TEST_METHOD(TestRetrievePair)
		{
			CSTXProtocol proPairs;

			proPairs.AppendDataPair("Hello", "World");
			proPairs.AppendDataPair(u"Goodbye", u"Kitty");
			proPairs.AppendDataPair("Nice weather", 1024);
			proPairs.AppendDataPair(u"Hi there", 1921);
			proPairs.AppendUnicodeStringPair("Go", "Home");

			char16_t buf1[64] = { 0 };
			char16_t buf2[64] = { 0 };
			proPairs.GetNextStringPair(buf1, 64, buf2, 64);
			Assert::IsTrue(std::u16string(u"Hello") == std::u16string(buf1));
			Assert::IsTrue(std::u16string(u"World") == std::u16string(buf2));

			proPairs.GetNextStringPair(buf1, 64, buf2, 64);
			Assert::IsTrue(std::u16string(u"Goodbye") == std::u16string(buf1));
			Assert::IsTrue(std::u16string(u"Kitty") == std::u16string(buf2));

			uint32_t val = proPairs.GetNextStringToDWORDPair(buf1, 64);
			Assert::IsTrue(std::u16string(u"Nice weather") == std::u16string(buf1));
			Assert::AreEqual(uint32_t(1024), val);

			val = proPairs.GetNextStringToDWORDPair(buf2, 64);
			Assert::IsTrue(std::u16string(u"Hi there") == std::u16string(buf2));
			Assert::AreEqual(uint32_t(1921), val);

			proPairs.GetNextUnicodeStringPair(buf1, 64, buf2, 64);
			Assert::IsTrue(std::u16string(u"Go") == std::u16string(buf1));
			Assert::IsTrue(std::u16string(u"Home") == std::u16string(buf2));

		}
		TEST_METHOD(TestRetrieveRawData)
		{
			CSTXProtocol proRaws;

			const char rawData1[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
			proRaws.AppendRawData((void*)rawData1, 12);
			const char rawData2[7] = { 11,12,13,14,15,16,17 };
			proRaws.AppendRawData((void*)rawData2, 7);
			proRaws.AppendRawData(nullptr, 0);

			char rawBuf[128] = { 0 };
			int len = proRaws.GetNextRawData(rawBuf, 128);
			Assert::AreEqual(sizeof(rawData1), (unsigned int)len);
			Assert::AreEqual(0, memcmp(rawBuf, rawData1, len));

			len = proRaws.GetNextRawData(rawBuf, 128);
			Assert::AreEqual(sizeof(rawData2), (unsigned int)len);
			Assert::AreEqual(0, memcmp(rawBuf, rawData2, len));

			char rawBufEmpty[16] = { 0 };
			char rawBufEmptyCompare[16] = { 0 };
			len = proRaws.GetNextRawData(rawBufEmpty, 16);
			Assert::AreEqual(0, len);
			Assert::AreEqual(0, memcmp(rawBufEmptyCompare, rawBufEmpty, 16));	//Input buffer should not be touched
		}

		TEST_METHOD(TestRetrieveGUID)
		{
			CSTXProtocol proGUID;
			GUID g1 = GenerateGUID();
			proGUID.AppendData(g1);

			GUID g2 = proGUID.GetNextGUID();
			Assert::AreEqual(0, memcmp(&g1, &g2, sizeof(g1)));
		}

		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
			GUID guid;
			guid.Data1 = 0xAE3C55DA;
			guid.Data2 = 12765;
			guid.Data3 = 7883;
			for (int i = 0; i < 8; i++)
				guid.Data4[i] = rand() % 256;

			CSTXProtocol pro;
			CSTXProtocol proEmbedded;
			proEmbedded.AppendData("Hello");
			proEmbedded.AppendData("World");
			/*
			pro.AppendData("Abc");
			pro.AppendData((uint32_t)32);
			pro.AppendData((int64_t)64);
			pro.AppendData((uint16_t)16);
			pro.AppendData((unsigned char)'C');
			pro.AppendUnicodeString(u"Unicode");
			pro.AppendUnicodeString(u"UnicodeString2");
			pro.AppendData(guid);
			*/
			pro.AppendDataPair(u"Data1", 1024);
			pro.AppendData(&proEmbedded);
			//pro.AppendUnicodeStringPair(u"UPKey1", u"UPValue1");
			pro.AppendDataPair("Data2", 2048);

			pro.SeekReadToBegin();

			/*
			pro.EnumValues([&](STXPROTOCOLVALUE *pVal, STXPROTOCOLVALUE *pValExtra, void *pUserData)
			{
			CSTXProtocolString val(pVal);
			CSTXProtocolString valExtra(pValExtra);
			if (pVal->nValueType != STXPROTOCOL_DATA_TYPE_OBJECT)
			{
			pVal->pObject->EnumValues()
			}
			else if (pValExtra->nValueType != STXPROTOCOL_DATA_TYPE_INVALID)
			{
			std::cout << CSTXProtocol::GetTypeString(pVal->nValueType) << ": " << (const char*)val << "\t" << (const char*)valExtra << std::endl;
			}
			else
			{
			std::cout << CSTXProtocol::GetTypeString(pVal->nValueType) << ": " << (const char*)val << std::endl;
			}

			}, 0);
			*/

			//pro.EnumValues(STXProtocolEnumFuncImpl, 0);

			pro.SeekReadToBegin();
		}

	};
}