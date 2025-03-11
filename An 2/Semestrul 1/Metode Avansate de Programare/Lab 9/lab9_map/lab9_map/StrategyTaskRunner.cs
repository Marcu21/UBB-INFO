namespace lab9_map;

public class StrategyTaskRunner : TaskRunner
{
    private readonly Container container;
    
    public StrategyTaskRunner(Strategy strategy)
    {
        TaskContainerFactory factory = TaskContainerFactory.Instance;
        container = factory.CreateContainer(strategy);
    }
    
    public void ExecuteOneTask()
    {
        Task t = container.Remove();
        t.Execute();
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
        container.Add(t);
    }
    
    public bool HasTask()
    {
        return !container.IsEmpty();
    }
}