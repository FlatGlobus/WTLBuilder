// Windows Template Library - WTL version 9.10
// Copyright (C) Microsoft Corporation, WTL Team. All rights reserved.
//
// This file is a part of the Windows Template Library.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.


function OnFinish(selProj, selObj)
{
	try
	{
		var strProjectPath = wizard.FindSymbol('PROJECT_PATH');
		var strProjectName = wizard.FindSymbol('PROJECT_NAME');

		// Create symbols based on the project name
		var strSafeProjectName = CreateSafeName(strProjectName);
		wizard.AddSymbol("SAFE_PROJECT_NAME", strSafeProjectName);
		wizard.AddSymbol("NICE_SAFE_PROJECT_NAME", strSafeProjectName.substr(0, 1).toUpperCase() + strSafeProjectName.substr(1))
		wizard.AddSymbol("UPPERCASE_SAFE_PROJECT_NAME", strSafeProjectName.toUpperCase());

		// Set current year symbol
		var d = new Date();
		var nYear = 0;
		nYear = d.getFullYear();
		if(nYear >= 2003)
			wizard.AddSymbol("WTL_CURRENT_YEAR", nYear);

		// Set APPID and LIBID symbols for COM servers
		if(wizard.FindSymbol("WTL_COM_SERVER"))
		{
			var strGuid = wizard.CreateGuid();
			var strVal = wizard.FormatGuid(strGuid, 0);
			wizard.AddSymbol("WTL_APPID", strVal);

			strGuid = wizard.CreateGuid();
			strVal = wizard.FormatGuid(strGuid, 0);
			wizard.AddSymbol("WTL_LIBID", strVal);
		}

		// Set app type symbols
		if (wizard.FindSymbol("WTL_APPTYPE_SDI") || wizard.FindSymbol("WTL_APPTYPE_MTSDI"))
		{
				wizard.AddSymbol("WTL_FRAME_BASE_CLASS","CFrameWindowImpl");
		}
		else if(wizard.FindSymbol("WTL_APPTYPE_MDI"))
		{
			wizard.AddSymbol("WTL_FRAME_BASE_CLASS", "CMDIFrameWindowImpl");
			wizard.AddSymbol("WTL_CHILD_FRAME_BASE_CLASS","CMDIChildWindowImpl");
		}
		else if(wizard.FindSymbol("WTL_APPTYPE_DLG"))
		{
			wizard.AddSymbol("WTL_MAINDLG_CLASS","CMainDlg");
			if(wizard.FindSymbol("WTL_ENABLE_AX"))
				wizard.AddSymbol("WTL_MAINDLG_BASE_CLASS", "CAxDialogImpl");
			else
				wizard.AddSymbol("WTL_MAINDLG_BASE_CLASS", "CDialogImpl");

			wizard.AddSymbol("WTL_USE_TOOLBAR", false);
			wizard.AddSymbol("WTL_USE_REBAR", false);
			wizard.AddSymbol("WTL_USE_CMDBAR", false);
			wizard.AddSymbol("WTL_USE_STATUSBAR", false);
			wizard.AddSymbol("WTL_USE_VIEW", false);
		}

		// Set view symbols
		if(wizard.FindSymbol("WTL_USE_VIEW"))
		{
			wizard.AddSymbol("WTL_VIEW_FILE", "View");
			wizard.AddSymbol("WTL_VIEW_CLASS", "CView");

			wizard.AddSymbol("WTL_VIEWTYPE_GENERIC", true);
		}

		// Create project and configurations
		selProj = CreateCustomProject(strProjectName, strProjectPath);
		AddConfigurations(selProj, strProjectName);
		AddFilters(selProj);

		var InfFile = CreateCustomInfFile();
		AddFilesToCustomProj(selProj, strProjectName, strProjectPath, InfFile);
		AddPchSettings(selProj);
		InfFile.Delete();

		selProj.Object.Save();

		// Open resource editor if not VS2005 Express
			if(wizard.FindSymbol("WTL_APPTYPE_DLG"))
			{
				var ResHelper = wizard.ResourceHelper;
				ResHelper.OpenResourceFile(strProjectPath + "\\" + strProjectName + ".rc");
				ResHelper.OpenResourceInEditor("DIALOG", "IDD_MAINDLG");
				ResHelper.CloseResourceFile();
			}
			else if(wizard.FindSymbol("WTL_USE_VIEW") && wizard.FindSymbol("WTL_VIEWTYPE_FORM"))
			{
				var strDialogID = "IDD_" + wizard.FindSymbol("UPPERCASE_SAFE_PROJECT_NAME") + "_FORM";
				var ResHelper = wizard.ResourceHelper;
				ResHelper.OpenResourceFile(strProjectPath + "\\" + strProjectName + ".rc");
				ResHelper.OpenResourceInEditor("DIALOG", strDialogID);
				ResHelper.CloseResourceFile();
			}

	}
	catch(e)
	{
		if (e.description.length != 0)
			SetErrorInfo(e);
		return e.number
	}
}

