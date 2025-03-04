#include "crc.h"


/// <summary>
/// 位反转函数,将高位和低位数据顺序反过来
/// </summary>
/// <param name="inVal">反转前数据</param>
/// <param name="width">反转位数</param>
/// <returns></returns>
crc_word_t BitsReverse(crc_word_t inVal, uint8_t width)
{
    crc_word_t outVal = 0;

    for (uint8_t i = 0; i < width; i++)
    {
        if (inVal & ((crc_word_t)1 << i))
            outVal |= (crc_word_t)1 << (width - 1 - i);
    }
    return outVal;
}

/// <summary>
/// 更新CRC查表数组
/// </summary>
/// <param name="crc">CRC结构</param>
void CrcUpdateTable(CrcInfoType* crc)
{
    crc_word_t validBits = (~((crc_word_t)0) >> (sizeof(crc_word_t) * 8 - crc->Width));
    crc_word_t poly = crc->Poly;
    crc_word_t value;
    crc_word_t bit;
    uint8_t j;

    if (crc->RefIn)
    {
        poly = BitsReverse(poly, crc->Width);
        for (crc_word_t i = 0; i < 256; i++)
        {
            value = i;
            for (j = 0; j < 8; j++)
            {
                if (value & 1)
                {
                    value = (value >> 1) ^ poly;
                }
                else
                {
                    value >>= 1;
                }
            }
            crc->Table[i] = value & validBits;
        }
    }
    else
    {
        poly = (crc->Width < 8) ? (poly << (8 - crc->Width)) : poly;
        bit = (crc->Width > 8) ? ((crc_word_t)1 << (crc->Width - 1)) : 0x80;
        for (crc_word_t i = 0; i < 256; i++)
        {
            value = (crc->Width > 8) ? ((crc_word_t)i << (crc->Width - 8)) : i;
            for (j = 0; j < 8; j++)
            {
                if (value & bit)
                {
                    value = (value << 1) ^ poly;
                }
                else
                {
                    value = (value << 1);
                }
            }
            crc->Table[i] = value & ((crc->Width < 8) ? 0xff : validBits);
        }
    }
    //CrcTablePrint(type);

    crc->TableUpdated = 1;
}

/// <summary>
/// 打印CRC查表数组
/// </summary>
/// <param name="crc">CRC结构</param>
void CrcTablePrint(CrcInfoType* crc)
{
    if (!crc->TableUpdated)
        CrcUpdateTable(crc);

    crc_word_t i;

    PRINTF_DBG("crc->Table = \n{//%s", crc->Name);
    for (i = 0; i < 256; i++)
    {
        if (i % 16 == 0) PRINTF_DBG("\n     ");
        if (crc->Width < 9) PRINTF_DBG("0x%02" PRIFMT_CRC_WORD ", ", crc->Table[i]);
        else if (crc->Width < 17) PRINTF_DBG("0x%04" PRIFMT_CRC_WORD ", ", crc->Table[i]);
        else if (crc->Width < 33) PRINTF_DBG("0x%08" PRIFMT_CRC_WORD ", ", crc->Table[i]);
        else PRINTF_DBG("0x%16" PRIFMT_CRC_WORD ", ", crc->Table[i]);
    }
    PRINTF_DBG("\n};\n\n");
}

/// <summary>
/// CRC计算（若运行时修改结构体CRC参数需要运行 CrcUpdateTable() 重新生成查表）
/// </summary>
/// <param name="crc">CRC结构</param>
/// <param name="buf">输入数据</param>
/// <param name="bufLen">输入数据长度</param>
/// <returns>CRC值</returns>
crc_word_t CrcCalculate(CrcInfoType* crc, uint8_t* buf, uint32_t bufLen)
{
    if (!crc->TableUpdated)
        CrcUpdateTable(crc);

    crc_word_t crc_result = crc->Init;
    uint8_t byte;
    uint8_t msb;

    if (crc->RefIn)
    {
        crc_result = BitsReverse(crc_result, crc->Width);
        if (crc->Width > 8)
        {
            while (bufLen--)
            {
                byte = *buf++;
                crc_result = (crc_result >> 8) ^ crc->Table[(crc_result & 0xFF) ^ byte];
            }
        }
        else {
            while (bufLen--)
            {
                byte = *buf++;
                crc_result = crc->Table[crc_result ^ byte];
            }
        }
    }
    else {
        if (crc->Width > 8)
        {
            while (bufLen--)
            {
                byte = *buf++;
                msb = crc_result >> (crc->Width - 8);
                crc_result = (crc_result << 8) ^ crc->Table[msb ^ byte];
            }
        }
        else
        {
            crc_result <<= (8 - crc->Width);
            while (bufLen--)
            {
                byte = *buf++;
                crc_result = crc->Table[crc_result ^ byte];
            }
            crc_result >>= (8 - crc->Width);
        }
    }

    if (crc->RefOut ^ crc->RefIn)
    {
        crc_result = BitsReverse(crc_result, crc->Width);
    }
    crc_result ^= crc->XorOut;

    crc_word_t validBits = (~((crc_word_t)0) >> (sizeof(crc_word_t) * 8 - crc->Width));
    return crc_result & validBits;
}