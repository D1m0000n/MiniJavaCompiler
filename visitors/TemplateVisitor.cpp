#include "TemplateVisitor.h"

#include "elements.h"

template<typename T>
T TemplateVisitor<T>::Accept(BaseElement * element) {
    element->Accept(this);
    return tos_value_;
}

template std::string TemplateVisitor<std::string>::Accept(BaseElement *element);
template int TemplateVisitor<int>::Accept(BaseElement* element);