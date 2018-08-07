
#include "base/bits.h"
#include "base/types.h"
#include "catch2/catch.hpp"

#include <iostream>

using namespace estp;
using namespace std;

TEST_CASE( "Create 8-bit masks", "[bits]" ) {

	REQUIRE( uint8_t{0x01} == bitmask<uint8_t>(Msb{0}) );
	REQUIRE( uint8_t{0x0F} == bitmask<uint8_t>(Msb{3}) );
	REQUIRE( uint8_t{0x1F} == bitmask<uint8_t>(Msb{4}) );
	REQUIRE( uint8_t{0xFF} == bitmask<uint8_t>(Msb{7}) );

	REQUIRE( uint8_t{0xFF} == bitmask<uint8_t>(Lsb{0}) );
	REQUIRE( uint8_t{0xF8} == bitmask<uint8_t>(Lsb{3}) );
	REQUIRE( uint8_t{0xF0} == bitmask<uint8_t>(Lsb{4}) );
	REQUIRE( uint8_t{0x80} == bitmask<uint8_t>(Lsb{7}) );

	REQUIRE( uint8_t{0x01} == bitmask<uint8_t>(Lsb{0}, Msb{0}) );
	REQUIRE( uint8_t{0x03} == bitmask<uint8_t>(Lsb{0}, Msb{1}) );
	REQUIRE( uint8_t{0xFF} == bitmask<uint8_t>(Lsb{0}, Msb{7}) );
	REQUIRE( uint8_t{0x3C} == bitmask<uint8_t>(Lsb{2}, Msb{5}) );
	REQUIRE( uint8_t{0x20} == bitmask<uint8_t>(Lsb{5}, Msb{5}) );
	REQUIRE( uint8_t{0x60} == bitmask<uint8_t>(Lsb{5}, Msb{6}) );
	REQUIRE( uint8_t{0xE0} == bitmask<uint8_t>(Lsb{5}, Msb{7}) );

	REQUIRE( uint8_t{0x01} == bitmask<uint8_t>(Msb{0}, Lsb{0}) );
	REQUIRE( uint8_t{0x03} == bitmask<uint8_t>(Msb{1}, Lsb{0}) );
	REQUIRE( uint8_t{0xFF} == bitmask<uint8_t>(Msb{7}, Lsb{0}) );
	REQUIRE( uint8_t{0x3C} == bitmask<uint8_t>(Msb{5}, Lsb{2}) );
	REQUIRE( uint8_t{0x20} == bitmask<uint8_t>(Msb{5}, Lsb{5}) );
	REQUIRE( uint8_t{0x60} == bitmask<uint8_t>(Msb{6}, Lsb{5}) );
	REQUIRE( uint8_t{0xE0} == bitmask<uint8_t>(Msb{7}, Lsb{5}) );

	REQUIRE( uint8_t{0x00} == bitmask<uint8_t>(Lsb{0}, Width{0}) );
	REQUIRE( uint8_t{0x01} == bitmask<uint8_t>(Lsb{0}, Width{1}) );
	REQUIRE( uint8_t{0x7F} == bitmask<uint8_t>(Lsb{0}, Width{7}) );
	REQUIRE( uint8_t{0xFF} == bitmask<uint8_t>(Lsb{0}, Width{8}) );

	REQUIRE( uint8_t{0x1C} == bitmask<uint8_t>(Lsb{2}, Width{3}) );
	REQUIRE( uint8_t{0x3C} == bitmask<uint8_t>(Lsb{2}, Width{4}) );
	REQUIRE( uint8_t{0x7C} == bitmask<uint8_t>(Lsb{2}, Width{5}) );
	REQUIRE( uint8_t{0xFC} == bitmask<uint8_t>(Lsb{2}, Width{6}) );

	REQUIRE( uint8_t{0x00} == bitmask<uint8_t>(Msb{7}, Width{0}) );
	REQUIRE( uint8_t{0x80} == bitmask<uint8_t>(Msb{7}, Width{1}) );
	REQUIRE( uint8_t{0xFE} == bitmask<uint8_t>(Msb{7}, Width{7}) );
	REQUIRE( uint8_t{0xFF} == bitmask<uint8_t>(Msb{7}, Width{8}) );

	REQUIRE( uint8_t{0x38} == bitmask<uint8_t>(Msb{5}, Width{3}) );
	REQUIRE( uint8_t{0x3C} == bitmask<uint8_t>(Msb{5}, Width{4}) );
	REQUIRE( uint8_t{0x3E} == bitmask<uint8_t>(Msb{5}, Width{5}) );
	REQUIRE( uint8_t{0x3F} == bitmask<uint8_t>(Msb{5}, Width{6}) );

}

