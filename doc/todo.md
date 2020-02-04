Estoppel TODO list and idea board

## Punchlist
- Create blinky app for STM32L4
- Migrate data structures
- Write test cases for data structures
- Create I/O abstraction


## Desired C++17 Features
- Replace compiler-specific attributes with standard ones (e.g. ([nodiscard]), etc)
- Replace SFINAE templates with constexpr if
- Create global vars as inline constexpr values
- Improve assert handler
    - Use constexpr construct for assert (example (<https://github.com/32bitmicro/newlib-nano-1.0/blob/master/newlib/libc/include/assert.h>))
    
- Look for improvements for pack-expansion handling (no recursive templates)
- Use template constructor argument deduction for templated classes
- Use nested namespace declarations
- Use init statements in if/switch expressions as possible
- Switch to string_view
- Use structured bindings for multiple return items
- Consider use of std::optional/std::any/std::variant (use std::get_if for conditional retrival)
- Evaluate std::to_chars instead of format library
- std::error_code (<https://en.cppreference.com/w/cpp/error/error_code)>
- std::void_t<...> for expression SFINAE
- Add class template argument deduction helpers
- Switch to std::span (<https://github.com/tcbrindle/span>)


## Misc improvements
- Use gsl::not_null<T> to eliminate null-pointer checks
    - Create special type for not_null<T*>
    - Create confirm_valid(T*) function to generate not_null values with assertion
    - Create assume_valid(T*) function to generate not_null without checking
- Use gsl::finally for close-of-scope actions
- Expects() and Ensures() from GSL for pre- and post-conditions
- gsl::zstring for null terminated strings (or gsl::czstring)
- Use gsl::owner<T> to convey pointer ownership
- Create special type a la owner<T> or unique_ptr<T> to denote global objects
    - Create release(T*) function to denote giving up of ownership
    - Create share(T&), loan(T&) to create Retained and Temp values
    - Create Retained<T&>, Temp<T&> to denote retained and temporary values, respectively
    - Create Unique<T*> to denote exclusive ownership
- Return tuple or struct instead of in-out parametrs
- Prefer in-class initializers
- Default arguments instead of overloaded methods
- Use std::optional instead of status value+inout parameter (or Expected<T>)
- Switch to preferring free functions over methods
- Use c++17 constexpr features
- switch to stream-like handling for I/O, logging, tracing (easily overridden)
- Consider user-defined literals for units
- Change framework configuration scheme
- Change "app" concept
- Use structs or enum classes for strong types
- Adopt fmt (<https://fmt.dev/latest/index.html>) (aka std::format) library
- Consider a tagged boolean type (example (<https://github.com/akrzemi1/explicit/blob/master/doc/tagged_bool.md>)
- Consider an explicit output parameter type (example (<https://github.com/akrzemi1/explicit/blob/master/include/ak_toolkit/out_param.hpp>)



## BVBE Missing Features
- Event framework
- Actor class
- Event-based shell
- Global codebase configuration scheme
- Implement better trace dump scheme (Segger SystemView)
- Better register access scheme
- Timer driver
- List data structure
- Peripheral hardware drivers (accel, flash)
- Interrupt-driven I2C
- Interrupt-driven SPI
- Peripheral clock manager (std::chrono)
- RTC driver
- Centralized timebase with adjustable frequency clock
- Asynchronous I/O
- USB driver
- Sleep controller
- NRF51 UART driver
- Protobuf support
- NVIC CMSIS replacement
- FPU CMSIS replacement
- Deadline stack?
- Persistent boot counter w/ linker support
- Reboot count/source in power-on message
- ASSERT logging to EEPROM
- Error/CHECK stack
- Shell command to retrieve failure logs
- Add git hash to build info
- Initialization control via HSM

## Code Ideas
### Configuration
Use template global variables to define an option and its default value
Use explicit instantiation to set the value for a given platform or application

Example:
driver.hh
```c++
namespace config {

template<typename APP>
constexpr int32_t kDriverBufferSize = 2048;

}

static byte buffer[::config::kDriverBufferSize<Application>];
```

application.hh
```c++
struct FizzBuzz {};

namespace config {
using Application = ::FizzBuzz;

template<>
constexpr int32_t kDriverBufferSize<::FizzBuzz> = 512;

}
```

### Events
Event Queue:
- provides simple insertion/removal at front or back
- statically sized

Event Pools:
- Provide dynamic memory service
- A type of actor that the framework knows how to handle
- Fixed number of event pools can be registered with framework (compile time definition)
- Just a glorified framework-aware block pool

Agents:
- Adapt the framework interface to a specific actor
- Converts event type and date (WHAT) into actor-specific action (HOW)

Actors:
- Register agent with framework
- Provide framework with memory for pending event queue and deferral queue

Framework:
- Array of registered actors (agent, event queue)
- Set of actors with pending events (bit array?)
- Main execution loop
- static Publish function for multicast events
- posting events (async) to front or back of queue
- immediately executing events
- subscribing to events
- deferring events

Events:
- Objects derived from Event base class
- Base class has members for event pool reference
- Should be trivially destructible

See also: http://makulik.github.io/sttcl/

### Type ID system
```c++
class type_id_t
{
    using sig = type_id_t();

    sig* id;
    type_id_t(sig* id) : id{id} {}

public:
    template<typename T>
    friend type_id_t type_id();

    bool operator==(type_id_t o) const { return id == o.id; }
    bool operator!=(type_id_t o) const { return id != o.id; }
};

template<typename T>
type_id_t type_id() { return &type_id<T>; }
```

## Resources

### modm
<http://modm.io/>

All resources are template classes (including pins)
Resources "assigned" at compile time by instantiating templates, e.g.
```c++
template<typename CFG=SpiConfigExemplar>
class Spi3 {
...
}

// Call example configuration classes 'exemplars'
struct Spi3Config {
    using Miso = typename Pin::PA3;
    using Mosi = typename Pin::PA4;
    using Sclk = typename Pin::PC1;
    constexpr auto kMode = SpiBase::Mode::kMode3;
}
using FlashSpi = Spi3<Spi3Config>;
using SpiFlashDevice = M25tSpiFlash<FlashSpi, Pin::PB4 /*chip-select*/>;
SpiFlashDevice ext_flash{};
```
Create HAL abstractions that allow for any possible combination of perhipherals + GPIO + clocks + IRQ + etc....
Then use a device-specific header to create aliases or instances of the specific combinations that are valid -> don't expect application code to match up peripherals to GPIOs

Classes for each resource (Pin, Controller, etc)
Platform files for each platform (aka PCB) that provides the following:
- Aliases for hardware-specific classes as generically named resources; e.g. Platform:I2cMaster0 = stm32l4::I2cMaster<0>
- Template classes for drivers with Resources passed as template arguments
Application config files that map resources exposed by platforms to resources required by application
```c++
alias Terminal = platform::DebugSerialPort
alias FlashMemory = platform::GigadeviceFlash;
```
Application config files also defines static resources such as buffers, scheduler, etc

### modm Register Abstraction
<https://github.com/modm-io/modm/blob/develop/src/modm/architecture/interface/register.hpp>

Uses enumerations to define bit fields
Provides overloaded operators for type-safe bit twiddling

### Variadic CRTP
<http://stevedewhurst.com/once_weakly/once-weakly20170328/once-weakly20170328.pdf>

Can be used to compose types statically with specific features or operations, such as restricted numeric types
Could be used to implement memory-mapped registers (read-only, write-only, etc)

### Boost Type.Erasure
<https://github.com/boost-experimental/te>

Experimental library for run-time polymorphism

### C++ Guideline Support Library (GSL)
[Single header implementation](https://github.com/martinmoene/gsl-lite)

### Expected<T>
<https://github.com/martinmoene/expected-lite>

Alternative to exceptions for error handling

### Statement Expressions
<https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html>

Feature of gcc and clang
Used for CHECK() macro

### Open source libraries
[Facebook Folly](https://github.com/facebook/folly/blob/master/folly/docs/Overview.md)
- Packed pointers

[Google Abseil](https://abseil.io/about/intro)

