Estoppel TODO list and idea board





C++17 Features
- Replace compiler-specific attributes with standard ones (e.g. [[nodiscard]], etc)
- Replace SFINAE templates with constexpr if
- Create global vars as inline constexpr values
- Improve assert handler
- Look for improvements for pack-expansion handling (no recursive templates)
- Use template constructor argument deduction for templated classes
- Use nested namespace declarations
- Use init statements in if/switch expressions as possible
- Switch to string_view
- Use structured bindings for multiple return items
- Consider use of std::optional/std::any/std::variant (use std::get_if for conditional retrival)
- Evaluate std::to_chars instead of format library

Misc fixes
- Change framework configuration scheme
- Change "app" concept


BVBE Missing Features list:
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

Display Driver:
- Framebuffer class to manage hardware device
- Frame class to implement memory abstraction/rotation via iterators or array notation
- Pixel/PackedPixel class to represent memory within a frame
- Canvas class to implement drawing functions


template<PixelFormat>
Frame {
	BitFieldArray pixels[]
	Size
	Origin
	MemoryOrder
	
	Pixel {
	}
	
	Canvas : public CanvasInterface {
	}
}

Canvas { virtual base class }


Events:

Event Queue provides simple insertion/removal at front or back

Actors derive from a base class that provides tie-in to framework
- Base class provides methods for 
	> posting events (async) to front or back of queue
	> notifying framework when actor event queue is not empty
	> immediately executing events
	> subscribing to events
	> deferring events
- Base class registers with framework on init
- Base class either is-a or has-a 'Agent' object for handling framework activity

Framework maintains shared state:
- Array of registered actors
- List of actors with pending events (bit array?)
- Main execution loop
- static Publish function for multicast events
- Framework produces/provides agents to actors upon registering

Event pool:
- Release/retain mechanisms for memory management
- Automatically populates pool reference field of Event

Events:
- Objects derived from Event base class
- Base class has members for pool reference
- Has Dispatch(BvbeActor &a) method for visitor pattern implementation (private, called by framework)
- 