TEST_CASE( "Create 32-bit masks", "[bits]" ) {

	REQUIRE( uint32_t{0x00000001} == bitmask<uint32_t>(Msb{0}) );
	REQUIRE( uint32_t{0x0000000F} == bitmask<uint32_t>(Msb{3}) );
	REQUIRE( uint32_t{0x00007FFF} == bitmask<uint32_t>(Msb{14}) );
	REQUIRE( uint32_t{0x0FFFFFFF} == bitmask<uint32_t>(Msb{27}) );
	REQUIRE( uint32_t{0xFFFFFFFF} == bitmask<uint32_t>(Msb{31}) );

	REQUIRE( uint32_t{0xFFFFFFFF} == bitmask<uint32_t>(Lsb{0}) );
	REQUIRE( uint32_t{0xFFFFFFF8} == bitmask<uint32_t>(Lsb{3}) );
	REQUIRE( uint32_t{0xFFFFFFF0} == bitmask<uint32_t>(Lsb{4}) );
	REQUIRE( uint32_t{0xFFFE0000} == bitmask<uint32_t>(Lsb{17}) );

	REQUIRE( uint32_t{0x00000001} == bitmask<uint32_t>(Lsb{0}, Msb{0}) );
	REQUIRE( uint32_t{0x00000003} == bitmask<uint32_t>(Lsb{0}, Msb{1}) );
	REQUIRE( uint32_t{0xFFFFFFFF} == bitmask<uint32_t>(Lsb{0}, Msb{31}) );
	REQUIRE( uint32_t{0x03FFE000} == bitmask<uint32_t>(Lsb{13}, Msb{25}) );
	REQUIRE( uint32_t{0x07FFE000} == bitmask<uint32_t>(Lsb{13}, Msb{26}) );
	REQUIRE( uint32_t{0x0FFFE000} == bitmask<uint32_t>(Lsb{13}, Msb{27}) );

	REQUIRE( uint32_t{0x00000001} == bitmask<uint32_t>(Msb{0}, Lsb{0}) );
	REQUIRE( uint32_t{0x00000003} == bitmask<uint32_t>(Msb{1}, Lsb{0}) );
	REQUIRE( uint32_t{0xFFFFFFFF} == bitmask<uint32_t>(Msb{31}, Lsb{0}) );
	REQUIRE( uint32_t{0x03FFE000} == bitmask<uint32_t>(Msb{25}, Lsb{13}) );
	REQUIRE( uint32_t{0x07FFE000} == bitmask<uint32_t>(Msb{26}, Lsb{13}) );
	REQUIRE( uint32_t{0x0FFFE000} == bitmask<uint32_t>(Msb{27}, Lsb{13}) );

	REQUIRE( uint32_t{0x00000000} == bitmask<uint32_t>(Lsb{0}, Width{0}) );
	REQUIRE( uint32_t{0x00000001} == bitmask<uint32_t>(Lsb{0}, Width{1}) );
	REQUIRE( uint32_t{0x0001FFFF} == bitmask<uint32_t>(Lsb{0}, Width{17}) );
	REQUIRE( uint32_t{0x07FFFFFF} == bitmask<uint32_t>(Lsb{0}, Width{27}) );
	REQUIRE( uint32_t{0xFFFFFFFF} == bitmask<uint32_t>(Lsb{0}, Width{32}) );

	REQUIRE( uint32_t{0x1C000000} == bitmask<uint32_t>(Lsb{26}, Width{3}) );
	REQUIRE( uint32_t{0x3C000000} == bitmask<uint32_t>(Lsb{26}, Width{4}) );
	REQUIRE( uint32_t{0x7C000000} == bitmask<uint32_t>(Lsb{26}, Width{5}) );
	REQUIRE( uint32_t{0xFC000000} == bitmask<uint32_t>(Lsb{26}, Width{6}) );

	REQUIRE( uint32_t{0x00000000} == bitmask<uint32_t>(Msb{31}, Width{0}) );
	REQUIRE( uint32_t{0x80000000} == bitmask<uint32_t>(Msb{31}, Width{1}) );
	REQUIRE( uint32_t{0xFE000000} == bitmask<uint32_t>(Msb{31}, Width{7}) );
	REQUIRE( uint32_t{0xFFFFFFFF} == bitmask<uint32_t>(Msb{31}, Width{32}) );

	REQUIRE( uint32_t{0x00070000} == bitmask<uint32_t>(Msb{18}, Width{3}) );
	REQUIRE( uint32_t{0x00078000} == bitmask<uint32_t>(Msb{18}, Width{4}) );
	REQUIRE( uint32_t{0x0007C000} == bitmask<uint32_t>(Msb{18}, Width{5}) );
	REQUIRE( uint32_t{0x0007E000} == bitmask<uint32_t>(Msb{18}, Width{6}) );
	REQUIRE( uint32_t{0x0007FFFF} == bitmask<uint32_t>(Msb{18}, Width{19}) );

}

TEST_CASE( "Count trailing zeros (unsigned char)", "[bits]" ) {
	REQUIRE( -1 == ctz(static_cast<unsigned char>(0)) );

	for(unsigned i=0; i<8; ++i) {
		REQUIRE( i == ctz(static_cast<unsigned char>(1U<<i)) );
	}
}

