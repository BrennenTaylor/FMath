#include <gtest/gtest.h>

#include <FMath/FMath.h>

#include <sstream>
#include <iomanip>

TEST(Vector3, Union) {
    Farlor::Vector3 testVec(1.0, 2.0, 3.0);
    
    EXPECT_NEAR(testVec.x, 1.0, 0.0001);
    EXPECT_NEAR(testVec.y, 2.0, 0.0001);
    EXPECT_NEAR(testVec.z, 3.0, 0.0001);

    testVec.x = 4.0;
    testVec.y = 5.0;
    testVec.z = 6.0;

    EXPECT_NEAR(testVec.m_data.at(0), 4.0, 0.0001);
    EXPECT_NEAR(testVec.m_data.at(1), 5.0, 0.0001);
    EXPECT_NEAR(testVec.m_data.at(2), 6.0, 0.0001);
}

TEST(Vector3, Constructors) {
    {
        const Farlor::Vector3 testVec;
        
        EXPECT_NEAR(testVec.x, 0.0, 0.0001);
        EXPECT_NEAR(testVec.y, 0.0, 0.0001);
        EXPECT_NEAR(testVec.z, 0.0, 0.0001);
    }

    {
        const Farlor::Vector3 testVec(2.5);
        
        EXPECT_NEAR(testVec.x, 2.5f, 0.0001);
        EXPECT_NEAR(testVec.y, 2.5f, 0.0001);
        EXPECT_NEAR(testVec.z, 2.5f, 0.0001);
    }

    {
        const Farlor::Vector3 testVec(1.0, 2.0, 3.0);
        
        EXPECT_NEAR(testVec.x, 1.0, 0.0001);
        EXPECT_NEAR(testVec.y, 2.0, 0.0001);
        EXPECT_NEAR(testVec.z, 3.0, 0.0001);
    }
}

TEST(Vector3, PlusEqOp) {
    Farlor::Vector3 firstVector(1.0, 2.0, 3.0);
    const Farlor::Vector3 secondVector(2.0, 3.0, 4.0);
    
    firstVector += secondVector;

    EXPECT_NEAR(firstVector.x, 3.0, 0.0001);
    EXPECT_NEAR(firstVector.y, 5.0, 0.0001);
    EXPECT_NEAR(firstVector.z, 7.0, 0.0001);
}

TEST(Vector3, PlusOp) {
    const Farlor::Vector3 firstVector(1.0, 2.0, 3.0);
    const Farlor::Vector3 secondVector(2.0, 3.0, 4.0);
    
    const Farlor::Vector3 result = firstVector + secondVector;

    EXPECT_NEAR(result.x, 3.0, 0.0001);
    EXPECT_NEAR(result.y, 5.0, 0.0001);
    EXPECT_NEAR(result.z, 7.0, 0.0001);
}

TEST(Vector3, MinusEqOp) {
    Farlor::Vector3 firstVector(1.0, 2.0, 3.0);
    const Farlor::Vector3 secondVector(2.0, 3.0, 4.0);
    
    firstVector -= secondVector;

    EXPECT_NEAR(firstVector.x, -1.0, 0.0001);
    EXPECT_NEAR(firstVector.y, -1.0, 0.0001);
    EXPECT_NEAR(firstVector.z, -1.0, 0.0001);
}

TEST(Vector3, MinusOp) {
    const Farlor::Vector3 firstVector(1.0, 2.0, 3.0);
    const Farlor::Vector3 secondVector(2.0, 3.0, 4.0);
    
    const Farlor::Vector3 result = firstVector - secondVector;

    EXPECT_NEAR(result.x, -1.0, 0.0001);
    EXPECT_NEAR(result.y, -1.0, 0.0001);
    EXPECT_NEAR(result.z, -1.0, 0.0001);
}

