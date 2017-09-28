#include "stdafx.h"
#include "CButtonST.h"
#ifdef __WTLBUILDER__
namespace DecorativeCtrl
{
   typedef long HorizAlignButtonSTStyle;
   typedef long ButtonSTStyle;
   static void RegisterButtonSTStyles();

   REGISTER_COMPONENT_EX(CButtonST,CButtonSTComp,DecorativeCtrl,IDB_BUTTONST)
      
   CButtonSTComp::CButtonSTComp(LPTSTR _name):ControlComponent<DecorativeCtrl::CButtonSTComp>(_name)
   {
      RegisterButtonSTStyles();
	  SetDefaultSize(85,22);
   }
   
   
   CButtonSTComp::~CButtonSTComp(void)
   {
   }
   
   BOOL CButtonSTComp::CreateComponent(Component * _Parent)
   {
		SetComponentParent(_Parent);
		Create((HWND)_Parent->GetHandle(),GetBoundsRect(),get_Caption(),get_InternalWindowStyle(),get_InternalWindowStyleEx());
		return ::IsWindow(m_hWnd);
   }
   
   void CButtonSTComp::InitProperty(void)
   {
      inImage.Change.SetObject(this);
      inImage.Change.SetMethod(&CButtonSTComp::OnInImageChange);
      
      outImage.Change.SetObject(this);
      outImage.Change.SetMethod(&CButtonSTComp::OnOutImageChange);
      
      ControlComponent<CButtonSTComp>::InitProperty();
	   
	  SET_PROP_VALUE(InternalWindowStyle, CButtonSTWinTraits::GetWndStyle(0))
	  SET_PROP_VALUE(InternalWindowStyleEx, CButtonSTWinTraits::GetWndExStyle(0))
	  ADD_WIN_STYLE(BS_OWNERDRAW | WS_VISIBLE)

      //DEFINE_PROPERTY(Style,ButtonSTStyle,CButtonSTComp,0)
      DEFINE_PROPERTY(Flat,BOOL,CButtonSTComp,FALSE)
      //DEFINE_PROPERTY(Transparent,BOOL,CButtonSTComp,FALSE)
      DEFINE_PROPERTY(Caption,CString,CButtonSTComp,get_Name())
      DEFINE_PROPERTY(BkColorIn,CColorref,CButtonSTComp,COLOR_BTNFACE)
      DEFINE_PROPERTY(TextColorIn,CColorref,CButtonSTComp,COLOR_WINDOWTEXT)
      DEFINE_PROPERTY(BkColorOut,CColorref,CButtonSTComp,COLOR_BTNFACE)
      DEFINE_PROPERTY(TextColorOut,CColorref,CButtonSTComp,COLOR_WINDOWTEXT)
      DEFINE_PROPERTY(EnablePressed,bool,CButtonSTComp,false)
      DEFINE_PROPERTY(Pressed,bool,CButtonSTComp,false)
      DEFINE_PROPERTY(Alignment,HorizAlignButtonSTStyle,CButtonSTComp,(long)GetAlign())

      inImage.AddProperty(_T("InImage"),objprop);
      outImage.AddProperty(_T("OutImage"),objprop);
   }

   void CButtonSTComp::OnInImageChange(CImage * )
   {
       if((HBITMAP)inImage)
           SetBitmaps((HBITMAP)inImage,RGB(0,0,0),(HBITMAP)outImage,RGB(0,0,0));
       else
           if((HICON)inImage)
               SetIcon((HICON)inImage,(HICON)outImage);
           SetModified();
   }

   void CButtonSTComp::OnOutImageChange(CImage *)
   {
       if((HBITMAP)outImage)
           SetBitmaps((HBITMAP)inImage,0,(HBITMAP)outImage,0);
       else
           if((HICON)outImage)
               SetIcon((HICON)inImage,(HICON)outImage);
           SetModified();
   }


   /*void CButtonSTComp::set_Style(long val)
   {
       windowStyle&=~(BS_OWNERDRAW|BS_CHECKBOX);
       windowStyle|=val;
       m_bIsCheckBox = (val & BS_CHECKBOX) == BS_CHECKBOX;
       set_InternalWindowStyle(windowStyle);
       ModifyStyle(0,BS_OWNERDRAW);
   }
   
   long CButtonSTComp::get_Style(void)
   {
       return m_bIsCheckBox==TRUE ? BS_CHECKBOX : BS_PUSHBUTTON;
       //return (GetStyle() & BS_CHECKBOX) == BS_CHECKBOX ? BS_CHECKBOX : BS_PUSHBUTTON;
   }
*/
   void CButtonSTComp::set_Caption(CString str)
   {
      caption.Empty();
      caption=(LPCTSTR)str;
      if(IsWindow())
         SetWindowText((LPCTSTR)caption);
      SetModified();
   }
   
