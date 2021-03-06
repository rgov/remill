/* Copyright 2015 Peter Goodman (peter@trailofbits.com), all rights reserved. */

#ifndef REMILL_ARCH_RUNTIME_TYPES_H_
#define REMILL_ARCH_RUNTIME_TYPES_H_

#include "remill/Arch/Runtime/Util.h"
#include <cstdint>

#include <functional>
#include <limits>
#include <type_traits>

struct State;

// Address in the source architecture type. We don't use a `uintptr_t` because
// that might be specific to the destination architecture type.
typedef IF_64BIT_ELSE(uint64_t, uint32_t) addr_t;
typedef addr_t order_t;

typedef unsigned uint128_t __attribute__((mode(TI)));
static_assert(16 == sizeof(uint128_t), "Invalid `uint128_t` size.");

typedef int int128_t __attribute__((mode(TI)));
static_assert(16 == sizeof(int128_t), "Invalid `int128_t` size.");

union float32_t;
union float64_t;
struct float80_t;

union alignas(float) float32_t {
  float val;
  struct {
    uint32_t sign:1;
    uint32_t exponent:8;
    uint32_t fraction:23;
  } __attribute__((packed));

  ALWAYS_INLINE float32_t(void);
  ALWAYS_INLINE float32_t(float val_);
  ALWAYS_INLINE float32_t &operator=(float new_val);
  ALWAYS_INLINE float32_t &operator=(double new_val);
  ALWAYS_INLINE float32_t &operator=(const float64_t &new_val);
  ALWAYS_INLINE float32_t &operator=(int64_t new_val);
  ALWAYS_INLINE float32_t &operator=(int32_t new_val);
  ALWAYS_INLINE float32_t &operator=(int16_t new_val);
  ALWAYS_INLINE float32_t &operator=(int8_t new_val);
  ALWAYS_INLINE operator float(void) const;
} __attribute__((packed));

static_assert(4 == sizeof(float32_t), "Invalid `float32_t` size.");

union alignas(double) float64_t {
  double val;
  struct {
    uint64_t sign:1;
    uint64_t exponent:11;
    uint64_t fraction:52;
  } __attribute__((packed));

  ALWAYS_INLINE float64_t(void);
  ALWAYS_INLINE float64_t(double val_);
  ALWAYS_INLINE float64_t(float val_);
  ALWAYS_INLINE float64_t(float32_t val_);
  ALWAYS_INLINE float64_t &operator=(double new_val);
  ALWAYS_INLINE float64_t &operator=(float new_val);
  ALWAYS_INLINE float64_t &operator=(float32_t new_val);
  ALWAYS_INLINE float64_t &operator=(int64_t new_val);
  ALWAYS_INLINE float64_t &operator=(int32_t new_val);
  ALWAYS_INLINE float64_t &operator=(int16_t new_val);
  ALWAYS_INLINE float64_t &operator=(int8_t new_val);
  ALWAYS_INLINE operator double(void) const;
} __attribute__((packed));

static_assert(8 == sizeof(float64_t), "Invalid `float64_t` size.");

struct alignas(1) float80_t {
  struct {
    uint16_t sign:1;
    uint16_t exponent:15;
  } __attribute__((packed));
  struct {
    uint64_t integer:1;
    uint64_t fraction:63;
  } __attribute__((packed));

  ALWAYS_INLINE float80_t(void);
  ALWAYS_INLINE float80_t(float32_t);
  ALWAYS_INLINE float80_t(float64_t);
  ALWAYS_INLINE float80_t &operator=(float32_t new_val);
  ALWAYS_INLINE float80_t &operator=(float64_t new_val);

} __attribute__((packed));

static_assert(10 == sizeof(float80_t), "Invalid `float80_t` size.");

// Add in some missing type traits.
namespace std {

template <>
struct is_signed<int128_t> {
  static constexpr bool value = true;
};

template <>
struct is_unsigned<int128_t> {
  static constexpr bool value = false;
};

template <>
struct is_signed<uint128_t> {
  static constexpr bool value = false;
};

template <>
struct is_unsigned<uint128_t> {
  static constexpr bool value = true;
};

}  // namespace

template <typename T>
struct VectorInfo;

template <typename T>
struct AggVectorInfo;

// Forward-declaration of basic vector types.
union vec8_t;
union vec16_t;
union vec32_t;
union vec64_t;
union vec128_t;
union vec256_t;
union vec512_t;

