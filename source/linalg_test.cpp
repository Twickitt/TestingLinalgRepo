#include <linalg_realization.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <vector>


using linalg::Matrix;

constexpr double DOUBLE_EPSILON = 1e-8;
TEST(CONSTRUCTOR, default_constructor) 
{
    linalg::Matrix m;
    EXPECT_EQ(0, m.size());
    EXPECT_EQ(0, m.rows());
    EXPECT_EQ(0, m.columns());
    EXPECT_TRUE(m.empty());
}

TEST(CONSTRUCTOR, two_parameter_constructor_value)
{
    linalg::Matrix m(4, 4, 2.5);
    EXPECT_EQ(4, m.rows());
    EXPECT_EQ(4, m.columns());
    EXPECT_EQ(16, m.size());
    EXPECT_EQ(16, m.capacity());
    EXPECT_DOUBLE_EQ(2.5, m(0, 0));
    EXPECT_DOUBLE_EQ(2.5, m(0, 1));
    EXPECT_DOUBLE_EQ(2.5, m(0, 2));
    EXPECT_DOUBLE_EQ(2.5, m(0, 3));
    EXPECT_DOUBLE_EQ(2.5, m(1, 0));
    EXPECT_DOUBLE_EQ(2.5, m(1, 1));
    EXPECT_DOUBLE_EQ(2.5, m(1, 2));
    EXPECT_DOUBLE_EQ(2.5, m(1, 3));
    EXPECT_DOUBLE_EQ(2.5, m(2, 0));
    EXPECT_DOUBLE_EQ(2.5, m(2, 1));
    EXPECT_DOUBLE_EQ(2.5, m(2, 2));
    EXPECT_DOUBLE_EQ(2.5, m(2, 3));
    EXPECT_DOUBLE_EQ(2.5, m(3, 0));
    EXPECT_DOUBLE_EQ(2.5, m(3, 1));
    EXPECT_DOUBLE_EQ(2.5, m(3, 2));
    EXPECT_DOUBLE_EQ(2.5, m(3, 3));
}

TEST(CONSTRUCTOR, single_parameter_constructor) 
{
    linalg::Matrix m(4);
    EXPECT_EQ(4, m.rows());
    EXPECT_EQ(1, m.columns());
    EXPECT_EQ(4, m.size());
    EXPECT_FALSE(m.empty());
}

TEST(CONSTRUCTOR, two_parameter_constructor) 
{
    linalg::Matrix m(4, 6);
    EXPECT_EQ(4, m.rows());
    EXPECT_EQ(6, m.columns());
    EXPECT_EQ(24, m.size());
    EXPECT_FALSE(m.empty());
}

TEST(CONSTRUCTOR, copy_constructor) 
{
    linalg::Matrix m1(4);
    linalg::Matrix m2(m1);
    EXPECT_EQ(m1.rows(), m2.rows());
    EXPECT_EQ(m1.columns(), m2.columns());
    EXPECT_EQ(m1.size(), m2.size());
}

TEST(CONSTRUCTOR, move_constructor) 
{
    linalg::Matrix m1(4, 6);
    linalg::Matrix m2(std::move(m1));
    EXPECT_EQ(4, m2.rows());
    EXPECT_EQ(6, m2.columns());
    EXPECT_EQ(0, m1.rows());
    EXPECT_EQ(0, m1.columns());
}

