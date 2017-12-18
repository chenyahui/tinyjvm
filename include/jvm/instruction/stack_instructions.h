#ifndef MY_JVM_INSTRUCTION_STORE_INSTRUCTIONS_H
#define MY_JVM_INSTRUCTION_STORE_INSTRUCTIONS_H

#include <jvm/instruction/instruction.h>
namespace cyh {
template <int num = 1>
class POP_Instruction : public NoOperandsInstruction {
public:
    void Execute(JFrame& frame)
    {
	auto op_stack = frame.OpStack();
	for (int i = 0; i < num; i++) {
	    op_stack.Pop<LocalSlot>();
	}
    }
};

using POP2_Instruction = POP_Instruction<2>;

// X代表弹出几个，D代表复制栈顶前几个
template <int D = 1, int X = 0>
class DUP_Instruction : public NoOperandsInstruction {
public:
    void Execute(JFrame& frame)
    {
	std::vector<LocalSlot> temp;

	auto op_stack = frame.OpStack();

	// 弹出
	for (int i = 0; i < X + D; i++) {
	    temp.push_back(op_stack.Pop<LocalSlot>());
	}

	// 入栈
	for (int i = 0; i < X + D; i++) {
	    op_stack.Push<LocalSlot>(temp[i]);
	}
	// 倒着复制
	for (int i = 0; i < D; i++) {
	    op_stack.Push<LocalSlot>(temp[i]);
	}
    }
};

using DUP_X1_Instruction = DUP_Instruction<1, 1>;
using DUP_X2_Instruction = DUP_Instruction<1, 2>;
using DUP2_Instruction = DUP_Instruction<2, 0>;
using DUP2_X1_Instruction = DUP_Instruction<2, 1>;
using DUP2_X2_Instruction = DUP_Instruction<2, 1>;

class SWAP_Instruction : public NoOperandsInstruction {
public:
    void Execute(JFrame& frame) override
    {
	auto op_stack = frame.OpStack();

	auto val1 = op_stack.Pop<LocalSlot>();
	auto val2 = op_stack.Pop<LocalSlot>();

	op_stack.Push<LocalSlot>(val1);
	op_stack.Push<LocalSlot>(val2);
    }
};
}
#endif
