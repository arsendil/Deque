#include "gtest/gtest.h"
#include "headers/Deque.hpp"

TEST(DequeBasicTest, EmptyDeque)
{
    Deque<int> d;
    EXPECT_EQ(d.size(), 0u);
    EXPECT_TRUE(d.begin() == d.end());
}

TEST(DequeIteratorTest, CopyAndAssign)
{
    Deque<int> d;
    Deque<int>::const_iterator it1 = d.begin();
    Deque<int>::const_iterator it2(it1); 
    EXPECT_TRUE(it1 == it2);

    Deque<int>::const_iterator it3;
    it3 = it1; 
    EXPECT_TRUE(it3 == it1);
}

TEST(DequeIteratorTest, IncrementDecrementOnEmpty)
{
    Deque<int> d;
    Deque<int>::const_iterator it = d.begin();

    Deque<int>::const_iterator it2 = it++;
    EXPECT_TRUE(it2 == d.begin());

    Deque<int>::const_iterator it3 = it--;
    EXPECT_TRUE(it3 != it);  
}

TEST(DequeIteratorTest, ComparisonOperators)
{
    Deque<int> d;
    Deque<int>::const_iterator it1 = d.begin();
    Deque<int>::const_iterator it2 = d.end();

    EXPECT_TRUE(it1 == it2);  
    EXPECT_TRUE(it1 <= it2);
    EXPECT_TRUE(it2 >= it1);
}

TEST(DequeTest, PushBackAndSize)
{
    Deque<int> dq;
    EXPECT_TRUE(dq.empty());
    EXPECT_EQ(dq.size(), 0u);

    dq.push_back(10);
    dq.push_back(20);

    EXPECT_FALSE(dq.empty());
    EXPECT_EQ(dq.size(), 2u);

    EXPECT_EQ(*dq.begin(), 10);
    EXPECT_EQ(*(dq.begin() + 1), 20);
}

TEST(DequeTest, PushFrontAndOrder)
{
    Deque<int> dq;
    dq.push_front(5);
    dq.push_front(15);

    EXPECT_EQ(dq.size(), 2u);
    EXPECT_EQ(*dq.begin(), 15);
    EXPECT_EQ(*(dq.begin() + 1), 5);
}

TEST(DequeTest, PopBack)
{
    Deque<int> dq;
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);

    dq.pop_back();
    EXPECT_EQ(dq.size(), 2u);
    EXPECT_EQ(*(dq.end() - 1), 2);

    dq.pop_back();
    dq.pop_back();
    EXPECT_TRUE(dq.empty());
}

TEST(DequeTest, PopFront)
{
    Deque<int> dq;
    dq.push_back(100);
    dq.push_back(200);
    dq.push_back(300);

    dq.pop_front();
    EXPECT_EQ(dq.size(), 2u);
    EXPECT_EQ(*dq.begin(), 200);

    dq.pop_front();
    dq.pop_front();
    EXPECT_TRUE(dq.empty());
}

TEST(DequeTest, ResizeGrowWithInitialValue)
{
    Deque<int> d;

    EXPECT_EQ(d.size(), 0u);
    EXPECT_TRUE(d.empty());

    d.resize(5, 42);
    EXPECT_EQ(d.size(), 5u);

    for (Deque<int>::iterator it = d.begin(); it != d.end(); ++it) {
        EXPECT_EQ(*it, 42);
    }
}

TEST(DequeTest, ResizeShrink)
{
    Deque<int> d(5, 13);
    EXPECT_EQ(d.size(), 5u);

    d.resize(2, 99);
    EXPECT_EQ(d.size(), 2u);

    for (Deque<int>::iterator it = d.begin(); it != d.end(); ++it) {
        EXPECT_EQ(*it, 13);
    }
}

TEST(DequeTest, ResizeGrowAgain)
{
    Deque<int> d(2, 7); 
    EXPECT_EQ(d.size(), 2u);

    d.resize(4, 99);
    EXPECT_EQ(d.size(), 4u);

    EXPECT_EQ(d.begin()[0], 7);
    EXPECT_EQ(d.begin()[1], 7);
    EXPECT_EQ(d.begin()[2], 99);
    EXPECT_EQ(d.begin()[3], 99);
}

TEST(DequeTest, CopyConstructorBasic)
{
    Deque<int> d1;
    d1.push_back(1);
    d1.push_back(2);
    d1.push_back(3);

    Deque<int> d2(d1);

    EXPECT_EQ(d1.size(), d2.size());

    for (size_t i = 0; i < d1.size(); ++i) {
        EXPECT_EQ(d1.begin()[i], d2.begin()[i]);
    }
}

