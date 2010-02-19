
#undef BUILDING_QT4_GUI

#include "qt4_gui.hpp"

#include <gwenhywfar/gwenhywfar.h>
#include <gwenhywfar/gui.h>
#include <gwenhywfar/dialog.h>
#include <gwenhywfar/debug.h>

#include <qapplication.h>


static int GWENHYWFAR_CB _gwenGuiSignalHandler(GWEN_DIALOG *dlg,
					       GWEN_DIALOG_EVENTTYPE t,
					       const char *sender) {
  fprintf(stderr,
	  "Received event %d from widget [%s]\n", t, sender);

  switch(t) {
  case GWEN_DialogEvent_TypeInit:
    fprintf(stderr, "Init\n");
    GWEN_Dialog_SetCharProperty(dlg, "combo1",
				GWEN_DialogProperty_AddValue,
				0,
				"Erster Text in Combo1",
				0);
    GWEN_Dialog_SetCharProperty(dlg, "combo1",
				GWEN_DialogProperty_AddValue,
				0,
				"Zweiter Text in Combo1",
				0);

    GWEN_Dialog_SetCharProperty(dlg, "combo2",
				GWEN_DialogProperty_AddValue,
				0,
				"Erster Text in Combo2",
				0);
    GWEN_Dialog_SetCharProperty(dlg, "combo1",
				GWEN_DialogProperty_AddValue,
				0,
				"Zweiter Text in Combo2",
				0);

    GWEN_Dialog_SetCharProperty(dlg, "listbox1",
				GWEN_DialogProperty_Title,
				0,
				"Column1\tColumn2",
				0);

    GWEN_Dialog_SetCharProperty(dlg, "listbox1",
				GWEN_DialogProperty_AddValue,
				0,
				"Zeile 1 Spalte 1\tZeile 1 Spalte 2",
				0);

    GWEN_Dialog_SetCharProperty(dlg, "listbox1",
				GWEN_DialogProperty_AddValue,
				0,
				"Zeile 2 Spalte 1\tZeile 2 Spalte 2",
				0);

    GWEN_Dialog_SetIntProperty(dlg, "listbox1",
			       GWEN_DialogProperty_ColumnWidth,
			       0,
                               100,
			       0);
    GWEN_Dialog_SetIntProperty(dlg, "listbox1",
			       GWEN_DialogProperty_ColumnWidth,
			       1,
			       200,
			       0);

    GWEN_Dialog_SetIntProperty(dlg, "",
			       GWEN_DialogProperty_Width,
			       0,
			       640,
			       0);
   GWEN_Dialog_SetIntProperty(dlg, "",
			       GWEN_DialogProperty_Height,
			       0,
			       480,
			       0);

    break;

  case GWEN_DialogEvent_TypeFini:
    fprintf(stderr, "Fini\n");
    break;
  case GWEN_DialogEvent_TypeValueChanged:
    fprintf(stderr, "ValueChanged\n");
    if (strcasecmp(sender, "listbox1")==0) {
      fprintf(stderr, "Selected list entry %d\n",
	      GWEN_Dialog_GetIntProperty(dlg, "listbox1", GWEN_DialogProperty_Value, 0, -1));
    }
    break;

  case GWEN_DialogEvent_TypeActivated:
    fprintf(stderr, "Activated\n");
    if (strcasecmp(sender, "okButton")==0)
      return GWEN_DialogEvent_ResultAccept;
    else if (strcasecmp(sender, "abortButton")==0)
      return GWEN_DialogEvent_ResultReject;
    break;
  case GWEN_DialogEvent_TypeEnabled:
    fprintf(stderr, "Enabled\n");
    break;
  case GWEN_DialogEvent_TypeDisabled:
    fprintf(stderr, "Disabled\n");
    break;
  case GWEN_DialogEvent_TypeGetImagePath:
    fprintf(stderr, "GetImagePath\n");
    return GWEN_DialogEvent_ResultNotHandled;
  case GWEN_DialogEvent_TypeGetIconPath:
    fprintf(stderr, "GetIconPath\n");
    return GWEN_DialogEvent_ResultNotHandled;
  case GWEN_DialogEvent_TypeClose:
    fprintf(stderr, "Close\n");
    return GWEN_DialogEvent_ResultNotHandled;
  case GWEN_DialogEvent_TypeLast:
    fprintf(stderr, "Last, ignored\n");
    return GWEN_DialogEvent_ResultNotHandled;
  }
  return GWEN_DialogEvent_ResultHandled;
}