// TODO(pag): See if using the `ext_vector_type` attribute (OpenCL) produces
//            better code. These might also work better with NEON because they
//            support different kinds of selectors (`xyzw`).
#define MAKE_VECTOR(base_type, prefix, nelms, vec_size_bits, width_bytes) \
    typedef base_type prefix ## v ## nelms ## _t \
        __attribute__((vector_size(width_bytes))); \
    static_assert(width_bytes == sizeof(prefix ## v ## nelms ## _t), \
        "Invalid definition of `" #prefix "v" #nelms "`."); \
    static_assert((width_bytes * 8) == vec_size_bits, \
            "Invalid definition of `" #prefix "v" #nelms "`."); \
    template <> \
    struct VectorInfo<prefix ## v ## nelms ## _t> { \
      enum { \
        kNumElms = nelms \
      }; \
      typedef base_type BaseType; \
      typedef vec ## vec_size_bits ## _t VecType; \
    }

MAKE_VECTOR(uint8_t, uint8, 1, 8, 1);
MAKE_VECTOR(uint8_t, uint8, 2, 16, 2);
MAKE_VECTOR(uint8_t, uint8, 4, 32, 4);
MAKE_VECTOR(uint8_t, uint8, 8, 64, 8);
MAKE_VECTOR(uint8_t, uint8, 16, 128, 16);
MAKE_VECTOR(uint8_t, uint8, 32, 256, 32);
MAKE_VECTOR(uint8_t, uint8, 64, 512, 64);

MAKE_VECTOR(uint16_t, uint16, 1, 16, 2);
MAKE_VECTOR(uint16_t, uint16, 2, 32, 4);
MAKE_VECTOR(uint16_t, uint16, 4, 64, 8);
MAKE_VECTOR(uint16_t, uint16, 8, 128, 16);
MAKE_VECTOR(uint16_t, uint16, 16, 256, 32);
MAKE_VECTOR(uint16_t, uint16, 32, 512, 64);

MAKE_VECTOR(uint32_t, uint32, 1, 32, 4);
MAKE_VECTOR(uint32_t, uint32, 2, 64, 8);
MAKE_VECTOR(uint32_t, uint32, 4, 128, 16);
MAKE_VECTOR(uint32_t, uint32, 8, 256, 32);
MAKE_VECTOR(uint32_t, uint32, 16, 512, 64);

MAKE_VECTOR(uint64_t, uint64, 1, 64, 8);
MAKE_VECTOR(uint64_t, uint64, 2, 128, 16);
MAKE_VECTOR(uint64_t, uint64, 4, 256, 32);
MAKE_VECTOR(uint64_t, uint64, 8, 512, 64);

//MAKE_VECTOR(uint128_t, uint128, 0, 64, 8);
MAKE_VECTOR(uint128_t, uint128, 1, 128, 16);
MAKE_VECTOR(uint128_t, uint128, 2, 256, 32);
MAKE_VECTOR(uint128_t, uint128, 4, 512, 64);

MAKE_VECTOR(float, float32, 1, 32, 4);
MAKE_VECTOR(float, float32, 2, 64, 8);
MAKE_VECTOR(float, float32, 4, 128, 16);
MAKE_VECTOR(float, float32, 8, 256, 32);
MAKE_VECTOR(float, float32, 16, 512, 64);

MAKE_VECTOR(double, float64, 1, 64, 8);
MAKE_VECTOR(double, float64, 2, 128, 16);
MAKE_VECTOR(double, float64, 4, 256, 32);
MAKE_VECTOR(double, float64, 8, 512, 64);

template <typename T>
struct SingletonVectorType;

template <>
struct SingletonVectorType<uint8_t> {
  typedef uint8v1_t Type;
};

template <>
struct SingletonVectorType<uint16_t> {
  typedef uint16v1_t Type;
};

template <>
struct SingletonVectorType<uint32_t> {
  typedef uint32v1_t Type;
};

template <>
struct SingletonVectorType<uint64_t> {
  typedef uint64v1_t Type;
};

template <>
struct SingletonVectorType<uint128_t> {
  typedef uint128v1_t Type;
};

template <>
struct SingletonVectorType<float32_t> {
  typedef float32v1_t Type;
};

template <>
struct SingletonVectorType<float64_t> {
  typedef float64v1_t Type;
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"

union vec8_t final {
  ALWAYS_INLINE vec8_t(void);

  uint8v1_t bytes;
  uint8v1_t iwords;  // Ideal.

} __attribute__((packed));

static_assert(1 == sizeof(vec8_t) &&
              1 == sizeof(vec8_t().bytes) &&
              1 == sizeof(vec8_t().iwords),
              "Invalid structure packing of `vec8_t`.");

union vec16_t final {
  ALWAYS_INLINE vec16_t(void);
  ALWAYS_INLINE vec16_t(vec8_t sub_vec);

  uint8v2_t bytes;
  uint16v1_t words;
  uint16v1_t iwords;  // Ideal.
} __attribute__((packed));

static_assert(2 == sizeof(vec16_t) &&
              2 == sizeof(vec16_t().bytes) &&
              2 == sizeof(vec16_t().words) &&
              2 == sizeof(vec16_t().iwords),
              "Invalid structure packing of `vec16_t`.");

union vec32_t final {
  ALWAYS_INLINE vec32_t(void);
  ALWAYS_INLINE vec32_t(vec8_t sub_vec);
  ALWAYS_INLINE vec32_t(vec16_t sub_vec);

  uint8v4_t bytes;
  uint16v2_t words;
  uint32v1_t dwords;
  uint32v1_t iwords;  // Ideal.
  float32v1_t floats;
} __attribute__((packed));

static_assert(4 == sizeof(vec32_t) &&
              4 == sizeof(vec32_t().bytes) &&
              4 == sizeof(vec32_t().words) &&
              4 == sizeof(vec32_t().dwords) &&
              4 == sizeof(vec32_t().floats) &&
              4 == sizeof(vec32_t().iwords),
              "Invalid structure packing of `vec32_t`.");

union vec64_t final {
  ALWAYS_INLINE vec64_t(void);
  ALWAYS_INLINE vec64_t(vec8_t sub_vec);
  ALWAYS_INLINE vec64_t(vec16_t sub_vec);
  ALWAYS_INLINE vec64_t(vec32_t sub_vec);

  uint8v8_t bytes;
  uint16v4_t words;
  uint32v2_t dwords;
  uint64v1_t qwords;

  IF_64BIT_ELSE(uint64v1_t, uint32v2_t) iwords;  // Ideal.

  float32v2_t floats;
  float64v1_t doubles;
} __attribute__((packed));

#pragma clang diagnostic pop

static_assert(8 == sizeof(vec64_t) &&
              8 == sizeof(vec64_t().bytes) &&
              8 == sizeof(vec64_t().words) &&
              8 == sizeof(vec64_t().dwords) &&
              8 == sizeof(vec64_t().qwords) &&
              8 == sizeof(vec64_t().floats) &&
              8 == sizeof(vec64_t().doubles) &&
              8 == sizeof(vec64_t().iwords),
              "Invalid structure packing of `vec64_t`.");

union vec128_t final {
  ALWAYS_INLINE vec128_t(void);
  ALWAYS_INLINE vec128_t(vec8_t sub_vec);
  ALWAYS_INLINE vec128_t(vec16_t sub_vec);
  ALWAYS_INLINE vec128_t(vec32_t sub_vec);
  ALWAYS_INLINE vec128_t(vec64_t sub_vec);

  uint8v16_t bytes;
  uint16v8_t words;
  uint32v4_t dwords;
  uint64v2_t qwords;

  IF_64BIT_ELSE(uint64v2_t, uint32v4_t) iwords;  // Ideal.

  uint128v1_t dqwords;
  float32v4_t floats;
  float64v2_t doubles;
} __attribute__((packed));

static_assert(16 == sizeof(vec128_t) &&
              16 == sizeof(vec128_t().bytes) &&
              16 == sizeof(vec128_t().words) &&
              16 == sizeof(vec128_t().dwords) &&
              16 == sizeof(vec128_t().qwords) &&
              16 == sizeof(vec128_t().dqwords) &&
              16 == sizeof(vec128_t().floats) &&
              16 == sizeof(vec128_t().doubles) &&
              16 == sizeof(vec128_t().iwords),
              "Invalid structure packing of `vec128_t`.");

union vec256_t final {
  ALWAYS_INLINE vec256_t(void);
  ALWAYS_INLINE vec256_t(vec8_t sub_vec);
  ALWAYS_INLINE vec256_t(vec16_t sub_vec);
  ALWAYS_INLINE vec256_t(vec32_t sub_vec);
  ALWAYS_INLINE vec256_t(vec64_t sub_vec);
  ALWAYS_INLINE vec256_t(vec128_t sub_vec);

  uint8v32_t bytes;
  uint16v16_t words;
  uint32v8_t dwords;
  uint64v4_t qwords;
  uint128v2_t dqwords;

  IF_64BIT_ELSE(uint64v4_t, uint32v8_t) iwords;  // Ideal.

  float32v8_t floats;
  float64v4_t doubles;
} __attribute__((packed));


static_assert(32 == sizeof(vec256_t) &&
              32 == sizeof(vec256_t().bytes) &&
              32 == sizeof(vec256_t().words) &&
              32 == sizeof(vec256_t().dwords) &&
              32 == sizeof(vec256_t().qwords) &&
              32 == sizeof(vec256_t().dqwords) &&
              32 == sizeof(vec256_t().floats) &&
              32 == sizeof(vec256_t().doubles) &&
              32 == sizeof(vec256_t().iwords),
              "Invalid structure packing of `vec256_t`.");

union vec512_t final {
  ALWAYS_INLINE vec512_t(void);
  ALWAYS_INLINE vec512_t(vec8_t sub_vec);
  ALWAYS_INLINE vec512_t(vec16_t sub_vec);
  ALWAYS_INLINE vec512_t(vec32_t sub_vec);
  ALWAYS_INLINE vec512_t(vec64_t sub_vec);
  ALWAYS_INLINE vec512_t(vec128_t sub_vec);
  ALWAYS_INLINE vec512_t(vec256_t sub_vec);

  uint8v64_t bytes;
  uint16v32_t words;
  uint32v16_t dwords;
  uint64v8_t qwords;
  uint128v4_t dqwords;

  uint128v4_t iwords;  // Ideal.

  float32v16_t floats;
  float64v8_t doubles;
} __attribute__((packed));

static_assert(64 == sizeof(vec512_t) &&
              64 == sizeof(vec512_t().bytes) &&
              64 == sizeof(vec512_t().words) &&
              64 == sizeof(vec512_t().dwords) &&
              64 == sizeof(vec512_t().qwords) &&
              64 == sizeof(vec512_t().dqwords) &&
              64 == sizeof(vec512_t().floats) &&
              64 == sizeof(vec512_t().doubles) &&
              64 == sizeof(vec512_t().iwords),
              "Invalid structure packing of `vec512_t`.");

// Aligned vector types.
typedef vec8_t avec8_t __attribute__((aligned(64)));
typedef vec16_t avec16_t __attribute__((aligned(64)));
typedef vec32_t avec32_t __attribute__((aligned(64)));
typedef vec64_t avec64_t __attribute__((aligned(64)));
typedef vec128_t avec128_t __attribute__((aligned(64)));
typedef vec256_t avec256_t __attribute__((aligned(64)));
typedef vec512_t avec512_t __attribute__((aligned(64)));

#define MAKE_AGG_VEC_INFO(type) \
  template <> \
  struct AggVectorInfo<type> { \
    enum : size_t { \
      kSize = sizeof(type) \
    }; \
    typedef type Type; \
  }

MAKE_AGG_VEC_INFO(vec8_t);
MAKE_AGG_VEC_INFO(vec16_t);
MAKE_AGG_VEC_INFO(vec32_t);
MAKE_AGG_VEC_INFO(vec64_t);
MAKE_AGG_VEC_INFO(vec128_t);
MAKE_AGG_VEC_INFO(vec256_t);
MAKE_AGG_VEC_INFO(vec512_t);

template <typename T>
struct NextLargerIntegerType;

template <typename T>
struct NextSmallerIntegerType;

template <typename T>
struct SignedIntegerType {
  typedef T Type;
};

template <typename T>
struct UnsignedIntegerType {
  typedef T Type;
};

#define MAKE_SIGNED_INT_CHANGERS(signed_type, unsigned_type) \
    static_assert(sizeof(signed_type) == sizeof(unsigned_type), \
                  "Invalid int changer type type."); \
    static_assert(std::is_signed<signed_type>::value != \
                  std::is_signed<unsigned_type>::value, \
                  "Sign match between int type and next int type."); \
    template <> \
    struct SignedIntegerType<unsigned_type> { \
      typedef signed_type Type ; \
    }; \
    template <> \
    struct UnsignedIntegerType<signed_type> { \
      typedef unsigned_type Type ; \
    }

#define MAKE_INT_TYPE(cur, next) \
    static_assert(sizeof(next) == (2 * sizeof(cur)), \
                  "Invalid next int type."); \
    static_assert(std::is_signed<cur>::value == std::is_signed<next>::value, \
                  "Sign mismatch between int type and next int type."); \
    template <> \
    struct NextLargerIntegerType<cur> { \
      typedef next Type; \
    }; \
    template <> \
    struct NextSmallerIntegerType<next> { \
      typedef cur Type; \
    }

MAKE_SIGNED_INT_CHANGERS(int8_t, uint8_t);
MAKE_SIGNED_INT_CHANGERS(int16_t, uint16_t);
MAKE_SIGNED_INT_CHANGERS(int32_t, uint32_t);
MAKE_SIGNED_INT_CHANGERS(int64_t, uint64_t);
MAKE_SIGNED_INT_CHANGERS(int128_t, uint128_t);

MAKE_INT_TYPE(int8_t, int16_t);
MAKE_INT_TYPE(uint8_t, uint16_t);

MAKE_INT_TYPE(int16_t, int32_t);
MAKE_INT_TYPE(uint16_t, uint32_t);

MAKE_INT_TYPE(int32_t, int64_t);
MAKE_INT_TYPE(uint32_t, uint64_t);

MAKE_INT_TYPE(int64_t, int128_t);
MAKE_INT_TYPE(uint64_t, uint128_t);

#undef MAKE_SIGNED_INT_CHANGERS
#undef MAKE_INT_TYPE

#define WIDEN_INTEGER_TYPE(T) \
  typename NextLargerIntegerType<T>::Type

#define TO_SIGNED_INTEGER_TYPE(T) \
  typename SignedIntegerType<T>::Type

#define TO_UNSIGNED_INTEGER_TYPE(T) \
  typename UnsignedIntegerType<T>::Type

template <typename T>
struct Mn final {
  addr_t addr;
};

template <typename T>
struct MnW final {
  addr_t addr;
};

// Note: We use `addr_t` as the internal type for `Rn` and `In` struct templates
//       because this will be the default register size used for parameter
//       passing in the underlying ABI that Clang chooses to use when converting
//       this code to bitcode. We want to avoid the issue where a size that's
//       too small, e.g. `uint8_t` or `uint16_t` in a struct, is passed as an
//       aligned pointer to a `byval` parameter.
template <typename T>
struct Rn final {
  const addr_t val;
};

template <typename T>
struct RnW final {
  T *val_ref;
};

template <>
struct Rn<float32_t> final {
  const float32_t val;
};

template <>
struct Rn<float64_t> final {
  const float64_t val;
};

template <>
struct RnW<float32_t> final {
  float32_t *val_ref;
};

template <>
struct RnW<float64_t> final {
  float64_t *val_ref;
};

template <typename T>
struct In final {
  const addr_t val;
};

template <typename T>
struct Vn final {
  const T *val;
};

template <typename T>
struct VnW final {
  T *val_ref;
};

template <typename T>
struct BaseType {
  typedef T Type;
};

#define BASE_TYPE_OF(T) \
  typename BaseType<T>::Type

template <typename T>
struct IsRegister {
  static constexpr bool kValue = false;
};

template <typename T>
struct IsRegister<Rn<T>> {
  static constexpr bool kValue = true;
};

template <typename T>
struct IsRegister<RnW<T>> {
  static constexpr bool kValue = true;
};

template <typename T>
struct IsRegister<Vn<T>> {
  static constexpr bool kValue = true;
};

template <typename T>
struct IsRegister<VnW<T>> {
  static constexpr bool kValue = true;
};

template <typename T>
struct BaseType<volatile T> : public BaseType<T> {};

template <typename T>
struct BaseType<const T> : public BaseType<T> {};

template <typename T>
struct BaseType<T &> : public BaseType<T> {};

template <typename T>
struct BaseType<T *> : public BaseType<T> {};

template <typename T>
struct BaseType<Mn<T>> : public BaseType<T> {};

template <typename T>
struct BaseType<MnW<T>> : public BaseType<T> {};

template <typename T>
struct BaseType<Rn<T>> : public BaseType<T> {};

template <typename T>
struct BaseType<RnW<T>> : public BaseType<T> {};

template <typename T>
struct BaseType<In<T>> {
  typedef typename BaseType<T>::Type Type;
};

template <typename T>
struct BaseType<Vn<T>> {
  typedef typename BaseType<T>::Type Type;
};

template <typename T>
struct BaseType<VnW<T>> {
  typedef typename BaseType<T>::Type Type;
};

inline uint8_t operator "" _u8(unsigned long long value) {
  return static_cast<uint8_t>(value);
}

inline uint16_t operator "" _u16(unsigned long long value) {
  return static_cast<uint16_t>(value);
}

inline uint32_t operator "" _u32(unsigned long long value) {
  return static_cast<uint32_t>(value);
}

inline uint64_t operator "" _u64(unsigned long long value) {
  return static_cast<uint64_t>(value);
}

inline int8_t operator "" _s8(unsigned long long value) {
  return static_cast<int8_t>(value);
}

inline int16_t operator "" _s16(unsigned long long value) {
  return static_cast<int16_t>(value);
}

inline int32_t operator "" _s32(unsigned long long value) {
  return static_cast<int32_t>(value);
}

inline int64_t operator "" _s64(unsigned long long value) {
  return static_cast<int64_t>(value);
}
#endif  // REMILL_ARCH_RUNTIME_TYPES_H_