TEST(DequeTest, CopyConstructorIndependence)
{
    Deque<int> d1;
    d1.push_back(10);
    d1.push_back(20);

    Deque<int> d2(d1);

    d2.push_back(30);

    EXPECT_EQ(d1.size(), 2u);
    EXPECT_EQ(d2.size(), 3u);

    EXPECT_EQ(d1.begin()[0], 10);
    EXPECT_EQ(d1.begin()[1], 20);

    EXPECT_EQ(d2.begin()[0], 10);
    EXPECT_EQ(d2.begin()[1], 20);
    EXPECT_EQ(d2.begin()[2], 30);
}

TEST(DequeTest, RangeConstructorFromVector)
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    Deque<int> d(v.begin(), v.end());

    Deque<int>::iterator it = d.begin();
    for (size_t i = 0; i < v.size(); ++i, ++it) {
        EXPECT_EQ(*it, v[i]);
    }
}

TEST(DequeTest, RangeConstructorFromArray)
{
    int arr[] = {10, 20, 30};
    Deque<int> d(arr, arr + 3);

    Deque<int>::iterator it = d.begin();
    EXPECT_EQ(*it, 10); ++it;
    EXPECT_EQ(*it, 20); ++it;
    EXPECT_EQ(*it, 30);
}

TEST(DequeTest, RangeConstructorEmpty)
{
    std::vector<int> emptyVec;
    Deque<int> d(emptyVec.begin(), emptyVec.end());

    EXPECT_TRUE(d.empty());
}

TEST(DequeTest, FrontBackSinglePushFront)
{
    Deque<int> d;
    d.push_front(10);

    EXPECT_EQ(d.front(), 10);
    EXPECT_EQ(d.back(), 10);
}

TEST(DequeTest, FrontBackSinglePushBack)
{
    Deque<int> d;
    d.push_back(20);

    EXPECT_EQ(d.front(), 20);
    EXPECT_EQ(d.back(), 20);
}

TEST(DequeTest, FrontBackMultiplePush)
{
    Deque<int> d;
    d.push_front(1);
    d.push_front(2);
    d.push_back(3);
    d.push_back(4);

    EXPECT_EQ(d.front(), 2);
    EXPECT_EQ(d.back(), 4);
}

TEST(DequeTest, ConstFrontBack)
{
    Deque<int> d;
    d.push_back(5);
    d.push_back(6);

    const Deque<int>& cd = d;

    EXPECT_EQ(cd.front(), 5);
    EXPECT_EQ(cd.back(), 6);
}

TEST(DequeTest, AssignmentBasic)
{
    Deque<int> d1;
    d1.push_back(1);
    d1.push_back(2);
    d1.push_back(3);

    Deque<int> d2;
    d2 = d1;

    EXPECT_EQ(d1.size(), d2.size());
    EXPECT_EQ(d2.front(), 1);
    EXPECT_EQ(d2.back(), 3);

    while (!d1.empty() && !d2.empty()) {
        EXPECT_EQ(d1.front(), d2.front());
        d1.pop_front();
        d2.pop_front();
    }
}

TEST(DequeTest, AssignmentSelf)
{
    Deque<int> d;
    d.push_back(42);
    d.push_back(43);

    d = d;

    EXPECT_EQ(d.size(), 2);
    EXPECT_EQ(d.front(), 42);
    EXPECT_EQ(d.back(), 43);
}

TEST(DequeTest, AssignmentEmpty)
{
    Deque<int> d1;
    d1.push_back(10);
    d1.push_back(20);

    Deque<int> d2;
    d2 = d1;

    d1.clear();

    EXPECT_FALSE(d2.empty());
    EXPECT_EQ(d2.size(), 2);
    EXPECT_EQ(d2.front(), 10);
    EXPECT_EQ(d2.back(), 20);
}

TEST(DequeTest, EqualityOperator)
{
    Deque<int> d1;
    d1.push_back(1);
    d1.push_back(2);

    Deque<int> d2;
    d2.push_back(1);
    d2.push_back(2);

    EXPECT_TRUE(d1 == d2);

    d2.push_back(3);
    EXPECT_FALSE(d1 == d2);
}

TEST(DequeTest, LessThanOperator)
{
    Deque<int> d1;
    d1.push_back(1);
    d1.push_back(2);

    Deque<int> d2;
    d2.push_back(1);
    d2.push_back(3);

    EXPECT_TRUE(d1 < d2);
    EXPECT_FALSE(d2 < d1);
}