function CreateCustomProject(strProjectName, strProjectPath)
{
	try
	{
		var strProjTemplatePath = wizard.FindSymbol('PROJECT_TEMPLATE_PATH');
		var strProjTemplate = '';
		var WizardVersion = wizard.FindSymbol('WIZARD_VERSION');
		if(WizardVersion >= 10.0)
			strProjTemplate = strProjTemplatePath + '\\default.vcxproj';
		else
			strProjTemplate = strProjTemplatePath + '\\default.vcproj';

		var Solution = dte.Solution;
		var strSolutionName = "";
		if (wizard.FindSymbol("CLOSE_SOLUTION"))
		{
			Solution.Close();
			strSolutionName = wizard.FindSymbol("VS_SOLUTION_NAME");
			if (strSolutionName.length)
			{
				var strSolutionPath = strProjectPath.substr(0, strProjectPath.length - strProjectName.length);
				Solution.Create(strSolutionPath, strSolutionName);
			}
		}

		var strProjectNameWithExt = '';
		if(WizardVersion >= 10.0)
			strProjectNameWithExt = strProjectName + '.vcxproj';
		else
			strProjectNameWithExt = strProjectName + '.vcproj';

		var oTarget = wizard.FindSymbol("TARGET");
		var prj;
		if (wizard.FindSymbol("WIZARD_TYPE") == vsWizardAddSubProject)  // vsWizardAddSubProject
		{
			var prjItem = oTarget.AddFromTemplate(strProjTemplate, strProjectNameWithExt);
			prj = prjItem.SubProject;
		}
		else
		{
			prj = oTarget.AddFromTemplate(strProjTemplate, strProjectPath, strProjectNameWithExt);
		}
		return prj;
	}
	catch(e)
	{
		throw e;
	}
}

function AddFilters(proj)
{
	try
	{
		// Add the folders to your project
		var strSrcFilter = wizard.FindSymbol('SOURCE_FILTER');
		var group = proj.Object.AddFilter('Source Files');
		group.Filter = strSrcFilter;

		strSrcFilter = wizard.FindSymbol('INCLUDE_FILTER');
		group = proj.Object.AddFilter('Header Files');
		group.Filter = strSrcFilter;

		strSrcFilter = wizard.FindSymbol('RESOURCE_FILTER');
		group = proj.Object.AddFilter('Resource Files');
		group.Filter = strSrcFilter;

		strSrcFilter = wizard.FindSymbol('FORM_FILTER');
		group = proj.Object.AddFilter('Form Files');
		group.Filter = strSrcFilter;

	}
	catch(e)
	{
		throw e;
	}
}

