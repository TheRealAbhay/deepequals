#include <iostream>
#include <vector>
#include <unordered_map>
#include <typeindex>

bool deepEquals(const std::any& a, const std::any& b);

template <typename T>
bool deepEqualsPrimitives(const T& a, const T& b) {
    return a == b;
}

template <typename T>
bool deepEqualsObjects(const T& a, const T& b) {
    const auto& type = typeid(T);
    if (type == typeid(std::vector<typename T::value_type>)) {
        const auto& vecA = std::any_cast<const std::vector<typename T::value_type>&>(a);
        const auto& vecB = std::any_cast<const std::vector<typename T::value_type>&>(b);
        if (vecA.size() != vecB.size()) {
            return false;
        }
        for (size_t i = 0; i < vecA.size(); ++i) {
            if (!deepEquals(vecA[i], vecB[i])) {
                return false;
            }
        }
        return true;
    } else if (type == typeid(std::unordered_map<typename T::key_type, typename T::mapped_type>)) {
        const auto& mapA = std::any_cast<const std::unordered_map<typename T::key_type, typename T::mapped_type>&>(a);
        const auto& mapB = std::any_cast<const std::unordered_map<typename T::key_type, typename T::mapped_type>&>(b);
        if (mapA.size() != mapB.size()) {
            return false;
        }
        for (const auto& [key, value] : mapA) {
            if (!mapB.count(key) || !deepEquals(value, mapB.at(key))) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool deepEquals(const std::any& a, const std::any& b) {
    if (a.type() != b.type()) {
        return false;
    }
    if (a.type() == typeid(std::nullptr_t)) {
        return true;
    } else if (a.type() == typeid(bool)) {
        return deepEqualsPrimitives(std::any_cast<const bool&>(a), std::any_cast<const bool&>(b));
    } else if (a.type() == typeid(int)) {
        return deepEqualsPrimitives(std::any_cast<const int&>(a), std::any_cast<const int&>(b));
    } else if (a.type() == typeid(double)) {
        return deepEqualsPrimitives(std::any_cast<const double&>(a), std::any_cast<const double&>(b));
    } else if (a.type() == typeid(std::string)) {
        return deepEqualsPrimitives(std::any_cast<const std::string&>(a), std::any_cast<const std::string&>(b));
    } else if (a.type() == typeid(std::vector<std::any>)) {
        return deepEqualsObjects(std::any_cast<const std::vector<std::any>&>(a), std::any_cast<const std::vector<std::any>&>(b));
    } else if (a.type() == typeid(std::unordered_map<std::string, std::any>)) {
        return deepEqualsObjects(std::any_cast<const std::unordered_map<std::string, std::any>&>(a), std::any_cast<const std::unordered_map<std::string, std::any>&>(b));
    }
    return false;
}

int main() {
    std::any a = 5
    return 0;
}