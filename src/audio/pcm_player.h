#pragma once

#include <stdint.h>

class PCM_Player 
{
public:
    struct Parameters {
        uint32_t sample_rate;
        uint8_t total_channels;
        uint8_t bytes_per_sample;
        uint32_t block_size;
        bool operator==(const Parameters& o) {
            return 
                (sample_rate == o.sample_rate) &&
                (total_channels == o.total_channels) &&
                (bytes_per_sample == o.bytes_per_sample) &&
                (block_size == o.block_size);
        }
    };
public:
    virtual void ConsumeBuffer(const uint8_t* buf, const int N) = 0;
    virtual bool SetParameters(const Parameters params) = 0;
    virtual Parameters GetParameters(void) = 0;
};