TEST(CONSTRUCTOR, initializer_list)
{   
    linalg::Matrix m1; 
    linalg::Matrix m2 = { {1, 2, 3}, {4, 5, 6} }; 
    linalg::Matrix m3 = { {1, 2, 3, 4, 5, 6} };
    linalg::Matrix m4 = { 1, 2, 3, 4, 5, 6 }; 
    m1 = linalg::Matrix{ 1, 2, 3, 4, 5, 6 }; 
    EXPECT_DOUBLE_EQ(1.0, m1(0, 0));
    EXPECT_DOUBLE_EQ(2.0, m1(1, 0));
    EXPECT_DOUBLE_EQ(3.0, m1(2, 0));
    EXPECT_DOUBLE_EQ(4.0, m1(3, 0));
    EXPECT_DOUBLE_EQ(5.0, m1(4, 0));
    EXPECT_DOUBLE_EQ(6.0, m1(5, 0));

    EXPECT_DOUBLE_EQ(1.0, m2(0, 0));
    EXPECT_DOUBLE_EQ(2.0, m2(0, 1));
    EXPECT_DOUBLE_EQ(3.0, m2(0, 2));
    EXPECT_DOUBLE_EQ(4.0, m2(1, 0));
    EXPECT_DOUBLE_EQ(5.0, m2(1, 1));
    EXPECT_DOUBLE_EQ(6.0, m2(1, 2));

    EXPECT_DOUBLE_EQ(1.0, m3(0, 0));
    EXPECT_DOUBLE_EQ(2.0, m3(0, 1));
    EXPECT_DOUBLE_EQ(3.0, m3(0, 2));
    EXPECT_DOUBLE_EQ(4.0, m3(0, 3));
    EXPECT_DOUBLE_EQ(5.0, m3(0, 4));
    EXPECT_DOUBLE_EQ(6.0, m3(0, 5));

    EXPECT_DOUBLE_EQ(1.0, m4(0, 0));
    EXPECT_DOUBLE_EQ(2.0, m4(1, 0));
    EXPECT_DOUBLE_EQ(3.0, m4(2, 0));
    EXPECT_DOUBLE_EQ(4.0, m4(3, 0));
    EXPECT_DOUBLE_EQ(5.0, m4(4, 0));
    EXPECT_DOUBLE_EQ(6.0, m4(5, 0));
}

TEST(ASSIGNMENT, copy_assignment) 
{
    linalg::Matrix m1(3, 3);
    linalg::Matrix m2 = m1;
    EXPECT_EQ(m1.rows(), m2.rows());
    EXPECT_EQ(m1.columns(), m2.columns());
    EXPECT_EQ(m1.size(), m2.size());
}

TEST(ASSIGNMENT, move_assignment) 
{
    linalg::Matrix m1(3, 3);
    linalg::Matrix m2 = std::move(m1);
    EXPECT_EQ(3, m2.rows());
    EXPECT_EQ(3, m2.columns());
    EXPECT_EQ(0, m1.rows());
    EXPECT_EQ(0, m1.columns());
}

TEST(ACCESS, non_const_operator) 
{
    linalg::Matrix m(2, 3);
    m(1, 2) = 3.0;
    EXPECT_DOUBLE_EQ(3.0, m(1, 2));
}

TEST(ACCESS, const_operator) 
{
    const linalg::Matrix m(2, 3, 0.0);
    EXPECT_DOUBLE_EQ(0.0, m(1, 2));
}

TEST(CAPACITY, resize) 
{
    linalg::Matrix m(4);
    EXPECT_EQ(4, m.rows());
    EXPECT_EQ(1, m.columns());
    
    m.reshape(3, 5);
    EXPECT_EQ(3, m.rows());
    EXPECT_EQ(5, m.columns());
    EXPECT_EQ(15, m.size());
}

TEST(CAPACITY, reserve_and_shrink) 
{
    linalg::Matrix m;
    m.reserve(10);
    EXPECT_GE(m.capacity(), 10);
    
    m.shrink_to_fit();
    EXPECT_EQ(m.size(), m.capacity());
}

TEST(CAPACITY, clear) 
{
    linalg::Matrix m(3, 4);
    EXPECT_FALSE(m.empty());
    
    m.clear();
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(0, m.size());
}

TEST(ITERATORS, non_const_iterators) 
{
    linalg::Matrix m(2, 2);
    double value = 1.0;
    for (double* i = m.begin(); i != m.end(); ++i)
        *i = value++;
    
    EXPECT_DOUBLE_EQ(1.0, m(0, 0));
    EXPECT_DOUBLE_EQ(2.0, m(0, 1));
    EXPECT_DOUBLE_EQ(3.0, m(1, 0));
    EXPECT_DOUBLE_EQ(4.0, m(1, 1));
}

