#include <utils/types.h>

template<typename T>
TypeIndex getTypeIndex()
{
return std::type_index(typeid(T));
}