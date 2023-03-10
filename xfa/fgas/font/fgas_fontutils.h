// Copyright 2014 The PDFium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef XFA_FGAS_FONT_FGAS_FONTUTILS_H_
#define XFA_FGAS_FONT_FGAS_FONTUTILS_H_

#include <stdint.h>

#include "core/fxcrt/fx_codepage_forward.h"
#include "core/fxcrt/widestring.h"

struct FGAS_FONTUSB {
  static constexpr uint16_t kNoBitField = 999;

  uint16_t wStartUnicode;
  uint16_t wEndUnicode;
  uint16_t wBitField;
  FX_CodePage wCodePage;
};

const FGAS_FONTUSB* FGAS_GetUnicodeBitField(wchar_t wUnicode);

struct FGAS_FontInfo {
  uint32_t dwFontNameHash;   // WideString hash.
  const char* pPsName;       // Raw, POD struct.
  const char* pReplaceFont;  // Raw, POD struct.
  uint16_t dwStyles;
  FX_CodePage wCodePage;
};

WideString FGAS_FontNameToEnglishName(const WideString& wsLocalName);
const FGAS_FontInfo* FGAS_FontInfoByFontName(WideStringView wsFontName);

#endif  // XFA_FGAS_FONT_FGAS_FONTUTILS_H_
