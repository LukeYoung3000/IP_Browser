#include "cNotebook.h"

wxBEGIN_EVENT_TABLE(cNotebook, wxNotebook)
	EVT_CHOICE(20001, OnNetworkSelect)
	EVT_CHOICE(20002, OnDeviceSelect)
wxEND_EVENT_TABLE()

cNotebook::cNotebook(wxWindow * parent) : wxNotebook(parent, 10001)
{

	// 1. Tab Setup
	tab_net = new wxNotebookPage(this, -1);
	tab_dev = new wxNotebookPage(this, -1);

	this->AddPage(tab_net, "Network");
	this->AddPage(tab_dev, "Device");

	sqlite.db_path_ = "ip.db";



	// 2. Network Tab Setup

	// Use SQLite To Get The List Of Networks
	wxArrayString choices;
	GetNetworks(choices);

	// Populate Choice Elements - Test
	//wxArrayString choices; choices.Add("Test 0"); choices.Add("Test 1"); choices.Add("Test 2"); choices.Add("Test 0");

	// Choice Box
	new wxStaticText(tab_net, wxID_ANY, "Select Network:", wxPoint(10, 10), wxSize(200, 20)); // Text (Above Choice Box)
	c_net_select = new wxChoice(tab_net, 20001, wxPoint(10,40), wxSize(200,40), choices);

	// Network Information
	new wxStaticText(tab_net, wxID_ANY, "Network ID:", wxPoint(10, 80), wxSize(200, 20));
	st_netid = new wxStaticText(tab_net, wxID_ANY, "----", wxPoint(10, 110), wxSize(200, 20));
	new wxStaticText(tab_net, wxID_ANY, "Subnet Mask:", wxPoint(10, 140), wxSize(200, 20));
	st_subnet = new wxStaticText(tab_net, wxID_ANY, "----", wxPoint(10, 170), wxSize(200, 20));

	// List Control
	lc_net_display = new wxListCtrl(tab_net, wxID_ANY, wxPoint(220, 40), wxSize(400, 300), wxLC_REPORT);  
	lc_net_display->InsertColumn(0, "Device Name", wxLIST_FORMAT_LEFT, 200);
	lc_net_display->InsertColumn(1, "IP Address", wxLIST_FORMAT_LEFT, 100);
	lc_net_display->InsertColumn(2, "Subnet Mask", wxLIST_FORMAT_LEFT, 100);




	// 3. Device Tab Setup

	// Use SQLite To Get A List Of Devices
	choices.clear();
	GetDevices(choices);

	// Choice Box
	new wxStaticText(tab_dev, wxID_ANY, "Select Device:", wxPoint(10, 10), wxSize(200, 20)); // Text (Above Choice Box)
	c_dev_select = new wxChoice(tab_dev, 20002, wxPoint(10, 40), wxSize(200, 40), choices);

	// List Control
	lc_dev_display = new wxListCtrl(tab_dev, wxID_ANY, wxPoint(220, 40), wxSize(400, 300), wxLC_REPORT);
	lc_dev_display->InsertColumn(0, "Network Name", wxLIST_FORMAT_LEFT, 200);
	lc_dev_display->InsertColumn(1, "IP Address", wxLIST_FORMAT_LEFT, 100);
	lc_dev_display->InsertColumn(2, "Subnet Mask", wxLIST_FORMAT_LEFT, 100);




	this->Layout();

}

cNotebook::~cNotebook()
{
}

void cNotebook::OnNetworkSelect(wxCommandEvent & evt)
{
	wxString net_name = evt.GetString();

	// Get Network Info From SQLite DB
	wxString query = wxString::Format("SELECT network_id,subnet_mask FROM networks WHERE name = \"%s\" ;", net_name);
	LSY::SQLite3::Table sql_tab;
	if (!sqlite.GetTable(query.ToStdString(), sql_tab))
		return;

	// Populate Information
	st_netid->SetLabelText(wxString(sql_tab.data[0][0]));
	st_subnet->SetLabelText(wxString(sql_tab.data[0][1]));


	// Get IP Addresses and Device Names From SQLite DB
	query = wxString::Format("SELECT device_name,ip_address,subnet_mask FROM ips WHERE network_name = \"%s\" ;", net_name);
	sql_tab.clear();
	if (!sqlite.GetTable(query.ToStdString(), sql_tab))
		return;

	// Populate List Control
	lc_net_display->DeleteAllItems();
	for (int i = 0; i < sql_tab.num_rows(); i++)
	{
		int j = lc_net_display->InsertItem(0, wxString(sql_tab.data[i][0]));	// Device Name
		lc_net_display->SetItem(j, 1, wxString(sql_tab.data[i][1]));			// IP Address
		lc_net_display->SetItem(j, 2, wxString(sql_tab.data[i][2]));			// Subnet Mask
	}

	evt.Skip();
}

void cNotebook::OnDeviceSelect(wxCommandEvent & evt)
{
	wxString dev_name = evt.GetString();

	// Get IP Addresses and Device Names From SQLite DB
	wxString query = wxString::Format("SELECT network_name,ip_address,subnet_mask FROM ips WHERE device_name = \"%s\" ;", dev_name);
	LSY::SQLite3::Table sql_tab;
	if (!sqlite.GetTable(query.ToStdString(), sql_tab))
		return;

	// Populate List Control
	lc_dev_display->DeleteAllItems();
	for (int i = 0; i < sql_tab.num_rows(); i++)
	{
		int j = lc_dev_display->InsertItem(0, wxString(sql_tab.data[i][0]));	// Network Name
		lc_dev_display->SetItem(j, 1, wxString(sql_tab.data[i][1]));			// IP Address
		lc_dev_display->SetItem(j, 2, wxString(sql_tab.data[i][2]));			// Subnet Mask
	}

	evt.Skip();
}



bool cNotebook::GetNetworks(wxArrayString &networks)
{
	LSY::SQLite3::Table table;
	if (!sqlite.GetTable("SELECT name FROM networks;", table))
		return false;

	// Populate Array String
	networks.clear();
	for (int i = 0; i < table.num_rows(); i++)
		networks.Add(wxString(table.data[i][0]));

	return true;
}

bool cNotebook::GetDevices(wxArrayString &devices)
{
	LSY::SQLite3::Table table;
	if (!sqlite.GetTable("SELECT name FROM devices;", table))
		return false;

	// Populate Array String
	devices.clear();
	for (int i = 0; i < table.num_rows(); i++)
		devices.Add(wxString(table.data[i][0]));

	return true;
}