TEST(Vector3, TimesEqOp) {
    Farlor::Vector3 firstVector(1.0, 2.0, 3.0);
    const Farlor::Vector3 secondVector(2.0, 3.0, 4.0);
    
    firstVector *= secondVector;

    EXPECT_NEAR(firstVector.x, 2.0, 0.0001);
    EXPECT_NEAR(firstVector.y, 6.0, 0.0001);
    EXPECT_NEAR(firstVector.z, 12.0, 0.0001);
}

TEST(Vector3, TimesOp) {
    const Farlor::Vector3 firstVector(1.0, 2.0, 3.0);
    const Farlor::Vector3 secondVector(2.0, 3.0, 4.0);
    
    const Farlor::Vector3 result = firstVector * secondVector;

    EXPECT_NEAR(result.x, 2.0, 0.0001);
    EXPECT_NEAR(result.y, 6.0, 0.0001);
    EXPECT_NEAR(result.z, 12.0, 0.0001);
}

TEST(Vector3, DivEqOp) {
    Farlor::Vector3 firstVector(1.0, 2.0, 3.0);
    const Farlor::Vector3 secondVector(2.0, 3.0, 4.0);
    
    firstVector /= secondVector;

    EXPECT_NEAR(firstVector.x, 1.0f / 2.0f, 0.0001);
    EXPECT_NEAR(firstVector.y, 2.0f / 3.0f, 0.0001);
    EXPECT_NEAR(firstVector.z, 3.0f / 4.0f, 0.0001);
}

TEST(Vector3, DivOp) {
    const Farlor::Vector3 firstVector(1.0, 2.0, 3.0);
    const Farlor::Vector3 secondVector(2.0, 3.0, 4.0);
    
    const Farlor::Vector3 result = firstVector / secondVector;

    EXPECT_NEAR(result.x, 1.0f / 2.0f, 0.0001);
    EXPECT_NEAR(result.y, 2.0f / 3.0, 0.0001);
    EXPECT_NEAR(result.z, 3.0f / 4.0f, 0.0001);
}

TEST(Vector3, Equality) {
    const Farlor::Vector3 firstVector(1.0, 2.0, 3.0);
    const Farlor::Vector3 secondVector(1.0, 2.0, 3.0);
    const Farlor::Vector3 thirdVector(2.0, 2.0, 3.0);

    
    EXPECT_TRUE(firstVector == secondVector);
    EXPECT_FALSE(firstVector == thirdVector);
}

TEST(Vector3, NonEquality) {
    const Farlor::Vector3 firstVector(1.0, 2.0, 3.0);
    const Farlor::Vector3 secondVector(1.0, 2.0, 3.0);
    const Farlor::Vector3 thirdVector(2.0, 2.0, 3.0);
    
    EXPECT_TRUE(firstVector != thirdVector);
    EXPECT_FALSE(firstVector != secondVector);
}

TEST(Vector3, Index) {
    Farlor::Vector3 testVec(1.0, 2.0, 3.0);

    EXPECT_NEAR(testVec[0], 1.0f, 0.0001f);
    EXPECT_NEAR(testVec[1], 2.0f, 0.0001f);
    EXPECT_NEAR(testVec[2], 3.0f, 0.0001f);

    testVec[0] = 5.0f;

    EXPECT_NEAR(testVec.x, 5.0f, 0.0001f);
}

TEST(Vector3, TimesScalarEqOp) {
    Farlor::Vector3 firstVector(1.0, 2.0, 3.0);
    const float scalar = 2.0f;
    
    firstVector *= scalar;

    EXPECT_NEAR(firstVector.x, 2.0, 0.0001);
    EXPECT_NEAR(firstVector.y, 4.0, 0.0001);
    EXPECT_NEAR(firstVector.z, 6.0, 0.0001);
}

