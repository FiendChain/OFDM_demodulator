#pragma once

#include "pad_data_group.h"

class MSC_XPAD_Processor;
class MOT_Processor;

// This class does the following steps: 
// 1. Reconstructs the MSC XPAD data group from XPAD data group segments
// 2. Passes reconstructed MSC XPAD data group to msc_xpad_processor for decoding
// 3. Passes decoded MSC XPAD data group to the MOT processor as a MOT segment
// 4. MOT segments are assembled into MOT entities 
class PAD_MOT_Processor 
{
private:
    enum State { WAIT_LENGTH, WAIT_START, READ_DATA };
private:
    PAD_Data_Group data_group;    
    State state;

    MSC_XPAD_Processor* msc_xpad_processor;
    MOT_Processor* mot_processor;
public:
    PAD_MOT_Processor();
    ~PAD_MOT_Processor();
    void ProcessXPAD(
        const bool is_start, const bool is_conditional_access, 
        const uint8_t* buf, const int N);
    void SetGroupLength(const uint16_t length);
    MOT_Processor* Get_MOT_Processor(void) { return mot_processor; }
private:
    int Consume(
        const bool is_start, const bool is_conditional_access, 
        const uint8_t* buf, const int N);
    void Interpret(void);
};