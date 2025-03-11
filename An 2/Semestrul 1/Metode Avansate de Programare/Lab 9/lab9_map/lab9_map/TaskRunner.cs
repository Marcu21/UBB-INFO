namespace lab9_map;

public interface TaskRunner
{
    void ExecuteOneTask();
    void ExecuteAll();
    void AddTask(Task t);
    bool HasTask();
}
