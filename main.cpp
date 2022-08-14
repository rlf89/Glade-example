#include <gtkmm.h>
#include <iostream>
#include <string>

Gtk::ApplicationWindow *pAppWindow = nullptr;
Gtk::Label *testDisplay = nullptr;

int ctr = 0;

static void on_button_clicked(){

	if (testDisplay){

		ctr++;

		testDisplay->set_label(std::to_string(ctr));
	}
}

int main(int argc, char **argv){

	auto app = Gtk::Application::create(argc, argv, "org.bytesunited.myproject");

	// Load the GtkBuilder file and instantiate its widgets:
	auto refBuilder = Gtk::Builder::create();

	try{

		refBuilder->add_from_resource("/org/bytesunited/myproject/mainWindow.glade");

	} catch (...){

		std::cerr << "Error loading resource mainWindow.glade" << std::endl;

		return 1;
	}

	// Get the GtkBuilder-instantiated Dialog:
	refBuilder->get_widget("main_window", pAppWindow);

	if (pAppWindow){

		// Get the GtkBuilder-instantiated Button, and connect a signal handler:
		Gtk::Button *eButton = nullptr;

		refBuilder->get_widget("e_button", eButton);
		refBuilder->get_widget("test_display", testDisplay);

		if (eButton){
			
			eButton->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
		}

		app->run(*pAppWindow);
	}

	delete pAppWindow;

	return 0;
}