function AddConfigurations(proj, strProjectName)
{
	try
	{
		for(var i = 0; i < proj.Object.Configurations.Count; i++)
		{
			var config = proj.Object.Configurations.Item(i + 1);

			// Check if it's Debug configuration
			var bDebug = (config.ConfigurationName.search("Debug") != -1);

			// General settings
			config.CharacterSet = charSetUnicode;

			var WizardVersion = wizard.FindSymbol('WIZARD_VERSION');
			if(bDebug)
			{
				if(WizardVersion < 8.0)
				{
					config.IntermediateDirectory = 'Debug';
					config.OutputDirectory = 'Debug';
				}

				config.ATLMinimizesCRunTimeLibraryUsage = false;
			}
			else
			{
				if(WizardVersion < 8.0)
				{
					config.IntermediateDirectory = 'Release';
					config.OutputDirectory = 'Release';
				}

				config.ATLMinimizesCRunTimeLibraryUsage = false;
			}

			if(wizard.FindSymbol("WTL_USE_VIEW") && wizard.FindSymbol("WTL_COMBO_VIEW_TYPE") == "WTL_VIEWTYPE_HTML")
				config.UseOfATL = useATLDynamic;

			// Compiler settings
			var CLTool = config.Tools('VCCLCompilerTool');
			CLTool.UsePrecompiledHeader = pchUseUsingSpecific;
			CLTool.WarningLevel = warningLevel_3;
			if(bDebug)
			{
				CLTool.RuntimeLibrary = rtMultiThreadedDebug;
				CLTool.MinimalRebuild = true;
				CLTool.DebugInformationFormat = debugEditAndContinue;
				CLTool.BasicRuntimeChecks = runtimeBasicCheckAll;
				CLTool.Optimization = optimizeDisabled;
			}
			else
			{
				CLTool.RuntimeLibrary = rtMultiThreaded;
				CLTool.ExceptionHandling = false;
				CLTool.DebugInformationFormat = debugDisabled;
			}

			var strDefines = GetPlatformDefine(config);
			strDefines += "_WINDOWS;STRICT;";
			if(bDebug)
				strDefines += "_DEBUG";
			else
				strDefines += "NDEBUG";
			CLTool.PreprocessorDefinitions = strDefines;

			// Linker settings
			var LinkTool = config.Tools('VCLinkerTool');
			LinkTool.SubSystem = subSystemWindows;
			if(bDebug)
			{
				LinkTool.LinkIncremental = linkIncrementalYes;
				LinkTool.GenerateDebugInformation = true;
			}
			else
			{
				LinkTool.LinkIncremental = linkIncrementalNo;
			}

			// Resource settings
			var RCTool = config.Tools("VCResourceCompilerTool");
			RCTool.Culture = rcEnglishUS;
			RCTool.AdditionalIncludeDirectories = "$(IntDir)";
			if(bDebug)
				RCTool.PreprocessorDefinitions = "_DEBUG";
			else
				RCTool.PreprocessorDefinitions = "NDEBUG";

			// MIDL settings
			var MidlTool = config.Tools("VCMidlTool");
			MidlTool.MkTypLibCompatible = false;
			if(IsPlatformWin32(config))
				MidlTool.TargetEnvironment = midlTargetWin32;
			if(bDebug)
				MidlTool.PreprocessorDefinitions = "_DEBUG";
			else
				MidlTool.PreprocessorDefinitions = "NDEBUG";
			MidlTool.HeaderFileName = strProjectName + ".h";
			MidlTool.InterfaceIdentifierFileName = strProjectName + "_i.c";
			MidlTool.ProxyFileName = strProjectName + "_p.c";
			MidlTool.GenerateStublessProxies = true;
			MidlTool.TypeLibraryName = "$(IntDir)/" + strProjectName + ".tlb";
			MidlTool.DLLDataFileName = "";

			// Post-build settings
			if(wizard.FindSymbol('WTL_COM_SERVER'))
			{
				var PostBuildTool = config.Tools("VCPostBuildEventTool");
				PostBuildTool.Description = "Performing registration...";
				PostBuildTool.CommandLine = "\"$(TargetPath)\" /RegServer";
			}
		}
	}
	catch(e)
	{
		throw e;
	}
}

