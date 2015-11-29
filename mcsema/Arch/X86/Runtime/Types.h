/* Copyright 2015 Peter Goodman (peter@trailofbits.com), all rights reserved. */

#ifndef MCSEMA_ARCH_X86_RUNTIME_TYPES_H_
#define MCSEMA_ARCH_X86_RUNTIME_TYPES_H_

typedef RnW<uint8_t> R8W;
typedef RnW<uint16_t> R16W;
typedef RnW<decltype(Reg().full)> R32W;  // AMD64-ism.
IF_64BIT( typedef RnW<uint64_t> R64W; )

typedef Rn<uint8_t> R8;
typedef Rn<uint16_t> R16;
typedef Rn<uint32_t> R32;
IF_64BIT( typedef Rn<uint64_t> R64; )

typedef Vn<vec64_t> V64;
typedef Vn<avec128_t> V128;
typedef Vn<avec256_t> V256;
IF_AVX512( typedef Vn<avec512_t> V512; )

typedef IF_AVX512_ELSE(avec512_t, IF_AVX_ELSE(avec256_t, avec128_t)) WriteVecType;

typedef VnW<vec64_t> V64W;  // Legacy MMX technology register.
typedef VnW<WriteVecType> V128W;
IF_AVX( typedef VnW<WriteVecType> V256W; )
IF_AVX512( typedef VnW<WriteVecType> V512W; )

typedef MnW<uint8_t> M8W;
typedef MnW<uint16_t> M16W;
typedef MnW<uint64_t> M32W;
IF_64BIT( typedef MnW<uint64_t> M64W; )

typedef MnW<vec64_t> MV64W;
typedef MnW<vec128_t> MV128W;
IF_AVX( typedef MnW<vec256_t> MV256W; )
IF_AVX512( typedef MnW<vec512_t> MV512W; )

typedef Mn<uint8_t> M8;
typedef Mn<uint16_t> M16;
typedef Mn<uint32_t> M32;
IF_64BIT( typedef Mn<uint64_t> M64; )

typedef Mn<vec64_t> MV64;
typedef Mn<vec128_t> MV128;
IF_AVX( typedef Mn<vec256_t> MV256; )
IF_AVX512( typedef Mn<vec512_t> MV512; )

typedef In<uint8_t> I8;
typedef In<uint16_t> I16;
typedef In<uint32_t> I32;
IF_64BIT( typedef In<uint64_t> I64; )

typedef addr_t PC;
typedef addr_t ADDR;

#endif  // MCSEMA_ARCH_X86_RUNTIME_TYPES_H_