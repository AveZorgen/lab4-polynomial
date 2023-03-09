#include <fstream>
#include "Polynomial.h"
#include "gtest/gtest.h"

TEST(Polynomial_Test, create_polynomial) {
    EXPECT_NO_THROW(Polynomial());
}

TEST(Polynomial_Test, can_create_copied_polinomial) {
    Polynomial p1;
    EXPECT_NO_THROW(Polynomial p2(p1));
}

TEST(Polynomial_Test, compare_correctly) {
    Polynomial p1;
    Polynomial p2 = p1;
    EXPECT_EQ(p1, p2);
}


TEST(Polynomial_Test, addasc_correctly) {
    Polynomial p1, p2;
    p1.addasc({4221, 2 });
    p1.addasc({4220, 2 });
    p1.addasc({4222, 2 });
    p1.addasc({4219, 2 });

    p2.addasc({4219, 2 });
    p2.addasc({4220, 2 });
    p2.addasc({4221, 2 });
    p2.addasc({4222, 2 });
    EXPECT_EQ(p1, p2);
}

TEST(Polynomial_Test, clean_correctly) {
    Polynomial p1, p2;
    p1.addasc({4242, 42});
    p1.addasc({4848, 48});
    EXPECT_NE(p1, p2);
    p1.clean();
    EXPECT_EQ(p1, p2);
}

TEST(Polynomial_Test_Source, can_read_polynomial) {
    Polynomial p1;
    ifstream file("source.txt");
    EXPECT_NO_THROW(file >> p1);
}

TEST(Polynomial_Test_Source, fill_polynomial_right) {
    Polynomial p1, p2;
    ifstream file("source.txt"); //-5.2x^-3z^2+32x^1y^3+10 2x^2y^3z^5-1.73y^-7-10
    file >> p1;
    p2.addasc({7, 10, 12, -5.2});
    p2.addasc({11, 13, 10, 32});
    p2.addasc({10, 10, 10, 10});
    EXPECT_EQ(p1, p2);
}

TEST(Polynomial_Test_Source, add_polynomial_correctly) {
    Polynomial p1, p2;
    ifstream file("source.txt"); //-5.2x^-3z^2+32x^1y^3+10 2x^2y^3z^5-1.73y^-7-10
    file >> p1 >> p2;
    Polynomial p3 = p1 + p2;
    Polynomial p4;
    p4.addasc({7, 10, 12, -5.2});
    p4.addasc({10, 3, 10, -1.73});
    p4.addasc({10, 10, 10, -10});
    p4.addasc({10, 10, 10, 10});
    p4.addasc({11, 13, 10, 32});
    p4.addasc({12, 13, 15, 2});
    EXPECT_EQ(p3, p4);
}

TEST(Polynomial_Test_Source, mul_polynomial_correctly) {
    Polynomial p1, p2;
    ifstream file("source.txt"); //-5.2x^-3z^2+32x^1y^3+10 2x^2y^3z^5-1.73y^-7-10
    file >> p1 >> p2;
    Polynomial p3 = p1 * p2;
    Polynomial p4;
    p4.addasc({7, 3, 12, 8.996});
    p4.addasc({7, 10, 12, 52});
    p4.addasc({9, 13, 17, -10.4});
    p4.addasc({10, 3, 10, -17.3});
    p4.addasc({10, 10, 10, -100});
    p4.addasc({11, 6, 10, -55.36});
    p4.addasc({11, 13, 10, -320});
    p4.addasc({12, 13, 15, 20});
    p4.addasc({13, 16, 15, 64});
    EXPECT_EQ(p3, p4);
}

TEST(Polynomial_Test_Source, can_calc_point_value) {
    Polynomial p1;
    ifstream file("source.txt"); //-5.2x^-3z^2+32x^1y^3+10 2x^2y^3z^5-1.73y^-7-10
    file >> p1;
    EXPECT_EQ(p1.approx(1, 0, 0), 10);
    EXPECT_EQ(p1.approx(15, 0, 0), 10);
    EXPECT_EQ(p1.approx(1, 0, 1), 4.8);
    EXPECT_EQ(p1.approx(2, 0, 1), 9.35);
    EXPECT_EQ(p1.approx(2, 1, 1), 73.35);
    EXPECT_EQ(p1.approx(2, 10, 1), 64009.35);
}

TEST(Polynomial_Test_Source2, can_read_polynomial) {
    Polynomial p1;
    ifstream file("source2.txt");
    EXPECT_NO_THROW(file >> p1);
}

TEST(Polynomial_Test_Source2, fill_polynomial_right) {
    Polynomial p1, p2;
    ifstream file("source2.txt"); //5x^2y+3x^2y^2 5y+1z-3x^2y^2z-3y^2
    file >> p1;
    p2.addasc({ 12, 11, 10, 5 });
    p2.addasc({ 12, 12, 10, 3 });
    EXPECT_EQ(p1, p2);
}

TEST(Polynomial_Test_Source2, add_polynomial_correctly) {
    Polynomial p1, p2;
    ifstream file("source2.txt"); //5x^2y+3x^2y^2 5y+1z-3x^2y^2z-3y^2
    file >> p1 >> p2;
    Polynomial p3 = p1 + p2;
    Polynomial p4;
    p4.addasc({ 10, 10, 11, 1 });
    p4.addasc({ 10, 11, 10, 5 });
    p4.addasc({ 10, 12, 10, -3 });
    p4.addasc({ 12, 11, 10, 5 });
    p4.addasc({ 12, 12, 10, 3 });
    p4.addasc({ 12, 12, 11, -3 });
    EXPECT_EQ(p3, p4);
}

TEST(Polynomial_Test_Source2, mul_polynomial_correctly) {
    Polynomial p1, p2;
    ifstream file("source2.txt"); //5x^2y+3x^2y^2 5y+1z-3x^2y^2z-3y^2
    file >> p1 >> p2;
    Polynomial p3 = p1 * p2;
    /*
     * {5| 2, 1, 1| 5031} {25| 2, 2, 0| 5050} {3| 2, 2, 1| 5051} {-9| 2, 4, 0| 5090} {-15| 4, 3, 1| 5871} {-9| 4, 4, 1| 5891}
     */
    Polynomial p4;
    p4.addasc({ 12, 11, 11, 5 });
    p4.addasc({ 12, 12, 10, 25 });
    p4.addasc({ 12, 12, 11, 3 });
    p4.addasc({ 12, 14, 10, -9 });
    p4.addasc({ 14, 13, 11, -15 });
    p4.addasc({ 14, 14, 11, -9 });
    EXPECT_EQ(p3, p4);
}

TEST(Polynomial_Test_Source2, can_calc_point_value) {
    Polynomial p1;
    ifstream file("source2.txt"); //5x^2y+3x^2y^2 5y+1z-3x^2y^2z-3y^2
    file >> p1;
    EXPECT_EQ(p1.approx(1, 0, 0), 0);
    EXPECT_EQ(p1.approx(15, 1, 0), 1800);
    EXPECT_EQ(p1.approx(1, 1, 0), 8);
    EXPECT_EQ(p1.approx(2, 1, 0), 32);
    EXPECT_EQ(p1.approx(2, 1, 1), 32);
    EXPECT_EQ(p1.approx(2, 10, 1), 1400);
}