TEST_CASE( "Count trailing zeros (unsigned short)", "[bits]" ) {
	REQUIRE( -1 == ctz(static_cast<unsigned short>(0)) );

	for(unsigned i=0; i<16; ++i) {
		REQUIRE( i == ctz(static_cast<unsigned short>(1U<<i)) );
	}
}

TEST_CASE( "Count trailing zeros (unsigned int)", "[bits]" ) {
	REQUIRE( -1 == ctz(static_cast<unsigned int>(0)) );

	for(unsigned i=0; i<bitsize<unsigned int>(); ++i) {
		REQUIRE( i == ctz(static_cast<unsigned int>(1U<<i)) );
	}
}

TEST_CASE( "Count trailing zeros (unsigned long)", "[bits]" ) {
	REQUIRE( -1 == ctz(static_cast<unsigned long>(0)) );

	for(unsigned i=0; i<bitsize<unsigned long>(); ++i) {
		REQUIRE( i == ctz(static_cast<unsigned long>(1UL<<i)) );
	}
}

TEST_CASE( "Count trailing zeros (unsigned long long)", "[bits]" ) {
	REQUIRE( -1 == ctz(static_cast<unsigned long long>(0)) );

	for(unsigned i=0; i<bitsize<unsigned long long>(); ++i) {
		REQUIRE( i == ctz(static_cast<unsigned long long>(1ULL<<i)) );
	}
}

TEST_CASE( "Count leading zeros (unsigned char)", "[bits]" ) {
	REQUIRE( -1 == clz(static_cast<unsigned char>(0)) );

	for(unsigned i=0; i<8; ++i) {
		REQUIRE( (8 - i - 1) == clz(static_cast<unsigned char>(1U<<i)) );
	}
}

TEST_CASE( "Count leading zeros (unsigned short)", "[bits]" ) {
	REQUIRE( -1 == clz(static_cast<unsigned short>(0)) );

	for(unsigned i=0; i<16; ++i) {
		REQUIRE( (16 - i - 1) == clz(static_cast<unsigned short>(1U<<i)) );
	}
}

TEST_CASE( "Count leading zeros (unsigned int)", "[bits]" ) {
	REQUIRE( -1 == clz(static_cast<unsigned int>(0)) );

	for(unsigned i=0; i<bitsize<unsigned int>(); ++i) {
		REQUIRE( (bitsize<unsigned int>() - i - 1) ==
				clz(static_cast<unsigned int>(1U<<i)) );
	}
}

TEST_CASE( "Count leading zeros (unsigned long)", "[bits]" ) {
	REQUIRE( -1 == clz(static_cast<unsigned long>(0)) );

	for(unsigned i=0; i<bitsize<unsigned long>(); ++i) {
		REQUIRE( (bitsize<unsigned long>() - i - 1) ==
				clz(static_cast<unsigned long>(1UL<<i)) );
	}
}

TEST_CASE( "Count leading zeros (unsigned long long)", "[bits]" ) {
	REQUIRE( -1 == clz(static_cast<unsigned long long>(0)) );

	for(unsigned i=0; i<bitsize<unsigned long long>(); ++i) {
		REQUIRE( (bitsize<unsigned long long>() - i - 1) ==
				clz(static_cast<unsigned long long>(1ULL<<i)) );
	}
}

TEST_CASE( "FindMsb (unsigned char)", "[bits]" ) {
	REQUIRE( -1 == FindMsb(static_cast<unsigned char>(0)) );

	for(unsigned i=0; i<8; ++i) {
		REQUIRE( i == FindMsb(static_cast<unsigned char>(1U<<i)) );
	}
}

TEST_CASE( "FindMsb (unsigned short)", "[bits]" ) {
	REQUIRE( -1 == FindMsb(static_cast<unsigned short>(0)) );

	for(unsigned i=0; i<16; ++i) {
		REQUIRE( i == FindMsb(static_cast<unsigned short>(1U<<i)) );
	}
}

TEST_CASE( "FindMsb (unsigned int)", "[bits]" ) {
	REQUIRE( -1 == FindMsb(static_cast<unsigned int>(0)) );

	for(unsigned i=0; i<bitsize<unsigned int>(); ++i) {
		REQUIRE( i == FindMsb(static_cast<unsigned int>(1U<<i)) );
	}
}

TEST_CASE( "FindMsb (unsigned long)", "[bits]" ) {
	REQUIRE( -1 == FindMsb(static_cast<unsigned long>(0)) );

	for(unsigned i=0; i<bitsize<unsigned long>(); ++i) {
		REQUIRE( i == FindMsb(static_cast<unsigned long>(1UL<<i)) );
	}
}

TEST_CASE( "FindMsb (unsigned long long)", "[bits]" ) {
	REQUIRE( -1 == FindMsb(static_cast<unsigned long long>(0)) );

	for(unsigned i=0; i<bitsize<unsigned long long>(); ++i) {
		REQUIRE( i == FindMsb(static_cast<unsigned long long>(1ULL<<i)) );
	}
}

