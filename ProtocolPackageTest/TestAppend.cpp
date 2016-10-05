#include "stdafx.h"
#include "CppUnitTest.h"

#include "../ProtocolPackage/STXProtocol.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProtocolPackageTest
{		
	TEST_CLASS(UnitTest_Append)
	{
		CSTXProtocol proPrimitives;
		CSTXProtocol proStrings;
		CSTXProtocol proPairs;
		CSTXProtocol proRaws;

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
		TEST_METHOD(TestSimpleAppendPrimitive)
		{
			size_t expectLength = 2;		//By default, an empty package has length and CRC data. 
			Assert::AreEqual(expectLength, proPrimitives.GetDataLen());		//Length, CRC

			//Add WORD, Type + WORD[2]
			proPrimitives.AppendData((uint16_t)123);
			expectLength += 3;
			Assert::AreEqual(expectLength, proPrimitives.GetDataLen());

			//Add Byte, Type + Byte[1]
			proPrimitives.AppendData((unsigned char)254);
			expectLength += 2;
			Assert::AreEqual(expectLength, proPrimitives.GetDataLen());

			//Add DWORD, Type + DWORD[4]
			proPrimitives.AppendData((uint32_t)175553337);
			expectLength += 5;
			Assert::AreEqual(expectLength, proPrimitives.GetDataLen());

			//Add int64, Type + int64[8]
			proPrimitives.AppendData((int64_t)123);
			expectLength += 9;
			Assert::AreEqual(expectLength, proPrimitives.GetDataLen());

			//Add float, Type + float[4]
			proPrimitives.AppendData((float)123.32);
			expectLength += 5;
			Assert::AreEqual(expectLength, proPrimitives.GetDataLen());

			//Add double, Type + double[8]
			proPrimitives.AppendData((double)3291.876);
			expectLength += 9;
			Assert::AreEqual(expectLength, proPrimitives.GetDataLen());

		}
		
		TEST_METHOD(TestSimpleAppendString)
		{
			size_t expectLength = 2;		//By default, an empty package has length and CRC data. 
			Assert::AreEqual(expectLength, proStrings.GetDataLen());		//Length, CRC

			//Add string 'Hello World', Type + lenthPrefix + content[11]
			proStrings.AppendData("Hello World");
			expectLength += 13;
			Assert::AreEqual(expectLength, proStrings.GetDataLen());

			//Add Unicode string as UTF8 'Hello Kitty', Type + lenthPrefix + content[11]
			proStrings.AppendData(u"Hello Kitty");
			expectLength += 13;
			Assert::AreEqual(expectLength, proStrings.GetDataLen());

			//Add raw data 'Hello', Type + lenthPrefix + content[5]
			proStrings.AppendRawData("Hello", 5);
			expectLength += 7;
			Assert::AreEqual(expectLength, proStrings.GetDataLen());

			//Add as Unicode string 'Hello', Type + lenthPrefix + content[10]
			proStrings.AppendUnicodeString(u"World");
			expectLength += 12;
			Assert::AreEqual(expectLength, proStrings.GetDataLen());

			//Add as empty string , Type + lenthPrefix + content[0]
			proStrings.AppendData("");
			expectLength += 2;
			Assert::AreEqual(expectLength, proStrings.GetDataLen());

		}

		TEST_METHOD(TestAppendLongString)
		{
			size_t expectLength = 2;		//By default, an empty package has length and CRC data. 
			Assert::AreEqual(expectLength, proStrings.GetDataLen());		//Length, CRC

			size_t lengthPrefixWhole = CSTXProtocol::GetCompactIntegerLen(expectLength);

			//Add string 'Hello World', Type + lenthPrefix + content[?]
			const char str1[] = "Maybe you glance through a ground-floor window and your gaze lingers a little longer than it should because the twinkle of a chandelier catches your eye. Or maybe the crisp lines of a doorman¡¯s uniform make you pause or maybe it¡¯s the gentle hand he proffers to help an elderly resident cross the threshold.";
			size_t strLen1 = strlen(str1);
			size_t lengthPrefixLen1 = CSTXProtocol::GetCompactIntegerLen(strLen1);
			proStrings.AppendData(str1);
			expectLength += (1 + lengthPrefixLen1 + strLen1);

			//for large data appended, the length of the whole package might also be extended to mote bytes.
			size_t lengthPrefixWholeAfter = CSTXProtocol::GetCompactIntegerLen(expectLength);

			Assert::AreEqual(expectLength + (lengthPrefixWholeAfter - lengthPrefixWhole), proStrings.GetDataLen());
		}

		TEST_METHOD(TestAppendPair)
		{
			size_t expectLength = 2;		//By default, an empty package has length and CRC data. 
			Assert::AreEqual(expectLength, proPairs.GetDataLen());		//Length, CRC

			//Add string pair 'Hello'/'World', Type + lenthPrefix1 + content1[5] + lenthPrefix2 + content2[5]
			proPairs.AppendDataPair("Hello", "World");
			expectLength += 13;
			Assert::AreEqual(expectLength, proPairs.GetDataLen());	

			//Add Unicode string pair 'Hello'/'World' but stored as UTF8 string pair, Type + lenthPrefix1 + content1[5] + lenthPrefix2 + content2[5]
			proPairs.AppendDataPair(u"Hello", u"Kitty");
			expectLength += 13;
			Assert::AreEqual(expectLength, proPairs.GetDataLen());
		
			//Add pair string/DWORD 'Hello'/1024, Type + lenthPrefix1 + content1[5] + DWORD[4]
			proPairs.AppendDataPair("Hello", 1024);
			expectLength += 11;
			Assert::AreEqual(expectLength, proPairs.GetDataLen());

			//Add pair string/DWORD 'Hi there'/1921, Type + lenthPrefix1 + content1[8] + DWORD[4]
			proPairs.AppendDataPair(u"Hi there", 1921);
			expectLength += 14;
			Assert::AreEqual(expectLength, proPairs.GetDataLen());

			//Add Unicode string pair 'Go'/'Home', Type + lenthPrefix1 + content1[4] + lenthPrefix2 + content2[8]
			proPairs.AppendUnicodeStringPair("Go", "Home");
			expectLength += 15;
			Assert::AreEqual(expectLength, proPairs.GetDataLen());
		}
		TEST_METHOD(TestAppendRawData)
		{
			size_t expectLength = 2;		//By default, an empty package has length and CRC data. 
			Assert::AreEqual(expectLength, proRaws.GetDataLen());		//Length, CRC

			//Add raw bytes data, Type + lenthPrefix + content[12]
			char rawData1[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
			proRaws.AppendRawData(rawData1, 12);
			expectLength += 14;
			Assert::AreEqual(expectLength, proRaws.GetDataLen());

			//Add raw bytes data, Type + lenthPrefix + content[7]
			char rawData2[7] = { 11,12,13,14,15,16,17 };
			proRaws.AppendRawData(rawData2, 7);
			expectLength += 9;
			Assert::AreEqual(expectLength, proRaws.GetDataLen());

			//Add empty raw data, Type + lenthPrefix + content[0]
			proRaws.AppendRawData(nullptr, 0);
			expectLength += 2;
			Assert::AreEqual(expectLength, proRaws.GetDataLen());

			//Add typed raw data, Type + lenthPrefix + content[?]
			proRaws.AppendData<int>(1020);
			expectLength += 1 + 1 + sizeof(int);
			Assert::AreEqual(expectLength, proRaws.GetDataLen());
		}

		TEST_METHOD(TestAppendGUID)
		{
			CSTXProtocol proGUID;

			size_t expectLength = 2;		//By default, an empty package has length and CRC data. 
			Assert::AreEqual(expectLength, proGUID.GetDataLen());		//Length, CRC

			//Add guid, Type + content[16]
			GUID g1 = GenerateGUID();
			proGUID.AppendData(g1);
			expectLength += 17;
			Assert::AreEqual(expectLength, proGUID.GetDataLen());
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