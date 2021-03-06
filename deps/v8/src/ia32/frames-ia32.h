// Copyright 2011 the V8 project authors. All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of Google Inc. nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef V8_IA32_FRAMES_IA32_H_
#define V8_IA32_FRAMES_IA32_H_

namespace v8 {
namespace internal {


// Register lists
// Note that the bit values must match those used in actual instruction encoding
static const int kNumRegs = 8;


// Caller-saved registers
static const RegList kJSCallerSaved =
  1 << 0 |  // eax
  1 << 1 |  // ecx
  1 << 2 |  // edx
  1 << 3 |  // ebx - used as a caller-saved register in JavaScript code
  1 << 7;   // edi - callee function

static const int kNumJSCallerSaved = 5;

typedef Object* JSCallerSavedBuffer[kNumJSCallerSaved];


// Number of registers for which space is reserved in safepoints.
static const int kNumSafepointRegisters = 8;

// ----------------------------------------------------


class StackHandlerConstants : public AllStatic {
 public:
  static const int kNextOffset    = 0 * kPointerSize;
  static const int kContextOffset = 1 * kPointerSize;
  static const int kFPOffset      = 2 * kPointerSize;
  static const int kStateOffset   = 3 * kPointerSize;
  static const int kPCOffset      = 4 * kPointerSize;

  static const int kSize = kPCOffset + kPointerSize;
};


class EntryFrameConstants : public AllStatic {
 public:
  static const int kCallerFPOffset      = -6 * kPointerSize;

  static const int kFunctionArgOffset   = +3 * kPointerSize;
  static const int kReceiverArgOffset   = +4 * kPointerSize;
  static const int kArgcOffset          = +5 * kPointerSize;
  static const int kArgvOffset          = +6 * kPointerSize;
};


class ExitFrameConstants : public AllStatic {
 public:
  static const int kCodeOffset     = -2 * kPointerSize;
  static const int kSPOffset       = -1 * kPointerSize;

  static const int kCallerFPOffset =  0 * kPointerSize;
  static const int kCallerPCOffset = +1 * kPointerSize;

  // FP-relative displacement of the caller's SP.  It points just
  // below the saved PC.
  static const int kCallerSPDisplacement = +2 * kPointerSize;
};


class StandardFrameConstants : public AllStatic {
 public:
  // StandardFrame::IterateExpressions assumes that kContextOffset is the last
  // object pointer.
  static const int kFixedFrameSize    =  4;  // Currently unused.
  static const int kExpressionsOffset = -3 * kPointerSize;
  static const int kMarkerOffset      = -2 * kPointerSize;
  static const int kContextOffset     = -1 * kPointerSize;
  static const int kCallerFPOffset    =  0 * kPointerSize;
  static const int kCallerPCOffset    = +1 * kPointerSize;
  static const int kCallerSPOffset    = +2 * kPointerSize;
};


class JavaScriptFrameConstants : public AllStatic {
 public:
  // FP-relative.
  static const int kLocal0Offset = StandardFrameConstants::kExpressionsOffset;
  static const int kLastParameterOffset = +2 * kPointerSize;
  static const int kFunctionOffset = StandardFrameConstants::kMarkerOffset;

  // Caller SP-relative.
  static const int kParam0Offset   = -2 * kPointerSize;
  static const int kReceiverOffset = -1 * kPointerSize;
};


class ArgumentsAdaptorFrameConstants : public AllStatic {
 public:
  static const int kLengthOffset = StandardFrameConstants::kExpressionsOffset;
};


class InternalFrameConstants : public AllStatic {
 public:
  static const int kCodeOffset = StandardFrameConstants::kExpressionsOffset;
};


inline Object* JavaScriptFrame::function_slot_object() const {
  const int offset = JavaScriptFrameConstants::kFunctionOffset;
  return Memory::Object_at(fp() + offset);
}


} }  // namespace v8::internal

#endif  // V8_IA32_FRAMES_IA32_H_
