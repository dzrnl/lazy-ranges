#include "lib/notstd/ranges/ranges.h"

#include <gtest/gtest.h>

using namespace notstd::ranges::views;

template<typename Range, typename ValueType = typename Range::value_type>
std::vector<ValueType> RangeToVector(Range range) {
    std::vector<ValueType> result;
    for (ValueType i : range) {
        result.push_back(i);
    }

    return result;
}

TEST(NotStdSetTestSuite, TransformTest) {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    ASSERT_EQ(RangeToVector(vec | transform([](int i) { return i * i; })),
              std::vector<int>({1, 4, 9, 16, 25}));

    ASSERT_EQ(RangeToVector(vec | transform([](int i) { return -3 * i; })),
              std::vector<int>({-3, -6, -9, -12, -15}));

    ASSERT_EQ(RangeToVector(vec | transform([](int i) { return i % 4; })),
              std::vector<int>({1, 2, 3, 0, 1}));

    ASSERT_EQ(RangeToVector(vec | transform([](int i) { return i + 5; })),
              std::vector<int>({6, 7, 8, 9, 10}));
}

TEST(NotStdSetTestSuite, MultiTransformTest) {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    ASSERT_EQ(RangeToVector(vec | transform([](int i) { return i * i; })
                            | transform([](int i) { return -3 * i; })),
              std::vector<int>({-3, -12, -27, -48, -75}));

    ASSERT_EQ(RangeToVector(vec | transform([](int i) { return -3 * i; })
                            | transform([](int i) { return i * i; })),
              std::vector<int>({9, 36, 81, 144, 225}));

    ASSERT_EQ(RangeToVector(vec | transform([](int i) { return i % 4; })
                            | transform([](int i) { return i + 5; })),
              std::vector<int>({6, 7, 8, 5, 6}));

    ASSERT_EQ(RangeToVector(vec | transform([](int i) { return i + 5; })
                            | transform([](int i) { return i + 4; })
                            | transform([](int i) { return i % 2; })),
              std::vector<int>({0, 1, 0, 1, 0}));
}

TEST(NotStdSetTestSuite, FilterTest) {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    ASSERT_EQ(RangeToVector(vec | filter([](int i) { return i % 2 == 0; })),
              std::vector<int>({2, 4}));

    ASSERT_EQ(RangeToVector(vec | filter([](int i) { return i >= 3; })),
              std::vector<int>({3, 4, 5}));

    ASSERT_EQ(RangeToVector(vec | filter([](int i) { return i == 2; })),
              std::vector<int>({2}));

    ASSERT_EQ(RangeToVector(vec | filter([](int i) { return i != 4; })),
              std::vector<int>({1, 2, 3, 5}));
}

TEST(NotStdSetTestSuite, MultiFilterTest) {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    ASSERT_EQ(RangeToVector(vec | filter([](int i) { return i % 2 == 0; })
                            | filter([](int i) { return i < 3; })),
              std::vector<int>({2}));

    ASSERT_EQ(RangeToVector(vec | filter([](int i) { return i >= 2; })
                            | filter([](int i) { return i < 5; })),
              std::vector<int>({2, 3, 4}));

    ASSERT_EQ(RangeToVector(vec | filter([](int i) { return i != 3; })
                            | filter([](int i) { return i == 3; })),
              std::vector<int>({}));

    ASSERT_EQ(RangeToVector(vec | filter([](int i) { return i != 4; })
                            | filter([](int i) { return i % 2 != 0; })),
              std::vector<int>({1, 3, 5}));
}

TEST(NotStdSetTestSuite, TakeTest) {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    ASSERT_EQ(RangeToVector(vec | take(3)),
              std::vector<int>({1, 2, 3}));

    ASSERT_EQ(RangeToVector(vec | take(100)),
              std::vector<int>({1, 2, 3, 4, 5}));

    ASSERT_EQ(RangeToVector(vec | take(0)),
              std::vector<int>({}));

    ASSERT_EQ(RangeToVector(vec | take(1)),
              std::vector<int>({1}));
}

TEST(NotStdSetTestSuite, MultiTakeTest) {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    ASSERT_EQ(RangeToVector(vec | take(3)
                            | take(2)),
              std::vector<int>({1, 2}));

    ASSERT_EQ(RangeToVector(vec | take(100)
                            | take(0)),
              std::vector<int>({}));

    ASSERT_EQ(RangeToVector(vec | take(0)
                            | take(2)),
              std::vector<int>({}));

    ASSERT_EQ(RangeToVector(vec | take(3)
                            | take(4)),
              std::vector<int>({1, 2, 3}));
}

TEST(NotStdSetTestSuite, DropTest) {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    ASSERT_EQ(RangeToVector(vec | drop(3)),
              std::vector<int>({4, 5}));

    ASSERT_EQ(RangeToVector(vec | drop(100)),
              std::vector<int>({}));

    ASSERT_EQ(RangeToVector(vec | drop(0)),
              std::vector<int>({1, 2, 3, 4, 5}));

    ASSERT_EQ(RangeToVector(vec | drop(1)),
              std::vector<int>({2, 3, 4, 5}));
}

