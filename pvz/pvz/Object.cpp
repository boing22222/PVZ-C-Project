#include "Object.h"
std::string Object::GetName() {
    return className;
}

void Object::SetName(const std::string& cName) {
    className = cName;
}