#include "crc.h"

/// <summary>
/// 默认CRC配置
/// </summary>
CrcInfoType crc[] =
{
    {.Name = "CRC4",       .Width = 4,  .Poly = 0x03,       .Init = 0x00,       .XorOut = 0x00,       .RefIn = true,  .RefOut = true  },
    {.Name = "CRC8",       .Width = 8,  .Poly = 0x07,       .Init = 0x00,       .XorOut = 0x00,       .RefIn = false, .RefOut = false },
    {.Name = "CRC16",      .Width = 16, .Poly = 0x1021,     .Init = 0x0000,     .XorOut = 0x0000,     .RefIn = true,  .RefOut = true  },
    {.Name = "CRC32",      .Width = 32, .Poly = 0x04C11DB7, .Init = 0xFFFFFFFF, .XorOut = 0xFFFFFFFF, .RefIn = true,  .RefOut = true  },
    {.Name = "CRC16_7606", .Width = 16, .Poly = 0x755B,     .Init = 0x0000,     .XorOut = 0x0000,     .RefIn = false, .RefOut = false },
};

int main()
{
    uint8_t str[] = { 0x06, 0x4E };
    crc_word_t crc_result;

    //CrcUpdateTable(&crc[3]);
    crc_result = CrcCalculate(&crc[0], str, sizeof(str));
    PRINTF_DBG("CRC = 0x%X\r\n", crc_result);
    crc_result = CrcCalculate(&crc[1], str, sizeof(str));
    PRINTF_DBG("CRC = 0x%X\r\n", crc_result);
    crc_result = CrcCalculate(&crc[2], str, sizeof(str));
    PRINTF_DBG("CRC = 0x%X\r\n", crc_result);
    crc_result = CrcCalculate(&crc[3], str, sizeof(str));
    PRINTF_DBG("CRC = 0x%X\r\n", crc_result);
    return 0;
}

