/* Copyright 2015 Peter Goodman (peter@trailofbits.com), all rights reserved. */

namespace {

template <typename D, typename S>
IMPL_INSTR(MOV, D dst, S src) {
  W(dst) = R(src);
}

}  // namespace

DEF_INSTR(MOV_GPR8_IMMb_C6r0_8) = MOV<R8W, IMM8>;
DEF_INSTR(MOV_MEMb_IMMb_8) = MOV<R8W, IMM8>;

DEF_INSTR(MOV_GPRv_IMMz_8) = MOV<R8W, IMM8>;
DEF_INSTR(MOV_GPRv_IMMz_16) = MOV<R16W, IMM16>;
DEF_INSTR(MOV_GPRv_IMMz_32) = MOV<R32W, IMM32>;
DEF_INSTR(MOV_GPRv_IMMz_64) = MOV<R64W, IMM64>;

DEF_INSTR(MOV_MEMv_IMMz_8) = MOV<M64, IMM8>;
DEF_INSTR(MOV_MEMv_IMMz_16) = MOV<M64, IMM16>;
DEF_INSTR(MOV_MEMv_IMMz_32) = MOV<M64, IMM32>;
DEF_INSTR(MOV_MEMv_IMMz_64) = MOV<M64, IMM64>;

DEF_INSTR(MOV_GPR8_GPR8_88_8) = MOV<R8W, R8>;
DEF_INSTR(MOV_MEMb_GPR8_8) = MOV<M8, R8>;

DEF_INSTR(MOV_MEMv_GPRv_64) = MOV<M64, R64>;
DEF_INSTR(MOV_MEMv_GPRv_32) = MOV<M64, R32>;
DEF_INSTR(MOV_MEMv_GPRv_16) = MOV<M64, R16>;
DEF_INSTR(MOV_MEMv_GPRv_8) = MOV<M64, R8>;

DEF_INSTR(MOV_GPRv_GPRv_89_64) = MOV<M64, R64>;
DEF_INSTR(MOV_GPRv_GPRv_89_32) = MOV<M64, R32>;
DEF_INSTR(MOV_GPRv_GPRv_89_16) = MOV<M64, R16>;
DEF_INSTR(MOV_GPRv_GPRv_89_8) = MOV<M64, R8>;

DEF_INSTR(MOV_GPR8_MEMb_8) = MOV<R8W, M8>;
DEF_INSTR(MOV_GPR8_GPR8_8A_8) = MOV<R8W, R8>;

DEF_INSTR(MOV_GPRv_MEMv_8) = MOV<R8W, M8>;
DEF_INSTR(MOV_GPRv_MEMv_16) = MOV<R16W, M16>;
DEF_INSTR(MOV_GPRv_MEMv_32) = MOV<R32W, M32>;
DEF_INSTR(MOV_GPRv_MEMv_64) = MOV<R64W, M64>;

DEF_INSTR(MOV_MEMv_GPRv_8B_64) = MOV<M64, R64>;
DEF_INSTR(MOV_MEMv_GPRv_8B_32) = MOV<M64, R32>;
DEF_INSTR(MOV_MEMv_GPRv_8B_16) = MOV<M64, R16>;
DEF_INSTR(MOV_MEMv_GPRv_8B_8) = MOV<M64, R8>;

//1148 MOV MOV_MEMw_SEG DATAXFER BASE I86 ATTRIBUTES:
//1149 MOV MOV_GPRv_SEG DATAXFER BASE I86 ATTRIBUTES: SCALABLE
//1150 MOV MOV_SEG_MEMw DATAXFER BASE I86 ATTRIBUTES: NOTSX
//1151 MOV MOV_SEG_GPR16 DATAXFER BASE I86 ATTRIBUTES: NOTSX

DEF_INSTR(MOV_AL_MEMb_8) = MOV<R8W, M8>;

DEF_INSTR(MOV_OrAX_MEMv_8) = MOV<R8W, M8>;
DEF_INSTR(MOV_OrAX_MEMv_16) = MOV<R16W, M16>;
DEF_INSTR(MOV_OrAX_MEMv_32) = MOV<R32W, M32>;
DEF_INSTR(MOV_OrAX_MEMv_64) = MOV<R64W, M64>;

DEF_INSTR(MOV_MEMb_AL_8) = MOV<M8, R8>;

DEF_INSTR(MOV_MEMv_OrAX_8) = MOV<M8, R8>;
DEF_INSTR(MOV_MEMv_OrAX_16) = MOV<M16, R16>;
DEF_INSTR(MOV_MEMv_OrAX_32) = MOV<M32, R32>;
DEF_INSTR(MOV_MEMv_OrAX_64) = MOV<M64, R64>;

DEF_INSTR(MOV_GPR8_IMMb_D0_8) = MOV<R8W, IMM8>;

DEF_INSTR(MOV_GPRv_IMMv_8) = MOV<R8W, SIMM8>;
DEF_INSTR(MOV_GPRv_IMMv_16) = MOV<R16W, SIMM16>;
DEF_INSTR(MOV_GPRv_IMMv_32) = MOV<R32W, SIMM32>;
DEF_INSTR(MOV_GPRv_IMMv_64) = MOV<R64W, SIMM64>;