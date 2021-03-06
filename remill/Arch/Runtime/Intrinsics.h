/* Copyright 2015 Peter Goodman (peter@trailofbits.com), all rights reserved. */

#ifndef REMILL_ARCH_SEMANTICS_INSTRINSICS_H_
#define REMILL_ARCH_SEMANTICS_INSTRINSICS_H_

#include "remill/Arch/Runtime/Types.h"

extern "C" {

extern order_t __remill_memory_order;

// The basic block "template".
[[gnu::used]]
void __remill_basic_block(State &state, addr_t);

// Address computation intrinsic. This is only used for non-zero
// `address_space`d memory accesses.
[[gnu::used]]
extern addr_t __remill_compute_address(
    const State &state, addr_t address, int address_space);

// Semantics, describes that some value is now a possible program counter.
[[gnu::used]]
extern addr_t __remill_create_program_counter(addr_t);

// Memory read intrinsics.
[[gnu::used]]
extern uint8_t __remill_read_memory_8(order_t, addr_t);

[[gnu::used]]
extern uint16_t __remill_read_memory_16(order_t, addr_t);

[[gnu::used]]
extern uint32_t __remill_read_memory_32(order_t, addr_t);

[[gnu::used]]
extern uint64_t __remill_read_memory_64(order_t, addr_t);

[[gnu::used]]
extern order_t __remill_read_memory_v8(order_t, addr_t, vec8_t &);

[[gnu::used]]
extern order_t __remill_read_memory_v16(order_t, addr_t, vec16_t &);

[[gnu::used]]
extern order_t __remill_read_memory_v32(order_t, addr_t, vec32_t &);

[[gnu::used]]
extern order_t __remill_read_memory_v64(order_t, addr_t, vec64_t &);

[[gnu::used]]
extern order_t __remill_read_memory_v128(order_t, addr_t, vec128_t &);

[[gnu::used]]
extern order_t __remill_read_memory_v256(order_t, addr_t, vec256_t &);

[[gnu::used]]
extern order_t __remill_read_memory_v512(order_t, addr_t, vec512_t &);

// Memory write intrinsics.
[[gnu::used]]
extern order_t __remill_write_memory_8(order_t, addr_t, uint8_t);

[[gnu::used]]
extern order_t __remill_write_memory_16(order_t, addr_t, uint16_t);

[[gnu::used]]
extern order_t __remill_write_memory_32(order_t, addr_t, uint32_t);

[[gnu::used]]
extern order_t __remill_write_memory_64(order_t, addr_t, uint64_t);

[[gnu::used]]
extern order_t __remill_write_memory_v8(order_t, addr_t, const vec8_t &);

[[gnu::used]]
extern order_t __remill_write_memory_v16(order_t, addr_t, const vec16_t &);

[[gnu::used]]
extern order_t __remill_write_memory_v32(order_t, addr_t, const vec32_t &);

[[gnu::used]]
extern order_t __remill_write_memory_v64(order_t, addr_t, const vec64_t &);

[[gnu::used]]
extern order_t __remill_write_memory_v128(order_t, addr_t, const vec128_t &);

[[gnu::used]]
extern order_t __remill_write_memory_v256(order_t, addr_t, const vec256_t &);

[[gnu::used]]
extern order_t __remill_write_memory_v512(order_t, addr_t, const vec512_t &);


[[gnu::used]]
extern order_t __remill_read_memory_f32(order_t, addr_t, float32_t &);

[[gnu::used]]
extern order_t __remill_read_memory_f64(order_t, addr_t, float64_t &);

[[gnu::used]]
extern order_t __remill_read_memory_f80(order_t, addr_t, float80_t &);

[[gnu::used]]
extern order_t __remill_write_memory_f32(order_t, addr_t, const float32_t &);

[[gnu::used]]
extern order_t __remill_write_memory_f64(order_t, addr_t, const float64_t &);

[[gnu::used]]
extern order_t __remill_write_memory_f80(order_t, addr_t, const float80_t &);

[[gnu::used]]
extern bool __remill_undefined_bool(void);

[[gnu::used]]
extern uint8_t __remill_undefined_8(void);

[[gnu::used]]
extern uint16_t __remill_undefined_16(void);

[[gnu::used]]
extern uint32_t __remill_undefined_32(void);

[[gnu::used]]
extern uint64_t __remill_undefined_64(void);

[[gnu::used]]
extern float32_t __remill_undefined_f32(void);

[[gnu::used]]
extern float64_t __remill_undefined_f64(void);

// Inlining control. The idea here is that sometimes we want to defer inlining
// until a later time, and we need to communicate what should eventually be
// inlined, even if it's not currently inlined.
[[gnu::used]]
extern void __remill_defer_inlining(void);

// Generic error.
[[gnu::used]]
extern void __remill_error(State &, addr_t addr);

// Control-flow intrinsics.
[[gnu::used]]
extern void __remill_function_call(State &, addr_t addr);

[[gnu::used]]
extern void __remill_function_return(State &, addr_t addr);

[[gnu::used]]
extern void __remill_jump(State &, addr_t addr);

[[gnu::used]]
extern void __remill_system_call(State &, addr_t ret_addr);

[[gnu::used]]
extern void __remill_system_return(State &, addr_t addr);

[[gnu::used]]
extern void __remill_interrupt_call(State &, addr_t ret_addr);

[[gnu::used]]
extern void __remill_interrupt_return(State &, addr_t addr);

// Represents a known unknown block.
[[gnu::used]]
extern void __remill_missing_block(State &, addr_t);

[[gnu::used]]
extern addr_t __remill_conditional_branch(
    bool condition, addr_t if_true, addr_t if_false);

// Memory barriers types, see: http://g.oswego.edu/dl/jmm/cookbook.html
[[gnu::used]]
extern order_t __remill_barrier_load_load(order_t);

[[gnu::used]]
extern order_t __remill_barrier_load_store(order_t);

[[gnu::used]]
extern order_t __remill_barrier_store_load(order_t);

[[gnu::used]]
extern order_t __remill_barrier_store_store(order_t);

// Atomic operations. The address/size are hints, but the granularity of the
// access can be bigger. These have implicit StoreLoad semantics.
[[gnu::used]]
extern order_t __remill_atomic_begin(order_t);

[[gnu::used]]
extern order_t __remill_atomic_end(order_t);

// Arch-specific feature lookup. Implemented as a pseudo control-flow
// intrinsic.
[[gnu::used]]
extern void __remill_read_cpu_features(State &, addr_t addr);

// Arch-specific. Marshal a float80_t into a float64_t.
//
// TODO(pag): https://stackoverflow.com/questions/2963055/msvc-win32-convert-extended-precision-float-80-bit-to-double-64-bit
extern void __remill_read_f80(const float80_t &, float64_t &);

// Arch-specific. Marshal a float64_t into a float64_t.
extern void __remill_write_f80(const float64_t &, float80_t &);

#define __remill_barrier_compiler()
//  __asm__ __volatile__ ("" ::: "memory")

[[gnu::used]]
extern void __remill_intrinsics(void);

}  // extern C

#endif  // REMILL_ARCH_SEMANTICS_INSTRINSICS_H_
