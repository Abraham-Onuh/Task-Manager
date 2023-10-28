#include "Task.h"


Task* tasks[50];     //array for polymorphism; made global so they can be accessed easily by the class functions

int Task::total = 0;

void date_range(Date& input);       //used for exception handling; definition is done below

Task::Task()
{
    this->name = "";
    this->info = "";
    this->start.day = 0;
    this->start.month = 0;
    this->start.year = 0;
    this->finish.day = 0;
    this->finish.month = 0;
    this->finish.year = 0;
    this->category = 0;
    this->priority = 0;
}


string Task::getname() const
{
    return name;
}

string Task::getinfo() const
{
    return info;
}

Date Task::getstart() const
{
    return start;
}

Date Task::getfinish() const
{
    return finish;
}

char Task::getcategory() const
{
    return category;
}

char Task::getpriority() const
{
    return priority;
}


string Task::getstatus(Date today) const
{
    if (finish.day <= today.day && finish.month == today.month && finish.year == today.year)
        return "Task Completed.";

    return "Task Uncompleted";
}


string Task::namecategory(char categoryin) const
{
    string temp;

    switch (categoryin)
    {
    case 'A': temp = "University";  break;
    case 'B': temp = "Work"; break;
    case 'C': temp = "Household"; break;
    default: temp = "Trivial task"; break;
    }

    return temp;
}


void Task::begin()
{
    char symb;
    ifstream input_file;
    input_file.open("TaskRecords.txt");      //upon starting the program, we open our file/database (if one exists) to read its content 

    if (!input_file) {
        cout << "FIle does not exist yet but will be created!" << endl;
    }

    else
    {
        while(true)
        {
            input_file.ignore(255, '\n');
            getline(input_file, name);
            getline(input_file, info);
            input_file >> start.day >> symb >> start.month >> symb >> start.year;
            input_file >> finish.day >> symb >> finish.month >> symb >> finish.year;
            input_file >> category >> priority;

            if (input_file.eof())
                break;

            switch (category)
            {
            case 'A':
                tasks[total - 1] = new University(name, info, start, finish, category, priority); break;

            case 'B':
                tasks[total - 1] = new Work(name, info, start, finish, category, priority); break;

            case'C':
                tasks[total - 1] = new Household(name, info, start, finish, category, priority); break;

            default: cout << "  Input does not match available Categories. Try again" << endl; break;
         
            }
        }

        input_file.close();
    }

}

void Task::startmenu()
{
   int option;

   cout << endl << "Please before starting, enter today's date (DD, MM, YYYY): " << endl;
   cin >> present.day >> present.month >> present.year;

   do
   {
       system("cls");
       cout << "                                  =======Task Management Database======= " << endl;
       cout << "                                             Available Options:" << endl << endl;
       cout << "                                             1. Add A New Task" << endl;
       cout << "                                             2. Search For A Task (by Category and Priority)" << endl;
       cout << "                                             3. Show All Tasks" << endl;
       cout << "                                             4. Delete A Task" << endl;
       cout << "                                             5. Exit" << endl;
       cout << "                 ______________________________________________________________________________________" << endl << endl;

       cout << endl<< " Your Choice: ";

       cin >> option;

       switch (option)
       {
       case 1: addtask(); break;
       case 2: searchtask(); break;
       case 3: showtasks(); break;
       case 4: deletetask(); break;
       case 5:
       {
           for (int i = 0; i < total; i++)
           {
               delete tasks[i];         //freeing dynamically allocated memory before exiting the program
           }
           total = 0;
           cout << endl << endl;
           cout << "       Thank you for using this program!" << endl << endl;
           exit(0);
           break;
       }
       default:
       {
           cout << endl << "Please enter a valid number selection from the menu!" << endl << endl;
       }
       }

       char back;
       cout << endl << endl << "To return back to menu, press any key.";
       back = _getch();
   }

    while (option != 6);
}



void Task::addtask()
{
        char another;

        do
        {
            system("cls");
            cout << "\t\t\t    ||| NEW TASK ENTRY ||| " << endl << endl;
            cin.ignore();

            cout << " Enter Name of Task: ";
            getline(cin, name);

            cout << " Enter Task Description: ";
            getline(cin, info);

            cout << " Enter Start Date (in format DD,MM,YYYY): " << endl;
            date_range(start);

            cout << " Enter (Expected) Finish Date (in format DD,MM,YYYY): " << endl;
            date_range(finish);

            cout << " Enter Category (A,B, or C for Uni, Work or Household respectively): ";
            cin >> category;

            cout << " Enter Priority (1,2... in increasing order): ";
            cin >> priority;

            switch (category)
            {
            case 'A':
                tasks[total - 1] = new University(name, info, start, finish, category, priority); break;

            case 'B':
                tasks[total - 1] = new Work(name, info, start, finish, category, priority); break;

            case'C':
                tasks[total - 1] = new Household(name, info, start, finish, category, priority); break;

            default: cout << "  Input does not match available Categories. Try again" << endl; break;
            }

            ofstream output_file;      // (output file stream, and we give it a name -a 'handle', and the NAME of the file is in parantheses on next line)
            output_file.open("TaskRecords.txt", ios::app);     //we write to a new file or append to an existing one

            if (!output_file) 
            {
                cout << "This file could not be opened!" << endl;
            }

            else 
            {
                output_file << endl << name << endl;      //first line of file contains the name of task
                output_file << info << endl;              //second line of file contains the description of the task
                output_file << start.day << "-" << start.month << "-" << start.year << endl;       //third line of file contains the start date of task
                output_file << finish.day << "-" << finish.month << "-" << finish.year << endl;    //fourth line of file contains the end date (deadline) of task
                output_file << category << " " << priority;           //fifth line of file contains the category and priority of the task

                cout << endl << "Your entry has been saved successfully!" << endl;

                output_file.close();
            }


            cout << endl << "                   Do you want to add another Task? (y/n): ";
            cin >> another;
        } 
        
        while (another == 'y' || another == 'Y');

 }


 
