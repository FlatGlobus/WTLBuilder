// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __COMMANDS_H
#define __COMMANDS_H
//////////////////////////////////////////////////////////////////////////
enum Commands
{
    evStartingUp,//(void)
    evShutDown,//(void)
    evWinIniChange,//(void)
    evLoadPackages,// (void)
    evEditPackages, // (void)
    evAddMenu,//(const CMenuHandle * pMenuAdd,bTopLevel)
    evRunScript,//(LPCTSTR)
    evRunScriptFromFile,//(const LPTSTRfilename)
    evInvokeFunc,//(LPTSTRName, VARIANT* Params, LONG Count, VARIANT* RetValue)
    evLoadScriptFromFile,//(LPCSTR filename)
    evOnCommand,//(UINT commandId)
    evOutput,//(outMsg, LPCTSTR) show text in the output window with icon
    evClearOutput,//(void)
    evScriptError,
    evGetComponentInfo,//
    evCreateComponent,//
    evSendComponentInfo,
    evGetComponentBitmap,
    evGetPageBitmap,
    evIsFirstPage,
    evSelectComponent,
    evCreateForm,
    evResetSelectedComponent,
    evLoadForm,
    evSaveForm,
    evSaveAsForm,
    evGenerateLocFile,
    evFormSaved,//LPCTSTR filename
    evFormLoaded,//LPCTSTR filename
    evSaveFormAsTemplate,
    evSetActiveForm,
    evGetActiveForm,
    evGetFormFileName,
    evSetFormFileName,
    evAddForm,
    evCloseAllForms,
    evCloseForm,
    evAlignComponentsLeft,
    evAlignComponentsTop,
    evAlignComponentsRight,
    evAlignComponentsBottom,
    evAlignComponentsHoriz,
    evAlignComponentsVert,
    evMakeSameWidth,
    evMakeSameHeight,
    evMakeSameSize,
    evGoldenSectionWidth,
    evGoldenSectionHeight,
    evToParent,
    evHorizOrder,
    evHorizOrderRight,
    evVertOrder,
    evVertOrderBottom,
    evCenterGroupHoriz,
    evCenterGroupVert,
    evChangeParent,
    evAddUndo,
    evUndo,
    evCut,
    evCopy,
    evPaste,
    evDelete,
    evSelectAll,
    evShowGrid,
    evSetGridSizeX,
    evSetGridSizeY,
    evEnableUndo,
    evOnEditCommand,
    evTabIndex,
    evIsFormChanged,
    evXYCursor // CPoint
};

//for evOutput message
enum outMsg {InfoMsg=0,WarnMsg,ErrorMsg};

//////////////////////////////////////////////////////////////////////////
#endif