TEST(ITERATORS, const_iterators) 
{
    const linalg::Matrix m(2, 2, 0.0);
    size_t count = 0;
    for (double c : m) 
    {
        EXPECT_DOUBLE_EQ(0.0, c);
        count++;
    }
    EXPECT_EQ(4, count);
}

TEST(ARITHMETIC, scalar_multiplication) 
{
    linalg::Matrix m(2, 2);
    m(0, 0) = 1.0; m(0, 1) = 2.0;
    m(1, 0) = 3.0; m(1, 1) = 4.0;
    
    m *= 2;
    EXPECT_DOUBLE_EQ(2.0, m(0, 0));
    EXPECT_DOUBLE_EQ(4.0, m(0, 1));
    EXPECT_DOUBLE_EQ(6.0, m(1, 0));
    EXPECT_DOUBLE_EQ(8.0, m(1, 1));
}

TEST(ARITHMETIC, equality_operators) 
{
    linalg::Matrix m1(2, 2, 2.5);
    linalg::Matrix m2 = m1;
    
    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 != m2);
    
    ++m2(0, 0);
    EXPECT_FALSE(m1 == m2);
    EXPECT_TRUE(m1 != m2);
}

TEST(ARITHMETIC, matrix_multiplication) 
{
    linalg::Matrix m1(2, 1);
    linalg::Matrix m2(1, 2);
    
    m1(0, 0) = 2.0; m1(1, 0) = 3.0;
    m2(0, 0) = 4.0; m2(0, 1) = 5.0;
    
    m1 *= m2;
    EXPECT_EQ(2, m1.rows());
    EXPECT_EQ(2, m1.columns());
    EXPECT_DOUBLE_EQ(8.0, m1(0, 0));
    EXPECT_DOUBLE_EQ(10.0, m1(0, 1));
    EXPECT_DOUBLE_EQ(12.0, m1(1, 0));
    EXPECT_DOUBLE_EQ(15.0, m1(1, 1));
}

TEST(ARITHMETIC, addition_and_subtraction) 
{
    linalg::Matrix m1(1, 2);
    linalg::Matrix m2(1, 2);
    
    m1(0, 0) = 1.0; m1(0, 1) = 2.0;
    m2(0, 0) = 3.0; m2(0, 1) = 4.0;
    
    m1 += m2;
    EXPECT_DOUBLE_EQ(4.0, m1(0, 0));
    EXPECT_DOUBLE_EQ(6.0, m1(0, 1));
    
    m1 -= m2;
    EXPECT_DOUBLE_EQ(1.0, m1(0, 0));
    EXPECT_DOUBLE_EQ(2.0, m1(0, 1));
}

TEST(ARITHMETIC, unary_operators) 
{
    linalg::Matrix m(2, 2);
    m(0, 0) = 1.0; m(0, 1) = 2.0;
    
    linalg::Matrix neg = -m;
    EXPECT_DOUBLE_EQ(-1.0, neg(0, 0));
    EXPECT_DOUBLE_EQ(-2.0, neg(0, 1));
    
    linalg::Matrix pos = +m;
    EXPECT_DOUBLE_EQ(1.0, pos(0, 0));
    EXPECT_DOUBLE_EQ(2.0, pos(0, 1));
}

TEST(ARITHMETIC, binary_operators)
{
    linalg::Matrix m1(2, 2, 3.0);
    linalg::Matrix m2(2, 2, 2.0);
    linalg::Matrix m3 = m1 + m2;
    linalg::Matrix m4 = m2 + m1;
    EXPECT_DOUBLE_EQ(5.0, m3(0, 0));
    EXPECT_DOUBLE_EQ(5.0, m3(0, 1));
    EXPECT_DOUBLE_EQ(5.0, m3(1, 0));
    EXPECT_DOUBLE_EQ(5.0, m3(1, 1));
    EXPECT_TRUE(m3 == m4);
    m3 = m1 - m2;
    EXPECT_DOUBLE_EQ(1.0, m3(0, 0));
    EXPECT_DOUBLE_EQ(1.0, m3(0, 1));
    EXPECT_DOUBLE_EQ(1.0, m3(1, 0));
    EXPECT_DOUBLE_EQ(1.0, m3(1, 1));
}

