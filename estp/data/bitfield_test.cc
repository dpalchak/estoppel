#include "estp/data/bitfield.h"

#include "catch2/catch.hpp"

#include <type_traits>

using namespace estp;

TEST_CASE("Basic bitfield operations") {
    SECTION("Bitfield8") {
        Bitfield8<Lsb{2},Width{5}> field8;
        field8 = 0b01101u;
        REQUIRE(0b01101u == field8());
        REQUIRE(0b01101u == static_cast<uint8_t>(field8));

        field8 = 0b11010110u;
        REQUIRE(0b10110u == field8());
        REQUIRE(0b10110u == static_cast<uint8_t>(field8));

        field8 = 0b11100000u;
        REQUIRE(0 == field8());
        REQUIRE(0 == static_cast<uint8_t>(field8));
    }

    SECTION("Bitfield32") {
        Bitfield32<Lsb{25},Width{6}> field32;
        field32 = 0b101101u;
        REQUIRE(0b101101u == field32());
        REQUIRE(0b101101u == static_cast<uint32_t>(field32));

        field32 = 0b11010110u;
        REQUIRE(0b000010110u == field32());
        REQUIRE(0b000010110u == static_cast<uint32_t>(field32));

        field32 = 0b11000000u;
        REQUIRE(0 == field32());
        REQUIRE(0 == static_cast<uint32_t>(field32));
    }
}

TEST_CASE("Multi-bitfield Union") {
    union {
        uint16_t word{0};
        Bitfield16<Lsb{ 0},Width{5}> blue;
        Bitfield16<Lsb{ 5},Width{6}> green;
        Bitfield16<Lsb{11},Width{5}> red;
        Bitfield16<Lsb{ 0},Width{8}> lower_byte;
        Bitfield16<Lsb{ 8},Width{8}> upper_byte;
    } color;

    color.red = 0b00111u;
    color.green = 0b101010u;
    color.blue = 0b10000u;
    REQUIRE(0b0011110101010000u == color.word);
    REQUIRE(0b00111u == color.red());
    REQUIRE(0b101010u == color.green());
    REQUIRE(0b10000u == color.blue());
    REQUIRE(0b01010000u == color.lower_byte());
    REQUIRE(0b00111101u == color.upper_byte());

    color.lower_byte = 0b00001111u;
    color.upper_byte = 0b10101010u;
    REQUIRE(0b1010101000001111u == color.word);
    REQUIRE(0b10101u == color.red());
    REQUIRE(0b010000u == color.green());
    REQUIRE(0b01111u == color.blue());
    REQUIRE(0b00001111u == color.lower_byte());
    REQUIRE(0b10101010u == color.upper_byte());

    color.word = 0b0110011001100110u;
    REQUIRE(0b01100u == color.red());
    REQUIRE(0b110011u == color.green());
    REQUIRE(0b00110u == color.blue());
    REQUIRE(0b01100110u == color.lower_byte());
    REQUIRE(0b01100110u == color.upper_byte());
}

TEST_CASE("Bitfield with enumeration") {
    enum class Edge : uint32_t {
        kNone = 0b00,
        kRising = 0b01,
        kFalling = 0b10,
        kBoth = 0b11
    };

    union {
        uint32_t word{0};
        Bitfield<Lsb(0),Width(2),Edge> pin0;
        Bitfield<Lsb(2),Width(2),Edge> pin1;
        Bitfield<Lsb(4),Width(2),Edge> pin2;
    } irq_edge;

    REQUIRE(Edge::kNone == irq_edge.pin0());
    REQUIRE(Edge::kNone == irq_edge.pin1());
    REQUIRE(Edge::kNone == irq_edge.pin2());

    irq_edge.pin0 = Edge::kRising;
    irq_edge.pin1 = Edge::kFalling;
    irq_edge.pin2 = Edge::kBoth;

    REQUIRE(Edge::kRising == irq_edge.pin0());
    REQUIRE(Edge::kFalling == irq_edge.pin1());
    REQUIRE(Edge::kBoth == irq_edge.pin2());
    REQUIRE(0b00111001 == irq_edge.word);

}
