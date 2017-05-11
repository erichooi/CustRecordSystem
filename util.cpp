#include <iostream>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
void show_dialog(std::string message)
{
	int msgboxID = MessageBox(
		NULL,
		message.c_str(),
		"Warning",
		MB_ICONEXCLAMATION | MB_OK | MB_DEFBUTTON1 | MB_SYSTEMMODAL
	);
}

void clrscreen() 
{
    std::system("cls");
}

void sleep()
{
    Sleep(500);
}
#else
#include <gtkmm/messagedialog.h>
void show_dialog(std::string message)
{
    auto app = Gtk::Application::create();
    Gtk::MessageDialog dialog(message.c_str());
    int result = dialog.run();
    switch (result) {
        case(Gtk::RESPONSE_OK):
            dialog.hide();
            break;
    }
    app->run();
}

void clrscreen()
{
	std::system("clear");
}

void sleep()
{
    sleep(5);
}
#endif

int quit_loop()
{
    std::cout << "\n\n";
    std::cout << "Press q to quit or ENTER to continue...\n";
    if (std::getchar() == 113) {
        return 1;
    } 
    return 0;
}

int tokenize(std::string& str, std::vector<std::string>& v, std::string delimiter)
{
    v.clear();
    std::size_t prev_pos = 0, pos;
    while ((pos = str.find_first_of(delimiter, prev_pos)) != std::string::npos) {
        if (pos > prev_pos) {
            v.push_back(str.substr(prev_pos, pos-prev_pos));
            prev_pos = pos + 1;
        }
    }
    if (prev_pos < str.length()) {
        v.push_back(str.substr(prev_pos, std::string::npos));
    }
    return 1;
}
