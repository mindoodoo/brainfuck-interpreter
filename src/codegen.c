/*
 * Created on Mon Mar 13 2023
 *
 * by Léon Sautour
 */

#include "brainfuck.h"

// Entry point
LLVMModuleRef build_module(ast_node *ast_head) {
    // Create builder and module
    LLVMBuilderRef builder = LLVMCreateBuilder();
    LLVMModuleRef module = LLVMModuleCreateWithName("main_module");

    // Build brainfuck state
    build_state(module, builder);

    // Build internal library functions
}

void build_state(LLVMModuleRef mod, LLVMBuilderRef builder) {
    // Create type for our tape (byte)
    LLVMTypeRef tapeType = LLVMArrayType(LLVMInt8Type, TAPE_LENGTH);
    // Create global tape
    LLVMAddGlobal(mod, tapeType, "tape");
    // Create head pointer
    LLVMAddGlobal(mod, LLVMInt8Type, "head");
}

int build_internal_lib(LLVMModuleRef mod, LLVMBuilderRef builder) {


    // Implement standard functions
        // <
        // >
        // +
        // -
        // .
        // ,
        // [
        // ]
    return 0;
}

// ─── Internal Library Factories ──────────────────────────────────────────────────────────────────

// I have no clue if this works
// For the time being this doesn't create a function or anything yet
void move_left(LLVMModuleRef mod, LLVMBuilderRef builder) {
    LLVMValueRef head_global = LLVMGetNamedGlobal(mod, "tape");
    LLVMValueRef head = LLVMBuildLoad(builder, head_global, "head");
    LLVMValueRef new_head = LLVMBuildSub(builder, head, LLVMConstInt(LLVMInt8Type(), 1, 0), "new_head");
    LLVMValueRef store = LLVMBuildStore(builder, new_head, head_global);
}