TEST(DequeTest, GreaterThanOperator)
{
    Deque<int> d1;
    d1.push_back(5);
    d1.push_back(6);

    Deque<int> d2;
    d2.push_back(5);
    d2.push_back(4);

    EXPECT_TRUE(d1 > d2);
    EXPECT_FALSE(d2 > d1);
}

TEST(DequeTest, LessThanOrEqualOperator)
{
    Deque<int> d1;
    d1.push_back(10);
    d1.push_back(20);

    Deque<int> d2;
    d2.push_back(10);
    d2.push_back(20);

    Deque<int> d3;
    d3.push_back(10);
    d3.push_back(30);

    EXPECT_TRUE(d1 <= d2);
    EXPECT_TRUE(d1 <= d3);
    EXPECT_FALSE(d3 <= d1);
}

TEST(DequeTest, GreaterThanOrEqualOperator)
{
    Deque<int> d1;
    d1.push_back(1);
    d1.push_back(2);

    Deque<int> d2;
    d2.push_back(1);
    d2.push_back(2);

    Deque<int> d3;
    d3.push_back(1);
    d3.push_back(1);

    EXPECT_TRUE(d1 >= d2);
    EXPECT_TRUE(d1 >= d3);
    EXPECT_FALSE(d3 >= d1);
}

TEST(DequeTest, SwapBasic)
{
    Deque<int> d1;
    d1.push_back(1);
    d1.push_back(2);

    Deque<int> d2;
    d2.push_back(10);
    d2.push_back(20);
    d2.push_back(30);

    d1.swap(d2);

    EXPECT_EQ(d1.size(), 3u);
    EXPECT_EQ(d2.size(), 2u);

    EXPECT_EQ(d1.front(), 10);
    EXPECT_EQ(d1.back(), 30);

    EXPECT_EQ(d2.front(), 1);
    EXPECT_EQ(d2.back(), 2);
}

TEST(DequeTest, SwapEmptyWithNonEmpty)
{
    Deque<int> d1;
    Deque<int> d2;
    d2.push_back(100);

    d1.swap(d2);

    EXPECT_TRUE(d2.empty());
    EXPECT_FALSE(d1.empty());
    EXPECT_EQ(d1.front(), 100);
}

TEST(DequeTest, SwapBothEmpty)
{
    Deque<int> d1;
    Deque<int> d2;

    d1.swap(d2);

    EXPECT_TRUE(d1.empty());
    EXPECT_TRUE(d2.empty());
}

TEST(DequeTest, SwapSelf)
{
    Deque<int> d1;
    d1.push_back(42);
    d1.push_back(84);

    d1.swap(d1);

    EXPECT_EQ(d1.size(), 2u);
    EXPECT_EQ(d1.front(), 42);
    EXPECT_EQ(d1.back(), 84);
}

TEST(DequeTest, InsertFront) {
    Deque<int> d;
    d.push_back(2);
    d.push_back(3);

    // insert at front
    Deque<int>::iterator it = d.insert(d.begin(), 1);

    EXPECT_EQ(*it, 1);
    EXPECT_EQ(d.size(), 3u);
    EXPECT_EQ(d.front(), 1);
    EXPECT_EQ(d.back(), 3);
}

TEST(DequeTest, InsertBack) {
    Deque<int> d;
    d.push_back(1);
    d.push_back(2);

    // insert at end
    Deque<int>::iterator it = d.insert(d.end(), 3);

    EXPECT_EQ(*it, 3);
    EXPECT_EQ(d.size(), 3u);
    EXPECT_EQ(d.back(), 3);
}

TEST(DequeTest, InsertMiddle) {
    Deque<int> d;
    d.push_back(1);
    d.push_back(3);

    // insert before "3"
    Deque<int>::iterator it = d.insert(d.begin() + 1, 2);

    EXPECT_EQ(*it, 2);
    EXPECT_EQ(d.size(), 3u);

    EXPECT_EQ(d.front(), 1);
    EXPECT_EQ(d.back(), 3);

    Deque<int>::iterator it_check = d.begin();
    EXPECT_EQ(*it_check, 1);
    ++it_check;
    EXPECT_EQ(*it_check, 2);
    ++it_check;
    EXPECT_EQ(*it_check, 3);
}

TEST(DequeTest, InsertIntoEmpty) {
    Deque<int> d;

    Deque<int>::iterator it = d.insert(d.begin(), 42);

    EXPECT_EQ(d.size(), 1u);
    EXPECT_EQ(*it, 42);
    EXPECT_EQ(d.front(), 42);
    EXPECT_EQ(d.back(), 42);
}

int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
