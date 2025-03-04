#include "crc.h"

/// <summary>
/// 默认CRC配置
/// </summary>
CrcInfoType crc[] =
{
    {.Name = "CRC4/ITU",    .Width = 4,  .Poly = 0x03,       .Init = 0x00,       .XorOut = 0x00,       .RefIn = true,  .RefOut = true  },
    {.Name = "CRC8",        .Width = 8,  .Poly = 0x07,       .Init = 0x00,       .XorOut = 0x00,       .RefIn = false, .RefOut = false },
    {.Name = "CRC16/CCITT", .Width = 16, .Poly = 0x1021,     .Init = 0x0000,     .XorOut = 0x0000,     .RefIn = true,  .RefOut = true  },
    {.Name = "CRC32",       .Width = 32, .Poly = 0x04C11DB7, .Init = 0xFFFFFFFF, .XorOut = 0xFFFFFFFF, .RefIn = true,  .RefOut = true  },
    {.Name = "CRC16_7606",  .Width = 16, .Poly = 0x755B,     .Init = 0x0000,     .XorOut = 0x0000,     .RefIn = false, .RefOut = false },
};

uint8_t crc_bytes_a[] = { 0x06, 0x4E };
crc_word_t crc_results_a[] =
{
    0x04,
    0x93,
    0xFFAA,
    0x86E7D9EE,
    0x2137
};

// 48 65 6c 6c 6f 2c 43 61 72 72 6f 74 43 72 63 21 
uint8_t crc_bytes_b[] = { 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x43, 0x61, 0x72, 0x72, 0x6f, 0x74, 0x43, 0x72, 0x63, 0x21 };
crc_word_t crc_results_b[] =
{
    0x02,
    0x05,
    0xB4EB,
    0xA6C4ACBC,
    0xC1BC
};

int main()
{

    for (int i = 0; i < sizeof(crc_results_a) / sizeof(crc_word_t); i++)
    {
        crc_word_t crc_result = CrcCalculate(&crc[i], crc_bytes_a, sizeof(crc_bytes_a));
        PRINTF_DBG("[%s] %s = 0x%X\r\n", crc_result == crc_results_a[i] ? "PASS" : "FAIL", crc[i].Name, crc_result);
    }
    for (int i = 0; i < sizeof(crc_results_b) / sizeof(crc_word_t); i++)
    {
        crc_word_t crc_result = CrcCalculate(&crc[i], crc_bytes_b, sizeof(crc_bytes_b));
        PRINTF_DBG("[%s] %s = 0x%X\r\n", crc_result == crc_results_b[i] ? "PASS" : "FAIL", crc[i].Name, crc_result);
    }

    return 0;
}

