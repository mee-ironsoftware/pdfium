// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef XFA_FXFA_PARSER_CXFA_DOCUMENT_PARSER_H_
#define XFA_FXFA_PARSER_CXFA_DOCUMENT_PARSER_H_

#include <memory>
#include <utility>

#include "core/fxcrt/xml/cfx_xmlnode.h"
#include "xfa/fxfa/fxfa_basic.h"

class CXFA_Document;
class CXFA_Node;
class CFX_XMLDoc;
class CFX_XMLInstruction;
class IFX_SeekableStream;
class CFX_SeekableStreamProxy;

class CXFA_DocumentParser {
 public:
  CXFA_DocumentParser();
  explicit CXFA_DocumentParser(CXFA_Document* pFactory);
  ~CXFA_DocumentParser();

  bool Parse(const RetainPtr<IFX_SeekableStream>& pStream,
             XFA_PacketType ePacketID);

  CFX_XMLNode* ParseXMLData(const ByteString& wsXML);
  void ConstructXFANode(CXFA_Node* pXFANode, CFX_XMLNode* pXMLNode);

  std::unique_ptr<CFX_XMLNode> GetXMLRoot() { return std::move(m_pNodeTree); }
  CXFA_Node* GetRootNode() const;

  // Called later for the ctor with no parameters.
  void SetFactory(CXFA_Document* pFactory);

 private:
  std::unique_ptr<CFX_XMLNode> LoadXML(
      const RetainPtr<CFX_SeekableStreamProxy>& pStream);

  CXFA_Node* ParseAsXDPPacket(CFX_XMLNode* pXMLDocumentNode,
                              XFA_PacketType ePacketID);
  CXFA_Node* ParseAsXDPPacket_XDP(CFX_XMLNode* pXMLDocumentNode);
  CXFA_Node* ParseAsXDPPacket_Config(CFX_XMLNode* pXMLDocumentNode);
  CXFA_Node* ParseAsXDPPacket_Template(CFX_XMLNode* pXMLDocumentNode);
  CXFA_Node* ParseAsXDPPacket_Form(CFX_XMLNode* pXMLDocumentNode);
  CXFA_Node* ParseAsXDPPacket_Data(CFX_XMLNode* pXMLDocumentNode);
  CXFA_Node* ParseAsXDPPacket_LocaleConnectionSourceSet(
      CFX_XMLNode* pXMLDocumentNode,
      XFA_PacketType packet_type,
      XFA_Element element);
  CXFA_Node* ParseAsXDPPacket_Xdc(CFX_XMLNode* pXMLDocumentNode);
  CXFA_Node* ParseAsXDPPacket_User(CFX_XMLNode* pXMLDocumentNode);
  CXFA_Node* NormalLoader(CXFA_Node* pXFANode,
                          CFX_XMLNode* pXMLDoc,
                          XFA_PacketType ePacketID,
                          bool bUseAttribute);
  CXFA_Node* DataLoader(CXFA_Node* pXFANode,
                        CFX_XMLNode* pXMLDoc,
                        bool bDoTransform);
  CXFA_Node* UserPacketLoader(CXFA_Node* pXFANode, CFX_XMLNode* pXMLDoc);
  void ParseContentNode(CXFA_Node* pXFANode,
                        CFX_XMLNode* pXMLNode,
                        XFA_PacketType ePacketID);
  void ParseDataValue(CXFA_Node* pXFANode,
                      CFX_XMLNode* pXMLNode,
                      XFA_PacketType ePacketID);
  void ParseDataGroup(CXFA_Node* pXFANode,
                      CFX_XMLNode* pXMLNode,
                      XFA_PacketType ePacketID);
  void ParseInstruction(CXFA_Node* pXFANode,
                        CFX_XMLInstruction* pXMLInstruction,
                        XFA_PacketType ePacketID);

  UnownedPtr<CXFA_Document> m_pFactory;
  std::unique_ptr<CFX_XMLNode> m_pNodeTree;
  // TODO(dsinclair): Figure out who owns this.
  CXFA_Node* m_pRootNode = nullptr;
  const bool m_bDocumentParser;
};

#endif  // XFA_FXFA_PARSER_CXFA_DOCUMENT_PARSER_H_