   CString CButtonSTComp::get_Caption(void)
   {
      if(state.GetBit(csLoading))
      {
         caption= GET_PROP_VALUE(CString, Caption)
      }
      return caption;
   }

   void CButtonSTComp::set_Flat(BOOL val)
   {
      SetFlat(val==TRUE);
      SetModified();
   }
   
   BOOL CButtonSTComp::get_Flat(void)
   {
      return GetFlat()==true;
   }

   void CButtonSTComp::set_BkColorIn(CColorref val)
   {
      BkColorIn=val;
      SetColor(BTNST_COLOR_BK_IN,BkColorIn);
      SetModified();
   }
   
   CColorref CButtonSTComp::get_BkColorIn(void)
   {
      return BkColorIn;
   }

   void CButtonSTComp::set_TextColorIn(CColorref val)
   {
      TextColorIn=val;
      SetColor(BTNST_COLOR_FG_IN,TextColorIn);
      SetModified();
   }
   
   CColorref CButtonSTComp::get_TextColorIn(void)
   {
      return TextColorIn;
   }

   void CButtonSTComp::set_BkColorOut(CColorref val)
   {
      BkColorOut=val;
      SetColor(BTNST_COLOR_BK_OUT,BkColorOut);
      SetModified();
   }
   
   CColorref CButtonSTComp::get_BkColorOut(void)
   {
      return BkColorOut;
   }
   
   void CButtonSTComp::set_TextColorOut(CColorref val)
   {
      TextColorOut=val;
      SetColor(BTNST_COLOR_FG_OUT,TextColorOut);
      SetModified();
   }
   
   CColorref CButtonSTComp::get_TextColorOut(void)
   {
      return TextColorOut;
   }
   
   void CButtonSTComp::set_Transparent(BOOL val)
   {
      DrawTransparent(val==TRUE);
      drawTransparent=val;
      SetModified();
   }
   
   BOOL CButtonSTComp::get_Transparent(void)
   {
      return drawTransparent;
   }

   void CButtonSTComp::set_Alignment(long val)
   {
      SetAlign((CButtonST::Alignment)val);
      SetModified();
   }
   
   long CButtonSTComp::get_Alignment(void)
   {
      return (long)GetAlign();
   }

   void CButtonSTComp::set_Pressed(bool val)
   {
       if(val != GetPressed())
       {
            
            SetPressed(val);
            SetModified();
       }
   }

   bool CButtonSTComp::get_Pressed()
   {
        return GetPressed();
   }

   void CButtonSTComp::set_EnablePressed(bool val)
   {
       if(val != m_enablePressedState)
       {
           EnablePressedState(val);
           SetModified();
       }
   }

   bool CButtonSTComp::get_EnablePressed()
   {
       return m_enablePressedState;
   }
   
//////////////////////////////////////////////////////////////////////////
BEGIN_LIST_PROPERTY(HorizAlignButtonSTStyle)
    LIST_ITEM_DECORATE(CButtonST::ST_ALIGN_HORIZ,CButtonST::ST_ALIGN_HORIZ,Horiz)
    LIST_ITEM_DECORATE(CButtonST::ST_ALIGN_VERT,CButtonST::ST_ALIGN_VERT,Vert)
    LIST_ITEM_DECORATE(CButtonST::ST_ALIGN_HORIZ_RIGHT,CButtonST::ST_ALIGN_HORIZ_RIGHT,Right)
END_LIST_ITEM(HorizAlignButtonSTStyle)

/*BEGIN_LIST_PROPERTY(ButtonSTStyle)
   LIST_ITEM_DECORATE(BS_PUSHBUTTON,BS_PUSHBUTTON,PushButton)
   LIST_ITEM_DECORATE(BS_CHECKBOX,BS_CHECKBOX,CheckBox)
END_LIST_ITEM(ButtonSTStyle)
*/   
   static void RegisterButtonSTStyles()
   {
      static BOOL IsInited=FALSE;
      if(IsInited==TRUE)
         return;
      
      REGISTER_LIST_PROPERTY(HorizAlignButtonSTStyle)
      //REGISTER_LIST_PROPERTY(ButtonSTStyle)
      IsInited=TRUE;
   }
   
};
#endif