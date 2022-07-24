
#ifndef STONECOLD_COMMON_TYPES_H
#define STONECOLD_COMMON_TYPES_H

#include <memory>
#include <cstdint>
#include <typeinfo>
#include <typeindex>

// Macro to get the name of a variable
#define GET_VARIABLE_NAME(Variable) (#Variable)

namespace StoneCold::Common {

// StoneCold signed integer typedefs (fastest option, with a width of at least (!) 8, 16, 32 and 64 bits) 
using scInt8 = std::int_fast8_t;
using scInt16 = std::int_fast16_t;
using scInt32 = std::int_fast32_t;
using scInt64 = std::int_fast64_t;
// StoneCold unsigned integer typedefs (fastest option, with a width of at least (!) 8, 16, 32 and 64 bits) 
using scUint8 = std::uint_fast8_t;
using scUint16 = std::uint_fast16_t;
using scUint32 = std::uint_fast32_t;
using scUint64 = std::uint_fast64_t;
// StoneCold bit-mask typedefs (normal int option, with a width of exactly (!) 32 or 64 bits) 
using scBitMask32 = std::uint32_t;
using scBitMask64 = std::uint64_t;
// StoneCold custom integer typedefs
using scByte = std::uint_fast8_t;
using scEntityId = std::uint_fast16_t;
using scHash = std::uint_fast64_t;

template<class T> using scUptr = std::unique_ptr<T>;
template<class T> using scSptr = std::shared_ptr<T>;

template<typename T>
inline scHash GetTypeHash() noexcept { return std::type_index(typeid(T)).hash_code(); }

}

#endif
