#include "stdafx.h"
#include "CppUnitTest.h"

#include "../ProtocolPackage/STXProtocol.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProtocolPackageTest
{		
	TEST_CLASS(UnitTest_Enum)
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
		TEST_METHOD(TestSimpleEnum)
		{
			CSTXProtocol p;
			p.AppendData((uint16_t)123);
			p.AppendData((unsigned char)254);
			p.AppendData((uint32_t)175553337);
			p.AppendData((int64_t)301194722233);
			p.AppendData((int64_t)-92865553832);

			p.AppendDataPair("Key1", "Val1");
			p.AppendDataPair("Key2", 96);

			std::string s;
			p.EnumValues(STXProtocolEnumFuncImpl, &s);

			Assert::AreEqual(std::string(
				"Word:123\n"
				"Byte:254\n"
				"DWord:175553337\n"
				"int64:301194722233\n"
				"int64:-92865553832\n"
				"UTF-8 Pair:Key1,Val1\n"
				"UTF-8 to uint32_t Pair:Key2,96\n"
			), s);
		
		}

	};
}