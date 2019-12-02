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

#include "estp/data/color.h"
#include "estp/data/span.h"
#include "estp/driver/apa102.h"

#define SPI_INSTANCE 0                                               /**< SPI instance index. */
static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE); /**< SPI instance. */
static volatile bool spi_xfer_done; /**< Flag used to indicate that SPI instance
                                                                           completed
                                       the transfer. */
#if 0
static uint8_t header[] = {0, 0, 0, 0};
static uint8_t blue[] = {0xE3, 0xFF, 0x00, 0x00};
static uint8_t green[] = {0xE1, 0x00, 0x7F, 0x00};
static uint8_t red[] = {0xE1, 0x00, 0x00, 0xFF};
static uint8_t off[] = {0xE0, 0, 0, 0};
#endif
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

constexpr auto kLedCount = 64;
estp::Apa102 leds[kLedCount];

void redraw() {
    static uint8_t buf[4];

    std::memcpy(buf, estp::Apa102::kLeader, 4);
    APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, buf, 4, NULL, 0));

    for(auto& led : leds) {
        led.SerializeInto(estp::Span{buf,4});
        APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, buf, 4, NULL, 0));
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
    // APP_ERROR_CHECK(nrf_drv_spi_init(&spi, &spi_config, spi_event_handler,
    // NULL));
    APP_ERROR_CHECK(nrf_drv_spi_init(&spi, &spi_config, NULL, NULL));

    NRF_LOG_INFO("SPI example started.");

    uint8_t buf[4];
    std::memcpy(buf, estp::Apa102::kLeader,4);
    APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, buf, 4, NULL, 0));
    estp::Apa102::kOff.SerializeInto(estp::Span{buf,4});
    for (int i = 0; i < 65; i++) {
        APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, buf, 4, NULL, 0));
    }
    std::memcpy(buf, estp::Apa102::kTrailer,4);
    APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, buf, 4, NULL, 0));

    //leds[0] = estp::RgbColor8::kWhite;
    leds[1] = estp::RgbColor8{0,0,32};
    leds[2] = estp::RgbColor8{0,16,16};
    leds[3] = estp::RgbColor8{0,16,0};
    leds[4] = estp::RgbColor8{16,16,0};
    leds[5] = estp::RgbColor8{16,0,0};
    leds[6] = estp::RgbColor8{16,0,32};
    //leds[7] = estp::RgbColor8::kWhite;

    constexpr uint32_t kDelayMs = 50;
    for (;;) {
        NRF_LOG_INFO("====== Cycle ======");
        for(unsigned scale=0; scale<32; scale++) {
            for(auto& led : leds) {
                led.SetScale(scale);
            }
            redraw();
            bsp_board_led_invert(BSP_BOARD_LED_0);
            NRF_LOG_INFO("Scale: 0x%02X", scale);
            uint8_t check = *reinterpret_cast<uint8_t *>(&leds[4]);
            NRF_LOG_INFO("LED control: 0x%02X", check);
            NRF_LOG_FLUSH();
            nrf_delay_ms(kDelayMs);
        }
        for(unsigned scale=30; scale!=(0u-1u); scale--) {
            for(auto& led : leds) {
                led.SetScale(scale);
            }
            redraw();
            bsp_board_led_invert(BSP_BOARD_LED_0);
            NRF_LOG_INFO("Scale: 0x%02X", scale);
            uint8_t check = *reinterpret_cast<uint8_t *>(&leds[4]);
            NRF_LOG_INFO("LED control: 0x%02X", check);
            nrf_delay_ms(kDelayMs);
            NRF_LOG_FLUSH();
        }
    }
}
