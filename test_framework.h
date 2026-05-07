#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace mini_test {

struct TestCase {
    std::string name;
    std::function<void()> run;
};

inline std::vector<TestCase>& tests() {
    static std::vector<TestCase> all_tests;
    return all_tests;
}

struct RegisterTest {
    RegisterTest(const std::string& name, std::function<void()> run) {
        tests().push_back({name, run});
    }
};

inline void check(bool condition, const char* expression, const char* file, int line) {
    if (!condition) {
        throw std::runtime_error(std::string(file) + ":" + std::to_string(line)
                                 + " nepavyko: " + expression);
    }
}

inline int run_all() {
    int failed = 0;

    for (const auto& test : tests()) {
        try {
            test.run();
            std::cout << "[OK] " << test.name << std::endl;
        } catch (const std::exception& e) {
            ++failed;
            std::cout << "[FAIL] " << test.name << " - " << e.what() << std::endl;
        }
    }

    std::cout << "Praejo: " << tests().size() - failed
              << ", nepraejo: " << failed << std::endl;
    return failed == 0 ? 0 : 1;
}

} // namespace mini_test

#define JOIN_IMPL(a, b) a##b
#define JOIN(a, b) JOIN_IMPL(a, b)

#define TEST_CASE(name)                                                    \
    static void JOIN(test_, __LINE__)();                                    \
    static mini_test::RegisterTest JOIN(register_, __LINE__)(name, JOIN(test_, __LINE__)); \
    static void JOIN(test_, __LINE__)()

#define CHECK(expression) mini_test::check((expression), #expression, __FILE__, __LINE__)

#endif