TEST(ARITHMETIC, scalar_operations) 
{
    linalg::Matrix m(2, 2);
    m(0, 0) = 1.0; m(0, 1) = 2.0;
    
    linalg::Matrix result1 = m * 3;
    EXPECT_DOUBLE_EQ(3.0, result1(0, 0));
    EXPECT_DOUBLE_EQ(6.0, result1(0, 1));
    
    linalg::Matrix result2 = 0.5 * m;
    EXPECT_DOUBLE_EQ(0.5, result2(0, 0));
    EXPECT_DOUBLE_EQ(1.0, result2(0, 1));
}

TEST(PROPERTIES, trace_and_norm) 
{
    linalg::Matrix m(3, 3);
    for (size_t i = 0; i != m.rows(); ++i)
        for (size_t j = 0; j != m.columns(); ++j)
            m(i, j) = i * m.rows() + j + 1;
    EXPECT_DOUBLE_EQ(15.0, m.trace());  
    EXPECT_GT(m.norm(), 0.0);
}

TEST(OPERATIONS, transpose) 
{
    linalg::Matrix m(2, 2);
    m(0, 0) = 1.0; m(0, 1) = 2.0;
    m(1, 0) = 3.0; m(1, 1) = 4.0;

    linalg::Matrix transposed = linalg::transpose(m);
    EXPECT_DOUBLE_EQ(1.0, transposed(0, 0));
    EXPECT_DOUBLE_EQ(3.0, transposed(0, 1));
    EXPECT_DOUBLE_EQ(2.0, transposed(1, 0));
    EXPECT_DOUBLE_EQ(4.0, transposed(1, 1));
}

TEST(OPERATIONS, concatenate) 
{
    linalg::Matrix m1(2, 2);
    linalg::Matrix m2(2, 2);
    
    linalg::Matrix result = linalg::concatenate(m1, m2);
    EXPECT_EQ(2, result.rows());
    EXPECT_EQ(4, result.columns());
}

TEST(OPERATIONS, gauss_forward)
{
    linalg::Matrix m(3,4);

    int k = 1;
    for (double * it = m.begin(); it != m.end(); ++it)
        *it = ++k;

    m.gauss_forward();
    EXPECT_DOUBLE_EQ(2.0, m(0, 0));
    EXPECT_DOUBLE_EQ(3.0, m(0, 1));
    EXPECT_DOUBLE_EQ(4.0, m(0, 2));
    EXPECT_DOUBLE_EQ(5.0, m(0, 3));
    EXPECT_DOUBLE_EQ(0.0, m(1, 0));
    EXPECT_DOUBLE_EQ(-2.0, m(1, 1));
    EXPECT_DOUBLE_EQ(-4.0, m(1, 2));
    EXPECT_DOUBLE_EQ(-6.0, m(1, 3));
    EXPECT_DOUBLE_EQ(0.0, m(2, 0));
    EXPECT_DOUBLE_EQ(0.0, m(2, 1));
    EXPECT_DOUBLE_EQ(0.0, m(2, 2));
    EXPECT_DOUBLE_EQ(0.0, m(2, 3));
}

