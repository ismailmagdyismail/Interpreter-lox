#include <any>
#include <string>
#include <iomanip>
#include <sstream>

#define PRECISON 5

namespace Object
{
    std::string toString(const std::any& value) {
        if (!value.has_value()) {
            return std::string("null");
        }
        if (value.type() == typeid(int)) {
            return std::to_string(std::any_cast<int>(value));
        }
        if (value.type() == typeid(double)) {
            std::ostringstream stream;
            stream << std::fixed << std::setprecision(PRECISON) << std::any_cast<double>(value);
            return stream.str();
        }
        if (value.type() == typeid(std::string)) {
            return std::any_cast<std::string>(value);
        }
        if (value.type() == typeid(float)) {
            return std::to_string(std::any_cast<float>(value));
        }
        if (value.type() == typeid(bool)) {
            return std::to_string(std::any_cast<bool>(value));
        }
        return "Unsupported type";
    }
}
