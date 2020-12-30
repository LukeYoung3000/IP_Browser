#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_NOTEBOOK_PAGE_CHANGED(10001, OnNotebookChange)

wxEND_EVENT_TABLE()



cMain::cMain() : wxFrame(nullptr, wxID_ANY, "IP Browser - Luke Young", wxPoint(300,30), wxSize(660, 435))
{
	nb = new cNotebook(this);
}

cMain::~cMain()
{

}

void cMain::OnNotebookChange(wxBookCtrlEvent &evt)
{
	// This function is called when a tab page is changed
	evt.Skip();
}
