#include "estp/data/atomic_flags.hh"

#include "catch2/catch.hpp"

using namespace estp;

enum class Letters : unsigned {
    A = 0, B, C, D, E, F, G, H
};

using Flags8 = AtomicFlags<uint8_t, Letters>;
using Flags16 = AtomicFlags<uint16_t, Letters>;

TEST_CASE("AtomicFlags: Construction") {
    SECTION("Empty set") {
        auto f8 = Flags8{};
        REQUIRE(0 == f8.Load().bits());

        auto f16 = Flags16{};
        REQUIRE(0 == f16.Load().bits());
    }

    SECTION("From raw value") {
        auto const kF8 = Flags8::from_bits(0xDE);
        REQUIRE(0xDE == kF8.Load().bits());

        auto const kF16 = Flags16::from_bits(0xBEEF);
        REQUIRE(0xBEEF == kF16.Load().bits());
    }

    SECTION("From flags") {
        auto const kA = Flags8{Letters::A};
        REQUIRE(0x01 == kA.Load().bits());

        auto const kCada = Flags8{Letters::C, Letters::A, Letters::D, Letters::A};
        REQUIRE(0b00001101 == kCada.Load().bits());

        auto const kDaca = Flags8{Letters::D, Letters::A, Letters::C, Letters::A};
        REQUIRE(0b00001101 == kDaca.Load().bits());

        auto const kE = Flags16{Letters::E};
        REQUIRE(0b00000000'00010000 == kE.Load().bits());

        auto const kHead = Flags16{Letters::H, Letters::E, Letters::A, Letters::D};
        REQUIRE(0b00000000'10011001 == kHead.Load().bits());
    }
}
TEST_CASE("AtomicFlags: Manipulation") {
    SECTION("Test, TestAny, TestAll, Any, None") {
        auto const kCad = Flags8{Letters::C, Letters::A, Letters::D};

        REQUIRE(kCad.Test(Letters::A));
        REQUIRE(!kCad.Test(Letters::B));
        REQUIRE(kCad.Test(Letters::C));
        REQUIRE(kCad.Test(Letters::D));
        REQUIRE(!kCad.Test(Letters::E));
        REQUIRE(!kCad.Test(Letters::F));
        REQUIRE(!kCad.Test(Letters::G));
        REQUIRE(!kCad.Test(Letters::H));

        auto const kHag = Flags8{Letters::H, Letters::A, Letters::G};
        REQUIRE(kCad.TestAny(kHag));

        auto const kBeef = Flags8{Letters::B, Letters::E, Letters::E, Letters::F};
        REQUIRE(!kCad.TestAny(kBeef));

        REQUIRE(kCad.TestAll({Letters::C, Letters::A}));

        REQUIRE(!kCad.TestAll({Letters::C, Letters::A, Letters::F}));

        auto kHead = Flags16{Letters::H, Letters::E, Letters::A, Letters::D};
        REQUIRE(kHead.Test(Letters::A));
        REQUIRE(!kHead.Test(Letters::B));
        REQUIRE(!kHead.Test(Letters::C));
        REQUIRE(kHead.Test(Letters::D));
        REQUIRE(kHead.Test(Letters::E));
        REQUIRE(!kHead.Test(Letters::F));
        REQUIRE(!kHead.Test(Letters::G));
        REQUIRE(kHead.Test(Letters::H));

        REQUIRE(Flags8{}.None());
        REQUIRE(!kCad.None());

        REQUIRE(!Flags8{}.Any());
        REQUIRE(kCad.Any());

    }

    SECTION("Set, Clear") {
        auto flags = Flags8{Letters::C, Letters::A, Letters::D};

        flags.Set(Letters::H);
        REQUIRE(flags == Flags8{Letters::C, Letters::A, Letters::D, Letters::H});

        flags.Set(Letters::A);
        REQUIRE(flags == Flags8{Letters::C, Letters::A, Letters::D, Letters::H});

        flags.Set(Letters::F, Letters::G, Letters::D);
        REQUIRE(flags == Flags8{Letters::C, Letters::A, Letters::D, Letters::H,
            Letters::F, Letters::G});

        flags.Clear(Letters::F, Letters::G);
        REQUIRE(flags == Flags8{Letters::C, Letters::A, Letters::D, Letters::H});

        flags.Clear(Letters::B);
        REQUIRE(flags == Flags8{Letters::C, Letters::A, Letters::D, Letters::H});

        flags.Clear(Letters::H);
        REQUIRE(flags == Flags8{Letters::C, Letters::A, Letters::D});
    }

    SECTION("TestAndSet, TestAndClear") {
        auto flags = Flags8{Letters::C, Letters::A, Letters::D};

        REQUIRE(flags.TestAndSet(Letters::H));
        REQUIRE(flags == Flags8{Letters::C, Letters::A, Letters::D, Letters::H});

        REQUIRE(!flags.TestAndSet(Letters::A));
        REQUIRE(flags == Flags8{Letters::C, Letters::A, Letters::D, Letters::H});

        REQUIRE(flags.TestAndSetAll(Letters::F, Letters::G));
        REQUIRE(flags ==
            Flags8{Letters::C, Letters::A, Letters::D, Letters::H, Letters::F, Letters::G});

        REQUIRE(!flags.TestAndSetAny(Letters::C, Letters::A));
        REQUIRE(flags ==
            Flags8{Letters::C, Letters::A, Letters::D, Letters::H, Letters::F, Letters::G});

        REQUIRE(flags.TestAndClear(Letters::H));
        REQUIRE(flags == Flags8{Letters::C, Letters::A, Letters::D, Letters::F, Letters::G});

        REQUIRE(!flags.TestAndClear(Letters::B));
        REQUIRE(flags == Flags8{Letters::C, Letters::A, Letters::D, Letters::F, Letters::G});

        REQUIRE(flags.TestAndClearAll(Letters::F, Letters::G, Letters::D));
        REQUIRE(flags == Flags8{Letters::C, Letters::A});

        REQUIRE(flags.TestAndClearAny(Letters::B, Letters::A));
        REQUIRE(flags == Flags8{Letters::C});
    }
}
