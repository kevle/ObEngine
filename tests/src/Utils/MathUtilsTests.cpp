#include <catch/catch.hpp>

#include <Utils/MathUtils.hpp>

using namespace obe::Utils::Math;

TEST_CASE("A double should be truncated to an int without data loss (including floating point precision)", "[obe.Utils.Math.isDoubleInt]") 
{
    SECTION("Correct Positive values")
    {
        REQUIRE( isDoubleInt(0.0) == true );
        REQUIRE( isDoubleInt(42.0) == true );
        REQUIRE( isDoubleInt(7894561) == true );
        REQUIRE( isDoubleInt(2147483647) == true );
    }
    SECTION("Correct Negative values")
    {
        REQUIRE( isDoubleInt(-123456) == true );
        REQUIRE( isDoubleInt(-2147483647) == true );
    }
    SECTION("Overflow values")
    {
        REQUIRE( isDoubleInt(2147483648) == false );
        REQUIRE( isDoubleInt(-9000000000) == false );
    }
    SECTION("Floating point precision loss")
    {
        REQUIRE( isDoubleInt(4.5) == false );
        REQUIRE( isDoubleInt(-1.1) == false );
    }
}

TEST_CASE("A value should be converted from degrees to radians", "[obe.Utils.Math.convertToRadian]") 
{
    SECTION("Positive Known Angles")
    {
        REQUIRE(convertToRadian(0) == 0);
        REQUIRE(convertToRadian(90) == Approx(pi / 2));
        REQUIRE(convertToRadian(180) == Approx(pi).margin(0.1));
        REQUIRE(convertToRadian(270) == Approx(pi + pi / 2));
    }
    SECTION("Negative Known Angles")
    {
        REQUIRE(convertToRadian(-90) == Approx(-pi / 2));
        REQUIRE(convertToRadian(-180) == Approx(-pi));
        REQUIRE(convertToRadian(-270) == Approx(-pi - pi / 2));
        REQUIRE(convertToRadian(-360) == Approx(-2 * pi));
    }
    SECTION("Random Angles")
    {
        REQUIRE(convertToRadian(22) == Approx(0.383972));
        REQUIRE(convertToRadian(42) == Approx(0.733038));
        REQUIRE(convertToRadian(-59) == Approx(-1.02974));
        REQUIRE(convertToRadian(-196) == Approx(-3.42085));
    }
}

TEST_CASE("A value should be converted from radians to degrees", "[obe.Utils.Math.convertToDegree]")
{
    
}