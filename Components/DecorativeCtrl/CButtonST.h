#pragma once

#include <ButtonST.h>

#ifdef __WTLBUILDER__
namespace DecorativeCtrl
{
   class CButtonSTComp:public CButtonST,public ControlComponent<DecorativeCtrl::CButtonSTComp>
   {
      CImage inImage;
      CImage outImage;

      CColorref BkColorIn;
      CColorref TextColorIn;
      CColorref BkColorOut;
      CColorref TextColorOut;
      BOOL      drawTransparent;
         
      CString caption;
      void OnInImageChange(CImage *);
      void OnOutImageChange(CImage *);
      
   public:
      CButtonSTComp(LPTSTR _name=NULL);
      ~CButtonSTComp(void);
      
      virtual BOOL CreateComponent(Component *);
      BEGIN_MSG_MAP_EX(CButtonSTComp)
         CHAIN_MSG_MAP(ControlComponent<CButtonSTComp>)
         CHAIN_MSG_MAP(CButtonST)
      END_MSG_MAP()
         
      virtual void InitProperty(void);

      //DECLARE_PROPERTY(Style,long)  
      DECLARE_PROPERTY(Caption,CString)	
      DECLARE_PROPERTY(Flat,BOOL)
      
      DECLARE_PROPERTY(BkColorIn,CColorref)
      DECLARE_PROPERTY(TextColorIn,CColorref)
      DECLARE_PROPERTY(BkColorOut,CColorref)
      DECLARE_PROPERTY(TextColorOut,CColorref)

      DECLARE_PROPERTY(Transparent,BOOL)
      DECLARE_PROPERTY(Alignment,long)
      DECLARE_PROPERTY(Pressed,bool)
      DECLARE_PROPERTY(EnablePressed,bool)
      
   };
};
#endif   