void Task::searchtask()
{
    system("cls");
    cout << "\t\t\t    ||| RESULT OF SEARCH FROM TASK ENTRIES ||| " << endl << endl;

    int found = 0;
    char whichcategory, whatpriority;

    cout << "Which category of tasks are you looking for and of what priority? " << endl;
    cin >> whichcategory >> whatpriority;

    for (int i = 0; i < total; i++)
    {
        cout << endl << "Find below a list of your specified tasks: " << endl << endl;
        if (tasks[i]->getcategory() == whichcategory && tasks[i]->getpriority() == whatpriority)
        {
            found = 1;

            cout << "Task Name: " << tasks[i]->getname() << endl;
            cout << "Task Description: " << tasks[i]->getinfo() << endl;
            cout << "Start Date: " << tasks[i]->getstart().day << "-" << tasks[i]->getstart().month << "-" << tasks[i]->getstart().year << endl;
            cout << "End Date: " << tasks[i]->getfinish().day << "-" << tasks[i]->getfinish().month << "-" << tasks[i]->getfinish().year << endl;
            cout << tasks[i]->getstatus(present) << endl;
        }
    }

    if (found == 0)
    {
        cout << "No such task exists in the entries" << endl;

    }
}



 void Task::showtasks()
 {
        system("cls");
        cout << "\t\t\t    ||| TASK ENTRIES ||| " << endl << endl;

        if (total == 0)
        {
            cout << "No Tasks Entries in File!" << endl;
        }
        
        else 
        {
         
            for (int i = 0; i < total; i++) 
            {
                cout << endl;
                cout << "Task Name: " << tasks[i]->getname() << endl;
                cout << "Task Description: " << tasks[i]->getinfo() << endl;
                cout << "Start Date: " << tasks[i]->getstart().day << "-" << tasks[i]->getstart().month << "-" << tasks[i]->getstart().year << endl;
                cout << "End Date: " << tasks[i]->getfinish().day << "-" << tasks[i]->getfinish().month << "-" << tasks[i]->getfinish().year << endl;
                cout << "Category: " << tasks[i]->namecategory(tasks[i]->getcategory()) << endl;
                cout << "Priority: " << tasks[i]->getpriority() << endl;
                cout << tasks[i]->getstatus(present) << endl;
            }

        }
 }



void Task::deletetask()
{
        system("cls");
        cout << "\t\t\t    ||| DELETING A TASK ENTRY ||| " << endl <<endl;

        string taskcheck; 
        int found = 0;

        fstream input_file, output_file;
        input_file.open("TaskRecords.txt", ios::in);      //read all contents from the already existing file

        if (!input_file) 
        {
            cout << "This file could not be opened!" << endl;
        }
         
        if (total == 0)
        {
            cout << "No Tasks Entries in File." << endl;
        }

        else
        {
            cin.ignore();
            cout << endl << "Enter name of task to be deleted: " << endl;
            getline(cin, taskcheck);

            output_file.open("newTaskRecords.txt", ios::out | ios::app);    

            for (int i = 0; i < total; i++)
            {
                if (taskcheck != tasks[i]->getname())      //write to a new file only those tasks that are not the same with the task the user wants to delete
                {
                    output_file << endl << tasks[i]->getname() << endl;
                    output_file << tasks[i]->getinfo() << endl;
                    output_file << tasks[i]->getstart().day << "-" << tasks[i]->getstart().month << "-" << tasks[i]->getstart().year << endl;
                    output_file << tasks[i]->getfinish().day << "-" << tasks[i]->getfinish().month << "-" << tasks[i]->getfinish().year << endl;
                    output_file << tasks[i]->getcategory() << " " << tasks[i]->getpriority();

                }
            }

            for (int i = 0; i < total; i++)
            {
                if (taskcheck == tasks[i]->getname())
                {
                    found = 1;
                    cout << "Task found and will be deleted." << endl;

                    for (int j = i; j < total; j++)
                    {
                        tasks[j] = tasks[j + 1];         //we reorder the indices of the remaining tasks

                        if (j == total) 
                        {
                            tasks[j] = NULL;     //then the last index is set to null (freed)
                        }
                    }

                    total--;        //total number of tasks is decremented by the number of tasks deleted
                }
            }

            if (found == 0)
            {
                cout << "No such task exists in the entries" << endl;
            }

            output_file.close();
            input_file.close();

            remove("TaskRecords.txt");       // we delete the old file

            int confirm = rename("newTaskRecords.txt", "TaskRecords.txt");        //and rename the new file to the name of the old file
            if (found == 1 && confirm == 0)          
            {
                cout << "Success deleting task entry!" << endl;
            }

            else
            {
                cout << endl << " Task entry could not be deleted.";
            }
        }
        
 }



 void date_range(Date& input)      //definition of function that deals with exception handling
 {
        exceptioncheck:
        try
        {
            cin >> input.day >> input.month >> input.year;
            if (input.day < 1 || input.day > 31)
                throw 10;
            if (input.month < 1 || input.month > 12)
                throw 20;
        }

        catch (int confirm)
        {
            if (confirm == 10)
            {
                cerr << "The day in your date input is out of range of the possible days in a month!" << endl;
                cout << "            Your task will never be completed!!" << endl;
            }
            if (confirm == 20)
            {
                cerr << "The month in your date input is out of range of the possible months in a year!" << endl;
                cout << "            Your task will never be completed!!" << endl;
            }

            cin.clear();

            goto exceptioncheck;
        }
 }