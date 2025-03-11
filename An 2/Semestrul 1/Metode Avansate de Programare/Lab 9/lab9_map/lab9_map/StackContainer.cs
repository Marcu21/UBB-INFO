namespace lab9_map;

public class StackContainer : Container
{
    protected List<Task> tasks = new List<Task>();
    
    public void Add(Task task)
    {
        tasks.Add(task);
    }
    
    public Task Remove()
    {
        if (IsEmpty())
        {
            return null;
        }
        int last = Size() - 1;
        Task task = tasks[last];
        tasks.RemoveAt(last);
        return task;
    }
    
    public int Size()
    {
        return tasks.Count;
    }
    
    public bool IsEmpty()
    {
        return tasks.Count == 0;
    }
}