TEST(Vector3, TimesScalarOp) {
    const Farlor::Vector3 firstVector(1.0, 2.0, 3.0);
    const float scalar = 2.0f;
    
    {
        const Farlor::Vector3 result = firstVector * scalar;

        EXPECT_NEAR(result.x, 2.0, 0.0001);
        EXPECT_NEAR(result.y, 4.0, 0.0001);
        EXPECT_NEAR(result.z, 6.0, 0.0001);
    }

    {
        const Farlor::Vector3 result = scalar * firstVector;

        EXPECT_NEAR(result.x, 2.0, 0.0001);
        EXPECT_NEAR(result.y, 4.0, 0.0001);
        EXPECT_NEAR(result.z, 6.0, 0.0001);
    }
}

TEST(Vector3, DivScalarEqOp) {
    Farlor::Vector3 firstVector(1.0, 2.0, 3.0);
    const float scalar = 2.0f;
    
    firstVector /= scalar;

    EXPECT_NEAR(firstVector.x, 1.0f / 2.0f, 0.0001);
    EXPECT_NEAR(firstVector.y, 2.0f / 2.0f, 0.0001);
    EXPECT_NEAR(firstVector.z, 3.0f / 2.0f, 0.0001);
}

TEST(Vector3, DivScalarOp) {
    const Farlor::Vector3 firstVector(1.0, 2.0, 3.0);
    const float scalar = 2.0f;
    
    const Farlor::Vector3 result = firstVector / scalar;

    EXPECT_NEAR(result.x, 1.0f / 2.0f, 0.0001);
    EXPECT_NEAR(result.y, 2.0f / 2.0, 0.0001);
    EXPECT_NEAR(result.z, 3.0f / 2.0f, 0.0001);
}

TEST(Vector3, Print) {
    std::ostringstream out;
    const Farlor::Vector3 testVector(1.0, 2.0, 3.0);

    out << std::fixed << std::setprecision(2);
    out << testVector;

    EXPECT_EQ("<1.00, 2.00, 3.00>", out.str());
}

TEST(Vector3, Magnitude) {
    const Farlor::Vector3 testVec(1.0, 2.0, 3.0);

    EXPECT_NEAR(testVec.Magnitude(), std::sqrt(1.0f * 1.0f + 2.0f * 2.0f + 3.0f * 3.0f), 0.0001);
}

TEST(Vector3, SqrMagnitude) {
    const Farlor::Vector3 testVec(1.0, 2.0, 3.0);

    EXPECT_NEAR(testVec.SqrMagnitude(), 1.0f * 1.0f + 2.0f * 2.0f + 3.0f * 3.0f, 0.0001);
}

TEST(Vector3, Normalize) {
    Farlor::Vector3 testVec(1.0, 2.0, 3.0);
    testVec *= 2.0f;

    testVec.Normalize();

    EXPECT_NEAR(testVec.Magnitude(), 1.0, 0.0001);
}

TEST(Vector3, Normalized) {
    const Farlor::Vector3 testVec(1.0, 2.0, 3.0);
    const Farlor::Vector3 result = (testVec * 2.0f).Normalized();

    EXPECT_NEAR(result.Magnitude(), 1.0f, 0.0001);
}

TEST(Vector3, Dot) {
    const Farlor::Vector3 firstVector(1.0, 2.0, 3.0);
    const Farlor::Vector3 secondVector(2.0, 3.0, 4.0);
    const float result = firstVector.Dot(secondVector);

    EXPECT_NEAR(result, 2.0f + 6.0f + 12.0f, 0.0001);
}

TEST(Vector3, Cross) {
    const Farlor::Vector3 firstVector(1.0, 0.0, 0.0);
    const Farlor::Vector3 secondVector(0.0, 1.0, 0.0);
    const Farlor::Vector3 result = firstVector.Cross(secondVector);

    EXPECT_NEAR(result.x, 0.0f, 0.0001);
    EXPECT_NEAR(result.y, 0.0f, 0.0001);
    EXPECT_NEAR(result.z, 1.0f, 0.0001);
}