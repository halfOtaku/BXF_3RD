//////////////////////////////////////////////////////////////////////////////
// Name:        SVGTSpanElement.h
// Author:      Alex Thuering
// Copyright:   (c) 2005 Alex Thuering
// Licence:     wxWindows licence
// Notes:       generated by generate.py
//////////////////////////////////////////////////////////////////////////////

#ifndef WX_SVG_T_SPAN_ELEMENT_H
#define WX_SVG_T_SPAN_ELEMENT_H

#include "SVGTextPositioningElement.h"
#include "String_wxsvg.h"
#include "Element.h"

class wxSVGTSpanElement:
  public wxSVGTextPositioningElement
{
  public:
    wxSVGTSpanElement(std::wstring tagName = _T("tspan")):
      wxSVGTextPositioningElement(tagName) {}
    virtual ~wxSVGTSpanElement() {}
    wxSvgXmlNode* CloneNode(bool deep = true) { return new wxSVGTSpanElement(*this); }
    bool HasAttribute(const std::wstring& name);
    std::wstring GetAttribute(const std::wstring& name);
    bool SetAttribute(const std::wstring& name, const std::wstring& value);
    wxSvgXmlAttrHash GetAttributes() const;
    virtual wxSVGDTD GetDtd() const { return wxSVG_TSPAN_ELEMENT; }
};

#endif // WX_SVG_T_SPAN_ELEMENT_H