TEST(OPERATIONS, gauss_backward)
{
    linalg::Matrix m1(3,4);
    linalg::Matrix m2(3,3);
    int k = 1;
    for (double * it = m1.begin(); it != m1.end(); ++it)
        *it = ++k;
    k = 1;
    for (double * it = m2.begin(); it != m2.end() - 1; ++it)
    {   
        (k *= 2) += 1;
        *it = k;
    }
    m2(2, 2) = 1021.0;

    m1.gauss_backward();
    m2.gauss_backward();
    EXPECT_DOUBLE_EQ(1.0, m1(0, 0));
    EXPECT_DOUBLE_EQ(0.0, m1(0, 1));
    EXPECT_DOUBLE_EQ(-1.0, m1(0, 2));
    EXPECT_DOUBLE_EQ(-2.0, m1(0, 3));
    EXPECT_DOUBLE_EQ(0.0, m1(1, 0));
    EXPECT_DOUBLE_EQ(1.0, m1(1, 1));
    EXPECT_DOUBLE_EQ(2.0, m1(1, 2));
    EXPECT_DOUBLE_EQ(3.0, m1(1, 3));
    EXPECT_DOUBLE_EQ(0.0, m1(2, 0));
    EXPECT_DOUBLE_EQ(0.0, m1(2, 1));
    EXPECT_DOUBLE_EQ(0.0, m1(2, 2));
    EXPECT_DOUBLE_EQ(0.0, m1(2, 3));

    EXPECT_DOUBLE_EQ(1.0, m2(0, 0));
    EXPECT_DOUBLE_EQ(0.0, m2(0, 1));
    EXPECT_DOUBLE_EQ(0.0, m2(0, 2));
    EXPECT_DOUBLE_EQ(0.0, m2(1, 0));
    EXPECT_DOUBLE_EQ(1.0, m2(1, 1));
    EXPECT_DOUBLE_EQ(0.0, m2(1, 2));
    EXPECT_DOUBLE_EQ(0.0, m2(2, 0));
    EXPECT_DOUBLE_EQ(0.0, m2(2, 1));
    EXPECT_DOUBLE_EQ(1.0, m2(2, 2));
}

TEST(OPERATIONS, det)
{
    linalg::Matrix m(3,3);
    int k = 1;
    for (double * it = m.begin(); it != m.end(); ++it)
        *it = ++k;
    EXPECT_DOUBLE_EQ(0.0, m.det());
    EXPECT_EQ(3, m.rows());
    EXPECT_EQ(3, m.columns());
    EXPECT_EQ(9, m.size());
    EXPECT_EQ(9, m.capacity());
}

TEST(OPERATIONS, det2)
{
    linalg::Matrix m(3,3);    

    m(0, 0) = 3; m(0, 1) = 1; m(0, 2) = 1; 
    m(1, 0) = 2; m(1, 1) = 3; m(1, 2) = 5;
    m(2, 0) = 8; m(2, 1) = 9; m(2, 2) = 7;

    EXPECT_DOUBLE_EQ(-52.0, m.det());
    EXPECT_EQ(3, m.rows());
    EXPECT_EQ(3, m.columns());
    EXPECT_EQ(9, m.size());
    EXPECT_EQ(9, m.capacity());
}

TEST(OPERATIONS, det3)
{
    linalg::Matrix m(2,2);    

    m(0, 0) = 3.5; m(0, 1) = 1.982;
    m(1, 0) = -2.102; m(1, 1) = 3.83; 
    EXPECT_DOUBLE_EQ(17.571164, m.det());
    EXPECT_EQ(2, m.rows());
    EXPECT_EQ(2, m.columns());
    EXPECT_EQ(4, m.size());
    EXPECT_EQ(4, m.capacity());
}


TEST(OPERATIONS, inverse)
{
    linalg::Matrix m1(2, 2, 1.0);
    linalg::Matrix m2(3, 3, 1.0);
    m1(0,0) = 3.0;
    m2(0, 0) = 3.0;
    m2(1, 2) = 3.0;
    m2(2, 1) = 3.0;
    
    linalg::Matrix result1 = linalg::invert(m1);
    linalg::Matrix result2 = linalg::invert(m2);
    EXPECT_DOUBLE_EQ(0.5, result1(0, 0));
    EXPECT_DOUBLE_EQ(-0.5, result1(0, 1));
    EXPECT_DOUBLE_EQ(-0.5, result1(1, 0));
    EXPECT_DOUBLE_EQ(1.5, result1(1, 1));

    EXPECT_DOUBLE_EQ(0.4, result2(0, 0));
    EXPECT_DOUBLE_EQ(-0.1, result2(0, 1));
    EXPECT_DOUBLE_EQ(-0.1, result2(0, 2));
    EXPECT_DOUBLE_EQ(-0.1, result2(1, 0));
    EXPECT_DOUBLE_EQ(-0.1, result2(1, 1));
    EXPECT_DOUBLE_EQ(0.4, result2(1, 2));
    EXPECT_DOUBLE_EQ(-0.1, result2(2, 0));
    EXPECT_DOUBLE_EQ(0.4, result2(2, 1));
    EXPECT_DOUBLE_EQ(-0.1, result2(2, 2));
}

