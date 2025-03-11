namespace lab9_map;

public class AbstractTaskRunner : TaskRunner
{
    private readonly TaskRunner TaskRunner;
    
    public AbstractTaskRunner(TaskRunner taskRunner)
    {
        TaskRunner = taskRunner;
    }
    
    public void ExecuteOneTask()
    {
        TaskRunner.ExecuteOneTask();
    }
    
    public void ExecuteAll()
    {
        while (HasTask())
        {
            ExecuteOneTask();
        }
    }
    
    public void AddTask(Task t)
    {
        TaskRunner.AddTask(t);
    }
    
    public bool HasTask()
    {
        return TaskRunner.HasTask();
    }
}