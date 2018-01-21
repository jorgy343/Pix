#include "stdafx.h"
#include "CppUnitTest.h"

#include "Matrix44T.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Pix::Base::Tests
{
    TEST_CLASS(Matrix44TTests)
    {
    public:
        TEST_METHOD(GetDeterminant_Test)
        {
            Matrix44T<float> value(
                3, 7, -4, 9,
                -2, -7, 9, 5,
                -7, -9, 4, -6,
                4, 7, 8, -4);

            float result = value.GetDeterminant();
            Assert::AreEqual(5183.0f, result);
        }
    };
}