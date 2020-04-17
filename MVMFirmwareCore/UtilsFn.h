#pragma once

uint32_t GenerateFlag(int alarm_code)
{
    return (1 << alarm_code);
}