#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const std::string fname = "tasks.txt";
struct Task
{
    std::string desc;
    bool done;

    Task(std::string d, bool dn = false)
        : desc(d), done(dn) {}
};

void saveToFile(const std::vector<Task> &tasks)
{
    std::ofstream outFile(fname);

    if (!outFile.is_open())
    {
        std::cout << "error: could not save to file.\n";
        return;
    }

    for (const Task &task : tasks)
    {
        outFile << (task.done ? 1 : 0) << "|" << task.desc << "\n";
    }

    outFile.close();
    std::cout << "saved " << tasks.size() << " task(s) to " << fname << "\n";
}

void loadFromFile(std::vector<Task> &tasks)
{
    std::ifstream inFile(fname);
    if (!inFile.is_open())
    {
        return;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        size_t pipePos = line.find('|');

        if (pipePos == std::string::npos)
        {
            continue;
        }

        char statusChar = line[0];
        bool done = (statusChar == '1');
        std::string desc = line.substr(pipePos + 1);
        tasks.push_back(Task(desc, done));
    }

    inFile.close();
}

void listTasks(const std::vector<Task> &tasks)
{
    std::cout << "\n your todo list \n";

    if (tasks.empty())
    {
        std::cout << "no tasks yet, add one to get started\n";
        return;
    }

    for (size_t i = 0; i < tasks.size(); i++)
    {
        std::cout << i + 1 << ". ";
        std::cout << (tasks[i].done ? "[X] " : "[ ] ");
        std::cout << tasks[i].desc << "\n";
    }
    std::cout << "\n";
}

void addTask(std::vector<Task> &tasks, const std::string &desc)
{
    tasks.push_back(Task(desc));
    std::cout << "added: " << desc << "\n";
    saveToFile(tasks);
}

void completeTask(std::vector<Task> &tasks, int n)
{
    int idx = n - 1;

    if (idx < 0 || idx >= (int)tasks.size())
    {
        std::cout << "error: task " << n << " doesn't exist.\n";
        return;
    }

    tasks[idx].done = true;
    std::cout << "completed: " << tasks[idx].desc << "\n";
    saveToFile(tasks);
}

void deleteTask(std::vector<Task> &tasks, int n)
{
    int idx = n - 1;

    if (idx < 0 || idx >= (int)tasks.size())
    {
        std::cout << "error: task " << n << " doesn't exist.\n";
        return;
    }

    std::string d = tasks[idx].desc;
    tasks.erase(tasks.begin() + idx);
    std::cout << "deleted: " << d << "\n";
    saveToFile(tasks);
}

void showUsage()
{
    std::cout << "\nusage:\n";
    std::cout << "  ./todo list              - show all tasks\n";
    std::cout << "  ./todo add \"task name\"   - add a new task\n";
    std::cout << "  ./todo complete 3        - mark task #3 as done\n";
    std::cout << "  ./todo delete 2          - remove task #2\n\n";
}

int main(int argc, char *argv[])
{
    std::vector<Task> td;

    loadFromFile(td);

    if (argc < 2)
    {
        showUsage();
        return 0;
    }

    std::string command = argv[1];
    if (command == "list")
    {
        listTasks(td);
    }
    else if (command == "add")
    {
        if (argc < 3)
        {
            std::cout << "error: provide a task description\n";
            std::cout << "example: ./todo add \"buy food\"\n";
            return 1;
        }
        addTask(td, argv[2]);
    }
    else if (command == "complete")
    {
        if (argc < 3)
        {
            std::cout << "error provide a task number\n";
            std::cout << "example: ./todo complete 2\n";
            return 1;
        }
        int taskNum = std::stoi(argv[2]);
        completeTask(td, taskNum);
    }
    else if (command == "delete")
    {
        if (argc < 3)
        {
            std::cout << "error: provide a task number\n";
            std::cout << "example: ./todo delete 1\n";
            return 1;
        }
        int taskNum = std::stoi(argv[2]);
        deleteTask(td, taskNum);
    }
    else
    {
        std::cout << "unknown cmd: " << command << "\n";
        showUsage();
    }
    return 0;
}