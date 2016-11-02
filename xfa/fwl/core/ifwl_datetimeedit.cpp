// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "xfa/fwl/core/ifwl_datetimeedit.h"

#include "third_party/base/ptr_util.h"
#include "xfa/fwl/core/cfwl_widgetmgr.h"
#include "xfa/fwl/core/ifwl_datetimepicker.h"

IFWL_DateTimeEdit::IFWL_DateTimeEdit(const IFWL_App* app,
                                     const CFWL_WidgetImpProperties& properties,
                                     IFWL_Widget* pOuter)
    : IFWL_Edit(app, properties, pOuter) {
  SetDelegate(pdfium::MakeUnique<CFWL_DateTimeEditImpDelegate>(this));
}

CFWL_DateTimeEditImpDelegate::CFWL_DateTimeEditImpDelegate(
    IFWL_DateTimeEdit* pOwner)
    : CFWL_EditImpDelegate(pOwner), m_pOwner(pOwner) {}

void CFWL_DateTimeEditImpDelegate::OnProcessMessage(CFWL_Message* pMessage) {
  if (m_pOwner->m_pWidgetMgr->IsFormDisabled()) {
    DisForm_OnProcessMessage(pMessage);
    return;
  }

  CFWL_MessageType dwHashCode = pMessage->GetClassID();
  if (dwHashCode == CFWL_MessageType::SetFocus ||
      dwHashCode == CFWL_MessageType::KillFocus) {
    IFWL_Widget* pOuter = m_pOwner->GetOuter();
    pOuter->GetCurrentDelegate()->OnProcessMessage(pMessage);
  }
}

void CFWL_DateTimeEditImpDelegate::DisForm_OnProcessMessage(
    CFWL_Message* pMessage) {
  CFWL_MessageType dwHashCode = pMessage->GetClassID();
  if (m_pOwner->m_pWidgetMgr->IsFormDisabled()) {
    if (dwHashCode == CFWL_MessageType::Mouse) {
      CFWL_MsgMouse* pMouse = static_cast<CFWL_MsgMouse*>(pMessage);
      if (pMouse->m_dwCmd == FWL_MouseCommand::LeftButtonDown ||
          pMouse->m_dwCmd == FWL_MouseCommand::RightButtonDown) {
        if ((m_pOwner->m_pProperties->m_dwStates & FWL_WGTSTATE_Focused) == 0) {
          m_pOwner->m_pProperties->m_dwStates |= FWL_WGTSTATE_Focused;
        }
        IFWL_DateTimePicker* pDateTime =
            static_cast<IFWL_DateTimePicker*>(m_pOwner->m_pOuter);
        if (pDateTime->IsMonthCalendarShowed()) {
          CFX_RectF rtInvalidate;
          pDateTime->GetWidgetRect(rtInvalidate);
          pDateTime->ShowMonthCalendar(FALSE);
          rtInvalidate.Offset(-rtInvalidate.left, -rtInvalidate.top);
          pDateTime->Repaint(&rtInvalidate);
        }
      }
    }
  }
  CFWL_EditImpDelegate::OnProcessMessage(pMessage);
}
