//=========================================================================
// Copyright (C) 2012 The Elastos Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=========================================================================

#ifndef __ELASTOS_SECURITY_AUTHPROVIDER_H__
#define __ELASTOS_SECURITY_AUTHPROVIDER_H__

#include "elastos/security/Provider.h"

namespace Elastos {
namespace Security {

class AuthProvider
    : public Provider
    , public IAuthProvider
{
public:
    CAR_INTERFACE_DECL()

    virtual ~AuthProvider() = 0;

protected:
    CARAPI constructor(
        /* [in] */ const String& name,
        /* [in] */ Double version,
        /* [in] */ const String& info);
};

} // namespace Security
} // namespace Elastos

#endif // __ELASTOS_SECURITY_AUTHPROVIDER_H__
