// Copyright 2019 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_TOOLS_DEBUG_HELPER_HEAP_CONSTANTS_H_
#define V8_TOOLS_DEBUG_HELPER_HEAP_CONSTANTS_H_

#include <cstdint>
#include <string>
#include <vector>

#include "debug-helper.h"
#include "src/objects/instance-type.h"

namespace d = v8::debug_helper;

namespace v8_debug_helper_internal {

// ===== Functions generated by gen-heap-constants.py: =========================

// Returns the name of a known object, given its offset within the first page of
// the space, or empty string on failure.
std::string FindKnownObjectInOldSpace(uintptr_t offset);
std::string FindKnownObjectInReadOnlySpace(uintptr_t offset);
std::string FindKnownObjectInMapSpace(uintptr_t offset);

// In builds with pointer compression enabled, sets the *_first_page members in
// the HeapAddresses object. In other builds, does nothing.
void FillInUnknownHeapAddresses(d::HeapAddresses* heap_addresses,
                                uintptr_t any_uncompressed_ptr);

// Returns the instance type for the known Map, given its offset within the
// first page of the space, or empty string on failure.
int FindKnownMapInstanceTypeInMapSpace(uintptr_t offset);
int FindKnownMapInstanceTypeInReadOnlySpace(uintptr_t offset);

// ===== End of generated functions. ===========================================

// Returns a descriptive string if the given address matches a known object, or
// an empty string otherwise.
std::string FindKnownObject(uintptr_t address,
                            const d::HeapAddresses& heap_addresses);

struct KnownInstanceType {
  enum class Confidence {
    kLow,
    kHigh,
  };
  KnownInstanceType() : confidence(Confidence::kLow) {}
  KnownInstanceType(int type) : KnownInstanceType() {
    if (type >= 0) {
      confidence = Confidence::kHigh;
      types.push_back(static_cast<v8::internal::InstanceType>(type));
    }
  }
  Confidence confidence;
  std::vector<v8::internal::InstanceType> types;
};

// Returns information about the instance type of the Map at the given address,
// based on the list of known Maps.
KnownInstanceType FindKnownMapInstanceTypes(
    uintptr_t address, const d::HeapAddresses& heap_addresses);

}  // namespace v8_debug_helper_internal

#endif