int test1(int argc, char **argv) {
  QApplication a(argc, argv);
  QT4_Gui *gui;
  QString lf;
  int rv;
  GWEN_XMLNODE *n;
  GWEN_XMLNODE *nDialog;
  GWEN_DIALOG *dlg;

  rv=GWEN_Init();
  if (rv) {
    DBG_ERROR_ERR(0, rv);
    return 2;
  }

  GWEN_Logger_SetLevel(0, GWEN_LoggerLevel_Info);

  /* create GUI */
  gui=new QT4_Gui();
  GWEN_Gui_SetGui(gui->getCInterface());

  n=GWEN_XMLNode_new(GWEN_XMLNodeTypeTag,"root");
  GWEN_Logger_SetLevel(0, GWEN_LoggerLevel_Debug);
  GWEN_Logger_SetLevel(GWEN_LOGDOMAIN, GWEN_LoggerLevel_Verbous);
  if (GWEN_XML_ReadFile(n, "testdialog.xml",
			GWEN_XML_FLAGS_DEFAULT |
			GWEN_XML_FLAGS_HANDLE_HEADERS)) {
    fprintf(stderr, "Error reading XML file.\n");
    return 1;
  }

  nDialog=GWEN_XMLNode_FindFirstTag(n, "dialog", NULL, NULL);
  if (nDialog==NULL) {
    fprintf(stderr, "Dialog not found in XML file\n");
    return 2;
  }

  dlg=GWEN_Dialog_new("testdialog");
  rv=GWEN_Dialog_ReadXml(dlg, nDialog);
  if (rv) {
    fprintf(stderr, "Error reading widgets from XML node: %d\n", rv);
    return 2;
  }
  GWEN_XMLNode_free(n);

  GWEN_Dialog_SetSignalHandler(dlg, _gwenGuiSignalHandler);

  rv=GWEN_Gui_ExecDialog(dlg, 0);
  fprintf(stderr, "Result: %d\n", rv);

  return 0;
}



int test2(int argc, char **argv) {
  QApplication a(argc, argv);
  QT4_Gui *gui;
  QString lf;
  int rv;
  uint32_t pid;
  int i;

  rv=GWEN_Init();
  if (rv) {
    DBG_ERROR_ERR(0, rv);
    return 2;
  }

  GWEN_Logger_SetLevel(0, GWEN_LoggerLevel_Info);

  /* create GUI */
  gui=new QT4_Gui();
  GWEN_Gui_SetGui(gui->getCInterface());


#if 0
  pid=GWEN_Gui_ProgressStart(GWEN_GUI_PROGRESS_SHOW_PROGRESS | GWEN_GUI_PROGRESS_KEEP_OPEN,
			     "Progress-Title",
			     "This is an example progress with 2 steps"
			     "<html>This is an <strong>example</strong> progress with 2 steps</html>",
			     2,
			     0);
#else
  pid=GWEN_Gui_ProgressStart(GWEN_GUI_PROGRESS_SHOW_PROGRESS | GWEN_GUI_PROGRESS_KEEP_OPEN,
			     "Progress-Title",
			     "This is an <b>example</b> progress with 2 steps",
			     2,
			     0);
#endif

  GWEN_Gui_ProgressAdvance(pid, 1);
  rv=GWEN_Gui_MessageBox(GWEN_GUI_MSG_FLAGS_TYPE_INFO,
			 "MessageBox-Title",
			 "This message box should appear in the context of the open progress dialog",
			 "Button1",
			 "Button2",
			 "Button3",
			 pid);
  GWEN_Gui_ProgressAdvance(pid, 2);
  GWEN_Gui_ProgressEnd(pid);

  return 0;
}



int main(int argc, char **argv) {
  //return test1(argc, argv);
  return test2(argc, argv);
}




