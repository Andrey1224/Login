#include <FL/Fl.H>
#include <FL/fl_message.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Box.H>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function prototypes
void open_login_window(Fl_Widget*, void*);
void open_register_window(Fl_Widget*, void*);
void process_login(Fl_Widget*, void*);
void process_register(Fl_Widget*, void*);
bool check_credentials(const string&, const string&);
bool save_user(const string&, const string&);
bool is_username_taken(const string&);

// Callback to close the program when the main window is closed
void on_main_window_close(Fl_Widget*, void*) {
    cout << "Closing all windows and exiting program..." << endl;
    exit(0);
}

// Main window
void main_window() {
    Fl_Window* window = new Fl_Window(400, 300, "Login or Register");
    window->callback(on_main_window_close);

    Fl_Box* box = new Fl_Box(0, 50, 400, 50, "Login or Register");
    box->labelfont(FL_BOLD);
    box->labelsize(20);

    Fl_Button* login_btn = new Fl_Button(100, 150, 200, 30, "Login");
    login_btn->callback(open_login_window);

    Fl_Button* register_btn = new Fl_Button(100, 200, 200, 30, "Register New Account");
    register_btn->callback(open_register_window);

    window->end();
    window->show();
}

// Login window
void login_window() {
    Fl_Window* window = new Fl_Window(400, 300, "Login");

    Fl_Input* username_input = new Fl_Input(100, 100, 200, 30, "Username:");
    Fl_Input* password_input = new Fl_Input(100, 150, 200, 30, "Password:");
    password_input->type(FL_SECRET_INPUT);

    Fl_Button* login_btn = new Fl_Button(150, 200, 100, 30, "Login");
    login_btn->callback(process_login, new pair<Fl_Input*, Fl_Input*>(username_input, password_input));

    window->end();
    window->show();
}

// Registration window
void register_window() {
    Fl_Window* window = new Fl_Window(400, 500, "Register New Account");

    Fl_Input* username_input = new Fl_Input(100, 100, 200, 30, "Username:");
    Fl_Input* password_input = new Fl_Input(100, 150, 200, 30, "Password:");
    password_input->type(FL_SECRET_INPUT);

    Fl_Box* requirements_box = new Fl_Box(50, 200, 300, 120,
        "Password Requirements:\n"
        "- At least 8 characters\n"
        "- At least 1 uppercase letter\n"
        "- At least 1 lowercase letter\n"
        "- At least 1 digit\n"
        "- At least 1 special character (@, #, etc.)");
    requirements_box->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    requirements_box->labelfont(FL_ITALIC);
    requirements_box->labelsize(12);

    Fl_Button* register_btn = new Fl_Button(150, 350, 100, 30, "Register");
    register_btn->callback(process_register, new pair<Fl_Input*, Fl_Input*>(username_input, password_input));

    window->end();
    window->show();
}

// Processes login logic
void process_login(Fl_Widget*, void* data) {
    auto inputs = static_cast<pair<Fl_Input*, Fl_Input*>*>(data);
    string username = inputs->first->value();
    string password = inputs->second->value();

    if (username.empty() || password.empty()) {
        fl_message("Both username and password fields must be filled!");
        return;
    }

    if (check_credentials(username, password)) {
        fl_message("Login successful!");
    } else {
        fl_message("Invalid username or password!");
    }
}

// Validates password requirements
bool is_valid_password(const string& password) {
    if (password.length() < 8) {
        fl_message("Password must be at least 8 characters long.");
        return false;
    }

    bool has_upper = false, has_lower = false, has_digit = false, has_special = false;

    for (char ch : password) {
        if (isupper(ch)) has_upper = true;
        if (islower(ch)) has_lower = true;
        if (isdigit(ch)) has_digit = true;
        if (ispunct(ch)) has_special = true;
    }

    if (!has_upper) fl_message("Password must contain at least one uppercase letter.");
    if (!has_lower) fl_message("Password must contain at least one lowercase letter.");
    if (!has_digit) fl_message("Password must contain at least one digit.");
    if (!has_special) fl_message("Password must contain at least one special character (e.g., @, #, _).");

    return has_upper && has_lower && has_digit && has_special;
}

// Handles registration logic
void process_register(Fl_Widget* widget, void* data) {
    auto inputs = static_cast<pair<Fl_Input*, Fl_Input*>*>(data);

    string username = inputs->first->value();
    string password = inputs->second->value();

    Fl_Window* current_window = widget->window();

    if (username.empty()) {
        fl_message("Username cannot be empty!");
        return;
    }

    while (!is_valid_password(password)) {
        fl_message("Invalid password. Please try again!");
        inputs->second->value("");
        return;
    }

    if (is_username_taken(username)) {
        fl_message("Username is already taken!");
        return;
    }

    if (save_user(username, password)) {
        fl_message("Registration successful!");
        current_window->hide();
    } else {
        fl_message("Failed to save user data!");
    }
}

// Checks credentials
bool check_credentials(const string& username, const string& password) {
    ifstream file("users.txt");
    if (!file) return false;

    string line;
    while (getline(file, line)) {
        size_t delimiter = line.find(',');
        string stored_username = line.substr(0, delimiter);
        string stored_password = line.substr(delimiter + 1);

        if (stored_username == username && stored_password == password) {
            return true;
        }
    }
    return false;
}

// Saves user to file
bool save_user(const string& username, const string& password) {
    ofstream file("users.txt", ios::app);
    if (!file) return false;

    file << username << "," << password << endl;
    return true;
}

// Checks if username is taken
bool is_username_taken(const string& username) {
    ifstream file("users.txt");
    if (!file) return false;

    string line;
    while (getline(file, line)) {
        size_t delimiter = line.find(',');
        string stored_username = line.substr(0, delimiter);

        if (stored_username == username) {
            return true;
        }
    }
    return false;
}

// Opens login window
void open_login_window(Fl_Widget*, void*) {
    login_window();
}

// Opens registration window
void open_register_window(Fl_Widget*, void*) {
    register_window();
}

// Main function
int main(int argc, char** argv) {
    main_window();
    return Fl::run();
}
