// Copyright 2017 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FXCRT_XML_CFX_XMLINSTRUCTION_H_
#define CORE_FXCRT_XML_CFX_XMLINSTRUCTION_H_

#include <memory>
#include <vector>

#include "core/fxcrt/fx_string.h"
#include "core/fxcrt/xml/cfx_xmlnode.h"

class CFX_XMLInstruction : public CFX_XMLNode {
 public:
  explicit CFX_XMLInstruction(const WideString& wsTarget);
  ~CFX_XMLInstruction() override;

  // CFX_XMLNode
  FX_XMLNODETYPE GetType() const override;
  std::unique_ptr<CFX_XMLNode> Clone() override;
  void Save(const RetainPtr<IFX_SeekableWriteStream>& pXMLStream) override;

  bool IsOriginalXFAVersion() const;
  bool IsAcrobat() const;

  const std::vector<WideString>& GetTargetData() const { return m_TargetData; }
  void AppendData(const WideString& wsData);

 private:
  WideString name_;
  std::vector<WideString> m_TargetData;
};

#endif  // CORE_FXCRT_XML_CFX_XMLINSTRUCTION_H_
