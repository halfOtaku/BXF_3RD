//////////////////////////////////////////////////////////////////////////////
// Name:        CSSValue.h
// Purpose:     
// Author:      Alex Thuering
// Created:     2005/05/03
// RCS-ID:      $Id: CSSValue.h,v 1.9 2005/11/06 17:31:36 ntalex Exp $
// Copyright:   (c) 2005 Alex Thuering
// Licence:     wxWindows licence
//////////////////////////////////////////////////////////////////////////////

#ifndef wxSVG_CSS_VALUE_H
#define wxSVG_CSS_VALUE_H

#include <wx/geometry.h>
#include "RGBColor.h"
#include "CSSValues.h"

enum wxCSS_VALUE_TYPE
{
  wxCSS_INHERIT = 0,
  wxCSS_PRIMITIVE_VALUE,
  wxCSS_VALUE_LIST,
  wxCSS_SVG_COLOR,
  wxCSS_SVG_PAINT,
  wxCSS_CUSTOM = 3
};

class wxCSSValue
{
  protected:
	wxCSS_VALUE_TYPE m_cssValueType;
  
  public:
	wxCSSValue(): m_cssValueType(wxCSS_INHERIT) {}
	wxCSSValue(wxCSS_VALUE_TYPE cssValueType): m_cssValueType(cssValueType) {}
	virtual ~wxCSSValue() {}
	
	inline wxCSS_VALUE_TYPE GetCSSValueType() const { return m_cssValueType; }
	inline void SetCSSValueType(wxCSS_VALUE_TYPE cssValueType) { m_cssValueType = cssValueType; }
	
	virtual std::wstring GetCSSText() const = 0;
	virtual wxCSSValue* Clone() const = 0;
  
  public:
	static wxCSS_VALUE GetValueId(std::wstring value);
	static std::wstring GetValueString(wxCSS_VALUE value);
};

enum wxCSS_PRIMITIVE_TYPE
{
  wxCSS_UNKNOWN    = 0,
  wxCSS_NUMBER     = 1,
  wxCSS_PERCENTAGE = 2,
  wxCSS_EMS        = 3,
  wxCSS_EXS        = 4,
  wxCSS_PX         = 5,
  wxCSS_CM         = 6,
  wxCSS_MM         = 7,
  wxCSS_IN         = 8,
  wxCSS_PT         = 9,
  wxCSS_PC         = 10,
  wxCSS_DEG        = 11,
  wxCSS_RAD        = 12,
  wxCSS_GRAD       = 13,
  wxCSS_MS         = 14,
  wxCSS_S          = 15,
  wxCSS_HZ         = 16,
  wxCSS_KHZ        = 17,
  wxCSS_DIMENSION  = 18,
  wxCSS_STRING     = 19,
  wxCSS_URI        = 20,
  wxCSS_IDENT      = 21,
  wxCSS_ATTR       = 22,
  wxCSS_COUNTER    = 23,
  wxCSS_RECT       = 24,
  wxCSS_RGBCOLOR   = 25
};

class wxCSSPrimitiveValue: public wxCSSValue
{
  protected:
	wxCSS_PRIMITIVE_TYPE m_primitiveType;
	union
	{
	  wxCSS_VALUE m_ident;
	  double m_number;
	  std::wstring* m_string;
	  wxRect* m_rect;
	  wxRGBColor* m_color;
	};
  
  public:
	wxCSSPrimitiveValue(): wxCSSValue(wxCSS_PRIMITIVE_VALUE),
      m_primitiveType(wxCSS_UNKNOWN) {}
	wxCSSPrimitiveValue(double value): wxCSSValue(wxCSS_PRIMITIVE_VALUE),
      m_primitiveType(wxCSS_NUMBER), m_number(value) {}
	wxCSSPrimitiveValue(const std::wstring& value): wxCSSValue(wxCSS_PRIMITIVE_VALUE),
      m_primitiveType(wxCSS_STRING), m_string(new std::wstring(value)) {}
	wxCSSPrimitiveValue(const wxRect& value): wxCSSValue(wxCSS_PRIMITIVE_VALUE),
      m_primitiveType(wxCSS_RECT), m_rect(new wxRect(value)) {}
	wxCSSPrimitiveValue(const wxRGBColor& value): wxCSSValue(wxCSS_PRIMITIVE_VALUE),
      m_primitiveType(wxCSS_RGBCOLOR), m_color(new wxRGBColor(value)) {}
	wxCSSPrimitiveValue(wxCSS_VALUE value): wxCSSValue(wxCSS_PRIMITIVE_VALUE),
      m_primitiveType(wxCSS_IDENT), m_ident(value) {}
	wxCSSPrimitiveValue(const wxCSSPrimitiveValue& src);
    ~wxCSSPrimitiveValue() { CleanUp(); }
	wxCSSValue* Clone() const { return new wxCSSPrimitiveValue(*this); }
	
	inline wxCSS_PRIMITIVE_TYPE GetCSSPrimitiveType() const { return m_primitiveType; }
	inline void SetCSSPrimitiveType(wxCSS_PRIMITIVE_TYPE primitiveType) { m_primitiveType = primitiveType; }
	
	std::wstring GetCSSText() const;
	
	void     SetStringValue(wxCSS_PRIMITIVE_TYPE stringType, const std::wstring& stringValue);
	std::wstring GetStringValue() const;
	
	void   SetFloatValue(wxCSS_PRIMITIVE_TYPE unitType, double floatValue);
	double GetFloatValue(wxCSS_PRIMITIVE_TYPE unitType = wxCSS_NUMBER) const;
	
	void   SetRectValue(const wxRect& rect);
	wxRect GetRectValue() const;
	
	void SetRGBColorValue(const wxRGBColor& color);
	wxRGBColor GetRGBColorValue() const;
	
	void SetIdentValue(wxCSS_VALUE ident);
	wxCSS_VALUE GetIdentValue() const;
	
  protected:
	void CleanUp();
};

#endif //wxSVG_CSS_VALUE_H

