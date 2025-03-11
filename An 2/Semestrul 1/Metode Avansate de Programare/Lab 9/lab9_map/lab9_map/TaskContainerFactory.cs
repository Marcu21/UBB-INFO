namespace lab9_map;

public class TaskContainerFactory : Factory
{
    private static readonly TaskContainerFactory instance = new TaskContainerFactory();
    
    private TaskContainerFactory() { }
    
    public static TaskContainerFactory Instance
    {
        get
        {
            return instance;
        }
    }
    
    public Container CreateContainer(Strategy strategy)
    {
        if (strategy == Strategy.FIFO)
        {
            //return new QueueContainer();
        }
        else if (strategy == Strategy.LIFO)
        {
            return new StackContainer();
        }
        return null;
    }
}