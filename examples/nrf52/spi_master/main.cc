/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be
 * reverse engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include <string.h>

#include "app_error.h"
#include "app_util_platform.h"
#include "boards.h"
#include "nrf_delay.h"
#include "nrf_drv_spi.h"
#include "nrf_gpio.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "estp/data/color.hh"
#include "estp/data/span.hh"
#include "estp/driver/apa102.hh"

#define SPI_INSTANCE 0                                               /**< SPI instance index. */
static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE); /**< SPI instance. */
static volatile bool spi_xfer_done; /**< Flag used to indicate that SPI instance
                                                                           completed
                                       the transfer. */

/**
 * @brief SPI user event handler.
 * @param event
 */
void spi_event_handler(nrf_drv_spi_evt_t const* p_event, void* p_context) {
    spi_xfer_done = true;
    NRF_LOG_INFO("Transfer completed.");
#if 0
    if (m_rx_buf[0] != 0)
    {
        NRF_LOG_INFO(" Received:");
        NRF_LOG_HEXDUMP_INFO(m_rx_buf, strlen((const char *)m_rx_buf));
    }
#endif
}

using namespace estp;

constexpr Index kLedRows = 8;
constexpr Index kLedCols = 8;
constexpr Index kLedCount = kLedRows * kLedCols;

Apa102 leds[kLedRows][kLedCols];

constexpr Index kPaletteSize = 6;
constexpr RgbColor8 kPalette[kPaletteSize] = {
    {0,0,32},
    {0,16,16},
    {0,16,0},
    {16,16,0},
    {16,0,0},
    {16,0,32}
};

RgbColor8 const& NextColor() {
    static Index index = 0;
    auto curr = index;
    NRF_LOG_INFO("Color index %i", index);
    if(++index == kPaletteSize) {
        index = 0;
    }
    return kPalette[curr];
}

struct Coordinate {
    Index row{0};
    Index col{0};
};

Coordinate NextPerimeterCoord(Coordinate const current) {
    constexpr auto kLastCol = kLedCols - 1;
    constexpr auto kLastRow = kLedRows - 1;

    if (0 == current.row) {
        if (current.col > 0) {
            return {0, current.col-1};
        }
    }
    if (kLastRow == current.row) {
        if (current.col != kLastCol) {
            return {kLastRow, current.col+1};
        }
    }
    if (0 == current.col) {
        if (current.row < kLastRow) {
            return {current.row+1, 0};
        }
    }
    if (kLastCol == current.col) {
        if (current.row > 0) {
            return {current.row-1, kLastCol};
        }
    }
    ASSERT(false);
    return {0,0};
}

void redraw() {
    static uint8_t buf[4];

    std::memcpy(buf, estp::Apa102::kLeader, 4);
    APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, buf, 4, NULL, 0));

    for(int r=0; r<kLedRows; r++) {
        APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, reinterpret_cast<uint8_t*>(&leds[r][0]),
            sizeof(Apa102)*kLedCols, NULL, 0));
    }

    std::memcpy(buf, estp::Apa102::kTrailer, 4);
    APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, buf, 4, NULL, 0));
}


int main(void) {
    bsp_board_init(BSP_INIT_LEDS);

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
    spi_config.ss_pin = NRF_DRV_SPI_PIN_NOT_USED;    // SPI_SS_PIN;
    spi_config.miso_pin = NRF_DRV_SPI_PIN_NOT_USED;  // SPI_MISO_PIN;
    spi_config.mosi_pin = 22;                        // SPI_MOSI_PIN;
    spi_config.sck_pin = 16;                         // SPI_SCK_PIN;

    // APP_ERROR_CHECK(nrf_drv_spi_init(&spi, &spi_config, spi_event_handler, NULL));
    APP_ERROR_CHECK(nrf_drv_spi_init(&spi, &spi_config, NULL, NULL));

    NRF_LOG_INFO("SPI example started.");
    redraw();

    constexpr uint32_t kDelayMs = 50;
    auto color = NextColor();
    Coordinate head{0,0};
    for(int i=0; i<12; i++) {
        // Give head a "head" start....
        head = NextPerimeterCoord(head);
    }
    Coordinate tail{0,0};
    for (;;) {
        NRF_LOG_INFO("(%i, %i) ", head.row, head.col);
        if ((0 == head.row) && (0 == head.col)) {
            color = NextColor();
        }
        NRF_LOG_FLUSH();
        leds[head.row][head.col].SetScale(8).SetColor(color);
        leds[tail.row][tail.col].SetOff();
        redraw();
        nrf_delay_ms(kDelayMs);
        head = NextPerimeterCoord(head);
        tail = NextPerimeterCoord(tail);
    }
}
