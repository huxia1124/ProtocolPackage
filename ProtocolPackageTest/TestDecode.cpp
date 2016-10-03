#include "stdafx.h"
#include "CppUnitTest.h"

#include "../ProtocolPackage/STXProtocol.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProtocolPackageTest
{		
	TEST_CLASS(UnitTest_Decode)
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
		TEST_METHOD(TestSimpleDecode)
		{
			CSTXProtocol p;
			p.AppendData((uint16_t)123);
			p.AppendData((unsigned char)254);
			p.AppendData((uint32_t)175553337);
			p.AppendData((int64_t)301194722233);
			p.AppendData((int64_t)-92865553832);
			p.AppendData((float)123.32);
			p.AppendData((double)3291.876);
			p.AppendData("String");
			p.AppendData(u"Unicode String");
			p.AppendDataPair(u"Key1", 8200);

			unsigned char *buf = new unsigned char[p.GetDataLen()];
			memcpy(buf, p.GetBasePtr(), p.GetDataLen());

			CSTXProtocol dec1;
			Assert::AreEqual(0, dec1.Decode((void*)buf, nullptr));

			Assert::IsTrue(dec1.GetNextFieldType() == STXPROTOCOL_DATA_TYPE_WORD);
			Assert::IsTrue(uint16_t(123) == dec1.GetNextWORD());
			Assert::IsTrue((unsigned char)254 == dec1.GetNextByte());
			Assert::IsTrue((uint32_t)175553337 == dec1.GetNextDWORD());
			Assert::IsTrue((int64_t)301194722233 == dec1.GetNextI64());
			Assert::IsTrue((int64_t)-92865553832 == dec1.GetNextI64());
			Assert::AreEqual(123.32f, dec1.GetNextFloat(), 0.00001f);
			Assert::AreEqual(3291.876, dec1.GetNextDouble(), 0.0000001);
			Assert::AreEqual(std::string("String"), dec1.GetNextString());
			Assert::AreEqual(std::string("Unicode String"), dec1.GetNextString());

			Assert::AreEqual(0, dec1.Decode((void*)buf, nullptr));		// Decode again
			buf[1] = buf[1] + 1;										//change CRC byte
			Assert::ExpectException<std::runtime_error>([&] {dec1.Decode((void*)buf, nullptr); });

			memcpy(buf, p.GetBasePtr(), p.GetDataLen());		//restore
			buf[p.GetDataLen() - 2] ++;							//change some bytes
			buf[p.GetDataLen() - 4] ++;

			Assert::ExpectException<std::runtime_error>([&] {dec1.Decode((void*)buf, nullptr); });

			memcpy(buf, p.GetBasePtr(), p.GetDataLen());		//restore
			buf[0]-=4;											//change the size prefix, reduce 4 bytes
			Assert::ExpectException<std::runtime_error>([&] {dec1.Decode((void*)buf, nullptr, p.GetDataLen()); });

			memcpy(buf, p.GetBasePtr(), p.GetDataLen());		//restore
			buf[0] += 1;											//change the size prefix, reduce 4 bytes
			Assert::ExpectException<std::runtime_error>([&] {dec1.Decode((void*)buf, nullptr, p.GetDataLen()); });


			delete[]buf;

		}

	};
}