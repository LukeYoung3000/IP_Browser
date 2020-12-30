#pragma once

#include "wx/wx.h"
#include "cNotebook.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:

	cNotebook * nb = nullptr;

	void OnNotebookChange(wxBookCtrlEvent &evt);

	wxDECLARE_EVENT_TABLE();
};