TEST(OPERATIONS, power)
{
    linalg::Matrix m(3, 3, 1.0);
    m(0, 0) = 3.0;
    m(1, 2) = 3.0;
    m(2, 1) = 3.0;

    linalg::Matrix result1 = linalg::power(m, 3);
    EXPECT_DOUBLE_EQ(47, result1(0, 0));
    EXPECT_DOUBLE_EQ(39, result1(0, 1));
    EXPECT_DOUBLE_EQ(39, result1(0, 2));
    EXPECT_DOUBLE_EQ(39, result1(1, 0));
    EXPECT_DOUBLE_EQ(39, result1(1, 1));
    EXPECT_DOUBLE_EQ(47, result1(1, 2));
    EXPECT_DOUBLE_EQ(39, result1(2, 0));
    EXPECT_DOUBLE_EQ(47, result1(2, 1));
    EXPECT_DOUBLE_EQ(39, result1(2, 2));
}

TEST(DOCUMENT, operations)
{
    linalg::Matrix A(4, 4, 7.0);
    linalg::Matrix B = linalg::power(A, 0);
    linalg::Matrix m = {
        { 2.543534, -1.3,  4.7, -0.834634,  3.243634,  1.1},
        {-2.1,  1243.634534, -1.4,  2.9, -123120.5,  4.3},
        { 12341.7643643, -2.8,  5.1345345, -3.3346346,  2.4, -1.934433},
        {-3.5364436,  4.2, -2.6,  1.8, -4.1,  3.7},
        { 2.3346346, -1454.9,  3.8634346, -2.7,  5.2, -0.6},
        {-4.434636,  3.1, -2.26346,  4.6346346, -1.745454,  31242.8343534534}
    };
    linalg::Matrix C = {{1, 2, 3, 4}, {2, 1, 7, 4}, {1, 2, 4, 3}, {1, 3, 4, 2}};
    EXPECT_TRUE(linalg::invert(linalg::transpose(C)) == linalg::transpose(linalg::invert(C)));
    C += B;
    EXPECT_TRUE(linalg::invert(m * m) == linalg::invert(m) * linalg::invert(m));
    EXPECT_TRUE(linalg::invert(C * C) == linalg::invert(C) * linalg::invert(C));
    EXPECT_TRUE(linalg::power(linalg::power(C, -1), 6) == linalg::power(linalg::power(C, -2), 3));
    EXPECT_TRUE(linalg::power(linalg::invert(C), 6) == linalg::power(linalg::power(C, -2), 3));
}

TEST(OPERATIONS, solve)
{
    linalg::Matrix C {{1, 2, 3, 4}, {2, 1, 7, 4}, {1, 2, 4, 3}, {1, 3, 4, 2}};
    linalg::Matrix D = {1, 2, 3, 4};
    linalg::Matrix answer = {-11 / 2.0 , 5 /6.0, 11 /6.0, -1 / 6.0}; 
    EXPECT_TRUE(solve(C, D) == answer);
}

TEST(OUT, cout) 
{
    std::stringstream sout;
    linalg::Matrix m = {{1, 20, 300, 29}, {4000, 5, 60, 18}, {7, 40, 9, 11}, {12, 1200, 81, 1}};
    sout << m;
    EXPECT_EQ(sout.str(), "|   1    20   300    29|\n|4000     5    60    18|\n|   7    40     9    11|\n|  12  1200    81     1|\n");
}

/*int main()
{
    linalg::Matrix A = {{1, 2, 0, 4, 0}, {1, 4, 0, 7, 0}};
    linalg::Matrix B = {1, 2};
    solve_system(A, B);
    linalg::Matrix C = {{1, 2, 3}, {4, 1, 3}, {1, 9, 3}}; 
    linalg::LUDecomposition result = linalg::LUDecompose(C);
}*/
