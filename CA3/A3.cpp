#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Class;

class Student
{
public:
    Student(string id, string name);

    string get_student_id() { return student_id; }
    string get_student_name() { return student_name; }
    void enroll_in_class(Class *class_);
    void remove_from_registered_class(Class *class_);
    void wait_in_queue(Class *class_);
    void remove_from_waiting_queue_classes(Class *class_);
    void registration_status();

private:
    string student_id;
    string student_name;
    vector<Class *> registered_classes;
    vector<Class *> waiting_queue_classes;
};

Student::Student(string id, string name)
{
    if (id.size() < 6)
        exit(0);

    for (int i = 0; i < name.size(); i++)
        if (name[i] == ' ')
            exit(0);

    student_id = id;
    student_name = name;
}

void Student::enroll_in_class(Class *class_)
{
    registered_classes.push_back(class_);
}

void Student::remove_from_registered_class(Class *class_)
{
    auto it = find(registered_classes.begin(), registered_classes.end(), class_);

    registered_classes.erase(it);
}

void Student::wait_in_queue(Class *class_)
{
    waiting_queue_classes.push_back(class_);
}

void Student::remove_from_waiting_queue_classes(Class *class_)
{
    auto it = find(waiting_queue_classes.begin(), waiting_queue_classes.end(), class_);

    waiting_queue_classes.erase(it);
}

class Class
{
public:
    Class(string code, string title, string capacity);

    string get_class_code() { return class_code; }
    string get_class_title() { return class_title; }
    int get_capacity() { return class_capacity; }
    int get_registered_students_num() { return registered_students.size(); }
    int get_in_waiting_queue_students_num() { return in_waiting_queue_students.size(); }

    void add_student_to_class(Student *student);

    void drop_student_from_class(Student *student);

    void set_capacity(int capacity);

    bool has_student(Student *student);

private:
    string class_code;
    string class_title;
    int class_capacity;
    vector<Student *> registered_students;
    vector<Student *> in_waiting_queue_students;
};

Class::Class(string code, string title, string capacity)
{
    if (code.size() != 2 || stoi(capacity) < 0 || title.size() == 0)
        exit(0);
    for (int i = 0; i < title.size(); i++)
        if (title[i] == ' ')
            exit(0);

    class_code = code;
    class_title = title;
    class_capacity = stoi(capacity);
}

bool Class::has_student(Student *student)
{
    for (int i = 0; i < registered_students.size(); i++)
    {
        if (registered_students[i]->get_student_id() == student->get_student_id())
            return true;
    }
    for (int i = 0; i < in_waiting_queue_students.size(); i++)
    {
        if (in_waiting_queue_students[i]->get_student_id() == student->get_student_id())
            return true;
    }
    return false;
}

void Class::add_student_to_class(Student *student)
{
    if (has_student(student))
        return;

    if (registered_students.size() < class_capacity)
    {
        registered_students.push_back(student);
        student->enroll_in_class(this);
    }
    else
    {
        in_waiting_queue_students.push_back(student);
        student->wait_in_queue(this);
    }
}

void Class::drop_student_from_class(Student *student)
{

   if (!has_student(student))
        return;

    vector<Student *>::iterator it = find(registered_students.begin(), registered_students.end(), student);

    if (it != registered_students.end())
    {
        registered_students.erase(it);
        student->remove_from_registered_class(this);
        if (in_waiting_queue_students.size() == 0)
            return;

        Student* n_student = in_waiting_queue_students.front();
        n_student->remove_from_waiting_queue_classes(this);
        n_student->enroll_in_class(this);

        registered_students.push_back(in_waiting_queue_students.front());
        in_waiting_queue_students.erase(in_waiting_queue_students.begin());
        return;
    }

    vector<Student *>::iterator itw = find(in_waiting_queue_students.begin(), in_waiting_queue_students.end(), student);

    if (itw != in_waiting_queue_students.end())
    {
        in_waiting_queue_students.erase(itw);
        student->remove_from_waiting_queue_classes(this);
    }
}

