#pragma once

#include "lsy_sqlite.h"

#include "wx/wx.h"
#include "wx/notebook.h"
#include "wx/choice.h"
#include "wx/listctrl.h"
#include "wx/stattext.h"


class cNotebook : public wxNotebook
{

private:
	LSY::SQLite3 sqlite;
	bool GetNetworks(wxArrayString &networks);
	bool GetDevices(wxArrayString &devices);

public:
	cNotebook(wxWindow * parent);
	~cNotebook();

	// Event Methods
	void OnNetworkSelect(wxCommandEvent & evt);
	void OnDeviceSelect(wxCommandEvent & evt);

	wxDECLARE_EVENT_TABLE();

public:

	// Tabs
	wxNotebookPage * tab_net = nullptr;
	wxNotebookPage * tab_dev = nullptr;

	// Network Tab Objects
	wxChoice * c_net_select = nullptr;
	wxListCtrl * lc_net_display = nullptr;
	wxStaticText * st_netid = nullptr;
	wxStaticText * st_subnet = nullptr;

	// Device Tab Objects
	wxChoice * c_dev_select = nullptr;
	wxListCtrl * lc_dev_display = nullptr;



};

