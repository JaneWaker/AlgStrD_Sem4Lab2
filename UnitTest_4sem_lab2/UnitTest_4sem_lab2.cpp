#include "CppUnitTest.h"
#include "..\AlgStrD_4sem_lab2\Shannon-Fano.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace My4sem2test
{
	TEST_CLASS(My4sem2test)
	{
	public:

		TEST_METHOD(EasyString)
		{
			char* string = new char[5]{ 'h','e','l','l','o' };
			ShannonFano * test = new ShannonFano(string, 5);
			bool* code = test->MarkString();
			char* decode = test->DecodeString();
			for (size_t i = 0; i < 5; i++)
			{
				Assert::AreEqual(string[i], decode[i]);
			}
		}

		TEST_METHOD(OneLetter)
		{
			char* string = new char[1]{ 'h' };
			ShannonFano* test = new ShannonFano(string, 1);
			bool* code = test->MarkString();
			Assert::AreEqual(test->GetMarkLength(), 1);
			char* decode = test->DecodeString();
			for (size_t i = 0; i < 1; i++)
			{
				Assert::AreEqual(string[i], decode[i]);
			}
		}

		TEST_METHOD(FullOfSameLetter)
		{
			char* string = new char[5]{ '!','!','!','!','!' };
			ShannonFano* test = new ShannonFano(string, 5);
			bool* code = test->MarkString();
			Assert::AreEqual(test->GetMarkLength(), 5);
			char* decode = test->DecodeString();
			for (size_t i = 0; i < 5; i++)
			{
				Assert::AreEqual(string[i], decode[i]);
			}
		}

		TEST_METHOD(String1)
		{
			char* string = new char[56]{ 'F','i','v','e',' ','e','x','c','l','a','m','a','t','i','o','n',' ','m','a','r','k','s',',',' ','t','h','e',' ','s','u','r','e',' ','s','i','g','n',' ','o','f',' ','a','n',' ','i','n','s','a','n','e',' ','m','i','n','d','.' };
			ShannonFano* test = new ShannonFano(string, 56);
			bool* code = test->MarkString();
			char* decode = test->DecodeString();
			for (size_t i = 0; i < 56; i++)
			{
				Assert::AreEqual(string[i], decode[i]);
			}
		}

		TEST_METHOD(String2)
		{
			char* string = new char[10]{ 'a','o', 'a','o', 'a','o', 'a','o', 'a','o' };
			ShannonFano* test = new ShannonFano(string, 10);
			bool* code = test->MarkString();
			char* decode = test->DecodeString();
			for (size_t i = 0; i < 10; i++)
			{
				Assert::AreEqual(string[i], decode[i]);
			}
		}

		TEST_METHOD(String3)
		{
			char* string = new char[16]{ 'E','a','r','t','h',' ','i','s',' ','a',' ','l','i','b','r','a' };
			ShannonFano* test = new ShannonFano(string, 16);
			bool* code = test->MarkString();
			char* decode = test->DecodeString();
			for (size_t i = 0; i < 16; i++)
			{
				Assert::AreEqual(string[i], decode[i]);
			}
		}

		TEST_METHOD(nullString)
		{
			ShannonFano* test = new ShannonFano(NULL, 0);
			bool* code = test->MarkString();
			Assert::AreEqual(NULL, test->DecodeString());
		}
	};
}