void Class::set_capacity(int new_capacity)
{
    if (new_capacity < 0)
        return;

    if (new_capacity > class_capacity)
    {
        
        while (new_capacity > registered_students.size() && in_waiting_queue_students.size() > 0)
        {
            Student *s = in_waiting_queue_students.front();
            s->remove_from_waiting_queue_classes(this);
            s->enroll_in_class(this);
            
            registered_students.push_back(in_waiting_queue_students.front());
            in_waiting_queue_students.erase(in_waiting_queue_students.begin());
        }
        
    }

    class_capacity = new_capacity;
}

void Student::registration_status()
{
    cout << student_name << ":"<< endl;
    for (int i = 0; i < registered_classes.size(); i++)
        cout << registered_classes[i]->get_class_title() << endl;
    for (int i = 0; i < waiting_queue_classes.size(); i++)
        cout << waiting_queue_classes[i]->get_class_title() << "(w)" << endl;
}

class University
{

public:
    University(){};
    void load_std(int number);
    void load_cla(int number);
    void run_order();
    Student *find_student(string student_id);
    Class *find_class(string class_code);
    void report_classes();

private:
    vector<Student *> save_students;
    vector<Class *> save_classes;
};

Student *University::find_student(string student_id)
{
    for (int i = 0; i < save_students.size(); i++)
    {
        if (save_students[i]->get_student_id() == student_id)
            return save_students[i];
    }
    return nullptr;
}

Class *University::find_class(string class_code)
{
    for (int i = 0; i < save_classes.size(); i++)
    {
        if (save_classes[i]->get_class_code() == class_code)
            return save_classes[i];
    }
    return nullptr;
}

void University::load_std(int number)
{
    cin >> number;
    string s_id;
    string s_name;

    for (int i = 0; i < number; i++)
    {
        cin >> s_id >> s_name;

        Student *sinfo = new Student(s_id, s_name);
        save_students.push_back(sinfo);
    }
}

void University::load_cla(int number)
{
    cin >> number;
    string c_code;
    string c_title;
    string c_capacity;

    for (int i = 0; i < number; i++)
    {
        cin >> c_code >> c_title >> c_capacity;

        Class *cinfo = new Class(c_code, c_title, c_capacity);
        save_classes.push_back(cinfo);
    }
}

void University::report_classes()
{
    for (int i = 0; i < save_classes.size(); i++)
    {

        cout << save_classes[i]->get_class_title() << ": " << save_classes[i]->get_registered_students_num()
             << "(" << save_classes[i]->get_in_waiting_queue_students_num() << ")"<< endl;
    }

    cout << endl;
}

void University::run_order()
{
    string command;
    while (cin >> command)
    {
        if (command == "add")
        {
            string s_id, c_code;
            cin >> s_id >> c_code;
            Student *s = find_student(s_id);
            Class *c = find_class(c_code);
            if (s == nullptr || c == nullptr)
                continue;

            c->add_student_to_class(s);
        }
        else if (command == "drop")
        {
            string s_id, c_code;
            cin >> s_id >> c_code;
            Student *s = find_student(s_id);
            Class *c = find_class(c_code);
            if (s == nullptr || c == nullptr)
                continue;

            c->drop_student_from_class(s);
        }
        else if (command == "setcap")
        {
            int capacity;
            string c_code;
            cin >> c_code >> capacity;
            Class *cl = find_class(c_code);
            if (cl == nullptr)
                continue;
            cl->set_capacity(capacity);
        }
        else if (command == "report")
        {
            report_classes();
        }
        else if (command == "student")
        {
            string s_id;
            cin >> s_id;
            Student *s = find_student(s_id);
            s->registration_status();
        }
    }
}

int main()
{
    University university;
    int num;
    university.load_std(num);
    university.load_cla(num);
    university.run_order();
}
