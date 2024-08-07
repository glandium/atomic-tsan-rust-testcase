/* vim: set ts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

/* This file is generated from sources in nss/gtests/common/wycheproof
 * automatically and should not be touched manually.
 * Generation is trigged by calling python3 genTestVectors.py */

#ifndef rsa_signature_vectors_h__
#define rsa_signature_vectors_h__

#include "testvectors_base/test-structs.h"

// kSpki is an RSA public key in an X.509 SubjectPublicKeyInfo.
const uint8_t kSpki[] = {
    0x30, 0x81, 0x9f, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7,
    0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x81, 0x8d, 0x00, 0x30, 0x81,
    0x89, 0x02, 0x81, 0x81, 0x00, 0xf8, 0xb8, 0x6c, 0x83, 0xb4, 0xbc, 0xd9,
    0xa8, 0x57, 0xc0, 0xa5, 0xb4, 0x59, 0x76, 0x8c, 0x54, 0x1d, 0x79, 0xeb,
    0x22, 0x52, 0x04, 0x7e, 0xd3, 0x37, 0xeb, 0x41, 0xfd, 0x83, 0xf9, 0xf0,
    0xa6, 0x85, 0x15, 0x34, 0x75, 0x71, 0x5a, 0x84, 0xa8, 0x3c, 0xd2, 0xef,
    0x5a, 0x4e, 0xd3, 0xde, 0x97, 0x8a, 0xdd, 0xff, 0xbb, 0xcf, 0x0a, 0xaa,
    0x86, 0x92, 0xbe, 0xb8, 0x50, 0xe4, 0xcd, 0x6f, 0x80, 0x33, 0x30, 0x76,
    0x13, 0x8f, 0xca, 0x7b, 0xdc, 0xec, 0x5a, 0xca, 0x63, 0xc7, 0x03, 0x25,
    0xef, 0xa8, 0x8a, 0x83, 0x58, 0x76, 0x20, 0xfa, 0x16, 0x77, 0xd7, 0x79,
    0x92, 0x63, 0x01, 0x48, 0x1a, 0xd8, 0x7b, 0x67, 0xf1, 0x52, 0x55, 0x49,
    0x4e, 0xd6, 0x6e, 0x4a, 0x5c, 0xd7, 0x7a, 0x37, 0x36, 0x0c, 0xde, 0xdd,
    0x8f, 0x44, 0xe8, 0xc2, 0xa7, 0x2c, 0x2b, 0xb5, 0xaf, 0x64, 0x4b, 0x61,
    0x07, 0x02, 0x03, 0x01, 0x00, 0x01,
};
// kHash is the SHA-256 hash of {1,2,3,4}.
const uint8_t kHash[] = {
    0x9f, 0x64, 0xa7, 0x47, 0xe1, 0xb9, 0x7f, 0x13, 0x1f, 0xab, 0xb6,
    0xb4, 0x47, 0x29, 0x6c, 0x9b, 0x6f, 0x02, 0x01, 0xe7, 0x9f, 0xb3,
    0xc5, 0x35, 0x6e, 0x6c, 0x77, 0xe8, 0x9b, 0x6a, 0x80, 0x6a,
};
// kSignature is the signature of kHash with RSASSA-PKCS1-v1_5.
const uint8_t kSignature[] = {
    0xa5, 0xf0, 0x8a, 0x47, 0x5d, 0x3c, 0xb3, 0xcc, 0xa9, 0x79, 0xaf, 0x4d,
    0x8c, 0xae, 0x4c, 0x14, 0xef, 0xc2, 0x0b, 0x34, 0x36, 0xde, 0xf4, 0x3e,
    0x3d, 0xbb, 0x4a, 0x60, 0x5c, 0xc8, 0x91, 0x28, 0xda, 0xfb, 0x7e, 0x04,
    0x96, 0x7e, 0x63, 0x13, 0x90, 0xce, 0xb9, 0xb4, 0x62, 0x7a, 0xfd, 0x09,
    0x3d, 0xc7, 0x67, 0x78, 0x54, 0x04, 0xeb, 0x52, 0x62, 0x6e, 0x24, 0x67,
    0xb4, 0x40, 0xfc, 0x57, 0x62, 0xc6, 0xf1, 0x67, 0xc1, 0x97, 0x8f, 0x6a,
    0xa8, 0xae, 0x44, 0x46, 0x5e, 0xab, 0x67, 0x17, 0x53, 0x19, 0x3a, 0xda,
    0x5a, 0xc8, 0x16, 0x3e, 0x86, 0xd5, 0xc5, 0x71, 0x2f, 0xfc, 0x23, 0x48,
    0xd9, 0x0b, 0x13, 0xdd, 0x7b, 0x5a, 0x25, 0x79, 0xef, 0xa5, 0x7b, 0x04,
    0xed, 0x44, 0xf6, 0x18, 0x55, 0xe4, 0x0a, 0xe9, 0x57, 0x79, 0x5d, 0xd7,
    0x55, 0xa7, 0xab, 0x45, 0x02, 0x97, 0x60, 0x42,
};
// kSignature is an invalid signature of kHash with RSASSA-PKCS1-v1_5 with the
// NULL parameter omitted.
const uint8_t kSignatureInvalid[] = {
    0x71, 0x6c, 0x24, 0x4e, 0xc9, 0x9b, 0x19, 0xc7, 0x49, 0x29, 0xb8, 0xd4,
    0xfb, 0x26, 0x23, 0xc0, 0x96, 0x18, 0xcd, 0x1e, 0x60, 0xe8, 0x88, 0x94,
    0x8c, 0x59, 0xfb, 0x58, 0x5c, 0x61, 0x58, 0x7a, 0xae, 0xcc, 0xeb, 0xee,
    0x1e, 0x85, 0x7d, 0x83, 0xa9, 0xdc, 0x6f, 0x4c, 0x34, 0x5c, 0xcb, 0xd9,
    0xde, 0x58, 0x76, 0xdf, 0x1f, 0x5e, 0xd4, 0x57, 0x5b, 0xeb, 0xaf, 0x4f,
    0x7a, 0xa7, 0x6b, 0x21, 0xf1, 0x0a, 0x96, 0x78, 0xc7, 0xa8, 0x02, 0x7a,
    0xc2, 0x06, 0xd3, 0x18, 0x79, 0x72, 0x6b, 0xfe, 0x2d, 0xec, 0xd8, 0x8e,
    0x98, 0x86, 0x89, 0xf4, 0x67, 0x14, 0x2b, 0xac, 0x6d, 0xd7, 0x04, 0xd8,
    0xab, 0x05, 0xe6, 0x51, 0xf6, 0xee, 0x58, 0x63, 0xef, 0x6a, 0x3e, 0x89,
    0x99, 0x2a, 0x1c, 0x10, 0xc2, 0xd0, 0x41, 0x9e, 0x1e, 0x9a, 0x9a, 0x57,
    0x32, 0x0f, 0x49, 0xb4, 0x57, 0x37, 0xa4, 0x26,
};

#endif  // rsa_signature_vectors_h__
