#include <gtest/gtest.h>

#include "Decoder.h"
#include "BaseTypes.h"
#include "Instruction.cpp"

namespace MyUnits
{

//    void SplitInWord()
//    {
//        buf_data = OPCODE;
//
//        uint offset = OPCODE_SIZE;
//        buf_data |= (CHECK_imm11 << offset);
//        offset += IMM_11_SIZE;
//        buf_data |= (CHECK_imm4_1 << offset);
//        offset += IMM_1_4_SIZE;
//        buf_data |= (FUNC << offset);
//        offset += FUNC_SIZE;
//        buf_data |= (CHECK_RS1 << offset);
//        offset += RS1_SIZE;
//        buf_data |= (CHECK_RS2 << offset);
//        offset += RS2_SIZE;
//        buf_data |= (CHECK_imm10_5 << offset);
//        offset += IMM_10_5_SIZE;
//        buf_data |= (CHECK_imm12 << offset);
//
//        instr = * decoder.Decode((buf_data));
//    }

    Word SplitAllImm(Word imm12, Word imm11, Word imm10_5, Word imm4_1)
    {
        Word _imm = (imm12 << 12u) | (imm11 << 11u) | (imm10_5 << 5u) | (imm4_1 << 1u);
        return _imm;
    }


//    bool CheckDecoderForBGEUInstraction(const Instruction& instr, Word rs1, Word rs2, Word imm, Word func)
//    {
//        return instr._imm.value() == imm &&
//               instr._src1 == rs1 &&
//               instr._src2 == rs2 &&
//               instr._type == IType::Br &&
//               instr._brFunc == static_cast<BrFunc>(func);
//    }
//
//    TEST(TEST_DECODER, TestDeocderForBGEU)
//    {
//
//        //SplitInWord();
//        //EXPECT_EQ(instr._src1, CHECK_RS1);
//
//        Instruction instr;
//        Word buf_data;
//        Decoder decoder;
//
//        buf_data = OPCODE;
//
//        uint offset = OPCODE_SIZE;
//        buf_data |= (CHECK_imm11 << offset);
//        offset += IMM_11_SIZE;
//        buf_data |= (CHECK_imm4_1 << offset);
//        offset += IMM_1_4_SIZE;
//        buf_data |= (FUNC << offset);
//        offset += FUNC_SIZE;
//        buf_data |= (CHECK_RS1 << offset);
//        offset += RS1_SIZE;
//        buf_data |= (CHECK_RS2 << offset);
//        offset += RS2_SIZE;
//        buf_data |= (CHECK_imm10_5 << offset);
//        offset += IMM_10_5_SIZE;
//        buf_data |= (CHECK_imm12 << offset);
//
//        instr = * decoder.Decode((buf_data));
//        EXPECT_TRUE(CheckDecoderForBGEUInstraction(instr, CHECK_RS1, CHECK_RS2,
//                SplitAllImm(CHECK_imm12, CHECK_imm11, CHECK_imm10_5, CHECK_imm4_1), FUNC));
//    }
//


    static Word OPCODE = 0b1100011;
    //static Word CHECK_IMM = 0b010010010011;
    static Word CHECK_imm11 = 0b1;
    static Word CHECK_imm4_1 = 0b0100;
    static Word CHECK_imm10_5 = 0b010001;
    static Word CHECK_imm12 = 0b0;
    static Word FUNC = 0b111;
    static Word CHECK_RS1 = 0b01001;
    static Word CHECK_RS2 = 0b10010;


    static uint OPCODE_SIZE = 7u;
    static uint FUNC_SIZE = 3u;
    static uint IMM_1_4_SIZE = 4u;
    static uint IMM_11_SIZE = 1u;
    static uint IMM_10_5_SIZE = 6u;
    static uint IMM_12_SIZE = 1u;
    static uint RS1_SIZE = 5u;
    static uint RS2_SIZE = 5u;



    bool CheckDecoderForBGEUInstraction(const Instruction& instr, Word rs1, Word rs2, Word imm, Word func)
    {
        return instr._imm.value() == imm &&
               instr._src1 == rs1 &&
               instr._src2 == rs2 &&
               instr._type == IType::Br &&
               instr._brFunc == static_cast<BrFunc>(func);
    }

    class DataFixture: public ::testing::Test
    {
    public:
        Word CHECK_IMM;

        DataFixture()
        {
            buf_data = OPCODE;

            uint offset = OPCODE_SIZE;
            buf_data |= (CHECK_imm11 << offset);
            offset += IMM_11_SIZE;
            buf_data |= (CHECK_imm4_1 << offset);
            offset += IMM_1_4_SIZE;
            buf_data |= (FUNC << offset);
            offset += FUNC_SIZE;
            buf_data |= (CHECK_RS1 << offset);
            offset += RS1_SIZE;
            buf_data |= (CHECK_RS2 << offset);
            offset += RS2_SIZE;
            buf_data |= (CHECK_imm10_5 << offset);
            offset += IMM_10_5_SIZE;
            buf_data |= (CHECK_imm12 << offset);

            decoder = Decoder();
            instr = Instruction();

            CHECK_IMM =  SplitAllImm(CHECK_imm12, CHECK_imm11, CHECK_imm10_5, CHECK_imm4_1);
        }

        void SetUp() override
        {
            instr = * decoder.Decode(buf_data);
        }

        void SetUp(Word rd, Word imm)
        {
            buf_data = OPCODE;

            uint offset = OPCODE_SIZE;
            buf_data |= (CHECK_imm11 << offset);
            offset += IMM_11_SIZE;
            buf_data |= (CHECK_imm4_1 << offset);
            offset += IMM_1_4_SIZE;
            buf_data |= (FUNC << offset);
            offset += FUNC_SIZE;
            buf_data |= (CHECK_RS1 << offset);
            offset += RS1_SIZE;
            buf_data |= (CHECK_RS2 << offset);
            offset += RS2_SIZE;
            buf_data |= (CHECK_imm10_5 << offset);
            offset += IMM_10_5_SIZE;
            buf_data |= (CHECK_imm12 << offset);

            SetUp();
        }
        void TearDown() override {}
        Instruction instr;

    private:
        Word buf_data;
        Decoder decoder;
    };

    TEST_F(DataFixture, TestDeocderForBGEU1)
    {
        EXPECT_EQ(instr._brFunc, static_cast<BrFunc>(FUNC));
        EXPECT_EQ(instr._imm.value(), CHECK_IMM);
        EXPECT_EQ(instr._src1, CHECK_RS1);
        EXPECT_EQ(instr._src2, CHECK_RS2);
        ASSERT_EQ(instr._type, IType::Br);
    }

    TEST_F(DataFixture, TestDeocderForBGEU2)
    {
        ASSERT_TRUE(CheckDecoderForBGEUInstraction(instr, CHECK_RS1, CHECK_RS2, CHECK_IMM, FUNC));
    }


    TEST_F(DataFixture, TestDeocderForBGEU3)
    {

    }
}