function AddPchSettings(proj)
{
	try
	{
		var files = proj.Object.Files;
		var fStdafx = files("StdAfx.cpp");

		for(var i = 0; i < fStdafx.FileConfigurations.Count; i++)
		{
			var config = fStdafx.FileConfigurations.Item(i + 1);
			config.Tool.UsePrecompiledHeader = pchCreateUsingSpecific;
		}
	}
	catch(e)
	{
		throw e;
	}
}

function DelFile(fso, strWizTempFile)
{
	try
	{
		if (fso.FileExists(strWizTempFile))
		{
			var tmpFile = fso.GetFile(strWizTempFile);
			tmpFile.Delete();
		}
	}
	catch(e)
	{
		throw e;
	}
}

function CreateCustomInfFile()
{
	try
	{
		var fso, TemplatesFolder, TemplateFiles, strTemplate;
		fso = new ActiveXObject('Scripting.FileSystemObject');

		var TemporaryFolder = 2;
		var tfolder = fso.GetSpecialFolder(TemporaryFolder);

		var strWizTempFile = tfolder.Path + "\\" + fso.GetTempName();

		var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');
		var strInfFile = strTemplatePath + '\\Templates.inf';
		wizard.RenderTemplate(strInfFile, strWizTempFile);

		var WizTempFile = fso.GetFile(strWizTempFile);
		return WizTempFile;
	}
	catch(e)
	{
		throw e;
	}
}

function GetTargetName(strName, strProjectName)
{
	try
	{
		var strTarget = strName;
		var strResPath = "res\\";

		if(strName.substr(0, 4) == "root")
		{
			var nNameLen = strName.length;
			if(strName == "root.ico" || strName == "rootDoc.ico" || strName == "root.exe.manifest")
			{
				strTarget = strResPath + strProjectName + strName.substr(4, nNameLen - 4);
			}
			else
			{
				strTarget = strProjectName + strName.substr(4, nNameLen - 4);
			}
		}
		else if(strName == 'frame.h')
		{
			strTarget = 'MainFrm.h';
		}
		else if(strName == 'frame.cpp')
		{
			strTarget = 'MainFrm.cpp';
		}
		else if(strName == 'frame.wff')
		{
			strTarget = 'MainFrm.wff';
		}
		else if(strName == 'view.h')
		{
			strTarget = 'View.h';
		}
		else if(strName == 'view.cpp')
		{
			strTarget = 'View.cpp';
		}
		else if(strName == 'view.wff')
		{
			strTarget = 'View.wff';
		}
		else if(strName == 'toolbar.bmp')
		{
			strTarget = strResPath + strName;
		}

		return strTarget; 
	}
	catch(e)
	{
		throw e;
	}
}

function AddFilesToCustomProj(proj, strProjectName, strProjectPath, InfFile)
{
	try
	{
		var projItems = proj.ProjectItems

		var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');

		var strTpl = '';
		var strName = '';

		var strTextStream = InfFile.OpenAsTextStream(1, -2);
		while (!strTextStream.AtEndOfStream)
		{
			strTpl = strTextStream.ReadLine();
			if (strTpl != '')
			{
				strName = strTpl;
				var strTarget = GetTargetName(strName, strProjectName);
				var strTemplate = strTemplatePath + '\\' + strTpl;
				var strFile = strProjectPath + '\\' + strTarget;

				var bCopyOnly = false;  //"true" will only copy the file from strTemplate to strTarget without rendering/adding to the project
				var strExt = strName.substr(strName.lastIndexOf("."));
				if(strExt==".bmp" || strExt==".ico" || strExt==".gif" || strExt==".rtf" || strExt==".css")
					bCopyOnly = true;
				wizard.RenderTemplate(strTemplate, strFile, bCopyOnly);

				// don't add these files to the project
				if(strTarget == strProjectName + ".h" ||
				   strTarget == strProjectName + "ps.mk" ||
				   strTarget == strProjectName + "ps.def")
					continue;

				proj.Object.AddFile(strFile);
			}
		}
		strTextStream.Close();
	}
	catch(e)
	{
		throw e;
	}
}
