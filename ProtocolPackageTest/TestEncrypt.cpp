#include "stdafx.h"
#include "CppUnitTest.h"

#include "../ProtocolPackage/STXProtocol.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProtocolPackageTest
{		
	TEST_CLASS(UnitTest_Encrypt)
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
		static void STXProtocolEnumFuncImpl(unsigned char originalType, STXPROTOCOLVALUE *pVal, STXPROTOCOLVALUE *pValExtra, void *pUserData)
		{
			std::string &s = *((std::string*)pUserData);

			CSTXProtocolString val(pVal);
			CSTXProtocolString valExtra(pValExtra);
			if (pVal->nValueType == STXPROTOCOL_DATA_TYPE_OBJECT)
			{
				s += ">>";
				pVal->pObject->EnumValues(STXProtocolEnumFuncImpl, &s);
				s += "<<";
			}
			else if (pValExtra->nValueType != STXPROTOCOL_DATA_TYPE_INVALID)
			{
				s += CSTXProtocol::GetTypeString(originalType);
				s += ":";
				s += (const char*)val;
				s += ",";
				s += (const char*)valExtra;
				s += "\n";
			}
			else
			{
				s += CSTXProtocol::GetTypeString(originalType);
				s += ":";
				s += (const char*)val;
				s += "\n";
			}
		}
		TEST_METHOD(TestSimpleEncrypt)
		{
			GUID g1 = GenerateGUID();

			CSTXProtocol p;

			//Add some data
			p.AppendData((uint16_t)123);
			p.AppendData((unsigned char)254);
			p.AppendData((uint32_t)175553337);
			p.AppendData((int64_t)301194722233);
			p.AppendData((int64_t)-92865553832);
			p.AppendUnicodeString(u"Unicode String");
			p.AppendData("Test1");
			p.AppendDataPair("Key1", "Val1");
			p.AppendDataPair("Key2", 96);
			p.AppendData(g1);

			//Get a copy of raw data
			long len = p.GetDataLen();
			char *pDataOriginal = new char[len];
			memcpy(pDataOriginal, p.GetBasePtr(), p.GetDataLen());

			//Remove all data and add again the same data
			p.Clear();

			p.AppendData((uint16_t)123);
			p.AppendData((unsigned char)254);
			p.AppendData((uint32_t)175553337);
			p.AppendData((int64_t)301194722233);
			p.AppendData((int64_t)-92865553832);
			p.AppendUnicodeString(u"Unicode String");
			p.AppendData("Test1");
			p.AppendDataPair("Key1", "Val1");
			p.AppendDataPair("Key2", 96);
			p.AppendData(g1);

			//Get raw data once again
			char *pData = new char[len];
			memcpy(pData, p.GetBasePtr(), p.GetDataLen());

			//Raw data should be the same
			Assert::AreEqual(0, memcmp(pData, pDataOriginal, p.GetDataLen()));

			delete []pDataOriginal;

			for (uint32_t i = 0; i < 10; i++)
			{
				uint32_t key = 0x3233AC40 + i;
				p.GetEncryptedData(pData, len, key);
				Assert::AreNotEqual(0, memcmp(p.GetBasePtr(), pData, p.GetDataLen()));

				long dataLen = 0;
				CSTXProtocol pd;
				pd.DecodeWithDecrypt(pData, &dataLen, key);

				Assert::IsTrue(p.GetDataLen() == pd.GetDataLen());
				Assert::AreEqual(0, memcmp(p.GetBasePtr(), pd.GetBasePtr(), p.GetDataLen()));
			}

			uint32_t key2 = 0xADE34B90;
			p.GetEncryptedData(pData, len, key2);

			for (uint32_t i = key2 - 128; i < key2 + 128; i++)
			{
				if(i != key2)
					Assert::ExpectException<std::runtime_error>([&] {CSTXProtocol pd2; pd2.DecodeWithDecrypt(pData, nullptr, key2 + 1); });
			}

			delete[]pData;
		}

	};
}