TEST(NotStdSetTestSuite, MultiDropTest) {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    ASSERT_EQ(RangeToVector(vec | drop(3)
                            | drop(2)),
              std::vector<int>({}));

    ASSERT_EQ(RangeToVector(vec | drop(100)
                            | drop(0)),
              std::vector<int>({}));

    ASSERT_EQ(RangeToVector(vec | drop(0)
                            | drop(2)),
              std::vector<int>({3, 4, 5}));

    ASSERT_EQ(RangeToVector(vec | drop(3)
                            | drop(1)),
              std::vector<int>({5}));
}

TEST(NotStdSetTestSuite, ReverseTest) {
    std::vector<int> vec1 = {1, 2, 3, 4, 5};

    ASSERT_EQ(RangeToVector(vec1 | reverse()),
              std::vector<int>({5, 4, 3, 2, 1}));

    std::vector<int> vec2 = {};

    ASSERT_EQ(RangeToVector(vec2 | reverse()),
              std::vector<int>({}));

    std::vector<int> vec3 = {1};

    ASSERT_EQ(RangeToVector(vec3 | reverse()),
              std::vector<int>({1}));
}

TEST(NotStdSetTestSuite, MultiReverseTest) {
    std::vector<int> vec1 = {1, 2, 3, 4, 5};

    ASSERT_EQ(RangeToVector(vec1 | reverse()
                            | reverse()),
              std::vector<int>({1, 2, 3, 4, 5}));

    ASSERT_EQ(RangeToVector(vec1 | reverse()
                            | reverse()
                            | reverse()),
              std::vector<int>({5, 4, 3, 2, 1}));

    std::vector<int> vec2 = {};

    ASSERT_EQ(RangeToVector(vec2 | reverse()
                            | reverse()),
              std::vector<int>({}));

    std::vector<int> vec3 = {1};

    ASSERT_EQ(RangeToVector(vec3 | reverse()
                            | reverse()),
              std::vector<int>({1}));
}

TEST(NotStdSetTestSuite, KeysTest) {
    std::map<int, std::string> map1 = {{1, "one"},
                                       {2, "two"},
                                       {3, "three"},
                                       {4, "four"},
                                       {5, "five"}};

    ASSERT_EQ(RangeToVector(map1 | keys()),
              std::vector<int>({1, 2, 3, 4, 5}));

    std::map<int, std::string> map2 = {};

    ASSERT_EQ(RangeToVector(map2 | keys()),
              std::vector<int>({}));

    std::map<int, std::string> map3 = {{1, "one"}};

    ASSERT_EQ(RangeToVector(map3 | keys()),
              std::vector<int>({1}));
}

TEST(NotStdSetTestSuite, ValuesTest) {
    std::map<int, std::string> map1 = {{1, "one"},
                                       {2, "two"},
                                       {3, "three"},
                                       {4, "four"},
                                       {5, "five"}};

    ASSERT_EQ(RangeToVector(map1 | values()),
              std::vector<std::string>({"one", "two", "three", "four", "five"}));

    std::map<int, std::string> map2 = {};

    ASSERT_EQ(RangeToVector(map2 | values()),
              std::vector<std::string>({}));

    std::map<int, std::string> map3 = {{1, "one"}};

    ASSERT_EQ(RangeToVector(map3 | values()),
              std::vector<std::string>({"one"}));
}

TEST(NotStdSetTestSuite, ReadmeTest) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};

    ASSERT_EQ(RangeToVector(vec | filter([](int i) { return i % 2 != 0; })
                            | transform([](int i) { return i * i; })),
              std::vector<int>({1, 9, 25}));
}

TEST(NotStdSetTestSuite, AllTest) {
    std::vector<int> vec = {2, 5, 1, 4, 2};

    ASSERT_EQ(RangeToVector(vec | take(3)
                            | filter([](int i) { return i % 2 != 0; })),
              std::vector<int>({5, 1}));

    ASSERT_EQ(RangeToVector(vec | drop(2)
                            | take(2)),
              std::vector<int>({1, 4}));

    ASSERT_EQ(RangeToVector(vec | take(3)
                            | reverse()),
              std::vector<int>({1, 5, 2}));

    ASSERT_EQ(RangeToVector(vec | drop(2)
                            | reverse()),
              std::vector<int>({2, 4, 1}));

    ASSERT_EQ(RangeToVector(vec | reverse()
                            | transform([](int i) { return 3 * i; })
                            | filter([](int i) { return i % 2 == 0; })),
              std::vector<int>({6, 12, 6}));

    std::map<int, std::string> map = {{1, "one"},
                                      {2, "two"},
                                      {4, "four"}};

    ASSERT_EQ(RangeToVector(map | filter([](std::pair<const int, std::string> pair) { return pair.first % 2 == 0; })
                            | keys()),
              std::vector<int>({2, 4}));

    ASSERT_EQ(RangeToVector(map | filter([](std::pair<const int, std::string> pair) { return pair.first % 2 == 0; })
                            | values()),
              std::vector<std::string>({"two", "four"}));
}
