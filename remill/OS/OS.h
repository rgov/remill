/* Copyright 2016 Peter Goodman (peter@trailofbits.com), all rights reserved. */

#ifndef REMILL_OS_OS_H_
#define REMILL_OS_OS_H_

#include <string>

namespace remill {

enum OSName {
  kOSInvalid,
  kOSMacOSX,
  kOSLinux
};

OSName GetOSName(std::string name_);

}  // namespace remill

#endif  // REMILL_OS_OS_H_
