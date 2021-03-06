#pragma once

// Prevents compiler from creating default copy constructor/assignment operator
#define DISABLE_COPY(type_name) \
  type_name(type_name const&) = delete; \
  type_name& operator=(type_name const&) = delete;

// Prevents compiler from creating default move constructor/assignment operator
#define DISABLE_MOVE(type_name) \
  type_name(type_name const&&) = delete; \
  type_name& operator=(type_name&&) = delete;

// Prevents compiler from creating default constructor
#define DISABLE_CONSTRUCTION(type_name) \
    type_name() = delete;

// Add quotes to a string containing a macro
// Allows for macro expansion within a string:
//
// Instead of "bar/FOO/baz" use QUOTE(bar/FOO/baz)
// to get the expanded value for FOO
#define QUOTE_(m) #m
#define QUOTE(m) QUOTE_(m)

// Joins two tokens together after macro expansion of either token
// #define PREFIX foo
// PREFIX ## bar => PREFIXbar
// TOKEN_JOIN(PREFIX, bar) => foobar
#define TOKEN_JOIN_(a, b) a ## b
#define TOKEN_JOIN(a, b) TOKEN_JOIN_(a, b)

#ifdef __GNUC__
// Force GCC to inline
#define INLINE inline __attribute__((always_inline))

// Prevent inlining
#define NOINLINE __attribute__((noinline))

// Use to force function return values to be used/checked
#define MUST_CHECK [[nodiscard]]
#define MUST_USE [[nodiscard]]

// Specify section for placement
#define SECTION(s)  __attribute__((section(s)))

// Specify a weak symbol
#define WEAK __attribute__((weak))

// Marks a declaration as used, in cases where the compiler can't see the
// connection (e.g. only used from assembly or ABI).
#define USED __attribute__((used))

// Create a symbol alias
#define ALIAS(s) __attribute__((alias (s)))

// Tricks the compiler into thinking a variable is used
// We name this like a macro, even though it isn't, because it operates like one
template<class T> void FORCE_USED( const T& ) { }

// Marks a struct/class as packed
#define PACKED __attribute__((packed))

// Aligns a variable to the maximum useful alignment for variables of the same size
#define ALIGNED __attribute__((aligned))

// Specifies a specific alignment for a variable
#define ALIGN(n) __attribute__((aligned (n)))

// Marks a function as not returning
#define NO_RETURN __attribute__((noreturn))

// Marks a location as unreachable
// Compiler is free to optimize the code assuming that control will never reach the marked point
// as doing so would be undefined behavior
#define UNREACHABLE() __builtin_unreachable()

// Disable instrumentation for a function
#define NO_INSTRUMENT __attribute__((no_instrument_function))

// Declares a label that has local visibilty
#define LOCAL_LABEL(_name) \
    __label__ _name

// Helpers for proper GCC pragmas
#define PRAGMA_SAVE_WARNINGS()           _Pragma("GCC diagnostic push")
#define PRAGMA_DISABLE_WARNING(_flag)    _Pragma(QUOTE(GCC diagnostic ignored _flag))
#define PRAGMA_RESTORE_WARNINGS()        _Pragma("GCC diagnostic pop")

// Check if an expression is a compile-time constant
#define IS_KNOWN_CONSTANT(expr) __builtin_constant_p(expr)

// This takes advantage of the constant expression checking behavior of __builtin_constant_p()
#define CONSTEXPR_POINTER(_type, _addr) \
  __builtin_constant_p((_type *const) _addr) ? (_type *const) _addr : (_type *const) _addr

// Create a complete GCC version number as an integer
// Example: GCC 4.9.0 => 40900
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)


// Print compile time messages that are not warnings
#define _PRAGMA(x) _Pragma (#x)
#define COMPILE_MESSAGE(x) _PRAGMA(message (#x))
#define TODO(x) COMPILE_MESSAGE("TODO: " #x)


#else // __GNUC__

// This is temporary
#error "Unsupported compiler"

#endif // __GNUC__
