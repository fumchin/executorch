/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <Foundation/Foundation.h>

#ifdef __cplusplus

#import <executorch/runtime/core/exec_aten/exec_aten.h>
#import <executorch/runtime/core/exec_aten/util/scalar_type_util.h>

namespace executorch::extension::utils {
using namespace aten;
using namespace runtime;

/**
 * Deduces the scalar type for a given NSNumber based on its type encoding.
 *
 * @param number The NSNumber instance whose scalar type is to be deduced.
 * @return The corresponding ScalarType.
 */
static inline ScalarType deduceScalarType(NSNumber *number) {
  auto type = [number objCType][0];
  type = (type >= 'A' && type <= 'Z') ? type + ('a' - 'A') : type;
  if (type == 'c') {
    return ScalarType::Byte;
  } else if (type == 's') {
    return ScalarType::Short;
  } else if (type == 'i') {
    return ScalarType::Int;
  } else if (type == 'q' || type == 'l') {
    return ScalarType::Long;
  } else if (type == 'f') {
    return ScalarType::Float;
  } else if (type == 'd') {
    return ScalarType::Double;
  }
  ET_CHECK_MSG(false, "Unsupported type: %c", type);
  return ScalarType::Undefined;
}

/**
 * Converts the value held in the NSNumber to the specified C++ type T.
 *
 * @tparam T The target C++ numeric type.
 * @param number The NSNumber instance to extract the value from.
 * @return The value converted to type T.
 */
template <typename T>
static inline T extractValue(NSNumber *number) {
  ET_CHECK_MSG(!(isFloatingType(deduceScalarType(number)) &&
    isIntegralType(CppTypeToScalarType<T>::value, true)),
    "Cannot convert floating point to integral type");
  T value;
  if constexpr (std::is_same_v<T, uint8_t>) {
    value = number.unsignedCharValue;
  } else if constexpr (std::is_same_v<T, int8_t>) {
    value = number.charValue;
  } else if constexpr (std::is_same_v<T, int16_t>) {
    value = number.shortValue;
  } else if constexpr (std::is_same_v<T, int32_t>) {
    value = number.intValue;
  } else if constexpr (std::is_same_v<T, int64_t>) {
    value = number.longLongValue;
  } else if constexpr (std::is_same_v<T, float>) {
    value = number.floatValue;
  } else if constexpr (std::is_same_v<T, double>) {
    value = number.doubleValue;
  } else if constexpr (std::is_same_v<T, BOOL>) {
    value = number.boolValue;
  } else if constexpr (std::is_same_v<T, uint16_t>) {
    value = number.unsignedShortValue;
  } else if constexpr (std::is_same_v<T, uint32_t>) {
    value = number.unsignedIntValue;
  } else if constexpr (std::is_same_v<T, uint64_t>) {
    value = number.unsignedLongLongValue;
  } else if constexpr (std::is_same_v<T, NSInteger>) {
    value = number.integerValue;
  } else if constexpr (std::is_same_v<T, NSUInteger>) {
    value = number.unsignedIntegerValue;
  } else if constexpr (std::is_same_v<T, BFloat16> ||
                       std::is_same_v<T, Half>) {
    value = T(number.floatValue);
  } else {
    static_assert(sizeof(T) == 0, "Unsupported type");
  }
  ET_DCHECK_MSG(std::numeric_limits<T>::lowest() <= value && value <= std::numeric_limits<T>::max(),
    "Value out of range");
  return value;
}

} // namespace executorch::extension::utils

#endif // __cplusplus
